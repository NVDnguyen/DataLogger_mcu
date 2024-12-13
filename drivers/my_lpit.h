/*
 * my_lpit.h
 *
 *  Created on: Dec 9, 2024
 *      Author: nvd
 */

#ifndef MY_LPIT_H_
#define MY_LPIT_H_
#include "MKE16Z4.h"
#define f 1000000

typedef void (*LPIT_CallBackType)(void); // Function pointer type
void LPIT_init_adc();
void LPIT_init(LPIT_CallBackType function);
void LPIT_StartTimer(uint8_t channel);
void LPIT_StopTimer(uint8_t channel);
void LPIT_Delay(uint32_t time);


#endif /* MY_LPIT_H_ */
