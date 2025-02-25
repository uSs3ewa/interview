package com.example.weather;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Ask for API key
        System.out.print("Enter your OpenWeather API key: ");
        String apiKey = scanner.nextLine().trim();

        // Ask for city name
        System.out.print("Enter the city name: ");
        String city = scanner.nextLine().trim();

        // Ask for mode selection
        System.out.print("Choose mode (1 - ON_DEMAND, 2 - POLLING): ");
        int modeChoice = scanner.nextInt();
        scanner.nextLine(); // Consume newline

        WeatherMode mode = (modeChoice == 2) ? WeatherMode.POLLING : WeatherMode.ON_DEMAND;

        try {
            // Initialize SDK
            WeatherSDK sdk = new WeatherSDK(apiKey, mode);

            // Fetch and print weather data
            System.out.println("Fetching weather data for " + city + "...");
            var weatherDataJson = sdk.getWeather(city);

            // Print the JSON response in readable format
            System.out.println(weatherDataJson.toPrettyString());

            // Cleanup SDK instance
            sdk.delete();
        } catch (WeatherSDKException e) {
            System.err.println("Error: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}

