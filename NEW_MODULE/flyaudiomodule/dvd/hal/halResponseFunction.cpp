#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "appRequestFunction.h"
#include "moduleParamRequest.h"
extern "C"{
	#include "unicodestring.h"
};


void halToDvd_InitCmd(unsigned char param){
	
}

void  halToDvd_InitState(unsigned char param){
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TIME,(u8*)"",0);
}

void  halToDvd_ErrCode(unsigned char errCode){
	
	switch(errCode){
		case 0x07:break;
		case 0x09:break;
	}
}

void  halToDvd_PlayMode(unsigned char playMode){
	
	switch(playMode){
		case 0x01:
			{
				setDigitalData(CONTROLID_DVD_MAIN_RPT,1);
				setDigitalData(CONTROLID_DVD_MAIN_SHUFFLE,0);
				setDigitalData(CONTROLID_DVD_MAIN_SCAN,0);
				pLocalParam->rpt_stat = 1;
				pLocalParam->shuffle_stat = 0;
				pLocalParam->scan_Stat = 0;
			}
			break;
		case 0x02:
			{
				setDigitalData(CONTROLID_DVD_MAIN_RPT,0);
				setDigitalData(CONTROLID_DVD_MAIN_SHUFFLE,0);
				setDigitalData(CONTROLID_DVD_MAIN_SCAN,0);
				pLocalParam->rpt_stat = 0;
			}
			break;
		case 0x30:
			{
				setDigitalData(CONTROLID_DVD_MAIN_SHUFFLE,1);
				setDigitalData(CONTROLID_DVD_MAIN_RPT,0);
				setDigitalData(CONTROLID_DVD_MAIN_SCAN,0);
				pLocalParam->shuffle_stat = 1;
				pLocalParam->rpt_stat = 0;
				pLocalParam->scan_Stat = 0;
			}
			break;
		case 0x20:
			{
				setDigitalData(CONTROLID_DVD_MAIN_SHUFFLE,0);
				setDigitalData(CONTROLID_DVD_MAIN_RPT,0);
				setDigitalData(CONTROLID_DVD_MAIN_SCAN,1);
				pLocalParam->scan_Stat = 1;
				pLocalParam->shuffle_stat = 0;
				pLocalParam->rpt_stat = 0;
			}
			break;
		case 0x00:
			{
				setDigitalData(CONTROLID_DVD_MAIN_SHUFFLE,0);
				setDigitalData(CONTROLID_DVD_MAIN_RPT,0);
				setDigitalData(CONTROLID_DVD_MAIN_SCAN,0);
				pLocalParam->shuffle_stat = 0;
				pLocalParam->scan_Stat = 0;
			}
			break;
		defaule:break;
	}
}

void halToDvd_ClipsInfo(u16 totalNum, u16 folderNum, u8 isRoot){
	
	
	pLocalParam->fileNumOfCurFolder = totalNum;
	pLocalParam->folderNumOfCurFolder = folderNum;
	pLocalParam->isRoot = isRoot;
	
	setProgressRange(CONTROLID_DVD_FOLDER_GAUGE,totalNum - 1);

	if(pLocalParam->trackList_Enable){
		 dvdToApp_refreshTrackList();
	}
	
	if(pLocalParam->folder_Enable){
		int i;
		for(i = 0; i < FILE_FOLDER_ITEM_MAX_COUNT; i++){
			pLocalParam->fileFolderItem[i].isBlank = 1;
		}
	}
	
	dvdToHal_RequestFileDirName(FILE_FOLDER_ITEM_MAX_COUNT, 0);
	pLocalParam->browsePos = 0;
	pLocalParam->lastBrowsePos = 0;
	
	//dvdToApp_identifyTrackListOrFolder();
	// TODO: Reset Scrol indexItem data
}

