#include "HX711.h"

HX711 scale;

#define DT_PIN 4
#define SCK_PIN 5

float calibration_factor = -417.0727046;

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
    sum += scale.get_value(1); // raw ADC value
    delay(10);
  }
  return (float)sum / samples;
}

void setup() {
  Serial.begin(9600);
  scale.begin(DT_PIN, SCK_PIN);
}

void loop() {

  Serial.println("\n========== New Trial =========");

  waitForEnter("Press ENTER to tare (remove offset).");

  Serial.println("Taring.... remove all weight.");
  delay(2000);
  scale.tare();

  long offset = scale.get_offset();
  Serial.print("Offset stored: ");
  Serial.println(offset);

  Serial.println("Offset removed.");
  waitForEnter("Press ENTER to begin taking 20 Newton readings.");

  float sumN = 0;

  for (int i = 0; i < 20; i++) {

    // Raw ADC average over 20 samples
    float raw = averageRaw(10);

    // Convert raw ==> grams
    float grams = raw / calibration_factor;

    // Grams ==> Newtons
    float newtons = (grams / 1000.0) * 9.81;

    sumN += newtons;

    // ----- PRINT EVERYTHING ----
    Serial.print("Reading ");
    Serial.print(i + 1);
    Serial.print(": Raw = ");
    Serial.print(raw);
    Serial.print(" | g = ");
    Serial.print(grams, 5);
    Serial.print(" | N = ");
    Serial.print(newtons, 5);
    Serial.println();
  }

  float avgN = sumN / 20.0;

  Serial.println("\n=== Result ===");
  Serial.print("Average Force: ");
  Serial.print(avgN, 5);
  Serial.println(" N");
  Serial.println("==============\n");

  while (1);
}
