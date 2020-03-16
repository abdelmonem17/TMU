/*
 * timer.c
 *
 * Created: 11/4/2019 1:43:00 PM
 *  Author: AVE-LAP-062
 */ 
#include "timer.h"
#include "avr/io.h"
#include "types.h"

#define PRESCALER_1024			1024
#define PRESCALER_256			256
#define PRESCALER_128			128
#define PRESCALER_64			64
#define PRESCALER_8				8

#define CLEAR_PRESCALER					0xF8
#define TIMER0_COMP_MODE				0x8
#define MICRO_SECOND_INVERSE			1000000.0
#define TIMER0_MAX_COUNTS				256




pFun Timer0_ISR[3];





static uint8 presacler0=0; 
static uint8 time0_matched=0;
volatile uint16 timer0_ticks=0; 


/****************************************************************************
*
*   @brief function initiates timers
*   this function  takes timer configuration and return the status
*   @params  name : timer_cgf
*			 type :Timer_cfg_S *
*   @return status_E
****************************************************************************/
uint8 Timer_Init(Timer_cfg_S * timer_cgf)
{	
	
	uint32 counter_us;
	counter_us=(timer_cgf->CPU_clk /MICRO_SECOND_INVERSE)*timer_cgf->counter_us;

	switch(timer_cgf->ch)
	{
		case CH0:
		{
			
			switch(timer_cgf->mode)
			{
				case TIMER:
				//to calculate the precious delay
				if (  (counter_us <= TIMER0_MAX_COUNTS) )
				{
					presacler0=_NO_PRESCALER0;
					
				}
				else if (  (counter_us/PRESCALER_8 <= TIMER0_MAX_COUNTS) )
				{
					presacler0=_8_PRESCALER0;
					counter_us /=PRESCALER_8;
					
				}
				else if (  (counter_us/PRESCALER_64 <= TIMER0_MAX_COUNTS) )
				{
					presacler0=_64_PRESCALER0;
					counter_us /=PRESCALER_64;
					
				}
				else if ( (counter_us/PRESCALER_256 <= TIMER0_MAX_COUNTS) )
				{
					presacler0=_256_PRESCALER0;
					counter_us /=PRESCALER_256;
					
				}
				else if (  (counter_us/PRESCALER_1024 <= TIMER0_MAX_COUNTS) )
				{
					presacler0=_1024_PRESCALER0;
					counter_us /=PRESCALER_1024;
					
				}
				else
				{
					return NOT_OK;
				}
				
				break;
			case COUNTER_FALLING:
				/*			make T0 as counter with external clock , internally pull up pin		*/
				Gpio_PinDirection(TIMER0_EXT_CLK_PIN_PORT,TIMER0_EXT_CLK_PIN,INPUT);
				Gpio_PinWrite(TIMER0_EXT_CLK_PIN_PORT,TIMER0_EXT_CLK_PIN,HIGH);
				presacler0=_EXT_FALLING0;
				break;
			case COUNTER_RISING:
				/*			make T0 as counter with external clock , internally pull up pin		*/
				Gpio_PinDirection(TIMER0_EXT_CLK_PIN_PORT,TIMER0_EXT_CLK_PIN,INPUT);
				Gpio_PinWrite(TIMER0_EXT_CLK_PIN_PORT,TIMER0_EXT_CLK_PIN,HIGH);
				presacler0=_EXT_RISING0;
				break;
			default:
				return NOT_OK;
				break;
			
			}
			TIMER0_COMPARE_REG = counter_us;
			TIMER0_CTL_REG=TIMER0_COMP_MODE;   //compare mode
			/*		enable polling or interrupt		*/
			if (timer_cgf->interrupt == INTERRUPT)
			{
				INT_TIMER0_OC_ENABLE();
				INT_GLOBAL_FLAG_ENABLE();
			}
			else
			{
				INT_TIMER0_OC_DISABLE();
			}
			
			break;
		}
		default:
		   return NOT_OK;
			break;
	}
	
	
	return OK;
}