void halToDvd_FolderFileName(u16 ItemIndex, u16 GobalIndex, char isFile, u8 *strName, int strNameLen){
	u8 *pName;
	int iDisplayItem = ItemIndex - pLocalParam->browsePos;
	
	if (iDisplayItem < 0 || iDisplayItem > FILE_FOLDER_ITEM_COUNT -1)
		return;

	file_folder_item_info_t *pFileFolderItem = &pLocalParam->fileFolderItem[iDisplayItem];
	
	pFileFolderItem->localIndex = ItemIndex;
	pFileFolderItem->globalIndex = GobalIndex;
	pFileFolderItem->isFile = isFile;

	if(uni16_strlen((unicode16_t *)strName) <= 0){
		pFileFolderItem->name.len = ansi_str_to_unicode16((u8*)"..",(unicode16_t *)pFileFolderItem->name.name);
		pFileFolderItem->name.len *= 2;
	}
	else{
		memcpy(pFileFolderItem->name.name, strName, strNameLen);
		pFileFolderItem->name.len = strNameLen;
	}
	pFileFolderItem->isBlank = false;

	if(iDisplayItem ==0){
		setUpdateUI(0x00);
		LOGD("halResponseFunction.c 100 setUpdateUI(0x00)");
	}
	
	if(iDisplayItem+1 <=  FILE_FOLDER_ITEM_COUNT){
		dvdToApp_refreshBrowseList(iDisplayItem);
	}
	
	if (((pLocalParam->lastBrowsePos + iDisplayItem + 1 >= pLocalParam->fileNumOfCurFolder))
		|| ((pLocalParam->browsePos > pLocalParam->fileNumOfCurFolder -1 - 4) && (pLocalParam->isSliderEvent == true)))
	{
		
		int i = iDisplayItem+1;
		pLocalParam->isSliderEvent = false;
		
		for (;i<FILE_FOLDER_ITEM_COUNT;i++)
		{
			iDisplayItem++;
			file_folder_item_info_t* pFileFolderItem = &pLocalParam->fileFolderItem[i];
			pFileFolderItem->isBlank = true;
			dvdToApp_refreshBrowseList(iDisplayItem);
		}
	}	
	
	if(iDisplayItem + 1 ==  FILE_FOLDER_ITEM_COUNT){
		setUpdateUI(0x01);
		LOGD("halResponseFunction.c 125     setUpdateUI(0x01)");
	}

}

void halToDvd_DVDRegion(unsigned char region){

}

void  halToDvd_VideoMode(unsigned char mode){
	
}

void  halToDvd_CurPlayDev(unsigned char dev){
	pLocalParam->curPlayDevice = dev;
}

