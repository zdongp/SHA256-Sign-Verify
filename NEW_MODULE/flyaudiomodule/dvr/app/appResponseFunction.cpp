#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "appResponseCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamResponse.h"
#include "timer_interface.h"
#include "moduleParamRequest.h"
#include "appRequestFunction.h"

extern "C"{
#include "unicodestring.h"
};


void dvrToApp_SetDVRMenuEnable()
{
	setAnalogData(CONTROLID_MENU_DRIVING_RECORD,0);
	setControllable(CONTROLID_MENU_DRIVING_RECORD,true);
}

void dvrToApp_SetDVRMenuDisable()
{
	setAnalogData(CONTROLID_MENU_DRIVING_RECORD,2);
	setControllable(CONTROLID_MENU_DRIVING_RECORD,false);
}

void dvrToApp_SetDVR_RecordingDisPlay(u8 status)
{
	setDigitalData(CONTROLID_DRIVING_USB_CAREMA_RECORDING,status);
}

void HaveDVREquipment()
{
	LOGD("HaveDVREquipment m_iPresentMode:%x",pLocalParam->m_iPresentMode);
	Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);
	switch(pLocalParam->m_iPresentMode)
	{
		case VideoMode://¼��ģʽ
		{
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
			pLocalParam->bStopVideo = false;
		}
		break;
		case RePlayMode://�ط�ģʽ
		{
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
			pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_PALY;

			//edited by chengzihong 20140811
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_PALY);
		}
		break;
		case SetTimeMode://ʱ������ģʽ
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_TIME_SET);
			//edited by chengzihong 20140811
			pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_TIME_SET;
		break;
		case SetVideoMode://�˵�(��Ƶ)����ģʽ
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_SET);
			//edited by chengzihong 20140811
			pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_SET;
		break;
		default:break;
	}
	
	pLocalParam->bEnterDVRModuleMark = true;
	
}


//PAGE_DRIVING_RECORD_MENU  	0x4001
void appToDvr_Return_Button_MouseUp()
{
	LOGD("appToDvr_Return_Button_MouseUp bDVRModuleState:%x",pLocalParam->bDVRModuleState);
	if(!pLocalParam->bDVRModuleState){
		dvrToApp_SetDVRMenuDisable();
	}
	dvrToModule_NotifySystem_JumpPage(PAGE_MENU);
	pLocalParam->m_wCurrentPage = PAGE_MENU;
	pLocalParam->bEnterDVRModuleMark = false;
}

void appToDvr_Menu_Button_MouseUp()
{
	LOGD("pLocalParam->bIsChangHe:%d",pLocalParam->bIsChangHe);
	if(pLocalParam->bIsChangHe == 1)
	{
		if(getCurSysSetDvrProtocolModeStatus() == 1)
		{
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
			return;
		}
	}
	
	u8 u_IsDVRstate = 1;
	u8 u_IsDVRstatelen = 1;
	getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_IS_DVRORTV, (u8*)&u_IsDVRstate, &u_IsDVRstatelen);
	LOGD("appToDvr_Menu_Button_MouseUp pLocalParam->bDVRModuleState:%x u_IsDVRstate:%x",pLocalParam->bDVRModuleState,u_IsDVRstate);

	if(pLocalParam->bDVRModuleState && u_IsDVRstate == 0)
		HaveDVREquipment();
	else
	    dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_NO_SIGN);
	

}

void appToDvr_DVR_RECORD_VIDEO_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(DVR_RECORD);
}

void appToDvr_DVR_RECORD_MUTE_Button_MouseUp()
{
	LOGD("appToDvr_DVR_RECORD_MUTE_Button_MouseUp pLocalParam->bStopVideo:%x",pLocalParam->bStopVideo);
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	if(!pLocalParam->bStopVideo)
	{
		pLocalParam->bMute = !pLocalParam->bMute;
		Set_DVR_SoftWareImitateKeyCtrl(MUTE);
	}
}

void appToDvr_DVR_RECORD_TIME_SET_Button_MouseUp()
{
	//SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(TIME_SET);
	Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);	
	//edited by chengzihong 20140811
	 dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_TIME_SET);
	 pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_TIME_SET;
}

void appToDvr_DVR_RECORD_SET_Button_MouseUp()
{
	//SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(VIDEO_SET);
	Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);
	//edited by chengzihong 20140811
    dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_SET);
    pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_SET;
}

void appToDvr_DVR_RECORD_FOLDER_Button_MouseUp()
{
	//SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(FILE_PLAYBACK);
	Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);
	//edited by chengzihong 20140811
	dvrToModule_NotifySystem_JumpPage( PAGE_DRIVING_RECORD_PALY);
	pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_PALY;
}

void appToDvr_DVR_RECORD_CODE_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(LOCK_FILE);
}

void appToDvr_DVR_RECORD_BACKGROUND_Button_MouseUp()
{
	//DeleteTimer(DVR_OSD_TIMER_HIDDEN_DISPLAY);
	dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
}


//PAGE_DRIVING_RECORD_TIME_SET  	0x4002
void appToDvr_TIME_SET_BACK_Button_MouseUp()
{
	LOGD("appToDvr_TIME_SET_BACK_Button_MouseUp pLocalParam->bDVRModuleState:%x",pLocalParam->bDVRModuleState);
	//DeleteTimer(DVR_OSD_TIMER_HIDDEN_DISPLAY);
	if(!pLocalParam->bDVRModuleState){
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_NO_SIGN);
	}
	else{
		Set_DVR_SoftWareImitateKeyCtrl(SAVE_SET);//�ر�����
		Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
		//edited by chengzihong 20140808
		pLocalParam->m_wCurrentPage = PAGE_MENU;
	}

	pLocalParam->bStopVideo = true;
}

void appToDvr_TIME_SET_UP_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(UP);
}

void appToDvr_TIME_SET_DOWN_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(DOWN);
}

void appToDvr_TIME_SET_OK_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(SET_ENSURE);
}

void appToDvr_TIME_SET_SET_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_CurTime();
}

//PAGE_DRIVING_RECORD_SET	0x4003	
void appToDvr_SET_BACK_Button_MouseUp()
{
	LOGD("appToDvr_SET_BACK_Button_MouseUp bDVRModuleState:%x ",pLocalParam->bDVRModuleState);
	//DeleteTimer(DVR_OSD_TIMER_HIDDEN_DISPLAY);
	if(!pLocalParam->bDVRModuleState){
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_NO_SIGN);
	}
	else{
		Set_DVR_SoftWareImitateKeyCtrl(SAVE_SET);//�ر�����
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
		//edited by chengzihong 20140811
		pLocalParam->m_wCurrentPage = PAGE_MENU;
	}

	pLocalParam->bStopVideo = true;

}

void appToDvr_SET_UP_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(DOWN);
}

void appToDvr_SET_DOWN_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(UP);
}

void appToDvr_SET_SURE_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(SET_ENSURE);
}

void appToDvr_PALY_UP_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(PREV);
	pLocalParam->bPlayOrPause = !pLocalParam->bPlayOrPause;
}

void appToDvr_PALY_PLAY_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(PLAY);
	pLocalParam->bPlayOrPause = false;
}

void appToDvr_PALY_NEXT_Button_MouseUp()
{
	SetTimer(TIME_5S,0,DVR_OSD_TIMER_HIDDEN_DISPLAY);	// 5000ms
	Set_DVR_SoftWareImitateKeyCtrl(NEXT);
	pLocalParam->bPlayOrPause = false;
}

void appToDvr_PALY_CODE_Button_MouseUp()
{
	Set_DVR_SoftWareImitateKeyCtrl(LOCK_FILE);
}

