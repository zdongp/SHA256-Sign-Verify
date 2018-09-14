#include <stdio.h>
#include <stdlib.h>
#include "param.h"
#include "global.h"
#include "pageID.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"

#include "moduleParamRequest.h"
#include "moduleParamResponse.h"

#include "appRequestFunction.h"

void moduleToMedia_FromSystemMessage(unsigned char *param, unsigned char len)
{
	switch(param[0]){
		case 0x01:
		{
			if(param[1] ==0x01)
			{
				mediaToModule_NotifyAuxscreen_PlayState(pLocalParam->mediaPlayState);
				mediaToModule_NotifyAuxscreen_TotalAndTrack((short)pLocalParam->currenTrack,(short)pLocalParam->totalTrack);
				mediaToModule_NotifyAuxscreen_SongName(pLocalParam->curSongName, strlen((char *)pLocalParam->curSongName));
				mediaToModule_NotifyAuxscreen_SongArtist(pLocalParam->curSongArtist,strlen((char *)pLocalParam->curSongArtist));
				mediaToModule_NotifyAuxscreen_SongAlbum(pLocalParam->curSongAlbum, strlen((char *)pLocalParam->curSongAlbum));
				mediaToModule_NotifyAuxscreen_DeviceName(pLocalParam->usbDeviceName, strlen((char *)pLocalParam->usbDeviceName));
			}
		}
			break;
		case 0x14:
			break;
		default:break;
	}
}

void moduleToMedia_ProcessPanelKey_AV(void)
{
	if(isInMediaPage())
	{
		mediaToModule_NotifySystem_SwitchModule();
	}
	else if(isInMediaOtherPage())
	{
		mediaToModule_NotifySystem_jumpPage(PAGE_MEDIA);
	}
	else
	{
		mediaToModule_NotifySystem_jumpPage(PAGE_MEDIA);				
	}
}

void moduleToMedia_PanKB_Media()
{
	u16 curPage = 0;
	unsigned char curPageLen = 1;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);
	if (curPage != PAGE_MEDIA)
	{
		mediaToModule_NotifySystem_jumpPage(PAGE_MEDIA);
	}

}

void showMediaOSD()
{
	u16 CurPageID = 0;
	u8 CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen);
	u8  DropOSDVisible = 0;
	u8  DropOSDVisiblelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_HOMEPAGE_OSD_VISIBLE,(u8*)&DropOSDVisible,&DropOSDVisiblelen);
	if(DropOSDVisible == 0 && CurPageID == PAGE_THIRD_PAGE)
	{
		LOGD("[%s]DropOSDVisible= %d",__FUNCTION__,DropOSDVisible);
	}
	else
	{
		LOGD("jing -----mediaToModule_NotifyOsd_DisplayOSDMediaInfo -- CurPageID = %x ",CurPageID);
		if(CurPageID != PAGE_MEDIA && CurPageID != PAGE_MEDIA && !(CurPageID >= PAGE_BACK_NOVIDEO && CurPageID <= PAGE_BACK_FULL_VIDEO_CONTROL))
		{
			if(pLocalParam->totalTrack==0)
				pLocalParam->currenTrack=0;
			mediaToModule_NotifyOsd_t123_DisplayTitle();
			mediaToModule_NotifyOsd_t123_DisplayOSDMediaInfo((u16)pLocalParam->currenTrack,(u16)pLocalParam->totalTrack);

		}
	}
}
void moduleToMedia_FromKey_GetPanelKey(unsigned char keyValue){
	LOGD("keyValue:%X", keyValue);


	switch (keyValue){
		case KEY_AV:
			moduleToMedia_ProcessPanelKey_AV();
			break;
		case 0x17:
		    moduleToMedia_PanKB_Media();
		    break;
		case KEY_SEEK_INC:
		case KEY_TUNE_INC:
			mediaToApp_playNext();
			// jing 2013-8-2
			// �жϵ�ǰҳ�治�ڶ�ý��ҳ��͵���ҳ�����ʾ����osd
			// ��ý��ҳ����� PAGE_MEDIA PAGE_MEDIA
			// ����ҳ���� PAGE_BACK_NOVIDEO=0x0700 �� PAGE_BACK_FULL_VIDEO_CONTROL= 0x0704 �����
			showMediaOSD();
			break;
		case KEY_SEEK_DEC:
		case KEY_TUNE_DEC:
			mediaToApp_palyPrev();
			// jing 2013-8-2
			// �жϵ�ǰҳ�治�ڶ�ý��ҳ��͵���ҳ�����ʾ����osd
			// ��ý��ҳ����� PAGE_MEDIA PAGE_MEDIA
			// ����ҳ���� PAGE_BACK_NOVIDEO=0x0700 �� PAGE_BACK_FULL_VIDEO_CONTROL= 0x0704 �����
			showMediaOSD();
			break;
		default:
			break;
		}

}

