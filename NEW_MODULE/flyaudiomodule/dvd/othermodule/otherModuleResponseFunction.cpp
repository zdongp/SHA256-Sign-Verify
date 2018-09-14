#include <stdio.h>
#include <stdlib.h>


#include "global.h"
#include "param.h"
#include "paramID.h"
#include "controlID.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleResponseFunction.h"
#include "appRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamResponse.h"
#include "timer_interface.h"





void FuncEnable(int controlId, int visible){
	switch(controlId)
	{
	case CONTROLID_DVD_MAIN_FOLDER_BUTTON:
		break;
	case CONTROLID_DVD_MAIN_TRACKLIST:
		break;
	case CONTROLID_MENU_DVD:
		if (3 == visible) //������ͼ��
			pLocalParam->bDVDMenuEnable = false;
		else
			pLocalParam->bDVDMenuEnable = true;
		break;
	default:
		break;
	}
	setAnalogData(controlId,visible);

}

void dvdToApp_UIDefaultDisplay(){
	setUpdateUI(0x00);
	FuncEnable(CONTROLID_DVD_MAIN_FOLDER_BUTTON, 3);		//�ļ��б��
	FuncEnable(CONTROLID_DVD_MAIN_TRACKLIST, 3);	//�ļ��б���
	FuncEnable(CONTROLID_MENU_DVD, 1);	//���˵�

	setDigitalData(CONTROLID_MENU_DVD, 1);


	//CString str = L"";
	//setSerialData(FUNCID_DVD_TXT_STATE,str);

	setVisible(CONTROLID_DVD_MAIN_NO_DISC, 1);	//״̬,

	//setVisible(FUNCID_DVD_TXT_TYPE,false);
	setVisible(CONTROLID_DVD_MAIN_TITLE_TEXT,0);
	setVisible(CONTROLID_DVD_MAIN_CURRENT_TITLE_NUM,0);
	setVisible(CONTROLID_DVD_MAIN_TRACK_TEXT,0);
	setVisible(CONTROLID_DVD_MAIN_CURRENT_TRACK_NUM,0);
	setVisible(CONTROLID_DVD_MAIN_CURRENT_TIME,0);
	setVisible(CONTROLID_DVD_MAIN_RPT,1);
	setVisible(CONTROLID_DVD_MAIN_SHUFFLE,1);



	setAnalogData(CONTROLID_DVD_MAIN_SCAN,3);

	setVisible(CONTROLID_DVD_MAIN_SCAN,1);
	setVisible(CONTROLID_DVD_MAIN_VIDEO,0);
	setVisible(CONTROLID_DVD_MAIN_FULL,0);
	setVisible(CONTROLID_DVD_MAIN_4_3,0);
	setVisible(CONTROLID_DVD_MAIN_16_9,0);
	setUpdateUI(0x01);
}

void moduleToDvd_FromSystem_InitByConfig(){
	dvdToApp_UIDefaultDisplay();
	if(!pLocalParam->bSoundRun)
		dvdToHal_IR(DVDTOHAL_IR_PAUSE);//��ͣ�ļ�
	dvdToHal_Init(0x01);

}

void moduleToDvd_FromSystem_GetBrakeStatus(u8 param){
	setUpdateUI(0x00);
	if(param == 0x01) //ɲ��
	{
		pLocalParam->brakeEnable = 0;
		setAnalogData(CONTROLID_DVD_MAIN_VIDEO,0);
		setControllable(CONTROLID_DVD_MAIN_VIDEO,1);

		setControllable(CONTROLID_DVD_MAIN_4_3,1);

		setControllable(CONTROLID_DVD_MAIN_16_9,1);

		setControllable(CONTROLID_DVD_MAIN_FULL,1);
	}
	else
	{
		pLocalParam->brakeEnable = 1;
		if(isInDVDVideoPage())//�˳���Ƶҳ
		{
			dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
		}
		setAnalogData(CONTROLID_DVD_MAIN_VIDEO,2);
		setControllable(CONTROLID_DVD_MAIN_VIDEO,0);

		setControllable(CONTROLID_DVD_MAIN_4_3,0);

		setControllable(CONTROLID_DVD_MAIN_16_9,0);

		setControllable(CONTROLID_DVD_MAIN_FULL,0);

	}
	setUpdateUI(0x01);
}



