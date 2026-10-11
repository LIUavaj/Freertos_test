#include "test.h"
#include "string.h"
#include "Led_Device.h"
//#include "main.h"      // 通常里面已经包含了 stm32f1xx_hal.h

void vLedInit()
{
	stLedDeviceParamtdf stinit;
	stinit.pstgpiobase = GPIOC;
	stinit.usgpiopin = GPIO_PIN_13;
	stinit.uconlevel = 1;
	vLedDeviceInit(&stinit,LED_BOARD);
	
	stinit.pstgpiobase = GPIOB;
	stinit.usgpiopin = GPIO_PIN_1;
	stinit.uconlevel = 0;
	vLedDeviceInit(&stinit,LED1);
	
	stinit.pstgpiobase = GPIOB;
	stinit.usgpiopin = GPIO_PIN_0;
	stinit.uconlevel = 0;
	vLedDeviceInit(&stinit,LED2);
	
	stinit.pstgpiobase = GPIOA;
	stinit.usgpiopin = GPIO_PIN_7;
	stinit.uconlevel = 0;
	vLedDeviceInit(&stinit,LED3);
	
	stinit.pstgpiobase = GPIOA;
	stinit.usgpiopin = GPIO_PIN_6;
	stinit.uconlevel = 0;
	vLedDeviceInit(&stinit,LED4);
	
	stinit.pstgpiobase = GPIOA;
	stinit.usgpiopin = GPIO_PIN_5;
	stinit.uconlevel = 0;
	vLedDeviceInit(&stinit,LED5);
	
	stinit.pstgpiobase = GPIOA;
	stinit.usgpiopin = GPIO_PIN_4;
	stinit.uconlevel = 0;
	vLedDeviceInit(&stinit,LED6);
	
	stinit.pstgpiobase = GPIOA;
	stinit.usgpiopin = GPIO_PIN_3;
	stinit.uconlevel = 0;
	vLedDeviceInit(&stinit,LED7);
	
	stinit.pstgpiobase = GPIOA;
	stinit.usgpiopin = GPIO_PIN_2;
	stinit.uconlevel = 0;
	vLedDeviceInit(&stinit,LED8);
	
	
	
}


void vTestExecute(void)
{
	uint8_t i;
	for(i = 0;i<9;i++)
	{
		vledOn(i);
		HAL_Delay(100);
	}
	
	for(i = 0;i<9;i++)
	{
		vledOFF(i);
		HAL_Delay(100);
	}
	
}
