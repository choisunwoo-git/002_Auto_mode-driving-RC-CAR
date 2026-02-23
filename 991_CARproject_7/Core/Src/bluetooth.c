/*
 * bluetooth.c
 *
 *  Created on: Oct 28, 2025
 *      Author: user13
 *
 *      Car light       자동차 플래시
 *      Car noise       자동차 경적
 */


#include "bluetooth.h"


uint8_t serial_RxData;
uint8_t go = 0;                 //전진 변수
uint8_t back = 0;               //후진 변수
uint8_t right = 0;              //우회전 변수
uint8_t left = 0;               //좌회전 변수
uint8_t stop = 0;               // 정지 변수
uint8_t speedInit = 0;          //속도 기본 변수
uint16_t original_speed = 0;
//===================================================================
//수정
//uint8_t speedUp = 0;            // 속도 상승 변수
//uint8_t speedDown = 0;          // 속도 저하 변수


uint8_t CarLightOn = 0;
uint8_t CarLightOff = 0;
int Motor_speed = 7;            //스피드 값 받을 변수
int Motor_speed_base = 350;
int num;
uint8_t AutoMode_Flag = 0;      //자동모드

//===================================================================

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //USART데이터 블루투스 1의 대한 데이터 인터럽트
{
   if(huart->Instance == USART1)   //USART1의 데이터 값 블루투스 huart값과 비교
   {
//	   HAL_UART_Receive_IT(&huart1, &serial_RxData, 1);        //인터럽트 받을준비됨huart1 저당메모리 주소


//	HAL_UART_Transmit (&huart1, &serial_RxData, 1, 1000);   //huart1 데이터 전송


        HAL_UART_Transmit_IT(&huart2, &serial_RxData, 1);
	//serial_RxData 휴대폰 받은 데이터 를 받으면

	if(serial_RxData == 'F'||
		 serial_RxData == 'B'||
		 serial_RxData == 'R'||
		 serial_RxData == 'L'||
		 serial_RxData == 'S'||
		 serial_RxData == 'Y'|| //자동모드
		 serial_RxData == 'X'||
		 serial_RxData == 'x'||
		 serial_RxData == '0'||
		 serial_RxData == '1'||
		 serial_RxData == '2'||
		 serial_RxData == '3'||
		 serial_RxData == '4'||
		 serial_RxData == '5'||
		 serial_RxData == '6'||
		 serial_RxData == '7'||
		 serial_RxData == '8'||
		 serial_RxData == '9')        //수정
	{

//=======================================================================
           if(serial_RxData == '0'||
                 serial_RxData == '1'||
                 serial_RxData == '2'||
                 serial_RxData == '3'||
                 serial_RxData == '4'||
                 serial_RxData == '5'||
                 serial_RxData == '6'||
                 serial_RxData == '7'||
                 serial_RxData == '8'||
                 serial_RxData == '9')
           {
              if (serial_RxData >= '0' && serial_RxData <= '9')
              {
                 num = serial_RxData - '0';
                 if(num >= 0 && num <= 9)
                 {
                    Motor_speed_base = 350;
                    Motor_speed = Motor_speed_base + ((num) * 50);
                    motor_speed();
                    original_speed = Motor_speed;
                 }


              }
           }

//=============================================================================

           switch(serial_RxData)
           {
                  case 'F' :               //전진
			go = 1;
			back = 0;
			right = 0;
			left = 0;
			stop = 0;
			break;
                  case 'B' :               //후진
			go = 0;
			back = 1;
			right = 0;
			left = 0;
			stop = 0;
			break;
	          case 'R' :              //오른쪽회전
			go = 0;
			back = 0;
			right = 1;
			left = 0;
			stop = 0;
			break;
	          case 'L' :              //좌측 회전
			go = 0;
			back = 0;
			right = 0;
			left = 1;
			stop = 0;
			break;
                  case 'S' :               //정지
			go = 0;
			back = 0;
			right = 0;
			left = 0;
			stop = 1;
			break;

                  case 'Y' :              //자동차 부저 SOUND//자동모드로 변경
                     if(AutoMode_Flag == 0)
                     {
                        AutoMode_Flag =1;
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);

                        go = 0;
                        back = 0;
                        right = 0;
                        left = 0;
                        stop = 1;
                     }
                     else if(AutoMode_Flag ==1)
                     {
                        AutoMode_Flag =0;
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);

                        go = 0;
                        back = 0;
                        right = 0;
                        left = 0;
                        stop = 1;
                     }
			break;
	          case 'X' :              //자동차 후래쉬 ON
			CarLightOn = 1;
			CarLightOff = 0;
			break;
	          case 'x' :              //자동차 후래쉬 OFF
	                CarLightOff = 1;
			CarLightOn = 0;
			break;

			default:
			break;
	   }HAL_UART_Receive_DMA(&huart1, &serial_RxData, 1);
	}
   }
   if(huart->Instance == USART2)   //USART1의 데이터 값 블루투스 huart값과 비교
   {
   //         HAL_UART_Receive_IT(&huart1, &serial_RxData, 1);        //인터럽트 받을준비됨huart1 저당메모리 주소


   //      HAL_UART_Transmit (&huart1, &serial_RxData, 1, 1000);   //huart1 데이터 전송


           HAL_UART_Transmit_IT(&huart2, &serial_RxData, 1);
           //serial_RxData 휴대폰 받은 데이터 를 받으면

           if(serial_RxData == 'F'||
                    serial_RxData == 'B'||
                    serial_RxData == 'R'||
                    serial_RxData == 'L'||
                    serial_RxData == 'S'||
                    serial_RxData == 'Y'||      //자동모드
                    serial_RxData == 'X'||
                    serial_RxData == 'x'||
                    serial_RxData == '0'||
                    serial_RxData == '1'||
                    serial_RxData == '2'||
                    serial_RxData == '3'||
                    serial_RxData == '4'||
                    serial_RxData == '5'||
                    serial_RxData == '6'||
                    serial_RxData == '7'||
                    serial_RxData == '8'||
                    serial_RxData == '9')        //수정
           {

//=============================================================================
              if(serial_RxData == '0'||
                    serial_RxData == '1'||
                    serial_RxData == '2'||
                    serial_RxData == '3'||
                    serial_RxData == '4'||
                    serial_RxData == '5'||
                    serial_RxData == '6'||
                    serial_RxData == '7'||
                    serial_RxData == '8'||
                    serial_RxData == '9')
              {
                 if (serial_RxData >= '0' && serial_RxData <= '9')
                 {
                    num = serial_RxData - '0';
                    if(num >= 1 && num <= 9)
                    {
                       Motor_speed_base = 350;
                       Motor_speed = Motor_speed_base + ((num) * 50);
                       motor_speed();
                    }


                 }
              }
//=============================================================================

              switch(serial_RxData)
              {
                     case 'F' :               //전진
                           go = 1;
                           back = 0;
                           right = 0;
                           left = 0;
                           stop = 0;
                           break;
                     case 'B' :               //후진
                           go = 0;
                           back = 1;
                           right = 0;
                           left = 0;
                           stop = 0;
                           break;
                     case 'R' :              //오른쪽회전
                           go = 0;
                           back = 0;
                           right = 1;
                           left = 0;
                           stop = 0;
                           break;
                     case 'L' :              //좌측 회전
                           go = 0;
                           back = 0;
                           right = 0;
                           left = 1;
                           stop = 0;
                           break;
                     case 'S' :               //정지
                           go = 0;
                           back = 0;
                           right = 0;
                           left = 0;
                           stop = 1;
                           break;
                           //추가기능
                     case 'Y' :              //자동차 부저 SOUND //자동모드로 변경
                        if(AutoMode_Flag == 0)
                        {
                           AutoMode_Flag =1;
                           HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);

                           go = 0;
                           back = 0;
                           right = 0;
                           left = 0;
                           stop = 1;
                        }
                        else if(AutoMode_Flag ==1)
                        {
                           AutoMode_Flag =0;
                           HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);

                           go = 0;
                           back = 0;
                           right = 0;
                           left = 0;
                           stop = 1;

                        }
                           break;
                     case 'X' :              //자동차 후래쉬 ON
                           CarLightOn = 1;
                           CarLightOff = 0;
                           break;
                     case 'x' :              //자동차 후래쉬 OFF
                           CarLightOff = 1;
                           CarLightOn = 0;
                           break;

                           default:
                           break;
              }HAL_UART_Receive_IT(&huart2, &serial_RxData, 1);
           }
   }
}



