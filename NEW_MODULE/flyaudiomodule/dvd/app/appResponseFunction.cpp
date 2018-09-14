#include <stdio.h>
#include <stdlib.h>


#include "global.h"
#include "param.h"
#include "paramID.h"
#include "controlID.h"
#include "pageID.h"
#include "halRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"
#include "appResponseCommand.h"
#include "halResponseFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "appRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "timer_interface.h"

void appToDvd_MainEQ_MouseUp(void){
	dvdToModule_NotifySystem_jumpPage(PAGE_EQ);
}

void appToDvd_MainAudio_MouseUp(void){
	dvdToModule_NotifySystem_jumpPage(PAGE_SOUND);	
}

void appToDvd_MainMute_MouseUp(void){
	//static int state = 1;
	//setDigitalData(CONTROLID_DVD_MAIN_MUTE,state);
	//state = state ^ 1;
	//dvdToHal_IR(DVDTOHAL_IR_MUTE);
}

void appToDvd_MainTrackList_MouseUp(void){
	if(pLocalParam->trackList_Enable){
		int i = 0;
		if(pLocalParam->totalTrack >= 20){
			for(i = 0; i < 20; i++ ){
				setVisible(CONTROLID_DVD_TRACKLIST_BEGIN + i, 1);
			}
		}
		else{
			for(i = 0; i < 20; i++ ){
				if(i < pLocalParam->totalTrack){
					setVisible(CONTROLID_DVD_TRACKLIST_BEGIN + i, 1);
					}
				else{
					setVisible(CONTROLID_DVD_TRACKLIST_BEGIN + i, 0);
					}
			}	
		}
		dvdToModule_NotifySystem_jumpPage(PAGE_DVD_TRACKLIST);
	}
}

void appToDvd_MainFolderButton_MouseUp(void){
	if(pLocalParam->folder_Enable){
		dvdToModule_NotifySystem_jumpPage(PAGE_DVD_FOLDER);
	}
}

void appToDvd_MainPlayPause_MouseUp(void){	
	if(pLocalParam->playStatus== PLAY_STATE_PLAY){
		dvdToHal_IR(DVDTOHAL_IR_PAUSE);
	}
	else{
		dvdToHal_IR(DVDTOHAL_IR_PLAY);
	}	
}

void appToDvd_MainStop_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_STOP);
	dvdToHal_IR(DVDTOHAL_IR_STOP);
	dvdToHal_IR(DVDTOHAL_IR_STOP);
}

void appToDvd_MainPrev_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_PREV);
}

void appToDvd_MainNext_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_NEXT);	
}

void appToDvd_MainFF_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_FF);	
}

void appToDvd_MainFB_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_FR);
}


void appToDvd_MainDisplayMode_MouseUp(char type){	
	static int cNewVideoMode = 0;
	
	switch(type){
		case 0x01:	// MAIN_4_3
			cNewVideoMode = 0;
			//setDigitalData(CONTROLID_DVD_MAIN_4_3,1);
			//setDigitalData(CONTROLID_DVD_MAIN_16_9,0);
			//setDigitalData(CONTROLID_DVD_MAIN_FULL,0);
			break;
		case 0x02:	// MAIN_16_9
			cNewVideoMode = 1;
			//setDigitalData(CONTROLID_DVD_MAIN_16_9,1);
			//setDigitalData(CONTROLID_DVD_MAIN_4_3,0);
			//setDigitalData(CONTROLID_DVD_MAIN_FULL,0);
			break;
		case 0x03:	// MAIN_FULL
			cNewVideoMode = 2;
			//setDigitalData(CONTROLID_DVD_MAIN_FULL,1);
			//setDigitalData(CONTROLID_DVD_MAIN_16_9,0);
			//setDigitalData(CONTROLID_DVD_MAIN_4_3,0);
			break;
	}
	
	//dvdToHal_IR(cNewVideoMode);
	dvdToHal_SetVideoMode(cNewVideoMode);
	if(cNewVideoMode != pLocalParam->imageRatio ){
		dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
	}
	pLocalParam->imageRatio = cNewVideoMode;
}

