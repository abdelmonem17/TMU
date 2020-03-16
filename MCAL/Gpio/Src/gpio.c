
#include "gpio.h"

#define PORT_SET			0xFF
#define PORT_CLEAR			0
#define NIBBLE_HIGH_MASK	0xF0
#define NIBBLE_LOW_MASK		0x0F		

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
void GpioPortDirection(uint8 port, uint8 direction)
{
	switch(port)
	{
		case PORT_A :
			(direction ==OUTPUT) ? (DIR_A = PORT_SET) : (DIR_A=PORT_CLEAR);
			break;
		case PORT_B :
			(direction ==OUTPUT) ? (DIR_B = PORT_SET) : (DIR_B=PORT_CLEAR);
			break;
		case PORT_C :
			(direction ==OUTPUT) ? (DIR_C = PORT_SET) : (DIR_C=PORT_CLEAR);
			break;
		case PORT_D :
			(direction == OUTPUT) ? (DIR_D = PORT_SET) : (DIR_D=PORT_CLEAR);
			break;
		default:
			//error option
			break;
	}
}


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

void GpioPortWrite(uint8 port, uint8 value)
{
	switch(port)
	{
		case PORT_A :
			OUT_A =value;
			break;
		case PORT_B :
			OUT_B =value;
			break;
		case PORT_C :
			OUT_C =value;
			break;
		case PORT_D :
			OUT_D =value;
			break;
		default:
			/*		error option      */
			break;
	}
}

/****************************************************************************
*
*   @brief function toggle GPIO PORTS
*   this function takes port profile and value
*   @params  name : port
*			 type :uint8
*
*   @return void
****************************************************************************/
void GpioPortToggle(uint8 port)
{
	switch(port)
	{
		case PORT_A :
			//OUT_A ^=0xff;
			TOGGLE_BYTE(OUT_A);
			break;
		case PORT_B :
			//OUT_B ^=0xff;
			TOGGLE_BYTE(OUT_B);
			break;
		case PORT_C :
			//OUT_C ^=0xff;
			TOGGLE_BYTE(OUT_C);
			break;
		case PORT_D :
			//OUT_D ^=0xff;
			TOGGLE_BYTE(OUT_D);
			break;
		default:
			/*       error option          */
			break;
	}
}


