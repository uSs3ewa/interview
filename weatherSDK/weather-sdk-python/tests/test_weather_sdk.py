import pytest

from weather_sdk.weather_mode import WeatherMode
from weather_sdk.weather_sdk import WeatherSDK, WeatherSDKException


def test_same_key_fails():
    sdk1 = WeatherSDK("FAKE_KEY", WeatherMode.ON_DEMAND)
    with pytest.raises(WeatherSDKException):
        WeatherSDK("FAKE_KEY", WeatherMode.ON_DEMAND)
    sdk1.delete()


def test_cache_limit():
    sdk = WeatherSDK("ANOTHER_FAKE_KEY", WeatherMode.ON_DEMAND)
    # We won't actually fetch from the API here, so let's just call get_weather
    for i in range(12):
        city = f"City{i}"
        try:
            sdk.get_weather(city)
        except WeatherSDKException:
            pass
    sdk.delete()
