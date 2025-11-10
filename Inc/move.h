/*
 * move.h
 *
 *  Created on: Oct 28, 2025
 *      Author: user13
 */

#ifndef INC_MOVE_H_
#define INC_MOVE_H_

#include "main.h"
#include "bluetooth.h"
#include "AutoMode.h"
//
//void motor_go()         //모터 전진
//{
//        HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 1);
//        HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
//        HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 1);
//        HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);
//}


#define IN1_PIN  	GPIO_PIN_4
#define IN1_GPIO_PORT  	GPIOA
#define IN2_PIN  	GPIO_PIN_0
#define IN2_GPIO_PORT  	GPIOB
#define IN3_PIN  	GPIO_PIN_1
#define IN3_GPIO_PORT  	GPIOC
#define IN4_PIN  	GPIO_PIN_0
#define IN4_GPIO_PORT  	GPIOC


//===============================================================
 //자동모드

   void AutoMode_motor_init();       //초기값 설정
   void AutoMode_motor_go();         //모터 전진
   void AutoMode_motor_back();       //모터 후진
   void AutoMode_motor_right();      //자동차 자체 우회전
   void AutoMode_motor_left();       //자동차 자체 좌회전
   void AutoMode_motor_stop();       //전원x

//=================================================================
//블루투스 휴대폰 수동모드

void motor_init();
void motor_go();
void motor_back();
void motor_right();
void motor_left();
void motor_stop();


#endif /* INC_MOVE_H_ */
