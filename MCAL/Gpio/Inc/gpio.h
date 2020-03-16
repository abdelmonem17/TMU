
/****************************************************************************
 * @file  customer.h
 * @brief this file includes some functions prototype to manipulate GPIO
 *
 * @author Abdelmonem Mostafa
 * @date  OCT 2019
 *
 ****************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_
#include "types.h"
#include "mega32_registers.h"


/************************************************************************/
/*						  PORTS ids                            */
/************************************************************************/

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3



/************************************************************************/
/*						  defines   input and output                            */
/************************************************************************/
#define INPUT  0	// defines LOW value for a bit
#define OUTPUT 1	// defines HIGH value for a bit


/************************************************************************/
/*				 Enum for defining bit numbers                          */
/************************************************************************/
typedef enum EN_bits
{
	BIT0 = 0x01,	// defines BIT0 in a register
	BIT1 = 0x02,	// defines BIT1 in a register
	BIT2 = 0x04,	// defines BIT2 in a register
	BIT3 = 0x08,	// defines BIT3 in a register
	BIT4 = 0x10,	// defines BIT4 in a register
	BIT5 = 0x20,	// defines BIT5 in a register
	BIT6 = 0x40,	// defines BIT6 in a register
	BIT7 = 0x80,	// defines BIT7 in a register
}EN_bits;

/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0	// defines LOW value for a bit
#define HIGH 1	// defines HIGH value for a bit


/************************************************************************/
/*				 Bits' Manipulation Macros	                            */
/************************************************************************/
#define SET_BIT(reg,bit)	reg|=(1<<bit)
#define CLR_BIT(reg,bit)	reg&=~(1<<bit)
#define READ_BIT(reg,bit)	reg&(1<<bit)
#define TOGGLE_BIT(reg,bit)	reg^=(1<<bit)

#define SET_BYTE(reg)	reg|=0xFF
#define CLR_BYTE(reg)	reg=0
#define TOGGLE_BYTE(reg)	reg^=0xff

/************************************************************************/
/*				 GPIO functions' prototypes	                            */
/************************************************************************/

/*===========================PORT Control===============================*/


/****************************************************************************
*
*   @brief function set GPIO PORTS direction
*   this function takes port profile and direction
*   @params  name : port
*			 type :uint8
*   @params  name : direction
*			 type :uint8
*				
*   @return void
****************************************************************************/
void GpioPortDirection(uint8 port, uint8 direction);



/****************************************************************************
*
*   @brief function write to GPIO PORTS
*   this function takes port profile and value
*   @params  name : port
*			 type :uint8
*   @params  name : value
*			 type :uint8
*
*   @return void
****************************************************************************/
void GpioPortWrite(uint8 port, uint8 value);




/****************************************************************************
*
*   @brief function toggle GPIO PORTS
*   this function takes port profile and value
*   @params  name : port
*			 type :uint8
*
*   @return void
****************************************************************************/

void GpioPortToggle(uint8 port);


/****************************************************************************
*
*   @brief function read GPIO PORTS
*   this function takes port profile
*   @params  name : port
*			 type :uint8
*
*   @return uint8
****************************************************************************/
uint8 GpioPortRead(uint8 port);


/*===========================PIN Control===============================*/




/****************************************************************************
*
*   @brief function set GPIO pins direction
*   this function takes port profile and pins and direction
*   @params  name : port
*			 type : uint8
*   @params  name : pins
*			 type : uint8
*   @params  name : direction
*			 type : uint8
*
*   @return  void
****************************************************************************/
void Gpio_PinDirection(uint8 port, uint8 pins, uint8 direction);



/****************************************************************************
*
*   @brief function write to specific pins
*   this function takes port profile ,pins and value
*   @params  name : port
*			 type : uint8
*   @params  name : pins
*			 type : uint8
*   @params  name : value
*			 type : uint8
*
*   @return  void
****************************************************************************/
void Gpio_PinWrite(uint8 port, uint8 pins, uint8 value);


/****************************************************************************
*
*   @brief function write high or low to specific pins
*   this function takes port profile ,pins and value
*   @params  name : port
*			 type : uint8
*   @params  name : pins
*			 type : uint8
*   @params  name : value
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioPinWrite_Same_Value(uint8 port, uint8 pins, uint8 value);



/****************************************************************************
*
*   @brief function toggle specific pins
*   this function takes port profile and pins
*   @params  name : port
*			 type : uint8
*   @params  name : pins
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioPinToggle(uint8 port, uint8 pins);


/****************************************************************************
*
*   @brief function read a specific pin
*   this function takes port profile and pin
*   @params  name : port
*			 type : uint8
*   @params  name : pin
*			 type : uint8
*
*   @return  uint8
****************************************************************************/
uint8 GpioPinRead(uint8 port, uint8 pin);



/*===========================Upper Nibble Control===============================*/

/****************************************************************************
*
*   @brief function set direction to higher four pins in a port
*   this function takes port profile and direction
*   @params  name : port
*			 type : uint8
*   @params  name : direction
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioUpperNibbleDirection(uint8 port, uint8 direction);


/****************************************************************************
*
*   @brief function write to to higher four pins in a port
*   this function takes port profile and direction
*   @params  name : port
*			 type : uint8
*   @params  name : value
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioUpperNibbleWrite(uint8 port, uint8 value);


/****************************************************************************
*
*   @brief function toggle higher four pins in a port
*   this function takes port profile
*   @params  name : port
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioUpperNibbleToggle(uint8 port);


/****************************************************************************
*
*   @brief function read higher four pins in a port
*   this function takes port profile and return port value
*   @params  name : port
*			 type : uint8
*   @params  name : direction
*			 type : uint8
*
*   @return  void
****************************************************************************/
uint8 GpioUpperNibbleRead(uint8 port);

/*===========================Lower Nibble Control===============================*/



/****************************************************************************
*
*   @brief function set direction to lower four pins in a port
*   this function takes port profile and direction
*   @params  name : port
*			 type : uint8
*   @params  name : direction
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioLowerNibbleDirection(uint8 port, uint8 direction);


/****************************************************************************
*
*   @brief function write to lowest four pins in a port
*   this function takes port profile and direction
*   @params  name : port
*			 type : uint8
*   @params  name : value
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioLowerNibbleWrite(uint8 port, uint8 value);



/****************************************************************************
*
*   @brief function toggle lowest four pins in a port
*   this function takes port profile and direction
*   @params  name : port
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioLowerNibbleToggle(uint8 port);

/****************************************************************************
*
*   @brief function read lowest four pins in a port
*   this function takes port profile and direction
*   @params  name : port
*			 type : uint8
*
*   @return  void
****************************************************************************/

uint8 GpioLowerNibbleRead(uint8 port);


#endif /* GPIO_H_ */