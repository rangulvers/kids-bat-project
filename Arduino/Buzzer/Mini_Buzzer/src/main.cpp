#include <Arduino.h>

#define BUZZER_PIN 10

int NOTE_C4 = 262;
int NOTE_G3 = 196;
int NOTE_A3 = 220;
int NOTE_B3 = 247;
// Define the notes and their durations
const int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

const int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Play the melody
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(BUZZER_PIN, melody[i], noteDuration);
    delay(noteDuration);
    noTone(BUZZER_PIN);
    delay(50);
  }
}
