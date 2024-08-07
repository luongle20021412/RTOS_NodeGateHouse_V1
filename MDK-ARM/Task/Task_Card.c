#include "TASK_DATA.h"
#include "RFID_RCC522.h"

extern osMessageQId xQueueDataTaskCardSendData_Card_tHandle;
extern osMessageQId xQueueDataTaskCardSendMasterCard_State_tHandle;
extern osMessageQId xQueueDataTaskCradSendCardID_State_tHandle;
uint32_t lastDelay = 0;

void TaskCard(void const* argument)
{
	uint8_t ID[5] = {0xE3, 0x9B, 0x33, 0x25, 0x6E};
	static Data_Card_t DataCard;
	static CardID_State_t State_Card = Do_Not_Card;
	static Data_Node_Gate_Home_t Gate;
	static MasterCard_State_t MasterState = Do_Nothing;
	static uint8_t countAddRemove, TimeOutAddRemo;
	memcpy(DataCard.Master_Card, ID, sizeof ID);
	
	for(;;)
	{
		xQueueReceive(xQueueDataTaskCardSendMasterCard_State_tHandle, &MasterState, portMAX_DELAY);
		if( MasterState == Do_Nothing)
		{
			if(MFRC522_Check(DataCard.CardID) == MI_OK)
			{
				if(DataCard.CardID[0] == DataCard.Master_Card[0] && DataCard.CardID[1] == DataCard.Master_Card[1] && DataCard.CardID[2] == DataCard.Master_Card[2] && DataCard.CardID[3] == DataCard.Master_Card[3] && DataCard.CardID[4] == DataCard.Master_Card[4])
				{
					State_Card = Master_Card;
					if((uint32_t)(HAL_GetTick() - lastDelay) > 1000)
					{
						countAddRemove++;
						if(countAddRemove >= 10)
						{
							MasterState = AddRemoveSlaveCard;
							xQueueSend(xQueueDataTaskCardSendMasterCard_State_tHandle,&MasterState, portMAX_DELAY);
						}
						lastDelay = HAL_GetTick();
					}
				}
				else
				{
					for(uint8_t  i = 0; i < 20; i++)
					{
						if(DataCard.CardID[0] == DataCard.Slaver_Card[i][0] && DataCard.CardID[1] == DataCard.Slaver_Card[i][1] && DataCard.CardID[2] == DataCard.Slaver_Card[i][2] && DataCard.CardID[3] == DataCard.Slaver_Card[i][3] && DataCard.CardID[4] == DataCard.Slaver_Card[i][4])
						{
							State_Card = Slave_Card;
							break;
						}
					}
					if(State_Card != Slave_Card) State_Card = Wrong_Card;
				}
				if(State_Card == Master_Card || State_Card == Slave_Card)
				{
					Gate.status++;
					if(Gate.status > 4) Gate.status = 1;
				}
			}
			else
			{
				State_Card = Do_Not_Card;
			}
		}
		else
		{
			//sau 10s khong co card tu dong thoai khoi trang thai add and remove
			MFRC522_Check(DataCard.CardID);
			xQueueSend(xQueueDataTaskCardSendData_Card_tHandle,&DataCard, portMAX_DELAY);
			if(MFRC522_Check(DataCard.CardID) == MI_ERR)
			{
				if((uint32_t)(HAL_GetTick() - lastDelay) > 1000)
				{
					TimeOutAddRemo++;
					lastDelay = HAL_GetTick();
				}
			}
			if(TimeOutAddRemo == 10)
			{
				MasterState = Do_Nothing;
				TimeOutAddRemo = 0;
				xQueueSend(xQueueDataTaskCardSendMasterCard_State_tHandle, &MasterState, portMAX_DELAY);
			}
			else if(TimeOutAddRemo != 10)
			{
				TimeOutAddRemo = 0;
			}
		}
		xQueueSend(xQueueDataTaskCradSendCardID_State_tHandle, &State_Card, portMAX_DELAY);
	}

}