void  halToDvd_DISCDevState(unsigned char queryDev, unsigned char devState){
	pLocalParam->deviceType = queryDev;
	pLocalParam->deviceStatus = devState;

	//moupeng 2015/7/31
	g_clsDvd.sendToFlyJniSdkDevState(devState);
	
	if(queryDev != 0){
		return;
	}
	char *str = NULL;
	char visible = 0;
	unsigned char buffer[64];
	int i, len = 0;
	switch(devState){
		case 0x00:
		{
			LOGD("                                         devState = NO DISC");
			str = "NO DISC";
			visible = 1;
			{
				u16 prePage = 0;
				u16 curPage = 0;
				u16 DVDSound = 0;
				u8 prePageLen, curPageLen, soundLen;
				getOtherModuleParam(MODULE_ID_SYSTEM,PREV_PAGE, (u8 *)&prePage,(u8 *)&prePageLen);
				getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL, (u8 *)&DVDSound,(u8 *)&soundLen);
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,(u8 *)&curPageLen);
				LOGD("curPage = 0x%x,    DVDSound = 0x%x,     prePage = 0x%x",curPage,DVDSound, prePage);
				if(curPage == PAGE_DVD_OPEN)
				{
					if((DVDSound == CHANNEL_DVD_CTRL || DVDSound == CHANNEL_DVD_VIDEO) && (prePage == PAGE_DVD_VIDEO
						|| prePage == PAGE_DVD_FOLDER
						|| prePage == PAGE_DVD_TRACKLIST 
						|| prePage == PAGE_DVD_VIDEO_CONTROL
						|| prePage == PAGE_DVD_VIDEO_SET
						|| prePage == PAGE_DVD_MAIN))
					{	
						dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
					}
					else
					{
						dvdToModule_NotifySystem_JumpPrePage();
					}
				}
				else/*��ʱ�����û��open����ͣ������Ƶҳ,��һ�����մ���*/
				{
					if((DVDSound == CHANNEL_DVD_CTRL || DVDSound == CHANNEL_DVD_VIDEO) && (curPage == PAGE_DVD_VIDEO
						|| curPage == PAGE_DVD_FOLDER
						|| curPage == PAGE_DVD_TRACKLIST 
						|| curPage == PAGE_DVD_VIDEO_CONTROL
						|| curPage == PAGE_DVD_VIDEO_SET
						|| curPage == PAGE_DVD_MAIN))
					{	
						dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
					}
				}
			}
			
			pLocalParam->u_DisplayOsdDevType = 0xFF;
			dvdToApp_displayDeviceStateOrTraceInfo(!visible);

			
			pLocalParam->curTitle = 0;	// jing �˵�ʱ��seek���������osd���ݣ���ʾ�հ�
			pLocalParam->curTrack = 0;	// jing �˵�ʱ��seek���������osd���ݣ���ʾ�հ�
		}
			break;
		case 0x01:
			LOGD("                                         devState = ERROR DISC");
			str = "ERROR DISC";
			visible = 1;
			dvdToApp_displayDeviceStateOrTraceInfo(!visible);
			break;
		case 0x02:
		{
			LOGD("                                         devState = OPEN");			
			str = "OPEN";
			dvdToModule_NotifySystem_jumpPage(PAGE_DVD_OPEN);
			visible = 1;
			dvdToApp_displayDeviceStateOrTraceInfo(!visible);
			dvdToApp_clearAllStateWhenOpenDVD();

			
			pLocalParam->curTitle = 0;	// jing �˵�ʱ��seek���������osd���ݣ���ʾ�հ�
			pLocalParam->curTrack = 0;	// jing �˵�ʱ��seek���������osd���ݣ���ʾ�հ�

			pLocalParam->uTemdiscOpenStatus = 0x02;
		}
		break;
		case 0x03:
		{
				LOGD("                                         devState = CLOSING");			
				str = "CLOSING";
				visible = 1;
				pLocalParam->GetCLOSEMsg = 1;
				u16 curPage = 0;
				unsigned char curPageLen;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,(u8 *)&curPageLen);
				if(curPage != PAGE_BACK_VIDEO)
				{
					if(pLocalParam->uTemdiscOpenStatus == 0x02){
						dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);
					}

					pLocalParam->uTemdiscOpenStatus = 0x03;
				}
				dvdToApp_displayDeviceStateOrTraceInfo(!visible);
				break;
		}
		case 0x04:
			break;
		case 0x05:
		{
			LOGD("                                         devState = LOADING");	
			//add:2012-07-20 11:25:29   ��ֹ��closing״̬ʱ�޷��رճ���ҳ��
			u16 curPage = 0;
			u8 curPageLen;
			getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,(u8 *)&curPageLen);
			if(curPage == PAGE_DVD_OPEN)
				dvdToModule_NotifySystem_jumpPage(PAGE_DVD_MAIN);

			str = "LOADING";
			visible = 1;
			dvdToApp_displayDeviceStateOrTraceInfo(!visible);
			//��ֹSTOP״̬�ĳ���
				setSerialData(CONTROLID_DVD_MAIN_CURRENT_TIME,(u8*)"",0);
			break;
		}
		case 0x06:break;
		case 0x07:break;
		case 0x08:
			LOGD("                                         devState = NO DISC");			
			str = "NO DISC";
			pLocalParam->u_DisplayOsdDevType = 0xFF;
			visible = 1;
			dvdToApp_displayDeviceStateOrTraceInfo(!visible);
			break;
		case 0x09:break;
	/*	case 0x09:
			dvdToApp_SetStateWhenReady();
			break;     */
		case 0x0A:
			break;
	}

	//dvdToApp_displayDeviceStateOrTraceInfo(!visible);

	if(visible && str != NULL){
		len = ansi_str_to_unicode16((u8 *)str, (unicode16_t *)buffer);
		
		setSerialData(CONTROLID_DVD_MAIN_NO_DISC, buffer, len*2);
		
	}
	LOGW("DVD send device status:0x%x", devState);
	dvdToModule_NotifyAuxscreen_DeviceState(devState);
	
	
	
}

void  halToDvd_DevContent(unsigned char content){
	
}

