#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"

#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "halRequestFunction.h"



void appInit(void){

}

void appDeInit(void){

}

void analyseAppMessage(unsigned char *buffer, unsigned char len)
{	

	
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;
	
	u8 u8_MouseStatus = 0;
	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);
	u8_MouseStatus = buffer[5];
	ctrlType = buffer[4];
	paramLen = len - 5;
	param = &buffer[5];

//	if(ctrlType == UIACTION_MOUSEUP){
//		if(pLocalParam->eScanState != Ctrl_STOP && ctrlId != CONTROLID_RADIO_MAIN_SCAN)
//			radioTohal_ScanCtrl(Ctrl_STOP);
//	}
	LOGD("radio analyseAppMessage:ctrlId=0x%0x,ctrlType=%d",ctrlId,ctrlType);
	switch(ctrlId){
		case CONTROLID_RADIO_MAIN_EQ://EQ
			if(ctrlType == UIACTION_MOUSEUP){
				appToRadio_Eq_MouseUp();
			}else if(ctrlType == UIACTION_MOUSEDOWN){
				appToRadio_Eq_MouseDown();
			}
			break;
		case CONTROLID_RADIO_MAIN_AUDIO://Audio
			if(ctrlType == UIACTION_MOUSEUP){
				appToRadio_Audio_MouseUp();
			}else if(ctrlType == UIACTION_MOUSEDOWN){
				appToRadio_Audio_MouseDown();
			}
			break;
		case CONTROLID_RADIO_MAIN_TURNOFF://�ر�������
		case CONTROLID_RADIO_MAIN_OTHER_TURNOFF:
			if(ctrlType == UIACTION_MOUSEUP)
				appToRadio_TurnOFF_MouseUp();
			break;
		case CONTROLID_RADIO_MAIN_FM1://
		//case CONTROLID_RADIO_MAIN_FM2://
		case CONTROLID_RADIO_MAIN_AM: //
			if(ctrlType == UIACTION_MOUSEUP){
		
                appToRadio_RadioChannel_MouseUp(ctrlId - CONTROLID_RADIO_MAIN_FM1);//FM1 FM2 AM
        	}
			else if(ctrlType == UIACTION_MOUSEDOWN){
        		appToRadio_RadioChannel_MouseDown(ctrlId - CONTROLID_RADIO_MAIN_FM1);
        	}
			break;
		case CONTROLID_RADIO_MAIN_SCAN://
            if(ctrlType == UIACTION_MOUSEUP)
            {
				pLocalParam->bUiButtonDownNoShow = false;
				appToRadio_Scan_MouseUp();
            }
			else if(ctrlType == UIACTION_MOUSETIMER)
			{	
				appToRadio_Scan_MouseTimer();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN)
			{
				appToRadio_Scan_MoudeDown();
			}
			break;
			
		case CONTROLID_MENU_RADIO://
		case CONTROLID_RADIO_JUMP_TO_MAIN_PAGE:
			if(ctrlType == UIACTION_MOUSEUP)
			appToRadio_MenuRadio_MouseUp();
			break;
		
		case CONTROLID_RADIO_MAIN_BACK:
			if(ctrlType == UIACTION_MOUSEUP)
			appToRadio_Back_MouseUp();
			break;
		//case CONTROLID_RADIO_MAIN_TIPS://
		case CONTROLID_RADIO_MAIN_UP://
		case CONTROLID_RADIO_MAIN_DOWN://
			if(ctrlType == UIACTION_MOUSEUP)
				appToRadio_FreqCtrl_MouseUp(ctrlId-CONTROLID_RADIO_MAIN_UP);
			else if (ctrlType == UIACTION_MOUSEDOWN)
				appToRadio_FreqCtrl_MouseDown(ctrlId-CONTROLID_RADIO_MAIN_UP);
			break;
 		case CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN:  //
		case CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+1://
		case CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+2://
		case CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+3://
		case CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+4://
		case CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+5://
		//case CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+6://
			if(ctrlType == UIACTION_MOUSETIMER)
			{
				appToRadio_Channel_MouseTimer(ctrlId-CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN);
			}
			else if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Channel_MouseUp(ctrlId-CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN);
			}
			else if(ctrlType == UIACTION_MOUSEDOWN)
			{
				appToRadio_Channel_MouseDown(ctrlId-CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN);
			}
			break;
			
		case CONTROLID_RADIO_MAIN_NEXT_CHANNEL:
			if(ctrlType == UIACTION_MOUSEUP){
				pLocalParam->bUiButtonDownNoShow = false;
				appToRadio_Scan_Inc_MouseUp();
			}
				break;
		case CONTROLID_RADIO_MAIN_ON_ONE_CHANNEL:
			if(ctrlType == UIACTION_MOUSEUP){
				pLocalParam->bUiButtonDownNoShow = false;
				appToRadio_Scan_Dec_MouseUp();
			}
				break;
		case CONTROLID_RAFIO_MAIN_FREQUENCY://frequency
		case CONTROLID_RAFIO_MAIN_FREQUENCY_NEW:
			if(ctrlType == UIACTION_MOUSEUP)
				appToRadio_Main_Frequency_MouseUp();
			break;
		case CONTROLID_RADIO_MAIN_CHANNEL_GUANG:
			if(ctrlType == UIACTION_MOUSEUP){
				appToRadio_Main_Gauge_MouseUp(param,len);
			}
			break;


			
		case CONTROLID_RADIO_MAIN_PREVIOUS:
			if(ctrlType == UIACTION_MOUSEUP){
				appToRadio_MAIN_PrePage();
			}
			break;
		case CONTROLID_RADIO_MAIN_NEXT:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_MAIN_NextPage();
			}
			break;

			
	// Set page
		case CONTROLID_RADIO_SET_AUDIO:
			if(ctrlType == UIACTION_MOUSEUP){
				appToRadio_Audio_MouseUp();
			}else if(ctrlType == UIACTION_MOUSEDOWN){
				appToRadio_Audio_MouseDown();
			}
			break;
		case CONTROLID_RADIO_SET_OPEN_RADIO:
			if(ctrlType == UIACTION_MOUSEUP)
				appToRadio_TurnOFF_MouseUp();
			break;
		case CONTROLID_RADIO_SET_BACK:
				appToRadio_Set_Back_MouseUp();
			break;
		case CONTROLID_RADIO_SET_TF_SET:
			if(ctrlType == UIACTION_MOUSEUP)
				appToRadio_Set_TA_MouseUp(u8_MouseStatus);
			
			break;
		case CONTROLID_RADIO_SET_TA_ON:
		case CONTROLID_RADIO_SET_TA_OFF:
			if(ctrlType == UIACTION_MOUSEUP)
			   appToRadio_Main_SetTA(ctrlId);
			break;
		case CONTROLID_RADIO_SET_AF_ON:
		case CONTROLID_RADIO_SET_AF_OFF:
			if(ctrlType == UIACTION_MOUSEUP)
			appToRadio_Main_SetAF(ctrlId);
			break;
		case CONTROLID_RADIO_SET_AF_SET:
			if(ctrlType == UIACTION_MOUSEUP)
				appToRadio_Set_AF_MouseUp(u8_MouseStatus);
			break;
		// number page
		case CONTROLID_RADIO_NUMBER_1:
		case CONTROLID_RADIO_NUMBER_2:
		case CONTROLID_RADIO_NUMBER_3:
		case CONTROLID_RADIO_NUMBER_4:
		case CONTROLID_RADIO_NUMBER_5:
		case CONTROLID_RADIO_NUMBER_6:
		case CONTROLID_RADIO_NUMBER_7:
		case CONTROLID_RADIO_NUMBER_8:
		case CONTROLID_RADIO_NUMBER_9:
		   	if(ctrlType == UIACTION_MOUSEUP)
			{
				int index = ctrlId - CONTROLID_RADIO_NUMBER_1 + 1;
				appToRadio_Number_num(index);
			}
			break;
		case CONTROLID_RADIO_NUMBER_0:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Number_num(0);
			}
			break;
		case CONTROLID_RADIO_NUMBER_POINT:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Number_Point();
			}
			break;
		case CONTROLID_RADIO_NUMBER_DEl:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Number_Del();
			}
			break;
		case CONTROLID_RADIO_NUMBER_CANCEL:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Number_Cancel();
			}
			break;
		case CONTROLID_RADIO_NUMBER_OK:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Number_OK();
			}
			break;
		case CONTROLID_RADIO_NUMBER_BACK:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Number_Back();
			}
			break;
		case CONTROLID_RADIO_MAIN_DELETE:
			appToRadio_Main_Delete();
			break;

		case  CONTROLID_RADIO_MAIN_SETUP://  s et
			 if(ctrlType == UIACTION_MOUSEUP)
			 {
				appToRadio_Set_MouseUp();
			 }
			break;	

			
		case CONTROLID_RADIO_MAIN_SET_GAO:
		case CONTROLID_RADIO_MAIN_SET_ZHONG:
		case CONTROLID_RADIO_MAIN_SET_DI:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Main_SetSensitivity(ctrlId);
			}
			break;
		
		case CONTROLID_RADIO_MAIN_FM_AM_SWITCH:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Radio_FM_AM_Switch();
			}						
			break;
		case  CONTROLID_RADIO_MAIN_INC_FINE_TUNE_OR_SEARCH:
		case CONTROLID_RADIO_MAIN_DEC_FINE_TUNE_OR_SEARCH:
			{
				RadioToUI_Main_SetFineTuneButton(ctrlId,ctrlType);
				if(ctrlType == UIACTION_MOUSEUP)
				{
					appToRadio_FreqCtrl_SetFineTune_MouseUp(ctrlId-CONTROLID_RADIO_MAIN_INC_FINE_TUNE_OR_SEARCH);
				}
				else if(ctrlType == UIACTION_MOUSETIMER)
				{
					pLocalParam->bUiButtonDownNoShow = false;
					appToRadio_FreqCtrl_SearchType(ctrlId-CONTROLID_RADIO_MAIN_INC_FINE_TUNE_OR_SEARCH);
				}
			}
			break;
		case CONTROLID_RADIO_MAIN_SWITCH_CHANNEL_BUTTON:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToRadio_Radio_FM_AM_Switch();
			}
			break;
	    default:
			break;
	}
}