void appToDvd_MainDisplayMode_MouseDown(char type){
	switch(type){
		case 0x01:	// MAIN_4_3
			setDigitalData(CONTROLID_DVD_MAIN_4_3,1);
			setDigitalData(CONTROLID_DVD_MAIN_16_9,0);
			setDigitalData(CONTROLID_DVD_MAIN_FULL,0);
			break;
		case 0x02:	// MAIN_16_9
			setDigitalData(CONTROLID_DVD_MAIN_16_9,1);
			setDigitalData(CONTROLID_DVD_MAIN_4_3,0);
			setDigitalData(CONTROLID_DVD_MAIN_FULL,0);
			break;
		case 0x03:	// MAIN_FULL
			setDigitalData(CONTROLID_DVD_MAIN_FULL,1);
			setDigitalData(CONTROLID_DVD_MAIN_16_9,0);
			setDigitalData(CONTROLID_DVD_MAIN_4_3,0);
			break;
	}

}


void appToDvd_MainVideo_MouseUp(void){
	
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);  //jump the image page
}

void appToDvd_MainPlayBackMode_MouseUp(char type){

	static int shuffle_stat=0, rpt_stat=0, scan_Stat = 0;
	setUpdateUI(0x00);
	
	switch(type){
		case 0x01:	// MAIN_RPT 	// repeat
			if(pLocalParam->rpt_stat == 0){
				dvdToHal_IR(DVDTOHAL_IR_REPEAT_SINGLE);
			}
			else{
				dvdToHal_IR(DVDTOHAL_IR_REPEAT_ALL);
			}
			break;
		case 0x02:	// MAIN_SHUFFLE // Shuffle
			if(pLocalParam->shuffle_stat == 0){
				dvdToHal_IR(DVDTOHAL_IR_UART_PM_SHUFFLE);
			}
			else{
				dvdToHal_IR(DVDTOHAL_IR_UART_PM_NORMAL);
			}
			break;
		case 0x03:	// MAIN_SCAN
			if(pLocalParam->scan_Stat == 0){
				dvdToHal_IR(DVDTOHAL_IR_UART_PM_INTRO);
			}
			else{
				dvdToHal_IR(DVDTOHAL_IR_UART_PM_NORMAL);
			}
		break;
		default:break;
	}
	
	setUpdateUI(0x01);
}

void appToDvd_MainBack_MouseUp(void){
	dvdToModule_NotifySystem_jumpPage(PAGE_MENU);
}

void appToDvd_MenuDvd_MouseUp(void){
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);//(PAGE_DVD_MAIN);
}

void appToDvd_DVDOpenBackground_MouseUp(void){
	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	
	u16 wPrePage = 0;
	u8 len = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, PREV_PAGE, (u8*)&wPrePage, (u8*)&len);
	if((wPrePage==PAGE_DVD_MAIN)
		||(wPrePage==PAGE_DVD_FOLDER)
		||(wPrePage==PAGE_DVD_TRACKLIST) 
		|| (wPrePage == PAGE_DVD_VIDEO) 
		|| (wPrePage == PAGE_DVD_VIDEO_CONTROL) 
		|| (wPrePage == PAGE_DVD_VIDEO_SET))
	{
		dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
	}
	else
	{
		dvdToModule_NotifySystem_JumpPrePage();
	}
	
}

void appToDvd_TrackListIndex_MouseUp(int index){	
	LOGD("appToDvd_TrackListIndex_MouseUp: %d",index);
	int iPlayIndex = index;
	
	if(iPlayIndex + 1 > pLocalParam->totalTrack)
		return;
	
	dvdToHal_PlayByIndex(iPlayIndex);
}

void appToDvd_TrackListIndex_MouseDown(int index){
	LOGD("appToDvd_TrackListIndex_MouseDown = %d", index);
	dvdToApp_DisplayPlayCDIndex(index);
}

void appToDvd_TrackList_Back_MouseUp(void){
	//dvdToModule_NotifySystem_JumpPrePage();
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
}

void appToDvd_FolderPrevPage_MouseUp(void){
	pLocalParam->lastBrowsePos -= 5;
	pLocalParam->browsePos -= 5;
	LOGD("pLocalParam->browsePos = 0x%d" , pLocalParam->browsePos );
	/*if(pLocalParam->browsePos < 0){
		pLocalParam->browsePos = 0;
		pLocalParam->lastBrowsePos = 0;
		return;
	}*/
	if(pLocalParam->browsePos == -5){
		pLocalParam->browsePos = 0;
		pLocalParam->lastBrowsePos = 0;
		return;
	}
	else if(pLocalParam->browsePos < 0)
	{
		pLocalParam->browsePos = 0;
		pLocalParam->lastBrowsePos = 0;
	}
	dvdToHal_RequestFileDirName(5, pLocalParam->browsePos);
	setAnalogData(CONTROLID_DVD_FOLDER_GAUGE,pLocalParam->browsePos);
}

