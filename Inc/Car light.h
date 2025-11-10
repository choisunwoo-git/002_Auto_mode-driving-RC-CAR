


#ifndef INC_CAR_LIGHT_H_
#define INC_CAR_LIGHT_H_



#endif /* INC_CAR_LIGHT_H_ */

#include "main.h"

#define   CAR_LIGHT_PIN         GPIO_PIN_1
#define   CAR_LIGHT_PORT        GPIOA


void Car_Light_Init();  //자동차 Flash 초기값

void Car_Light_On();    //자동차 Flash On

void Car_Light_Off();   //자동차 Flash Off


