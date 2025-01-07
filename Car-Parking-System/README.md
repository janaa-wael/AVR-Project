# 🚗 Car Parking Sensor Using ATmega32, Ultrasonic Sensor, LCD Display, LEDs, and Buzzer

## 🎯 Objective
The goal of this project is to create a simple car parking sensor system that helps drivers detect obstacles and prevent collisions while parking. The system uses an ultrasonic sensor to measure the distance between the car and obstacles, displaying the information on an LCD. LEDs and a buzzer provide visual and audio warnings based on proximity.

## 📝 Overview
This project utilizes an **ATmega32** microcontroller to process distance data from an ultrasonic sensor and display the results on an **LCD**. The system includes three LEDs (Red, Green, and Blue) and a buzzer that alerts the driver when the car is too close to an obstacle. The LEDs light up in stages, and the buzzer sounds when the object is near, helping drivers park safely.

## ✨ Features
- **📏 Ultrasonic Distance Measurement**: Measures the distance between the car and nearby objects.
- **📟 LCD Display**: Displays the distance in centimeters and shows "Stop" when the distance is less than 5 cm.
- **💡 LED Indicators**: Three LEDs (Red, Green, and Blue) light up based on object proximity.
- **🔊 Buzzer Alert**: Sounds when the object is too close (<= 5 cm).
- **📊 Dynamic LED Behavior**: 
  - Distance <= 5 cm: All LEDs flashing (Red, Green, Blue), Buzzer sounds, LCD shows "Stop."
  - 6 cm <= Distance <= 10 cm: All LEDs ON (Red, Green, Blue), No buzzer.
  - 11 cm <= Distance <= 15 cm: Red and Green LEDs ON, Blue LED OFF.
  - 16 cm <= Distance <= 20 cm: Only Red LED ON, others OFF.
  - Distance > 20 cm: All LEDs OFF, Buzzer OFF.

## 🛠️ Hardware Components
- **🖥️ ATmega32 Microcontroller**
- **📡 HC-SR04 Ultrasonic Sensor**
- **🔤 16x2 LCD Display**
- **🔴 Red, 🟢 Green, and 🔵 Blue LEDs**
- **🔔 Buzzer**

## 🔌 Pin Connections

### 🖥️ ATmega32:
- **Port A (PA1)**: Connected to LCD RS Pin
- **Port A (PA2)**: Connected to LCD E Pin
- **Port A (PA3 to PA6)**: Connected to LCD Data pins (D4-D7)
- **Port B (PC0 to PC2)**: Connected to Red, Green, and Blue LEDs respectively
- **Port C (PC5)**: Connected to the transistor controlling the Buzzer
- **Port D (PD6)**: Echo pin for the Ultrasonic sensor
- **Port D (PD7)**: Trigger pin for the Ultrasonic sensor

### 📡 Ultrasonic Sensor:
- **Echo**: Connected to PD6
- **Trigger**: Connected to PD7

### 📟 LCD Display (4-bit mode):
- **RS**: Connected to PA1
- **RW**: Grounded
- **E**: Connected to PA2
- **D4-D7**: Connected to PA3 to PA6

### 💡 LEDs:
- **Red LED**: Connected to PC0
- **Green LED**: Connected to PC1
- **Blue LED**: Connected to PC2

### 🔔 Buzzer:
- **Buzzer Pin**: Connected to PC5

## ⚙️ Operation Description
1. The ultrasonic sensor emits ultrasonic waves and listens for their reflection from an object.
2. The **ATmega32** microcontroller calculates the distance based on the time taken for the sound to return.
3. The distance is displayed on the **LCD** in centimeters.
4. The system continuously updates and recalculates the distance, providing real-time feedback.
5. **Distance to LED and Buzzer Mapping**:
   - Distance <= 5 cm: All LEDs flashing, Buzzer ON, LCD displays "Stop."
   - 6 cm <= Distance <= 10 cm: All LEDs ON, No Buzzer.
   - 11 cm <= Distance <= 15 cm: Red and Green LEDs ON, Blue LED OFF.
   - 16 cm <= Distance <= 20 cm: Only Red LED ON.
   - Distance > 20 cm: All LEDs OFF, Buzzer OFF.

## 📋 System Requirements
- **Microcontroller**: ATmega32
- **System Frequency**: 16 MHz
- Implemented using a **Layered Model Architecture**.

## 🔧 Drivers Requirements

### 🚪 GPIO Driver:
- Use the **GPIO driver** implemented in the course.

### 📏 ICU Driver:
- Use the **ICU driver** with a frequency of F_CPU/8.
- Detect the rising edge as the first edge.
- The **ICU_init** and **ICU_setCallBack** functions should be called in the **Ultrasonic_init** function.

### 🔔 Buzzer Driver:
- Use the **Buzzer driver** to alert when the distance is less than or equal to 5 cm.
- Buzzer Driver Functions:
  - `void Buzzer_init(void)`: Initializes the buzzer pin and turns it off.
  - `void Buzzer_on(void)`: Activates the buzzer.
  - `void Buzzer_off(void)`: Deactivates the buzzer.

### 📟 LCD Driver:
- Use the **LCD driver** with 4-bit data mode to display the distance in centimeters. If the distance is less than 5 cm, the LCD should display "Stop."

### 📡 Ultrasonic Driver:
- Implement the **Ultrasonic driver** using the ATmega32 ICU driver.
- Functions:
  - `void Ultrasonic_init(void)`: Initializes the ICU and sets up the trigger pin.
  - `void Ultrasonic_Trigger(void)`: Sends the trigger pulse.
  - `uint16 Ultrasonic_readDistance(void)`: Triggers the pulse and calculates the distance.
  - `void Ultrasonic_edgeProcessing(void)`: Processes the pulse time.