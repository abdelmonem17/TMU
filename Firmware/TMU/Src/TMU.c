/****************************************************************************
 * @file  TMU.h
 * @brief this file includes some functions implementation of time management unit
 *
 * @author Abdelmonem Mostafa
 * @date  NOV 16 2019
 *
 ****************************************************************************/

#include "TMU.h"
#include "timer.h"


/*- LOCAL MACROS ------------------------------------------*/
#define MAX_JOBS_COUNTS		100
#define MS_TO_US			1000			
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/



typedef struct
{
	
	uint32					next_Excution_Time;
	EnmTMUPeriodicity_t		shots;
	uint16 *				id_address;
	TMU_Job_t				job;
	uint16					delay_ms;
	
}TMU_jobProfile_t;

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint16 gu16_JobIndex=0;
static	TMU_jobProfile_t gaTMU_jobProfile_t_JobsRepo	[MAX_JOBS_COUNTS];
static volatile uint16 TMU_Ticks=1; 
static volatile uint8 gu8_TMU_Ticks_ovFlag=0;



/*- APIs IMPLEMENTATION -----------------------------------*/

/****************************************************************************
*
*   @brief function called in ISR of the timer
*   this function  counts system ticks 
*   @params  void
*   @return EnmTMUError_t
****************************************************************************/
static void TMU_CallTimerBack(void)
{
	   if (TMU_Ticks == NUMBER_ZERO )
	   {
		   gu8_TMU_Ticks_ovFlag=1;
	   }
	   else
	   {
		   
	   }
	   TMU_Ticks +=TMU_conf.resultion_ms;
	    
		
}
/****************************************************************************
*
*   @brief function initiates TMU
*   this function  takes TMU configuration and return the enum for error
*   @params  name : ConfigPtr
*			 type :	const TMU_ConfigType *
*   @return EnmTMUError_t
****************************************************************************/

EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr )
{
	timer_cfg.ch= ConfigPtr->channel;
	timer_cfg.counter_us=ConfigPtr->resultion_ms * MS_TO_US;
	
	if (Timer_Init(&timer_cfg) == NOT_OK)
	{
		return TMU_ErorrUnsuportedTimerResultion;
	}
	else
	{
		Timer_Start(ConfigPtr->channel);
		
	}
	switch(ConfigPtr->channel)
	{
		/*		assign function to count system ticks for TMU		*/
		case CH0:
			Timer0_ISR[TIMER0_ISR_INDEX]=TMU_CallTimerBack;
			break;
		default :
			return TMU_ErrorChannelUnaviable;
	}
	return TMU_No_error;
}

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
EnmTMUError_t TMU_Start_Timer(TMU_Job_t TMU_Job ,uint16 *pJob_Id ,uint16 delay_ms,EnmTMUPeriodicity_t shots_state)
{
	
	if (gu16_JobIndex != MAX_JOBS_COUNTS )
	{
		
	
		if (pJob_Id !=NULL && TMU_Job !=NULL)
		{
			*pJob_Id=gu16_JobIndex;
			gaTMU_jobProfile_t_JobsRepo[gu16_JobIndex].id_address=pJob_Id;
			gaTMU_jobProfile_t_JobsRepo[gu16_JobIndex].job=TMU_Job;
			gaTMU_jobProfile_t_JobsRepo[gu16_JobIndex].delay_ms=delay_ms;
			gaTMU_jobProfile_t_JobsRepo[gu16_JobIndex].shots=shots_state;
			gaTMU_jobProfile_t_JobsRepo[gu16_JobIndex].next_Excution_Time= TMU_Ticks+delay_ms;
			++gu16_JobIndex;
			return TMU_No_error;
		}
		else if(pJob_Id == NULL)
		{
			return TMU_ErrorNullIdPointer;
		}
		else
		{
			return TMU_ErrorNullJobPointer;
		}
	}
	else
	{
		return TMU_ErrorJobRepoFull;
	}
	
		
}


/****************************************************************************
*
*   @brief function initiates TMU
*   this function  takes job id and stop the timer for this job and return error type
*   @params  name : au16_job_Id
*			 type :	uint16
*   @return EnmTMUError_t
****************************************************************************/
EnmTMUError_t TMU_Stop_Timer(uint16 au16_job_Id )
{
		/*    overwrite on the job that will be deleted by the last job in the list  */ 
	if ( (au16_job_Id >=0) && (au16_job_Id < gu16_JobIndex) )
	{
		
		gaTMU_jobProfile_t_JobsRepo[au16_job_Id]=gaTMU_jobProfile_t_JobsRepo[--gu16_JobIndex];
		
		/*   	reassign the job id that was in the last location in the list	*/
		if(gaTMU_jobProfile_t_JobsRepo[gu16_JobIndex].id_address !=NULL)
		{
			*(gaTMU_jobProfile_t_JobsRepo[gu16_JobIndex].id_address) = au16_job_Id;
		}
		else
		{
			/*	unhandled null reference     */
		}
		return TMU_No_error;
	}
	else
	{
		return TMU_ErrorJobIdNotFound;
	}
}


/****************************************************************************
*
*   @brief function monitor jobs
*   this function  takes void and return void
*   @params  void
*   @return void
****************************************************************************/
void TMU_Dispatch(void)
{
	uint8 au8_TMU_Ticks_ovFlag=gu8_TMU_Ticks_ovFlag;
	/*			 assign flag after reading it			*/
	gu8_TMU_Ticks_ovFlag=NUMBER_ZERO;
	for (uint16 au8_job_Index=0 ; au8_job_Index < gu16_JobIndex ; au8_job_Index++ )
	{
		/*		to handle tmu ticks  overflow		*/
		if (au8_TMU_Ticks_ovFlag == NUMBER_ONE)
		{
			gaTMU_jobProfile_t_JobsRepo[au8_job_Index].next_Excution_Time=(uint16)gaTMU_jobProfile_t_JobsRepo[au8_job_Index].next_Excution_Time;
					
		}
		/*		check for job time if it came	*/
		if (  (gaTMU_jobProfile_t_JobsRepo[au8_job_Index].next_Excution_Time <=  TMU_Ticks  ))
		{
			/*		execute the job		*/
			gaTMU_jobProfile_t_JobsRepo[au8_job_Index].job();
			
			/*   check if the job one job */
			if(gaTMU_jobProfile_t_JobsRepo[au8_job_Index].shots == one_Shot)
			{
				TMU_Stop_Timer(au8_job_Index);
			}
			else
			{
				
				/*  calculate the next time for the job to be executed */
				gaTMU_jobProfile_t_JobsRepo[au8_job_Index].next_Excution_Time += gaTMU_jobProfile_t_JobsRepo[au8_job_Index].delay_ms;
				
			}
		}
		else
		{
			//noting
		}
		
		
	}
	
		
	

}


/****************************************************************************
*
*   @brief function deinitiates TMU
*   this function  takes void and return void
*   @params  void
*   @return void
****************************************************************************/
void TMU_Dinit (void )
{
	/*    clear timer configurations */
	Timer_Stop(CH0);
	timer_cfg.ch= NUMBER_MINUS_ONE;
	timer_cfg.counter_us=NUMBER_ZERO;
	
	
	/*		clear job rep			*/
	gu16_JobIndex=NUMBER_ZERO;
	
}