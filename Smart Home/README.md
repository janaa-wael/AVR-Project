# 🌟 Smart Home Automation Using ATmega32, LCD, Temperature Sensor, LDR Sensor, Flame Sensor, and Motor Control

## 🎯 Objective
To design and implement a smart home system that automates lighting and fan speed based on environmental conditions. The project uses an **ATmega32 microcontroller**, **LM35 temperature sensor**, **LDR (Light Dependent Resistor)**, **Flame sensor**, and a **PWM-controlled motor**. An **LCD** provides real-time display, and an **H-bridge circuit** controls the fan motor. LEDs indicate varying light intensity levels.

---

## 🛠️ Project Overview

This project develops a smart home system that adjusts lighting, fan speed, and safety alerts based on environmental conditions:

1. **Lighting Control:** The LDR detects ambient light intensity and controls three LEDs to indicate different light levels.
2. **Fan Speed Control:** The LM35 temperature sensor adjusts the fan speed proportionally to the room temperature.
3. **Fire Detection:** A flame sensor detects fire, triggers an alarm, and displays a critical alert on the LCD.
4. **LCD Display:** Shows real-time temperature readings, fan status, light intensity, and alerts.

---

## ✨ Features

- **Automatic Lighting Control:**  
  Based on the LDR readings, the system controls three LEDs according to light intensity thresholds:
  - Intensity < 15%: All 3 LEDs (Red, Green, and Blue) turn ON.
  - Intensity 16%–50%: Red and Green LEDs turn ON.
  - Intensity 51%–70%: Only the Red LED turns ON.
  - Intensity > 70%: All LEDs are turned OFF.
  
- **Automatic Fan Speed Control:**  
  Fan speed is automatically adjusted based on room temperature:
  - Temperature ≥ 40°C: Fan ON at 100% speed.
  - Temperature ≥ 35°C and < 40°C: Fan ON at 75% speed.
  - Temperature ≥ 30°C and < 35°C: Fan ON at 50% speed.
  - Temperature ≥ 25°C and < 30°C: Fan ON at 25% speed.
  - Temperature < 25°C: Fan OFF.
  
- **Fire Detection and Alert:**  
  If fire is detected:
  - The system raises an alarm.
  - Displays "Critical alert!" on the LCD.
  - Stays in alert mode until the flame is no longer detected.
  
- **LCD Display:**  
  Provides real-time feedback:
  - First row: Displays "FAN is ON" or "FAN is OFF."
  - Second row: Displays "Temp= xx°C LDR= xxx%" showing temperature and light intensity.

---

## 🔧 Hardware Components

- **Microcontroller:** ATmega32
- **Light Sensor:** LDR (Connected to PA0, ADC Channel 0)
- **Temperature Sensor:** LM35 (Connected to PA1, ADC Channel 1)
- **Display:** 16x2 LCD in 8-bit mode  
  - RS: PD0  
  - Enable: PD1  
  - R/W: Ground  
  - Data Pins: PORTC (8-bit mode)
- **Motor Control:** H-Bridge for fan speed control  
  - IN1: PB0  
  - IN2: PB1  
  - Enable1: PB3/OC0
- **LEDs:**  
  - Red LED: PB5  
  - Green LED: PB6  
  - Blue LED: PB7
- **Flame Sensor:** Connected to PD2
- **Buzzer:** Connected to PD3, activated during fire alert

---

## ⚙️ Operation Description

### Lighting Control (LDR):
- The LDR monitors light intensity, controlling the three LEDs based on preset thresholds.

### Temperature Control (LM35):
- The LM35 measures room temperature, and the fan speed is controlled using PWM signals based on the temperature ranges.

### Fire Detection:
- The flame sensor triggers an alert:
  - Displays "Critical alert!" on the LCD.
  - Activates the buzzer.
  - System remains in alert mode until the flame sensor clears the detection.

### LCD Display:
- **First row:** Indicates fan status ("FAN is ON" or "FAN is OFF").
- **Second row:** Displays temperature ("Temp= xxx°C") and light intensity ("LDR= xxx%").

---

## 📋 System Requirements

- **Microcontroller:** ATmega32
- **System Frequency:** 16 MHz
- Project implementation follows a layered model architecture.

---

## 🛠️ Drivers Requirements

### ADC Driver
- **Reference Voltage:** Internal 2.56V.
- **Prescaler:** F_CPU/128 for necessary accuracy.

```c
void ADC_init(void);           // Initializes the ADC
uint16 ADC_readChannel(uint8 channel_num);   // Reads analog data from a channel
