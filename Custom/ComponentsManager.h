#ifndef COMPONENTSMANAGER_H
#define COMPONENTSMANAGER_H


#include "dht22.h"
#include "Ds18b20.h"
#include "hd44780.h"

#define DHT22_PORT GPIOB
#define DHT22_PIN GPIO_PIN_5

#define DS18B20_PORT GPIOB
#define DS18B20_PIN GPIO_PIN_4


class ComponentsManager
{
	
	public:
	
			bool GetDHT22Measure(dht22MeasureObject& measure_object);
			bool GetDS18B20Measurement(DS18B20MeasureObject& measure_object);
			void hd44780SendString(char* string);
			void hd44780Clear();

	   static ComponentsManager* getInstance();
		
	
	private:
	static ComponentsManager* m_Instance;
	ComponentsManager();
	~ComponentsManager();

	DHT22 m_dht22;
	DS18B20 m_ds18b20;
	HD44780 m_hd44780;
	
	
};





#endif