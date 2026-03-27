#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const int trig = 5;
const int echoPin = 18;
WebServer server(80);

long readDistance() 
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void handleRoot() 
{
  long dist = readDistance();
  String html = "<h1>ESP32 Sonar</h1>";
  html += "<p>Distance: " + String(dist) + " cm</p>";
  if(dist < 20) html += "<p style='color:red;'>Obstacle detected!</p>";
  server.send(200, "text/html", html);
}

void setup() 
{
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echoPin, INPUT);
  
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
