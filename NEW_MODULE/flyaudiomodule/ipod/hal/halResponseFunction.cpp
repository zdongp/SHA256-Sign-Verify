#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "timer_interface.h"
#include "moduleParamRequest.h"
#include "moduleParamResponse.h"

/*
void analyseHalMessage_DVD(char resCmd, unsigned char *param, unsigned char len){

}
*/


//command命令是否执行成功
void halToIpod_GetReturnMessage(int iresult,int icommand)
{
	if(iresult == 0)//success
	{
		//CString str;
		//str.Format(L"\nCommand:0x%x is OK",icommand);
		//     TRACE(str);	  
		switch(icommand)
		{
		case 0x17://切换到相应播放类型 成功
			{
				if(pLocalParam->search)
				{
					switch(pLocalParam->browseInfo.iCurBrowsefolder)
					{
					case 0://应该不存在这种情况
						break;
					case 1://执行播放目录指令  相对与执行播放第一首
						ipodToHal_SetPlayListPlay(0);
						break;
					case 2://执行播放歌曲指令 
						ipodToHal_SetPlayListPlay(pLocalParam->browseInfo.iCurFilePos);
						break;
					}
					ipodToModule_NotifySystem_jumpPage(PAGE_IPOD);
					ipodToHal_SetTimeState();
					pLocalParam->search = false;				
				}
				else
				{
					ipodToHal_SetFirstItemPlay();
				}
			}
			break;
		case 0x26://自动返回时间 成功
			{
				int a=0;
				a++;
				usleep(50*1000);
				LOGD("************************call usleep(50*1000)");
			}
			break;
		case 0x29://播放控制 成功
			ipodToHal_SetTimeState();
			break;
		case 0x2e://设置随机模式 成功
			ipodToHal_QueryShuffleMode();
			break;
		case 0x31://设置循环模式 成功
			ipodToHal_QueryRepeatMode();
			break;
		case 0x38://表示成功切换到浏览目录
			ipodToHal_QueryTypeSum(5);
			break;
		}
	}
	else//不成功
	{
		switch(icommand)
		{
		case 0x02://出错 重新连接后一直发出该消息 则重新载入播放链表
		//	StartConnectIpod();
				  /*		  StartConnectIpod();
				  Message_SetMusicControl();
			Message_SetFirstItemPlay();*/
			break;
		}
		LOGD("Command:0x%x is not run",icommand);

	}
}

void halToIpod_GetConnectEcho(){
	if(pLocalParam->pingIpodSuccess || !pLocalParam->userConnected)
		return ;
	LOGD("IPOD Get Connect Echo!");
	pLocalParam->airMode =true;
	pLocalParam->pingIpodSuccess=1;
	setDigitalData(CONTROLID_IPOD_MAIN_CONNECTED,true);
	//thebug
	//CDrawButton *pButton = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_CONNECTED);
    //setData((int)1);

	//thebug
	//连接成功 删掉定时器
    //KillTimer(theApp.GetMainWnd()->m_hWnd,500);
    DeleteTimer(IPOD_CONNECT_TIMER);
	//SetTimer(5000,0,IPOD_PING_TIMER);

	short curSound = 0;
	unsigned char curSoundLen = 2;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, (u8 *)&curSoundLen);

	if (curSound != CHANNEL_IPOD_CTRL && curSound != CHANNEL_IPOD_VIDEO)
		{
			return;
		}
	
	
	ipodToHal_QueryCurPlayListSongSum();
	ipodToHal_QueryShuffleMode();
	ipodToHal_QueryRepeatMode();

	usleep(50*1000);
	
	ipodToHal_SetStartReturnTime();
	ipodToHal_SetTimeState();
}


void halToIpod_GetIPODType(int iType){
	pLocalParam->pingIpodSuccess=0;
	halToIpod_GetConnectEcho();
}