void  halToDvd_DISCFileType(unsigned char discType, unsigned char fileType){
	pLocalParam->discType = discType;
	pLocalParam->fileType = fileType;
	
	char *pDiscType = "";

	switch(discType){
		case 0x00:			// None Media
		case 0x01:			// DeInitialized media	
		case 0x02:
			break;	// LIPS
		case 0x03:
		case 0x04:
			pDiscType = "DVD";
			pLocalParam->u_DisplayOsdDevType = 0x05;
			break;
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x08:
			pDiscType = "VCD";
			pLocalParam->u_DisplayOsdDevType = 0x02;
			break;
		case 0x09:break;
	}

	switch(fileType){
		case 0x00:break;
		case 0x01:
		case 0x02:
			pDiscType = "MP3";
			pLocalParam->u_DisplayOsdDevType = 0x04;
			break;
		case 0x03:
			pDiscType = "CD";
			pLocalParam->u_DisplayOsdDevType = 0x01;
			break;
		case 0x04:
		case 0x05:
		case 0x06:
			pDiscType = "AVI";
			pLocalParam->u_DisplayOsdDevType = 0x07;
			break;
		case 0x07:
		case 0x08:break;
	}

	if(pDiscType != NULL){
		unsigned char buffer[32];
		int len;
		len = ansi_str_to_unicode16((u8*)pDiscType,(unicode16_t *)buffer);
		setSerialData(CONTROLID_DVD_MAIN_TYPE_TEXT, buffer, 2*len);
	}

	dvdToApp_identifyTrackListOrFolder();
	dvdToApp_SetStateWhenReady();
	dvdToModule_NotifyAuxscreen_DiscInfo(discType, fileType);
	//moupeng 2015/7/31
	g_clsDvd.sendToFlyJniSdkDvdDiscAndFileType(discType, fileType);
	
	
}

void  halToDvd_TotalTitleTrack(unsigned short totalTitle, unsigned short totalTrack){
	//dvdToApp_SetStateWhenReady();
	pLocalParam->totalTitle = totalTitle;
	pLocalParam->totalTrack = totalTrack;

	LOGD(" halToDvd_TotalTitleTrack:%x",pLocalParam->totalTrack = totalTrack);

}

void  halToDvd_CurTitleTrack(unsigned short curTitle, unsigned short curTrack){
	//TODO
	LOGD("halToDvd_CurTitleTrack %x %x",curTitle,curTrack);
	//moupeng 2015/7/31
	g_clsDvd.sendToFlyJniSdkTitleAndTrack(curTitle, curTrack);
	
	
	audioVideoToModule_NotifyOsd_DVDTitleValue(pLocalParam->u_DisplayOsdDevType, curTitle, curTrack);
	dvdToApp_SetStateWhenReady();
	setVisible(CONTROLID_DVD_MAIN_NO_DISC,0);
	
	unicode16_t uniBuffer[96];
	uni16_size_t uniLen = 0;
	char buffer[34];
	setUpdateUI(0x00);
	
	pLocalParam->curTitle = curTitle;
	pLocalParam->curTrack = curTrack;
	
	sprintf(buffer, "%d", curTitle);
	uniLen = 0;
	uniLen = ansi_str_to_unicode16((u8*)buffer, uniBuffer);
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TITLE_NUM, (u8*)uniBuffer, 2*uniLen);
	
	char *strTitle = NULL;
	unsigned char realBuffer1[40];
	int str1Len;
	strTitle = "Title";
	str1Len =  ansi_str_to_unicode16((u8 *)strTitle,(unicode16_t *)realBuffer1);
	setSerialData(CONTROLID_DVD_MAIN_TITLE_TEXT,realBuffer1,2 * str1Len);
	
	sprintf(buffer, "%d", curTrack);
	uniLen = 0;
	uniLen = ansi_str_to_unicode16((u8*)buffer, uniBuffer);
	setSerialData(CONTROLID_DVD_MAIN_CURRENT_TRACK_NUM, (u8*)uniBuffer, 2*uniLen);

	char *strTrack= NULL;
	unsigned char realBuffer2[40];
	int str2Len;
	strTrack= "Track";
	str2Len =  ansi_str_to_unicode16((u8 *)strTrack,(unicode16_t *)realBuffer2);
	setSerialData(CONTROLID_DVD_MAIN_TRACK_TEXT,realBuffer2,2 * str2Len);
	setUpdateUI(0x01);	

	u16 curPageId = 0;
	u8 curpageLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);

	u8 cOsd_Event = 0;
	u8 	cOsd_EventLen = 0;
	getOtherModuleParam(MODULE_ID_OSD,OSD_EVENT,(u8*)&cOsd_Event,&cOsd_EventLen);
	LOGD("----cOsd_Event--%x-",cOsd_Event);
	
	if(curPageId != PAGE_THIRD_PAGE && curPageId != PAGE_DVD_MAIN && curPageId != PAGE_DVD_TRACKLIST && curPageId != PAGE_DVD_FOLDER
		&& curPageId != PAGE_DVD_OPEN && curPageId != PAGE_DVD_VIDEO && curPageId != PAGE_DVD_VIDEO_CONTROL
		&& curPageId != PAGE_DVD_VIDEO_SET && cOsd_Event == 1)
	{
		u8 OsdDevType = pLocalParam->u_DisplayOsdDevType;
		//if(pLocalParam->playStatus == 0x00)
		//{   
		//	audioVideoToModule_NotifyOsd_DisplayOSDDVDInfo(0xFE, curTitle, curTrack);
		//}
		//else 
		{
			audioVideoToModule_NotifyOsd_DVDTitleValue(OsdDevType, curTitle, curTrack);
		}
		//pLocalParam->isKeyEvent = false;
	}

	LOGW("DVD send curtitle(%d) and curtrack(%d)", curTitle,  curTrack);
	dvdToModule_NotifyAuxscreen_TitleTrack(curTitle,curTrack);
	
}

