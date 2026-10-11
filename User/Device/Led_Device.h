#ifndef _LED_DEVICE_H_
#define _LED_DEVICE_H_

#include "main.h"

typedef struct {
	GPIO_TypeDef   		*pstgpiobase;
	uint16_t  			usgpiopin;
	uint8_t  			uconlevel;
}
stLedDeviceParamtdf;


void vLedDeviceInit(stLedDeviceParamtdf * pstinit,uint8_t lednum);
void vledOn(uint8_t lednum);
void vledOFF(uint8_t lednum);


#endif