void moduleToDvd_FromSystem_ACCOn(){

	readParameter();
	moduleToDvd_FromSystem_InitByConfig();

	dvdToApp_clearAllStateWhenOpenDVD();  //8-3

}

void moduleToDvd_FromSystem_ACCOff(){
	//dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
	saveParameter();
	moduleParameterInit();   //����Ĭ�ϲ���

}

void moduleToDvd_FromSystem_InitIdleParam(){
	u16 prePage = 0;
	u16 curPage = 0;
	unsigned char curPageLen;
	unsigned char prePageLen;

	//dvdToModule_NotifySystem_JumpPrePage();
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,(u8 *)&curPageLen);
	getOtherModuleParam(MODULE_ID_SYSTEM,PREV_PAGE, (u8 *)&prePage,(u8 *)&prePageLen);
	if(curPage == PAGE_DVD_VIDEO||curPage == PAGE_DVD_VIDEO_CONTROL||curPage == PAGE_DVD_VIDEO_SET || curPage == PAGE_DVD_FOLDER || curPage == PAGE_DVD_TRACKLIST)
	{
		dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
		//dvdToModule_NotifySystem_JumpPrePage();
	}

	dvdToApp_clearAllStateWhenOpenDVD();
	clearLastDeviceInfo();
}



void moduleToDvd_FromSystem_Message(unsigned char *param, unsigned char len){
	LOGD("moduleToDvd_FromSystem_Message    param[0] = %x  param[1] = %x", param[0],param[1]);
	switch(param[0]){
		case 0x14:
			moduleToDvd_FromSystem_InitByConfig();
			break;
		case 0x09:	// eg: Brake status
			moduleToDvd_FromSystem_GetBrakeStatus(param[1]);
			break;
		case 0x30:
			moduleToDvd_FromSystem_ACCOn();
			break;
		case 0x31:
			//to  ------->> module_extendInterface
			moduleToDvd_FromSystem_ACCOff();
			break;
		case 0x0E:
			if (param[1] == 1)
				moduleToDvd_FromSystem_InitIdleParam();
			else ////LL-9-8
			{
				//CString temp = L"";
				//m_pTheApp->m_pCenterUI->Set_Data(FUNCID_DVD_TXT_TIME,temp);
			}
			break;
		case 0x38:
			if(param[1] == 0)
				DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
			LOGD("--DeleteTimer--");
			break;
		default:
			break;

	}
}

/*******************************************************************************************************/

void moduleToDvd_FromAudiovideo_GetDvdModeInOut(int InOut){
	u8 nOldPlayState;
	
	LOGD("moduleToDvd_FromAudiovideo_GetDvdModeInOut");
	nOldPlayState = pLocalParam->playStatus;
	if(pLocalParam->bInDVD == InOut)
		return;
	pLocalParam->bInDVD= InOut;
	if(InOut)//����DVD
	{
		if (PLAY_STATE_PLAY == nOldPlayState || !pLocalParam->bSoundRun)
		{
			dvdToHal_IR(DVDTOHAL_IR_PLAY);
			pLocalParam->bSoundRun = 1;
		}
	}
	else //�뿪DVD
	{
		nOldPlayState = pLocalParam->playStatus;
		if (PLAY_STATE_PLAY == nOldPlayState)
		{
			dvdToHal_IR(DVDTOHAL_IR_STOP);
			pLocalParam->bSoundRun = 0;
		}
	}
}

void moduleToDvd_FromAudiovideo_GetVolumeOsdCtrl(void){
	u16 curpage = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&curpage, &len);
	if(curpage == PAGE_DVD_VIDEO_CONTROL || curpage == PAGE_DVD_VIDEO_SET){
		LOGD("dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);");
		dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
	}
}