void  halToDvd_TotalTime(unsigned char hour, unsigned char min, unsigned char sec){
	int	second = hour * 3600 + min*60 + sec;
	LOGD("TotalTime = %d", second);
	dvdToModule_NotifyAuxscreen_TotalTime(second);
}

void  halToDvd_EscapeTime(unsigned char hour, unsigned char min, unsigned char sec){
	
	pLocalParam->escapeTimeHour = hour;
	pLocalParam->escapeTimeMin = min;
	pLocalParam->escapeTimeSec = sec;

	if(pLocalParam->playStatus == 0x01||pLocalParam->playStatus == 0x03){
		unsigned char buffer[32];
		unsigned char realBuffer[160];
		int bufferLen;
		unsigned char *pRealBuf;
		int i;
		memset(buffer, 0x00, 32);          //set the array data zero
		memset(realBuffer, 0x00, 160);     //set the array data zero
		sprintf((char*)buffer, "%02d'%02d\"", min+hour*60, sec);
		bufferLen = ansi_str_to_unicode16(buffer, (unicode16_t *)realBuffer);
		setSerialData(CONTROLID_DVD_MAIN_CURRENT_TIME, realBuffer, 2*bufferLen);

		memset(buffer, 0x00, 32);          //set the array data zero
		memset(realBuffer, 0x00, 160);     //set the array data zero
		sprintf((char*)buffer, "%02d:%02d:%02d", hour, min, sec);
		bufferLen = ansi_str_to_unicode16(buffer, (unicode16_t *)realBuffer);
		setSerialData(CONTROLID_DVD_VIDEO_CONTROL_CURRENTTIME, realBuffer, 2*bufferLen);
	}

	int second = 0;
	second = hour*3600+min*60+sec;
	dvdToModule_NotifyAuxscreen_Time(second);
	dvdToModule_NotifyOSD_aboutT123_playtimes_Value(second);
	//moupeng 2015/7/31
	g_clsDvd.sendToFlyJniSdkCurrentTime(hour,min,sec);
}

