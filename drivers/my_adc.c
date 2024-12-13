/*
 * my_adc.c
 *
 *  Created on: Dec 4, 2024
 *      Author: nvd
 */

#include "my_adc.h"
#include "my_lpit.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void ADC_Init()
{
	PCC->CLKCFG[PCC_ADC0_INDEX] &= ~PCC_CLKCFG_CGC_MASK;

	PCC->CLKCFG[PCC_ADC0_INDEX] &= ~PCC_CLKCFG_PCS_MASK;
	PCC->CLKCFG[PCC_ADC0_INDEX] |= PCC_CLKCFG_PCS(2);

	SCG->SIRCDIV &= ~SCG_SIRCDIV_SIRCDIV2_MASK;
	SCG->SIRCDIV |= SCG_SIRCDIV_SIRCDIV2(4);	// Async CLK = SIRC / 8 = 1MHz

	// clock (bus peripheral clock / async clock)
	PCC->CLKCFG[PCC_ADC0_INDEX] |= PCC_CLKCFG_CGC(1);

	ADC0->CFG1 &= ~ADC_CFG1_ADICLK_MASK;	// ALT CLK 1


	// V-ref
	// Resolution (12-bit, 10-bit, and 8-bit)
	// Single or continuous conversion modes SC3[ADCO]

	// Configurable sample time and conversion speed/power

	// Software or hardware conversion trigger = SC2[ADTRG]

	// Automatic compare ?? - None

	// Hardware average function?? - None

	// Interrupt ?

}

//Synchronous
//	Polling
//
//Asynchronous
//	Interrupt
//	DMA


uint16_t ADC_ReadPolling()// read sync
{
	// Start Conversion
	// SW Trigger - SC1A[ADCH] = 11010 (Temperature Sensor)
#define A   0
	// Read - Modify - Write
	//u32 temp = ADC0->SC1[A];		// xxxxxxxxxxxxxxxxxx.11111

	//temp &= ~ADC_SC1_ADCH_MASK;		// xxxxxxxxxxxxxxxxxx.00000
	//temp |= ADC_SC1_ADCH(0b11010);	// xxxxxxxxxxxxxxxxxx.11010

	ADC0->SC1[A] = (ADC0->SC1[A] & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(0b11010);

	// Wait EOC - N * T		SC1n[COCO]
	while( (ADC0->SC1[A] & ADC_SC1_COCO_MASK) == 0 );

	// Read Data Register - Rn
	return ADC0->R[A];
}

uint16_t ADC_ReadAsync()
{
	//enable interrupt
	ADC0->SC1[A] = ADC_SC1_AIEN(1);
	// NVIC enable interrupt ADC0_IRQn
    //NVIC->ISER[0U] = (uint32_t)(1UL << (((uint32_t)ADC0_IRQn) & 0x1FUL));
	// Enable DMA [100] -> ADC -> RAM Array[100]
	ADC0->SC1[A] = (ADC0->SC1[A] & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(0b11010);
}

/**
 * // PIT - Time Counter
	//  - Generate Periodic Interrupt (Delay)
	//  - Periodic Trigger to other peripherals (Trigger ADC)
	// Start : Software / Trigger from another module / chained mode
    // Clock
	//LPIT_Init();
	ADC_Init();

	// Blinked LED - 200ms - use the PIT Interrupt
	//LPIT_StartTimer(0);
	uint16_t ADC_Data;

    while (1)
    {
    	ADC_Data = ADC_ReadPolling();
    	ADC_Data *= 2;
    }
    (void)ADC_Data;
 * */
