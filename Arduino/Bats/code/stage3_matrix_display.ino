#include <LedControl.h>
#include <NewPing.h>

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 8
#define POT_PIN A0
#define DIN_PIN 7    // MAX7219 DIN pin
#define CS_PIN 6     // MAX7219 CS pin (LOAD)
#define CLK_PIN 5    // MAX7219 CLK pin
#define MAX_DISTANCE 400  // Maximum distance to measure (in cm)

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);  // Initialize for one MAX7219 device
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false);    // Wake up the MAX7219
  lc.setIntensity(0, 8);    // Set brightness level (0-15)
  lc.clearDisplay(0);       // Clear display
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  unsigned int distance = sonar.ping_cm();

  // Read the potentiometer value to adjust beep duration
  int potValue = analogRead(POT_PIN);
  int volumeLevel = map(potValue, 0, 1023, 0, 100);

  if (distance == 0 || distance > MAX_DISTANCE) {
    Serial.println("No object detected within range.");
    lc.clearDisplay(0);    // Clear the display
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    lc.clearDisplay(0);

    if (distance <= 10) {
      // Light up all rows for distances 10 cm or less
      for (int row = 0; row <= 7; row++) {
        lc.setRow(0, row, B11111111);
      }
    } else if (distance <= 100) {
      // Map distances between 10 cm and 100 cm to numRows from 8 to 1
      int numRows = map(distance, 10, 100, 8, 1);
      numRows = constrain(numRows, 1, 8);

      // Light up rows from bottom upwards
      for (int row = 7; row >= 7 - (numRows - 1); row--) {
        lc.setRow(0, row, B11111111);
      }
    } else {
      // Light up only the bottom row for distances beyond 100 cm
      lc.setRow(0, 7, B11111111);
    }

    // Calculate beep interval based on distance
    unsigned int beepInterval;
    if (distance <= 10) {
      beepInterval = 100;  // Very close object, beep every 100 ms
    } else if (distance <= 100) {
      beepInterval = map(distance, 10, 100, 100, 1000);
    } else {
      beepInterval = 0;  // No beep for distances beyond 100 cm
    }

    // Control the active buzzer
    if (volumeLevel > 0 && beepInterval > 0) {
      int beepDuration = map(volumeLevel, 0, 100, 0, 50);  // Beep duration from 0 to 50 ms
      if (beepDuration > 0) {
        digitalWrite(BUZZER_PIN, HIGH);   // Turn buzzer on
        delay(beepDuration);              // Beep duration
        digitalWrite(BUZZER_PIN, LOW);    // Turn buzzer off
        delay(beepInterval - beepDuration); // Wait for the rest of the interval
      }
    }
  }

  delay(50);  // Small delay to prevent excessive looping
}