void moduleToDvd_FromAudiovideo_GetOsdVideoSetting(unsigned char type, unsigned char value){
	LOGD("                type = %x,   value = %d",type, value);
	switch(type){
		case 0x00:
			setAnalogData(CONTROLID_DVD_VIDEO_SET_COLOUR_GAUGE, value);
			break;
		case 0x01:
			setAnalogData(CONTROLID_DVD_VIDEO_SET_CHROMINANCE_GAUGE, value);
			break;
		case 0x02:
			setAnalogData(CONTROLID_DVD_VIDEO_SET_CONTRAST_GAUGE, value);
			break;
		case 0x03:
			setAnalogData(CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_GAUGE, value);
			break;
		default:
			break;
	}
}


void moduleToDvd_FromAudiovideo_Message(unsigned char *param, unsigned char len){
	switch(param[0]){// eg: get the audiovideo mode
		case 0x00:
			if((param[1] == CHANNEL_DVD_CTRL) || (param[1] == CHANNEL_DVD_VIDEO)){// DVD1 (control UI) Or DVD2 (video UI)
				moduleToDvd_FromAudiovideo_GetDvdModeInOut(1);
				dvdToModule_NotifyAuxscreen_TitleTrack(pLocalParam->curTitle,pLocalParam->curTrack );
			}
			else{
				moduleToDvd_FromAudiovideo_GetDvdModeInOut(0);
			}
			break;
		case 0x01:
			moduleToDvd_FromAudiovideo_GetVolumeOsdCtrl();
			break;
		case 0x11:
			moduleToDvd_FromAudiovideo_GetOsdVideoSetting(param[1], param[2]);
			break;
		default:
			break;
	}
}

/*******************************************************************************************************/

int isInDVDPage(){
	u16 wCurPage  = 0;
	u8 len=0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&wCurPage, &len);
	LOGD("dvd getCurPage %x",wCurPage);
	if((wCurPage==(u16)PAGE_DVD_MAIN)||(wCurPage==(u16)PAGE_DVD_FOLDER)||(wCurPage==(u16)PAGE_DVD_TRACKLIST))
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
int isInDVDVideoPage(){
	u16 wCurPage = 0;
	u8 len=0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&wCurPage, &len);

	if((wCurPage==(u16)PAGE_DVD_VIDEO)||(wCurPage==(u16)PAGE_DVD_VIDEO_SET)||(wCurPage==(u16)PAGE_DVD_VIDEO_CONTROL))
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
void showDVDOSDTitle(u16 curPageId)
{
	u8	DropOSDVisible = 0;
	u8	DropOSDVisiblelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_HOMEPAGE_OSD_VISIBLE,(u8*)&DropOSDVisible,&DropOSDVisiblelen);
	if(DropOSDVisible == 0 && curPageId == PAGE_THIRD_PAGE)
	{
		LOGD("[%s]DropOSDVisible= %d",__FUNCTION__,DropOSDVisible);
	}
	else
	{
		if(curPageId != PAGE_DVD_MAIN && curPageId != PAGE_DVD_TRACKLIST && curPageId != PAGE_DVD_FOLDER
						&& curPageId != PAGE_DVD_OPEN && curPageId != PAGE_DVD_VIDEO && curPageId != PAGE_DVD_VIDEO_CONTROL
						&& curPageId != PAGE_DVD_VIDEO_SET){
						u8 OsdDevType = pLocalParam->u_DisplayOsdDevType;
						u16 title = pLocalParam->curTitle;
						u16 track = pLocalParam->curTrack;
		audioVideoToModule_NotifyOsd_ShowDVDTitle();
		audioVideoToModule_NotifyOsd_DVDTitleValue(OsdDevType, title, track);
		}
	}
}

