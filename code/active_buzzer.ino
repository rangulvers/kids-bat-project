#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 8
#define POT_PIN A0
#define MAX_DISTANCE 400  // Maximum distance to measure (in cm)

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  unsigned long duration;
  unsigned int distance;

  // Read the potentiometer value to adjust beep duration
  int potValue = analogRead(POT_PIN);
  int volumeLevel = map(potValue, 0, 1023, 0, 100);

  // Send a 10us pulse to trigger the sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

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

    // Calculate beep interval based on distance
    unsigned int beepInterval;
    if (distance <= 10) {
      beepInterval = 100;  // Very close object, beep every 100 ms
    } else if (distance <= 100) {
      beepInterval = map(distance, 10, 100, 100, 1000);  // Interval from 100ms to 1000ms
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
