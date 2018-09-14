#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "moduleParamResponse.h"



void appToIpod_MainNext_MouseUp(){
	ipodToHal_SetSkipNext();

}

void appToIpod_MainPrev_MouseUp(){
	ipodToHal_SetSkipSuperior();
}

void appToIpod_MainPlayPause_MouseUp(){
	if(pLocalParam->playStatus == 1)
	{
		pLocalParam->contolPlayStatus = 2;
	}
	else
	{
		pLocalParam->contolPlayStatus = 1;
	}

	ipodToHal_SetPlayPause();
}

void appToIpod_MainShuffle_MouseUp(){
	if(pLocalParam->rand == 0)
	{
		ipodToHal_SetShuffleMode(1);
	}
	else
	{
		ipodToHal_SetShuffleMode(0);		
	}
}

void appToIpod_MainRPT_MouseUp(){
	switch(pLocalParam->RPT)
	{
	case 0x00:
		ipodToHal_SetRepeatMode(1);
		break;
	case 0x01:
		ipodToHal_SetRepeatMode(2);
		break;
	case 0x02:
		ipodToHal_SetRepeatMode(0);
		break;
	default:
		ipodToHal_SetRepeatMode(0);
		break;
	}
}

void appToIpod_EnterSearchPage(){
	if(!pLocalParam->airMode)
		return;

	pLocalParam->search = true;
	
	switch(pLocalParam->browseInfo.iCurBrowsefolder)
	{
	case 0:
		ipodToApp_EnterFirstSearchPage();
		ipodToHal_SetMusicControl();
		break;
	case 1://目录浏览
		if(pLocalParam->browseInfo.icurTypeShowPos<0)
			pLocalParam->browseInfo.icurTypeShowPos=0;
		ipodToHal_SetMusicControl();
		setProgressRange(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.icurTypeSum-1);
		setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.icurTypeShowPos);
		GetBrowseItemString();
		break;
	case 2://文件浏览
		if(pLocalParam->browseInfo.iCurFileShowPos<0)
			pLocalParam->browseInfo.iCurFileShowPos=0;
		//ipodToHal_SetMusicControl();
		setProgressRange(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.icurFileSum-1);
		setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.iCurFileShowPos);
		GetBrowseItemString();
		break;
	}
	
	ipodToModule_NotifySystem_jumpPage(PAGE_IPOD_SEARCH);		
}

void appToIpod_BrowseReturn(){
	switch(pLocalParam->browseInfo.iCurBrowsefolder)
	{
	case 0:
	case 1:
		{
			//CDrawGauge *pGauge;
			//pGauge = (CDrawGauge*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_GAUGE);

			ipodToApp_EnterFirstSearchPage();
			ipodToHal_SetMusicControl();
		}
		break;
	case 2:
		ipodToHal_SetMusicControl();
		ipodToHal_QueryTypeSum(pLocalParam->browseInfo.icurBrowseType);
		break;
	}
	//theApp.RefreshUI();
	
}

void appToIpod_SearchItem_MouseUp(int index){
	if(pLocalParam->browseEnable[index][1])
		appToIpod_BrowseItem(index);
	else
		appToIpod_PlayItem_MouseUp(index);
}

void appToIpod_PlayItem_MouseUp(int index){
	if(!pLocalParam->browseEnable[index][0])
		return;
	switch(pLocalParam->browseInfo.iCurBrowsefolder)
	{
	case 0:
		break;
	case 1://执行播放列表返回
		pLocalParam->browseInfo.icurTypePos = pLocalParam->browseInfo.icurTypeShowPos+index;
		ipodToHal_SetTypeMode(pLocalParam->browseInfo.icurBrowseType,pLocalParam->browseInfo.icurTypeShowPos+index);
		break;
	case 2://执行播放具体歌曲返回
		pLocalParam->browseInfo.iCurFilePos = pLocalParam->browseInfo.iCurFileShowPos+index;
		ipodToHal_SetTypeMode(pLocalParam->browseInfo.icurBrowseType,pLocalParam->browseInfo.icurTypePos);
		break;
	}
	
}

