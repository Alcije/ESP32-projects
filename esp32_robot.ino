#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const int motorLeft = 12;
const int motorRight = 13;
WebServer server(80);

void handleRoot() 
{
  String html = "<h1>ESP32 Robot Control</h1>";
  html += "<a href='/forward'>Forward</a> | <a href='/stop'>Stop</a>";
  server.send(200, "text/html", html);
}

void handleForward() 
{
  digitalWrite(motorLeft,HIGH);
  digitalWrite(motorRight,HIGH);
  server.sendHeader("Location","/");
  server.send(303,"text/plain","");
}

void handleStop() 
{
  digitalWrite(motorLeft,LOW);
  digitalWrite(motorRight,LOW);
  server.sendHeader("Location","/");
  server.send(303,"text/plain","");
}

void setup() 
{
  Serial.begin(115200);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  { 
    delay(500); Serial.print("."); 
  }
  Serial.println("WiFi connected: " + WiFi.localIP().toString());
  
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/stop", handleStop);
  server.begin();
}

void loop() 
{
  server.handleClient();
}
