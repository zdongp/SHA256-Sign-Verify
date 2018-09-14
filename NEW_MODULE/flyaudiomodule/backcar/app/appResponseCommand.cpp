#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"

#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "appRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "param.h"
#include "timer_interface.h"



void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);

	ctrlType = buffer[4];
	paramLen = len - 5;
	param = &buffer[5];
    LOGD("backcar analyseAppMessage ctrlType:%x ctrlId:0x%x",ctrlType,ctrlId);
	switch(ctrlId){
		case CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_MENU:
			if(ctrlType == UIACTION_MOUSEUP)
			 	appToBackcar_EnterPanoramicVideo();
			break;
		case CONTROLID_BACKCAR_FULL_VIDEO_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP)
				appToBackcar_ExitPanoramicVideo();
			break;
		case CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_BACKGROUND:
			if(ctrlType == UIACTION_MOUSEUP)
				appToBackcar_EnterFullScreen();
			break;
		case CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_F_CAMERA_BTN:
			if(ctrlType == UIACTION_MOUSEUP)
				appToBackcar_SelectVideo('F');
			break;
		case CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_R_CAMERA_BTN:
			if(ctrlType == UIACTION_MOUSEUP)
				appToBackcar_SelectVideo('R');
			break;
		case CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_L_CAMERA_BTN:
			if(ctrlType == UIACTION_MOUSEUP)
				appToBackcar_SelectVideo('L');
			break;
		case CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_B_CAMERA_BTN:
			if(ctrlType == UIACTION_MOUSEUP)
				appToBackcar_SelectVideo('B');
			break;

		case CONTROLID_BACK_VIDEO_HAND_UP:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				backCarToModule_NotifyBT_HandUp_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN)
			{
				setAnalogData(CONTROLID_BACK_VIDEO_HAND_UP,1);
			}
			break;
		case CONTROLID_BACK_VIDEO_CALL_IN:
			if(ctrlType == UIACTION_MOUSEUP){
				backCarToModule_NotifyBT_CallIn_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				setAnalogData(CONTROLID_BACK_VIDEO_CALL_IN,1);
			}
			break;
		case CONTROLID_BACK_VIDEO_PERSPECTIVE_GUANGJIAO:
		case CONTROLID_BACK_VIDEO_PERSPECTIVE_NORMAL:
		case CONTROLID_BACK_VIDEO_PERSPECTIVE_FUJIAO:
			{
				if(ctrlType==UIACTION_MOUSEDOWN){
					   appToBackCar_T123VideoSetButton(ctrlId,ctrlType);
				}
			}
			break;

		case CONTROLID_BACK_VIDEO_OSD_GROUND:
		case CONTROLID_BACK_VIDEO_SET_BUTTON:// ï¿½ï¿½ï¿½Ã°ï¿½Å¥  //2014/04/14
		case CONTROLID_BACK_VIDEO_WARNINT_LINE_UP:
		case CONTROLID_BACK_VIDEO_WARNINT_LINE_DOWN:
		{
    		appToBackCar_T123VideoSetButton(ctrlId,ctrlType);
			if(ctrlType == UIACTION_MOUSEUP)
				appToBackCar_T123VideoSetButton_ColorPage(ctrlId,ctrlType);
    		break;
		}
		break;
		case CONTROLID_BACK_VIDEO_SET_CONTRAST_JIAN:// ï¿½Ô±È¶ï¿½ ï¿½ï¿½
		case CONTROLID_BACK_VIDEO_SET_CONTRAST_JIA:// ï¿½Ô±È¶ï¿½ ï¿½ï¿½
		case CONTROLID_BACK_VIDEO_SET_TONE_JIAN://ï¿½ï¿½ï¿½Í¶ï¿½ ï¿½ï¿½
		case CONTROLID_BACK_VIDEO_SET_TONE_JIA://  ï¿½ï¿½ï¿½Í¶ï¿½ ï¿½ï¿½
		case CONTROLID_BACK_VIDEO_SET_SATURATION_JIAN://  É«ï¿½ï¿½  ï¿½ï¿½
		case CONTROLID_BACK_VIDEO_SET_SATURATION_JIA://  É«ï¿½ï¿½  ï¿½ï¿½
		case CONTROLID_BACK_VIDEO_SET_BRIGHTNESS_JIAN:  //ÁÁ¶È¼õ°´Å¥
        case CONTROLID_BACK_VIDEO_SET_BRIGHTNESS_JIA:   //ÁÁ¶È¼Ó°´Å¥
    		appToBackcar_T123videoOSD_colorSetButton(ctrlId,ctrlType);
    		break;
		case CONTROLID_BACK_VIDEO_PRADO_SCREEN_COORDINATE:
		{
			LOGD("appAnalyseMessage Prado ControlID=0x70540,");
			if(ctrlType == UIACTION_MOUSEUP )
			   appToBackCar_Process_Prado_ScreenCoordinate(param,paramLen);
		}
		break;
		case CONTROLID_BACK_NO_SIGN_BACK:
			if(ctrlType == UIACTION_MOUSEUP)
				backCarToModule_NotifySystem_JumpPage(PAGE_MENU);
			break;
		case CONTROLID_BACK_VIDEO_TRACE_TYPE_SWITCH:
		case CONTROLID_BACK_VIDEO_TRACE_TYPE_CHANGE:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToBackCar_Video_TraceType_switch();
			}
			break;
		/*
		case CONTROLID_BACK_VIDEO_TRACE_TYPE_CHANGE:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				appToBackCar_Video_TraceType_switch();
			}
			break;
		*/
		case CONTROLID_BACK_VIDEO_ZOOM_IN_OR_OUT:
			if(ctrlType == UIACTION_MOUSEUP)
				setToExtcarSetVoiceSizeMessage(pLocalParam->uVideoZoomInOrOut);
			break;
		default:break;
	}
}
