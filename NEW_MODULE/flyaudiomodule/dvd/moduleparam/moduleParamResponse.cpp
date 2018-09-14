#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "paramID.h"
#include "moduleParamResponse.h"
#include "halRequestFunction.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"
#include "moduleParamRequest.h"



void moduleParameterInit(void){
	pLocalParam->bInDVD = 0;
	pLocalParam->trackList_Enable = 1;
	pLocalParam->folder_Enable = 1; 
	pLocalParam->bDVDMenuEnable = 1;
	pLocalParam->nPreDisState = -1;
	pLocalParam->SaveVideoMode = 0x02;
	pLocalParam->IsShowFullScreen = 0;
	pLocalParam->bVideo = 0;
	pLocalParam->browsePos = 0;
	pLocalParam->bLoadAndPlayVedio = 0;
	pLocalParam->GetCLOSEMsg  = 0;
	pLocalParam->TypeNum = 0;
	pLocalParam->IsVideoItem = 0;
	pLocalParam->IsShowOSD = 0;
	pLocalParam->isRoot = 0;
	pLocalParam->lastBrowsePos = 0;
	pLocalParam->imageRatio = 2;
	pLocalParam->isSliderEvent = false;
	dvdToApp_enableTrackListAndFolder(false, false);
	pLocalParam->uTemdiscOpenStatus = 0x00;
		
}

void moduleParameterDeInit(void){

}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
	    case CUR_PLAY_STATUS:
	    	*(u8*)param = (u8)pLocalParam->playStatus;
			*paramLen = sizeof(u8);
	    break;
        case CUR_DISC_TYPE:
            *(u8*)param = (u8)pLocalParam->discType;
			*paramLen = sizeof(u8);
        break;
        case CUR_TRACK_NUM:
            *(u8*)param = (u8)pLocalParam->curTrack;
			*paramLen = sizeof(u8);
        break;
        case CUR_CHAPTER_NUM:
            *(u8*)param = (u8)pLocalParam->curTitle;
			*paramLen = sizeof(u8);
        break;
		default:break;
	}
}

void SetDefaultParam()
{

	pLocalParam->IsPlayForBLCD = 0;
	pLocalParam->GetCLOSEMsg = 0;
	pLocalParam->bInDVD = 0;
	pLocalParam->bPull_Sek_OSD = 0;
	pLocalParam->brakeEnable = 0;
	pLocalParam->bSoundRun = 0;
	pLocalParam->bUSBtoDVD = 0;
	pLocalParam->curPlayDevice = 0;
	pLocalParam->playStatus = 0;
	pLocalParam->FileBrowsePos = 0;
	pLocalParam->browsePos = 0;
	pLocalParam->totalTrack = 0;
	
	//m_bHaveImage = false;
	
	//m_nCurPlayIndex = 0; //当前曲目
	//m_nTrackNum = 0; //曲目总数量

	//play Mode
	pLocalParam->shuffle_stat = 0;
	pLocalParam->rpt_stat = 0;
	pLocalParam->scan_Stat = 0;
	pLocalParam->uTemdiscOpenStatus = 0x00;
	
	dvdToApp_enableTrackListAndFolder(false,false);
	clearLastDeviceInfo();
}

void clearLastDeviceInfo(){
	setUpdateUI(0x00);
	setSerialData(CONTROLID_DVD_MAIN_FOLDER_NAME,(u8*)"",0);
	setSerialData(CONTROLID_DVD_MAIN_FILE_NAME,(u8*)"",0);

	//清除播放状态栏
	setSerialData(CONTROLID_DVD_MAIN_TITLE_TEXT,(u8*)"",0);
	setSerialData(CONTROLID_DVD_MAIN_TRACK_TEXT,(u8*)"",0);
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TITLE_NUM,(u8*)"",0);
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TRACK_NUM,(u8*)"",0);
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TIME,(u8*)"",0); //CONTROLID_DVD_MAIN_CURRENT_TIME
	setSerialData(CONTROLID_DVD_MAIN_NO_DISC,(u8*)"",0);
	int i=0;
	for (;i<5;i++)
	{
		pLocalParam->fileFolderItem[i].globalIndex = 0;
		pLocalParam->fileFolderItem[i].localIndex = 0;
		pLocalParam->fileFolderItem[i].isBlank = 1;
		setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN + i,0);
		pLocalParam->curPlayFolder.len= 0;
		pLocalParam->curPlayFolder.name[0] = 0;
		pLocalParam->curPlayFolder.name[1] = 0;
		setSerialData(CONTROLID_DVD_FOLDER_ITEM_BEGIN + i,(u8*)"",0);
	}
	setUpdateUI(0x01);
	LOGD("---------------------DVD_Module_clearLastDeviceInfo success");

}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& DVD moduleParameterReInit");
	moduleParameterInit();
}
int module_extendInterface(char *buffer, int len){
	u8 cmd = buffer[0];
	LOGD("***********************DVD module_extendInterface:%x,%x",cmd,buffer[1]);
	switch(cmd){
	case 0x2C:
		if(buffer[1]==0x00)//accoff
		{
			LOGD("----------dvd---ACC  OFF------------------");
			u16 curPage = 0;
			unsigned char curPageLen;
			getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,(u8 *)&curPageLen);
			if(curPage == PAGE_DVD_VIDEO||curPage == PAGE_DVD_VIDEO_CONTROL||curPage == PAGE_DVD_VIDEO_SET || curPage == PAGE_DVD_FOLDER || curPage == PAGE_DVD_TRACKLIST)
			{
				dvdToModule_NotifySystem_JumpPrePage();
			}
		
			dvdToApp_clearAllStateWhenOpenDVD();
			clearLastDeviceInfo();
			
		}
		else if(buffer[1] == 0x01)
		{
			LOGD("Module_DVD  acc restart");
			//readParameter();
		}
		else if(buffer[1] == 0x02)//
		{
			LOGD("Module_DVD default");
			moduleParameterInit();
		}
		break;
	case 0x2D:
		if(buffer[1]==0x00)//accon
		{
			LOGD("Module_DVD---ACC---ON");
			pLocalParam->uTemdiscOpenStatus = 0x00;
		}
		break;
	case 0xFD:
		{
			pLocalParam->bInDVD = 0;
			pLocalParam->trackList_Enable = 1;
			pLocalParam->folder_Enable = 1; 
			pLocalParam->bDVDMenuEnable = 1;
			pLocalParam->nPreDisState = -1;
			pLocalParam->SaveVideoMode = 0x02;
			pLocalParam->IsShowFullScreen = 0;
			pLocalParam->bVideo = 0;
			pLocalParam->browsePos = 0;
			pLocalParam->bLoadAndPlayVedio = 0;
			pLocalParam->GetCLOSEMsg  = 0;
			pLocalParam->TypeNum = 0;
			pLocalParam->IsVideoItem = 0;
			pLocalParam->IsShowOSD = 0;
			pLocalParam->isRoot = 0;
			pLocalParam->lastBrowsePos = 0;
			pLocalParam->imageRatio = 2;
			pLocalParam->isSliderEvent = false;

			dvdToApp_enableTrackListAndFolder(false, false);
			pLocalParam->uTemdiscOpenStatus = 0x00;
			
			dvdToHal_Init(0x01);
			//initTimerCenter(&TimerHandlerCenter);
		}
		break;
	default:break;
	}

	return 0;
}