/****************************************************************************
*
*   @brief function read GPIO PORTS
*   this function takes port profile
*   @params  name : port
*			 type :uint8
*
*   @return uint8
****************************************************************************/
uint8 GpioPortRead(uint8 port)
{
		switch(port)
		{
			case PORT_A :
				return IN_A ;
			case PORT_B :
				return IN_B ;
			case PORT_C :
				return IN_C ;
			case PORT_D :
				return IN_D ;
			default:
			/*           error option              */
				return NOT_OK;
		}
}





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
void Gpio_PinDirection(uint8 port, uint8 pins, uint8 direction)
{
	
	switch(port)
	{
		case PORT_A :
			(direction ==OUTPUT) ? (DIR_A |= pins) : (DIR_A &= (~pins) );
			break;
		case PORT_B :
			(direction ==OUTPUT) ? (DIR_B |= pins) : (DIR_B &= (~pins) );
			break;
		case PORT_C :
			(direction ==OUTPUT) ? (DIR_C |= pins) : (DIR_C &= (~pins) );
			break;
		case PORT_D :
			(direction ==OUTPUT) ? (DIR_D |= pins) : (DIR_D &= (~pins) );
			break;
			default:
			/*        error option            */
		break;
	}
	
}



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
void GpioPinWrite_Same_Value(uint8 port, uint8 pins, uint8 value)
{
	switch(port)
	{
		case PORT_A :
			/*     clear location            ,set value ones or zeros  */
			OUT_A = ( OUT_A & (~pins) ) | ( (value ==HIGH) ? pins : 0 )  ;
			break;
		case PORT_B :
			/*     clear location            ,set value ones or zeros  */
			OUT_B = ( OUT_B & (~pins) ) | ( (value ==HIGH) ? pins : 0 )  ;
			break;
		case PORT_C :
			/*     clear location            ,set value ones or zeros  */
			OUT_C = ( OUT_C & (~pins) ) | ( (value ==HIGH) ? pins : 0 )  ;
			break;
		case PORT_D :
			/*     clear location            ,set value ones or zeros  */
			OUT_D = ( OUT_D & (~pins) ) | ( (value ==HIGH) ? pins : 0 )  ;;
			break;
		default:
			/*     error option                                        */
			break;
	}
	
}



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
void Gpio_PinWrite(uint8 port, uint8 pins, uint8 value)
{
	switch(port)
	{
		case PORT_A :
		/*      clear location            ,set value        */
			OUT_A = ( OUT_A & (~pins) ) | ( value & pins)  ;
			break;
		case PORT_B :
			/*      clear location            ,set value        */
			OUT_B = ( OUT_B & (~pins) ) | ( value & pins  )  ;
			break;
		case PORT_C :
			/*      clear location            ,set value        */
			OUT_C = ( OUT_C & (~pins) ) | ( value & pins )   ;
			break;
		case PORT_D :
			/*      clear location            ,set value        */
			OUT_D = ( OUT_D & (~pins) ) | ( value & pins )    ;
			break;
		default:
			/*                  error option                   */
			break;
	}
	
}


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
void GpioPinToggle(uint8 port, uint8 pins)
{
	switch(port)
	{
		case PORT_A :
			OUT_A ^=pins;
			break;
		case PORT_B :
			OUT_B ^=pins;
		break;
		case PORT_C :
			OUT_C ^=pins;
			break;
		case PORT_D :
			OUT_D ^=pins;
		break;
			default:
		//error option
		break;
	}
}


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
uint8 GpioPinRead(uint8 port, uint8 pin)
{
	
	switch(port)
	{
		case PORT_A :
			return  ( ( IN_A & (1<<pin) ) !=0  ? HIGH :LOW) ;
		case PORT_B :
			return ( ( IN_B & (1<<pin) ) !=0 ? HIGH :LOW) ;
		case PORT_C :
			return ( ( IN_C & (1<<pin) ) !=0 ? HIGH :LOW) ;
		case PORT_D :
			return ( ( IN_D & (1<<pin) ) !=0 ? HIGH :LOW) ;
		default:
			/*           error option                    */
			return NOT_OK;
	}
	
}

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
void GpioUpperNibbleDirection(uint8 port, uint8 direction)
{
	switch(port)
	{
		case PORT_A :
			(direction == OUTPUT) ? (DIR_A |=0xF0) : (DIR_A &=0x0F);
			break;
		case PORT_B :
			(direction == OUTPUT) ? (DIR_B |=0xF0) : (DIR_B &=0x0F);
			break;
		case PORT_C :
			(direction == OUTPUT) ? (DIR_C |=0xF0) : (DIR_C &=0x0F);
			break;
		case PORT_D :
			(direction == OUTPUT) ? (DIR_D |=0xF0) : (DIR_D &=0x0F);
			break;
		default:
			/*            error option            */
			break;
	}
}


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
void GpioUpperNibbleWrite(uint8 port, uint8 value)
{
	switch(port)
	{
		case PORT_A :
			//clear upper ,		set upper	,shift value
			OUT_A = (OUT_A & NIBBLE_LOW_MASK) | (value<<4);
			break;
		case PORT_B :
			OUT_B = (OUT_B & NIBBLE_LOW_MASK) | (value<<4);
			break;
		case PORT_C :
			OUT_C = (OUT_C & NIBBLE_LOW_MASK) | (value<<4);
			break;
		case PORT_D :
			OUT_D = (OUT_D & NIBBLE_LOW_MASK) | (value<<4);
			break;
		default:
			/*        error option */
			break;
	}
}


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
uint8 GpioUpperNibbleRead(uint8 port)
{
	switch(port)
	{
		case PORT_A :
			return (IN_A >>4);
		case PORT_B :
			return (IN_B>>4) ;
		case PORT_C :
			return (IN_C >>4);
		case PORT_D :
			return (IN_D>>4) ;
		default:
			//error option
			return NOT_OK;
	}
}


