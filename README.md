# Ultrasonic Sensor Bat Project

## Introduction

This project simulates a bat's echolocation ability using an ultrasonic sensor, an active buzzer, and a MAX7219 LED matrix display. Designed for educational purposes, it guides students through building and programming an Arduino-based system that responds to distance measurements with sound and visual feedback.

The project is divided into three stages to facilitate step-by-step learning:

1. **Stage 1:** Ultrasonic Sensor Only
2. **Stage 2:** Add Active Buzzer for Sound
3. **Stage 3:** Add MAX7219 Matrix Display

## Table of Contents

- [Components Required](#components-required)
- [Stage 1: Ultrasonic Sensor Only](#stage-1-ultrasonic-sensor-only)
- [Stage 2: Add Active Buzzer for Sound](#stage-2-add-active-buzzer-for-sound)
- [Stage 3: Add MAX7219 Matrix Display](#stage-3-add-max7219-matrix-display)
- [Notes](#notes)
- [License](#license)

## Components Required

- **Arduino Uno**
- **HC-SR04 Ultrasonic Sensor**
- **Active Buzzer**
- **Potentiometer (e.g., 10kΩ)**
- **MAX7219 Dot Matrix LED Display Module**
- **Breadboard and Jumper Wires**

## Stage 1: Ultrasonic Sensor Only

In this stage, you'll set up the ultrasonic sensor to measure distances and display the readings on the Serial Monitor.

### Wiring Diagram

#### Components

- **HC-SR04 Ultrasonic Sensor**

#### Connections

| HC-SR04 Pin | Connects To        |
|-------------|--------------------|
| VCC         | Arduino **5V**     |
| GND         | Arduino **GND**    |
| Trig        | Arduino **Pin 9**  |
| Echo        | Arduino **Pin 10** |

### Instructions

1. **Setup Hardware:**

   - Connect the HC-SR04 ultrasonic sensor to the Arduino according to the wiring diagram.

2. **Upload Code:**

   - Use the provided code in `stage1_ultrasonic_sensor.ino` to read distance measurements.

3. **Test the Sensor:**

   - Open the Serial Monitor in the Arduino IDE to observe distance readings.

---

## Stage 2: Add Active Buzzer for Sound

In this stage, you'll add an active buzzer to provide auditory feedback based on the measured distance. A potentiometer will be used to adjust the volume.

### Wiring Diagram

#### Components

- **Active Buzzer**
- **Potentiometer**

#### Connections

**Active Buzzer**

| Buzzer Pin   | Connects To       |
|--------------|-------------------|
| Positive (+) | Arduino **Pin 8** |
| Negative (-) | Arduino **GND**   |

**Potentiometer**

| Potentiometer Terminal | Connects To        |
|------------------------|--------------------|
| One end terminal       | Arduino **5V**     |
| Other end terminal     | Arduino **GND**    |
| Middle terminal (wiper)| Arduino **A0**     |

### Instructions

1. **Add Components:**

   - Connect the active buzzer and potentiometer to the Arduino as per the wiring diagram.

2. **Upload Updated Code:**

   - Use the code in `stage2_buzzer_sound.ino` which includes sound functionality.

3. **Adjust Volume:**

   - Use the potentiometer to control the buzzer's volume.

4. **Observe Behavior:**

   - The buzzer's beeping frequency will change based on the distance to an object.

---

## Stage 3: Add MAX7219 Matrix Display

In the final stage, you'll add a MAX7219 dot matrix LED display to provide a visual representation of the measured distance.

### Wiring Diagram

#### Components

- **MAX7219 Dot Matrix LED Display Module**

#### Connections

| MAX7219 Pin | Connects To         |
|-------------|---------------------|
| VCC         | Arduino **5V**      |
| GND         | Arduino **GND**     |
| DIN         | Arduino **Pin 7**   |
| CS (LOAD)   | Arduino **Pin 6**   |
| CLK         | Arduino **Pin 5**   |

### Instructions

1. **Add the Display Module:**

   - Connect the MAX7219 dot matrix display module to the Arduino following the wiring diagram.

2. **Upload Final Code:**

   - Use the code in `stage3_matrix_display.ino` which includes display functionality.

3. **Test the System:**

   - Observe how the LED display visually represents the distance to objects.

4. **Combine Feedback:**

   - The system now provides both auditory and visual feedback based on distance measurements.

---

## Notes

- **Libraries Required:**

  - **NewPing Library:** Used for the ultrasonic sensor.
  - **LedControl Library:** Used for controlling the MAX7219 display.

  Install these libraries via the Arduino Library Manager.

- **Power Considerations:**

  - Ensure the total current draw does not exceed the Arduino's capabilities.
  - If necessary, use an external power supply for the MAX7219 display, ensuring common ground with the Arduino.

- **Avoiding Timer Conflicts:**

  - The code avoids using functions that rely on hardware timers to prevent conflicts with the `NewPing` library.

- **Educational Use:**

  - This project is ideal for teaching students about sensors, actuators, and microcontroller programming.
  - The step-by-step stages help build foundational knowledge before integrating more complex components.

---


Feel free to explore and modify the project to suit your educational needs. Contributions are welcome!
