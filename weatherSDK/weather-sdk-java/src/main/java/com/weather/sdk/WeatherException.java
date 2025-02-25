package com.weather.sdk;

/**
 * Custom exception class for errors in WeatherAPI.
 */
public class WeatherException extends Exception {
    public WeatherException(String message) {
        super(message);
    }
}
