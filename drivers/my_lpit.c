#include "my_lpit.h"
#include <stddef.h>
/*! Macro to convert a microsecond period to raw count value */
#define USEC_TO_COUNT(us, clockFreqInHz) (uint64_t)(((uint64_t)(us) * (clockFreqInHz)) / 1000000U)
/*
 * LPIT time counter
 * - gen periodic interrupt -> delay
 * - periodic trigger -> trigger ADC
 * @params : Clock / reload value / interrupt
 * @params : Mode(single / chained) / SW|HW trigger
 * */
volatile LPIT_CallBackType _lpitCallback ;
void LPIT_init(LPIT_CallBackType function){
	PCC->CLKCFG[PCC_LPIT0_INDEX] &= ~PCC_CLKCFG_PCS_MASK;
	// fast async
//	PCC->CLKCFG[PCC_LPIT0_INDEX] |= PCC_CLKCFG_PCS(3);// fast
//	SCG->FIRCDIV &= ~SCG_FIRCDIV_FIRCDIV2_MASK;
//	SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1);// div 1
	//slow
	PCC->CLKCFG[PCC_LPIT0_INDEX] |= PCC_CLKCFG_PCS(2);
	SCG->SIRCDIV &= ~SCG_SIRCDIV_SIRCDIV2_MASK;
	SCG->SIRCDIV |= SCG_SIRCDIV_SIRCDIV2(4);// clock=8 / 8 div = 1Mhz


	// enable clock/ async clock
	PCC->CLKCFG[PCC_LPIT0_INDEX] |= PCC_CLKCFG_CGC(1);

	//• Reset the timer channels and registers;
	LPIT0->MCR |= LPIT_MCR_SW_RST(1);
	LPIT0->MCR &= ~LPIT_MCR_SW_RST_MASK;
	//• Setup timer operation in debug and doze modes
	// and enable the module;
	LPIT0->MCR |= LPIT_MCR_M_CEN(1);
//	//• Setup the channel counters operation mode to "32-bit Periodic Counter",and keep
//	//default values for the trigger source;
//	LPIT0->CHANNEL[0].TCTRL &= ~LPIT_TCTRL_MODE_MASK;
//	//• Set timer period for channel 0 as 200ms;
//	LPIT0->CHANNEL[0].TVAL = 200001;
//	//• Enable channel0 interrupt;
//	LPIT0->MIER |= LPIT_MIER_TIE0(1);
//	NVIC->ISER[0] |= (1 << 22);


	_lpitCallback = function;

}
void LPIT_init_adc(){
	// enable slow clock 1MZ
	PCC->CLKCFG[PCC_LPIT0_INDEX] &= ~PCC_CLKCFG_PCS_MASK;
	PCC->CLKCFG[PCC_LPIT0_INDEX] |= PCC_CLKCFG_PCS(2);
	SCG->SIRCDIV &= ~SCG_SIRCDIV_SIRCDIV2_MASK;
	SCG->SIRCDIV |= SCG_SIRCDIV_SIRCDIV2(4);// clock=8 / 8 div = 1Mhz
	// setup channel
	LPIT0->MCR != LPIT_MCR_M_CEN(0);
	LPIT0->CHANNEL[0].TCTRL = 0;
	LPIT0->CHANNEL[0].TVAL = USEC_TO_COUNT(10000,f) - 1U;


	// set up dozen
	LPIT0->MCR != (LPIT_MCR_DBG_EN(0)
			| LPIT_MCR_DOZE_EN(0)
			| LPIT_MCR_M_CEN_MASK);
	// disable interrupt
	LPIT0->MIER &= ~ LPIT_MIER_TIE0_MASK;

}
void LPIT0_IRQHandler(void){
	// clear interrupt flag
	LPIT0->MSR = LPIT_MSR_TIF0(1);
	if(NULL != _lpitCallback){
		_lpitCallback();
	}
}
void LPIT_StartTimer(uint8_t channel){
	// CTRL[channel]_EN
	LPIT0->SETTEN |= LPIT_SETTEN_SET_T_EN_0(1);
	LPIT0->CHANNEL[channel].TCTRL |= LPIT_TCTRL_T_EN(1);
}
void LPIT_StopTimer(uint8_t channel){
	// CTRL[channel]_EN
}
void LPIT_Delay(uint32_t microSecond){

	/* f = 1Mhz = 1 000 000 hz
	 * delay time = 0.2s = T *(reload-1) = (reload-1)/f
	 * reload = [0.2]*1000000+1 = 200 001
	 */
	LPIT0->CHANNEL[0].TCTRL &= ~LPIT_TCTRL_MODE_MASK;
	LPIT0->CHANNEL[0].TVAL = USEC_TO_COUNT(microSecond,f) +1;


	LPIT0->MIER |= LPIT_MIER_TIE0(1);
	NVIC->ISER[0] |= (1 << 22);


}