/****************************************************************************
*
*   @brief function toggle higher four pins in a port
*   this function takes port profile
*   @params  name : port
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioUpperNibbleToggle(uint8 port)
{
	switch(port)
	{
		case PORT_A :
			OUT_A  ^=NIBBLE_HIGH_MASK ;
			break;
		case PORT_B :
			OUT_B ^= NIBBLE_HIGH_MASK ;
			break;
		case PORT_C :
			OUT_C ^=NIBBLE_HIGH_MASK ;
			break;
		case PORT_D :
			OUT_D  ^=NIBBLE_HIGH_MASK ;
			break;
		default:
			/*error option*/
		break;
	}
	
}

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
void GpioLowerNibbleDirection(uint8 port, uint8 direction)
{
	switch(port)
	{
		case PORT_A :
			(direction ==OUTPUT) ? (DIR_A |=NIBBLE_LOW_MASK ) : (DIR_A &=NIBBLE_HIGH_MASK);
			break;
		case PORT_B :
			(direction ==OUTPUT) ? (DIR_B |=NIBBLE_LOW_MASK) : (DIR_B &=NIBBLE_HIGH_MASK);
			break;
		case PORT_C :
			(direction ==OUTPUT) ? (DIR_C |=NIBBLE_LOW_MASK) : (DIR_C &=NIBBLE_HIGH_MASK);
			break;
		case PORT_D :
			(direction ==OUTPUT) ? (DIR_D |=NIBBLE_LOW_MASK) : (DIR_D &=NIBBLE_HIGH_MASK);
			break;
		default:
			/*       error option           */
			break;
	}
}


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
void GpioLowerNibbleWrite(uint8 port, uint8 value)
{
	switch(port)
	{
		case PORT_A :
			/*		clear upper ,		set upper	,value			*/
			OUT_A = (OUT_A & NIBBLE_HIGH_MASK) | (value & NIBBLE_LOW_MASK);
			break;
		case PORT_B :
			OUT_B = (OUT_B & NIBBLE_HIGH_MASK) | (value & NIBBLE_LOW_MASK);
			break;
		case PORT_C :
			OUT_C = (OUT_C & NIBBLE_HIGH_MASK) | (value & NIBBLE_LOW_MASK);
			break;
		case PORT_D :
			OUT_D = (OUT_D & NIBBLE_HIGH_MASK) | (value & NIBBLE_LOW_MASK);
			break;
		default:
			/*error option*/
			break;
	}
}


/****************************************************************************
*
*   @brief function toggle lowest four pins in a port
*   this function takes port profile and direction
*   @params  name : port
*			 type : uint8
*
*   @return  void
****************************************************************************/
void GpioLowerNibbleToggle(uint8 port)
{
	switch(port)
	{
		case PORT_A :
			/*clear upper ,		set upper	,shift value*/
			OUT_A  ^=NIBBLE_LOW_MASK ;
		break;
		case PORT_B :
			OUT_B ^= NIBBLE_LOW_MASK;
			break;
		case PORT_C :
			OUT_C ^= NIBBLE_LOW_MASK;
			break;
		case PORT_D :
			OUT_D  ^= NIBBLE_LOW_MASK;
			break;
		default:
			/* error option         */
			break;
	}
}




/****************************************************************************
*
*   @brief function read lowest four pins in a port
*   this function takes port profile and direction
*   @params  name : port
*			 type : uint8
*
*   @return  void
****************************************************************************/

uint8 GpioLowerNibbleRead(uint8 port)
{
	switch(port)
	{
		case PORT_A :
			return (IN_A & 0x0f);
		case PORT_B :
			return (IN_B & 0x0f) ;
		case PORT_C :
			return (IN_C & 0x0f);
		case PORT_D :
			return (IN_D & 0x0f) ;
		default:
			//error option
			return NOT_OK;
	}
}