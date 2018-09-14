#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"
#include "appResponseCommand.h"

void test(){//测试用
	//u8 buf[]={0x01,0x53,0x00,0x59,0x00,0x4E,0x00,0x43,0x00, 0x3C,0x00,0xBE,0x8B,0x6E,0x7F,0x00,0x00};
	//u8 buf[]={0x01,0x00,0x53,0x00,0x59,0x00,0x4E,0x00,0x43,0x00,0x3C,0x8B,0xBE,0x7F,0x6E};
	//u8 buf[] = {0x00, 'a','b','c','d','e','f'};
	//Get_Sync_Title(buf,17);
	//u8 buf[]={0x01,0x00,0x8D,0x44,0x6E,0x90,0x00,0x00};
	//Get_Sync_Char_Button1(buf,8);
	//Get_Sync_String_OneLine(buf,15);
	//Get_Sync_String_FourLine(buf,15);
	//Get_CurSelectLine(1);
	//u8 buf[]={0x08,0x01,0x77};
	//analyseHalMessage_CarType_NEW_FOCUS(buf,3);
	//u8 buf[]={0x08, 0x00, 0x23};
	//analyseHalMessage_CarType_NEW_FOCUS(buf,3);
}

void test1(){//测试用

}

void appToSYNC_MainButton_MouseUp(u32 FunID)
{
	syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_RELEASE_FINGER);
}

void appToSYNC_MainButton_MouseTimer(u32 FunIDs)
{
	syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_RELEASE_FINGER);
}

void appToSYNC_MainButton_MouseDown(u32 FunID)
{
	u8 IR_Sign = 0;
	switch(FunID){
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1:
			IR_Sign = IR_SYNV_BTN_1;
		break;
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2:
			IR_Sign = IR_SYNV_BTN_2;
		break;
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3:
			IR_Sign = IR_SYNV_BTN_3;
		break;
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4:
			IR_Sign = IR_SYNV_BTN_4;
		break;
		
		case CONTROLIDTRAVEL_SYNV_MENU_BTN:
			IR_Sign = IR_SYNV_MENU_BTN;
		break;
		case CONTROLIDTRAVEL_SYNV_PHONE_BTN:
			IR_Sign = IR_SYNV_PHONE_BTN;
		break;
		case CONTROLIDTRAVEL_SYNV_END_BTN:
			IR_Sign = IR_SYNV_END_BTN;
		break;
		case CONTROLIDTRAVEL_SYNV_SEND_BTN:
			IR_Sign = IR_SYNV_SEND_BTN;
		break;
		case CONTROLIDTRAVEL_SYNV_INFO_BTN:
			IR_Sign = IR_SYNV_INFO_BTN;
		break;

		//------------TEXT文本选择功能键---------//
		case CONTROLIDTRAVEL_SYNV_PREV_BTN:
			IR_Sign = IR_SYNV_PREV_BTN;
		break;
		case CONTROLIDTRAVEL_SYNV_NEXT_BTN:
			IR_Sign = IR_SYNV_NEXT_BTN;
		break;
		case CONTROLIDTRAVEL_SYNV_UP_BTN:
			IR_Sign = IR_SYNV_UP_BTN;
		break;
		case CONTROLIDTRAVEL_SYNV_DOWN_BTN:
			IR_Sign = IR_SYNV_DOWN_BTN;
		break;
		case CONTROLIDTRAVEL_SYNV_OK_BTN:
			IR_Sign = IR_SYNV_OK_BTN;
		break;
		
		case CONTROLIDTRAVEL_SYNV_0:
			IR_Sign = IR_SYNV_SYNV_0;
		break;
		case CONTROLIDTRAVEL_SYNV_1:
			IR_Sign = IR_SYNV_SYNV_1;
		break;
		case CONTROLIDTRAVEL_SYNV_2:
			IR_Sign = IR_SYNV_SYNV_2;
		break;
		case CONTROLIDTRAVEL_SYNV_3:
			IR_Sign = IR_SYNV_SYNV_3;
		break;
		case CONTROLIDTRAVEL_SYNV_4:
			IR_Sign = IR_SYNV_SYNV_4;
		break;
		case CONTROLIDTRAVEL_SYNV_5:
			IR_Sign = IR_SYNV_SYNV_5;
		break;
		case CONTROLIDTRAVEL_SYNV_6:
			IR_Sign = IR_SYNV_SYNV_6;
		break;
		case CONTROLIDTRAVEL_SYNV_7:
			IR_Sign = IR_SYNV_SYNV_7;
		break;
		case CONTROLIDTRAVEL_SYNV_8:
			IR_Sign = IR_SYNV_SYNV_8;
		break;
		case CONTROLIDTRAVEL_SYNV_9:
			IR_Sign = IR_SYNV_SYNV_9;
		break;
		case CONTROLIDTRAVEL_SYNV_XING:	
			IR_Sign = IR_SYNV_SYNV_MULTIPLY;
		break;
		case CONTROLIDTRAVEL_SYNV_JIN:
			IR_Sign = IR_SYNV_SYNV_WELL;
		break;		
		case CONTROLIDTRAVEL_SYNV_AUX_BTN:
			IR_Sign = IR_SYNV_AUX_BTN;
		break;
		default:break;
	}

	syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_Sign);
}

