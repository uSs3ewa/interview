package com.example.weather; // Change from com.weather.sdk

import java.util.Timer;
import java.util.TimerTask;

public class PollingService {
    private final WeatherSDK sdk;
    private final Timer timer = new Timer(true);

    public PollingService(WeatherSDK sdk) {
        this.sdk = sdk;
        startPolling();
    }

    private void startPolling() {
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                for (String city : sdk.cache.keySet()) {
                    try {
                        sdk.getWeather(city);
                    } catch (WeatherSDKException ignored) {}
                }
            }
        }, 0, 600_000);
    }
}

