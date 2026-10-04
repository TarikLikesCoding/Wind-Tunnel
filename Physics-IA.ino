#include "HX711.h"

HX711 scale;

#define DT_PIN 4
#define SCK_PIN 5

void clearSerialBuffer() {
  while (Serial.available() > 0) Serial.read();
}

void waitForEnter(const char* msg) {
  Serial.println(msg);
  clearSerialBuffer();
  while (Serial.available() == 0) {}
  Serial.read();
}

float averageRaw(int samples) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += scale.get_value(1);  // raw value
    delay(10);
  }
  return (float)sum / samples;
}

void setup() {
  Serial.begin(9600);
  scale.begin(DT_PIN, SCK_PIN);

  Serial.println("=== HX711 Calibration Mode ===");
  waitForEnter("Press ENTER to tare (remove offset).");

  Serial.println("Taring... remove all weight.");
  delay(2000);
  scale.tare();

  // Print offset
  long offset = scale.get_offset();
  Serial.print("Offset stored: ");
  Serial.println(offset);

  Serial.println("Offset removed.");
  waitForEnter("Place known mass, then press ENTER.");
  Serial.println("Enter known mass in grams:");
}

float knownMass = 0;

void loop() {
  if (knownMass == 0 && Serial.available() > 0) {
    // Read entire line from Serial Monitor until newline
    String line = Serial.readStringUntil('\n');
    knownMass = line.toFloat();  // convert full line to float

    if (knownMass <= 0) {
      Serial.println("Invalid mass. Try again:");
      knownMass = 0;  // reset to retry
      return;
    }

    Serial.print("Using known mass: ");
    Serial.print(knownMass);
    Serial.println(" g");

    delay(2000);

    Serial.println("Collecting 30 averaged raw readings...");
    float rawAvg = averageRaw(30);

    Serial.print("Average raw value: ");
    Serial.println(rawAvg);

    // calibration factor = raw value / mass
    float calibFactor = rawAvg / knownMass;

    Serial.println("\n=== CALIBRATION RESULT ===");
    Serial.print("Calibration Factor = ");
    Serial.println(calibFactor, 6);
    Serial.println("Copy this number into your measurement code.");
    Serial.println("===========================\n");
  }
}