# Weather SDK for Java

## Installation

1. Clone the repo into `/home/stoat/interview/weatherSDK/java/`.
2. Run `mvn clean install` to build the project.

## Usage Example

```java
import com.example.weather.*;

public class Main {
    public static void main(String[] args) {
        try {
            WeatherSDK sdk = new WeatherSDK("YOUR_API_KEY", WeatherMode.ON_DEMAND);
            // Retrieve weather for London
            System.out.println("London Weather: " + sdk.getWeather("London"));
            // Cleanup
            sdk.delete();
        } catch (WeatherSDKException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
```
