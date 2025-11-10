#include "AutoMode.h"

//============================================================
#define MIN_SPEED   350         // 최소속도
#define MAX_SPEED   700        // 최대속도
#define BASE_SPEED  500         // 기본속도 500  성공 70%
#define FRONT_SAFE  50          // 직진 유지 거리 60 -> 40
#define FRONT_STOP  28          // 회전 시작 거리     22 ->28성공 70%           28 -> 27 테스트 블로킹 제거 -> 28

/*
 * 첫번쨰 구간문제점 발생 정면이동시 중간구간 FRONT_SAFE > 현재 정면거리 > FRONT_STOP 두번째 로직에서 문제발생
 * 회전  구간시 도는 방샹과 반대의 위치한 벽과 가까운 부분의 센서의 경우 속도가 빠른 것과 비례하여 거리가 매우 근접할경우 인식이 됨
 *첫번째 구간에서 벽과 가까울경우 가아제 회전 PWM을 지정 회전시 정면 센서의 경우 회전구간을 빠져 나올시 회전중 각도의 꺽임의 비례해
 *정면 거리 측정이 값자기 매우 길어짐 그로인한 벽면을 글으면서 이동을 함
 *특정 조건하의 플래그를 추가
 *특정 기존의 기능 정면으로 이동하며 중앙의 위치를 잡고 정면이동을 구현
 *거리가 가까워 질경우 강제 회전 회전시 정면센서의 측정 거리가 매우 멀어져 정면이동 구형화됨
 *이로인한 문제점 로직으로 구현해야함
 *새로운 조건필요
 *
 */

//좌우 근접거리 추가
#define RIGHT_dangerous_distance 9
#define LEFT_dangerous_distance 9
//#define SIDE_WALL   10

#define  diff_MAX  8


