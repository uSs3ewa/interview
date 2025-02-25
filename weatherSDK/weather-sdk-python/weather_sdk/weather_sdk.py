import threading
import time
from collections import OrderedDict

import requests

from .exceptions import WeatherSDKException
from .weather_mode import WeatherMode

_ACTIVE_KEYS = set()


class WeatherSDK:
    OPENWEATHER_URL = "https://api.openweathermap.org/data/2.5/weather"

    def __init__(self, api_key: str, mode: WeatherMode):
        if api_key in _ACTIVE_KEYS:
            raise WeatherSDKException("An SDK with this API key already exists!")
        _ACTIVE_KEYS.add(api_key)

        self._api_key = api_key
        self._mode = mode
        self._cache = OrderedDict()  # city -> (data, timestamp)
        self._lock = threading.Lock()

        if self._mode == WeatherMode.POLLING:
            self._polling_thread = threading.Thread(
                target=self._polling_loop, daemon=True
            )
            self._polling_thread.start()
        else:
            self._polling_thread = None

    def get_weather(self, city: str) -> dict:
        if not city:
            raise WeatherSDKException("City name must not be empty")

        with self._lock:
            if city in self._cache:
                data, ts = self._cache[city]
                if (time.time() - ts) < 600:  # Cache valid for 10 min
                    return data

        return self._fetch_and_cache_weather(city)

    def _fetch_and_cache_weather(self, city: str) -> dict:
        params = {"q": city, "appid": self._api_key, "units": "metric"}
        try:
            resp = requests.get(self.OPENWEATHER_URL, params=params)
            if resp.status_code == 401:
                raise WeatherSDKException("Invalid API Key. Please check your API key.")
            elif resp.status_code == 404:
                raise WeatherSDKException(f"City '{city}' not found.")
            elif not resp.ok:
                raise WeatherSDKException(
                    f"Failed to fetch weather: HTTP {resp.status_code} {resp.text}"
                )

            data = resp.json()
            with self._lock:
                self._cache_weather(city, data)
            return data

        except requests.exceptions.RequestException as e:
            raise WeatherSDKException(f"Network error: {e}")

    def _cache_weather(self, city: str, data: dict):
        if city not in self._cache and len(self._cache) >= 10:
            self._cache.popitem(last=False)

        if city in self._cache:
            del self._cache[city]

        self._cache[city] = (data, time.time())

    def _polling_loop(self):
        while True:
            with self._lock:
                for city in list(self._cache.keys()):
                    try:
                        self._fetch_and_cache_weather(city)
                    except WeatherSDKException:
                        pass
            time.sleep(300)

    def delete(self):
        if self._api_key in _ACTIVE_KEYS:
            _ACTIVE_KEYS.remove(self._api_key)
        with self._lock:
            self._cache.clear()
