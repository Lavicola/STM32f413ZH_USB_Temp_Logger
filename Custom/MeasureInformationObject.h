#include "stdint.h"


typedef struct MeasureInformation {
   char temp_in_string[12];
	 char rh_in_string[10];
	 uint8_t date[3];
	 uint8_t time[2];
} MeasureInformation;
 