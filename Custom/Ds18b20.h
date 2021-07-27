
#ifndef DS18B20_H
#define DS18B20_H


#include "ISensor.h"


#define DS18B20_PORT GPIOB
#define DS18B20_PIN GPIO_PIN_4


typedef struct DS18B20MeasureObject{
	float tmp;
}DS18B20MeasureObject;


class DS18B20 : ISensor{
	
	private:
		GPIO_TypeDef* m_GPIO_PORT;
		uint16_t m_GPIO_PIN;

		
	public:
		DS18B20(uint16_t a_pin,GPIO_TypeDef* a_port);

		void Start (void);
		bool Check_Response(void); 
		void Write (uint8_t data);
	  uint8_t Read (void);
		bool GetMeasurement(DS18B20MeasureObject& measure_object);


	
	
	
	
	
	
};

#endif
