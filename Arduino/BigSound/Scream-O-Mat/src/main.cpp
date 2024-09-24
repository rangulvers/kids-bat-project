#include <Arduino.h>

const int soundSensorPin = A0;  // Analog pin connected to the sound sensor
const int potiPin = A4;         // Potentiometer connected to analog pin A1
const int ledPin = 13;          // Built-in LED pin on most Arduino boards

const int ledOK = 8;            // LED pin for OK
const int ledLoud = 4;          // LED pin for Loud

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledOK, OUTPUT);
  pinMode(ledLoud, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int soundValue = analogRead(soundSensorPin);  // Read sound sensor value
  int threshold = analogRead(potiPin);          // Read potentiometer value to adjust threshold
  
  Serial.print("Sound level: ");
  Serial.println(soundValue);
  Serial.print("Threshold: ");
  Serial.println(threshold);  // Show the dynamically changing threshold

  // Check if the sound level exceeds the threshold
  if (soundValue > threshold) {
    digitalWrite(ledPin, HIGH);   // Built-in LED ON
    Serial.println("Loud sound detected!");
    digitalWrite(ledLoud, HIGH);  // Loud LED ON
    digitalWrite(ledOK, LOW);     // OK LED OFF
  } else {
    digitalWrite(ledOK, HIGH);    // OK LED ON
    digitalWrite(ledLoud, LOW);   // Loud LED OFF
    digitalWrite(ledPin, LOW);    // Built-in LED OFF
  }
  
  delay(50);  // Short delay to avoid flooding the serial monitor
}
