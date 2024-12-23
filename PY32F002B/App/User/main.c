/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "aries_sdk.h"		

#define CPU_FREQ							24000000

#define LED_PORT							GPIOA
#define LED_PIN								GPIO_PIN_5

#define BUTTON_PORT						GPIOA
#define	BUTTON_PIN						GPIO_PIN_4

#define LED(X)								HAL_GPIO_WritePin(LED_PORT, LED_PIN, X)
#define BUTTON()							HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET

#define DATA_RX_BUFF_LEN      64
#define MIN(X,Y)					X > Y ? Y : X
uint8_t buff_rx[DATA_RX_BUFF_LEN];
	
void cdc_process_handle()
{
    uint32_t length = aries_sdk_cdc_get_length();
    if(length != 0)
    {
			length = MIN(length, DATA_RX_BUFF_LEN);
			if (aries_sdk_cdc_read(buff_rx, length) != 0)
			{
				//aries_sdk_cdc_write(buff_rx, length);
        buff_rx[length] = '\0';
        printf("You Send ==> %sh", buff_rx);
			}
    }
}

#if   defined ( __CC_ARM )
#define PRINTF_BUFF_LEN       64
uint8_t buff_tx[PRINTF_BUFF_LEN];
volatile uint32_t count = 0;
int fputc(int ch, FILE* f)
{
    buff_tx[count++] = ch;
		if(count >= PRINTF_BUFF_LEN || ch == '\n')
		{
			aries_sdk_cdc_write(buff_tx, count);
			count = 0;
		}
    return (ch);
}
#elif __GNUC__
int _write(int fd, char *ptr, int len)
{ 
  aries_sdk_cdc_write(ptr, len);
  return len;
}
#else
#endif

/**
  * @brief  GPIO configuration.
  * @param  None
  * @retval None
  */
static void APP_GpioConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();                          /* Enable GPIOA clock */

  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* Push-pull output */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin = BUTTON_PIN;	
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;            		 /* Input Floating Mode */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Enable pull-up */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);    
}

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
	uint32_t ledTick = 0;
	HAL_Init();
	APP_GpioConfig();
	aries_sdk_init();
	printf("PY32F002B Application Startup...\r\n");
  while (1)
  {
		if((HAL_GetTick() - ledTick) > 500)
		{
			HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
			printf("LED Changed ...\r\n");
			ledTick = HAL_GetTick();
		}
		if(BUTTON() == 1)
		{
			printf("Button press down ...\r\n");
		}
		cdc_process_handle();
  }
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file：Pointer to the source file name
  * @param  line：assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add His own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
