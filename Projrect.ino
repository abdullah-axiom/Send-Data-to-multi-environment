#include <WiFiUdp.h>
#include <NTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <UniversalTelegramBot.h>

String emailfrom = "esp8266@gmail.com";
String emailto = "afayad@axiomworks.ai";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initWiFi();
}

void loop() {
  int degree = analogRead(A0);
  int other = random(1023);
  send_localdb(degree,other);
  telegram(degree,other);
  to_iothub(degree,other);
  delay(5000);
}
