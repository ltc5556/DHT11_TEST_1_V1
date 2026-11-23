// DHT11 + LED blink by temperature/humidity
// LED on pin 13 (UNO onboard LED). Blink faster when hotter / more humid.

#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define LEDPIN 13

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DHT11_TEST_1_V1 with LED"));
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    // error: blink very fast
    blinkLed(80, 6);
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F(" C"));

  // Blink interval (ms): hotter or more humid -> shorter delay -> faster blink
  // Base 600ms, minus temperature and humidity contribution, clamp to 100~800
  int interval = 600 - (int)(t * 8) - (int)(h * 2);
  if (interval < 100) interval = 100;
  if (interval > 800) interval = 800;

  Serial.print(F("LED blink interval(ms): "));
  Serial.println(interval);

  // Blink several times this round, then read sensor again
  blinkLed(interval, 4);
}

void blinkLed(int intervalMs, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LEDPIN, HIGH);
    delay(intervalMs);
    digitalWrite(LEDPIN, LOW);
    delay(intervalMs);
  }
}
