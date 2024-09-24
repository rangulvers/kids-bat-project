
### Components:
1. **Arduino board** (e.g., Uno)
2. **Sound sensor** (connected to analog pin A0)
3. **Potentiometer** (connected to analog pin A1)
4. **Green LED (OK)** (connected to pin 8)
5. **Yellow LED (Loud)** (connected to pin 4)
6. **Resistors** (220 ohm for each LED)
7. **Jumper wires** for connections

### Wiring Diagram:

#### **Sound Sensor**:
- **VCC** -> Arduino **5V**
- **GND** -> Arduino **GND**
- **Out (Signal)** -> Arduino **A0**

#### **Potentiometer**:
- **One outer pin** -> Arduino **5V**
- **Other outer pin** -> Arduino **GND**
- **Middle pin (wiper)** -> Arduino **A1**

#### **Green LED (OK)**:
- **Anode (long leg)** -> Arduino **pin 8**
- **Cathode (short leg)** -> **220-ohm resistor** -> Arduino **GND**

#### **Yellow LED (Loud)**:
- **Anode (long leg)** -> Arduino **pin 4**
- **Cathode (short leg)** -> **220-ohm resistor** -> Arduino **GND**

#### **Built-in LED**:
- This is already connected to **pin 13**, so no external wiring is required for the built-in LED.

### Wiring Summary:

| Component       | Arduino Pin | Description                                      |
|-----------------|-------------|--------------------------------------------------|
| Sound Sensor    | A0          | Analog input from the sound sensor               |
| Potentiometer   | A1          | Analog input from the potentiometer              |
| Green LED       | 8           | Digital pin controlling the "OK" LED             |
| Yellow LED      | 4           | Digital pin controlling the "Loud" LED           |
| Built-in LED    | 13          | Built-in LED on the Arduino                      |
| GND Connections | GND         | Ground connections for the LEDs and components   |
| VCC Connections | 5V          | Power connections for the sound sensor and potentiometer |

This setup will allow you to monitor sound levels and adjust the threshold dynamically with the potentiometer, using the two LEDs to signal whether the sound is within the "OK" range or too loud.
