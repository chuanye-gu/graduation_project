#ifndef _led_
#define _led_
#include "stm32f10x_conf.h"
extern void LED_Init(void);	  //LED��ʼ��
#define led_on    GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define led_off   GPIO_SetBits(GPIOA, GPIO_Pin_15)

#endif



