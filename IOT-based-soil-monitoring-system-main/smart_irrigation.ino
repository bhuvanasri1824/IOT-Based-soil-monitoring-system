// Smart Irrigation System using Blynk
// This code is designed to control a water pump based on soil moisture levels
// and can be monitored and controlled via the Blynk app.
#define BLYNK_TEMPLATE_ID "TMPL3F-iFpduH"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "kyACDurbVGByKTC_By7-ZodRcrgZ_PCn";
char ssid[] = "don't ask me";
char pass[] = "123456789";

BlynkTimer timer;
bool Relay = 0;

#define sensor A0
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  timer.setInterval(100L, soilMoistureSensor);
}

BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
  }
}
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);
}

void loop() {
  Blynk.run();
  timer.run();
}