void appToSYNC_MENUSync_MouseUp(){
	syncToModule_NotifySystem_JumpPage(PAGE_SYNV_MENU);	
}

void appToSYNC_MainBACK_MouseUp(){
	syncToModule_NotifySystem_JumpPage(PAGE_MENU);
}

void appToSYNC_MainAudio_MouseUp(){
	syncToModule_NotifySystem_JumpPage(PAGE_SOUND);
}

void appToSYNC_InSpeech_MouseUp(void){
	syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_RELEASE_FINGER);
	test();
}

void appToSYNC_ApplicationButton_MouseUp()
{
	syncToHal_Command(SYNC_MODE,SYNC_CMD_0X00,IR_SYNV_RELEASE_FINGER);
}

void appToSyncModule_BackNextPage_File_Button(int ctrlId,char ctrlType)
{
	switch(ctrlId)
    {
		//-------------功能键------------------//
		//case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1:			           		       
		//case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2:		           		        
		//case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3:		           		       
		//case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4:
		
		//case CONTROLIDTRAVEL_SYNV_MENU_BTN:
		//case CONTROLIDTRAVEL_SYNV_INFO_BTN:
		//case CONTROLIDTRAVEL_SYNV_AUX_BTN:
		
		//case CONTROLIDTRAVEL_SYNV_UP_BTN:
		//case CONTROLIDTRAVEL_SYNV_DOWN_BTN:
		//case CONTROLIDTRAVEL_SYNV_PREV_BTN:
		//case CONTROLIDTRAVEL_SYNV_NEXT_BTN:
		//case CONTROLIDTRAVEL_SYNV_OK_BTN:
		//------------数字区域键------------//

		///////////////////////////////////////////////////////
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_1:			           		       
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_2:		           		        
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_3:		           		       
		case CONTROLIDTRAVEL_SYNV_FUNCTION_BTN_4:
		case CONTROLIDTRAVEL_SYNV_MENU_BTN:
		case CONTROLIDTRAVEL_SYNV_UP_BTN:
		case CONTROLIDTRAVEL_SYNV_DOWN_BTN:
		case CONTROLIDTRAVEL_SYNV_PREV_BTN:
		case CONTROLIDTRAVEL_SYNV_NEXT_BTN:
		case CONTROLIDTRAVEL_SYNV_OK_BTN:
			case CONTROLIDTRAVEL_SYNV_PHONE_BTN:	
			case CONTROLIDTRAVEL_SYNV_SEND_BTN:
			case CONTROLIDTRAVEL_SYNV_END_BTN:

			if(ctrlType == UIACTION_MOUSEUP){
			}
			break;

		default:break;
    }
}