#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const int ldrPin = 34;
WebServer server(80);

void handleRoot() 
{
  int ldrValue = analogRead(ldrPin);
  String html = "<h1>ESP32 Light Sensor</h1>";
  html += "<p>Light Level: " + String(ldrValue) + "</p>";
  server.send(200, "text/html", html);
}

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) 
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
