#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"


void ipodToApp_SetSerialData_Ansi2Unicode(int controlId, u8 *pBuf, int nLen)
{
	int nSendLen = nLen * 2;
	u8 *pwBuf = (u8*)malloc(nSendLen + 2);
	memset(pwBuf, 0, nSendLen + 2);
	ansi_str_to_unicode16(pBuf, (unsigned short *)pwBuf);
	setSerialData(controlId, pwBuf, nSendLen);
	free(pwBuf);
}

//使浏览项目是否有效
void ipodToApp_SetBrowseItemEnable(int item,bool bEnablePlay,bool bEnableSearch,u8 *pStr,int strLen)
{
	//strLen *=2;
	//CDrawButton *pButtonPlay,*pButtonBrowse;
	//CDrawText *pText;
	//pText->SetData(pStr);
	pLocalParam->browseEnable[item][0] = bEnablePlay;
	pLocalParam->browseEnable[item][1] = bEnableSearch;
	if(item<0 || item >4)
		return;
	//setUpdateUI(false);
	if(bEnableSearch)
	{
		setGroupNumber(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+item,1);
	}
	else if(bEnablePlay)
	{
		if(bEnablePlay == 2)
			setGroupNumber(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+item,3);
		else 
			setGroupNumber(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+item,2);
	}
	else 
		{
			setGroupNumber(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+item,0);
		}
	setSerialData(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+item,(u8 *)pStr,strLen);
	//setUpdateUI(true);
	/*
	switch(item)
	{
	case 0:
		//pButtonPlay = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_PLAY1); 		
		//pButtonBrowse = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_BROWSE1); 
		//pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TXT1);
		
		break;
	case 1:
		//pButtonPlay = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_PLAY2); 		
		//pButtonBrowse = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_BROWSE2); 
		//pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TXT2);
		break;
	case 2:
		//pButtonPlay = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_PLAY3); 		
		//pButtonBrowse = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_BROWSE3); 
		//pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TXT3);
		break;
	case 3:
		//pButtonPlay = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_PLAY4); 		
		//pButtonBrowse = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_BROWSE4); 
		//pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TXT4);
		break;
	case 4:
		//pButtonPlay = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_PLAY4); 		
		//pButtonBrowse = (CDrawButton*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_BROWSE4); 
		//pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TXT4);
		break;
	default:
		return;
	}
	*/
	
	if(bEnablePlay)
	{
		//pButtonPlay->SetData(0);
	}
	else
	{
		//pButtonPlay->SetData(2);
		
	}
	if(bEnableSearch)
	{
		//pButtonBrowse->SetData(0);
	}
	else
	{
		//pButtonBrowse->SetData(2);
	}
    
}

//使所有浏览项目无效
void ipodToApp_SetBrowseItemHide()
{
	//thebug
	setUpdateUI(0x00);
	int i=0;
	//u8 empty[4] = {0x00, 0x00, 0x00, 0x00};
	for (;i<FILE_FOLDER_ITEM_COUNT;i++)
		{
		
			setSerialData(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+i, (u8*)"",0);
			setGroupNumber(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+i, 0);

			pLocalParam->browseEnable[i][0] = 0;
			pLocalParam->browseEnable[i][1] = 0;
			
			//setVisible(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+i, 0);
			//setControllable(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+i, 0);
		}
	setUpdateUI(0x01);
}


void ipodToApp_DisplayTrackMessage(int iTrack,int iTrackSum)
{
	//CDrawText *pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_POSITIONTXT);
	//CString str;
	//str.Format(L"%03d/%03d",iTrack,iTrackSum);
	
	//pText->SetData(str);
    //pText = (CDrawText*)theApp.m_project.GetDrawObjFromFuncID(FUNCID_IPOD_TRACKTXT);
	//pText->SetData((CString)L"TRACK");
    //pText->SetVisible(true);
   // theApp.RefreshUI();
    setUpdateUI(false);

	unicode16_t uniBuffer[96];
	uni16_size_t uniLen = 0;
	char buffer[34];
	
	sprintf(buffer, "%d/%d", iTrack,iTrackSum);
	uniLen = 0;
	uniLen = ansi_str_to_unicode16((u8*)buffer, uniBuffer);
	setSerialData(CONTROLID_IPOD_MAIN_CURRENT_TRACK_NUM, (u8*)uniBuffer, 2*uniLen);

	setVisible(CONTROLID_IPOD_MAIN_CURRENT_TRACK_NUM, true);
	setVisible(CONTROLID_IPOD_MAIN_TRACK_TEXT, true);

	setUpdateUI(true);
}

