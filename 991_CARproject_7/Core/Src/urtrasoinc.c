#include "urtrasoinc.h"



static uint8_t trigger_state = 0;
//트리거

//=========================================
uint16_t IC_Value1 = 0;
uint16_t IC_Value2 = 0;
uint16_t echoTime = 0;
uint8_t captureFlag = 0;
uint8_t distance_Right = 0;

//==========================================
//2채널
uint16_t IC_2Value1 = 0;
uint16_t IC_2Value2 = 0;
uint16_t echo2Time = 0;
uint8_t capture2Flag = 0;
uint8_t distance2_Front = 0;

//3채널
uint16_t IC_3Value1 = 0;
uint16_t IC_3Value2 = 0;
uint16_t echo3Time = 0;
uint8_t capture3Flag = 0;
uint8_t distance3_Left = 0;

//==========================================

int _write(int file, unsigned char* p, int len)
{
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, p, len, 100); //시리얼 통신 전달
    return (status == HAL_OK ? len : 0);
}



void HCSR04_TRIGGER(void)//수동적인 에
{
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0);
   delay_us(1);        //1ms
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);
   delay_us(10);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0);

   __HAL_TIM_ENABLE_IT(&htim2,TIM_IT_CC1 );     //인터럽트 켜기

}

//===============================================
//2채널
void HCSR04_TRIGGER2()//수동적인 에
{
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
   delay_us(1);         //1ms
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 1);
   delay_us(10);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);

   __HAL_TIM_ENABLE_IT(&htim2,TIM_IT_CC2 );

}

//3채널
void HCSR04_TRIGGER3()//수동적인 에
{
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);
   delay_us(1);         //1ms
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);
   delay_us(10);
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);

   __HAL_TIM_ENABLE_IT(&htim2,TIM_IT_CC3 );     //인터럽트 켜기

}
//===============================================


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
   if(htim -> Channel == HAL_TIM_ACTIVE_CHANNEL_1)
   {
      if(captureFlag == 0)      //아직 캡처를 안했다면
      {
         IC_Value1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
         captureFlag = 1;       //캡쳐 플래그 세움 (캡쳐 했음)
         __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING); //매크로 캡쳐
      }
      else if(captureFlag ==1)
      {
         IC_Value2 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
         __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);

         if(IC_Value2 > IC_Value1)
         {
            echoTime = IC_Value2 - IC_Value1;
         }
         else if(IC_Value2 < IC_Value1)
         {
            echoTime = (0xffff - IC_Value1) + IC_Value2; //0xffff = ff -> 8bit
         }
         distance_Right = echoTime /58;
         captureFlag = 0;
         __HAL_TIM_DISABLE_IT(&htim2,TIM_IT_CC1 );//인터럽트 끈다.
      }
   }

   //============================================================================================
   //2채널
   else if(htim -> Channel == HAL_TIM_ACTIVE_CHANNEL_2)
   {
      if(capture2Flag == 0)      //아직 캡처를 안했다면
      {
         IC_2Value1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
         capture2Flag = 1;       //캡쳐 플래그 세움 (캡쳐 했음)
         __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING); //매크로 캡쳐
      }
      else if(capture2Flag ==1)
      {
         IC_2Value2 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
         __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);

         if(IC_2Value2 > IC_2Value1)
         {
            echo2Time = IC_2Value2 - IC_2Value1;
         }
         else if(IC_2Value2 < IC_2Value1)
         {
            echo2Time = (0xffff - IC_2Value1) + IC_2Value2; //0xffff = ff -> 8bit
         }
         distance2_Front = echo2Time /58;
         capture2Flag = 0;
         __HAL_TIM_DISABLE_IT(&htim2,TIM_IT_CC2 );//인터럽트 끈다.
      }
   }

   //3채널
   else if(htim -> Channel == HAL_TIM_ACTIVE_CHANNEL_3)
   {
      if(capture3Flag == 0)      //아직 캡처를 안했다면
      {
         IC_3Value1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_3);
         capture3Flag = 1;       //캡쳐 플래그 세움 (캡쳐 했음)
         __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING); //매크로 캡쳐
      }
      else if(capture3Flag ==1)
      {
         IC_3Value2 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_3);
         __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);

         if(IC_3Value2 > IC_3Value1)
         {
            echo3Time = IC_3Value2 - IC_3Value1;
         }
         else if(IC_3Value2 < IC_3Value1)
         {
            echo3Time = (0xffff - IC_3Value1) + IC_3Value2; //0xffff = ff -> 8bit
         }
         distance3_Left = echo3Time /58;
         capture3Flag = 0;
         __HAL_TIM_DISABLE_IT(&htim2,TIM_IT_CC3 );//인터럽트 끈다.
      }
   }
   //============================================================================================
}

