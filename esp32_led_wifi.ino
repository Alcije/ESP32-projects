#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

const int ledPin = 2;

void handleRoot() 
{
  String html = "<h1>ESP32 LED Control</h1><a href='/on'>ON</a> | <a href='/off'>OFF</a>";
  server.send(200, "text/html", html);
}

void handleOn() 
{
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location","/");
  server.send(303,"text/plain","");
}

void handleOff() 
{
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location","/");
  server.send(303,"text/plain","");
}

void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() 
{
  server.handleClient();
}