void moduleToMedia_FromAudioVideo_GetSoundChannel(u8 nSoundChannel)
{
	LOGD("moduleToMedia_FromAudioVideo_GetSoundChannel nSoundChannel:%x",nSoundChannel);
	if(nSoundChannel == CHANNEL_MP3){
		mediaToApp_SendMediaChannelState(1);

		LOGD("++++pLocalParam->currenTrack,pLocalParam->totalTrack:%d %d",pLocalParam->currenTrack,pLocalParam->totalTrack);

		
		mediaToModule_NotifyAuxscreen_TotalAndTrack(pLocalParam->currenTrack,pLocalParam->totalTrack);

		int nSongNameLen = strlen((char*)(pLocalParam->curSongName));
		LOGD("++++pLocalParam->curSongName:%s(%d)",pLocalParam->curSongName,nSongNameLen);
		mediaToModule_NotifyAuxscreen_SongName(pLocalParam->curSongName,nSongNameLen);

		int nSongArtistLen = strlen((char*)(pLocalParam->curSongArtist));
		mediaToModule_NotifyAuxscreen_SongArtist(pLocalParam->curSongArtist, nSongArtistLen);

		int nSongAlbumLen = strlen((char*)(pLocalParam->curSongArtist));
		mediaToModule_NotifyAuxscreen_SongAlbum(pLocalParam->curSongAlbum, nSongAlbumLen);

		int nameLen = strlen((char *)pLocalParam->usbDeviceName);
		mediaToModule_NotifyAuxscreen_DeviceName(pLocalParam->usbDeviceName,nameLen);
	}
	else
	{
		mediaToApp_SendMediaChannelState(0);
		if(nSoundChannel == CHANNEL_THREECHANNEL)
		{
			mediaToModule_NotifyAuxscreen_TotalAndTrack(0x00,0x00);
			mediaToModule_NotifyAuxscreen_Time(0);
			mediaToModule_NotifyAuxscreen_TotalTime(0);
			mediaToModule_NotifyAuxscreen_PlayState(0);
			mediaToModule_NotifyAuxscreen_SongName((u8 *)" ",0x01);
			mediaToModule_NotifyAuxscreen_SongArtist((u8 *)" ",0x01);
			mediaToModule_NotifyAuxscreen_SongAlbum((u8 *)" ",0x01);
			mediaToModule_NotifyAuxscreen_DeviceName((u8 *)" ",0x01);
		}
	}
}


void moduleToMedia_FromKey_Message(unsigned char *param, unsigned char len)
{
	switch(param[0]){
		case 0x00:	
			moduleToMedia_FromKey_GetPanelKey(param[1]);
			break;
		case 0x01:	
			//moduleToMedia_FromKey_JumpToVideoPage();
			break;
		default:
			break;
	}

}

void moduleToMedia_FromAudioVideoMessage(u8 *param, u8 len)
{
	switch(param[0]){
		case 0x00:	
			moduleToMedia_FromAudioVideo_GetSoundChannel(param[1]);
			break;
		case 0x01:
			mediaToApp_enterMediaChannel_IsNormal(param[1]);
			break;
		default:
			break;
	}
}


int isInMediaPage()
{
	u16 wCurPage  = 0;
	u8 len=0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&wCurPage, (u8 *)&len);

	if(wCurPage==(u16)PAGE_MEDIA)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int isInMediaOtherPage()
{
	u16 wCurPage  = 0;
	u8 len=0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&wCurPage, (u8 *)&len);

	if(wCurPage==(u16)PAGE_MEDIA_SEARCH)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void moduleToMedia_FromExternalCtrlMessage(u8 *param, u8 len)
{
	switch(param[0])
	{
		case 0x01:
		{
			if(param[1] == 0x01)
				mediaToModule_NotifySystem_jumpPage(PAGE_MEDIA);
		}
		break;
		case 0xFF:
		{
			getVoiceStatusFromExternalctrl(param[1]);
		}
		break;
	}
}

void moduleToMedia_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    switch(param[0])
    {
    	case 0xff:
    		analyseAppMessage(param+1,len-1);
		break;
		case 0x01:
			Automate_selectMusic(param[1]);
		break;
		case 0x02:
			Automate_GoToAutoMate(param[1]);
		break;
		case 0x04:    
			Automate_getUSBState(1);
		break;
		case 0x05:
			Automate_getUSBState(1);
		break;
    }
}

void moduleToMedia_FromJniSdk(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    switch(param[0])
    {
	    case 0x01:
		{
			if(param[1] == 0x00||param[1] == 0x01)
			{	
				u16 curPage = 0;
				unsigned char curPageLen;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,&curPageLen);
				if(curPage == PAGE_MEDIA)
				{
					if(param[1] == 0x01)
					mediaToApp_play();
				}	
				else
					mediaToModule_NotifySystem_jumpPage(PAGE_MEDIA);
			}
	    }		
		break;
		case 0x02:
			mediaToApp_SpecifyToPlayTheSongOrNo(param,(u8)len);
		break;
		case 0xFF:
		{
			LOGD("FLYJNISDK To MEDIA Set Paly:%x %x",param[1],param[2]);
			if(param[1] == 0x00)
			{
				switch(param[2])
				{
					case 0x00://Prev
					mediaToApp_palyPrev();
					break;
					case 0x01://Next
					mediaToApp_playNext();
					break;
					case 0x02://pause
					mediaToApp_pause();
					break;
					case 0x03://play
					mediaToApp_play();
					break;
					case 0x04://stop
					mediaToApp_stop();
					break;
					case 0x05://finish
					mediaToApp_finishPlay();
					break;
				}
			}
			else if(param[1] == 0x01)
			{
				mediaToApp_SetplayMod(param[2]);
			}
		}
		break;
		default:break;
    }
}


void getVoiceStatusFromExternalctrl(u8 param)
{
	if(param == 0x00)
	{
		pLocalParam->mediaVoiceState = false;
	}
	else if(param == 0x01)
	{
		pLocalParam->mediaVoiceState = true;
	}
}
 

