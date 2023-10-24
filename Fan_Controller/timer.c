/*
 * timer.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Wael
 */

#include "timer.h"
#include "common_macros.h"
#include "gpio.h"	   /* MCAL Component to deal with AVR */
#include <avr/io.h>	   /* Holds AVR registers defintion */

/* Function to initialize Timer0 with configurations and its
 * functionality
 */
void Timer_init(const Timer_Config* configs){
	/* TCCR0	: Register bits description:
	 * FOC0		: Force output compare = 0 (PWM Mode)
	 * WGM01:0	: Wave-Generation Mode = (configs->mode)
	 * COM01:0	: Compare Output Mode = 10 : Non-inverting mode (Always!)
	 * CS02:0 	: Clock Select = (configs->prescaler)
	 */
	TCCR0 =   (configs->mode << WGM00)
			| (configs->cmp_mode << COM00)
			| (configs->prescaler);

	/* Configuring Force Output Compare Bit
	 * -- CLEAR_BIT @ any PWM Mode
	 * -- SET_BIT @ any non-PWM Mode
	 */
	if (((configs->mode)!=FAST_PWM) && ((configs->mode)!=PWM_PHASE_CORRECT))
		SET_BIT(TCCR0, FOC0);
	else {
		GPIO_setupPinDirection(OC0_PORT_ID, OC0_PIN_ID, PIN_OUTPUT);
	}

	/* Enabling Interrupts per mode
	 * -- Normal Mode (Overflow Mode) : SET (Timer Overflow Interrupt Enable)
	 * -- Compare Modes : SET (Output Compare Interrupt Enable)
	 */
	if ((configs->mode)!=NORMAL_MODE)
		SET_BIT(TIMSK, OCIE0);
	else
		SET_BIT(TIMSK, TOIE0);

	/** Initializing Output Compare Register with 0 **/
	OCR0 = 0;
	TCNT0 = 0;
}

/* Function to change the duty_cycle analog signal of PWM Mode
 * Input should be a duty_cycle value 0:100, otherwise, the function dysfunctions
 */
void PWM_Timer0_Start(uint8 duty_cycle){
	if (duty_cycle<0 || duty_cycle>100){
		/** DO NOTHIING -- Invalid range! **/
	} else{
		uint8 compare_value = 0;
		/* Duty Cycle = (Compare Value) / (Max output compare value) */
		compare_value = (uint8)((uint16)(duty_cycle*MAX_OUTPUT_COMPARE)/100);
		OCR0 = compare_value;
	}
}
