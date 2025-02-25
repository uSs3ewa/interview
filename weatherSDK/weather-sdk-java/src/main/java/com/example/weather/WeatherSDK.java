package com.example.weather;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import okhttp3.*;

import java.io.IOException;
import java.time.Duration;
import java.time.Instant;
import java.util.*;
import java.util.concurrent.*;

public class WeatherSDK {

  private static final String OPENWEATHER_URL = "https://api.openweathermap.org/data/2.5/weather";

  // Tracks active API keys to ensure no duplicate instance with the same key
  private static final Set<String> ACTIVE_KEYS = new HashSet<>();

  private final String apiKey;
  private final WeatherMode mode;
  private final ObjectMapper objectMapper;
  private final OkHttpClient httpClient;

  // Caching: city -> CacheEntry
  protected final Map<String, CacheEntry> cache = new ConcurrentHashMap<>();
  // Store city fetch order if we need to limit to 10
  final Deque<String> cityOrder = new LinkedList<>();

  // Executor for polling tasks
  private ScheduledExecutorService pollingExecutor;

  /**
   * Main constructor for the SDK.
   * 
   * @param apiKey The OpenWeather API key.
   * @param mode   The mode of SDK operation (ON_DEMAND or POLLING).
   * @throws WeatherSDKException if an SDK with the same API key already exists.
   */
  public WeatherSDK(String apiKey, WeatherMode mode) throws WeatherSDKException {
    // Ensure only one instance per API key
    synchronized (ACTIVE_KEYS) {
      if (ACTIVE_KEYS.contains(apiKey)) {
        throw new WeatherSDKException("An SDK with this API key already exists!");
      }
      ACTIVE_KEYS.add(apiKey);
    }

    this.apiKey = apiKey;
    this.mode = mode;
    this.objectMapper = new ObjectMapper();
    this.httpClient = new OkHttpClient();

    // If in polling mode, schedule periodic updates
    if (mode == WeatherMode.POLLING) {
      startPolling();
    }
  }

  /**
   * Retrieves the weather data for a given city in JSON format.
   * 
   * @param city The city name.
   * @return A {@link JsonNode} containing the weather data.
   * @throws WeatherSDKException if the city is invalid or network/API errors
   *                             occur.
   */
  public JsonNode getWeather(String city) throws WeatherSDKException {
    // Validate city name
    if (city == null || city.isEmpty()) {
      throw new WeatherSDKException("City name must not be empty");
    }

    // Check cache for data that is <10 minutes old
    CacheEntry entry = cache.get(city);
    if (entry != null &&
        Duration.between(entry.getTimestamp(), Instant.now()).toMinutes() < 10) {
      return entry.getData();
    }

    // Fetch fresh data
    return fetchAndCacheWeather(city);
  }

  /**
   * Internal method to fetch data from the OpenWeather API and store in cache.
   */
  private JsonNode fetchAndCacheWeather(String city) throws WeatherSDKException {
    Request request = new Request.Builder()
        .url(OPENWEATHER_URL + "?q=" + city + "&appid=" + apiKey + "&units=metric")
        .build();

    try (Response response = httpClient.newCall(request).execute()) {
      if (!response.isSuccessful()) {
        throw new WeatherSDKException("Failed to fetch weather: " + response.code());
      }
      String body = response.body().string();
      JsonNode node = objectMapper.readTree(body);

      // Cache it
      cacheWeather(city, node);
      return node;
    } catch (IOException e) {
      throw new WeatherSDKException("Network error: " + e.getMessage());
    }
  }

  /**
   * Caches the provided weather data for the city, respecting the 10-city limit.
   */
  private void cacheWeather(String city, JsonNode data) {
    // If city is new and we already have 10 stored, remove the oldest
    if (!cache.containsKey(city) && cache.size() >= 10) {
      String oldest = cityOrder.pollFirst(); // remove first
      if (oldest != null) {
        cache.remove(oldest);
      }
    }
    // If city already exists, remove from queue so we can place it at the end
    cityOrder.remove(city);

    // Insert at the end
    cityOrder.addLast(city);
    cache.put(city, new CacheEntry(data, Instant.now()));
  }

  /**
   * Starts a polling executor that periodically refreshes weather data for all
   * cached cities.
   */
  private void startPolling() {
    pollingExecutor = Executors.newSingleThreadScheduledExecutor();
    // Poll every 5 minutes
    pollingExecutor.scheduleAtFixedRate(() -> {
      for (String city : cache.keySet()) {
        try {
          fetchAndCacheWeather(city);
        } catch (WeatherSDKException e) {
          // Log or handle if needed
        }
      }
    }, 0, 5, TimeUnit.MINUTES);
  }

  /**
   * Deletes the SDK instance: stops polling, clears caches, and frees up the API
   * key.
   */
  public void delete() {
    if (pollingExecutor != null && !pollingExecutor.isShutdown()) {
      pollingExecutor.shutdownNow();
    }
    synchronized (ACTIVE_KEYS) {
      ACTIVE_KEYS.remove(apiKey);
    }
    cache.clear();
    cityOrder.clear();
  }
}
