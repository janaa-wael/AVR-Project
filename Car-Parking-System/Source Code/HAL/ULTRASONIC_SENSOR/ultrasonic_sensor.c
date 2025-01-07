#include "ultrasonic_sensor.h"
#include "../../LIB/std_types.h"
#include "../../MCAL/ICU/icu.h"
#include "../../MCAL/GPIO/gpio.h"
#include <util/delay.h>

// Global variable to store pulse duration
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

ICU_ConfigType US_CONFIG = {F_CPU_8, RAISING};

void Ultrasonic_init(void)
{
	ICU_init(&US_CONFIG);
	ICU_setCallBack(&Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIG_PORT, TRIG_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(ECHO_PORT, ECHO_PIN, PIN_INPUT);

}

void Ultrasonic_Trigger(void)
{
	ICU_clearTimerValue();
	GPIO_writePin(TRIG_PORT, TRIG_PIN, LOGIC_HIGH);
	_delay_us(10); // Create a 10 microsecond delay
	GPIO_writePin(TRIG_PORT, TRIG_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
    Ultrasonic_Trigger();

    // Wait a short time for the measurement to complete (e.g., 15 ms)
    _delay_ms(15);

    float calculatedDistance = (g_timeHigh * 0.0343) / 2.0; // Using float for higher precision

    // Round the calculated distance to the nearest integer
    uint32 distance = (uint16)(calculatedDistance + 0.5); // Adding 0.5 for proper rounding
    //uint16 distance = (g_timeHigh * 0.0343) / 2.0;

    return distance;
}

void Ultrasonic_edgeProcessing(void)
{
    if (g_edgeCount == 0)
    {
        // First rising edge detected, start timing
        ICU_clearTimerValue();
        ICU_setEdgeDetectionType(FALLING);  // Look for falling edge next
        g_edgeCount = 1;
    }
    else if (g_edgeCount == 1)
    {
        // Falling edge detected, capture pulse duration
        g_timeHigh = ICU_getInputCaptureValue();
        g_edgeCount = 0;  // Reset edge count for the next pulse
        ICU_setEdgeDetectionType(RAISING);  // Set edge detection back to rising for the next trigger
    }
}