void AutoMode()
{
    HCSR04_TRIGGER();
    HCSR04_TRIGGER2();
    HCSR04_TRIGGER3();

    printf("Right : %d cm\n", distance_Right);
    printf("Front : %d cm\n", distance2_Front);
    printf("Left  : %d cm\n", distance3_Left);

    if (AutoMode_Flag == 1)
    {
        int space_diffrnrent = 0;
        int PWM_Front_Speed = 0;
        int diff = 0;    //변수 서로간의 차이
        int PWM_offset = 0;     //PWM_offset PWM서로간의 차이
        uint8_t moveFlag_L = 2;
        uint8_t moveFlag_R = 2;

        go = left = right = back = stop = 0;
        go = 1;
        uint16_t left_speed  = BASE_SPEED;
        uint16_t right_speed = BASE_SPEED;

        if(distance2_Front > FRONT_SAFE )
        {
           go = 1;
           left = 0;
           right =0;
           back = 0;
           stop = 0;
           //거리가 멀시 직진하면서 양쪽 거리의 차이만큼 양옆의 모터의 속도를 차이를 줌
           left_speed  = BASE_SPEED;
           right_speed = BASE_SPEED;

           space_diffrnrent = distance3_Left - distance_Right;

           diff = abs(distance3_Left - distance_Right); //절대값
           if(diff > diff_MAX)  //범위제한
           {
              diff = diff_MAX;
           }

           if(space_diffrnrent >  diff_MAX)        ///거리차이가 클경우 강제로 최대치 규정
           {
              //왼쪽 공간 클시
              space_diffrnrent = diff_MAX;  //최대차이 10으로 조정
           }
           else if(space_diffrnrent <  -diff_MAX)  //오른쪽 공간 -영역
           {
              //오른쪽 공간 클시
              space_diffrnrent = -diff_MAX;
           }

//           moveFlag_L = 0;
//           moveFlag_R = 1;

           if(space_diffrnrent > 0)     //공간값 +영역일경우 왼쪽 공간이 더 넓음
           {
              moveFlag_L = 1;
              moveFlag_R = 0;
           }
           else                         //공간값 - 영역 오른쪽 공간이 더 넓음
           {
              moveFlag_R = 1;
              moveFlag_L = 0;
           }
           PWM_offset = 5;     //PWM_offset, PWM 듀티비 조정 양쪽차이 최대 100, 5 -> 7 - >12 -> 20 -> 10 -> 20-> 8 ->

           if(moveFlag_L == 1)   //왼쪽 공간이 더 넓음, 오른쪽 으로 회전
           {
              left_speed += diff * PWM_offset;
              right_speed -= diff * PWM_offset;
           }
           else if(moveFlag_R == 1)      //오른쪽 공간이 더 넓음, 왼쪽 으로 회전
           {
              left_speed -= diff * PWM_offset;
              right_speed += diff * PWM_offset;
           }

           if(distance3_Left < LEFT_dangerous_distance)         //왼쪽 공간이 없을시 오른쪽 으로 회전 로직을 추가
           {
           go = 0;
           left = 0;
           right =1;
           back = 0;
           stop = 0;

           left_speed  = 450;           //  620테스트 -> 600 -> 550 -> 500 -> 450
           right_speed = 350;           //  350테스트

           }
           else if(distance_Right < RIGHT_dangerous_distance)   //오른쪽 공간이 없을시 왼쪽 으로 회전 로직을 추가
           {
           go = 0;
           left = 1;
           right =0;
           back = 0;
           stop = 0;

           left_speed  = 350;           //  350테스트
           right_speed = 450;           //  620테스트 -> 600 -> 550 -> 500 -> 450

           }


        }
        // 중간구간 벽이랑 가까워질수록 속도 저하 구현
        else if(FRONT_SAFE >= distance2_Front && distance2_Front >= FRONT_STOP) //최대 > 현재 > 최소
        {
           go = 1;
           left = 0;
           right =0;
           back = 0;
           stop = 0;
           //일정구간구역 속도감소
           //양 옆의 길이차이 만큼 양쪽 속도 유연하게 제어

           left_speed  = BASE_SPEED;    //추가 2025118, 속도 360 고정 문제 있을수 있음
           right_speed = BASE_SPEED;    //추가 2025118, 속도 360 고정 문제 있을수 있음

           diff = distance3_Left - distance_Right;

           //PWM_Front_Speed 값이 0 ~ 1이 나와야함
           //범위 ->  (60 ~ 20) - 20 / 60 - 20
           float PWM_Front_Speed =  (float)(distance2_Front - FRONT_STOP) / (FRONT_SAFE - FRONT_STOP);

           if(PWM_Front_Speed < 0.36f) PWM_Front_Speed = 0.36f;
           left_speed  = left_speed * PWM_Front_Speed;
           right_speed = right_speed * PWM_Front_Speed;

           diff = abs(distance3_Left - distance_Right); //절대값
           if(diff > diff_MAX)  //범위제한
           {
              diff = diff_MAX;
           }

           if(space_diffrnrent >  diff_MAX)        ///거리차이가 클경우 강제로 최대치 규정
           {
              //왼쪽 공간 클시
              space_diffrnrent = diff_MAX;  //최대차이 10으로 조정
           }
           else if(space_diffrnrent <  -diff_MAX)  //오른쪽 공간 -영역
           {
              //오른쪽 공간 클시
              space_diffrnrent = -diff_MAX;
           }

//           moveFlag_L = 0;
//           moveFlag_R = 1;

           if(space_diffrnrent > 0)     //공간값 +영역일경우 왼쪽 공간이 더 넓음
           {
              moveFlag_L = 1;
              moveFlag_R = 0;
           }
           else                         //공간값 - 영역 오른쪽 공간이 더 넓음
           {
              moveFlag_R = 1;
              moveFlag_L = 0;
           }
           PWM_offset = 9;     //PWM_offset, PWM 듀티비 조정 양쪽차이 최대 100, 5 -> 7 - >12 -> 20 -> 15 -> 10 ->15 -> 8

           if(moveFlag_L == 1)   //왼쪽 공간이 더 넓음, 오른쪽 으로 회전
           {
              left_speed += diff * PWM_offset;
              right_speed -= diff * PWM_offset;
           }
           else if(moveFlag_R == 1)      //오른쪽 공간이 더 넓음, 왼쪽 으로 회전
           {
              left_speed -= diff * PWM_offset;
              right_speed += diff * PWM_offset;
           }


        }
        else if(FRONT_STOP > distance2_Front)   //강제 회전구간
        {
           go = 0;
           left = 0;
           right =0;
           back = 0;
           stop = 0;

           diff = distance3_Left - distance_Right;

           if(diff_MAX <=  diff)        ///거리차이가 클경우 강제로 최대치 규정
           {
              go = 0;
              left = 1;
              right =0;
              back = 0;
              stop = 0;

                 //왼쪽 공간 클시
             diff = diff_MAX;  //최대차이 10으로 조정
             left_speed  = 360;
             right_speed = 500;         // 수정 600 -> 620/ 새배터리 교체 힘 증가로 값 조정 590 -> 550 -> 500
           }
           else if(-diff_MAX >=  diff)  //오른쪽 공간 -영역
           {
             go = 0;
             left = 0;
             right =1;
             back = 0;
             stop = 0;

                 //오른쪽 공간 클시
             diff = -diff_MAX;
             left_speed  = 500;         // 수정 600 -> 620/ 새배터리 교체 힘 증가로 값 조정 590 -> 550 -> 500
             right_speed = 360;

           }


        }
        //=========================================================================================


        //=====================================================
        // ④ 속도 제한 (보정)
      //좌측 우측의 값의 최대 최소 값이 일정 범위를 넘을시 제한범위 지정
        //=====================================================
        if (left_speed < MIN_SPEED)  left_speed = MIN_SPEED;
        if (right_speed < MIN_SPEED) right_speed = MIN_SPEED;
        if (left_speed > MAX_SPEED)  left_speed = MAX_SPEED;
        if (right_speed > MAX_SPEED) right_speed = MAX_SPEED;

        TIM3->CCR1 = left_speed;
        TIM3->CCR2 = right_speed;
    }
}
