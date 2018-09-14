#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "appResponseCommand.h"
#include "appRequestFunction.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "timer_interface.h"


void appToBackCar_ProcessMoveLineMsg(char cIndex)
{
	if (0 == cIndex)// up
	{
		if (pLocalParam->cCurPosOfLine <= pLocalParam->cMaxRangeOfLine - 1)
		{
			pLocalParam->cCurPosOfLine += 1;

			if (0 == pLocalParam->cCurPosOfLine)
				setVisible(CONTROLID_BACK_VIDEO_GAUGE, false);
			else
				setVisible(CONTROLID_BACK_VIDEO_GAUGE, true);

			setAnalogData(CONTROLID_BACK_VIDEO_GAUGE, pLocalParam->cCurPosOfLine);
		}
	}
	else if (1 == cIndex) // timer
	{
		if(pLocalParam->cCurPosOfLine > 0)
		{
			pLocalParam->cCurPosOfLine -= 1;

			if (0 == pLocalParam->cCurPosOfLine)
				setVisible(CONTROLID_BACK_VIDEO_GAUGE, false);
			else
				setVisible(CONTROLID_BACK_VIDEO_GAUGE, true);

			setAnalogData(CONTROLID_BACK_VIDEO_GAUGE, pLocalParam->cCurPosOfLine);
		}
	}
}

void appToBackCar_Cordonl_MouseUp(char cIndex)
{
	appToBackCar_ProcessMoveLineMsg(cIndex);
}

void appToBackCar_Cordonl_MouseTimer(char cIndex)
{
	appToBackCar_ProcessMoveLineMsg(cIndex);
}

void appToBackcar_EnterPanoramicVideo(void)
{
    backCarToModule_NotifySystem_JumpPage(PAGE_BACK_FULL_VIDEO_CONTROL);

	BackcarToHal_EnterPanoramicVideo();
	backCarToModule_NotifyOSD(true);

	BackcarToHal_SelectVideo(pLocalParam->saveBackCar);
	setAnalogData(CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_WHICH_IMG,((short)pLocalParam->saveBackCar)-1);
}

void appToBackcar_ExitPanoramicVideo(void)
{
	if(pLocalParam->EnterAllScreen != 1) return;

	backCarToModule_NotifySystem_JumpPage(PAGE_BACK_FULL_VIDEO_CONTROL);
	usleep(50*1000);
	BackcarToHal_ExitFullScreen();
	pLocalParam->EnterAllScreen=0;
}

static void appToBackcar_EnterSelectScreen(char direction)
{
	BackcarToHal_SelectVideo(direction);
	pLocalParam->saveBackCar=direction;
}

void appToBackcar_SelectVideo(char direction)
{
	if(pLocalParam->EnterAllScreen != 0) return;

	switch(direction)
	{
		case 'F':
		case 'f':
			appToBackcar_EnterSelectScreen(0x01);
			setAnalogData(CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_WHICH_IMG,(short)0);
			break;
		case 'R':
		case 'r':
			appToBackcar_EnterSelectScreen(0x04);
			setAnalogData(CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_WHICH_IMG,(short)3);
			break;
		case 'L':
		case 'l':
			appToBackcar_EnterSelectScreen(0x03);
			setAnalogData(CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_WHICH_IMG,(short)2);
			break;
		case 'B':
		case 'b':
			appToBackcar_EnterSelectScreen(0x02);
			setAnalogData(CONTROLID_BACKCAR_FULL_VIDEO_CONTROL_WHICH_IMG,(short)1);
			break;
		default:
			break;
	}

}


void appToBackcar_EnterFullScreen(void)
{
	if(pLocalParam->EnterAllScreen != 0) return ;

	BackcarToHal_EnterFullScreen();
	usleep(40*1000);
	backCarToModule_NotifySystem_JumpPage(PAGE_BACK_FULL_VIDEO);
	pLocalParam->EnterAllScreen=1;
}

