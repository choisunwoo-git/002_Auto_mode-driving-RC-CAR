/*
 * speed.h
 *
 *  Created on: Oct 29, 2025
 *      Author: user13
 */

#ifndef INC_SPEED_H_
#define INC_SPEED_H_

#include "stm32f4xx_hal.h"
#include "tim.h"
#include "stdio.h"
#include "bluetooth.h"


void motor_speedInit();
void motor_speedUp();
void motor_speedDown();
void pwm_sweep_test();
void motor_speed();
#endif /* INC_SPEED_H_ */
