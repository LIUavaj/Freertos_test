#include "Led_Device.h"
#include "string.h"
#include "math.h"
stLedDeviceParamTdf astLedDeviceParam[LED_DEV_NUM];       //编号0为板载led


/// @brief      获取 LED 设备参数
///
/// @param      emDevNum   ：设备号
///
/// @note       注意，返回值是 stLedDeviceParamTdf 型的指针，且指针指向的内容是不可更改的（只读的）
const stLedDeviceParamTdf *c_pstGetLedDeviceParam(emLedDevNumTdf emDevNum)
{
    return &astLedDeviceParam[emDevNum];
}

/// @brief      拷贝运行参数
///
/// @param      emDevNum   ：设备号
///
/// @note    
void vLedDeviceRunningParamInit(stLedRunningParamTdf *pstInit, emLedDevNumTdf emDevNum)
{
    memcpy(&astLedDeviceParam[emDevNum].stRunningParam, pstInit, sizeof(stLedRunningParamTdf) / sizeof(uint8_t));
}

/// @brief      LED 更新引脚电平
///
/// @param      emDevNum   ：设备号
///
/// @note           点亮电平                当前状态                引脚输出电平
///                 emOnLevel               emCurrentStatus         GPIO_PinState
///             ------------------------------------------------------------------------
///                 emLedOnLevel_Low(0)     emLedStatus_Off(0)      GPIO_PIN_SET(1)
///                 emLedOnLevel_Low(0)     emLedStatus_On(1)       GPIO_PIN_RESET(0)
///                 emLedOnLevel_High(1)    emLedStatus_Off(0)      GPIO_PIN_RESET(0)
///                 emLedOnLevel_High(1)    emLedStatus_On(1)       GPIO_PIN_SET(1)
///
///             由以上真值表，有 GPIO_PinState = !(emOnLevel ^ emCurrentStatus)
static void vLedUpdatePinLevel(emLedDevNumTdf emDevNum)
{
    uint8_t ucOutput;
    
    // 1. 根据真值表，计算输出引脚电平
    ucOutput = !(astLedDeviceParam[emDevNum].stStaticParam.emOnLevel ^ astLedDeviceParam[emDevNum].stRunningParam.emCurrentStatus);
    
    // 2. 更新 LED 输出引脚电平
    HAL_GPIO_WritePin(astLedDeviceParam[emDevNum].stStaticParam.pstGpioBase, astLedDeviceParam[emDevNum].stStaticParam.usGpioPin, (GPIO_PinState)ucOutput);
}

/*  打开led */

void vledOn(emLedDevNumTdf ememlednum)
{
    // 1. 设置当前状态
    astLedDeviceParam[ememlednum].stRunningParam.emCurrentStatus = emLedStatus_On;
    
    // 2. 根据当前状态更新输出引脚电平
    vLedUpdatePinLevel(ememlednum);
}


/*  关闭led */ 

void vledOFF(emLedDevNumTdf ememlednum)
{
    // 1. 设置当前状态
    astLedDeviceParam[ememlednum].stRunningParam.emCurrentStatus = emLedStatus_Off;
    
    // 2. 根据当前状态更新输出引脚电平
    vLedUpdatePinLevel(ememlednum);
	 
}


/* 翻转led */

void vledToggel(emLedDevNumTdf ememlednum)
{
    // 1. 设置当前状态
    astLedDeviceParam[ememlednum].stRunningParam.emCurrentStatus = (emLedStatusTdf)!astLedDeviceParam[ememlednum].stRunningParam.emCurrentStatus;
    
    // 2. 根据当前状态更新输出引脚电平
    vLedUpdatePinLevel(ememlednum);
}

/// @brief      LED 闪烁执行
///
/// @param      emDevNum    ：设备编号
///
/// @note
void vLedDeviceBilnkExecute(emLedDevNumTdf emDevNum)
{
    // 1. 根据当前计数，更新状态和引脚输出
    if(astLedDeviceParam[emDevNum].stRunningParam.ulCurrentCount < astLedDeviceParam[emDevNum].stRunningParam.ulOnCountThreshold)
    {
        vledOn(emDevNum);
    }
    else if(astLedDeviceParam[emDevNum].stRunningParam.ulCurrentCount <= astLedDeviceParam[emDevNum].stRunningParam.ulOnCountThreshold + 
                                                                         astLedDeviceParam[emDevNum].stRunningParam.ulOffCountThreshold)
    {
        vledOFF(emDevNum);
    }
    
    // 2. 更新当前计数
    astLedDeviceParam[emDevNum].stRunningParam.ulCurrentCount++;
	HAL_Delay(0);
    if(astLedDeviceParam[emDevNum].stRunningParam.ulCurrentCount >= astLedDeviceParam[emDevNum].stRunningParam.ulOnCountThreshold + 
                                                                         astLedDeviceParam[emDevNum].stRunningParam.ulOffCountThreshold)
    {
        astLedDeviceParam[emDevNum].stRunningParam.ulCurrentCount = 0;
    }
}

