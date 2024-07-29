#include <TASK_DATA.h>
#include "RFID_RCC522.h"
#include "main.h"

extern osMessageQId  xQueueSendDataLCD;

void TaskCard(void *argument)
{
	uint8_t ID[5] = {0xE3, 0x9B, 0x33, 0x25, 0x6E};
	static Data_Card_t DataCard;
	CardID_State_t State_Card = Do_Not_Card;
	memcpy(DataCard.Master_Card, ID, sizeof ID);
	
	for(;;)
	{
		if(MFRC522_Check(DataCard.CardID) == MI_OK)
		{
			if(DataCard.CardID[0] == DataCard.Master_Card[0] && DataCard.CardID[1] == DataCard.Master_Card[1] && DataCard.CardID[2] == DataCard.Master_Card[2] && DataCard.CardID[3] == DataCard.Master_Card[3] && DataCard.CardID[4] == DataCard.Master_Card[4])
			{
				State_Card = Master_Card; 
			}
			else
			{
				State_Card = Slave_Card;
			}
		}
		else
		{
			State_Card = Do_Not_Card;
		}
	}

}
