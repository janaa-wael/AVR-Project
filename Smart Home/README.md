🔌 Smart Home Automation Using ATmega32
🌟 Project Overview
This project implements a Smart Home Automation System using the ATmega32 microcontroller. It automates lighting, fan speed, and fire detection based on environmental conditions, such as light intensity, room temperature, and fire hazards. The system also features an LCD display to show real-time information, and it uses a motor control circuit for fan speed regulation.

🚀 Features
Automatic Lighting Control:

Adjusts LEDs based on ambient light intensity using an LDR.
Thresholds for LEDs:
< 15% light: All 3 LEDs (Red, Green, Blue) ON.
16-50%: Red & Green ON.
51-70%: Only Red ON.
> 70%: All LEDs OFF.
Fan Speed Control:

The fan speed is controlled based on room temperature using a PWM signal.
≥ 40°C: Fan @ 100%.
35°C - 40°C: Fan @ 75%.
30°C - 35°C: Fan @ 50%.
25°C - 30°C: Fan @ 25%.
< 25°C: Fan OFF.
Fire Detection:

A flame sensor detects fire and triggers a buzzer alarm.
The system displays "Critical Alert!" on the LCD when a fire is detected.
LCD Display:

Row 1: Shows fan status ("FAN is ON" or "FAN is OFF").
Row 2: Displays real-time temperature and light intensity.
🔧 Hardware Components
Microcontroller: ATmega32
Sensors:
LDR (for ambient light detection) - connected to ADC Channel 0
LM35 (for temperature measurement) - connected to ADC Channel 1
Flame Sensor (for fire detection)
Display: 16x2 LCD (connected in 8-bit mode)
Motor Control: H-Bridge (for fan motor speed control)
LEDs: Red, Green, Blue (for light intensity display)
Buzzer: For fire alert
📜 Operation Description
Lighting Control: The LDR monitors ambient light and controls the three LEDs accordingly.
Fan Speed Control: The LM35 sensor measures room temperature and adjusts the fan speed using PWM.
Fire Detection: The flame sensor triggers the alarm and displays an alert on the LCD when fire is detected.
📟 LCD Display Details
Row 1: Displays the fan's status (ON/OFF).
Row 2: Displays temperature (in °C) and light intensity (in %).
🛠️ System Architecture
The project follows a layered architecture model. The drivers used in the project are:

ADC Driver: For reading analog data from the LM35 and LDR sensors.
GPIO Driver: To handle basic pin configurations.
PWM Driver: For fan speed control.
LCD Driver: To display the system's real-time status.
Temperature Sensor Driver: To read temperature values.
LED Driver: To control the red, green, and blue LEDs based on light intensity.
DC Motor Driver: For fan speed control.
Flame Sensor Driver: To detect fire incidents.
Buzzer Driver: For fire alert sound.
📋 Circuit Schematic
You can refer to the provided circuit schematic to build the hardware connections for the system.

⚙️ Drivers and Functions
Each hardware component has its own driver with specific functions for initialization, control, and real-time data handling. The system includes ADC, GPIO, PWM, LCD, motor, and sensor drivers.