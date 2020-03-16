/*
 * timer_lcfg.c
 *
 * Created: 11/4/2019 3:22:11 PM
 *  Author: AVE-LAP-062
 */ 
#include "timer_lcfg.h"

#define FR_CPU					8000000UL
#define INTERRUPT_TIME_US		1000UL


Timer_cfg_S timer_cfg={CH0,TIMER,INTERRUPT_TIME_US,FR_CPU,INTERRUPT};