

/**
 * TIM, PWM의 제어를 통해 속도를 제어
 *
 */

#include "main.h"
#include "speed.h"
#include "bluetooth.h"

extern int Motor_speed;


void motor_speedInit()  //초기값  수정
{
	TIM3 -> CCR1 = 340; // 70% duty
	TIM3 -> CCR2 = 340;
}

//===================================================================================================

//void motor_speedUp()    //하나로 통일, 변수로 값을 지정
//{
//	TIM3 -> CCR1 = 900; // 90% duty
//}
//
//void motor_speedDown()
//{
//	TIM3 -> CCR1 = 500; // 50% duty
//}

//========================================================


void motor_speed()
{
   TIM3 -> CCR1  = Motor_speed;
   TIM3 -> CCR2  = Motor_speed;
}

//===================================================================================================

void pwm_sweep_test()
{
   printf("CCR1=%lu\r\n", TIM3 -> CCR1);
   printf("CCR2=%lu\r\n", TIM3 -> CCR2);

   //확인용 딜레이 나중에 지우기
//   HAL_Delay(1);
   //논 블로킹 딜레이 추가
   //딜레이제거


}
