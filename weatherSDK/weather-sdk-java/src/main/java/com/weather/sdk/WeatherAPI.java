package com.weather.sdk;

import com.fasterxml.jackson.databind.ObjectMapper;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import java.io.IOException;

public class WeatherAPI {
  private static final String BASE_URL = "https://api.openweathermap.org/data/2.5/weather";
  private static final OkHttpClient client = new OkHttpClient();
  private static final ObjectMapper objectMapper = new ObjectMapper();

  public static WeatherData fetchWeather(String city, String apiKey) throws WeatherException {
    String url = BASE_URL + "?q=" + city + "&appid=" + apiKey + "&units=metric";
    Request request = new Request.Builder().url(url).build();

    try (Response response = client.newCall(request).execute()) {
      if (!response.isSuccessful()) {
        throw new WeatherException("Failed to fetch weather data: " + response.message());
      }
      return objectMapper.readValue(response.body().string(), WeatherData.class);
    } catch (IOException e) {
      throw new WeatherException("Network error: " + e.getMessage());
    }
  }
}
