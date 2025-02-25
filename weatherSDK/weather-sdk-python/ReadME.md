# Weather SDK (Python)

## Introduction

The **Weather SDK** for Python provides an easy-to-use interface to fetch weather data from the **OpenWeather API**. It supports:

- Fetching real-time weather data for a given city.
- Caching responses for optimized performance.
- Operating in two modes: **ON_DEMAND** and **POLLING**.
- Handling errors like invalid API keys, network failures, and rate limits.

## Features

- **Simple API** with minimal setup.
- **JSON responses** formatted for easy parsing.
- **Caching mechanism** to store the last 10 weather requests for up to 10 minutes.
- **Polling mode** to update cached cities in the background.
- **Unit-tested for reliability and accuracy.**

## Installation

### Prerequisites

- **Python 3.8+**
- An **OpenWeather API Key** (Get it from [OpenWeather](https://openweathermap.org/api))

### Clone the Repository

```sh
git clone https://github.com/yourusername/weather-sdk-python.git
cd weather-sdk-python
```

### Install Dependencies

```sh
pip install -r requirements.txt
```

### Install the SDK as a Package

```sh
pip install .
```

## Usage

### Running the SDK

You can use `demo.py` to interactively fetch weather data:

```sh
python demo.py
```

### Example `demo.py`

```python
from weather_sdk.weather_sdk import WeatherSDK
from weather_sdk.weather_mode import WeatherMode

def main():
    api_key = input("Enter your OpenWeather API key: ").strip()
    city = input("Enter the city name: ").strip()
    mode_choice = input("Choose mode (1 - ON_DEMAND, 2 - POLLING): ").strip()

    mode = WeatherMode.POLLING if mode_choice == "2" else WeatherMode.ON_DEMAND

    sdk = WeatherSDK(api_key, mode)
    print(f"Fetching weather data for {city}...")

    try:
        weather_data = sdk.get_weather(city)
        print(weather_data)
    except Exception as e:
        print(f"Error: {e}")
    finally:
        sdk.delete()

if __name__ == "__main__":
    main()
```

### Example Console Input

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

- `weather_sdk.py` → Handles API requests, caching, and polling.
- `weather_mode.py` → Defines ON_DEMAND and POLLING modes.
- `exceptions.py` → Custom exception handling.
- `cache_entry.py` → Stores cached weather data with timestamps.

### **2. Main Application**

- `demo.py` → Accepts user input and fetches weather data.

### **3. Installation & Dependencies**

- `setup.py` → Defines package installation.
- `requirements.txt` → Lists dependencies.
- `pyproject.toml` → Supports package management.

## Configuration

### **Dependencies (requirements.txt)**

Ensure the following dependencies are installed:

```sh
requests
```

If needed, manually install:

```sh
pip install requests
```

## Testing the SDK

Run unit tests using pytest:

```sh
pytest tests/
```

## Contributions

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.

#### My personal steps for accessing SDK

```
cd /home/stoat/interview/weatherSDK/weather-sdk-python

python3 -m venv venv

source venv/bin/activate.fish

pip install -r requirements.txt

python demo.py
```
