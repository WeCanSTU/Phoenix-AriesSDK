#include "defines.h"
#include "port_def.h"
#include "user_i2c_drv.h"

#include "py32f0xx_hal.h"

#define I2C_ADDRESS           0xA0               /* Local address 0xA0 */
#define I2C_SPEEDCLOCK        400000             /* Communication speed 400K */


#define I2C_DUTYCYCLE    I2C_DUTYCYCLE_2 /* Duty cycle */
I2C_HandleTypeDef I2cHandle;

void user_i2c_init(void)
{
	/* I2C initialization */
	I2cHandle.Instance             = I2C;                       /* I2C */
	I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;            /* I2C communication speed */
	I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;             /* I2C duty cycle */
	I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;               /* I2C address */
	I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;   /* Prohibit broadcast calls */
	I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;     /* Allow clock extension */
	HAL_I2C_Init(&I2cHandle);	
}


uint32_t user_i2c_read(TwoWireParams *params)
{	
  uint32_t cnt = 0;
	if (HAL_I2C_Mem_Read(&I2cHandle, (params->slaveAddr << 1) & 0xFF, params->reg, 1, (uint8_t *)params->pData, params->size, 1000) == HAL_OK)
	{
		/*Determine the current I2C status*/
		while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY);					
		cnt = params->size;					
	}
  return cnt;
}

uint32_t user_i2c_write(TwoWireParams *params)
{
  uint32_t cnt = 0;
  if (HAL_I2C_Mem_Write(&I2cHandle, (params->slaveAddr << 1) & 0xFF, params->reg, 1, (uint8_t *)params->pData, params->size, 1000) == HAL_OK)
  {
    /*Determine the current I2C status*/
    while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY);					
    cnt = params->size;					
  }
  return cnt;
}
