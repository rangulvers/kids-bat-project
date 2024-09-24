#include <Arduino.h>
#include <LiquidCrystal.h>

// Initialize the LCD library with the numbers of the interface pins
// Adjust the pin numbers according to your wiring
LiquidCrystal lcd(9, 10, 5, 6, 7, 2); //lcd( rs, enable, d4, d5, d6, d7);

const int soundSensorPin = A0;  // Analog pin connected to the sound sensor
const int potiPin = A4;         // Potentiometer connected to analog pin A4
const int ledPin = 13;          // Built-in LED pin on most Arduino boards

const int ledOK = 8;            // LED pin for OK
const int ledLoud = 4;          // LED pin for Loud

float averageSoundLevel = 0;    // Variable to store the average sound level
const float alpha = 0.01;       // Smoothing factor for the moving average

float maxSoundLevel = 0;        // Variable to store the maximum sound level

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledOK, OUTPUT);
  pinMode(ledLoud, OUTPUT);
  Serial.begin(9600);
  
  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.clear();  // Clear the LCD screen

  averageSoundLevel = analogRead(soundSensorPin);  // Initialize the average sound level
}

void loop() {
  float soundValue = analogRead(soundSensorPin);  // Read sound sensor value
  float potiValue = analogRead(potiPin);          // Read potentiometer value

  if (soundValue > maxSoundLevel) {
    maxSoundLevel = soundValue;
  }
  // Normalize potentiometer value to a range (e.g., 0.5 to 2.0)
  float sensitivity = map(potiValue, 10, 1023, 50, 200) / 100.0;

  // Update the average sound level using a simple moving average
  averageSoundLevel = (alpha * soundValue) + ((1 - alpha) * averageSoundLevel);

  // Adjust the threshold based on the potentiometer value and the average sound level
  float threshold = averageSoundLevel + sensitivity;

  // Serial output for debugging
  Serial.print("Sound level: ");
  Serial.println(soundValue);
  Serial.print("Threshold: ");
  Serial.println(threshold);  // Show the dynamically changing threshold
  Serial.print("Average Sound Level: ");
  Serial.println(averageSoundLevel);

  // Update the LCD display to fit 16x2 size
  lcd.setCursor(0, 0);  // Column 0, Row 0
  lcd.print("S:");
  lcd.print(soundValue);
  lcd.print(" T:");
  lcd.print(threshold);

  lcd.setCursor(0, 1);  // Column 0, Row 1
  lcd.print("M:");
  lcd.print(maxSoundLevel);
  lcd.print(" A:");
  lcd.print(averageSoundLevel, 1);  // Display average with 1 decimal place

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
