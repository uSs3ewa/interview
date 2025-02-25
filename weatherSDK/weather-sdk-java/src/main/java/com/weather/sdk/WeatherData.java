package com.weather.sdk;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

@JsonIgnoreProperties(ignoreUnknown = true)
public class WeatherData {
  public WeatherMain main;
  public Wind wind;
  public int visibility;
  public long dt;
  public Sys sys;
  public String name;
  public int timezone;

  public static class WeatherMain {
    public double temp;
    public double feels_like;
  }

  public static class Wind {
    public double speed;
  }

  public static class Sys {
    public long sunrise;
    public long sunset;
  }
}
