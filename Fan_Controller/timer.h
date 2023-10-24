/*
 * timer.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Wael
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
/***********************************************
 * 			   MACROS DEFINITIONS
 ***********************************************/
#define MAX_OUTPUT_COMPARE 	255
#define OC0_PORT_ID 		PORTB_ID
#define OC0_PIN_ID			PIN3_ID

/***********************************************
 * 				TYPES DEFINITIONS
 ***********************************************/
typedef enum{
	CLK_1=1,
	CLK_8,
	CLK_64,
	CLK_256,
	CLK_1024,
	EXTERNAL_FALLING_EDGE,
	EXTERNAL_RISING_EDGE
}Timer_Prescaler;

typedef enum{
	NORMAL_MODE,
	PWM_PHASE_CORRECT,
	COMPARE,
	FAST_PWM
}Timer_Mode;

typedef enum{
	NORMAL,				/** Normal Port Operation for all modes **/
	TOGGLE,				/** Toggle OC0 on compare match **/
	NON_INVERTING,		/** CLEAR OC0 on compare match **/
	INVERTING			/** SET OC0 on compare match **/
}Timer_Compare_Mode;

typedef struct{
	Timer_Prescaler prescaler;
	Timer_Mode mode;
	Timer_Compare_Mode cmp_mode;
}Timer_Config;

/***********************************************
 * 			   FUNCTION PROTOTYPES
 ***********************************************/
void Timer_init(const Timer_Config* configs);
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* TIMER_H_ */
