#ifndef TASK_DATA_H_
#define TASK_DATA_H_

#include <cmsis_os.h>
#include "stm32f1xx.h"
#include "string.h"


typedef struct{
	uint8_t Master_Card[5];
	uint8_t Slaver_Card[20][5];
	uint8_t Name_Slaver[20][5];
	uint8_t CardID[5];
}Data_Card_t;
typedef struct{
	uint8_t Pass_Home[7];
	uint8_t Pass_Change[7];
	uint8_t XacNhanLai[7];
	uint8_t Enter_Pass[7];
}Data_Pass_t;

typedef struct{
	char ID;
	uint8_t status;
	uint8_t count;
}Data_Node_Gate_Home_t;

typedef enum{
	Do_Not_Card = 0,
	Slave_Card,
	Master_Card,
}CardID_State_t;

typedef enum{
	Do_Nothing = 0,
	AddSlaveCard,
	RemoveSlaveCard,
	CreatPass,
	ChangePass
}MasterCard_State_t;



#endif
