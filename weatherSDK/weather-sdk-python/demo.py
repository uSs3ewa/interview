from weather_sdk.weather_mode import WeatherMode
from weather_sdk.weather_sdk import WeatherSDK

API_KEY = "0a3b489ccf8c8d9cc7f05752526e9f62"

sdk = WeatherSDK(API_KEY, WeatherMode.ON_DEMAND)
print(sdk.get_weather("London"))
sdk.delete()
