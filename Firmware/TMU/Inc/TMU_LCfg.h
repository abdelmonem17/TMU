/****************************************************************************
 * @file  TMU_LCfg.h
 * @brief this file includes TMU configurations
 *
 * @author Abdelmonem Mostafa
 * @date  OCT 2019
 *
 ****************************************************************************/


#ifndef TMU_LCONG_H_
#define TMU_LCONG_H_
#include "Types.h"
#include "timer.h"




/************************************************************************/
/*			typedef for structs                                               */
/************************************************************************/
typedef struct  
{
	uint8 channel;
	uint16 resultion_ms;
}TMU_ConfigType;


extern TMU_ConfigType TMU_conf;


#endif /* TMU_LCONG_H_ */