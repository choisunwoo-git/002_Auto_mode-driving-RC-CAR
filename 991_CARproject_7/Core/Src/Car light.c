

#include "Car light.h"



void Car_Light_Init()
{
   HAL_GPIO_WritePin(CAR_LIGHT_PORT, CAR_LIGHT_PIN, 0);
}

void Car_Light_On()
{
   HAL_GPIO_WritePin(CAR_LIGHT_PORT, CAR_LIGHT_PIN, 1);
}

void Car_Light_Off()
{
   HAL_GPIO_WritePin(CAR_LIGHT_PORT, CAR_LIGHT_PIN, 0);
}