void appToDvd_FolderNextPage_MouseUp(void){
	if(pLocalParam->lastBrowsePos +5 > pLocalParam->fileNumOfCurFolder - 1)
		return;
	//int num;
	//num = pLocalParam->lastBrowsePos;

	pLocalParam->lastBrowsePos += 5;
	pLocalParam->browsePos += 5;
	setUpdateUI(0x00);
		if(pLocalParam->browsePos + 5>= pLocalParam->fileNumOfCurFolder){
			pLocalParam->browsePos = pLocalParam->fileNumOfCurFolder - 1;
			setAnalogData(CONTROLID_DVD_FOLDER_GAUGE,pLocalParam->browsePos);

			pLocalParam->browsePos = pLocalParam->lastBrowsePos;
			dvdToHal_RequestFileDirName(5,pLocalParam->browsePos);
			return;
		}

		dvdToHal_RequestFileDirName(5,pLocalParam->browsePos);
		setAnalogData(CONTROLID_DVD_FOLDER_GAUGE,pLocalParam->browsePos);
	setUpdateUI(0x01);

}

void appToDvd_FolderCurPage_MouseUp(void){

}

void appToDvd_FolderGauge_MouseUp(u8 *buffer,u8 len){
	int pos = 0;

	pos += (int)((buffer[0] << 24) & 0xFF000000);
	pos += (int)((buffer[1] << 16) & 0xFF0000);
	pos += (int)((buffer[2] << 8) & 0xFF00);
	pos += (int)(buffer[3] & 0xFF);
	LOGD("pos = %d", pos);
	pLocalParam->lastBrowsePos = pos;
	pLocalParam->browsePos = pos;
	pLocalParam->isSliderEvent = true;
	dvdToHal_RequestFileDirName(5,pLocalParam->lastBrowsePos);
}

void appToDvd_FolderItem_MouseUp(int index){
	
	int iFolderItemIndex = 0, iPlayItem = 0;
	iFolderItemIndex = index;	//ctrlId - CONTROLID_DVD_FOLDER_ITEM_BEGIN;

	if(pLocalParam->fileFolderItem[iFolderItemIndex].isBlank){
		return;
	}

	if(pLocalParam->fileFolderItem[iFolderItemIndex].isFile){
		// setAnalogData(CONTROLID_DVD_FOLDER_ITEM_BEGIN+iFolderItemIndex, 4);
		if(!pLocalParam->IsVideoItem){
			dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
		}
		else{
			dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
		}
			
	}
	else{
		// setAnalogData(CONTROLID_DVD_FOLDER_ITEM_BEGIN+iFolderItemIndex, 1);
	}

	int iNewPlayIndex = pLocalParam->fileFolderItem[iFolderItemIndex].localIndex;
	dvdToHal_PlayByIndex(iNewPlayIndex);
}

void appToDvd_FolderItem_MouseDown(int index){
	int iFolderItemIndex = 0, iPlayItem = 0;
	iFolderItemIndex = index;	//ctrlId - CONTROLID_DVD_FOLDER_ITEM_BEGIN;
	iPlayItem = pLocalParam->fileFolderItem[iFolderItemIndex].localIndex;
	
	if(pLocalParam->fileFolderItem[iFolderItemIndex].isBlank)
		return;
		   
	if(pLocalParam->fileFolderItem[iFolderItemIndex].isFile){
	}
	else{
	}	
}

void appToDvd_FolderBack_MouseUp(void){
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
}

void appToDvd_VideoBackground_MouseUp(void){
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO_CONTROL);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_PlayPause_MouseUp(void){
	
	if(pLocalParam->playStatus== 0x01){	// PLAY
		dvdToHal_IR(DVDTOHAL_IR_PAUSE);
	}
	else{
		dvdToHal_IR(DVDTOHAL_IR_PLAY);
	}

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Stop_MouseUp(void){
	
	dvdToHal_IR(DVDTOHAL_IR_STOP);
	dvdToHal_IR(DVDTOHAL_IR_STOP);
	dvdToHal_IR(DVDTOHAL_IR_STOP);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Prev_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_PREV);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Next_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_NEXT);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_FastForward_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_FF);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_FastBackward_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_FR);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_MainMenu_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_ROOT_MENU);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}
 
void appToDvd_VideoCtrl_Menu_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_ROOT_MENU);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}


void appToDvd_VideoCtrl_Audio_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_AUDIO);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_SubTitle_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_SUB_TITLE);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Set_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_SET_A);
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO_SET);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Back_MouseUp(void){
	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
}

