#ifndef TASK_DATA_H_
#define TASK_DATA_H_

#include <cmsis_os.h>
#include "stm32f1xx.h"
#include "string.h"
#include "Flash.h"

typedef struct{
	uint8_t CardID[5];
	uint8_t Master_Card[5];
	uint8_t Slaver_Card[20][5];
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
	Wrong_Card,
}CardID_State_t;

typedef enum{
	Do_Nothing = 0,
	AddRemoveSlaveCard,
	CreatChangPass,
}MasterCard_State_t;

typedef enum{
	Page1 = 0,
	Page2,
	Page3
}Page_t;
#define MAX_Slave_Card 	20
#define SIZE_PAGE 2048
#define Address_NodeGate 0x1122334400
//Define PIN PORT SPI, RFID
#define SPI1_CS_PIN	GPIO_PIN_1
#define SPI1_CE_PIN	GPIO_PIN_0
#define SPI1_Port		GPIOB

#define CS_RFID_Pin GPIO_PIN_4
#define CS_RFID_GPIO_Port GPIOA

// Define PIN PORT STEPMOTOR
#define DIR_Motor		 	GPIO_PIN_7
#define ENABLE_Motor	GPIO_PIN_8	
#define Step_Motor			GPIO_PIN_6
#define Motor_Port			GPIOB

// Define PIN PORY KEYPAD 4x4
#define ROW_PORT		GPIOC
#define ROW_PORT_B	GPIOB
#define ROW_1_Pin		GPIO_PIN_15
#define ROW_2_Pin		GPIO_PIN_14
#define ROW_3_Pin		GPIO_PIN_9
#define ROW_4_Pin		GPIO_PIN_10

#define COL_PORT		GPIOA
#define COL_1_Pin		GPIO_PIN_3
#define COL_2_Pin		GPIO_PIN_2
#define COL_3_Pin		GPIO_PIN_1
#define COL_4_Pin		GPIO_PIN_0

#endif
