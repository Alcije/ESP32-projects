#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int ledPin = 2;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
}

void loop() 
{
  if (SerialBT.available()) 
  {
    char cmd = SerialBT.read();
    if (cmd == '1') digitalWrite(ledPin, HIGH);
    if (cmd == '0') digitalWrite(ledPin, LOW);
  }
}