void appToIpod_BrowseItem(int index){
	if(!pLocalParam->browseEnable[index][1])
		return;
	switch(pLocalParam->browseInfo.iCurBrowsefolder)
	{
	case 0://根目录
		//thebug
		setAnalogData(CONTROLID_IPOD_SEARCH_CURPAGE,0);
		setControllable(CONTROLID_IPOD_SEARCH_CURPAGE,true);
		if(index == 3)
			{	
				pLocalParam->browseInfo.icurBrowseType =5;
				ipodToHal_QueryTypeSum(5);
			}
		else 
			{
				pLocalParam->browseInfo.icurBrowseType =index+1;
				ipodToHal_QueryTypeSum(index+1);
			}
		break;
	case 1://在二级目录
		pLocalParam->browseInfo.iCurFileShowPos =0;
		pLocalParam->browseInfo.icurTypePos = pLocalParam->browseInfo.icurTypeShowPos+index;
		ipodToHal_SetBrowseItem(pLocalParam->browseInfo.icurBrowseType,pLocalParam->browseInfo.icurTypeShowPos+index);
		break;
	case 2:// 在浏览歌曲时  没有浏览键存在
		break;
	default:
		break;
	}
}

void appToIpod_SearchNextPage_MouseUp(){
	/*
	if(pLocalParam->lastBrowsePos +5 > pLocalParam->fileNumOfCurFolder - 1)
		return;
	int num;
	num = pLocalParam->lastBrowsePos;

	pLocalParam->lastBrowsePos += 5;
	pLocalParam->browsePos += 5;
	
	if(pLocalParam->browsePos + 5>= pLocalParam->fileNumOfCurFolder){
		pLocalParam->browsePos = pLocalParam->fileNumOfCurFolder - 1;
		setAnalogData(CONTROLID_DVD_FOLDER_GAUGE,pLocalParam->browsePos);

		pLocalParam->browsePos = pLocalParam->lastBrowsePos;
		dvdToHal_RequestFileDirName(5,pLocalParam->browsePos);
		return;
	}

	dvdToHal_RequestFileDirName(5,pLocalParam->browsePos);
	setAnalogData(CONTROLID_DVD_FOLDER_GAUGE,pLocalParam->browsePos);

	*/



	switch(pLocalParam->browseInfo.iCurBrowsefolder)
	{
	case 0://不存在这种情况
		break;
	case 1://目录浏览
		if(pLocalParam->browseInfo.icurTypeShowPos+5<pLocalParam->browseInfo.icurTypeSum)
		{
			pLocalParam->browseInfo.icurTypeShowPos+=5;
			//if(pLocalParam->browseInfo.icurTypeShowPos+5>=pLocalParam->browseInfo.icurTypeSum)
			{
				//pLocalParam->browseInfo.icurTypeShowPos=pLocalParam->browseInfo.icurTypeSum-1;
			}
			//pGauge->SetYPos(m_browseInfo.icurTypeShowPos);
			
			if(pLocalParam->browseInfo.icurTypeShowPos + 5>= pLocalParam->browseInfo.icurTypeSum){
				//pLocalParam->browseInfo.icurTypeShowPos = pLocalParam->browseInfo.icurTypeSum - 1;
				setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.icurTypeSum - 1);
			
				//pLocalParam->browsePos = pLocalParam->lastBrowsePos;
				GetBrowseItemString();
				return;
			}

			
			setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.icurTypeShowPos);
			GetBrowseItemString();
		}
		break;
	case 2://文件浏览
		if(pLocalParam->browseInfo.iCurFileShowPos+5<pLocalParam->browseInfo.icurFileSum)
		{
			pLocalParam->browseInfo.iCurFileShowPos+=5;
			//if(pLocalParam->browseInfo.iCurFileShowPos+5>=pLocalParam->browseInfo.icurFileSum)
			{
				//pLocalParam->browseInfo.iCurFileShowPos=pLocalParam->browseInfo.icurFileSum-1;
			}
			//pGauge->SetYPos(m_browseInfo.iCurFileShowPos);

			if(pLocalParam->browseInfo.iCurFileShowPos + 5>= pLocalParam->browseInfo.icurFileSum){
				//pLocalParam->browseInfo.iCurFileShowPos = pLocalParam->browseInfo.icurFileSum - 1;
				setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.icurFileSum - 1);
			
				//pLocalParam->browsePos = pLocalParam->lastBrowsePos;
				GetBrowseItemString();
				return;
			}

			setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.iCurFileShowPos);
			GetBrowseItemString();
		}
		break;
	}
}

