#include "TASK_DATA.h"
#include "LCD20X4.h"

extern osMessageQId xQueueDataTaskCradSendCardID_State_tHandle;
extern osMessageQId xQueueDataTaskCardSendMasterCard_State_tHandle;

void TaskLCD(void const* argument)
{
	static Data_Card_t DataCardSendLCD;
	static CardID_State_t CardID_Status;
	static MasterCard_State_t MasterState;
	static uint8_t keyLCD;
	for(;;)
	{
		//Data Card
		if(xQueueReceive(xQueueDataTaskCradSendCardID_State_tHandle,&CardID_Status,portMAX_DELAY) == pdPASS)
		{
			if(CardID_Status == Master_Card)
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
		if(xQueueReceive(xQueueDataTaskCardSendMasterCard_State_tHandle, &MasterState, portMAX_DELAY) == pdPASS)
		{
			if( MasterState == AddRemoveSlaveCard)
			{
				
			}
			if( MasterState == CreatChangPass)
			{
				
			}
		}
	}
}