void ipodToApp_EnterFirstSearchPage(){
	//ipodToApp_SetBrowseItemHide();
	/*
	u8 str[FILE_FOLDER_NAME_MAX_LEN];
	u8 ansiStr[FILE_FOLDER_NAME_MAX_LEN/2];
	int strLen = 0;

	memset(ansiStr, 0, FILE_FOLDER_NAME_MAX_LEN/2);
	memcpy(ansiStr, IDS_PLAYLIST_SEARCH, sizeof(IDS_PLAYLIST_SEARCH));
	strLen = ansi_str_to_unicode16((u8*)ansiStr,(unicode16_t *)str);
	strLen *= 2;
	//str.LoadString(IDS_PLAYLIST_SEARCH);
	ipodToApp_SetBrowseItemEnable(0,false,true,str,strLen);
	LOGD("%s::::::::unicodeLen:%d",ansiStr,strLen);

	memset(ansiStr, 0, FILE_FOLDER_NAME_MAX_LEN/2);
	memcpy(ansiStr, IDS_ARTIST_SEARCH, sizeof(IDS_ARTIST_SEARCH));
	strLen = ansi_str_to_unicode16((u8*)ansiStr,(unicode16_t *)str);
	strLen *= 2;
	//str.LoadString(IDS_ARTIST_SEARCH);
	ipodToApp_SetBrowseItemEnable(1,false,true,str,strLen);

	memset(ansiStr, 0, FILE_FOLDER_NAME_MAX_LEN/2);
	memcpy(ansiStr, IDS_ALBUM_SEARCH, sizeof(IDS_ALBUM_SEARCH));
	strLen = ansi_str_to_unicode16((u8*)ansiStr,(unicode16_t *)str);
	strLen *= 2;
	//str.LoadString(IDS_ALBUM_SEARCH);	
	ipodToApp_SetBrowseItemEnable(2,false,true,str,strLen);

	memset(ansiStr, 0, FILE_FOLDER_NAME_MAX_LEN/2);
	memcpy(ansiStr, IDS_SONG_SEARCH, sizeof(IDS_SONG_SEARCH));
	strLen = ansi_str_to_unicode16((u8*)ansiStr,(unicode16_t *)str);
	strLen *= 2;
	//str.LoadString(IDS_SONG_SEARCH);	
	ipodToApp_SetBrowseItemEnable(3,false,true,str,strLen);

	ipodToApp_SetBrowseItemEnable(4,false,false,(u8*)"",0);
	setGroupNumber(CONTROLID_DVD_FOLDER_ITEM_BEGIN+4, 0);
	*/

	pLocalParam->browseInfo.iCurBrowsefolder = 0;
	pLocalParam->browseInfo.icurBrowseType = -1;
	pLocalParam->browseInfo.icurTypeShowPos =0;
	pLocalParam->browseInfo.icurTypeSum =0;
	pLocalParam->browseInfo.icurFileSum =0;
	pLocalParam->browseInfo.iCurFileShowPos = 0;
	//pGauge->SetYSize(3);
	//pGauge->SetYPos(0);	
	setProgressRange(CONTROLID_IPOD_SEARCH_GAUGE,3);
	setAnalogData(CONTROLID_IPOD_SEARCH_GAUGE,0);

			
	setUpdateUI(false);

	setAnalogData(CONTROLID_IPOD_SEARCH_CURPAGE,2);
	setControllable(CONTROLID_IPOD_SEARCH_CURPAGE,false);
		
	u8 str1[FILE_FOLDER_NAME_MAX_LEN]={IDS_PLAYLIST_SEARCH};
	ipodToApp_SetBrowseItemEnable(0,false,true,str1,2*uni16_strlen((unicode16_t *) str1));
	//LOGD("%s::::::::unicodeLen:%d",ansiStr,strLen);

	u8 str2[FILE_FOLDER_NAME_MAX_LEN]={IDS_ARTIST_SEARCH};
	ipodToApp_SetBrowseItemEnable(1,false,true,str2,2*uni16_strlen((unicode16_t *) str2));

	u8 str3[FILE_FOLDER_NAME_MAX_LEN]={IDS_ALBUM_SEARCH};
	ipodToApp_SetBrowseItemEnable(2,false,true,str3,2*uni16_strlen((unicode16_t *) str3));

	u8 str4[FILE_FOLDER_NAME_MAX_LEN]={IDS_SONG_SEARCH};
	ipodToApp_SetBrowseItemEnable(3,false,true,str4,2*uni16_strlen((unicode16_t *) str4));

	//setSerialData(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+4, (u8*)"",0);
	ipodToApp_SetBrowseItemEnable(4,false,false,(u8*)"",0);
	setUpdateUI(true);
	//setGroupNumber(CONTROLID_IPOD_SEARCH_ITEM_BEGIN+4, 0);
}

void ipodToApp_SetCurrentTime(u8 *str,int strLen)
{
	//unicode16_t strBuff[64];
	//uni16_strcat(str,pLocalParam->mainTotalTime);
	setUpdateUI(false);
	setSerialData(CONTROLID_IPOD_MAIN_CURRENT_TIME,(u8 *)str,2*uni16_strlen((u16 *)str));
	setVisible(CONTROLID_IPOD_MAIN_CURRENT_TIME,true);
	setUpdateUI(true);
}
