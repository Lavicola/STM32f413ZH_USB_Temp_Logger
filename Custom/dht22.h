#ifndef DHT22_H
#define DHT22_H


#include "ISensor.h"


typedef struct dht22MeasureObject{
	float tmp;
	float rh;
}dht22MeasureObject;


class DHT22 : ISensor{
	
	private:
		GPIO_TypeDef* m_GPIO_PORT;
		uint16_t m_GPIO_PIN;

		
	public:
		DHT22(uint16_t a_pin,GPIO_TypeDef* a_port);

	
		void Start(void);
		bool Check_Response (void);
		uint8_t Read (void);
		bool parse(uint8_t data[40], float* a_ptemperature, float* a_phumidity);
		bool GetMeasurement(dht22MeasureObject& measure_object );

	
	
	
	
	
	
};

#endif