void moduleToDvd_FromKey_GetPanelKey(unsigned char keyValue){

	switch (keyValue){
		case KEY_MENU:
			dvdToModule_NotifySystem_jumpPage(PAGE_MENU);
			break;
		case KEY_AV:
			if(isInDVDPage()){
				dvdToModule_NotifySystem_SwitchModule();
			}
			else if(isInDVDVideoPage()){
				dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
			}
			else{
				dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
			}
			break;
		case KEY_DVD:
			dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
			break;
		case KEY_FM:
			dvdToHal_IR(DVDTOHAL_IR_PAUSE);
			break;
		case KEY_OPEN:
			dvdToHal_IR(DVDTOHAL_IR_EJECT);
			break;
		case KEY_SEEK_INC:{
				u16 curPageId = 0;
				u8 curpageLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);
				if(!(curPageId == PAGE_GPS_PAGE&&pLocalParam->playStatus==0x00))
					dvdToHal_IR(DVDTOHAL_IR_NEXT);

				showDVDOSDTitle(curPageId);
			}
			break;
		case KEY_SEEK_DEC:{
			//PAGE_GPS_PAGE
				u16 curPageId = 0;
				u8 curpageLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);
				if(!(curPageId == PAGE_GPS_PAGE&&pLocalParam->playStatus==0x00))
					dvdToHal_IR(DVDTOHAL_IR_PREV);
				showDVDOSDTitle(curPageId);
			}
			break;
		case KEY_TUNE_DOWN:
			//Set_DVD_Req(DVD_REQ_CMD_IR,IR_EJECT);
			break;
		case KEY_TUNE_INC:{
			//PAGE_GPS_PAGE
				u16 curPageId = 0;
				u8 curpageLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);
				if(!(curPageId == PAGE_GPS_PAGE&&pLocalParam->playStatus==0x00))
					dvdToHal_IR(DVDTOHAL_IR_NEXT);
				showDVDOSDTitle(curPageId);
			}
			break;
		case KEY_TUNE_DEC:{
				u16 curPageId = 0;
				u8 curpageLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);
				if(!(curPageId == PAGE_GPS_PAGE&&pLocalParam->playStatus==0x00))
					dvdToHal_IR(DVDTOHAL_IR_PREV);
				showDVDOSDTitle(curPageId);
			}
			break;
		default:
			break;
		}

}

void moduleToDvd_FromKey_Message(unsigned char *param, unsigned char len){
	LOGD("moduleToDvd_FromKey_Message:param[0]:%d",param[0]);
	switch(param[0]){
		case 0x00:
			moduleToDvd_FromKey_GetPanelKey(param[1]);
			break;
		case 0x01:
			moduleToDvd_FromKey_JumpToVideoPage();
			break;
		default:
			break;
	}

}

/*******************************************************************************************************/

void moduleToDvd_FromBlcd_GetBlcdDeviceCtrl(unsigned char cmd){
	switch (cmd)
	{
	case 0x14:
		 pLocalParam->IsPlayForBLCD = 1;
		 dvdToHal_IR(DVDTOHAL_IR_PLAY);
		break;
	case 0X15:
		dvdToHal_IR(DVDTOHAL_IR_PAUSE);
		break;
	case 0x18:
		dvdToHal_IR(DVDTOHAL_IR_PREV);
		break;
	case 0x19:
		dvdToHal_IR(DVDTOHAL_IR_NEXT);
		break;
	case 0x17:
		dvdToHal_IR(DVDTOHAL_IR_STOP);
		break;
	default:
		break;
	}

}


void moduleToDvd_FromBlcd_Message(unsigned char *param, unsigned char len){
	switch(param[0]){
		case 0x01:
			if(param[1] == 0x00){
				//if(PLAY_STATE_PLAY != pLocalParam->playStatus)
				//	dvdToHal_IR(DVDTOHAL_IR_PLAY);
			}
			else{
				if(PLAY_STATE_PLAY == pLocalParam->playStatus)
					dvdToHal_IR(DVDTOHAL_IR_PAUSE);
			}
			break;
		case 0x10:
			moduleToDvd_FromBlcd_GetBlcdDeviceCtrl(param[1]);
			break;
		default:break;
	}

}

void moduleToDvd_FromGps_Message(unsigned char *param, unsigned char len)
{
	u16 curPageId = 0;
	u8 curpageLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);
	LOGD("moduleToDvd_FromGps:PAGEID:%x",curPageId);

	switch(param[0]){
		case 0x79:
			if(curPageId == PAGE_DVD_VIDEO_CONTROL || curPageId == PAGE_DVD_VIDEO_SET)
			{
				dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
			}
			break;
		default:break;
	}
}