void appToDvr_PALY_BACK_Button_MouseUp()
{
	LOGD("appToDvr_PALY_BACK_Button_MouseUp  bDVRModuleState:%x",pLocalParam->bDVRModuleState);
	//DeleteTimer(DVR_OSD_TIMER_HIDDEN_DISPLAY);
	if(!pLocalParam->bDVRModuleState){
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_NO_SIGN);
	}
	else{
		Set_DVR_SoftWareImitateKeyCtrl(BACK2RECORD);
		Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
		//edited by chengzihong 20140811
		pLocalParam->m_wCurrentPage = PAGE_MENU;
	}

	pLocalParam->bStopVideo = true;
}

void appToDvr_PLAY_BACKGROUND_Button_MouseUp()
{
	dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
	pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_PALY;
}


void appToDvr_VIDEO_BACKGROUND_Button_MouseUp()
{
	if(pLocalParam->bIsChangHe == 1)
	{
		if(pLocalParam->uDvrModule_is_T123 == 1)
		{
			if(getCurSysSetDvrProtocolModeStatus() == 1)
			{
				dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_CHANGHE_DVR_SET_OSD);
				return;
			}
		}
	}
	
	//DeleteTimer(DVR_OSD_TIMER_HIDDEN_DISPLAY);
	LOGD("appToDvr_VIDEO_BACKGROUND_Button_MouseUp pLocalParam->m_wCurrentPage:%x",pLocalParam->m_wCurrentPage);
	if(pLocalParam->m_wCurrentPage == PAGE_DRIVING_RECORD_PALY){
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_PALY);
	}
	else if(pLocalParam->m_wCurrentPage == PAGE_DRIVING_RECORD_SET)
	{
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_SET);
	}
	else if(pLocalParam->m_wCurrentPage == PAGE_DRIVING_RECORD_TIME_SET)
	{
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_TIME_SET);
	}
	else{
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_MENU);
	}
}

void appToDvr_VIDEO_NoSign_Back_Button_MouseUp()
{
	if(!pLocalParam->bDVRModuleState){
		dvrToApp_SetDVRMenuDisable();
	}
	dvrToModule_NotifySystem_JumpPage(PAGE_MENU);
	pLocalParam->m_wCurrentPage = PAGE_MENU;
	pLocalParam->bEnterDVRModuleMark = false;
}


void appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_menu(int ctrlId,u8 ctrlType)
{
      u8 swtich_button=0;
      u8 button_status=0xff;
     
      switch(ctrlId){
      	case CONTROLIDTRAVEL_DRIVING_RECORD_MENU_BACK:
      		swtich_button=0x01;
			break;
        case CONTROLIDTRAVEL_DRIVING_RECORD_MUTE:
        	swtich_button=0x03;
			break;     	
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET:
			swtich_button=0x4;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_FOLDER:
			swtich_button=0x05;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET:
			swtich_button=0x07;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_CODE://LOCK
			swtich_button=0x06;
		    break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_VIDEO://¼��
			swtich_button=0x02;
		    break;
          default:
		  	return;
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
        dvrToModule_NotifyOSD_aboutT123_VideoOSD_dvrMenu_Button(swtich_button,button_status);

}

void appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_videoset(int ctrlId,u8 ctrlType)
{
    u8 swtich_button=0;
    u8 button_status=0xff;
    
    switch(ctrlId){ 
    case CONTROLIDTRAVEL_DRIVING_RECORD_SET_UP:
    	    swtich_button = 0x02;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET_DOWN:
			swtich_button = 0x03;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET_SURE:
			swtich_button = 0x04;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_SET_BACK:
			swtich_button = 0x01;
			break;
        default:
			return;
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
     
    dvrToModule_NotifyOSD_aboutT123_VideoOSD_videoset_Button(swtich_button,button_status);

}

void appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_folderplay(int ctrlId,u8 ctrlType)
{
    u8 swtich_button=0;
    u8 button_status=0xff;
    
    switch(ctrlId){ 
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_UP:
			swtich_button = 0x02;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_PLAY:
			swtich_button = 0x03;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_NEXT:
			swtich_button = 0x04;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_CODE:
			swtich_button = 0x05;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_PLAY_BACK:
			swtich_button = 0x01;
			break;
        default:
			return;
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
      dvrToModule_NotifyOSD_aboutT123_VideoOSD_recordPlay_Button(swtich_button,button_status);

}

void appToDVR_VideoOSD_ButtonMessageToT123ChipLocation_timeset(int ctrlId,u8 ctrlType)
{
    u8 swtich_button=0;
    u8 button_status=0xff;
    
    switch(ctrlId){ 
    		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_UP:
    			swtich_button = 0x02;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_DOWN:
			swtich_button = 0x03;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_OK:
			swtich_button = 0x04;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_SET:
			swtich_button = 0x05;
			break;
		case CONTROLIDTRAVEL_DRIVING_RECORD_TIME_SET_BACK:
			swtich_button = 0x01;
			break;
        default:
			return;
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
      dvrToModule_NotifyOSD_aboutT123_VideoOSD_timeset_Button(swtich_button,button_status);

}

void appToDvr_Menu_Button_Camera_MouseUp()
{
		u8 u_IsCvbsOrUsbstate = 0;
		u8 u_IsCvbsOrUsblen = 1;
		getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_CVBS_OR_USB_SWITCH, (u8*)&u_IsCvbsOrUsbstate, &u_IsCvbsOrUsblen);
		if(u_IsCvbsOrUsbstate == 1)
		{
			dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_NO_SUPPORT_USB_CAMERA);
		}
		else
		{
			if(pLocalParam->emUsbCameraIsExistDevice == CAMERA_NO_DEVICE)
			{
				dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_NO_SIGN);
			}
			else
			{
				dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
			}
		}
}

void appToDvr_Menu_Button_Camera_Recording()
{
   if(pLocalParam->bCurIsUsbCameraRecording == false)
   	{
   		pLocalParam->bCurIsUsbCameraRecording = 1;
		SetToHal_DVR_USB_Carema_Recording(0x01);
   	}
   else if(pLocalParam->bCurIsUsbCameraRecording == true)
   	{
   		pLocalParam->bCurIsUsbCameraRecording = 0;
		SetToHal_DVR_USB_Carema_Recording(0x00);
   	}

	/*
   if(pLocalParam->emDvrUsbCameraWhichRoad == USB_CAMERA_WHICH_ROAD_SINGLE && pLocalParam->uIdIsDevice_F == CAMERA_NO_DEVICE)
   	{
   		dvr_NotifyApp_SdCard_State(0x01,0x01);
   	}
   else if(pLocalParam->emDvrUsbCameraWhichRoad == USB_CAMERA_WHICH_ROAD_DOUBLE && (pLocalParam->uIdIsDevice_F == CAMERA_NO_DEVICE || pLocalParam->uIdIsDevice_R == CAMERA_NO_DEVICE))
   	{
   		dvr_NotifyApp_SdCard_State(0x01,0x01);
   	}
   	*/

	dvrToApp_SetDVR_RecordingDisPlay(pLocalParam->bCurIsUsbCameraRecording);
}

void appToDvr_Menu_Button_Camera_Photograph()
{
	SetToHal_DVR_USB_Carema_Photograph();
}

void appToDvr_Menu_Button_UsbCamera_YMD(u8 y, u8 month, u8 d)
{
	char param[20] = {0};
	char szUnicodeBuf[50] = {0};
	sprintf(param, "%04d/%02d/%02d",y,month,d);
	int len =	ansi_str_to_unicode16((u8*)param,(unicode16_t*)szUnicodeBuf);
		
	setSerialData(0x400107 ,(u8*)szUnicodeBuf,2*len);
}

void appToDvr_Menu_Button_UsbCamera_HMS(u8 h, u8 m, u8 s)
{
	char param[20] = {0};
	char szUnicodeBuf[50] = {0};
	sprintf(param, "%02d:%02d:%02d",h,m,s);
	int len =	ansi_str_to_unicode16((u8*)param,(unicode16_t*)szUnicodeBuf);
		
	setSerialData(0x400108 ,(u8*)szUnicodeBuf,2*len);
}

void appToDvr_UsbCameraVersion(u8 uId,u8 *param,u8 len)
{
	//if(uId == 0x00)return;
	
	LOGD("[%s] param:%s",__FUNCTION__,param+1);
	u8 *pAnsicBuf = (u8*)malloc(len+1-1);
	memset(pAnsicBuf, 0, len+1-1);
	memcpy(pAnsicBuf, param+1, len);
	u8 *pUnicodeBuf = (u8*)malloc((len-1)*2+2);
	memset(pUnicodeBuf, 0, (len-1)*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(pAnsicBuf, (unicode16_t*)pUnicodeBuf);
	setSerialData(CONTROLID_DRIVING_USB_CAREMA_SET_VERSION_INFO_TEXT,pUnicodeBuf,nUnicodeBufLen*2);
	free(pAnsicBuf);
	free(pUnicodeBuf);
}

void setAnsiSerialData(u32 id, u8 *p, u32 len)
{
	u32 dwAnsiBufLen = strlen((char*)p);
	u8 *pUnicodeBuf = (u8*)malloc(dwAnsiBufLen * 2 + 2);
	memset(pUnicodeBuf, 0, dwAnsiBufLen * 2 + 2);
	u32 dwUnicodeBufLen = ansi_str_to_unicode16(p, (unsigned short*)pUnicodeBuf);
	setSerialData(id, pUnicodeBuf, dwUnicodeBufLen * 2);
	free(pUnicodeBuf);
}

void appToDvr_DVR_RECORD_SET_Button_Camera_MouseUp()
{
	dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_USB_CAMERA_SET);
}

void UI_Usb_Camera_Resolution(E_DVR_USB_CAMERA_RESOLUTION em)
{
	int nMap[SIZE_MAP_MAXLEN] = {0};
	//nMap[DVR_USB_CAMERA_RESOLUTION_480X272P] = ;
	nMap[DVR_USB_CAMERA_RESOLUTION_1280X720P] = STRING_DRIVING_USB_CAREMA_SET_RESOLUTION_720P;
	nMap[DVR_USB_CAMERA_RESOLUTION_1920X1080P] = STRING_DRIVING_USB_CAREMA_SET_RESOLUTION_1080P;
	//nMap[DVR_USB_CAMERA_RESOLUTION_640X480P] = ;
	//nMap[DVR_USB_CAMERA_RESOLUTION_640X360P] = ;
	//nMap[DVR_USB_CAMERA_RESOLUTION_400X480P] = ;
	//nMap[DVR_USB_CAMERA_RESOLUTION_320X240P] = ;
	if (em < SIZE_MAP_MAXLEN)
		setStringText(CONTROLID_DRIVING_USB_CAREMA_SET_RESOLUTION_TEXT, nMap[em]);
}

void UI_Usb_Camera_Recording_Times(E_DVR_USB_CAMERA_RECORDING_TIMES em)
{
	int nMap[SIZE_MAP_MAXLEN] = {0};
	nMap[CAMERA_RECORDING_TIMES_2M] = STRING_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_2MIN;
	nMap[CAMERA_RECORDING_TIMES_3M] = STRING_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_3MIN;
	nMap[CAMERA_RECORDING_TIMES_5M] = STRING_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_5MIN;
	nMap[CAMERA_RECORDING_TIMES_10M] = STRING_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_10MIN;
	if (em < SIZE_MAP_MAXLEN)
		setStringText(CONTROLID_DRIVING_USB_CAREMA_SET_RECORDING_TIMES_TEXT, nMap[em]);
}

void UI_Usb_Camera_Storage_Size(E_DVR_USB_CAMERA_STORAGE_SIZE em)
{
	int nMap[SIZE_MAP_MAXLEN] = {0};
	nMap[CAMERA_STORAGE_SIZE_2G] = STRING_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_2G;
	nMap[CAMERA_STORAGE_SIZE_4G] = STRING_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_4G;
	nMap[CAMERA_STORAGE_SIZE_8G] = STRING_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_8G;
	nMap[CAMERA_STORAGE_SIZE_16G] = STRING_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_16G;
	if (em < SIZE_MAP_MAXLEN)
		setStringText(CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_SIZE_TEXT, nMap[em]);
}

void UI_Usb_Camera_ApplyButton_IsControllable(bool bState)
{
	if(bState)
	{
		setAnalogData(CONTROLID_DRIVING_USB_CAREMA_SETTING_APPLY, 0);
		setControllable(CONTROLID_DRIVING_USB_CAREMA_SETTING_APPLY, 1);
	}
	else{
		setAnalogData(CONTROLID_DRIVING_USB_CAREMA_SETTING_APPLY, 2);
		setControllable(CONTROLID_DRIVING_USB_CAREMA_SETTING_APPLY, 0);
	}
}

void DisplayUI_Usb_Camera_Storage_Path(u8 *param,int len)
{
	LOGD("[%s] param=%s len:%d",__FUNCTION__,param,len);
	setAnsiSerialData(CONTROLID_DRIVING_USB_CAREMA_SET_STORAGE_PATH_TEXT, (u8*)param, len);
}

void appToDvr_Usb_Camera_Set_Resolution_Button(u8 param)
{
	E_DVR_USB_CAMERA_RESOLUTION emTempResolution = (E_DVR_USB_CAMERA_RESOLUTION)pLocalParam->m_iUsbCameraSettingParam[0];

	
	if(emTempResolution == DVR_USB_CAMERA_RESOLUTION_1280X720P){
		emTempResolution = DVR_USB_CAMERA_RESOLUTION_1920X1080P;
	}
	else if(emTempResolution == DVR_USB_CAMERA_RESOLUTION_1920X1080P){
		emTempResolution = DVR_USB_CAMERA_RESOLUTION_1280X720P;
	}

	if(emTempResolution > 2 || emTempResolution == 0)
		emTempResolution = DVR_USB_CAMERA_RESOLUTION_1280X720P;

	

	/*
	LOGD("pLocalParam->nDvrIsSupportResolutionsCounts:%d",pLocalParam->nDvrIsSupportResolutionsCounts);
	if(pLocalParam->nDvrIsSupportResolutionsCounts <= 1)
		return;
	
	for(int n = 0;n < pLocalParam->nDvrIsSupportResolutionsCounts;n++)
	{
		if(pLocalParam->uDvrIsSupportResolutions[n] == (u8)emTempResolution)
		{
			if(param == 0)
			{
				if(n == 0)
				{
					emTempResolution = (E_DVR_USB_CAMERA_RESOLUTION)pLocalParam->uDvrIsSupportResolutions[pLocalParam->nDvrIsSupportResolutionsCounts - 1];
				}
				else
				{
					emTempResolution = (E_DVR_USB_CAMERA_RESOLUTION)pLocalParam->uDvrIsSupportResolutions[n-1];
				}
			}
			else if(param == 1)
			{
				if(n == (pLocalParam->nDvrIsSupportResolutionsCounts - 1))
				{
					emTempResolution = (E_DVR_USB_CAMERA_RESOLUTION)pLocalParam->uDvrIsSupportResolutions[0];
				}
				else
				{
					emTempResolution = (E_DVR_USB_CAMERA_RESOLUTION)pLocalParam->uDvrIsSupportResolutions[n+1];
				}
			}
			break;
		}
	}*/
	
	LOGD("emTempResolution:%d",emTempResolution);

	UI_Usb_Camera_Resolution(emTempResolution);

	pLocalParam->m_iUsbCameraSettingParam[0] = (int)emTempResolution;
		
	UI_Usb_Camera_ApplyButton_IsControllable(true);
}

void appToDvr_Usb_Camera_Set_RecordingTimes_Button(u8 param)
{
	E_DVR_USB_CAMERA_RECORDING_TIMES emTempRecordingTimes = (E_DVR_USB_CAMERA_RECORDING_TIMES)pLocalParam->m_iUsbCameraSettingParam[1]; 
	
	if((E_SELECT_CTRL)param == SELECT_CTRL_UP)
	{
		if(emTempRecordingTimes == CAMERA_RECORDING_TIMES_2M)
		{
			//emTempRecordingTimes = CAMERA_RECORDING_TIMES_10M;
			emTempRecordingTimes = CAMERA_RECORDING_TIMES_5M;
		}
		else if(emTempRecordingTimes == CAMERA_RECORDING_TIMES_10M)
		{
			emTempRecordingTimes = CAMERA_RECORDING_TIMES_5M;
		}
		else if(emTempRecordingTimes == CAMERA_RECORDING_TIMES_5M)
		{
			emTempRecordingTimes = CAMERA_RECORDING_TIMES_3M;
		}
		else if(emTempRecordingTimes == CAMERA_RECORDING_TIMES_3M)
		{
			emTempRecordingTimes = CAMERA_RECORDING_TIMES_2M;
		}
	}
	else if((E_SELECT_CTRL)param == SELECT_CTRL_DOWN)
	{
		if(emTempRecordingTimes == CAMERA_RECORDING_TIMES_2M)
		{
			emTempRecordingTimes = CAMERA_RECORDING_TIMES_3M;
		}
		else if(emTempRecordingTimes == CAMERA_RECORDING_TIMES_3M)
		{
			emTempRecordingTimes = CAMERA_RECORDING_TIMES_5M;
		}
		else if(emTempRecordingTimes == CAMERA_RECORDING_TIMES_5M)
		{
			//emTempRecordingTimes = CAMERA_RECORDING_TIMES_10M;
			emTempRecordingTimes = CAMERA_RECORDING_TIMES_2M;
		}
		else if(emTempRecordingTimes == CAMERA_RECORDING_TIMES_10M)
		{
			emTempRecordingTimes = CAMERA_RECORDING_TIMES_2M;
		}
	}

	if(emTempRecordingTimes == 0)
		emTempRecordingTimes = CAMERA_RECORDING_TIMES_5M;

	pLocalParam->m_iUsbCameraSettingParam[1] = (int)emTempRecordingTimes;
	LOGD("emTempRecordingTimes:%d",emTempRecordingTimes);
	
	UI_Usb_Camera_Recording_Times(emTempRecordingTimes);

	UI_Usb_Camera_ApplyButton_IsControllable(true);
}

void appToDvr_Usb_Camera_Set_StorageSize_Button(u8 param)
{
	E_DVR_USB_CAMERA_STORAGE_SIZE emTempStorageSize = (E_DVR_USB_CAMERA_STORAGE_SIZE)pLocalParam->m_iUsbCameraSettingParam[2];
	if((E_SELECT_CTRL)param == SELECT_CTRL_UP)
	{
		if(emTempStorageSize == CAMERA_STORAGE_SIZE_2G)
		{
			emTempStorageSize = CAMERA_STORAGE_SIZE_16G;
		}
		else if(emTempStorageSize == CAMERA_STORAGE_SIZE_16G)
		{
			emTempStorageSize = CAMERA_STORAGE_SIZE_8G;
		}
		else if(emTempStorageSize == CAMERA_STORAGE_SIZE_8G)
		{
			emTempStorageSize = CAMERA_STORAGE_SIZE_4G;
		}
		else if(emTempStorageSize == CAMERA_STORAGE_SIZE_4G)
		{
			emTempStorageSize = CAMERA_STORAGE_SIZE_2G;
		}
	}
	else if((E_SELECT_CTRL)param == SELECT_CTRL_DOWN)
	{
		if(emTempStorageSize == CAMERA_STORAGE_SIZE_2G)
		{
			emTempStorageSize = CAMERA_STORAGE_SIZE_4G;
		}
		else if(emTempStorageSize == CAMERA_STORAGE_SIZE_4G)
		{
			emTempStorageSize = CAMERA_STORAGE_SIZE_8G;
		}
		else if(emTempStorageSize == CAMERA_STORAGE_SIZE_8G)
		{
			emTempStorageSize = CAMERA_STORAGE_SIZE_16G;
		}
		else if(emTempStorageSize == CAMERA_STORAGE_SIZE_16G)
		{
			emTempStorageSize = CAMERA_STORAGE_SIZE_2G;
		}
	}

	if(emTempStorageSize == 0)
		emTempStorageSize = CAMERA_STORAGE_SIZE_4G;
	
	pLocalParam->m_iUsbCameraSettingParam[2] = (int)emTempStorageSize;
	LOGD("emTempStorageSize:%d",emTempStorageSize);
	
	UI_Usb_Camera_Storage_Size(emTempStorageSize);

	UI_Usb_Camera_ApplyButton_IsControllable(true);
}

void appToDvr_Usb_Camera_Set_StoragePath_Button(u8 param)
{
	E_DVR_USB_CAMERA_STORAGE_PATH emTempStoragePath = (E_DVR_USB_CAMERA_STORAGE_PATH)pLocalParam->m_iUsbCameraSettingParam[3];
	
	if(emTempStoragePath == CAMERA_STORAGE_PATH_SDCARD)
	{
		emTempStoragePath = CAMERA_STORAGE_PATH_FLASH;
	}
	else if(emTempStoragePath == CAMERA_STORAGE_PATH_FLASH)
	{
		emTempStoragePath = CAMERA_STORAGE_PATH_SDCARD;
	}

	pLocalParam->m_iUsbCameraSettingParam[3] = (int)emTempStoragePath;

	UI_Usb_Camera_Storage_Path(emTempStoragePath);

	UI_Usb_Camera_ApplyButton_IsControllable(true);
}

void appToDvr_Usb_Camera_Setting_Apply()
{
	//UsbCameraParamVariable_Temp_To_Real();
	applyUsbCaremaDataToDevice();
	//UI_Usb_Camera_Show_Setting_Info();
}

void UsbCameraParamVariable_Temp_To_Real()
{
	pLocalParam->emUsbCameraResolution = (E_DVR_USB_CAMERA_RESOLUTION)pLocalParam->m_iUsbCameraSettingParam[0];
	pLocalParam->emUsbCameraRecordingTimes = (E_DVR_USB_CAMERA_RECORDING_TIMES)pLocalParam->m_iUsbCameraSettingParam[1];
	pLocalParam->emUsbCameraStorageSize = (E_DVR_USB_CAMERA_STORAGE_SIZE)pLocalParam->m_iUsbCameraSettingParam[2];
	pLocalParam->emUsbCameraStoragePath = (E_DVR_USB_CAMERA_STORAGE_PATH)pLocalParam->m_iUsbCameraSettingParam[3];
	pLocalParam->emDvrUsbCameraWhichRoad = (E_DVR_USB_CAMERA_WHICH_ROAD)pLocalParam->m_iUsbCameraSettingParam[4];
}

void UsbCameraParamVariable_Real_To_Temp()
{
	LOGD("UsbCameraParamVariable_Real_To_Temp%d %d",pLocalParam->emUsbCameraResolution,pLocalParam->m_iUsbCameraSettingParam[0]);
	pLocalParam->m_iUsbCameraSettingParam[0] = (int)pLocalParam->emUsbCameraResolution;
	pLocalParam->m_iUsbCameraSettingParam[1] = (int)pLocalParam->emUsbCameraRecordingTimes;
	pLocalParam->m_iUsbCameraSettingParam[2] = (int)pLocalParam->emUsbCameraStorageSize;
	pLocalParam->m_iUsbCameraSettingParam[3] = (int)pLocalParam->emUsbCameraStoragePath;
	pLocalParam->m_iUsbCameraSettingParam[4] = (int)pLocalParam->emDvrUsbCameraWhichRoad;
}

void UI_Usb_Camera_Show_Setting_Info()
{
	UI_Usb_Camera_ApplyButton_IsControllable(false);

	UI_Usb_Camera_Resolution(pLocalParam->emUsbCameraResolution);
	UI_Usb_Camera_Recording_Times(pLocalParam->emUsbCameraRecordingTimes);
	UI_Usb_Camera_Storage_Size(pLocalParam->emUsbCameraStorageSize);
	UI_Usb_Camera_Storage_Path(pLocalParam->emUsbCameraStoragePath);
	UI_Usb_Camera_Mono_Road(pLocalParam->emDvrUsbCameraWhichRoad);
}

void UI_Usb_Camera_Storage_Path(E_DVR_USB_CAMERA_STORAGE_PATH em)
{
	char szMsg[PATH_STRING_MAX_LEN];
	memset(szMsg,0,sizeof(szMsg));
	
	UsbCameraParam_StorageFilePath_EM_To_String(em,szMsg);
	//TEST
	//if(szMsg == NULL)
	if(szMsg[0] == '/0')
		return;

	DisplayUI_Usb_Camera_Storage_Path((u8*)szMsg,strlen(szMsg));
}

E_DVR_USB_CAMERA_STORAGE_PATH UsbCameraParam_StorageFilePath_String_To_EM(char *str)
{
	E_DVR_USB_CAMERA_STORAGE_PATH uCmd = (E_DVR_USB_CAMERA_STORAGE_PATH)0xFF;
	if(strcmp(str,DVR_USB_CAMERA_FILE_PATH_FLASH) == 0)
	{
		uCmd = CAMERA_STORAGE_PATH_FLASH;
	}
	else if(strcmp(str,DVR_USB_CAMERA_FILE_PATH_SDCARD) == 0)
	{
		uCmd = CAMERA_STORAGE_PATH_SDCARD;
	}

	return uCmd;
}

void UsbCameraParam_StorageFilePath_EM_To_String(E_DVR_USB_CAMERA_STORAGE_PATH em,char *str)
{
	char szMsg[PATH_STRING_MAX_LEN] = {0};
	memset(szMsg,0,sizeof(szMsg));
	
	switch(em)
	{
		case CAMERA_STORAGE_PATH_SDCARD:
			sprintf(szMsg, "%s", DVR_USB_CAMERA_FILE_PATH_SDCARD);
			break;
		case CAMERA_STORAGE_PATH_FLASH:
			sprintf(szMsg, "%s", DVR_USB_CAMERA_FILE_PATH_FLASH);
			break;
	}
	

	LOGD("[%s] Storage File Path string:%s",__FUNCTION__,szMsg);
	memcpy(str,szMsg,strlen(szMsg));
}

E_DVR_USB_CAMERA_RESOLUTION UsbCameraParam_Resolution_String_To_EM(u8 *str)
{
	E_DVR_USB_CAMERA_RESOLUTION em_TemParam = (E_DVR_USB_CAMERA_RESOLUTION)0xFF;

	if(strcmp((char*)(str),STRING_CAMERA_RESOLUTION_480X272P) == 0)
	{
		em_TemParam = DVR_USB_CAMERA_RESOLUTION_480X272P;
	}
	else if(strcmp((char*)(str),STRING_CAMERA_RESOLUTION_1280X720P) == 0)
	{
		em_TemParam = DVR_USB_CAMERA_RESOLUTION_1280X720P;
	}
	else if(strcmp((char*)(str),STRING_CAMERA_RESOLUTION_1920X1080P) == 0)
	{
		em_TemParam = DVR_USB_CAMERA_RESOLUTION_1920X1080P;
	}
	else if(strcmp((char*)(str),STRING_CAMERA_RESOLUTION_640X480P) == 0)
	{
		em_TemParam = DVR_USB_CAMERA_RESOLUTION_640X480P;
	}
	else if(strcmp((char*)(str),STRING_CAMERA_RESOLUTION_640X360P) == 0)
	{
		em_TemParam = DVR_USB_CAMERA_RESOLUTION_640X360P;
	}
	else if(strcmp((char*)(str),STRING_CAMERA_RESOLUTION_400X480P) == 0)
	{
		em_TemParam = DVR_USB_CAMERA_RESOLUTION_400X480P;
	}
	else if(strcmp((char*)(str),STRING_CAMERA_RESOLUTION_320X240P) == 0)
	{
		em_TemParam = DVR_USB_CAMERA_RESOLUTION_320X240P;
	}
	
	return em_TemParam;
}


void UsbCameraParam_Resolution_EM_To_String(E_DVR_USB_CAMERA_RESOLUTION em,char *str)
{
	char szMsg[STRING_MAX_LEN] = {0};
	memset(szMsg,0,sizeof(szMsg));

	switch(em)
	{
		case DVR_USB_CAMERA_RESOLUTION_480X272P:
			sprintf(szMsg, "%s", STRING_CAMERA_RESOLUTION_480X272P);
		break;
		case DVR_USB_CAMERA_RESOLUTION_1280X720P:
			sprintf(szMsg, "%s", STRING_CAMERA_RESOLUTION_1280X720P);
		break;
		case DVR_USB_CAMERA_RESOLUTION_1920X1080P:
			sprintf(szMsg, "%s", STRING_CAMERA_RESOLUTION_1920X1080P);
		break;
		case DVR_USB_CAMERA_RESOLUTION_640X480P:
			sprintf(szMsg, "%s", STRING_CAMERA_RESOLUTION_640X480P);
		break;
		case DVR_USB_CAMERA_RESOLUTION_640X360P:
			sprintf(szMsg, "%s", STRING_CAMERA_RESOLUTION_640X360P);
		break;
		case DVR_USB_CAMERA_RESOLUTION_400X480P:
			sprintf(szMsg, "%s", STRING_CAMERA_RESOLUTION_400X480P);
		break;
		case DVR_USB_CAMERA_RESOLUTION_320X240P:
			sprintf(szMsg, "%s", STRING_CAMERA_RESOLUTION_320X240P);
		break;
	}

	LOGD("[%s] Resolution strings:%s",__FUNCTION__,szMsg);

	memcpy(str,szMsg,strlen(szMsg));
}

void ToHal_DVR_USB_Carema_Resolution(E_DVR_USB_CAMERA_RESOLUTION em)
{
	char szMsg[STRING_MAX_LEN] = {0};
	memset(szMsg,0,sizeof(szMsg));

	UsbCameraParam_Resolution_EM_To_String(em,szMsg);
	SetToHal_DVR_USB_Carema_SetResolution(szMsg);
}

void ToHal_DVR_USB_Carema_StorageFilePath(E_DVR_USB_CAMERA_STORAGE_PATH em)
{
	char cTem[PATH_STRING_MAX_LEN];
	memset(cTem,0,sizeof(cTem));
	
	UsbCameraParam_StorageFilePath_EM_To_String(em,cTem);
	SetToHal_DVR_USB_Carema_SetStoragePath((u8*)cTem,strlen(cTem));
}

void applyUsbCaremaDataToDevice()
{
	//ToHal_DVR_USB_Carema_Resolution(pLocalParam->emUsbCameraResolution);
	//SetToHal_DVR_USB_Carema_SetRecordingTimes((u16)(pLocalParam->emUsbCameraRecordingTimes)*60);
	//SetToHal_DVR_USB_Carema_SetStorageSize((u32)(pLocalParam->emUsbCameraStorageSize)*1024);
	//ToHal_DVR_USB_Carema_StorageFilePath(pLocalParam->emUsbCameraStoragePath);
	//ToHal_DVR_USB_Carema_WhichOne_Road_Recording(pLocalParam->emDvrUsbCameraWhichRoad);

	ToHal_DVR_USB_Carema_Resolution((E_DVR_USB_CAMERA_RESOLUTION)pLocalParam->m_iUsbCameraSettingParam[0]);
	SetToHal_DVR_USB_Carema_SetRecordingTimes((u16)pLocalParam->m_iUsbCameraSettingParam[1]*60);
	SetToHal_DVR_USB_Carema_SetStorageSize((u32)pLocalParam->m_iUsbCameraSettingParam[2]*1024);
	ToHal_DVR_USB_Carema_StorageFilePath((E_DVR_USB_CAMERA_STORAGE_PATH)pLocalParam->m_iUsbCameraSettingParam[3]);
	ToHal_DVR_USB_Carema_WhichOne_Road_Recording((E_DVR_USB_CAMERA_WHICH_ROAD)pLocalParam->m_iUsbCameraSettingParam[4]);

	UI_Usb_Camera_ApplyButton_IsControllable(false);

	SetToHal_DVR_USB_CaremaParamEnd();
}

static 	u8 uUsbCameraVideoParam_Color[][2] = {
		{0,12},
		{1,24},
		{2,36},	
		{3,48},	
		{4,60},	
		{5,72},
		{6,84},
		{7,96},
		{8,108},	
		{9,120},	
		{10,128}
};

static 	u8 uUsbCameraVideoParam_Chrominance[][2] = {
		{0,7},
		{1,14},
		{2,21},	
		{3,28},	
		{4,35},	
		{5,42},
		{6,49},
		{7,56},
		{8,63},	
		{9,70},	
		{10,80}
};

static 	u8 uUsbCameraVideoParam_Brightness[][2] = {
		{0,12},
		{1,24},
		{2,36},	
		{3,48},	
		{4,60},	
		{5,72},
		{6,84},
		{7,96},
		{8,108},	
		{9,120},	
		{10,128}
};

static 	u8 uUsbCameraVideoParam_ContrastGauge[][2] = {
		{0,4},
		{1,10},
		{2,16},	
		{3,22},	
		{4,28},	
		{5,34},
		{6,40},
		{7,46},
		{8,52},	
		{9,58},	
		{10,64}
};

bool UsbCamera_SetVideoParam_Level_To_Data(E_DVR_USB_CAMERA_SET_VIDEO_TPYE emType,u8 uInLevel,u8 *uOutTemData)
{
	int i=0;
	int nCount = 0;

	switch(emType)
	{
		case TPYE_VIDEO_COLOR:
		{
			nCount = (sizeof(uUsbCameraVideoParam_Color)/sizeof(uUsbCameraVideoParam_Color[0]));
			for(i=0;i < nCount;i++)
			{
				if (uUsbCameraVideoParam_Color[i][0] == uInLevel)
				{
					*uOutTemData = uUsbCameraVideoParam_Color[i][1];
					return true;
				}
			}
		}
		break;
		case TPYE_VIDEO_CHROMINANCE:
		{
			nCount = (sizeof(uUsbCameraVideoParam_Chrominance)/sizeof(uUsbCameraVideoParam_Chrominance[0]));
			for(i=0;i < nCount;i++)
			{
				if (uUsbCameraVideoParam_Chrominance[i][0] == uInLevel)
				{
					*uOutTemData = uUsbCameraVideoParam_Chrominance[i][1];
					return true;
				}
			}
		}
		break;
		case TPYE_VIDEO_BRIGHTNESS:
		{
			nCount = (sizeof(uUsbCameraVideoParam_Brightness)/sizeof(uUsbCameraVideoParam_Brightness[0]));
			for(i=0;i < nCount;i++)
			{
				if (uUsbCameraVideoParam_Brightness[i][0] == uInLevel)
				{
					*uOutTemData = uUsbCameraVideoParam_Brightness[i][1];
					return true;
				}
			}
		}
		break;
		case TPYE_VIDEO_CONTRAST_GAUGE:
		{
			nCount = (sizeof(uUsbCameraVideoParam_ContrastGauge)/sizeof(uUsbCameraVideoParam_ContrastGauge[0]));
			for(i=0;i < nCount;i++)
			{
				if (uUsbCameraVideoParam_ContrastGauge[i][0] == uInLevel)
				{
					*uOutTemData = uUsbCameraVideoParam_ContrastGauge[i][1];
					return true;
				}
			}
		}
		break;
	}

	return false;
}

bool UsbCamera_SetVideoParam_Data_To_Level(E_DVR_USB_CAMERA_SET_VIDEO_TPYE emType,u8 uInData,u8 *uOutLevel)
{
	int i=0;
	int nCount = 0;

	switch(emType)
	{
		case TPYE_VIDEO_COLOR:
		{
			nCount = (sizeof(uUsbCameraVideoParam_Color)/sizeof(uUsbCameraVideoParam_Color[0]));
			for(i=0;i < nCount;i++)
			{
				if (uUsbCameraVideoParam_Color[i][1] == uInData)
				{
					*uOutLevel = uUsbCameraVideoParam_Color[i][0];
					return true;
				}
			}
		}
		break;
		case TPYE_VIDEO_CHROMINANCE:
		{
			nCount = (sizeof(uUsbCameraVideoParam_Chrominance)/sizeof(uUsbCameraVideoParam_Chrominance[0]));
			for(i=0;i < nCount;i++)
			{
				if (uUsbCameraVideoParam_Chrominance[i][1] == uInData)
				{
					*uOutLevel = uUsbCameraVideoParam_Chrominance[i][0];
					return true;
				}
			}
		}
		break;
		case TPYE_VIDEO_BRIGHTNESS:
		{
			nCount = (sizeof(uUsbCameraVideoParam_Brightness)/sizeof(uUsbCameraVideoParam_Brightness[0]));
			for(i=0;i < nCount;i++)
			{
				if (uUsbCameraVideoParam_Brightness[i][1] == uInData)
				{
					*uOutLevel = uUsbCameraVideoParam_Brightness[i][0];
					return true;
				}
			}
		}
		break;
		case TPYE_VIDEO_CONTRAST_GAUGE:
		{
			nCount = (sizeof(uUsbCameraVideoParam_ContrastGauge)/sizeof(uUsbCameraVideoParam_ContrastGauge[0]));
			for(i=0;i < nCount;i++)
			{
				if (uUsbCameraVideoParam_ContrastGauge[i][1] == uInData)
				{
					*uOutLevel = uUsbCameraVideoParam_ContrastGauge[i][0];
					return true;
				}
			}
		}
		break;
	}

	return false;
}

void DisplayingUI_GetUsbCameraVideoSettingParam(E_DVR_USB_CAMERA_SET_VIDEO_TPYE emType,u8 u8Level)
{
	LOGD("[%s] emType = %x,u8Level = %d",__FUNCTION__,emType,u8Level);
	switch(emType){
		case TPYE_VIDEO_COLOR:
			setAnalogData(CONTROLID_DRIVING_USB_CAREMA_VIDEO_SETTING_COLOR, u8Level);
			break;
		case TPYE_VIDEO_CHROMINANCE:
			setAnalogData(CONTROLID_DRIVING_USB_CAREMA_VIDEO_SETTING_CHROMINANCE, u8Level);
			break;
		case TPYE_VIDEO_BRIGHTNESS:
			setAnalogData(CONTROLID_DRIVING_USB_CAREMA_VIDEO_SETTING_BRIGHTNESS, u8Level);
			break;
		case TPYE_VIDEO_CONTRAST_GAUGE:
			setAnalogData(CONTROLID_DRIVING_USB_CAREMA_VIDEO_SETTING_CONTRAST_GAUGE, u8Level);
			break;
		default:break;
	}
}

void appToDvd_VideoSet_Color(u8 param)
{
	if(param == 0)
	{
		if(pLocalParam->uUsbCameraVideoColor_Level == 10)
			return;
		
		pLocalParam->uUsbCameraVideoColor_Level++;
	}
	else if(param == 1)
	{
		if(pLocalParam->uUsbCameraVideoColor_Level == 0)
			return;
		
		pLocalParam->uUsbCameraVideoColor_Level--;
	}

	u8 uTemData = 0xff;
	if(UsbCamera_SetVideoParam_Level_To_Data(TPYE_VIDEO_COLOR,pLocalParam->uUsbCameraVideoColor_Level,&uTemData))
	{
		if(uTemData == 0xff)
			return;
		
		SetToHal_DVR_USB_CaremaVideoParam((u8)TPYE_VIDEO_COLOR,uTemData);
	}
}

void appToDvd_VideoSet_Chrominace(u8 param)
{
	if(param == 0)
	{
		if(pLocalParam->uUsbCameraVideoChrominance_Level == 10)
			return;
		
		pLocalParam->uUsbCameraVideoChrominance_Level++;
	}
	else if(param == 1)
	{
		if(pLocalParam->uUsbCameraVideoChrominance_Level == 0)
			return;
		
		pLocalParam->uUsbCameraVideoChrominance_Level--;
	}

	u8 uTemData = 0xff;
	if(UsbCamera_SetVideoParam_Level_To_Data(TPYE_VIDEO_CHROMINANCE,pLocalParam->uUsbCameraVideoChrominance_Level,&uTemData))
	{
		if(uTemData == 0xff)
			return;
		
		SetToHal_DVR_USB_CaremaVideoParam((u8)TPYE_VIDEO_CHROMINANCE,uTemData);
	}
}

void appToDvd_VideoSet_Brightness(u8 param)
{
	if(param == 0)
	{
		if(pLocalParam->uUsbCameraVideoBrightness_Level == 10)
			return;
		
		pLocalParam->uUsbCameraVideoBrightness_Level++;
	}
	else if(param == 1)
	{
		if(pLocalParam->uUsbCameraVideoBrightness_Level == 0)
			return;
		
		pLocalParam->uUsbCameraVideoBrightness_Level--;
	}

	u8 uTemData = 0xff;
	if(UsbCamera_SetVideoParam_Level_To_Data(TPYE_VIDEO_BRIGHTNESS,pLocalParam->uUsbCameraVideoBrightness_Level,&uTemData))
	{
		if(uTemData == 0xff)
			return;
		
		SetToHal_DVR_USB_CaremaVideoParam((u8)TPYE_VIDEO_BRIGHTNESS,uTemData);
	}
}

void appToDvd_VideoSet_ContrastGauge(u8 param)
{
	if(param == 0)
	{
		if(pLocalParam->uUsbCameraVideoContrastGauge_Level == 10)
			return;
		
		pLocalParam->uUsbCameraVideoContrastGauge_Level++;
	}
	else if(param == 1)
	{
		if(pLocalParam->uUsbCameraVideoContrastGauge_Level == 0)
			return;
		
		pLocalParam->uUsbCameraVideoContrastGauge_Level--;
	}

	u8 uTemData = 0xff;
	if(UsbCamera_SetVideoParam_Level_To_Data(TPYE_VIDEO_CONTRAST_GAUGE,pLocalParam->uUsbCameraVideoContrastGauge_Level,&uTemData))
	{
		if(uTemData == 0xff)
			return;
		
		SetToHal_DVR_USB_CaremaVideoParam((u8)TPYE_VIDEO_CONTRAST_GAUGE,uTemData);
	}
}


void appToDvr_Usb_Camera_Set_Switch_one(u8 param)
{
	E_DVR_USB_CAMERA_WHICH_ROAD emTempWhichOneRoad_Recording = (E_DVR_USB_CAMERA_WHICH_ROAD)pLocalParam->m_iUsbCameraSettingParam[4];

	#ifdef EMERGENCY
	if((E_SELECT_CTRL)param == SELECT_CTRL_UP)
	{
		if(emTempWhichOneRoad_Recording == USB_CAMERA_WHICH_ROAD_DOUBLE)
		{
			emTempWhichOneRoad_Recording = USB_CAMERA_WHICH_ROAD_EMERGENCY_COLLISION;
		}
		else if(emTempWhichOneRoad_Recording == USB_CAMERA_WHICH_ROAD_EMERGENCY_COLLISION)
		{
			emTempWhichOneRoad_Recording = USB_CAMERA_WHICH_ROAD_SINGLE;
		}
		else if(emTempWhichOneRoad_Recording == USB_CAMERA_WHICH_ROAD_SINGLE)
		{
			emTempWhichOneRoad_Recording = USB_CAMERA_WHICH_ROAD_DOUBLE;
		}
	}
	else if((E_SELECT_CTRL)param == SELECT_CTRL_DOWN)
	{
		if(emTempWhichOneRoad_Recording == USB_CAMERA_WHICH_ROAD_SINGLE)
		{
			emTempWhichOneRoad_Recording = USB_CAMERA_WHICH_ROAD_EMERGENCY_COLLISION;
		}
		else if(emTempWhichOneRoad_Recording == USB_CAMERA_WHICH_ROAD_EMERGENCY_COLLISION)
		{
			emTempWhichOneRoad_Recording = USB_CAMERA_WHICH_ROAD_DOUBLE;
		}
		else if(emTempWhichOneRoad_Recording == USB_CAMERA_WHICH_ROAD_DOUBLE)
		{
			emTempWhichOneRoad_Recording = USB_CAMERA_WHICH_ROAD_SINGLE;
		}
	}
	#else
	if(emTempWhichOneRoad_Recording == USB_CAMERA_WHICH_ROAD_DOUBLE)
	{
		emTempWhichOneRoad_Recording = USB_CAMERA_WHICH_ROAD_SINGLE;
	}
	else if(emTempWhichOneRoad_Recording == USB_CAMERA_WHICH_ROAD_SINGLE)
	{
		emTempWhichOneRoad_Recording = USB_CAMERA_WHICH_ROAD_DOUBLE;
	}
	#endif

	LOGD("[%s] emTempWhichOneRoad_Recording:%d",__FUNCTION__,emTempWhichOneRoad_Recording);
	
	pLocalParam->m_iUsbCameraSettingParam[4] = (int)emTempWhichOneRoad_Recording;
	
	UI_Usb_Camera_Mono_Road(emTempWhichOneRoad_Recording);
	UI_Usb_Camera_ApplyButton_IsControllable(true);
}

void UI_Usb_Camera_Mono_Road(E_DVR_USB_CAMERA_WHICH_ROAD em)
{
	int nMap[SIZE_MAP_MAXLEN] = {0};
	nMap[USB_CAMERA_WHICH_ROAD_SINGLE] = STRING_DRIVING_USB_CAREMA_SWITCH_ROAD_SINGLE;
	nMap[USB_CAMERA_WHICH_ROAD_DOUBLE] = STRING_DRIVING_USB_CAREMA_SWITCH_ROAD_DOUBLE;
	nMap[USB_CAMERA_WHICH_ROAD_EMERGENCY_COLLISION] = STRING_DRIVING_USB_CAREMA_SWITCH_ROAD_EMERGENCY_COLLISION;
	if (em < SIZE_MAP_MAXLEN)
		setStringText(CONTROLID_DRIVING_USB_CAREMA_SET_SWITCH_ONE_RECOIDING_TXT, nMap[em]);
}

void ToHal_DVR_USB_Carema_WhichOne_Road_Recording(E_DVR_USB_CAMERA_WHICH_ROAD em)
{
	if(em == USB_CAMERA_WHICH_ROAD_DOUBLE)
	{
		SetToHal_DVR_USB_Carema_SwitchOneRecording(0x01);
	}
	else if(em == USB_CAMERA_WHICH_ROAD_SINGLE)
	{
		SetToHal_DVR_USB_Carema_SwitchOneRecording(0x00);
	}
	else if(em == USB_CAMERA_WHICH_ROAD_EMERGENCY_COLLISION)
	{
		SetToHal_DVR_USB_Carema_SwitchOneRecording(0x02);
	}

	UI_Usb_Camera_Mono_Road(em);
}

void appToDvr_DVR_UsbCamara_FOLDER_Button_MouseUp()
{
	dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_USB_CAMERA_FOLDER);
}

