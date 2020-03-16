/*
 * TMU_LCfg.c
 *
 * Created: 11/16/2019 9:46:58 PM
 *  Author: Eng Abdo
 */ 
#include "TMU_LCfg.h"
#include "timer.h"


/************************************************************************/
/*   TMU configuration parameters                                                                     */
/************************************************************************/
#define RESLUTION_MS		1
#define TMU_TIMER_CHANNEL	CH0


TMU_ConfigType TMU_conf =	{TMU_TIMER_CHANNEL,RESLUTION_MS};