void halToIpod_GetTypeSum(int iSum){
	if(pLocalParam->search)
	{
		//CDrawGauge *pGauge;
		//pGauge = (CDrawGauge*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_GAUGE);
		if(pLocalParam->browseInfo.iCurBrowsefolder == 0&&pLocalParam->browseInfo.icurBrowseType != 5)//从一级目录进入二级目录
		{
			pLocalParam->browseInfo.icurTypeSum = iSum;
			pLocalParam->browseInfo.icurTypeShowPos = 0;
			pLocalParam->browseInfo.iCurBrowsefolder =1;
			//pGauge->SetYSize(iSum);
			//pGauge->SetYPos(0);
			setProgressRange(CONTROLID_IPOD_SEARCH_GAUGE,iSum - 1);
			setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,0);
            GetBrowseItemString();
		}
		else if(pLocalParam->browseInfo.iCurBrowsefolder == 0&&pLocalParam->browseInfo.icurBrowseType == 5)//第一级目录进入歌曲浏览
		{
			pLocalParam->browseInfo.iCurBrowsefolder =2;
			pLocalParam->browseInfo.iCurFileShowPos = 0;
			pLocalParam->browseInfo.icurFileSum = iSum;
			//pGauge->SetYSize(iSum);
			//pGauge->SetYPos(0);
			setProgressRange(CONTROLID_IPOD_SEARCH_GAUGE,iSum - 1);
			setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,0);
            GetBrowseItemString();	
		}
		else if(pLocalParam->browseInfo.iCurBrowsefolder == 2&&pLocalParam->browseInfo.icurBrowseType != 5)//第三级目录返回进入二级目录浏览
		{
			pLocalParam->browseInfo.icurTypeSum = iSum;
			pLocalParam->browseInfo.icurTypeShowPos = 0;
			pLocalParam->browseInfo.iCurBrowsefolder =1;
			//pGauge->SetYSize(iSum);
			//pGauge->SetYPos(0);
			setProgressRange(CONTROLID_IPOD_SEARCH_GAUGE,iSum - 1);
			setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,0);
            GetBrowseItemString();		    	
		}
		else if(pLocalParam->browseInfo.iCurBrowsefolder == 2&&pLocalParam->browseInfo.icurBrowseType == 5)//第三级歌曲浏览返回进入一级目录浏览
		{
			ipodToApp_EnterFirstSearchPage();

			
		}		
		else
		{
			pLocalParam->browseInfo.iCurBrowsefolder =2;
			pLocalParam->browseInfo.icurFileSum = iSum;
			pLocalParam->browseInfo.iCurFileShowPos = 0;
			//pGauge->SetYSize(iSum);
			//pGauge->SetYPos(0);
			setProgressRange(CONTROLID_IPOD_SEARCH_GAUGE,iSum - 1);
			setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,0);
			GetBrowseItemString();
		}
		//theApp.RefreshUI();
	}
	else
	{
		
		pLocalParam->typeListInfo.iSum = iSum;
	}	
}