void DisplayingOrHidingFormatPromtDialog(u8 state)
{
	setUpdateUI(false);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_DIALOG, state);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_TEXT, state);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_SURE, state);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_CHANCE, state);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_PROMT_SURE, 0);
	setUpdateUI(true);

	setStringText(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_TEXT,STRING_DRIVING_USB_CAREMA_FORMAT_CARD_WHETHER);
}

void GetSyncInforsToFormatPromtDialog(u8 state)
{
	setUpdateUI(false);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_SURE, 0);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_CHANCE, 0);
	if(state == 0)//No SD
	{
		setStringText(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_TEXT,STRING_DRIVING_USB_CAREMA_FORMAT_CARD_NO_SD);
		setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_PROMT_SURE, 1);
	}
	else if(state == 1)//doing
	{
		setStringText(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_TEXT,STRING_DRIVING_USB_CAREMA_FORMAT_CARD_DOING);
	}
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_DIALOG, 1);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_TEXT, 1);
	setUpdateUI(true);
}

void GetAsyncInforsToFormatPromtDialog(u8 state)
{
	setUpdateUI(false);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_SURE, 0);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_CHANCE, 0);
	if(state == 0)//Succes
	{
		setStringText(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_TEXT,STRING_DRIVING_USB_CAREMA_FORMAT_CARD_DONE);
	}
	else if(state == 1)//Error
	{
		setStringText(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_TEXT,STRING_DRIVING_USB_CAREMA_FORMAT_CARD_ERROR);
	}
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_PROMT_SURE, 1);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_DIALOG, 1);
	setVisible(CONTROLID_DRIVING_USB_CAREMA_SETTING_MD_FORMAT_TEXT, 1);
	setUpdateUI(true);
}

