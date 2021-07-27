#include <stm32f4xx_hal.h>
#include <stdint.h>



static TIM_HandleTypeDef htim3;



void MX_TIM3_Init(void);

void TIM_Start(void);

void Error_Handler(void);

void delay (uint16_t us);



