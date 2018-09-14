#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamResponse.h"

#include "paramID.h"
#include "pageID.h"

extern "C"{
#include "unicodestring.h"
};

void dvdToApp_SetUIVideoMode(int modeFlag){
setUpdateUI(0x00);
	switch(modeFlag){
		case 0x00:
			setDigitalData(CONTROLID_DVD_MAIN_4_3, 1);
			setDigitalData(CONTROLID_DVD_MAIN_16_9,0);
			setDigitalData(CONTROLID_DVD_MAIN_FULL,0);
			break;
		case 0x01:
			setDigitalData(CONTROLID_DVD_MAIN_16_9, 1);
			setDigitalData(CONTROLID_DVD_MAIN_4_3,0);
			setDigitalData(CONTROLID_DVD_MAIN_FULL,0);
			break;
		case 0x02:
			setDigitalData(CONTROLID_DVD_MAIN_FULL, 1);
			setDigitalData(CONTROLID_DVD_MAIN_16_9,0);
			setDigitalData(CONTROLID_DVD_MAIN_4_3,0);
			break;
			
	}
	setUpdateUI(0x01);

}

void dvdToApp_identifyTrackListOrFolder(void){
	int discType, fileType;
	int enableTracklist = 0, enableFolder = 0;
	int audio = 1;
	discType = pLocalParam->discType;
	fileType = pLocalParam->fileType;
	
	switch(discType){
		case 0x00:	// No media
		case 0x01:	// DeInitialized Media
		case 0x02:	// CLIPS
			break;
		case 0x03:	// DVD Audio
			enableTracklist = 1;
			break;
		case 0x04:	// DVD Video
		case 0x05:	// SVCD
		case 0x06:	// VCD
		case 0x07:	// KADAK Picture CD
		case 0x08:	// FUJICOLOR Picture CD
			audio = 0;
			break;
		case 0x09:	// Reserved
			break;
	}
		
	switch(fileType){
		case 0x00:	// None
			break;
		case 0x01:	// MP2/MP3
		case 0x02:	// WMA
			enableFolder = 1;
			break;
		case 0x03:	// CDDA
			enableTracklist = 1;
			break;
		case 0x04:	// JPEG
		case 0x05:	// MPEG
		case 0x06:	// AVI
			audio = 0;
			enableFolder = 1;
			break;
		case 0x07:	// SubTitle
		case 0x08:	// Reserved
			break;
	}

	LOGD("dvdToApp_enableTrackListAndFolder audio %x",audio);
	dvdToApp_enableTrackListAndFolder(enableTracklist, enableFolder);
	dvdToApp_displayVideoModeOrAudioMode(audio);

	if(!audio){
		dvdToApp_SetUIVideoMode(pLocalParam->imageRatio);
	}

	pLocalParam->bVideo = !audio;
	
	short soundchannel = 0;
	u8 len = 0;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8*)&soundchannel, &len);
	LOGD("audio = %d        soundchannel = %x        pLocalParam->GetCLOSEMsg = %d", audio, soundchannel, pLocalParam->GetCLOSEMsg);
	if(!audio && (soundchannel == CHANNEL_DVD_CTRL || soundchannel == CHANNEL_DVD_VIDEO)&& pLocalParam->GetCLOSEMsg && !pLocalParam->brakeEnable){
		u16 prePage = 0;
		u8 curPage = 0;
		unsigned char curPageLen;
		getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,&curPageLen);
		if(curPage != PAGE_BACK_VIDEO){
			LOGD("			dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO)");
			dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
			
		}
		
	}
	
	pLocalParam->StoreTheAudioMode = audio;
}