void appToIpod_SearchPrevPage_MouseUp(){
	/*
	pLocalParam->lastBrowsePos -= 5;
	pLocalParam->browsePos -= 5;

	if(pLocalParam->browsePos < 0){
		pLocalParam->browsePos = 0;
		pLocalParam->lastBrowsePos = 0;
		return;
	}
	dvdToHal_RequestFileDirName(5, pLocalParam->browsePos);
	setAnalogData(CONTROLID_DVD_FOLDER_GAUGE,pLocalParam->browsePos);
	*/




	switch(pLocalParam->browseInfo.iCurBrowsefolder)
	{
	case 0://不存在这种情况
		break;
	case 1://目录浏览
		if(pLocalParam->browseInfo.icurTypeShowPos>0)
		{
			pLocalParam->browseInfo.icurTypeShowPos-=5;
			if(pLocalParam->browseInfo.icurTypeShowPos<0)
				pLocalParam->browseInfo.icurTypeShowPos=0;
			//pGauge->SetYPos(m_browseInfo.icurTypeShowPos);
			setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.icurTypeShowPos);
			GetBrowseItemString();
		}
		break;
	case 2://文件浏览
		if(pLocalParam->browseInfo.iCurFileShowPos>0)
		{
			pLocalParam->browseInfo.iCurFileShowPos-=5;
			if(pLocalParam->browseInfo.iCurFileShowPos<0)
				pLocalParam->browseInfo.iCurFileShowPos=0;
			//pGauge->SetYPos(m_browseInfo.iCurFileShowPos);
			setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.iCurFileShowPos);
			GetBrowseItemString();
		}
		break;
	}
}


void appToIpod_SearchGauge_MouseUp(u8 *buffer,u8 len){
	int pos = 0;

	pos += (int)((buffer[0] << 24) & 0xFF000000);
	pos += (int)((buffer[1] << 16) & 0xFF0000);
	pos += (int)((buffer[2] << 8) & 0xFF00);
	pos += (int)(buffer[3] & 0xFF);


	switch(pLocalParam->browseInfo.iCurBrowsefolder)
	{
	case 0://不存在这种情况
		break;
	case 1://目录浏览
		pLocalParam->browseInfo.icurTypeShowPos = pos;
		//if(pLocalParam->browseInfo.icurTypeShowPos>0)
		{
			//pLocalParam->browseInfo.icurTypeShowPos-=5;
			if(pLocalParam->browseInfo.icurTypeShowPos<0)
				pLocalParam->browseInfo.icurTypeShowPos=0;
			//pGauge->SetYPos(m_browseInfo.icurTypeShowPos);
			//setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.icurTypeShowPos);
			GetBrowseItemString();
		}
		break;
	case 2://文件浏览
		pLocalParam->browseInfo.iCurFileShowPos = pos;
		//if(pLocalParam->browseInfo.iCurFileShowPos>0)
		{
			//pLocalParam->browseInfo.iCurFileShowPos-=5;
			if(pLocalParam->browseInfo.iCurFileShowPos<0)
				pLocalParam->browseInfo.iCurFileShowPos=0;
			//pGauge->SetYPos(m_browseInfo.iCurFileShowPos);
			//setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,pLocalParam->browseInfo.iCurFileShowPos);
			GetBrowseItemString();
		}
		break;
	}

	//pLocalParam->lastBrowsePos = pos;
	//pLocalParam->browsePos = pos;
	//pLocalParam->isSliderEvent = true;

	//dvdToHal_RequestFileDirName(5,pLocalParam->lastBrowsePos);
}

void appToIpod_MainConnected_MouseUp(){
	//CDrawButton *pButton = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_CONNECTED);
	//pButton->SetData((int)0);
	if(pLocalParam->airMode)
	{
		pLocalParam->userConnected = false;
		ipodToHal_LeaveAIRMode();
		pLocalParam->airMode =false;
		ClearIPODMessage();
		setDigitalData(CONTROLID_IPOD_MAIN_CONNECTED,false);
	}
	else
	{
		pLocalParam->userConnected = true;
		GetIPODConnect(1);
	}
	//theApp.RefreshUI();
}