void halToIpod_GetTypeItemString(int Command,u8 *str){
	//pLocalParam->browseInfo.icurTypeShowPos+5<pLocalParam->browseInfo.icurTypeSum
	static u8 fileFolderItem[5][256];
	if(pLocalParam->browseInfo.iCurBrowsefolder == 1)
	{
		int pos = Command-pLocalParam->browseInfo.icurTypeShowPos;
		if(pos<0||pos>4)
			return;
		memcpy(fileFolderItem[pos],str,2*uni16_strlen((u16 *)str)+2);
		if((pLocalParam->browseInfo.icurTypeShowPos+5 < pLocalParam->browseInfo.icurTypeSum)
			&& pos == 4)
		{
			setUpdateUI(0x00);
			int i = 0;
			for (;i<FILE_FOLDER_ITEM_COUNT;i++)
				ipodToApp_SetBrowseItemEnable(i,true,true,fileFolderItem[i],2*uni16_strlen((u16 *)fileFolderItem[i]));
			setUpdateUI(0x01);
		}
		else if( (pLocalParam->browseInfo.icurTypeShowPos+5 >= pLocalParam->browseInfo.icurTypeSum)
			&& pos == pLocalParam->browseInfo.icurTypeSum-pLocalParam->browseInfo.icurTypeShowPos-1)
		{
			setUpdateUI(0x00);
			int i = 0;
			for (;i<=pos;i++)
				ipodToApp_SetBrowseItemEnable(i,true,true,fileFolderItem[i],2*uni16_strlen((u16 *)fileFolderItem[i]));
			i = pos+1;
			for (;i<FILE_FOLDER_ITEM_COUNT;i++)
				ipodToApp_SetBrowseItemEnable(i,false,false,(u8 *)"",0);
			setUpdateUI(0x01);
		}
		//ipodToApp_SetBrowseItemEnable(pos,true,true,str,);
	}
	else
	{
		int pos = Command-pLocalParam->browseInfo.iCurFileShowPos;
		if(pos<0||pos>4)
			return;

		memcpy(fileFolderItem[pos],str,2*uni16_strlen((u16 *)str)+2);
		if((pLocalParam->browseInfo.iCurFileShowPos+5 < pLocalParam->browseInfo.icurFileSum)
			&& pos == 4)
		{
			setUpdateUI(0x00);
			int i = 0;
			for (;i<FILE_FOLDER_ITEM_COUNT;i++)
			{
				//if(isCurSong(i,fileFolderItem[i]))
					//ipodToApp_SetBrowseItemEnable(i,2,false,fileFolderItem[i],2*uni16_strlen(fileFolderItem[i]));
				//else 
					ipodToApp_SetBrowseItemEnable(i,true,false,fileFolderItem[i],2*uni16_strlen((u16 *)fileFolderItem[i]));
			}
			setUpdateUI(0x01);
		}
		else if( (pLocalParam->browseInfo.iCurFileShowPos+5 >= pLocalParam->browseInfo.icurFileSum)
			&& pos == pLocalParam->browseInfo.icurFileSum-pLocalParam->browseInfo.iCurFileShowPos-1)
		{
			setUpdateUI(0x00);
			int i = 0;
			for (;i<=pos;i++)
			{
				//if(isCurSong(i,fileFolderItem[i]))
					//ipodToApp_SetBrowseItemEnable(i,2,false,fileFolderItem[i],2*uni16_strlen(fileFolderItem[i]));
				//else 
					ipodToApp_SetBrowseItemEnable(i,true,false,fileFolderItem[i],2*uni16_strlen((u16 *)fileFolderItem[i]));
			}
			i = pos+1;
			for (;i<FILE_FOLDER_ITEM_COUNT;i++)
				ipodToApp_SetBrowseItemEnable(i,false,false,(u8 *)"",0);
			setUpdateUI(0x01);
		}

		
		//ipodToApp_SetBrowseItemEnable(pos,true,false,str,2*uni16_strlen(str));
	}

}