/// @brief      LED 呼吸灯执行
///
/// @param      emDevNum    ：设备编号
///
/// @note       呼吸灯以 LED 闪烁函数为基础，增加了【呼吸周期】
///
///             【闪烁周期】 = 【ON 持续时间（计数阈值）】+【OFF 持续时间（计数阈值）】
///             【最大计数】 = 【呼吸周期】 / 【闪烁周期】
///             【ON 持续时间（计数阈值）】和【OFF 持续时间（计数阈值）】，应该在每次【闪烁周期】开始前，重新计算
///             目前使用 y = sin(x) * sin(x) 函数作为计算公式
///
///             举例：
///
///             上层每 1 ms 调用一次本函数
///
///             【闪烁周期】 = 10，【ON 持续时间（计数阈值）】 = 5，【OFF 持续时间（计数阈值）】 = 5，
///             则 LED 点亮 5 ms，熄灭 5 ms，如此循环
///
///             【呼吸周期】 = 1000，则 LED 应在 1000 ms 内完成一次呼吸
///             每个【呼吸周期】内包含 1000 / 10 = 100 个【闪烁周期】，即【最大计数】为 100
///             
///             在【当前呼吸计数值】为 3 时，【ON 持续时间（计数阈值）】 = sin(【当前呼吸计数值】 / 【最大计数】 * 3.1415926) * sin(【当前呼吸计数值】 / 【最大计数】 * 3.1415926) * 【闪烁周期】
///                                                                         = sin(3 / 10 * 3.1415926) * sin(3 / 10 * 3.1415926) * 10
void vLedDeviceBreathExecute(emLedDevNumTdf emDevNum)
{
    uint32_t ulBreathCountMax;          // 呼吸计数最大值
    uint32_t ulBlinkPeriod;             // 闪烁周期
    static uint32_t s_ulBreathCount;    // 当前呼吸计数值
    
    // 1. LED 执行周期闪烁
    vLedDeviceBilnkExecute(emDevNum);
    
    // 2. 计算初始参数
    // 2.1. 计算 闪烁周期，闪烁周期 = ON 持续时间（计数阈值） +  OFF 持续时间（计数阈值）
    ulBlinkPeriod = astLedDeviceParam[emDevNum].stRunningParam.ulOnCountThreshold + astLedDeviceParam[emDevNum].stRunningParam.ulOffCountThreshold;
    
    // 2.2. 计算呼吸灯周期内最大计数，最大计数 = 呼吸周期 / PWM 周期
    ulBreathCountMax = astLedDeviceParam[emDevNum].stRunningParam.ulBreathPeriod / ulBlinkPeriod;
    
    // 3. 每次 闪烁周期开始时，重新计算【ON 持续时间（计数阈值）】和【OFF 持续时间（计数阈值）】
    if(astLedDeviceParam[emDevNum].stRunningParam.ulCurrentCount == 0)
    {
        // 3.1. ON 持续时间（计数阈值） = 闪烁周期 / [sin(s_ulCount) * sin(s_ulCount)]
        astLedDeviceParam[emDevNum].stRunningParam.ulOnCountThreshold = ulBlinkPeriod * sin(PI * s_ulBreathCount / ulBreathCountMax) * sin(PI * s_ulBreathCount / ulBreathCountMax);
        
        // 3.2. OFF 持续时间（计数阈值） = 最大计数 - ON平持续时间（计数阈值）
        astLedDeviceParam[emDevNum].stRunningParam.ulOffCountThreshold = ulBlinkPeriod - astLedDeviceParam[emDevNum].stRunningParam.ulOnCountThreshold;
        
        // 3.3. 计数器超出最大值，则清零
        s_ulBreathCount++;
        if(s_ulBreathCount >= ulBreathCountMax)
        {
            s_ulBreathCount = 0;
        }
    }
}


/// @brief      LED 周期执行
///
/// @param      emDevNum    ：设备编号
///
/// @note       根据模式执行不同操作
void vLedDevicePeriodExecute(emLedDevNumTdf emDevNum)
{
    switch(astLedDeviceParam[emDevNum].stRunningParam.emMode)
    {
        case emLedMode_Blink:
        {
            vLedDeviceBilnkExecute(emDevNum);
            break;
        }
		case emLedMode_Breath:
        {
            vLedDeviceBreathExecute(emDevNum);
            break;
        }
        default:
        {
            ;
        }
    }
}

/* 结构体初始化 */
void vLedDeviceInit(stLedStaticParamTdf * pstinit,emLedDevNumTdf ememlednum)
{
//	astLedDeviceParam[ememlednum].pstgpiobase = pstinit->pstgpiobase;
//	astLedDeviceParam[ememlednum].usgpiopin = pstinit->usgpiopin;
//	astLedDeviceParam[ememlednum].emonlevel = pstinit->emonlevel;
	
	// 1. 初始化静态参数
    memcpy(&astLedDeviceParam[ememlednum].stStaticParam, pstinit, sizeof(stLedStaticParamTdf) / sizeof(uint8_t));
}