void dvdToApp_refreshTrackList(void){
	int index;
	setUpdateUI(0x00);
	for(index = 0;index < TRACKLIST_ITEM_COUNT; index++){
		if(index < pLocalParam->fileNumOfCurFolder){
			setVisible(CONTROLID_DVD_TRACKLIST_BEGIN+index, 1);
		}
		else{
			setVisible(CONTROLID_DVD_TRACKLIST_BEGIN+index, 0);
		}
	}
	setUpdateUI(0x01);
}
void dvdToApp_refreshBrowseList(int i){
	

	setUpdateUI(0x00);
	int isFile = pLocalParam->fileFolderItem[i].isFile;
	if(pLocalParam->fileFolderItem[i].isBlank){
		u8 empty[4] = {0x00, 0x00, 0x00, 0x00};
		setSerialData(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i, empty, 2);
		setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i, 0);
	}
	else{
		setSerialData(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i, (u8 *)pLocalParam->fileFolderItem[i].name.name, pLocalParam->fileFolderItem[i].name.len);
		if(isFile){
			if(pLocalParam->fileFolderItem[i].globalIndex== pLocalParam->curPlayFileIndex){
				setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN + i, 3);
				return;
			}
			setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN + i, 2);
			//setAnalogData(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i,2);
		}
		else{
			setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN + i, 1);
			//setAnalogData(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i,1);
		}
	}
	setUpdateUI(0x01);
}

void dvdToApp_clearAllStateWhenOpenDVD(void){

	// clear directory and file name
	pLocalParam->curPlayFile.name[0]= 0;
	pLocalParam->curPlayFile.name[1]= 0;
	pLocalParam->curPlayFolder.name[0]= 0;
	pLocalParam->curPlayFolder.name[1]= 0;
	pLocalParam->curBrowseFolder.name[0]= 0;
	pLocalParam->curBrowseFolder.name[1]= 0;
	pLocalParam->curPlayFile.len= 0;
	pLocalParam->curPlayFolder.len= 0;
	pLocalParam->curBrowseFolder.len= 0;
	
	// clear status bar
	pLocalParam->lastBrowsePos = 0;
	pLocalParam->GetCLOSEMsg = 0;
	pLocalParam->isRoot = 0;
	
	//TODO:
	char clearbuffer[2]={0x00,0x00};
	setUpdateUI(0x00);
	setDigitalData(CONTROLID_DVD_MAIN_RPT, false);
	setDigitalData(CONTROLID_DVD_MAIN_SHUFFLE , false);
	setDigitalData(CONTROLID_DVD_MAIN_SCAN, false);
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TITLE_NUM,(u8*)clearbuffer, 2);
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TRACK_NUM,(u8*)clearbuffer, 2);
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TIME,(u8*)clearbuffer, 2);
	setSerialData(CONTROLID_DVD_MAIN_TYPE_TEXT,(u8*)clearbuffer, 2);
	setSerialData(CONTROLID_DVD_MAIN_FOLDER_NAME,(u8*)clearbuffer,2);
	setSerialData(CONTROLID_DVD_MAIN_FILE_NAME,(u8*)clearbuffer,2);

	setAnalogData(CONTROLID_DVD_MAIN_TRACKLIST, 2);
	setAnalogData(CONTROLID_DVD_MAIN_FOLDER_BUTTON, 2);
	setAnalogData(CONTROLID_DVD_FOLDER_GAUGE,0);//add 2012-07-09 14:25:44
	int i;
	for(i = 0; i < 5; i++){
		pLocalParam->fileFolderItem[i].localIndex= 0;
		pLocalParam->fileFolderItem[i].globalIndex= 0;
		pLocalParam->fileFolderItem[i].isBlank = 1;
		pLocalParam->fileFolderItem[i].name.name[0]= '\0';
		
		setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i, 0);
	}
	setDigitalData(pLocalParam->curPlayFileIndex%20+CONTROLID_DVD_TRACKLIST_BEGIN, 0);
	setUpdateUI(0x01);
	dvdToApp_displayDeviceStateOrTraceInfo(false);
	clearLastDeviceInfo();
	dvdToApp_displayVideoModeOrAudioMode(true);
	LOGD("DVD_Module_clearAllStateWhenOpenDVD _ Success");
}

