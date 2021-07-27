extern "C"{
#include "stm32f4xx_hal.h"
}

class HD44780 {

	public:
HD44780 (void);   // initialize lcd

void send_cmd (char cmd);  // send command to the lcd

void send_data (char data);  // send data to the lcd

void send_string ( char *str);  // send string to the lcd

void clear (void);  
	
};