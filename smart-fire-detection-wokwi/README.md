# Smart Fire Detection & Automatic Response System

## Overview

This project is an ESP32-based fire detection and automatic response system developed and simulated using Wokwi.

The system monitors temperature, smoke/gas level, and an LDR-based simulated flame/light condition. The ESP32 processes the sensor readings using threshold-based risk scoring.

When the combined sensor conditions indicate a fire event, the system activates a buzzer and LED for local warning and triggers a relay connected to a simulated pump.

The project demonstrates sensor interfacing, ADC-based data acquisition, GPIO control, embedded decision-making, and automatic response using an ESP32.

---

## Features

- Real-time temperature monitoring using DHT22
- Analog smoke/gas monitoring using MQ-2
- LDR-based simulated flame/light condition
- Threshold-based fire risk calculation
- Audible warning using buzzer
- Visual warning using LED
- Relay-based automatic response
- Pump represented using an LED in Wokwi
- Serial Monitor for real-time sensor readings
- Complete simulation and testing using Wokwi

---

## System Architecture

```text
DHT22 Temperature Sensor ──┐
                           │
MQ-2 Smoke/Gas Sensor ─────┤
                           ├──> ESP32
LDR Simulated Flame/Light ──┘      │
                                  │
                            Risk Analysis
                                  │
                    ┌─────────────┼─────────────┐
                    │             │             │
                    ▼             ▼             ▼
                 Buzzer        Fire LED       Relay
                                                │
                                                ▼
                                        Pump Simulation
```

---

## Working Principle

1. The DHT22 provides the temperature reading.
2. The MQ-2 provides an analog smoke/gas sensor reading.
3. The LDR is used as a simulated flame/light condition in the Wokwi prototype.
4. The ESP32 compares the sensor readings with configured thresholds.
5. A risk score is calculated based on the detected conditions.
6. When the risk score reaches the fire-confirmation threshold, the ESP32:
   - Activates the buzzer.
   - Turns on the fire LED.
   - Activates the relay.
   - Turns on the simulated pump.
7. When the fire condition is not confirmed, the response outputs remain OFF.

---

## Detection Logic

The system uses a simple weighted risk-scoring method:

| Condition | Score |
|---|---:|
| High temperature | +1 |
| High smoke level | +1 |
| Simulated flame/light detected | +2 |

### Fire Decision

```text
Risk Score >= 3
        ↓
Fire detected
        ↓
Buzzer ON
Fire LED ON
Relay ON
Pump simulation ON
```

If the risk score is below 3, the system remains in the SAFE state.

---

## Thresholds Used in Prototype

```cpp
float temperatureThreshold = 50.0;
int smokeThreshold = 2000;
```

These values are prototype/demo thresholds used for simulation.

For a real-world implementation, sensor calibration and controlled testing would be required to determine suitable thresholds.

---

## Pin Connections

| Component | ESP32 Pin |
|---|---|
| DHT22 DATA | GPIO 4 |
| MQ-2 AO | GPIO 34 |
| LDR Output | GPIO 27 |
| Buzzer | GPIO 26 |
| Relay IN | GPIO 25 |
| Fire LED | GPIO 2 |

GPIO 34 is used for the MQ-2 analog output because it is an ADC-capable input on the ESP32.

---

## Testing Scenarios

| Scenario | Temperature | Smoke | Flame/Light | Risk Score | Expected Result |
|---|---|---|---|---:|---|
| Normal | Low | Low | Not Detected | 0 | SAFE |
| Smoke warning | Low | High | Not Detected | 1 | SAFE |
| Temperature warning | High | Low | Not Detected | 1 | SAFE |
| Multiple warning | High | High | Not Detected | 2 | SAFE |
| Fire condition | Low | High | Detected | 3 | FIRE DETECTED |
| Fire condition | High | Low | Detected | 3 | FIRE DETECTED |
| Maximum risk | High | High | Detected | 4 | FIRE DETECTED |

---

## Technologies Used

- ESP32
- Embedded C/C++
- Arduino framework
- Wokwi
- DHT22
- MQ-2
- LDR
- Relay
- Buzzer
- LED
- GPIO
- ADC

---

## Project Limitations

- The project is currently developed and tested in the Wokwi simulator.
- The pump is represented by an LED in the simulation.
- An LDR is used to simulate a flame/light condition instead of a dedicated flame sensor.
- MQ-2 and temperature thresholds are prototype values and require calibration for real deployment.
- The current system uses simple threshold-based risk scoring.
- The system has not been tested on physical fire or hazardous conditions.

---

## Future Enhancements

- Replace the LDR simulation with a dedicated flame sensor.
- Calibrate MQ-2 and temperature thresholds using real-world data.
- Add hysteresis and time-based fire confirmation.
- Add sensor fault detection.
- Add Wi-Fi-based remote notifications.
- Develop a web or mobile monitoring dashboard.
- Store sensor readings for historical analysis.
- Add battery backup.
- Use an appropriately rated pump driver or relay in physical implementation.
- Add multiple sensor nodes for larger-area monitoring.

---

## Project Structure

```text
smart-fire-detection-esp32/
│
├── README.md
│
├── src/
│   └── fire_detection.ino
│
├── docs/
│   ├── architecture.png
│   ├── circuit-diagram.png
│   └── future-enhancements.md
│
├── screenshots/
│   ├── 01-complete-circuit.png
│   ├── 02-safe-condition.png
│   ├── 03-warning-condition.png
│   └── 04-fire-detected.png
│
└── wokwi/
    └── wokwi-link.txt
```

---

## Wokwi Simulation

Wokwi project:

[Open Wokwi Simulation](https://wokwi.com/projects/476428820570747905
)

---

## Author

Dande Vaishnavi
