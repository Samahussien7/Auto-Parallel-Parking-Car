#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

#include <Math.h>

float a1,a2,b1,b2,c1,c2,det;
void trilaterate(float x1, float y1, float d1, float x2, float y2, float d2, float x3, float y3, float d3) {
  a1 = 2 * (x2 - x1);
  b1 = 2 * (y2 - y1);
  c1 = d1 * d1 - d2 * d2 - x1 * x1 + x2 * x2 - y1 * y1 + y2 * y2;

  a2 = 2 * (x3 - x1);
  b2 = 2 * (y3 - y1);
  c2 = d1 * d1 - d3 * d3 - x1 * x1 + x3 * x3 - y1 * y1 + y3 * y3;

  det = a1 * b2 - a2 * b1;

  float resultX = (c1 * b2 - c2 * b1) / det;
  float resultY = (a1 * c2 - a2 * c1) / det;
  Serial.println("--------------------------------------------------");
  Serial.print("Estimated Coordinates : ");
  Serial.print(resultX);
  Serial.print(", ");
  Serial.println(resultY);

}

void setup() {
  Serial.begin(9600);
}
const char* ssidArray[] = {"car1", "car2", "car3"};
float point[3][2] = {{0, 0}, {0, 10}, {5, 5}};
int arraySize = sizeof(ssidArray) / sizeof(ssidArray[0]);

void localization()
{
  double distance[3];
  int numNetworks = WiFi.scanNetworks();
  Serial.println("--------------------------------------------------");
  for (int i = 0; i < numNetworks; i++)
  {
    // Serial.println(WiFi.SSID(i) + " | RSSI: " + String(WiFi.RSSI(i)));
    for (int j = 0; j < arraySize; j++) {
      if(String(WiFi.SSID(i)) == String(ssidArray[j]))
      {
        double s = (-59 - WiFi.RSSI(i)) / (10.0 * 3);
        distance[j] = pow(10.0, s);
        // Serial.println("Whole Term: " + String(s));
        Serial.println(String(ssidArray[j]) + " with RSSI = " + String(WiFi.RSSI(i)));
        Serial.println("has distance of = " + String(distance[j]) + "\n");
      }
    }
  }

  trilaterate(point[0][0],point[0][1],distance[0],point[1][0],point[1][1],distance[1],point[2][0],point[2][1],distance[2]);
}

int flag=1;
void loop() {
  // Do other tasks if needed
  if(flag)localization();
  flag=0;
}