void halToIpod_GetTimeState(int iLength, int iNowTime,int iStatus){
	//thebug
	//Message_NoticeAllTime(iLength);//当前总时间

	//mustadd
	iLength /= 1000;
	int second = (iLength)%60;
	int minute = (iLength)/60;
	
	//unicode16_t uniBuffer[96];
	uni16_size_t strLen = 0;
	char buffer[16];
	{
		sprintf(buffer, "/%02d'%02d''", minute,second);
		strLen = ansi_str_to_unicode16((u8*)buffer, pLocalParam->mainTotalTime);
	
		//LOGD("halToIpod_GetReturnTime::::::%s::::%d",buffer,strLen);
		//str.Format(L"%02d'%02d''",minute,second);
		//Message_NoticeTime(iTime);
	}

	//setProgressRange(CONTROLID_IPOD_MAIN_GAUGE,iLength-1);
	//setSerialData(CONTROLID_IPOD_MAIN_CURRENT_SURPLUS_TIME, (u8*)uniBuffer, 2*strLen);
	//setVisible(CONTROLID_IPOD_MAIN_CURRENT_SURPLUS_TIME,true);


		
	if(pLocalParam->playStatus !=iStatus)	
	{
		switch(iStatus)
		{
		case 0x00://stop
			//Message_NoticePlayStatus(1);
			break;
		case 0x01://play  
			//Message_NoticeTrack();
			break;
		case 0x02://paused
			//Message_NoticePlayStatus(0);
			break;
		}
	}
	pLocalParam->playStatus = iStatus;
	
	if(iNowTime == 0)
	{
		ipodToHal_QueryCurPlayListSongSum();
		//SetTimer(1000,0,IPOD_NEXTSONG_TIMER);
	}
	if(pLocalParam->enter)//进入后第一次处理该消息
	{
		if(pLocalParam->initPlayStatus == true)
		{
			switch(iStatus)
			{
			case 0x00://stop
				ipodToHal_SetMusicControl();
				ipodToHal_SetFirstItemPlay();
				break;
			case 0x01://play  
				break;
			case 0x02://paused
				pLocalParam->contolPlayStatus = 1;
				ipodToHal_SetPlayPause();
				LOGD("IPOD Set Play!");
				break;
			}
		}
		else
		{
			switch(iStatus)
			{
			case 0x00://stop
				break;
			case 0x01://play
				pLocalParam->contolPlayStatus = 2;
				ipodToHal_SetPlayPause();
				break;
			case 0x02://paused
				break;				
			}
		}
	}
	else
	{		
		//CDrawText *pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TIMETXT);
		//CString str;
		u8 str[FILE_FOLDER_NAME_MAX_LEN];
		int strLen;
		switch(iStatus)
		{
		case 0x00://stop
			strLen = ansi_str_to_unicode16((u8*)"STOP",(unicode16_t *)str);
			break;
		case 0x01://play 
			strLen = ansi_str_to_unicode16((u8*)"PLAY",(unicode16_t *)str);
			return;
			break;
		case 0x02://paused
			strLen = ansi_str_to_unicode16((u8*)"PAUSE",(unicode16_t *)str);
			break;
		}
		strLen *= 2;
		//ipodToApp_SetCurrentTime(str,strLen);


		//setSerialData(CONTROLID_IPOD_MAIN_CURRENT_START_TIME,(u8 *)str,strLen);
		//setVisible(CONTROLID_IPOD_MAIN_CURRENT_START_TIME,true);
		//pText->SetData(str);
		//theApp.RefreshUI();
		//

		//thebug
		//SetTimer(theApp.m_pMainWnd->m_hWnd,502,500,NULL);//调用CheckControlPlayStatus
	}	
	pLocalParam->enter = false;
}

void halToIpod_GetTypeListIndex(int iNumber){
	//	TRACE(L"\n-------CIPODModule::Message_GetTypeListIndex()------------");
	//查询新的title  album  artist
	if(!pLocalParam->airMode)return;

	
	{
		//ipodToHal_QueryCurrentPositionMusicName(iNumber);	
		SetTimer(1000,1,IPOD_GETSONGNAME_TIMER);
	}
	
	
    if(pLocalParam->curTrack == iNumber)
	{
		return;
	}
	pLocalParam->curTrack = iNumber;
	//mustadd
	//Message_NoticeTrack();
	if(pLocalParam->showSubOSD)
	{
		//Message_SubOSD_SetMenu();
		//theApp.m_messageCenter.m_osdModule.SetwhichOSDShow(IPODSUBOSD);
		ipodToModule_NotifyOsd_DisplayOSDIpodInfo(pLocalParam->curTrack+1,pLocalParam->trackSum);
		pLocalParam->showSubOSD = 0;
	}
	ipodToApp_DisplayTrackMessage(pLocalParam->curTrack+1,pLocalParam->trackSum);	
	//	CString str;
	//	str.Format(L"\ncur Track:%d",m_icurTrack+1);
	//	TRACE(str);

}

