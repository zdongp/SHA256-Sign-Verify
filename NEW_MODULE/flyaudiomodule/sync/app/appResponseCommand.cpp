#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
#include "timer_interface.h"

void appInit(void){
}

void appDeInit(void){
}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;
	u8 u8_MouseStatus = 0;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);

	ctrlType = buffer[4];
	u8_MouseStatus = buffer[5];
	paramLen = len - 5;
	param = &buffer[5];

	//if(!pLocalParam->b_SyncAble)
	//	return;
	appToSyncModule_BackNextPage_File_Button(ctrlId,ctrlType);
	LOGD("AppToSYNC_ctrlType:0x%x.  ctrlId:  0x%x+++++++++\n",ctrlType,ctrlId);
	switch(ctrlId)
    {
    	/*************** 新福克斯  NEW_FOCUS*******************/
		case CONTROLID_MENU_SYNV: ///*进入SYNC_MANI*/		
			if(ctrlType == UIACTION_MOUSEUP)
				appToSYNC_MENUSync_MouseUp();
		break;
		case CONTROLIDTRAVEL_SYNV_MENU_BACK: ///*返回*/
			if(ctrlType == UIACTION_MOUSEUP)
				appToSYNC_MainBACK_MouseUp();
		break;
		case CONTROLIDTRAVEL_SYNV_AUDIO:	///*Audio*/
			if(ctrlType == UIACTION_MOUSEUP){
				appToSYNC_MainAudio_MouseUp();
			}
		break;

		//-------------功能键------------------//
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1:			           		       
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2:		           		        
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3:		           		       
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4:
		
		case CONTROLIDTRAVEL_SYNV_MENU_BTN:
		case CONTROLIDTRAVEL_SYNV_INFO_BTN:
		case CONTROLIDTRAVEL_SYNV_AUX_BTN:
		
		case CONTROLIDTRAVEL_SYNV_UP_BTN:
		case CONTROLIDTRAVEL_SYNV_DOWN_BTN:
		case CONTROLIDTRAVEL_SYNV_PREV_BTN:
		case CONTROLIDTRAVEL_SYNV_NEXT_BTN:
		case CONTROLIDTRAVEL_SYNV_OK_BTN:
		//------------数字区域键------------//
		case CONTROLIDTRAVEL_SYNV_0:			           		                   
		case CONTROLIDTRAVEL_SYNV_1:			           		                    
		case CONTROLIDTRAVEL_SYNV_2:			           		                   
		case CONTROLIDTRAVEL_SYNV_3:			           		                   
		case CONTROLIDTRAVEL_SYNV_4:			           		                  
		case CONTROLIDTRAVEL_SYNV_5:		           		                        
		case CONTROLIDTRAVEL_SYNV_6:			           		                   
		case CONTROLIDTRAVEL_SYNV_7:			           		                  
		case CONTROLIDTRAVEL_SYNV_8:			           		                   
		case CONTROLIDTRAVEL_SYNV_9:			           		                   
		case CONTROLIDTRAVEL_SYNV_XING:			           		                
		case CONTROLIDTRAVEL_SYNV_JIN:
		
		case CONTROLIDTRAVEL_SYNV_PHONE_BTN:	
		case CONTROLIDTRAVEL_SYNV_SEND_BTN:
		case CONTROLIDTRAVEL_SYNV_END_BTN:
			if(ctrlType == UIACTION_MOUSEUP){
				appToSYNC_MainButton_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToSYNC_MainButton_MouseTimer(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToSYNC_MainButton_MouseDown(ctrlId);
			}
		break;
		case CONTROLIDTRAVEL_SYNV_SPEECH_BTN:  /*speech按钮*/
			if(ctrlType == UIACTION_MOUSEUP){
				appToSYNC_InSpeech_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
			}
			else if(ctrlType == UIACTION_MOUSEDOWN)
				{
				syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_SPEECH);
			}
		break;
		case CONTROLIDTRAVEL_SYNC_APPLICATION:
		if(ctrlType == UIACTION_MOUSEUP){
			appToSYNC_ApplicationButton_MouseUp();
		}
		else if(ctrlType == UIACTION_MOUSEDOWN)
		{
		 	syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_APPLICATION);
		}
		break;
		default:break;
    }
}


