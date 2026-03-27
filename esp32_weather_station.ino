#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
#define LEDPIN 2
#define LDRPIN 34

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

DHT dht(DHTPIN,DHTTYPE);
WebServer server(80);

void handleRoot() 
{
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int light = analogRead(LDRPIN);
  
  String html = "<h1>ESP32 Weather Station</h1>";
  html += "<p>Temp: "+String(temp)+" °C</p>";
  html += "<p>Humidity: "+String(hum)+" %</p>";
  html += "<p>Light: "+String(light)+"</p>";
  
  if(temp>28) html += "<p style='color:red;'>Too Hot!</p>";
  
  server.send(200,"text/html",html);
}

void setup() 
{
  pinMode(LEDPIN, OUTPUT);
  dht.begin();
  Serial.begin(115200);
  
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  { 
    delay(500); Serial.print("."); 
  }
  Serial.println("WiFi connected: "+WiFi.localIP().toString());
  
  server.on("/",handleRoot);
  server.begin();
}

void loop() 
{
  server.handleClient();
}
