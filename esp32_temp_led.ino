#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
#define LEDPIN 2

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot() 
{
  float temp = dht.readTemperature();
  String html = "<h1>ESP32 Temp + LED</h1>";
  html += "<p>Temp: " + String(temp) + " °C</p>";
  html += "<p>LED: <a href='/on'>ON</a> | <a href='/off'>OFF</a></p>";
  server.send(200, "text/html", html);
}

void handleOn() 
{ 
  digitalWrite(LEDPIN,HIGH); server.sendHeader("Location","/"); server.send(303,"text/plain",""); 
}
void handleOff() 
{ 
  digitalWrite(LEDPIN,LOW); server.sendHeader("Location","/"); server.send(303,"text/plain",""); 
}

void setup() 
{
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  { 
    delay(500); Serial.print("."); 
  }
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
