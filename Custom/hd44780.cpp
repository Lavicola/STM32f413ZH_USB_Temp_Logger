
/** 
Function(implementation) used from: https://controllerstech.com/i2c-lcd-in-stm32/


**/

#include "HD44780.h"

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup


int static cursor_position = 0;	

HD44780::HD44780(){
	
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	HD44780::send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	HD44780::send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	HD44780::send_cmd (0x30);
	HAL_Delay(10);
	HD44780::send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	HD44780::send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	HD44780::send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	HD44780::send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	HD44780::send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	HD44780::send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	
	cursor_position = 0;
}

	


void HD44780::put_cur(int row, int col){
	    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    HD44780::send_cmd (col);
}



void HD44780::send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void HD44780::send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void HD44780::clear (void)
{
	HD44780::send_cmd (0x00);
	for (int i=0; i<100; i++)
	{
		HD44780::send_data (' ');
	}
	
	cursor_position = 0;
	HD44780::put_cur(cursor_position,0);

	
}

void HD44780::send_string (char *str)
{
	while (*str) HD44780::send_data (*str++);
	cursor_position +=1;
	HD44780::put_cur(cursor_position,0);

}
