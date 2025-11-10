

#ifndef INC_URTRASOINC_H_
#define INC_URTRASOINC_H_



#endif /* INC_URTRASOINC_H_ */


#include "main.h"
#include "bluetooth.h"
#include "delay_us.h"

extern  uint8_t distance_Right;

//====================================================
//2채널
extern  uint8_t distance2_Front;

//3채널
extern  uint8_t distance3_Left;

//======================================================



void HCSR04_TRIGGER(void);

//===================================
//2채널
void HCSR04_TRIGGER2(void);

//3채널
void HCSR04_TRIGGER3(void);

//======================================
