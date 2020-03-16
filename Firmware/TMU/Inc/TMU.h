/****************************************************************************
 * @file  TMU.h
 * @brief this file includes some functions prototype of time management unit
 *
 * @author Abdelmonem Mostafa
 * @date  NOV 16 2019
 *
 ****************************************************************************/


#ifndef TMU_H_
#define TMU_H_

#include "TMU_retval.h"
#include "TMU_LCfg.h"
/*- INCLUDES -----------------------------------------------*/


/*- CONSTANTS ----------------------------------------------*/
#ifndef NULL
#define NULL ( (void*)0 )
#endif

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void(*TMU_Job_t)(void);
/*- ENUMS --------------------------------------------------*/
typedef enum
{
	TMU_No_error=0,
	TMU_ErorrUnsuportedTimerResultion=-1,
	TMU_ErrorNullJobPointer=-2,
	TMU_ErrorNullIdPointer=-3,
	TMU_ErrorJobIdNotFound=-4,
	TMU_ErrorJobRepoFull=-5,
	TMU_ErrorChannelUnaviable=-6
	
}EnmTMUError_t;

typedef enum
{
	periodic,
	one_Shot	
}EnmTMUPeriodicity_t;


/*- FUNCTION DECLARATIONS ----------------------------------*/



/****************************************************************************
*
*   @brief function initiates TMU
*   this function  takes TMU configuration and return the enum for error
*   @params  name : ConfigPtr
*			 type :	const TMU_ConfigType *
*   @return EnmTMUError_t
****************************************************************************/
EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr ); 

/****************************************************************************
*
*   @brief function start calculating delay for a specific functionality
*   this function  takes TMU configuration and return the enum for error
*   @params  name : TMU_Job
*			 type :	TMU_Job_t
*   @params  name : pJob_Id
*			 type :	uint16
*   @params  name : delay_ms
*			 type :	uint16
*   @params  name : EnmTMUPeriodicity_t
*			 type :	periodicity
*   @return EnmTMUError_t
****************************************************************************/
EnmTMUError_t TMU_Start_Timer(TMU_Job_t TMU_Job ,uint16 *pJob_Id ,uint16 delay_ms,EnmTMUPeriodicity_t periodicity);

/****************************************************************************
*
*   @brief function initiates TMU
*   this function  takes job id and stop the timer for this job and return error type
*   @params  name : au16_job_Id
*			 type :	uint16
*   @return EnmTMUError_t
****************************************************************************/
EnmTMUError_t TMU_Stop_Timer(uint16 au16_job_Id );

/****************************************************************************
*
*   @brief function monitor jobs
*   this function  takes void and return void
*   @params  void
*   @return void
****************************************************************************/
void TMU_Dispatch(void);
/****************************************************************************
*
*   @brief function deinitiates TMU
*   this function  takes void and return void
*   @params  void
*   @return void
****************************************************************************/
void TMU_Dinit (void );


#endif /* TMU_H_ */