void  halToDvd_PlayStateSpeed(unsigned char state, unsigned char speed){
	
	pLocalParam->playStatus = state;
	//moupeng 2015/7/30
	g_clsDvd.sendToFlyJniSdkPlayState(pLocalParam->playStatus);
	
	bool isModify = false;
	char *str = "";
	switch(state){
		case 0x00:
			str = "STOP";
			LOGD("-------halToDvd----STOP----------");
			pLocalParam->u_DisplayOsdPlayStatus = 0xFE;
			isModify = true;
			break;
		case 0x01:
		{
			str = "PLAY";
			if(pLocalParam->displayTraceInfo){
				dvdToApp_displayDeviceStateOrTraceInfo(true);
			}

			short DVDSound = 0;
			unsigned char soundLen;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&DVDSound,(u8 *)&soundLen);
			// TODO:
			if((DVDSound != CHANNEL_DVD_VIDEO && DVDSound != CHANNEL_DVD_CTRL) && !pLocalParam->IsPlayForBLCD){
				dvdToHal_IR(DVDTOHAL_IR_STOP);
			}
			isModify = true;
			break;
		}
		case 0x02:
			str = "PAUSE";
			isModify = true;
			break;
	
	}
	if(isModify)
	{
		unsigned char playStatusBuffer[40];

		int bufLen = ansi_str_to_unicode16((u8 *)str, (unicode16_t *)playStatusBuffer);
		setSerialData(CONTROLID_DVD_MAIN_CURRENT_TIME, playStatusBuffer, 2*bufLen);
	}
	dvdToModule_NotifyAuxscreen_PlayState(state);

}

void  halToDvd_PlayFolderName(unsigned char *name, int len){

	if(len == 2 && name[0] == 0 && name[1] == 0){
		pLocalParam->curPlayFolder.len = ansi_str_to_unicode16((u8 *)"ROOT", (unicode16_t *)pLocalParam->curPlayFolder.name);
		pLocalParam->curPlayFolder.len *= 2;
	}
	else{
		memcpy(pLocalParam->curPlayFolder.name, name, len);
		pLocalParam->curPlayFolder.len = len;
	}
	
	setSerialData(CONTROLID_DVD_MAIN_FOLDER_NAME, pLocalParam->curPlayFolder.name, pLocalParam->curPlayFolder.len);
}

void  halToDvd_PlayFileInfo(unsigned short localIndex, unsigned short globalIndex, char fileType, unsigned char *name, int len){
	char *fileSuffix = NULL;
	int i, suffixLen = 0;
	char *pCurPlayDir;

	memcpy(pLocalParam->curPlayFile.name, name, len);
	pLocalParam->curPlayFile.len = len;
	pLocalParam->curPlayFileIndex = globalIndex; 

	setSerialData(CONTROLID_DVD_MAIN_FILE_NAME, pLocalParam->curPlayFile.name,pLocalParam->curPlayFile.len);

	if(pLocalParam->trackList_Enable){
        dvdToApp_DisplayPlayCDIndex(globalIndex);
	}

	if(pLocalParam->folder_Enable){
		for(i = 0; i < FILE_FOLDER_ITEM_COUNT; ++i){
			if(pLocalParam->fileFolderItem[i].isBlank){
				setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i,0);
				continue;
			}
			
			if(pLocalParam->fileFolderItem[i].globalIndex == globalIndex){
				if(pLocalParam->fileFolderItem[i].isFile){
					setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i,3);
				}
				else{
					setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i,1);
				}
			}
			else{
				if(pLocalParam->fileFolderItem[i].isFile){
					setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i,2);
				}
				else{
					setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN+i,1);
				}
			}
		}
	}
	else if(pLocalParam->trackList_Enable){//----------------2012-7-25----chenbohong-----------//
		if(pLocalParam->curPlayFileIndex < 20)
			setDigitalData(pLocalParam->curPlayFileIndex%20+CONTROLID_DVD_TRACKLIST_BEGIN, 1);
	}
	
}

void halInit_ResponseDVD(void){
	setUpdateUI(0x00);
	setAnalogData(CONTROLID_DVD_MAIN_TRACKLIST, 2);
	setAnalogData(CONTROLID_DVD_MAIN_FOLDER_BUTTON, 2);
	setUpdateUI(0x01);
}