void appToDvr_Usb_Camera_Set_Format()
{
	DisplayingOrHidingFormatPromtDialog(1);
}

void appToDvr_Usb_Camera_Set_SureOrChance_Format(u8 p)
{
	if(p == 0)
	{
		SetToHal_DVR_USB_Carema_MemoryCard_ToFormat(1);
	}
	else if(p == 1)
	{
		DisplayingOrHidingFormatPromtDialog(0);
	}
}

void appToDvr_Usb_Camera_Format_PromtDialogs_Hide()
{
	DisplayingOrHidingFormatPromtDialog(0);
}

void ToHalDvr_EmergencyCollisionSwitch(u8 param)
{
	SetToHal_DVR_USB_Carema_SwitchEmergencyCollision(param);
}

void ToUI_KeepTimesOfEmergencyCollision(u8 param)
{
	u8 ansiBuf[5];
	memset(ansiBuf, 0, sizeof(ansiBuf));
	sprintf((char*)ansiBuf,"%d", param);
	int nAnsiBufLen = strlen((char*)ansiBuf);
	setAnsiSerialData(CONTROLID_DRIVING_USB_CAREMA_SETTING_EC_KEEP_TIMES_TXT, (u8*)ansiBuf, nAnsiBufLen);
}
	
void ToHalDvr_SetKeepTimesOfEmergencyCollision(u8 param)
{
	u8 uTemp = pLocalParam->uCurEmergencyCollisionKeepTimes;
	LOGD("uTemp:%d",uTemp);
	if(param == 0)
	{
		if(uTemp == USB_CAMERA_KEEP_TIMES_MAX)
			uTemp = USB_CAMERA_KEEP_TIMES_MIN;
		else
			uTemp++;
	}
	else if(param == 1)
	{
		if(uTemp == USB_CAMERA_KEEP_TIMES_MIN)
			uTemp = USB_CAMERA_KEEP_TIMES_MAX;
		else
			uTemp--;
	}
	SetToHal_DVR_USB_Carema_RecordingTextKeepTimes_EC(uTemp);
}

