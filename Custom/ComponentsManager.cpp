#include "ComponentsManager.h"


ComponentsManager* ComponentsManager::m_Instance = NULL; 


ComponentsManager::ComponentsManager() : m_dht22(DHT22_PIN,DHT22_PORT), m_ds18b20(DS18B20_PIN,DS18B20_PORT),m_hd44780() {
			
}

bool ComponentsManager::GetDHT22Measure(dht22MeasureObject& measure_object)
{		
		return m_dht22.GetMeasurement(measure_object);
		
}

bool ComponentsManager::GetDS18B20Measurement(DS18B20MeasureObject& measure_object){
	
	return m_ds18b20.GetMeasurement(measure_object);
	
}


void ComponentsManager::hd44780SendString(char* string){	
	m_hd44780.send_string(string);	
}

void ComponentsManager::hd44780Clear(){
	m_hd44780.clear();	
}


ComponentsManager* ComponentsManager::getInstance(){
	
	if(!ComponentsManager::m_Instance) {
	ComponentsManager::m_Instance = new ComponentsManager();
	}
	
	return m_Instance;

	
}


