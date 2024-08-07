#include <TASK_DATA.h>
//add and remove
extern osMessageQId xQueueDataTaskCardSendMasterCard_State_tHandle;
extern osMessageQId xQueueDataTaskCardSendData_Card_tHandle;

void TaskAdd(void const* argument)
{
	static MasterCard_State_t MasterState = Do_Nothing;
	static Data_Card_t CardAddRemove;
	static Page_t PageAddRemov = Page1;
	static _Bool RemovCard = 0;
	static uint8_t countAdd = 0, ucount = 0, ucountQuantityCard;
	static uint32_t lastDelay;
	for(;;)
	{
		xQueueReceive(xQueueDataTaskCardSendData_Card_tHandle, &CardAddRemove, portMAX_DELAY);
		if(xQueueReceive(xQueueDataTaskCardSendMasterCard_State_tHandle, &MasterState, portMAX_DELAY) == pdPASS)
		{
			if(MasterState == AddRemoveSlaveCard)
			{
				//check master card
				if(CardAddRemove.Master_Card[0] != CardAddRemove.CardID[0] && CardAddRemove.Master_Card[1] != CardAddRemove.CardID[1] && CardAddRemove.Master_Card[2] != CardAddRemove.CardID[2] && CardAddRemove.Master_Card[3] != CardAddRemove.CardID[3] && CardAddRemove.Master_Card[4] != CardAddRemove.CardID[4])
				{
					// check add and remove
					for(ucount = 0;  ucount< 20; ucount++)
					{
						if(CardAddRemove.Slaver_Card[ucount][0] == CardAddRemove.CardID[0] && CardAddRemove.Slaver_Card[ucount][1] == CardAddRemove.CardID[1] && CardAddRemove.Slaver_Card[ucount][2] == CardAddRemove.CardID[2] && CardAddRemove.Slaver_Card[ucount][3] == CardAddRemove.CardID[3] && CardAddRemove.Slaver_Card[ucount][4] == CardAddRemove.CardID[4])
						{
							RemovCard =! RemovCard;
							break;	
						}
						else
						{
							countAdd++;
						}
					}
				}
				if(RemovCard){
					memset(CardAddRemove.Slaver_Card[ucount], 0xFF, sizeof(CardAddRemove.Slaver_Card[ucount]));
					ucountQuantityCard--;
					MasterState = Do_Nothing;
					if(PageAddRemov == Page2)
					{
						PageAddRemov = Page1;
						Flash_Erase(Page_addres_1);
						Flash_Write_Array(Page_addres_1+ 2, (uint8_t *)CardAddRemove.Slaver_Card, 100);
						Flash_Erase(Page_addres_3);
						Flash_Write_Array(Page_addres_3 + 2,(uint8_t*)PageAddRemov, 1);
						Flash_Erase(Page_addres_2);
					}
					else
					{
						PageAddRemov = Page2;
						Flash_Erase(Page_addres_2);
						Flash_Write_Array(Page_addres_2 + 2, (uint8_t *)CardAddRemove.Slaver_Card, 100);
						Flash_Erase(Page_addres_3);
						Flash_Write_Array(Page_addres_3 + 2, (uint8_t *)PageAddRemov, 1);
						Flash_Erase(Page_addres_1);
					}
					Flash_Erase(Page_QuantitySlave);
					Flash_Write_Array(Page_QuantitySlave, &ucountQuantityCard, 2);
					xQueueSend(xQueueDataTaskCardSendMasterCard_State_tHandle,&MasterState,portMAX_DELAY);
					xQueueSend(xQueueDataTaskCardSendData_Card_tHandle, &CardAddRemove,portMAX_DELAY);
				}
				else if(countAdd == 20)
				{
					ucountQuantityCard++;
					MasterState = Do_Nothing;
					for(uint8_t i = 0; i < 20; i++)
					{
						if(CardAddRemove.Slaver_Card[i][0] == 0xFF && CardAddRemove.Slaver_Card[i][1] == 0xFF && CardAddRemove.Slaver_Card[i][2] == 0xFF&& CardAddRemove.Slaver_Card[i][3] == 0xFF && CardAddRemove.Slaver_Card[i][4] == 0xFF)
						{
							for(uint8_t j = 0; j < 5; j++)
							{
								CardAddRemove.Slaver_Card[i][j] = CardAddRemove.CardID[j];
							}
						}	
					}
					if(PageAddRemov == Page2)
					{
						Flash_Erase(Page_addres_2);
						Flash_Erase(Page_addres_3);
						Flash_Erase(Page_QuantitySlave);
						Flash_Write_Array(Page_addres_3 + 2, (uint8_t *)PageAddRemov, 1);
						Flash_Write_Array(Page_addres_2 + 2, (uint8_t *)CardAddRemove.Slaver_Card, 100);
						Flash_Write_Array(Page_QuantitySlave + 2, &ucountQuantityCard, 2);
						xQueueSend(xQueueDataTaskCardSendMasterCard_State_tHandle,&MasterState,portMAX_DELAY);
						xQueueSend(xQueueDataTaskCardSendData_Card_tHandle, &CardAddRemove,portMAX_DELAY);
					}
				}
			}	
		}
	}
}
