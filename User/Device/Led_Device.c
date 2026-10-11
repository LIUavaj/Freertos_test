#include "Led_Device.h"
#include "string.h"

stLedDeviceParamtdf astleddeviceparam[9];       //编号0为板载led

/*  打开led */

void vledOn(uint8_t lednum)
{
	if(astleddeviceparam[lednum].uconlevel == 0)
	{
		HAL_GPIO_WritePin(astleddeviceparam[lednum].pstgpiobase,astleddeviceparam[lednum].usgpiopin,GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(astleddeviceparam[lednum].pstgpiobase,astleddeviceparam[lednum].usgpiopin,GPIO_PIN_SET);
	}
}


/*  关闭led */ 

void vledOFF(uint8_t lednum)
{
	if(astleddeviceparam[lednum].uconlevel == 0)
	{
		HAL_GPIO_WritePin(astleddeviceparam[lednum].pstgpiobase,astleddeviceparam[lednum].usgpiopin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(astleddeviceparam[lednum].pstgpiobase,astleddeviceparam[lednum].usgpiopin,GPIO_PIN_RESET);
	}
	
}
/* 结构体初始化 */
void vLedDeviceInit(stLedDeviceParamtdf * pstinit,uint8_t lednum)
{
	astleddeviceparam[lednum].pstgpiobase = pstinit->pstgpiobase;
	astleddeviceparam[lednum].usgpiopin = pstinit->usgpiopin;
	astleddeviceparam[lednum].uconlevel = pstinit->uconlevel;
}
