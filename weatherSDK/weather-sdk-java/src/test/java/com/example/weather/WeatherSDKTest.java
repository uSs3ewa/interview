package com.example.weather;

import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

public class WeatherSDKTest {

  @Test
  void testCreateTwoSDKsSameKeyShouldFail() throws WeatherSDKException {
    WeatherSDK sdk1 = new WeatherSDK("FAKE_KEY", WeatherMode.ON_DEMAND);
    assertThrows(WeatherSDKException.class, () -> {
      new WeatherSDK("FAKE_KEY", WeatherMode.ON_DEMAND);
    });
    sdk1.delete();
  }

  @Test
  void testCacheLimit() throws WeatherSDKException {
    WeatherSDK sdk = new WeatherSDK("ANOTHER_FAKE_KEY", WeatherMode.ON_DEMAND);
    for (int i = 0; i < 12; i++) {
      // We'll see that only the last 10 remain
      try {
        sdk.getWeather("City" + i);
      } catch (WeatherSDKException e) {
        // ignoring fetch failures since we have a fake key
      }
    }
    // We can’t directly check private members, but we expect no error
    // Or you can use reflection to verify internal size is <= 10
    sdk.delete();
  }
}