void dvdToApp_enableTrackListAndFolder(int enableTracklist,int enableFolder){
	setUpdateUI(0x00);
	if(enableTracklist){
		setAnalogData(CONTROLID_DVD_MAIN_TRACKLIST, 0);
		setControllable(CONTROLID_DVD_MAIN_TRACKLIST, 1);
	}
	else {
		setAnalogData(CONTROLID_DVD_MAIN_TRACKLIST, 2);
		setControllable(CONTROLID_DVD_MAIN_TRACKLIST, 0);
	}
	
	if(enableFolder){
		setAnalogData(CONTROLID_DVD_MAIN_FOLDER_BUTTON, 0);
		setControllable(CONTROLID_DVD_MAIN_FOLDER_BUTTON, 1);
	}
	else{
		setAnalogData(CONTROLID_DVD_MAIN_FOLDER_BUTTON, 2);
		setControllable(CONTROLID_DVD_MAIN_FOLDER_BUTTON, 0);
	}
	setUpdateUI(0x01);
	pLocalParam->trackList_Enable = enableTracklist;
	pLocalParam->folder_Enable = enableFolder;
	
}
void dvdToApp_displayVideoModeOrAudioMode(int audio){
	
	setUpdateUI(0x00);
	setVisible(CONTROLID_DVD_MAIN_RPT, audio);
	setVisible(CONTROLID_DVD_MAIN_SHUFFLE, audio);
	setVisible(CONTROLID_DVD_MAIN_SCAN, audio);

	if(pLocalParam->brakeEnable){
		setAnalogData(CONTROLID_DVD_MAIN_VIDEO,2);
		setControllable(CONTROLID_DVD_MAIN_VIDEO,0);
		//setVisible(CONTROLID_DVD_MAIN_VIDEO,0);
	}
	else{
		setControllable(CONTROLID_DVD_MAIN_VIDEO,1);
		//setVisible(CONTROLID_DVD_MAIN_VIDEO,1);
		setAnalogData(CONTROLID_DVD_MAIN_VIDEO,0);
	}
		
	setVisible(CONTROLID_DVD_MAIN_FULL, !audio);
	setVisible(CONTROLID_DVD_MAIN_4_3, !audio);
	setVisible(CONTROLID_DVD_MAIN_16_9, !audio);
	setVisible(CONTROLID_DVD_MAIN_VIDEO, !audio);
	setUpdateUI(0x01);

	pLocalParam->IsShowFullScreen = !audio;
}
/*
Index =0 时表示 没有歌曲被选择
*/
void dvdToApp_DisplayPlayCDIndex(int Index)
{
	
	static int DisplayIndex= -1;
	
	if(Index >= 20){
		Index = -1;
	}
	LOGD("Index = %d,           DisplayIndex = %d", Index, DisplayIndex);
	if(DisplayIndex == Index){
		return;
	}
	
	
	if(DisplayIndex != -1){
		setDigitalData(CONTROLID_DVD_TRACKLIST_BEGIN + DisplayIndex,0);	
	}	
	
	DisplayIndex = Index;
	
	if(DisplayIndex != -1){
		setDigitalData(CONTROLID_DVD_TRACKLIST_BEGIN + DisplayIndex,1);
	}
}

void dvdToApp_displayDeviceStateOrTraceInfo(int displayTraceInfo){
	pLocalParam->displayTraceInfo = displayTraceInfo;
	setUpdateUI(0x00);
	setVisible(CONTROLID_DVD_MAIN_TITLE_TEXT, displayTraceInfo);
	setVisible(CONTROLID_DVD_MAIN_TRACK_TEXT, displayTraceInfo);
	setVisible(CONTROLID_DVD_MAIN_CURRENT_TITLE_NUM, displayTraceInfo);
	setVisible(CONTROLID_DVD_MAIN_CURRENT_TRACK_NUM, displayTraceInfo);
	setVisible(CONTROLID_DVD_MAIN_CURRENT_TIME, displayTraceInfo);
	setVisible(CONTROLID_DVD_MAIN_TYPE_TEXT, displayTraceInfo);
	
	setVisible(CONTROLID_DVD_MAIN_NO_DISC,!displayTraceInfo);
	setUpdateUI(0x01);
}

void dvdToApp_SetStateWhenReady(void){
	dvdToApp_displayDeviceStateOrTraceInfo(true);
}

