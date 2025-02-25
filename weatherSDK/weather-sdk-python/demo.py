import json

from weather_sdk.weather_mode import WeatherMode
from weather_sdk.weather_sdk import WeatherSDK


def main():
    print("Welcome to Weather SDK!")

    # Ask user for API Key
    api_key = input("Enter your OpenWeather API key: ").strip()

    # Ask user for City Name
    city = input("Enter the city name: ").strip()

    # Ask user to choose mode
    mode_choice = input("Choose mode (1 - ON_DEMAND, 2 - POLLING): ").strip()
    mode = WeatherMode.POLLING if mode_choice == "2" else WeatherMode.ON_DEMAND

    try:
        # Initialize SDK
        sdk = WeatherSDK(api_key, mode)

        # Fetch and print weather data
        print(f"Fetching weather data for {city}...\n")
        weather_data = sdk.get_weather(city)

        # Print JSON in readable format
        print(json.dumps(weather_data, indent=2))

    except Exception as e:
        print(f"\n❌ Error: {e}")

    finally:
        # Clean up SDK instance
        sdk.delete()


if __name__ == "__main__":
    main()
