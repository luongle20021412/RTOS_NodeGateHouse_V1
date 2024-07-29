#include <TASK_DATA.h>
#include "LCD20X4.h"

extern osMessageQId xQueueSendDataLCD;


void TaskLCD(void *argument)
{
	static Data_Card_t DataCardSendLCD;
	static CardID_State_t CardID_Status;
	static uint8_t keyLCD;
	for(;;)
	{
		//Data Card
		if(xQueueReceive(xQueueSendDataLCD,&DataCardSendLCD,portMAX_DELAY) == pdPASS)
		{
			if(DataCardSendLCD.CardID[0] == DataCardSendLCD.Master_Card[0] && DataCardSendLCD.CardID[1] == DataCardSendLCD.Master_Card[1] && DataCardSendLCD.CardID[2] == DataCardSendLCD.Master_Card[2] && DataCardSendLCD.CardID[3] == DataCardSendLCD.Master_Card[3] && DataCardSendLCD.CardID[4] == DataCardSendLCD.Master_Card[4])
			{
				LCD20X4_Gotoxy(0,2);
				LCD20X4_PutString("Card MAster");
			}
			else
			{
				LCD20X4_Gotoxy(1,2);
				LCD20X4_PutString("Card slaver");
			}
		}
	}
}
