package com.example.weather;

import com.fasterxml.jackson.databind.JsonNode;
import java.time.Instant;

public class CacheEntry {
  private final JsonNode data;
  private final Instant timestamp;

  public CacheEntry(JsonNode data, Instant timestamp) {
    this.data = data;
    this.timestamp = timestamp;
  }

  public JsonNode getData() {
    return data;
  }

  public Instant getTimestamp() {
    return timestamp;
  }
}
