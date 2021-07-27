#include "Ds18b20.h"
#include "TIM_Delay.h"



DS18B20::DS18B20(uint16_t a_pin,GPIO_TypeDef* a_port){
	m_GPIO_PIN = a_pin;
	m_GPIO_PORT = a_port;			
}

void DS18B20::Start(void)
{
	Set_Pin_Output(m_GPIO_PORT, m_GPIO_PIN);   // set the pin as output
	HAL_GPIO_WritePin (m_GPIO_PORT, m_GPIO_PIN, GPIO_PIN_RESET);  // pull the pin low
	delay (480);   // delay according to datasheet

	Set_Pin_Input(m_GPIO_PORT, m_GPIO_PIN);    // set the pin as input
	return;
}


bool DS18B20::Check_Response(void){
	
	bool Response = false;
	
	delay (80);    // delay according to datasheet

	if (!(HAL_GPIO_ReadPin (m_GPIO_PORT, m_GPIO_PIN))) Response = true;    // if the pin is low i.e the presence pulse is detected

	delay (400); // 480 us delay totally.

	return Response ;
}



void DS18B20::Write (uint8_t data)
{
	Set_Pin_Output(m_GPIO_PORT, m_GPIO_PIN);  // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			Set_Pin_Output(m_GPIO_PORT, m_GPIO_PIN);  // set as output
			HAL_GPIO_WritePin (m_GPIO_PORT, m_GPIO_PIN, GPIO_PIN_RESET);  // pull the pin LOW
			delay (1);  // wait for 1 us

			Set_Pin_Input(m_GPIO_PORT, m_GPIO_PIN);  // set as input
			delay (50);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			ISensor::Set_Pin_Output(m_GPIO_PORT, m_GPIO_PIN);
			HAL_GPIO_WritePin (m_GPIO_PORT, m_GPIO_PIN, GPIO_PIN_RESET);  // pull the pin LOW
			delay (50);  // wait for 60 us

			ISensor::Set_Pin_Input(m_GPIO_PORT, m_GPIO_PIN);
		}
	}
}

uint8_t DS18B20::Read (void)
{
	uint8_t value=0;

	ISensor::Set_Pin_Input(m_GPIO_PORT, m_GPIO_PIN);

	for (int i=0;i<8;i++)
	{
		ISensor::Set_Pin_Output(m_GPIO_PORT, m_GPIO_PIN);   // set as output

		HAL_GPIO_WritePin (m_GPIO_PORT, m_GPIO_PIN, GPIO_PIN_RESET);  // pull the data pin LOW
		delay (1);  // wait for > 1us

		ISensor::Set_Pin_Input(m_GPIO_PORT, m_GPIO_PIN);  // set as input
		if (HAL_GPIO_ReadPin (m_GPIO_PORT, m_GPIO_PIN))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delay (50);  // wait for 60 us
	}
	return value;
}




bool DS18B20::GetMeasurement(DS18B20MeasureObject& measure_object){
	
		
uint8_t Temp_byte1, Temp_byte2;
uint16_t SUM;

	
		Start ();
		if(!Check_Response()){
		 return false;
		}
	
	  HAL_Delay (1);
	  Write (0xCC);  // skip ROM
	  Write (0x44);  // convert t
	  HAL_Delay (800);

		Start ();
		if(!Check_Response()){
		 return false;
		}

			HAL_Delay(1);
      Write (0xCC);  // skip ROM
      Write (0xBE);  // Read Scratch-pad

      Temp_byte1 = Read();
	  Temp_byte2 = Read();
	  SUM = (Temp_byte2<<8)|Temp_byte1;
		measure_object.tmp = (float)SUM/16;

	
	
		return true;
	
	
}



