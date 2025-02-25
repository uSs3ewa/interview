# Weather SDK

## Introduction

The **Weather SDK** provides a simple and efficient way to fetch weather data from the **OpenWeather API**. It supports:

- Fetching real-time weather data for a given city.
- Caching responses for optimized performance.
- Operating in two modes: **ON_DEMAND** and **POLLING**.
- Handling errors like invalid API keys, network failures, and rate limits.

## Features

- **Easy-to-use API** with minimal setup.
- **Supports JSON responses** formatted for easy parsing.
- **Caching mechanism** to store the last 10 weather requests for up to 10 minutes.
- **Polling mode** to update cached cities in the background.
- **Unit-tested for reliability and accuracy.**

## Installation

This project is a **Maven-based Java SDK**.

### Prerequisites

- **Java 11+**
- **Maven**
- An **OpenWeather API Key** (Get it from [OpenWeather](https://openweathermap.org/api))

### Clone the Repository

```sh
git clone https://github.com/yourusername/weather-sdk-java.git
cd weather-sdk-java
```

### Build the Project

```sh
mvn clean package
```

## Usage

### Running the SDK

To run the application and fetch weather data interactively:

```sh
mvn exec:java -Dexec.mainClass="com.example.weather.Main"
```

### Interactive Console Input

The program will prompt for the following inputs:

1. **Enter your OpenWeather API key:** _(Required for authentication)_
2. **Enter the city name:** _(The city you want to fetch weather for)_
3. **Choose mode:**
   - `1` → **ON_DEMAND** (Fetches weather data only when requested)
   - `2` → **POLLING** (Continuously updates cached cities in the background)

### Example Input

```
Enter your OpenWeather API key: 1234567890abcdef
Enter the city name: London
Choose mode (1 - ON_DEMAND, 2 - POLLING): 1
```

### Example Output

```json
{
  "coord": {
    "lon": -0.1257,
    "lat": 51.5085
  },
  "weather": [
    {
      "id": 800,
      "main": "Clear",
      "description": "clear sky",
      "icon": "01n"
    }
  ],
  "main": {
    "temp": 5.22,
    "feels_like": 2.71,
    "pressure": 1018,
    "humidity": 87
  },
  "visibility": 10000,
  "wind": {
    "speed": 3.09,
    "deg": 230
  },
  "clouds": {
    "all": 4
  },
  "sys": {
    "country": "GB",
    "sunrise": 1740466458,
    "sunset": 1740504789
  },
  "timezone": 0,
  "name": "London",
  "cod": 200
}
```

## Code Structure

### **1. Core SDK Files**

- `WeatherSDK.java` → Handles API requests, caching, and polling.
- `WeatherMode.java` → Defines ON_DEMAND and POLLING modes.
- `WeatherSDKException.java` → Custom exception handling.
- `CacheEntry.java` → Stores cached weather data with timestamps.

### **2. API Handling**

- `WeatherAPI.java` → Fetches weather data using OkHttp.
- `WeatherData.java` → Maps JSON responses to Java objects.
- `WeatherException.java` → Handles errors in API requests.

### **3. Background Polling**

- `PollingService.java` → Automatically updates cached weather data.

### **4. Main Application**

- `Main.java` → Accepts user input and fetches weather data.

### **5. Unit Tests**

- `WeatherSDKTest.java` → Verifies key functionalities using JUnit.

## Configuration

### Maven Dependencies

Ensure the following dependencies are included in `pom.xml`:

```xml
<dependencies>
    <dependency>
        <groupId>com.squareup.okhttp3</groupId>
        <artifactId>okhttp</artifactId>
        <version>4.11.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.15.2</version>
    </dependency>
    <dependency>
        <groupId>org.junit.jupiter</groupId>
        <artifactId>junit-jupiter</artifactId>
        <version>5.9.0</version>
        <scope>test</scope>
    </dependency>
</dependencies>
```

## Testing the SDK

Run unit tests using Maven:

```sh
mvn test
```

## Contributions

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.