void appToBackCar_T123VideoSetButton(int ctrlId,u8 ctrlType)
{
	if(ctrlId == CONTROLID_BACK_VIDEO_WARNINT_LINE_UP || ctrlId == CONTROLID_BACK_VIDEO_WARNINT_LINE_DOWN)
	{
		if(ctrlType == UIACTION_MOUSEUP)
			appToBackCar_Cordonl_MouseUp(ctrlId-CONTROLID_BACK_VIDEO_WARNINT_LINE_UP);
		else if (ctrlType == UIACTION_MOUSETIMER)
			appToBackCar_Cordonl_MouseTimer(ctrlId-CONTROLID_BACK_VIDEO_WARNINT_LINE_UP);
	}

	//DeleteTimer(BACK_OSD_VIDEO_SET_CONTROL);
	//SetTimer(3000,0,BACK_OSD_VIDEO_SET_CONTROL);

	u8 swtich_button=0;
	u8 button_status=0xff;

	switch(ctrlId)
	{
	case CONTROLID_BACK_VIDEO_OSD_GROUND:
		//swtich_button = ;
		return;
		break;
	case CONTROLID_BACK_VIDEO_SET_BUTTON:// ï¿½ï¿½ï¿½Ã°ï¿½Å¥  //2014/04/14
		swtich_button = 0x01;
		break;
	case CONTROLID_BACK_VIDEO_WARNINT_LINE_UP:
		swtich_button = 0x10;
		break;
	case CONTROLID_BACK_VIDEO_WARNINT_LINE_DOWN:
		swtich_button = 0x11;
		break;
	case CONTROLID_BACK_VIDEO_PERSPECTIVE_GUANGJIAO:
		{
			swtich_button = 0x20;
			if(pLocalParam->nBackVisionAngle==0x01)return;
			pLocalParam->nBackVisionAngle = 0x01;
			backcarToModule_NotifySystem_VisionAngle(0x01);
			backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(0x21,0x00);
			backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(0x22,0x00);
		}
		break;
	case CONTROLID_BACK_VIDEO_PERSPECTIVE_NORMAL:
		{
			swtich_button = 0x21;
			if(pLocalParam->nBackVisionAngle==0x02)return;
			pLocalParam->nBackVisionAngle = 0x02;
			backcarToModule_NotifySystem_VisionAngle(0x02);
			backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(0x20,0x00);
			backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(0x22,0x00);

		}
		break;
	case CONTROLID_BACK_VIDEO_PERSPECTIVE_FUJIAO:
		{
			swtich_button = 0x22;
			if(pLocalParam->nBackVisionAngle==0x03)return;
			pLocalParam->nBackVisionAngle = 0x03;
			backcarToModule_NotifySystem_VisionAngle(0x03);
			backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(0x20,0x00);
			backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(0x21,0x00);
		}
		break;
	}

	if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
	{
		button_status=0x00;
	}
	else
	{

		button_status=0x01;
	}

	backcarToModule_NotifyOSD_aboutT123_VideoOSDSetButton(swtich_button,button_status);


}

void appToBackCar_T123VideoSetButton_ColorPage(int ctrlId,u8 ctrlType)
{
	switch(ctrlId)
	{
		case CONTROLID_BACK_VIDEO_OSD_GROUND:
		    BackcarVideo_BackGroundColor_Set(false);
			break;
		case CONTROLID_BACK_VIDEO_SET_BUTTON:// ï¿½ï¿½ï¿½Ã°ï¿½Å¥  //2014/04/14 
			BackcarVideo_BackGroundColor_Set(true);
			break;
		case CONTROLID_BACK_VIDEO_WARNINT_LINE_UP:
		    break;
	    case CONTROLID_BACK_VIDEO_WARNINT_LINE_DOWN:
	        break;
	}

}