void halToIpod_GetMusicName(u8 *iSongName){
	//CDrawText *pText;
	
	//pText = (CDrawText *)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_SONGTITLE);
	//pText->SetData(iSongName);
	//LOGD("iSongNameLen:%d",2*uni16_strlen((unicode16_t *) iSongName));
	updateTypeListInfo(iSongName);
	if(pLocalParam->search)
	{
		if(pLocalParam->browseInfo.iCurBrowsefolder == 2)
		{
			GetBrowseItemString();
		}
	}
	else
	{	
		//theApp.RefreshUI();
	}
	setUpdateUI(false);
	setSerialData(CONTROLID_IPOD_MAIN_SONG_NAME,(u8*)iSongName,2*uni16_strlen((unicode16_t *) iSongName));
	setVisible(CONTROLID_IPOD_MAIN_SONG_NAME,true);

	setUpdateUI(true);
	//setSerialData(0x0A0024,iSongName,2*uni16_strlen((unicode16_t *) iSongName));
	//setVisible(0x0A0024,true);
	//sleep();
	
	ipodToHal_QueryCurrentPositionArtist(pLocalParam->curTrack);
	
}

void halToIpod_GetMusicArtist(u8 *iArtist){
	//CDrawText *pText;
	//pText = (CDrawText *)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_SONGARTIST);
	//pText->SetData(iArtist);
	setUpdateUI(false);
	setSerialData(CONTROLID_IPOD_MAIN_SINGER_NAME,(u8*)iArtist,2*uni16_strlen((unicode16_t *) iArtist));
	setVisible(CONTROLID_IPOD_MAIN_SINGER_NAME,true);
	setUpdateUI(true);
	ipodToHal_QueryCurrentPositionAlbum(pLocalParam->curTrack);
	//theApp.RefreshUI();
}

void halToIpod_GetMusicAlbum(u8 *iAlbum){
	//CDrawText *pText;
	//pText = (CDrawText *)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_SONGALBUM);
	//pText->SetData(iAlbum);
	//theApp.RefreshUI();
	setUpdateUI(false);
	setSerialData(CONTROLID_IPOD_MAIN_ABLUM_NAME,(u8*)iAlbum,2*uni16_strlen((unicode16_t *) iAlbum));
	setVisible(CONTROLID_IPOD_MAIN_ABLUM_NAME,true);
	setUpdateUI(true);
}

void halToIpod_GetReturnTime(int iTime){
	//CDrawText *pText;
	int second = (iTime)%60;
	int minute = (iTime)/60;
	if(iTime == 0)
	{
		ipodToHal_QueryCurPlayListSongSum();
		//SetTimer(1000,0,IPOD_NEXTSONG_TIMER);
	}


	unicode16_t uniBuffer[96];
	uni16_size_t strLen = 0;
	char buffer[34];
	
	if(pLocalParam->playStatus == 0x01)
	{
		sprintf(buffer, "%02d'%02d''", minute,second);
		strLen = ansi_str_to_unicode16((u8*)buffer, uniBuffer);
		//mustadd
		//LOGD("halToIpod_GetReturnTime::::::%s::::%d",buffer,strLen);
		//str.Format(L"%02d'%02d''",minute,second);
		//Message_NoticeTime(iTime);
	}
	else
	{
		ipodToHal_SetTimeState();
		switch(pLocalParam->playStatus)
		{
		case 0x00://stop
			strLen = ansi_str_to_unicode16((u8*)"STOP",(unicode16_t *)uniBuffer);
			break;
		case 0x02://paused
			strLen = ansi_str_to_unicode16((u8*)"PAUSE",(unicode16_t *)uniBuffer);
			break;
		}
	}
	ipodToApp_SetCurrentTime((u8*)uniBuffer,strLen);

	//pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TIMETXT);
	//pText->SetData(str);
	//theApp.RefreshUI();
	
}

void halToIpod_GetShuffleMode(int iShuffleMode){
	pLocalParam->rand = iShuffleMode;
	//CDrawImage *pImage = (CDrawImage*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_RAND);
	switch(iShuffleMode)
	{
	case 0:
		//pImage->SetData((int)0);
		setGroupNumber(CONTROLID_IPOD_MAIN_SHUFFLE,0);
		break;
	case 1:
		//pImage->SetData((int)1);
		setGroupNumber(CONTROLID_IPOD_MAIN_SHUFFLE,1);
		break;
	case 2:
		ipodToHal_SetShuffleMode(0);
		break;
	default:
		ipodToHal_SetShuffleMode(0);
		break;
	}
	//theApp.RefreshUI();
}