void moduleToDvd_FromKey_JumpToVideoPage()
{
	u16 curPageId = 0;
	u8 curpageLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);
	LOGD("moduleToDvd_FromKey_JumpToVideoPage:PAGEID:%x",curPageId);
	if(curPageId == PAGE_DVD_VIDEO_CONTROL || curPageId == PAGE_DVD_VIDEO_SET)
	{
		LOGD("dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO)");
		dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
	}
}

void moduleToDvd_FromCenter_Message(unsigned char *param, unsigned char len)
{
	LOGD("++++++++++++++++++++%x++",param[1]);
	switch(param[0]){
		case 0x00:/*��ACCʱ��STOP��DVD*/
		{
			short DVDSound = 0;
			unsigned char soundLen;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&DVDSound,(u8 *)&soundLen);
			LOGD("++++++++++++++++++++%x++",DVDSound);
			if(DVDSound == CHANNEL_DVD_VIDEO || DVDSound == CHANNEL_DVD_CTRL)
			{
				if(param[1] == 0x01)
				{
					DeleteTimer(DVD_DELAY_STOP);
					DeleteTimer(DVD_DELAY_PLAY);
					
					dvdToHal_IR(DVDTOHAL_IR_STOP);
					dvdToHal_IR(DVDTOHAL_IR_STOP);
					dvdToHal_IR(DVDTOHAL_IR_STOP);
					SetTimer(2000,1,DVD_DELAY_STOP);
				}
				else
				{
					DeleteTimer(DVD_DELAY_PLAY);
					DeleteTimer(DVD_DELAY_STOP);
					
					dvdToHal_IR(DVDTOHAL_IR_PLAY);
					SetTimer(2000,1,DVD_DELAY_PLAY);
				}
			}
		}
		break;
		default:break;
	}

}

void moduleToDvd_FromExternalCtrl_Message(unsigned char *param,unsigned char len)
{
	LOGD("moduleToDvd_FromExternalCtrl_Message param[1]:%x pLocalParam->playStatus:%x",param[1],pLocalParam->playStatus);
	if(param[0] == 0x00)
	{
		switch(param[1])
		{
			case 0x00:
			{
				if(pLocalParam->playStatus != PLAY_STATE_STOP){
					dvdToHal_IR(DVDTOHAL_IR_STOP);
					dvdToHal_IR(DVDTOHAL_IR_STOP);
					dvdToHal_IR(DVDTOHAL_IR_STOP);
				}
			}
			break;
			case 0x01:
			{
				if(pLocalParam->playStatus != PLAY_STATE_PAUSE){
					dvdToHal_IR(DVDTOHAL_IR_PAUSE);
				}
			}
			break;
			case 0x02:
			{
				if(pLocalParam->playStatus != PLAY_STATE_PLAY){
					dvdToHal_IR(DVDTOHAL_IR_PLAY);
				}	
			}
			break;
			case 0x03:
				dvdToHal_IR(DVDTOHAL_IR_FR);
			break;
			case 0x04:
				dvdToHal_IR(DVDTOHAL_IR_FF);
			break;
			case 0x05:
				dvdToHal_IR(DVDTOHAL_IR_REPEAT_ALL);
			break;
			case 0x06:
			{
				static int shuffle_stat=0;	
				if(pLocalParam->shuffle_stat == 0){
					dvdToHal_IR(DVDTOHAL_IR_UART_PM_SHUFFLE);
				}
				else
				{
					dvdToHal_IR(DVDTOHAL_IR_UART_PM_NORMAL);
				}
			}
			break;
			case 0x07:
				dvdToHal_IR(DVDTOHAL_IR_REPEAT_SINGLE);
			break;
			case 0x08:
			{
				static int scan_Stat = 0;
				if(pLocalParam->scan_Stat == 0){
					dvdToHal_IR(DVDTOHAL_IR_UART_PM_INTRO);
				}
				else{
					dvdToHal_IR(DVDTOHAL_IR_UART_PM_NORMAL);
				}
			}
			break;
			default:break;
		}
	}
	else if(param[0] == 0x01)
	{
		if(param[1] == 0x01)
		{
			dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
		}
		else
		{
		}
	}
}


void moduleToDVD_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}

