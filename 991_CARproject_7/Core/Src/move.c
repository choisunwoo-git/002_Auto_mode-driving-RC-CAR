


/**
 * 동작제어코드
 * HIGH, LOW을 통해
 * DC모터의 극성을 제어
 */

#include "move.h"

//자동모드 제어


   void AutoMode_motor_init()       //초기값 설정
   {
           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 0);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 0);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);
   }

   void AutoMode_motor_go()         //모터 전진
   {
           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 1);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 1);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);
   }

   void AutoMode_motor_back()       //모터 후진
   {
           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 0);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 1);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 0);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 1);
   }

   void AutoMode_motor_right()      //자동차 자체 우회전
   {

         HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 1);
         HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
         HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 0);
         HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 1);


   }

   void AutoMode_motor_left()       //자동차 자체 좌회전
   {

           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 0);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 1);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 1);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);

   }

   void AutoMode_motor_stop()       //전원x
   {
           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 0);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 0);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);
   }


//===============================================================
//블루투스 모드 제어

   void motor_init()       //초기값 설정
   {
           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 0);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 0);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);
   }

   void motor_go()         //모터 전진
   {
           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 1);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 1);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);
   }

   void motor_back()       //모터 후진
   {
           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 0);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 1);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 0);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 1);
   }

   void motor_right()      //자동차 자체 우회전
   {

         HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 1);
         HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
         HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 0);
         HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 1);


   }

   void motor_left()       //자동차 자체 좌회전
   {

           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 0);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 1);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 1);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);

   }

   void motor_stop()       //전원x
   {
           HAL_GPIO_WritePin(IN1_GPIO_PORT, IN1_PIN, 0);
           HAL_GPIO_WritePin(IN2_GPIO_PORT, IN2_PIN, 0);
           HAL_GPIO_WritePin(IN3_GPIO_PORT, IN3_PIN, 0);
           HAL_GPIO_WritePin(IN4_GPIO_PORT, IN4_PIN, 0);
   }

