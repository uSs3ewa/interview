package com.example.weather;

/**
 * A custom exception class for Weather SDK errors.
 */
public class WeatherSDKException extends Exception {
    public WeatherSDKException(String message) {
        super(message);
    }
}

