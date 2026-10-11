#include "test.h"
#include "string.h"
#include "Led_Device.h"
//#include "main.h"      // 通常里面已经包含了 stm32f1xx_hal.h

void vLedInit()
{
	
	
	stLedStaticParamTdf stinit;
	stLedRunningParamTdf    stRunningInit;
	
	
	stRunningInit.emMode                = emLedMode_Breath;
    stRunningInit.ulCurrentCount        = 0;
    stRunningInit.ulOnCountThreshold    = 5;
    stRunningInit.ulOffCountThreshold   = 5;
	stRunningInit.ulBreathPeriod        = 1000;
    vLedDeviceRunningParamInit(&stRunningInit, LED_BOARD);    
    
	stinit.pstGpioBase = GPIOC;
	stinit.usGpioPin = GPIO_PIN_13;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED_BOARD);
	
	stinit.pstGpioBase = GPIOB;
	stinit.usGpioPin = GPIO_PIN_1;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED1);
	
	stinit.pstGpioBase = GPIOB;
	stinit.usGpioPin = GPIO_PIN_0;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED2);
	
	stinit.pstGpioBase = GPIOA;
	stinit.usGpioPin = GPIO_PIN_7;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED3);
	
	stinit.pstGpioBase = GPIOA;
	stinit.usGpioPin = GPIO_PIN_6;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED4);
	
	stinit.pstGpioBase = GPIOA;
	stinit.usGpioPin = GPIO_PIN_5;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED5);
	
	stinit.pstGpioBase = GPIOA;
	stinit.usGpioPin = GPIO_PIN_4;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED6);
	
	stinit.pstGpioBase = GPIOA;
	stinit.usGpioPin = GPIO_PIN_3;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED7);
	
	stinit.pstGpioBase = GPIOA;
	stinit.usGpioPin = GPIO_PIN_2;
	stinit.emOnLevel = emLedOnLevel_Low;
	vLedDeviceInit(&stinit,LED8);
	
	
	
}


void vTestExecute(void)
{
	uint8_t i;
//	static volatile emLedStatusTdf  s_emm;
//	for(i = 0;i<9;i++)
//	{
//		vledOn((emLedDevNumTdf)i);
//		HAL_Delay(100);
//	}
//	s_emm = c_pstGetLedDeviceParam(LED8)->stRunningParam.emCurrentStatus;
//	
//	for(i = 0;i<9;i++)
//	{
//		vledOFF((emLedDevNumTdf)i);
//		HAL_Delay(100);
//		
//	}
//	s_emm = c_pstGetLedDeviceParam(LED8)->stRunningParam.emCurrentStatus;	
//	for(i = 0;i<9;i++)
//	{
//		vledToggel((emLedDevNumTdf)i);
//		HAL_Delay(100);
//	}
    vLedDevicePeriodExecute(LED_BOARD);
    
}