void appToDvr_ChangHe_DVR_NO_DATA_VIDEO_OSD_BUTTON_BACKGROUND(void)
{
	if(getCurSysSetDvrProtocolModeStatus() == 1)
	{
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
		return;
	}
}

void appToDvr_ChangHe_DVR_NO_DATA_VIDEO_OSD_BUTTON_SET(void)
{
	if(getCurSysSetDvrProtocolModeStatus() == 1)
	{
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD);
		return;
	}
}

s32 getCurSysSetDvrProtocolModeStatus(void)
{
	u8 u_IsDvrIsProtocolMode = 1;
	u8 u_IsDvrIsProtocolModelen = 1;
	getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_DVR_PROTOCOL_MODE, (u8*)&u_IsDvrIsProtocolMode, &u_IsDvrIsProtocolModelen);
	LOGD("u_IsDvrIsProtocolMode:%d",u_IsDvrIsProtocolMode);
	
	return u_IsDvrIsProtocolMode;
}

void appToDvr_Menu_Button_Camera_changhe_MouseUp()
{
	if(pLocalParam->emUsbCameraIsExistDevice == CAMERA_NO_DEVICE)
	{
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_NO_SIGN);
	}
	else
	{
		dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO_changhe);
	}
}

void ToUI_USB_CaremaRecordingStatePromt(u8 p)
{
	setAnalogData(CONTROLID_DRIVING_USB_CAREMA_RECORDING_STATE_PROMPT,(int)p);
}

