#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"

void appToMedia_MenuMedia_MouseUp()
{
	mediaToModule_NotifySystem_jumpPage(PAGE_MEDIA);
}

void appToMedia_MainBack_MouseUp()
{
		mediaToModule_NotifySystem_jumpPage(PAGE_MENU);
}


void appToMedia_GetMediaPlayState(u8 state )
{
	mediaToModule_NotifyAudiovideo_MediaPlayStates(state);
	mediaToModule_NotifyAuxscreen_PlayState(state);

}
void appToMedia_GetMediaPlayAndTotalTime(u8* param,int len )
{
	u16 playTime=0;
	u16 totalTime=0;
	totalTime=param[0]*256+param[1];
	playTime=param[2]*256+param[3];
	
	mediaToModule_NotifyAuxscreen_Time(playTime);
	mediaToModule_NotifyAuxscreen_TotalTime(totalTime);
}
void appToMedia_GetMediaPlaySongName(u8 *param,int len)
{
	LOGD("appToMedia_GetMediaPlaySongName:len=%d",len);
	if(strcmp((char *)param,(char *)pLocalParam->curSongName) == NULL)
		return;
		
	memset(pLocalParam->curSongName, 0, sizeof(pLocalParam->curSongName));
	memcpy(pLocalParam->curSongName, param, len);
	mediaToModule_NotifyAuxscreen_SongName(param, len);
}

void appToMedia_GetMediaPlaySongArtist(u8 *param,int len)
{
	if(strcmp((char *)param,(char *)pLocalParam->curSongArtist) == NULL)
		return;

	memset(pLocalParam->curSongArtist, 0, sizeof(pLocalParam->curSongArtist));
	memcpy(pLocalParam->curSongArtist, param, len);
	mediaToModule_NotifyAuxscreen_SongArtist(param, len);
}

void appToMedia_GetMediaPlaySongAlbum(u8 *param,int len)
{
	if(strcmp((char *)param,(char *)pLocalParam->curSongAlbum) == NULL)
		return;

	memset(pLocalParam->curSongAlbum, 0, sizeof(pLocalParam->curSongAlbum));
	memcpy(pLocalParam->curSongAlbum, param, len);
	mediaToModule_NotifyAuxscreen_SongAlbum(param, len);
}

void appToMedia_GetMediaPlaySongtrack(u8 *param,int len)
{
	if(param[0] != 0x01)
		return;

	int Total_Track = param[1]*256*256*256+param[2]*256*256+param[3]*256+param[4];
	int Cur_Track  = param[5]*256*256*256+param[6]*256*256+param[7]*256+param[8];
	LOGD("[%s] totalTrack=%d,currenTrack=%d",__FUNCTION__,Total_Track,Cur_Track);
	
	if((Total_Track == pLocalParam->totalTrack) && (Cur_Track == pLocalParam->currenTrack))
		return;
	
	pLocalParam->totalTrack = Total_Track;
	pLocalParam->currenTrack = Cur_Track;

	mediaToModule_NotifyAuxscreen_TotalAndTrack((short)Cur_Track,(short)Total_Track);

	u16 CurPageID = 0;
	u8 CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&CurPageID, &CurPageIDLen);
	LOGD("jing -----mediaToModule_NotifyOsd_DisplayOSDMediaInfo -- CurPageID = %x ",CurPageID);
	u8  DropOSDVisible = 0;
	u8  DropOSDVisiblelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_HOMEPAGE_OSD_VISIBLE,(u8*)&DropOSDVisible,&DropOSDVisiblelen);
	if(DropOSDVisible == 0 && CurPageID == PAGE_THIRD_PAGE)
	{
		LOGD("[%s]DropOSDVisible= %d",__FUNCTION__,DropOSDVisible);
	}
	else
	{
		if( CurPageID != PAGE_MEDIA && CurPageID != PAGE_MEDIA && !(CurPageID >= PAGE_BACK_NOVIDEO && CurPageID <= PAGE_BACK_FULL_VIDEO_CONTROL))
		{
			//mediaToModule_NotifyOsd_t123_DisplayTitle();
			mediaToModule_NotifyOsd_t123_DisplayOSDMediaInfo((u16)Cur_Track,(u16)Total_Track);
		}
	}
}


void appToMedia_GetMediaUsbState(u8 *p,int len)
{
	pLocalParam->usb1state = p[0];
	LOGD("usb1state: %x",pLocalParam->usb1state);
	if(p[0] == 0x00)
	{
		//memset(pLocalParam->usbDeviceName,0,sizeof(pLocalParam->usbDeviceName));
		//mediaToModule_NotifyAuxscreen_ClearMediaInfo();
	}
	else
	{
		//memcpy(pLocalParam->usbDeviceName,"Media",5);
		//mediaToModule_NotifyAuxscreen_DeviceName(pLocalParam->usbDeviceName, strlen((char *)pLocalParam->usbDeviceName));
	}
}

void appToMedia_GetUSBDeviceName(u8 *p,int len)
{
	if(len < 1)
		return;
	memset(pLocalParam->usbDeviceName,0,sizeof(pLocalParam->usbDeviceName));
	if(len > 256)
		len = 256;
	memcpy(pLocalParam->usbDeviceName,p,len);
}

