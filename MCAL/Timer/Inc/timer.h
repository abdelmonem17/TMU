/****************************************************************************
 * @file  timer.h
 * @brief this file includes some functions prototype of timer
 *
 * @author Abdelmonem Mostafa
 * @date  NOV 16 2019
 *
 ****************************************************************************/
 


#ifndef TIMER_H_
#define TIMER_H_
#include "gpio.h"
#include "timer_cfg.h"
#include "timer_lcfg.h"


#define TIMER0_ISR_INDEX	0

typedef	void(*pFun)(void);
extern volatile uint16 timer0_ticks;
extern pFun Timer0_ISR[3];


/****************************************************************************
*
*   @brief function inits timer
*   this function takes  timer config
*   @params  name : timer_conf
*			 type :Timer_cfg_S
*
*   @return uint8
****************************************************************************/
uint8 Timer_Init(Timer_cfg_S *);

/****************************************************************************
*
*   @brief function starts timer
*   this function takes  timer channel
*   @params  name : ch
*			 type :Timer_ch_E
*
*   @return uint8
****************************************************************************/
void Timer_Start(Timer_ch_E);

/****************************************************************************
*
*   @brief function stops timer
*   this function takes  timer channel
*   @params  name : ch
*			 type :Timer_ch_E
*
*   @return uint8
****************************************************************************/
void Timer_Stop(Timer_ch_E);

/****************************************************************************
*
*   @brief function sets timer interrupt time
*   this function takes  timer channel and timer channel
*   @params  name : ch
*			 type :	Timer_ch_E
*   @params  name : counts_us
*			 type :	uint16
*
*   @return uint8
****************************************************************************/
uint8 Timer_set_counter(Timer_ch_E,uint16);

/****************************************************************************
*
*   @brief function gets timer status
*   this function takes  timer channel
*   @params  name : ch
*			 type :Timer_ch_E
*
*   @return BOOL_E
****************************************************************************/
BOOL_E Timer_GetStatus(Timer_ch_E);





#endif /* TIMER_H_ */