void appToBackcar_T123videoOSD_colorSetButton(int ctrlID,u8 ctrlType)
{
    u8 swtich_button=0;
    u8 button_status=0xff;
    u8 value=0xff;
    u8 setOptions=0xff;
    u8 u_WhichColorValue = 0;

	switch(ctrlID)
    {
    	case CONTROLID_BACK_VIDEO_SET_TONE_JIAN://ï¿½ï¿½ï¿½Í¶ï¿½ ï¿½ï¿½
    	swtich_button=0x01;
    	u_WhichColorValue = 2;
    	break;
    	case CONTROLID_BACK_VIDEO_SET_TONE_JIA://  ï¿½ï¿½ï¿½Í¶ï¿½ ï¿½ï¿½
    	swtich_button=0x02;
    	u_WhichColorValue = 1;
    	break;
    	case CONTROLID_BACK_VIDEO_SET_BRIGHTNESS_JIAN:  //ÁÁ¶È¼õ°´Å¥
    	swtich_button=0x03;
    	u_WhichColorValue = 8;
    	break;
        case CONTROLID_BACK_VIDEO_SET_BRIGHTNESS_JIA:   //ÁÁ¶È¼Ó°´Å¥
        swtich_button=0x04;
        u_WhichColorValue = 7;
        break;
    	case CONTROLID_BACK_VIDEO_SET_SATURATION_JIAN://  É«ï¿½ï¿½  ï¿½ï¿½
    	swtich_button=0x05;
    	u_WhichColorValue = 4;
    	break;
    	case CONTROLID_BACK_VIDEO_SET_SATURATION_JIA://  É«ï¿½ï¿½  ï¿½ï¿½
    	swtich_button=0x06;
    	u_WhichColorValue = 3;
    	break;
    	case CONTROLID_BACK_VIDEO_SET_CONTRAST_JIAN:// ï¿½Ô±È¶ï¿½ ï¿½ï¿½
    	swtich_button=0x07;
    	u_WhichColorValue = 6;
    	break;
    	case CONTROLID_BACK_VIDEO_SET_CONTRAST_JIA:// ï¿½Ô±È¶ï¿½ ï¿½ï¿½
    	swtich_button=0x08;
    	u_WhichColorValue = 5;
    	break;
		default:return;
		break;
    }
			
     if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
     {
    	 button_status=0x00;
	 }
	 else
	 {
	     button_status=0x01;
	 }
	 backcarToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(swtich_button,button_status);
	 
	 if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
     {
		 backCarToModule_NotifyAudioVideo_aboutBackCarVideoSet(u_WhichColorValue);
	 }
    
}

void appToBackCar_Process_Prado_ScreenCoordinate(u8* param,u8 paramLen)
{
    if(paramLen>=4){
    	int x = param[0]+param[1]*256;
    	int y = param[2]+param[3]*256;

    	backCarToModule_NotifyExtcar_Prado_ScreenCoordinates(param,paramLen);
        LOGD("Prado_ScreenCoordinate origin x=%d,y=%d",x,y);
    }
}

void ToUI_BackCarVideo_TraceType(Em_Backcar_TraceType em)
{
	setAnalogData(CONTROLID_BACK_VIDEO_TRACE_TYPE, (int)em);
	setGroupNumber(CONTROLID_BACK_VIDEO_TRACE_TYPE_SWITCH, (int)em);
}

void appToBackCar_Video_TraceType_switch(void)
{
	Em_Backcar_TraceType e_TemBackcar_TraceType = pLocalParam->e_Backcar_TraceType;

	switch(e_TemBackcar_TraceType)
	{
		case TraceType_0:
			e_TemBackcar_TraceType = TraceType_1;
			break;
		case TraceType_1:
			e_TemBackcar_TraceType = TraceType_2;
			break;
		case TraceType_2:
			e_TemBackcar_TraceType = TraceType_0;
			break;
		default:break;
	}

	ToUI_BackCarVideo_TraceType(e_TemBackcar_TraceType);
	pLocalParam->e_Backcar_TraceType = e_TemBackcar_TraceType;
	backCarToModule_NotifySystem_BackCarVideoLineType((u8)pLocalParam->e_Backcar_TraceType);
}

void IsDisplaying_WarnintLineText(u8 p)
{
	if(p == 1)//e.g:ChangHe don't show.
	{
		BackcarToApp_Displaying_WarnintLineText(false);
	}
	else
	{
    	BackcarToApp_Displaying_WarnintLineText(true);
	}
}

void showVideoZoomInOrOutStatus(u8 param)
{
	if(param == 0x00)
		setDigitalData(CONTROLID_BACK_VIDEO_ZOOM_IN_OR_OUT,0);
	else 
		setDigitalData(CONTROLID_BACK_VIDEO_ZOOM_IN_OR_OUT,1);
}