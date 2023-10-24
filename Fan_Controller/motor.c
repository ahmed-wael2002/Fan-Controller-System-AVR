/*
 * motor.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Wael
 */

#include "motor.h"
#include "timer.h"
#include "gpio.h"

void DcMotor_init(void){
	/* Initializing Timer --Setting up PWM Signal */
	Timer_Config timer_configurations = {CLK_8, FAST_PWM, NON_INVERTING};
	Timer_init(&timer_configurations);

	/* setup direction of motor pins to be OUTPUT */
	GPIO_setupPinDirection(MOTOR_EN_PORT, MOTOR_EN_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_IN1_PORT, MOTOR_IN1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_IN2_PORT, MOTOR_IN2_PIN, PIN_OUTPUT);

	/* Initialize motor @ stop state : assign 00 to both pins */
	GPIO_writePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed){
	/* Changing speed of the motor
	 * -- Change the duty cycle of the PWM signal from the timer
	 * -- The PWM signal is output to the enable pin of the driver
	 */
	PWM_Timer0_Start(speed);

	if (state == OFF){
		GPIO_writePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, LOGIC_LOW);
	}
	else if (state == ANTICLOCKWISE){
		GPIO_writePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, LOGIC_HIGH);
	}
	else if (state == CLOCKWISE){
		GPIO_writePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, LOGIC_HIGH);
		GPIO_writePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, LOGIC_LOW);
	}
}
