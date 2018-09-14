#include <stdio.h>
#include <stdlib.h>

#include "global.h"


#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleID.h"
#include "param.h"


void mediaToModule_NotifySystem_jumpPage(u16 pageID)
{
	 u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&pageID,2);
     makeAndSendMessageToModule(MODULE_ID_MEDIA,MODULE_ID_SYSTEM,buf,3);
	
}
void mediaToModule_NotifyAudiovideo_MediaPlayStates(u8 state)
{
	u8 buf[] = {0x01, state};

	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUDIOVIDEO, buf, 2);

}


void mediaToModule_NotifyAuxscreen_TotalAndTrack(short track, short total)
{

	unsigned char buf[] = {0x20,0x00,0x00,0x00,0x00};
	memcpy(&buf[1],&track,2);
	memcpy(&buf[3],&total,2);
	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUXSCREEN, buf, 5);
}
void mediaToModule_NotifyAuxscreen_Time(int time)

{
	unsigned char buff[] = {0x21, 0x00, 0x00, 0x00, 0x00};

	memcpy(&buff[1], &time, 4);
	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUXSCREEN, buff, 5);
}
void mediaToModule_NotifyAuxscreen_TotalTime(int time)
{
	unsigned char buff[] = {0x22, 0x00, 0x00, 0x00, 0x00};

	memcpy(&buff[1], &time, 4);
	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUXSCREEN, buff, 5);
}

void mediaToModule_NotifyAuxscreen_PlayState(char state)
{
	unsigned char buff[2] = {0x23, 0x00};
	if(state == 0)
		buff[1]=1;
	else
		buff[1]=0;
	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUXSCREEN, buff, 2);
}

void mediaToModule_NotifyAuxscreen_SongName(u8 *pBuf, int nLen)
{
	u8 szBuf[256] = {0};
	szBuf[0] = 0x24;
	memcpy(szBuf + 1, (char*)pBuf, nLen);
	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUXSCREEN, szBuf, nLen + 1);
}

void mediaToModule_NotifyAuxscreen_SongArtist(u8 *pBuf, int nLen)
{
	u8 szBuf[256] = {0};
	szBuf[0] = 0x25;
	memcpy(szBuf + 1, (char*)pBuf, nLen);
	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUXSCREEN, szBuf, nLen + 1);
}

void mediaToModule_NotifyAuxscreen_SongAlbum(u8 *pBuf, int nLen)
{
	u8 szBuf[256] = {0};
	szBuf[0] = 0x26;
	memcpy(szBuf + 1, (char*)pBuf, nLen);
	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUXSCREEN, szBuf, nLen + 1);
}

void mediaToModule_NotifyAuxscreen_DeviceName(u8 *pBuf, int nLen)
{
	u8 szBuf[300] = {0};
	szBuf[0] = 0x58;
	if(nLen  <= 0)
		nLen = 1;
	memcpy(szBuf + 1, (char*)pBuf, nLen);
	makeAndSendMessageToModule(MODULE_ID_MEDIA, MODULE_ID_AUXSCREEN, szBuf, nLen + 1);
}

void mediaToModule_NotifyAuxscreen_ClearMediaInfo()
{
	pLocalParam->totalTrack = 0x00;
	pLocalParam->currenTrack = 0x00;
	pLocalParam->mediaPlayState=0x00;
	mediaToModule_NotifyAuxscreen_TotalAndTrack(0x00, 0x00);
	mediaToModule_NotifyAuxscreen_PlayState(0);
	mediaToModule_NotifyAuxscreen_Time(0);
	mediaToModule_NotifyAuxscreen_TotalTime(0);
	memset(pLocalParam->curSongName, 0, sizeof(pLocalParam->curSongName));
	memset(pLocalParam->curSongArtist, 0, sizeof(pLocalParam->curSongArtist));
	memset(pLocalParam->curSongAlbum, 0, sizeof(pLocalParam->curSongAlbum));
	memset(pLocalParam->usbDeviceName,0,sizeof(pLocalParam->usbDeviceName));
	u8 pbuf[1] = {0};
	mediaToModule_NotifyAuxscreen_SongName(pbuf, 0x01);
	mediaToModule_NotifyAuxscreen_SongArtist(pbuf,0x01);
	mediaToModule_NotifyAuxscreen_SongAlbum(pbuf, 0x01);
	mediaToModule_NotifyAuxscreen_DeviceName(pbuf, 0x00);
}


void mediaToModule_NotifyOsd_DisplayOSDMediaInfo(unsigned char type,u16 title,u16 track){
	u8 buf[] = {0xEE, 0x10, 0x00,0x00,0x00,0x00,0x00};  // jing 2013-8-2

	buf[2] = type;
	buf[3] = (track >> 8) & 0xFF;
	buf[4] = track & 0xFF;
	buf[5] = (title>> 8) & 0xFF;
	buf[6] = title & 0xFF;
	
	makeAndSendMessageToModule(MODULE_ID_MEDIA,MODULE_ID_OSD,buf,7);
}

void mediaToModule_NotifySystem_SwitchModule(void)//
{
	unsigned char buff[] =  {0x81,MODULE_ID_MEDIA};
	makeAndSendMessageToModule(MODULE_ID_MEDIA,MODULE_ID_SYSTEM,buff,2);
}

void mediaToModule_NotifyOsd_t123_DisplayTitle()
{
	u8 buf[] = {0x01,0x14};
	makeAndSendMessageToModule(MODULE_ID_MEDIA,MODULE_ID_OSD,buf,2);
}
void mediaToModule_NotifyOsd_t123_DisplayOSDMediaInfo(u16 Current_Track,u16 Total_Track){
	u8 buf[] = {0x14,0x00,0x00,0x00,0x00};

    buf[1] = Current_Track&0x00FF;
	buf[2] = (Current_Track&0xFF00)>>8;
	buf[3] = Total_Track&0x00FF;
	buf[4] = (Total_Track&0xFF00)>>8;
	makeAndSendMessageToModule(MODULE_ID_MEDIA,MODULE_ID_OSD,buf,5);
}


