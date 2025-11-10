/*
 * bluetooth.h
 *
 *  Created on: Oct 28, 2025
 *      Author: user13
 */

#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

#include "main.h"
#include "usart.h"
#include "move.h"
#include "speed.h"
#include "Car light.h"
#include "urtrasoinc.h"

#include "delay_us.h"
#include "stdio.h"
#include "gpio.h"
#include "AutoMode.h"

void bluetoothControl();

extern uint8_t serial_RxData;   //다른 헤더, 소스에서 참고할수있게 주소값 선언
extern uint8_t AutoMode_Flag;

extern uint8_t go;                 //전진 변수
extern uint8_t back;               //후진 변수
extern uint8_t right;              //우회전 변수
extern uint8_t left;               //좌회전 변수
extern uint8_t stop;               //정지
extern uint16_t original_speed;
#endif /* INC_BLUETOOTH_H_ */
