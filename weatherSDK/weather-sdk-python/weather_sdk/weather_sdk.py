import threading
import time
from collections import OrderedDict
from datetime import datetime

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
            # Start a background thread to periodically refresh data
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
                if (time.time() - ts) < 600:  # 600 seconds = 10 min
                    # Return cached if <10 min
                    return data

        # If cache not valid, fetch new
        return self._fetch_and_cache_weather(city)

    def _fetch_and_cache_weather(self, city: str) -> dict:
        params = {"q": city, "appid": self._api_key, "units": "metric"}
        resp = requests.get(self.OPENWEATHER_URL, params=params)
        if not resp.ok:
            raise WeatherSDKException(
                f"Failed to fetch weather: HTTP {resp.status_code} {resp.text}"
            )
        data = resp.json()
        with self._lock:
            self._cache_weather(city, data)
        return data

    def _cache_weather(self, city: str, data: dict):
        # If new city and we have >= 10, pop oldest
        if city not in self._cache and len(self._cache) >= 10:
            self._cache.popitem(last=False)  # pop first inserted

        # If city in cache, remove it to re-insert
        if city in self._cache:
            del self._cache[city]

        self._cache[city] = (data, time.time())

    def _polling_loop(self):
        while True:
            with self._lock:
                for city in self._cache.keys():
                    try:
                        self._fetch_and_cache_weather(city)
                    except WeatherSDKException:
                        pass
            time.sleep(300)  # 5 minutes

    def delete(self):
        # Clean up
        if self._mode == WeatherMode.POLLING and self._polling_thread:
            # Thread is daemon, so it ends when the main process ends.
            # We could implement an event to signal stop if we need a clean exit in this environment.
            pass
        if self._api_key in _ACTIVE_KEYS:
            _ACTIVE_KEYS.remove(self._api_key)
        with self._lock:
            self._cache.clear()
