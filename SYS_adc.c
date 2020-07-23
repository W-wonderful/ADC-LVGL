#include "stm32f1xx_it.h"
#include "main.h"
#include "cmsis_os.h"

#include "sys_adc.h"

extern ADC_HandleTypeDef hadc1;
static osSemaphoreId adc1Sem=NULL;
//extern osMutexId SYSMutexHandle;
static uint32_t adc1_value[1]; 
double Vbattery_V = 0.0;
static uint32_t Vbattery_ADC_Value=0;
 

float get_batt(void)
{
	if(!adc1Sem)
	{
		osSemaphoreDef(adc1Sem);
		adc1Sem = osSemaphoreCreate(osSemaphore(adc1Sem) , 1);
		osSemaphoreWait(adc1Sem , osWaitForever);
	} 
	
//	adc1_value[0] = 0;
	HAL_ADC_Start_DMA(&hadc1,&adc1_value[0], 1);	
	osSemaphoreWait(adc1Sem , 1000);
	Vbattery_ADC_Value = adc1_value[0];
  Vbattery_V = (float)(14.0f*Vbattery_ADC_Value)/12285.0f;
	
	return Vbattery_V;
}

//void get_Vbattery_value(double *Vhr, double *Vbattery)
//{
//	 adc_update_value();
////	  *Vhr  = Vhr_Value;
//	  *Vbattery = Vbattery_Value;
//}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
	/* Get the converted value of regular channel */
 if(AdcHandle == &hadc1 && adc1Sem)
		osSemaphoreRelease(adc1Sem);
}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef* AdcHandle)
{
	/* Get the converted value of regular channel */
 if(AdcHandle == &hadc1 && adc1Sem)
		osSemaphoreRelease(adc1Sem);
}