void appToDvd_VideoCtrl_Left_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_LEFT);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Right_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_RIGHT);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Up_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_UP);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Down_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_DOWN);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Ok_MouseUp(void){
	dvdToHal_IR(DVDTOHAL_IR_ENTER);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoCtrl_Background_MouseUp(void){
	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
}


/////////////12-1//////////////////

void appToDvd_VideoSet_ColorDec_MouseUp(void){
	unsigned char buf[] = {0x11, 0x02};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_AUDIOVIDEO,buf,2);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoSet_ColorInc_MouseUp(void){
	unsigned char buf[] = {0x11, 0x01};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_AUDIOVIDEO,buf,2);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoSet_ChrominanceDec_MouseUp(void){
	unsigned char buf[] = {0x11, 0x04};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_AUDIOVIDEO,buf,2);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoSet_ChrominanceInc_MouseUp(void){
	unsigned char buf[] = {0x11, 0x03};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_AUDIOVIDEO,buf,2);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}


void appToDvd_VideoSet_ContrastDec_MouseUp(void){
	unsigned char buf[] = {0x11, 0x06};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_AUDIOVIDEO,buf,2);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoSet_ContrastInc_MouseUp(void){
	unsigned char buf[] = {0x11, 0x05};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_AUDIOVIDEO,buf,2);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}


void appToDvd_VideoSet_BrightnessDec_MouseUp(void){
	unsigned char buf[] = {0x11, 0x08};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_AUDIOVIDEO,buf,2);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

void appToDvd_VideoSet_BrightnessInc_MouseUp(void){
	unsigned char buf[] = {0x11, 0x07};
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_AUDIOVIDEO,buf,2);

	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}

/////////////12-1//////////////////
void appToDvd_VideoSet_Background_MouseUp(void){
	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
}

void appToDvd_VideoSet_CtrlBackground_MouseUp(void){
	DeleteTimer(DVD_OSD_TIMER_HIDDEN_DISPLAY);
	SetTimer(TIME_5S,0,DVD_OSD_TIMER_HIDDEN_DISPLAY);
}
int isEnable(int ctrlId){

	switch(ctrlId)
	{
	case CONTROLID_DVD_MAIN_FOLDER_BUTTON:
		if (!pLocalParam->folder_Enable)
			return 0;
		break;
	case CONTROLID_DVD_MAIN_TRACKLIST:
		if (!pLocalParam->trackList_Enable)
			return 0;
		break;
	case CONTROLID_MENU_DVD:
		if (!pLocalParam->bDVDMenuEnable)
			return false;
		break;
	case CONTROLID_DVD_MAIN_VIDEO:
		if (pLocalParam->brakeEnable)	// 开车状态不可访问
			return 0;
		break;
	default:
		return 1;
	}

	return 1;
}


/*
int MouseUp_Dvd_Ctrl(int dwFunID){
	switch(dwFunID)
		{
	case CONTROLID_DVD_MAIN_PREV:	// 上一曲
		dvdToHal_IR(DVDTOHAL_IR_PREV);
		break;
	case CONTROLID_DVD_VIDEO_CONTROL_PLAYPAUSE:	// 播放暂停

		if (pLocalParam->playStatus == PLAY_STATE_PAUSE)
			dvdToHal_IR(DVDTOHAL_IR_PLAY);
		else if(pLocalParam->playStatus == PLAY_STATE_PLAY)
				dvdToHal_IR(DVDTOHAL_IR_PAUSE);
			  else if (pLocalParam->playStatus == PLAY_STATE_STOP)
				 		dvdToHal_IR(DVDTOHAL_IR_PLAY);
		break;
	case CONTROLID_DVD_MAIN_NEXT:// 下一曲
		dvdToHal_IR(DVDTOHAL_IR_NEXT);
		break;
	case CONTROLID_DVD_MAIN_STOP:
		dvdToHal_IR(DVDTOHAL_IR_STOP);
		dvdToHal_IR(DVDTOHAL_IR_STOP);
		dvdToHal_IR(DVDTOHAL_IR_STOP);
		break;
	case CONTROLID_DVD_MAIN_FF://快进
		dvdToHal_IR(DVDTOHAL_IR_FF);
		break;
	case CONTROLID_DVD_MAIN_FB://快退
		dvdToHal_IR(DVDTOHAL_IR_FR);
		break;
	default:
		return 0;
		break;
	}
	return 1;

}
*/

