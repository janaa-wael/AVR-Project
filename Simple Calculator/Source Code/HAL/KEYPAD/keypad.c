/*
 * KEYPAD.c
 *
 * Created: 10/8/2024 7:45:13 PM
 *  Author: Jana Wael
 */

#include <avr/delay.h>
#include "../../LIB/std_types.h"
#include "../../LIB/common_macros.h"
#include "keypad.h"
#include "../../MCAL/GPIO/gpio.h"

const uint8 KEYPAD [4][4]= KPD_VALUES;

void KEYPAD_voidInit(void)
{
	/*Set the Raw port as input with PORT=1 to activate the internal pull up */
	GPIO_setupPortDirection(KEYPAD_ROW_PORT,ROW_PORT_INPUT);
	GPIO_writePort(KEYPAD_ROW_PORT,0x0F);
	/*Set the COL port as output with Initial value =LOGIC HIGH*/
	GPIO_setupPortDirection(KEYPAD_COL_PORT,COL_PORT_OUTPUT);
	GPIO_writePort(KEYPAD_COL_PORT,0x0F);
}

uint8 KEYPAD_READ(void) {
		uint8 row = 0;
		uint8 col = 0;
    GPIO_writePort(KEYPAD_COL_PORT,0x0F);
    GPIO_writePort(KEYPAD_ROW_PORT,0x0F);
    for (col = 0; col < 4; col++) {
        // Drive the current column low
        GPIO_writePin(KEYPAD_COL_PORT, col, 0);
        for (row = 0; row < 4; row++) {
            uint8 val;
            val = GPIO_readPin(KEYPAD_ROW_PORT, row);

            if (val == 0) {
                // Debounce
                _delay_ms(10);  // Assuming you have a delay function
                val = GPIO_readPin(KEYPAD_ROW_PORT, row);

                if (val == 0) {
                    // Wait until the key is released
                    while (val == 0) {
						val = GPIO_readPin(KEYPAD_ROW_PORT, row);
                    }
                    GPIO_writePin(KEYPAD_COL_PORT, col, 1); // Reset the column
                    return KEYPAD[row][col];  // Return the corresponding character from the keymap
                }
            }
        }

        // Reset the column back high
        GPIO_writePin(KEYPAD_COL_PORT, col, 1);
    }
    return 'x';  // Indicate no key press
}