void halToIpod_GetRepeatMode(int iRepeatMode){
	pLocalParam->RPT = iRepeatMode;
	//CDrawImage *pImage = (CDrawImage*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_RPT);
	switch (iRepeatMode)
	{
	case 0:
		setGroupNumber(CONTROLID_IPOD_MAIN_RPT,0);
		//pImage->SetData(0);
		break;
	case 1:
		setGroupNumber(CONTROLID_IPOD_MAIN_RPT,1);
		//pImage->SetData(1);
		break;
	case 2:
		setGroupNumber(CONTROLID_IPOD_MAIN_RPT,2);
		//pImage->SetData(2);
		break;
	default:
		break;
	}
	//theApp.RefreshUI();
}

void halToIpod_GetCurPlayListSongSum(int iSum){
	//SetTimer(1000,0,IPOD_NEXTSONG_TIMER);
	ipodToHal_QueryTypeListIndex();

	//	CString str1;
	//	str1.Format(L"\nIPOD :m_iTrackSum: %d iSum: %d",m_iTrackSum,iSum);
	//	TRACE(str1);
	if(pLocalParam->trackSum == iSum)
		return;
	pLocalParam->trackSum = iSum;
	//mustadd
	//Message_NoticeAllTrack();//当前总曲目
	//ipodToApp_DisplayTrackMessage(pLocalParam->curTrack+1,pLocalParam->trackSum);
}

void halToIpod_GetIPODConnect(int bConnect){
	if(pLocalParam->airMode == bConnect)
		return;
	if(pLocalParam->userConnected == false && bConnect == true)//用户有意断开 则继续断开
		return;
    pLocalParam->IPODConnect = bConnect;
	if(bConnect)//连接
	{
		StartConnectIpod();
	}
	else//断开
	{
		pLocalParam->airMode = false;
		//CDrawButton *pButton = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_CONNECTED);
        //SetData((int)0);
		ClearIPODMessage();
		
	}
}


int AnalyseCommand()
{
	int ucheckSum = 0,i;
	for(i=0;i<pLocalParam->commandBuff[2]+1;i++)
	{
		ucheckSum += pLocalParam->commandBuff[i+2];
	}
	ucheckSum= ucheckSum&0xff;
	ucheckSum= 0x100-ucheckSum;
	ucheckSum=(unsigned char)ucheckSum;
	if(ucheckSum != (int)pLocalParam->commandBuff[2+pLocalParam->commandBuff[2]+1])
	{
		int a=0;
		a++;
		return false;
	}
	switch(pLocalParam->commandBuff[3])   //模式
	{
    case 0x00:   //   Mode switching
		break;
    case 0x01:  //    Voice Recorder
		break;
    case 0x02:  //    Simple Remote
		break;
    case 0x04:  //     Advanced iPod Remote (AiR)
		return AnalyseAiRMode();
		break;
	case 0x66:
		//thebug
		LOGD("It is a BUG");
		//return AnalyseOtherMode();
		break;
    default:
		return false;
	}
	return true;
}


void analyseHalMessage_IPOD(unsigned char *buf, unsigned char len){
	int i;
	for(i=0;i<len;i++)
    {
		pLocalParam->commandBuff[pLocalParam->position]= buf[i];
		pLocalParam->position++;
		if(pLocalParam->position == 1)//第一位为0XFF
		{
			if(pLocalParam->commandBuff[0] != (unsigned char)0xFF)
				pLocalParam->position =0;
			continue;
		}
		if(pLocalParam->position == 2)//第二位为0X55
		{
			if(pLocalParam->commandBuff[1] != (unsigned char)0x55)
			{
				pLocalParam->position =0;
				analyseHalMessage_IPOD(pLocalParam->commandBuff+1,1);
			}
			continue;
		}
		if( pLocalParam->position == 3)//命令长度
		{
			pLocalParam->cmdlength = pLocalParam->commandBuff[2];
		}
		if(pLocalParam->position>= pLocalParam->cmdlength+4)
		{
			if(AnalyseCommand())
			{
				pLocalParam->position =0;
			}
			else
			{
				LOGD("AnalyseCommand() RETURN FALSE!");
				pLocalParam->position =0;
				analyseHalMessage_IPOD(pLocalParam->commandBuff+1,pLocalParam->cmdlength+3);
			}
		}		
		
    }

	
}



