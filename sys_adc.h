#ifndef __sys_adc_H
#define __sys_adc_H

#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))///////////��ȡһ�������Ԫ�ظ���
#define __LimitValue(x,min,max) ((x)=constrain((x),(min),(max)))
#define __LoopExecute(func,n) for(unsigned long i=0;i<(n);i++)func//////// ��һ�������ظ�����ָ������


//void get_adc_value(double *Vhr, double *Vbate);
//void adc_update_value(void);
float get_batt(void);

#endif /* __sys_adc_H */