void analyseHalMessage_DVD(char resCmd, u8 *param, u8 len){ 
	
	LOGD("analyseHalMessage_DVD resCmd %x param[0] %x param[1] %x",resCmd,param[0],param[1]);
	switch(resCmd){
		case 0x01:
			 halToDvd_InitCmd(param[0]);
			break;
		case 0x02:
			 halToDvd_InitState(param[0]);
			break;
		case 0x10:
			 halToDvd_ErrCode(param[0]);
			break;
		case 0x11:
			 halToDvd_PlayMode(param[0]);
			break;
		case 0x12:{
				u16 totalNum, folderNum;
				u8 isRootFolder = param[4];
				
				totalNum = (u16)((param[0] << 8) & 0xFF00);
				totalNum += (u16)(param[1] & 0xFF);

				folderNum = (u16)((param[2] << 8) & 0xFF00);
				folderNum += (u16)(param[3] & 0xFF);
				
				halToDvd_ClipsInfo(totalNum, folderNum, isRootFolder);
			}
			break;
		case 0x13:{
				u16 itemIndex;		// local Index
				u16 folderFileIndex;	// global Index
				char isFile;
				u8 *folderFileName;
				int folderFileNameLen;
				
				itemIndex = (u16)((param[0] << 8) & 0xFF00);
				itemIndex += (u16)(param[1]);
				folderFileIndex = (u16)((param[2] << 8) & 0xFF00);
				folderFileIndex += (u16)(param[3]);
				isFile = (char)param[4];
				folderFileNameLen = len - 5;
				folderFileName = &param[5];
				
				halToDvd_FolderFileName(itemIndex, folderFileIndex, isFile, folderFileName, folderFileNameLen);
			}
			break;
		case 0x15:
			 halToDvd_VideoMode(param[0]);
			break;
		case 0x20:
			 halToDvd_CurPlayDev(param[0]);
			break;
		case 0x21:
			 halToDvd_DISCDevState(param[0],param[1]);
			break;
		case 0x22:
			 halToDvd_DevContent(param[0]);
			break;
		case 0x23:
			 halToDvd_DISCFileType(param[0],param[1]);
			break;
		case 0x24:{
				unsigned short totalTitle;
				unsigned short totalTrack;
				totalTitle =  (unsigned short)((param[0])<<8 & 0xFF00);
				totalTitle += (unsigned short)(param[1] & 0xFF);
				totalTrack =  (unsigned short)((param[2])<<8 & 0xFF00);
				totalTrack += (unsigned short)(param[3] & 0xFF);
				
				halToDvd_TotalTitleTrack(totalTitle, totalTrack);
			}
			break;
		case 0x25:{
				unsigned short curTitle;
				unsigned short curTrack;

				curTitle =  (unsigned short)((param[0])<<8) & 0xFF00;
				curTitle += (unsigned short)(param[1] & 0xFF);
				curTrack =  (unsigned short)((param[2])<<8) & 0xFF00;
				curTrack += (unsigned short)(param[3] & 0xFF);
			
				halToDvd_CurTitleTrack(curTitle,curTrack);
			}
			break;
		case 0x26:{
				unsigned char totalHour, totalMin, totalSec;

				totalHour = param[0];
				totalMin = param[1];
				totalSec = param[2];

				halToDvd_TotalTime(totalHour, totalMin, totalSec);
			}
			break;
		case 0x27:{

				unsigned char escapeHour, escapeMin, escapeSec;
				
				escapeHour = param[0];
				escapeMin = param[1];
				escapeSec = param[2];
				
				halToDvd_EscapeTime(escapeHour, escapeMin, escapeSec);
			}
			break;
		case 0x28:
			 halToDvd_PlayStateSpeed(param[0], param[1]);
			break;
		case 0x29:
			 halToDvd_PlayFolderName(param, len);
			break;
		case 0x2A:{
				unsigned short localIndex;
				unsigned short globalIndex;
				char fileType;
				unsigned char *fileName;
				int fileNameLen;
                
				localIndex = (unsigned short)((param[0]) << 8) & 0xFF00;
				localIndex += (unsigned short)(param[1]) & 0xFF;
				globalIndex = (unsigned short)((param[2]) << 8) & 0xFF00;
				globalIndex += (unsigned short)(param[3]) & 0xFF;
				
				fileType = param[4];
				fileName = &param[5];
				fileNameLen = len - 5;
				
				halToDvd_PlayFileInfo(localIndex, globalIndex, fileType, fileName, fileNameLen);
			}
			break;
	}
}