/****************************************************************************
*
*   @brief function starts timer
*   this function  takes timer channel and return void
*   @params  name : channel
*			 type :Timer_ch_E
*   @return status_E
****************************************************************************/
void Timer_Start(Timer_ch_E ch)
{
	switch(ch)
	{
		case CH0:
			TIMER0_COUNTER_REG=NUMBER_ZERO;
			TIMER0_CTL_REG |=presacler0;
			break;
		default:
		break;
	}
}

/****************************************************************************
*
*   @brief function stops timer
*   this function  takes timer channel and return void
*   @params  name : channel
*			 type :Timer_ch_E
*   @return status_E
****************************************************************************/
void Timer_Stop(Timer_ch_E ch)
{
	switch(ch)
	{
		case CH0:
		/*	clear presacler		*/
		
		TIMER0_CTL_REG &=CLEAR_PRESCALER;
		break;
		default:
		break;
	}
}


/****************************************************************************
*
*   @brief function sets timer counter
*   this function  takes timer channel and counter value , and return void
*   @params  name : channel
*			 type :Timer_ch_E
*   @params  name : counter_us
*			 type :uint16
*   @return status_E
****************************************************************************/

uint8 Timer_set_counter(Timer_ch_E ch,uint16 counter_us)
{
	switch(ch)
	{
		case CH0:
			/*					to calculate the precious delay							*/
			if (  (counter_us <=TIMER0_MAX_COUNTS) )
			{
				presacler0=_NO_PRESCALER0;
				
			}
			else if (  (counter_us/PRESCALER_8 <=TIMER0_MAX_COUNTS) )
			{
				presacler0=_8_PRESCALER0;
				counter_us /=PRESCALER_8;
				
			}
			else if (  (counter_us/PRESCALER_64 <=TIMER0_MAX_COUNTS) )
			{
				presacler0=_64_PRESCALER0;
				counter_us /=PRESCALER_64;
				
			}
			else if ( (counter_us/PRESCALER_256 <=TIMER0_MAX_COUNTS) )
			{
				presacler0=_256_PRESCALER0;
				counter_us /=PRESCALER_256;
				
			}
			else if (  (counter_us/PRESCALER_1024 <=TIMER0_MAX_COUNTS) )
			{
				presacler0=_1024_PRESCALER0;
				counter_us /=PRESCALER_1024;
				
			}
			else
			{
				return NOT_OK;
			}
			return OK;
			TIMER0_COMPARE_REG=counter_us;
			/*					start timer with presacler0				*/
			
			TIMER0_CTL_REG =( TIMER0_CTL_REG & (~CLEAR_PRESCALER) ) | presacler0;
			break;
		default:
		return NOT_OK;
		break;
	}
	
}


/****************************************************************************
*
*   @brief function gets timer flag's state
*   this function  takes timer channel and return the status
*   @params  name : channel
*			 type :Timer_ch_E
*   @return BOOL_E
****************************************************************************/
BOOL_E Timer_GetStatus(Timer_ch_E ch)
{
	switch(ch)
	{
		case CH0:
			if ( (TIMER_INTERRUPT_FLAGS_REG & TIMER0_OC_FLAG) !=NUMBER_ZERO )
			{
				/*				stop timer     */
				/*				TIMER0_CTL_REG &=0xF8;			*/
				Timer_Stop(CH0);
				/*		clear interrupt flag		*/
				TIMER_INTERRUPT_FLAGS_REG =TIMER0_OC_FLAG;
				return true;
			}
			
			else if ((time0_matched==NUMBER_ONE))
			{
				Timer_Stop(CH0);
				time0_matched=0;
				return true;
			}
			else
			{
				return false;
			}
			break;
		default:
		return false;
			break;
	}
		
}

__attribute__((weak)) void	Timer0_Comp_Hock_ISR(void)
{

	timer0_ticks++;
}
INT_HANDLER(TIMER0_COMP_VECT)
{
	
	//Timer0_Comp_Hock_ISR();
	Timer0_ISR[TIMER0_ISR_INDEX]();
	
}