/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file            : usb_host.c
  * @version         : v1.0_Cube
  * @brief           : This file implements the USB Host
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *   s                          www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_msc.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */


USBH_HandleTypeDef hUsbHostFS;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;


#include "ff.h"
FATFS USBH_fatfs;
FIL MyFile;
FRESULT res;
uint32_t bytesWritten;
uint8_t rtext[200];
uint8_t wtext[] = "USB Host Library : Mass Storage Example";
uint8_t name[30]="awesome.txt";//name of the file
uint16_t counter=0;
uint32_t i=0;
uint8_t isMounted = 0;
FILINFO fno;


	
static int32_t uart_length=0;
extern char USBHPath [];  /* USBH logical drive path */

extern UART_HandleTypeDef huart3;
uint8_t uart_tx_buffer[100];


void userFunction(void) {
	UINT bytesread;
	FRESULT l_result = FR_DISK_ERR;
	
	
	if (Appli_state == APPLICATION_READY) {		
		// mount it first!
		if(isMounted == 0)
		{
		uint8_t a = f_mount(&USBH_fatfs,"0://",1);
			isMounted = 1;
		}
		
		
		switch(f_stat(name,&fno)){
			
			case FR_NO_FILE:
				l_result = f_open(&MyFile,name,FA_CREATE_NEW|FA_WRITE);
			break;
			case FR_OK:
				l_result = f_open(&MyFile,name,FA_OPEN_APPEND|FA_WRITE);
			break;
			// I don´t expect other errors
			default:
				l_result = FR_DISK_ERR;
		}
		
			if(l_result == FR_OK){
				
				HAL_UART_Transmit(&huart3, "This is a test", strlen("This is a test"),1000);
				f_puts("This is a test\n",&MyFile);	
				f_close(&MyFile);
				
			}
		


  }
}

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * user callback declaration
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * Init USB host library, add supported class and start the library
  * @retval None
  */
void MX_USB_HOST_Init(void)
{
  /* USER CODE BEGIN USB_HOST_Init_PreTreatment */
  
  /* USER CODE END USB_HOST_Init_PreTreatment */
  
  /* Init host Library, add supported class and start the library. */
  if (USBH_Init(&hUsbHostFS, USBH_UserProcess, HOST_FS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_RegisterClass(&hUsbHostFS, USBH_MSC_CLASS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_Start(&hUsbHostFS) != USBH_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_HOST_Init_PostTreatment */
  
  /* USER CODE END USB_HOST_Init_PostTreatment */
}

/*
 * Background task
 */
void MX_USB_HOST_Process(void)
{
  /* USB Host Background task */
  USBH_Process(&hUsbHostFS);
}
/*
 * user callback definition
 */
static void USBH_UserProcess  (USBH_HandleTypeDef *phost, uint8_t id)
{
  /* USER CODE BEGIN CALL_BACK_1 */
  switch(id)
  {
  case HOST_USER_SELECT_CONFIGURATION:
  break;

  case HOST_USER_DISCONNECTION:
  Appli_state = APPLICATION_DISCONNECT;
  break;

  case HOST_USER_CLASS_ACTIVE:
  Appli_state = APPLICATION_READY;
  break;

  case HOST_USER_CONNECTION:
  Appli_state = APPLICATION_START;
  break;

  default:
  break;
  }
  /* USER CODE END CALL_BACK_1 */
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