void ToUI_USB_CaremaSdcardStatePromt(u8 p)
{
	if(p == 2)
	{
		System_notifyApp_SdcardSpaceState(1);
	}
	else
	{
		System_notifyApp_SdcardSpaceState(0);
	}
	
	setAnalogData(CONTROLID_DRIVING_USB_CAREMA_SDCARD_STATE_PROMPT,(int)p);
}

void ToUI_USB_CaremaRecordingLockStatePromt(u8 p)
{
	setAnalogData(CONTROLID_DRIVING_USB_CAREMA_RECORDING_LOCK_STATE_PROMPT,(int)p);
}

void ToUI_USB_CaremaRecordingLockStateButton(u8 p)
{
	setDigitalData(CONTROLID_DRIVING_USB_CAREMA_RECORDING_LOCK_STATE_BUTTON,p);
}

void ToUI_USB_CaremaSensitivityStateButton(u8 p)
{
	switch(p)
	{
		case 0x00:
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_LOW,1);
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_MID,0);
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_HIGH,0);
		break;
		case 0x01:
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_LOW,0);
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_MID,1);
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_HIGH,0);
		break;
		case 0x02:
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_LOW,0);
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_MID,0);
			setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_SENSITIVITY_HIGH,1);
		break;
	}
}

void appToDvr_Usb_Camera_Set_Sensitivity(u8 param)
{
	SetToHal_DVR_USB_Carema_RecordingSensitivity(param);
}

void appToDvr_Usb_Camera_Set_RecordingLock()
{
   if(pLocalParam->bCurIsUsbCameraVideoLock == false)
   	{
   		pLocalParam->bCurIsUsbCameraVideoLock = 1;
		SetToHal_DVR_USB_Carema_RecordingVideoLock(0x01);
		ToUI_USB_CaremaRecordingLockStateButton(pLocalParam->bCurIsUsbCameraVideoLock);
   	}
}