void GetBrowseItemString()
{
    //ipodToApp_SetBrowseItemHide();
	if(pLocalParam->browseInfo.iCurBrowsefolder == 1)//浏览目录
	{
		if(pLocalParam->browseInfo.icurTypeShowPos>=pLocalParam->browseInfo.icurTypeSum||pLocalParam->browseInfo.icurTypeShowPos<0)//越界
		{
			pLocalParam->browseInfo.icurTypeShowPos = 0;
		}
		if(pLocalParam->browseInfo.icurTypeSum == 0)
		{
			ipodToApp_SetBrowseItemHide();
		}
		else
		{
			if(pLocalParam->browseInfo.icurTypeShowPos+5<pLocalParam->browseInfo.icurTypeSum)
			{
				ipodToHal_QueryTypeItemString(pLocalParam->browseInfo.icurBrowseType,pLocalParam->browseInfo.icurTypeShowPos,5);
			}
			else
			{
				ipodToHal_QueryTypeItemString(pLocalParam->browseInfo.icurBrowseType,pLocalParam->browseInfo.icurTypeShowPos,pLocalParam->browseInfo.icurTypeSum-pLocalParam->browseInfo.icurTypeShowPos);
				
			}
		}
	}
	else if(pLocalParam->browseInfo.iCurBrowsefolder == 2)
	{
		if(pLocalParam->browseInfo.iCurFileShowPos>=pLocalParam->browseInfo.icurFileSum||pLocalParam->browseInfo.iCurFileShowPos<0)//越界
		{
			pLocalParam->browseInfo.iCurFileShowPos = 0;
		}
		if(pLocalParam->browseInfo.icurFileSum == 0)
		{
			ipodToApp_SetBrowseItemHide();
		}
		else
		{
			if(pLocalParam->browseInfo.iCurFileShowPos+5<pLocalParam->browseInfo.icurFileSum)
			{
				ipodToHal_QueryTypeItemString(5,pLocalParam->browseInfo.iCurFileShowPos,5);
			}
			else
			{
				ipodToHal_QueryTypeItemString(5,pLocalParam->browseInfo.iCurFileShowPos,pLocalParam->browseInfo.icurFileSum-pLocalParam->browseInfo.iCurFileShowPos);
				
			}
		}		
	}
	
}


