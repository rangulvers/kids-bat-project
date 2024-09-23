#include <Arduino.h>

#define BUZZER_PIN 8
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 400  // Maximum distance to measure (in cm)

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(13,OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  unsigned long duration;
  unsigned int distance;

  // Send a 10us pulse to trigger the sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  digitalWrite(13,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  digitalWrite(13,LOW);

  // Read the echo pin
  duration = pulseIn(ECHO_PIN, HIGH, MAX_DISTANCE * 58 * 2); // Timeout based on max distance

  if (duration == 0 || duration >= MAX_DISTANCE * 58 * 2) {
    // No echo received or object out of range
    Serial.println("No object detected within range.");
  } else {
    // Calculate distance in cm
    distance = duration / 58; // Speed of sound: 1 cm per 58 us
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Calculate beep interval and beep duration based on distance
    unsigned int beepInterval;
    unsigned int beepDuration;

    if (distance <= 25) {
      beepInterval = 50;  // Very close object, beep every 50 ms
      beepDuration = 30;   // Long beep duration for very close objects
    } else if (distance <= 200) {
      beepInterval = map(distance, 25, 200, 50, 1000);  // Interval from 50ms to 1000ms
      beepDuration = map(distance, 25, 200, 30, 10);    // Beep duration decreases with distance
    } else {
      beepInterval = 0;   // No beep for distances beyond 200 cm
      beepDuration = 0;
    }

    // Control the active buzzer
    if (beepInterval > 0 && beepDuration > 0) {
      digitalWrite(BUZZER_PIN, HIGH);   // Turn buzzer on
      delay(beepDuration);              // Beep duration
      digitalWrite(BUZZER_PIN, LOW);    // Turn buzzer off
      delay(beepInterval - beepDuration); // Wait for the rest of the interval
    }
  }

  delay(50);  // Small delay to avoid overwhelming the loop
}
