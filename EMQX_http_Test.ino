#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "xxx";
const char* password = "xxx";

WiFiClient wifiClient; // Create a WiFiClient object
HTTPClient http; // Declare the HTTPClient object here

// Replace with your EMQX server URL (without the trailing slash)
const char* emqx_server = "http://xxx.xxx.xxx.xxx:18083"; //public ip?

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Your other setup code here...
}

void loop() {
    // Check if WiFi is still connected
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi connection lost. Reconnecting...");
        WiFi.reconnect();
    }

    // Check if HTTP connection is still active
    if (!wifiClient.connected()) {
        Serial.println("HTTP connection lost. Reconnecting...");
        http.begin(wifiClient, "http://xxx.xxx.xxx.xxx:18083/"); // Use any valid URL for testing
        int httpCode = http.GET();
        if (httpCode == 200) {
            Serial.println("HTTP connection re-established.");
        } else {
            Serial.println("Error reconnecting to HTTP server.");
        }
        http.end(); // Close the connection
    }

    // Your other loop code here...

    delay(1000); // Adjust the delay as needed
}
