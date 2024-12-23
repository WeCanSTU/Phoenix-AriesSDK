#include "defines.h"
#include "port_def.h"
#include "user_iap_drv.h"
#include "crc32.h"
#include "py32f0xx_hal.h"
#include "py32f002b_ll_rcc.h"
#include "py32f002b_ll_bus.h"
#include "py32f002b_ll_system.h"
#include "py32f002b_ll_cortex.h"
#include "py32f002b_ll_utils.h"
#include "py32f002b_ll_pwr.h"
#include "py32f002b_ll_gpio.h"
#include "py32f002b_ll_rcc.h"

#define APP_ADDR            										0x08002000
#define APP_FLASH_SIZE            									(0x08006000 - APP_ADDR)
#define DFU_BUFFER_MAX_SIZE          								1024

typedef  void (*iapfun)(void);
iapfun jump2app;

#ifdef __GNUC__
uint8_t cbBlock[DFU_BUFFER_MAX_SIZE]  __attribute__((aligned(4))) = {0};
#elif __CC_ARM
__align(4) uint8_t cbBlock[DFU_BUFFER_MAX_SIZE] = {0};
#else
#endif

static IapBuffer iapBuffer = 
{
    .pBlock = (uint8_t*)cbBlock,
    .blockSize = DFU_BUFFER_MAX_SIZE
};

void sysJumpTo(uint32_t appAddr)
{
    if(((*(__IO uint32_t*)appAddr) & 0x2FFE0000) == 0x20000000)
    {
        NVIC->ICER[0] = 0xFFFFFFFF;
        jump2app =(iapfun)*(__IO uint32_t*)(appAddr + 4);
        __set_MSP(*(__IO uint32_t*)appAddr);
        jump2app();
    }
}

void user_iap_delay(uint32_t ms)
{
    
}

void user_iap_init(IapBuffer **pIapBuffer)
{
    *pIapBuffer = &iapBuffer;
}

void user_iap_reset()
{
    NVIC_SystemReset();
}

void user_iap_jump(void)
{
    sysJumpTo(APP_ADDR);
}

uint8_t user_iap_erase(FlashParams *params)
{
    uint32_t pageTotal = params->size / FLASH_PAGE_SIZE;				
    if (params->size == 0)
    {
        return 0;
    }		
    uint32_t PageSectorError = 0;		
    FLASH_EraseInitTypeDef EraseInitStruct = {0};
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;
    EraseInitStruct.PageAddress = APP_ADDR;
    EraseInitStruct.NbPages  = pageTotal;  
    /* Unlock Flash */
    HAL_FLASH_Unlock();		
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageSectorError) != HAL_OK)
    {
        return 0;
    }
    /* Lock Flash */
    HAL_FLASH_Lock();	
    return 1;
}

uint8_t user_iap_program(FlashParams *params)
{
    if(params->size == 0 || (params->addr + params->size) >= APP_FLASH_SIZE)
    {
        return 0;
    }
    uint32_t flash_program_start = APP_ADDR + params->addr;
    uint32_t flash_program_end = (flash_program_start + params->size);
    uint32_t *src = (uint32_t *)params->blockData;
    /* Unlock Flash */
    HAL_FLASH_Unlock();
    while (flash_program_start < flash_program_end)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)
        {
          flash_program_start += FLASH_PAGE_SIZE;
          src += FLASH_PAGE_SIZE / 4;
        }
    }	
    /* Lock Flash */
    HAL_FLASH_Lock();
		return 1;
}

uint8_t user_iap_read(FlashParams *params)
{
    uint8_t *p = (uint8_t *)(params->addr + APP_ADDR);
    return *p;
}

uint8_t user_iap_verify_image(FlashVerifyParams *params)
{
  if (params->len > APP_FLASH_SIZE)
  {
    return 0;
  }
		__IO uint8_t *p = (__IO uint8_t*)(APP_ADDR);
    uint32_t calCrc = 0;
    calCrc = crc32(calCrc, (const uint8_t *)p, params->len);		
    return calCrc == params->crc32; 
}

uint32_t user_iap_get_flash_size(void)
{
    return APP_FLASH_SIZE;
}

uint32_t user_iap_get_flash_block_size(void)
{
    return FLASH_PAGE_SIZE;
}
