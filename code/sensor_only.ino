#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 400  // Maximum distance to measure (in cm)

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  unsigned long duration;
  unsigned int distance;

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
  }

  delay(200);
}
