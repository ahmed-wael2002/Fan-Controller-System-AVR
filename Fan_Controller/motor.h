/*
 * motor.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Wael
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"


/******************************************
 * 			MACROS DEFINITIONS
 ******************************************/
/* Defining Enable pin for Motor
 * In case of a variable speed driver:
 * 	This pin should be connected to timer PWM output pin
 */
#define MOTOR_EN_PORT 	PORTB_ID
#define MOTOR_EN_PIN 	PIN3_ID

/* Defining First Input pin for Motor */
#define MOTOR_IN1_PORT 	PORTB_ID
#define MOTOR_IN1_PIN 	PIN0_ID

/* Defining Second Input pin for Motor */
#define MOTOR_IN2_PORT	PORTB_ID
#define MOTOR_IN2_PIN	PIN1_ID

/******************************************
 * 			 TYPES DEFINITIONS
 ******************************************/
/*
 * This enum is used to define the direction of rotation of the motor
 * 1- OFF			: IN1=0, IN2=0
 * 2- ANTICLOCKWISE	: IN1=0, IN2=1
 * 3- CLOCKWISE		: IN1=1, IN2=0
 */
typedef enum{
	OFF,			/* 00 */
	ANTICLOCKWISE, 	/* 01 */
	CLOCKWISE		/* 10 */
}DcMotor_State;

/******************************************
 * 			FUNCTION PROTOTYPES
 ******************************************/
void DcMotor_init(void);
void DcMotor_Rotate(DcMotor_State state, uint8 speed);


#endif /* MOTOR_H_ */
