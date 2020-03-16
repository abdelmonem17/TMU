/*
 * types.h
 *
 * Created: 10/21/2019 3:28:17 PM
 *  Author: AVE-LAP-062
 */ 


#ifndef TYPES_H_
#define TYPES_H_


/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;
typedef signed long long sint64;
typedef volatile uint8* const reg8_type;
typedef volatile uint16* const reg16_type;

#define OK								0
#define NOT_OK							1



#define NUMBER_ZERO						0
#define NUMBER_ONE						1
#define NUMBER_TWO						2
#define NUMBER_MINUS_ONE				-1



#endif /* TYPES_H_ */