int AnalyseAiRMode()
{
	switch(pLocalParam->commandBuff[5])     //命令序号
	{
	case 0x01:               //系统消息
		halToIpod_GetReturnMessage(pLocalParam->commandBuff[6],pLocalParam->commandBuff[7]*0x100+pLocalParam->commandBuff[8]);
        break;
	case 0x03:               //表示连接成功
        halToIpod_GetConnectEcho();
		break;
	case 0x13:               //得到IPOD型号
		halToIpod_GetIPODType(0x100*pLocalParam->commandBuff[6]+pLocalParam->commandBuff[7]);
        break;
	case 0x15:              //得倒IPOD名称
		{
			//int num = commandBuff[2]-3;
			//unsigned char buff[128];
			//memcpy(buff,UTF_8ToUnicode(commandBuff+6,num),128);               
			//CString str;
			//str.Format(_T("%s"),buff); 
			//theApp.m_messageCenter.m_iPodModule.Message_GetIPODName(str);
		}
        break;
	case 0x19:               //得到所指类型总数
		{
          int num = pLocalParam->commandBuff[6]*0x1000000+pLocalParam->commandBuff[7]*0x10000+
			        pLocalParam->commandBuff[8]*0x100+pLocalParam->commandBuff[9];
			halToIpod_GetTypeSum(num);
		}
		break;
	case 0x1B:   //获取所指位置的内容
		{
		  int position = pLocalParam->commandBuff[6]*0x1000000+pLocalParam->commandBuff[7]*0x10000+
			        pLocalParam->commandBuff[8]*0x100+pLocalParam->commandBuff[9];
			int num = pLocalParam->commandBuff[2]-7;
			unsigned char buff[128];
			utf8_to_unicode16( pLocalParam->commandBuff+10,(unsigned short *)buff);               
			//CString str;
			//str.Format(_T("%s"),buff); 
		    halToIpod_GetTypeItemString(position,buff);
		}
		break;
	case 0x1D:             //得到正在播放歌曲的状态
		{
			int totalTime = pLocalParam->commandBuff[6]*0x1000000+ pLocalParam->commandBuff[7]*0x10000+
			         pLocalParam->commandBuff[8]*0x100+ pLocalParam->commandBuff[9];
			int elapsedtime =  pLocalParam->commandBuff[10]*0x1000000+ pLocalParam->commandBuff[11]*0x10000+
			         pLocalParam->commandBuff[12]*0x100+ pLocalParam->commandBuff[13]; 
              halToIpod_GetTimeState(totalTime,elapsedtime, pLocalParam->commandBuff[14]);
		}
		break;
	case 0x1F://得到当前歌曲所在当前播放列表位置
		{
			int position = pLocalParam->commandBuff[6]*0x1000000+ pLocalParam->commandBuff[7]*0x10000+
			         pLocalParam->commandBuff[8]*0x100+ pLocalParam->commandBuff[9];
			halToIpod_GetTypeListIndex(position);
		}
		break;
	case 0x21://返回查询歌曲的歌曲名称
		{
			int num =  pLocalParam->commandBuff[2]-3;
			unsigned char buff[128];
			utf8_to_unicode16( pLocalParam->commandBuff+6,(unsigned short *)buff);               
			//CString str;
			//str.Format(_T("%s"),buff); 
			halToIpod_GetMusicName(buff);

		}
		break;
	case 0x23://返回请求歌曲的演唱者
		{
			int num =  pLocalParam->commandBuff[2]-3;
			unsigned char buff[128];
			utf8_to_unicode16( pLocalParam->commandBuff+6,(unsigned short *)buff);               
			//CString str;
			//str.Format(_T("%s"),buff); 
			halToIpod_GetMusicArtist(buff);
		}
		break;
	case 0x25://返回请求歌曲的专辑
		{
			int num = pLocalParam->commandBuff[2]-3;
			unsigned char buff[128];
			utf8_to_unicode16( pLocalParam->commandBuff+6,(unsigned short *)buff);               
			//CString str;
			//str.Format(_T("%s"),buff); 
			halToIpod_GetMusicAlbum(buff);
		}
		break;
	case 0x27://返回当前歌曲播放时间
		{
			if(pLocalParam->commandBuff[6] == 0x00)
			{
				return true;
			}
			int time =(pLocalParam->commandBuff[8]*0x100+pLocalParam->commandBuff[9])/pLocalParam->commandBuff[6];
			if(time == 0)
				halToIpod_GetReturnTime(time);
			if((pLocalParam->commandBuff[8]*0x100+pLocalParam->commandBuff[9])%pLocalParam->commandBuff[6]!=0)
			halToIpod_GetReturnTime(time);
		}		
		break;	
	case 0x2d://返回随机播放模式
          halToIpod_GetShuffleMode(pLocalParam->commandBuff[6]);
		  break;
	case 0x30://返回循环方式
		 halToIpod_GetRepeatMode(pLocalParam->commandBuff[6]);
		 break;
	case 0x36:  //得到歌曲数在播放链表          
		{
			int num = pLocalParam->commandBuff[6]*0x1000000+pLocalParam->commandBuff[7]*0x10000+
				pLocalParam->commandBuff[8]*0x100+pLocalParam->commandBuff[9];
		  	halToIpod_GetCurPlayListSongSum(num);
		}
        break;

	default:
        return false;
		
	}
	return true;
}





