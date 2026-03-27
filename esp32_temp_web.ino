#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot() 
{
  float temp = dht.readTemperature();
  String html = "<h1>ESP32 Temperature</h1><p>Temp: " + String(temp) + " °C</p>";
  server.send(200, "text/html", html);
}

void setup() 
{
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500); Serial.print("."); 
  }
  Serial.println("WiFi connected: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.begin();
}

void loop() 
{
  server.handleClient();
}