void MouseMove_GaugeBrowse(u8 param){
	pLocalParam->browsePos = param;
	pLocalParam->lastBrowsePos = param;
	setAnalogData(CONTROLID_DVD_FOLDER_GAUGE,(int)param);
    //GetNewBrowseList();//	定时刷新

}

void appToDVD_VideoOSD_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType)
{
     u8 swtich_button=0;
     u8 button_status=0xff;
         switch(ctrlId){             
             ////////////////////////////////OSD//////////////////////////////////////////////////////
             case CONTROLID_DVD_VIDEO_CONTROL_MENU:
                 swtich_button=0x01;
                 break;
    	      case CONTROLID_DVD_VIDEO_CONTROL_MAINMENU:
                 swtich_button=0x02;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_SET:
                 swtich_button=0x03;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_AUDIO:
                 swtich_button=0x04;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_SUBTITLE:
                 swtich_button=0x05;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_BACK:
                 swtich_button=0x06;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_UP:
                 swtich_button=0x07;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_LEFT:
                 swtich_button=0x08;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_OK:
                 swtich_button=0x09;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_RIGHT:
                 swtich_button=0x0A;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_DOWN:
                 swtich_button=0x0B;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_PREV:
                 swtich_button=0x0C;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_FF://FAST FORWARD
                 swtich_button=0x10;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_PLAYPAUSE:
                 swtich_button=0x0E;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_STOP:
                 swtich_button=0x0F;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_FB: //FAST BACKWARD
                 swtich_button=0x0D;
                 break;
             case CONTROLID_DVD_VIDEO_CONTROL_NEXT:
                 swtich_button=0x11;
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
       dvdToModule_NotifyOSD_aboutT123_VideoOSD_Button(swtich_button,button_status);

}

void appToDVD_VideoOSDColorSet_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType)
{
    u8 swtich_button=0;
    u8 button_status=0xff;
    u8 value=0xff;
    u8 setOptions=0xff;

	switch(ctrlId){ 			
			case CONTROLID_DVD_VIDEO_SET_COLOUR_DEC://ɫ�ʼ�
				swtich_button=0x01;
				break;
			case CONTROLID_DVD_VIDEO_SET_COLOUR_INC://ɫ�ʼ�
				swtich_button=0x02;
				break;
			case CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_DEC://���� ��
	            swtich_button=0x03;
				break;
			case CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_INC://���ȼ�
				swtich_button=0x04;
				break; 
			case CONTROLID_DVD_VIDEO_SET_CHROMINANCE_DEC://ɫ����
			    swtich_button=0x05;
				break;
			case CONTROLID_DVD_VIDEO_SET_CHROMINANCE_INC://ɫ����
			    swtich_button=0x06;
				break;
			case CONTROLID_DVD_VIDEO_SET_CONTRAST_DEC://�Աȶȼ�
			    swtich_button=0x07;
				break;
			case CONTROLID_DVD_VIDEO_SET_CONTRAST_INC://�Աȶȼ�
			    swtich_button=0x08;
				break;	 
			default:
				return;
				break;
		}
	

    if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
    {
        switch(ctrlId){             
                case CONTROLID_DVD_VIDEO_SET_COLOUR_DEC://ɫ�ʼ�
                    setOptions=0x62;
                    break;
                case CONTROLID_DVD_VIDEO_SET_COLOUR_INC://ɫ�ʼ�
                    setOptions=0x62;
                    break;
                case CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_DEC://���� ��
                    setOptions=0x63;
                    break;
                case CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_INC://���ȼ�
                    setOptions=0x63;
                    break; 
                case CONTROLID_DVD_VIDEO_SET_CHROMINANCE_DEC://ɫ����
                    setOptions=0x64;
                    break;
                case CONTROLID_DVD_VIDEO_SET_CHROMINANCE_INC://ɫ����
                    setOptions=0x64;
                    break;
                case CONTROLID_DVD_VIDEO_SET_CONTRAST_DEC://�Աȶȼ�
                    setOptions=0x65;
                    break;
                case CONTROLID_DVD_VIDEO_SET_CONTRAST_INC://�Աȶȼ�
                    setOptions=0x65;
                    break;   
                default:
    				return;
    				break;
            }
          //dvdToModule_NotifyOSD_aboutT123_colorSet_Value(setOptions,value);
        }

        if(ctrlType == UIACTION_MOUSEUP || ctrlType == UIACTION_MOUSETIMER)
        {
    	   button_status=0x00;
	    }
	    else
	    {
	       button_status=0x01;
	    }
     
	    dvdToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(swtich_button,button_status);
}

