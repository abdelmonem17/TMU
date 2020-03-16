/*
 * interrupt.h
 *
 * Created: 10/24/2019 2:30:39 PM
 *  Author: AVE-LAP-062
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include "mega32_registers.h"


	
//interrupt vectors
#define INT0_VECT			__vector_1


/* External Interrupt Request 1 */

#define INT1_VECT			__vector_2


/* External Interrupt Request 2 */

#define INT2_VECT			__vector_3


/* Timer/Counter2 Compare Match */

#define TIMER2_COMP_VECT		__vector_4


/* Timer/Counter2 Overflow */

#define TIMER2_OVF_VECT			__vector_5


/* Timer/Counter1 Capture Event */

#define TIMER1_CAPT_VECT		__vector_6


/* Timer/Counter1 Compare Match A */

#define TIMER1_COMPA_VECT		__vector_7


/* Timer/Counter1 Compare Match B */

#define TIMER1_COMPB_VECT		__vector_8


/* Timer/Counter1 Overflow */

#define TIMER1_OVF_VECT			__vector_9


/* Timer/Counter0 Compare Match */

#define TIMER0_COMP_VECT		__vector_10


/* Timer/Counter0 Overflow */

#define TIMER0_OVF_VECT			__vector_11


/* Serial Transfer Complete */

#define SPI_STC_VECT			__vector_12


/* USART, Rx Complete */

#define USART_RXC_VECT			__vector_13


/* USART Data Register Empty */

#define USART_DATA_EMPTY_VECT			__vector_14


/* USART, Tx Complete */

#define SIG_USART_TRANS_VECT			__vector_15


/* ADC Conversion Complete */

#define ADC_VECT			__vector_16


/* EEPROM Ready */

#define EE_RDY_VECT			__vector_17


/* Analog Comparator */

#define ANA_COMP_VECT			__vector_18


/* 2-wire Serial Interface */

#define TWI_VECT			__vector_19


/* Store Program Memory Ready */

#define SPM_RDY_VECT			__vector_20


#define _VECTORS_SIZE 84



#define __DIS_OPIMIZATION_ used
#define INT_HANDLER(vector,...)		\
									void vector (void) __attribute__ ((signal, __DIS_OPIMIZATION_)) __VA_ARGS__; \
									void vector (void)


//enabling interrupt macros
#define INT_GLOBAL_FLAG_ENABLE()		( STATUS_REG |=  (INT_GLOBAL_FLAG) )
#define INT_GLOBAL_FLAG_DISABLE()		( STATUS_REG &= ~(INT_GLOBAL_FLAG) )

//timer0 interrupt control
#define INT_TIMER0_OVF_ENABLE()			(TIMER_MSK_REG |= (TIMER0_OVF_INT_EN) )
#define INT_TIMER0_OVF_DISABLE()		(TIMER_MSK_REG &=~(TIMER0_OVF_INT_EN) )

#define INT_TIMER0_OC_ENABLE()			(TIMER_MSK_REG |= (TIMER0_OC_INT_EN) )
#define INT_TIMER0_OC_DISABLE()			(TIMER_MSK_REG &=~(TIMER0_OC_INT_EN) )


//timer1 interrupt control
#define INT_TIMER1_OVF_ENABLE()			(TIMER_MSK_REG |=  (TIMER1_OVF_INT_EN) )
#define INT_TIMER1_OVF_DISABLE()		(TIMER_MSK_REG &= ~(TIMER1_OVF_INT_EN) )

#define INT_TIMER1_OCA_ENABLE()			(TIMER_MSK_REG |=  (TIMER1_OCA_INT_EN) )
#define INT_TIMER1_OCA_DISABLE()		(TIMER_MSK_REG &= ~(TIMER1_OCA_INT_EN) )

#define INT_TIMER1_OCB_ENABLE()			(TIMER_MSK_REG |=   (TIMER1_OCB_INT_EN) )
#define INT_TIMER1_OCB_DISABLE()		(TIMER_MSK_REG &= ~ (TIMER1_OCB_INT_EN) )

#define INT_TIMER1_IC_ENABLE()			(TIMER_MSK_REG |=   (TIMER1_IC_INT_EN) )
#define INT_TIMER1_IC_DISABLE()		    (TIMER_MSK_REG &= ~ (TIMER1_IC_INT_EN) )


//timer2 interrupt control
#define INT_TIMER2_OVF_ENABLE()			(TIMER_MSK_REG |= (TIMER2_OVF_INT_EN) )
#define INT_TIMER2_OVF_DISABLE()		(TIMER_MSK_REG &=~(TIMER2_OVF_INT_EN) )

#define INT_TIMER2_OC_ENABLE()			(TIMER_MSK_REG |= (TIMER2_OC_INT_EN) )
#define INT_TIMER2_OC_DISABLE()			(TIMER_MSK_REG &=~(TIMER2_OC_INT_EN) )



#define INT_EXT0_ANYEDGE				0x01
#define INT_EXT0_FALLINGEDGE			0x02
#define INT_EXT0_RISINGEDGE				0x03
#define INT_EXT0_PIN_LOC				BIT6


#define INT_EXT0_EN_ANYEDGE()			MCU_CTL=( ( MCU_CTL& 0xfC ) |INT_EXT0_ANYEDGE );\
										INT_GCTL  |= INT_EXT0_PIN_LOC
										

#define INT_EXT0_EN_RISING()			MCU_CTL=( ( MCU_CTL& 0xfC ) |INT_EXT0_RISINGEDGE );\
										INT_GCTL  |= INT_EXT0_PIN_LOC
										
#define INT_EXT0_EN_FALLING()			MCU_CTL=( ( MCU_CTL& 0xfC ) |INT_EXT0_FALLINGEDGE );\
										INT_GCTL  |= INT_EXT0_PIN_LOC
										
#define INT_EXT0_DIS()					INT_GCTL  &= ~INT_EXT0_PIN_LOC

#endif /* INTERRUPT_H_ */