void bluetoothControl() //ap.c 파일 역할 현재 bluetoothControl 중심으로 데이터 처리
{
  MX_USART1_UART_Init();        //USART1 기본설정

  motor_init();                 //모터 기본설정

  Car_Light_Init();             //자동차 LIGHT 초기값
  motor_speedInit();            //속도

  HAL_TIM_Base_Start_IT(&htim11);               // for delat_us() Function
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);

  //=============================================
  //2채널
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
  //3채널
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
  //====================================================

  MX_TIM2_Init();
  MX_TIM11_Init();
  HAL_UART_Receive_DMA(&huart1, &serial_RxData, 1);     //huart1   받은데이터 인터럽트 serial_RxData의 받을준비
  HAL_UART_Receive_IT(&huart2, &serial_RxData, 1);
  while(1)
  {
  	pwm_sweep_test();       // PWM속도 시리얼로 출력        PC화면에 출력

//  	HCSR04_TRIGGER();
//  	HCSR04_TRIGGER2();
//  	HCSR04_TRIGGER3();
//
//  	     printf("Distance1 : %d cm\n", distance);
//  	     //============================================
//  	     //2채널
//  	     printf("Distance2 : %d cm\n", distance2);
//  	     //3채널
//  	     printf("Distance3 : %d cm\n", distance3);
//  	     //============================================
//  	     HAL_Delay(50);
//  	     HAL_Delay(500);

  	//모터 속도 제어 플래그 추가 해서 적용


  	if(AutoMode_Flag == 0)
  	{
  	   HCSR04_TRIGGER();
  	   HCSR04_TRIGGER2();
  	   HCSR04_TRIGGER3();
  	   printf("Right : %d cm\n", distance_Right);
  	   printf("Front : %d cm\n", distance2_Front);
  	   printf("Left : %d cm\n", distance3_Left);
  	}
  	else if(AutoMode_Flag == 1)
  	{
  	     AutoMode();

  	}

  	if(go)
  	{
  	         AutoMode_motor_go();     //모터전진
  	}

  	else if(back)
  	{
  	         AutoMode_motor_back();   //모터 후진
  	}

  	else if(right)
  	{
  	         AutoMode_motor_right();  // 우회전
  	}

  	else if(left)
  	{
  	         AutoMode_motor_left();   //모터 좌회전
  	}

  	else if(stop)
  	{
  	         AutoMode_motor_stop();   //모터 정지
  	}

        else if(CarLightOn)
        {
                Car_Light_On();      //자동차 앞 LIGHT_ON
                CarLightOff = 0;
        }
        else if(CarLightOff)
        {
                Car_Light_Off();      //자동차 앞 LIGHT_OFF
                CarLightOn = 0;
        }

  	//===========================================================

  }
}

