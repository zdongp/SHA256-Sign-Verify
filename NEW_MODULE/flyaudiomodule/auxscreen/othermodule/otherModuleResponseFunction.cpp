#include <stdio.h>
#include <stdlib.h>
#include "halRequestFunction.h"
#include "param.h"
#include "global.h"
#include "moduleParamRequest.h"
#include "otherModuleResponseFunction.h"

//��ǰ���ŵ�ģ��
void moduleToAuxScreen_PlayingModule(u8 nModule){
	static int i = 1;
	LOGI("+++i=%d, Play sound channel:%d, presoundchananel:%d",  i++, nModule,pLocalParam->nCurPlayingModule);
    u8 cPlayingMode = 0;
	switch(nModule){
	case CHANNEL_DVD_CTRL://   0x00// (���ƽ���)
	case CHANNEL_DVD_VIDEO://  0x01//����Ƶ���棩
		cPlayingMode = 0x01;
		break;
	case CHANNEL_CDC_CTRL://   0x02//�����ƽ��棩
	case CHANNEL_CDC_VIDEO://  0x03//����Ƶ���棩
		break;
	case CHANNEL_RADIO://      0x04//�����ƽ��棩
		cPlayingMode = 0x02;
		break;
	case CHANNEL_AUX_CTRL://   0x05
	case CHANNEL_AUX_VIDEO://  0x06
		cPlayingMode = 0x04;
		break;
	case CHANNEL_IPOD_CTRL://  0x07
	case CHANNEL_IPOD_VIDEO:// 0x08
		cPlayingMode = 0x03;
		break;
	case CHANNEL_TV_CTRL://    0x09
	case CHANNEL_TV_VIDEO://   0x0A
		cPlayingMode = 0x05;
		break;
	case CHANNEL_MP3://        0x0B
		cPlayingMode = 0x06;
		//moduleToAuxScreen_SendAllMediaInfoToHal();
		break;
	case CHANNEL_SRADIO://     0x0C
		cPlayingMode = 0x07;
		break;
	case CHANNEL_BT:
		cPlayingMode = 0x08;
		//moduleToAuxScreen_SendAllA2DPInfoToHal();
		break;
	case CHANNEL_THREECHANNEL://0x0E
		cPlayingMode = 0x06;
		break;
	}

  pLocalParam->nCurPlayingModule = cPlayingMode;
  auxScreenToHal_PlayingModule(cPlayingMode);
}


int getLanguageFromGps(void)
{
	int nRet = -1;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_GPS, 0, (u8*)&nRet, &len);

	/*

	LOGD("[%s] nRet = [0x%x]", __FUNCTION__, nRet);

	switch(nRet)
		{
		case 0x00:
			LOGD("[%s] nRet = [%s]", __FUNCTION__,  "chinese");
			break;
		default:
			LOGD("[%s] nRet = [%s]", __FUNCTION__,  "unknow");
			break;
		}
	*/

	return nRet;
}

//��ǰ����ý���ʱ�����Ϣ
void moduleToAuxScreen_PlayingInfo(u8* buf,int len){
	int nLanguage = -1;
	nLanguage = getLanguageFromGps();
	LOGD("buf[0]:%d,buf[1]:%d,nLanguage:%d",buf[0],buf[1],nLanguage);
	if (nLanguage == 0)//chinese
	{
			//-->¹ýÂË
		int nCanSendChinese = 1;
		//int nLen = 0;
		switch(buf[0])
		{
		case 0x54://žèÇúÃû
			nCanSendChinese = pLocalParam->nAuxScreenCanSendChinese;
			break;
		}

		LOGD("nCanSendChinese:%d",nCanSendChinese);
		if (nCanSendChinese == 0)
		{
			u8 cmd[300];
          memset(cmd,0,300);
          int nLen=1;
			cmd[0]=0x54;
			memcpy(&cmd[1],"",1);
          nLen=2;
			auxScreenToHal_PlayingInfo(cmd,nLen);
			return;
		}
		//<--
	}

	/*
	switch(buf[0])
		{
		case 0x54:
			LOGD("[%s] nRet = [%s]", __FUNCTION__,  "media song have send!");
			break;
		default:
			LOGD("[%s] nRet = [%s]", __FUNCTION__,  "other have send!");
			break;
		}
	*/
	
    if(pLocalParam->nIsAuxscreenExited)
	    auxScreenToHal_PlayingInfo(buf,len);
}




void moduleToAuxScreen_FromDVD_message(unsigned char *param,unsigned char len){
	unsigned char cmd = param[0];
	switch(cmd){
		case 0x11:
			moduleToAuxScreen_PlayingModule(param[1]);
			break;
		case 0x20:
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x26:
		{
			switch(param[0])
			{
				case 0x20:
					memset(pLocalParam->strCurAuxscreenShowInfo.Title,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Title));
					pLocalParam->strCurAuxscreenShowInfo.Titlelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.Title,param ,len);
				break;
				case 0x21:
					memset(pLocalParam->strCurAuxscreenShowInfo.PlayTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayTime));
					pLocalParam->strCurAuxscreenShowInfo.PlayTimelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.PlayTime,param ,len);
				break;
				case 0x22:
					param[0]=0x25;
				break;
				case 0x23:
					memset(pLocalParam->strCurAuxscreenShowInfo.PlayState,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayState));
					pLocalParam->strCurAuxscreenShowInfo.PlayStatelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.PlayState,param ,len);
				break;
				case 0x26:
					memset(pLocalParam->strCurAuxscreenShowInfo.TotalTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.TotalTime));
					pLocalParam->strCurAuxscreenShowInfo.TotalTimelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.TotalTime,param ,len);
				break;
			}

			u16 curSound = 0;
			u8 curSoundLen = 2;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, &curSoundLen);
			if(curSound == CHANNEL_DVD_CTRL || curSound == CHANNEL_DVD_VIDEO)
			{
				moduleToAuxScreen_PlayingInfo(param,len);
			}
		}
		break;
		default:
			u16 curSound = 0;
			u8 curSoundLen = 2;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, &curSoundLen);
			if(curSound == CHANNEL_DVD_CTRL || curSound == CHANNEL_DVD_VIDEO)
			{
				moduleToAuxScreen_PlayingInfo(param,len);
			}
		break;
	}
}
void moduleToAuxScreen_FromBT_message(unsigned char *param,unsigned char len){
	unsigned char cmd = param[0];
	int i = 0;
	for(i = 0;  i < len; i++)
	{
		LOGD("moduleToAuxScreen_FromBT_message  param[%d]=%x",i,param[i]);
	}
	
	switch(cmd){
		case 0x11:
			moduleToAuxScreen_PlayingModule(param[1]);
		break;
		case 0x70:
		case 0x71:
		case 0x72:
		case 0x73:
		case 0x74:
		case 0x75:
			moduleToAuxScreen_PlayingInfo(param,len);
		break;
		case 0x7A://A2DP Infors
		{
			switch(param[1])
			{
				case 0x00://Cur Track Number and Total Track Count
				{
					memcpy(&pLocalParam->a2dpData.nCurAndTotalTrack,&param[2],4);
					memset(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack));
					pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTracklen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,param ,len);
				}
				break;
				case 0x01://Cur Track Play Time
				{
					memcpy(&pLocalParam->a2dpData.sPlayTime,&param[2],4);
					memset(pLocalParam->strCurAuxscreenShowInfo.PlayTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayTime));
					pLocalParam->strCurAuxscreenShowInfo.PlayTimelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.PlayTime,param ,len);
				}
				break;
				case 0x02://Play Status
				{
					pLocalParam->a2dpData.cPlayState=param[2];
					memset(pLocalParam->strCurAuxscreenShowInfo.PlayState,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayState));
					pLocalParam->strCurAuxscreenShowInfo.PlayStatelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.PlayState,param ,len);
				}
				break;
				case 0x03://Cur Track Total Time
				{
					memcpy(&pLocalParam->a2dpData.sTotalTime,&param[2],4);
					memset(pLocalParam->strCurAuxscreenShowInfo.TotalTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.TotalTime));
					pLocalParam->strCurAuxscreenShowInfo.TotalTimelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.TotalTime,param ,len);
				}
				break;
				case 0x04://Song Title
				{
					memset(pLocalParam->a2dpData.strSongName, 0, sizeof(pLocalParam->a2dpData.strSongName));
					pLocalParam->a2dpData.nSongNameLen = len - 2;
					memcpy(pLocalParam->a2dpData.strSongName, param + 2, len - 2);
					memset(pLocalParam->strCurAuxscreenShowInfo.Title,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Title));
					pLocalParam->strCurAuxscreenShowInfo.Titlelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.Title,param ,len);
				}
				break;
				case 0x05://Song Artist
				{
					memset(pLocalParam->a2dpData.strSongArtist, 0, sizeof(pLocalParam->a2dpData.strSongArtist));
					pLocalParam->a2dpData.nSongArtistLen = len - 2;
					memcpy(pLocalParam->a2dpData.strSongArtist, param + 2, len - 2);
					memset(pLocalParam->strCurAuxscreenShowInfo.Artist,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Artist));
					pLocalParam->strCurAuxscreenShowInfo.Artistlen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.Artist,param ,len);
				}
				break;
				case 0x06://Song Album
				{
					memset(pLocalParam->a2dpData.strSongAlbum, 0, sizeof(pLocalParam->a2dpData.strSongAlbum));
					pLocalParam->a2dpData.nSongAlbumLen = len - 2;
					memcpy(pLocalParam->a2dpData.strSongAlbum, param + 2, len - 2);
					memset(pLocalParam->strCurAuxscreenShowInfo.Album,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Album));
					pLocalParam->strCurAuxscreenShowInfo.Albumlen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.Album,param ,len);
				}
				break;
				case 0x07://Song Folder Name
				{
				}
				break;
				case 0x08://A2DP Device Name
				{
				}
				break;
			}
			
			u16 curSound = 0;
			u8 curSoundLen = 2;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, &curSoundLen);
			if(curSound == CHANNEL_BT)
			{
				moduleToAuxScreen_PlayingInfo(param,len);
			}
		}
		break;
		default: 
			u16 curSound = 0;
			u8 curSoundLen = 2;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8 *)&curSound, &curSoundLen);
			if(curSound == CHANNEL_BT)
			{
				moduleToAuxScreen_PlayingInfo(param,len);
			}
		break;
	}

}
void moduleToAuxScreen_FromRadio_message(unsigned char *param,unsigned char len){
	unsigned char cmd = param[0];

	switch(cmd){
		case 0x11:
			moduleToAuxScreen_PlayingModule(param[1]);
			break;
		case 0x30:
		case 0x31:
		case 0x32:
		{
			switch(param[0])
			{
				case 0x30:
					memset(pLocalParam->strCurAuxscreenShowInfo.RadioChannel,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.RadioChannel));
					pLocalParam->strCurAuxscreenShowInfo.RadioChannellen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.RadioChannel,param ,len);
					break;
				case 0x31:
					memset(pLocalParam->strCurAuxscreenShowInfo.RadioFre,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.RadioFre));
					pLocalParam->strCurAuxscreenShowInfo.RadioFrelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.RadioFre,param ,len);
					break;
				case 0x32:
					memset(pLocalParam->strCurAuxscreenShowInfo.RadioRecord,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.RadioRecord));
					pLocalParam->strCurAuxscreenShowInfo.RadioRecordlen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.RadioRecord,param ,len);
					break;
			}
			
			u16 CurSoundChannel = 0;
			u8 CurSoundChannelLen = 0;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8*)&CurSoundChannel, &CurSoundChannelLen);
			if(CurSoundChannel == CHANNEL_RADIO)
			{
				moduleToAuxScreen_PlayingInfo(param,len);
			}
		}
		break;
		case 0x37:
			moduleToAuxScreen_PlayingInfo(param,len);
		break;
		default:
			u16 CurSoundChannel = 0;
			u8 CurSoundChannelLen = 0;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8*)&CurSoundChannel, &CurSoundChannelLen);
			if(CurSoundChannel == CHANNEL_RADIO)
			{
				moduleToAuxScreen_PlayingInfo(param,len);
			}
		break;
	}

}
void moduleToAuxScreen_FromAudioVideo_message(unsigned char *param,unsigned char len){
	unsigned char cmd = param[0];
	LOGW("++++From AV param:%x %x %x %x %x",param[0], param[1], param[2], param[3],param[4]);
	switch(cmd){
		case 0x00:
			moduleToAuxScreen_PlayingModule(param[1]);
			break;
		case 0x80:
			auxScreenToHal_PlayVolume(param[1]);
			break;
		default:break;
	}

}

void moduleToAuxScreen_FromSystem_Message(unsigned char *param, unsigned char len){
	int i = 0;
	switch(param[0]){
		case 0xA0:
			auxScreenToHal_TimeInfo(param, len);
			break;
		default:break;
	}
}
void moduleToAuxScreen_SendAllMediaInfoToHal(void)
{
	u8 buff1[5]={0x50,0x00,0x00,0x00,0x00};
	memcpy(&buff1[1],&pLocalParam->mediaData.nCurAndTotalTrack,4);
	moduleToAuxScreen_PlayingInfo(buff1,5);
	
	u8 buff2[5]={0x51,0x00,0x00,0x00,0x00};
	memcpy(&buff2[1],&pLocalParam->mediaData.sPlayTime,4);
	moduleToAuxScreen_PlayingInfo(buff2,5);
	
	u8 buff3[2]={0x52,0x00};
	buff3[1]=pLocalParam->mediaData.cPlayState;
	moduleToAuxScreen_PlayingInfo(buff3,2);
	
	u8 buff4[5]={0x53,0x00,0x00,0x00,0x00};
	memcpy(&buff4[1],&pLocalParam->mediaData.sTotalTime,4);
	moduleToAuxScreen_PlayingInfo(buff4,5);


	u8 szBuf[256 + 1] = {0};
	szBuf[0] = 0x54;
	memcpy(szBuf + 1, pLocalParam->mediaData.strSongName, pLocalParam->mediaData.nSongNameLen);
	moduleToAuxScreen_PlayingInfo(szBuf,  pLocalParam->mediaData.nSongNameLen + 1);

	u8 szBuf1[256 + 1] = {0};
	szBuf1[0] = 0x55;
	memcpy(szBuf1 + 1, pLocalParam->mediaData.strSongArtist, pLocalParam->mediaData.nSongArtistLen);
	moduleToAuxScreen_PlayingInfo(szBuf1,  pLocalParam->mediaData.nSongArtistLen + 1);

	u8 szBuf2[256 + 1] = {0};
	szBuf2[0] = 0x56;
	memcpy(szBuf2 + 1, pLocalParam->mediaData.strSongAlbum, pLocalParam->mediaData.nSongAlbumLen);
	moduleToAuxScreen_PlayingInfo(szBuf2,  pLocalParam->mediaData.nSongAlbumLen + 1);
}

void moduleToAuxScreen_SendAllA2DPInfoToHal(void)
{	
	u8 buff2[6]={0x7A,0x01,0x00,0x00,0x00,0X00};
	memcpy(&buff2[2],&pLocalParam->a2dpData.sPlayTime,4);
	moduleToAuxScreen_PlayingInfo(buff2,6);
	
	u8 buff3[3]={0x7A,0x02,0X00};
	buff3[2]=pLocalParam->a2dpData.cPlayState;
	moduleToAuxScreen_PlayingInfo(buff3,3);
	
	u8 buff4[6]={0x7A,0X03,0x00,0x00,0x00,0x00};
	memcpy(&buff4[2],&pLocalParam->a2dpData.sTotalTime,4);
	moduleToAuxScreen_PlayingInfo(buff4,6);

	u8 szBuf[256 + 1] = {0};
	szBuf[0] = 0x7A;
	szBuf[1] = 0x04;
	memcpy(szBuf + 2, pLocalParam->a2dpData.strSongName, pLocalParam->a2dpData.nSongNameLen);
	moduleToAuxScreen_PlayingInfo(szBuf,  pLocalParam->a2dpData.nSongNameLen + 2);

	u8 szBuf1[256 + 1] = {0};
	szBuf1[0] = 0x7A;
	szBuf1[1] = 0x05;
	memcpy(szBuf1 + 2, pLocalParam->a2dpData.strSongArtist, pLocalParam->a2dpData.nSongArtistLen);
	moduleToAuxScreen_PlayingInfo(szBuf1,  pLocalParam->a2dpData.nSongArtistLen + 2);

	u8 szBuf2[256 + 1] = {0};
	szBuf2[0] = 0x7A;
	szBuf2[1] = 0x06;
	memcpy(szBuf2 + 2, pLocalParam->a2dpData.strSongAlbum, pLocalParam->a2dpData.nSongAlbumLen);
	moduleToAuxScreen_PlayingInfo(szBuf2,  pLocalParam->a2dpData.nSongAlbumLen + 2);
}

void moduleToAuxScreen_FromMedia_Message(unsigned  char *param, unsigned char len)
{
	switch(param[0]){
		case 0x11:
			moduleToAuxScreen_PlayingModule(param[1]);
			break;
		case 0x20:
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x24:
		case 0x25:
		case 0x26:
		{
			switch(param[0])
			{
				case 0x20:
					param[0]=0x50;
					memcpy(&pLocalParam->mediaData.nCurAndTotalTrack,&param[1],4);
					memset(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack));
					pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTracklen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,param ,len);
				break;
				case 0x21:
					param[0]=0x51;
					memcpy(&pLocalParam->mediaData.sPlayTime,&param[1],4);
					memset(pLocalParam->strCurAuxscreenShowInfo.PlayTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayTime));
					pLocalParam->strCurAuxscreenShowInfo.PlayTimelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.PlayTime,param ,len);
				break;
				case 0x22:
					param[0]=0x53;
					memcpy(&pLocalParam->mediaData.sTotalTime,&param[1],4);
					memset(pLocalParam->strCurAuxscreenShowInfo.TotalTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.TotalTime));
					pLocalParam->strCurAuxscreenShowInfo.TotalTimelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.TotalTime,param ,len);
				break;
				case 0x23:
					param[0]=0x52;
					pLocalParam->mediaData.cPlayState=param[1];
					memset(pLocalParam->strCurAuxscreenShowInfo.PlayState,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayState));
					pLocalParam->strCurAuxscreenShowInfo.PlayStatelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.PlayState,param ,len);
				break;
				case 0x24:
					param[0] = 0x54;
					memset(pLocalParam->mediaData.strSongName, 0, sizeof(pLocalParam->mediaData.strSongName));
					pLocalParam->mediaData.nSongNameLen = len - 1;
					memcpy(pLocalParam->mediaData.strSongName, param + 1, len - 1);
					memset(pLocalParam->strCurAuxscreenShowInfo.Title,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Title));
					pLocalParam->strCurAuxscreenShowInfo.Titlelen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.Title,param ,len);
				break;
				case 0x25:
					param[0] = 0x55;
					memset(pLocalParam->mediaData.strSongArtist, 0, sizeof(pLocalParam->mediaData.strSongArtist));
					pLocalParam->mediaData.nSongArtistLen = len - 1;
					memcpy(pLocalParam->mediaData.strSongArtist, param + 1, len - 1);
					memset(pLocalParam->strCurAuxscreenShowInfo.Artist,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Artist));
					pLocalParam->strCurAuxscreenShowInfo.Artistlen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.Artist,param ,len);
				break;
				case 0x26:
					param[0] = 0x56;
					memset(pLocalParam->mediaData.strSongAlbum, 0, sizeof(pLocalParam->mediaData.strSongAlbum));
					pLocalParam->mediaData.nSongAlbumLen = len - 1;
					memcpy(pLocalParam->mediaData.strSongAlbum, param + 1, len - 1);
					memset(pLocalParam->strCurAuxscreenShowInfo.Album,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Album));
					pLocalParam->strCurAuxscreenShowInfo.Albumlen = len;
					memcpy(pLocalParam->strCurAuxscreenShowInfo.Album,param ,len);
				break;
			}
			
			u16 CurSoundChannel = 0;
			u8 CurSoundChannelLen = 0;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8*)&CurSoundChannel, &CurSoundChannelLen);
			if(CurSoundChannel == CHANNEL_MP3|| CurSoundChannel == CHANNEL_THREECHANNEL)
			{
				moduleToAuxScreen_PlayingInfo(param,len);
			}
		}
		break;
		default:
			u16 CurSoundChannel = 0;
			u8 CurSoundChannelLen = 0;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8*)&CurSoundChannel, &CurSoundChannelLen);
			if(CurSoundChannel == CHANNEL_MP3 || CurSoundChannel == CHANNEL_THREECHANNEL)
			{
				moduleToAuxScreen_PlayingInfo(param,len);
			}
		break;
	}
}

void moduleToAuxScreen_FromGPS_Message(u8 *param,u8 len)
{
	switch(param[0]){
		case 0x00:
			auxScreenToHal_GPSInfo(param+1,len-1);
			break;
		case 0x01:
			auxScreenToHal_GaodeMap_GPSInfo(param+1,len-1);
			break;
		default:break;
	}
}

void moduleToAuxScreen_FromAUXscreen_message(u8 *param,u8 len)
{
    u8 cmd = param[0];
    switch(cmd){
        case 0x01:
          break;
        case 0x03:
          break;
        case 0x11:
          moduleToAuxScreen_PlayingModule(param[1]);
          break;
        default:
          moduleToAuxScreen_PlayingInfo(param+1,len-1);
          break;
        }
}

void moduleToAuxScreen_FromExtcar_Message(u8 *param,u8 len)
{
    u8 cmd = param[0];
    switch(cmd){
        case 0x00:
		 {
			 pLocalParam->nAuxScreenCanSendChinese = param[1];
            if(pLocalParam->nIsAuxscreenExited)
            {
                u8 cmd[300];
                memset(cmd,0,300);
                
                int nLen=1;
				u16 CurSoundChannel = 0;
				u8 CurSoundChannelLen = 0;
				getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8*)&CurSoundChannel, &CurSoundChannelLen);
				LOGD("[%s] CurSoundChannel=%x param[1]:%d",__FUNCTION__,CurSoundChannel,param[1]);
              if(param[1]==0)
              {
                	if(CurSoundChannel == CHANNEL_MP3)
					{
        	        	cmd[0]=0x54;
						memcpy(&cmd[1],"",1);
                    	nLen=2;
						auxScreenToHal_PlayingInfo(cmd,nLen);
					}
              }
        	   else if(param[1]==1)
        	   {
					if(CurSoundChannel == CHANNEL_MP3)
					{
        	        	moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayState,pLocalParam->strCurAuxscreenShowInfo.PlayStatelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.TotalTime,pLocalParam->strCurAuxscreenShowInfo.TotalTimelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayTime,pLocalParam->strCurAuxscreenShowInfo.PlayTimelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Title,pLocalParam->strCurAuxscreenShowInfo.Titlelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Artist,pLocalParam->strCurAuxscreenShowInfo.Artistlen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Album,pLocalParam->strCurAuxscreenShowInfo.Albumlen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTracklen);
					}
					else if(CurSoundChannel == CHANNEL_RADIO)
					{
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.RadioChannel,pLocalParam->strCurAuxscreenShowInfo.RadioChannellen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.RadioFre,pLocalParam->strCurAuxscreenShowInfo.RadioFrelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.RadioRecord,pLocalParam->strCurAuxscreenShowInfo.RadioRecordlen);
					}
					else if(CurSoundChannel == CHANNEL_DVD_CTRL || CurSoundChannel == CHANNEL_DVR_VIDEO)
					{
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayState,pLocalParam->strCurAuxscreenShowInfo.PlayStatelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.TotalTime,pLocalParam->strCurAuxscreenShowInfo.TotalTimelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayTime,pLocalParam->strCurAuxscreenShowInfo.PlayTimelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Title,pLocalParam->strCurAuxscreenShowInfo.Titlelen);
					}
					else if(CurSoundChannel == CHANNEL_BT)
					{
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayState,pLocalParam->strCurAuxscreenShowInfo.PlayStatelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.TotalTime,pLocalParam->strCurAuxscreenShowInfo.TotalTimelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayTime,pLocalParam->strCurAuxscreenShowInfo.PlayTimelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Title,pLocalParam->strCurAuxscreenShowInfo.Titlelen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Artist,pLocalParam->strCurAuxscreenShowInfo.Artistlen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Album,pLocalParam->strCurAuxscreenShowInfo.Albumlen);
						moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTracklen);
					}
					else{
					}
        	   }
    	    }
        }
        break;
    }
}

void moduleToAuxScreen_Show_Message()
{
	u16 CurSoundChannel = 0;
	u8 CurSoundChannelLen = 0;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8*)&CurSoundChannel, &CurSoundChannelLen);
	if(CurSoundChannel == CHANNEL_MP3)
	{
    	moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayState,pLocalParam->strCurAuxscreenShowInfo.PlayStatelen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.TotalTime,pLocalParam->strCurAuxscreenShowInfo.TotalTimelen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayTime,pLocalParam->strCurAuxscreenShowInfo.PlayTimelen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Title,pLocalParam->strCurAuxscreenShowInfo.Titlelen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Artist,pLocalParam->strCurAuxscreenShowInfo.Artistlen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Album,pLocalParam->strCurAuxscreenShowInfo.Albumlen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTracklen);
	}
	else if(CurSoundChannel == CHANNEL_RADIO)
	{
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.RadioChannel,pLocalParam->strCurAuxscreenShowInfo.RadioChannellen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.RadioFre,pLocalParam->strCurAuxscreenShowInfo.RadioFrelen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.RadioRecord,pLocalParam->strCurAuxscreenShowInfo.RadioRecordlen);
	}
	else if(CurSoundChannel == CHANNEL_DVD_CTRL || CurSoundChannel == CHANNEL_DVR_VIDEO)
	{
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayState,pLocalParam->strCurAuxscreenShowInfo.PlayStatelen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.TotalTime,pLocalParam->strCurAuxscreenShowInfo.TotalTimelen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.PlayTime,pLocalParam->strCurAuxscreenShowInfo.PlayTimelen);
		moduleToAuxScreen_PlayingInfo((u8*)pLocalParam->strCurAuxscreenShowInfo.Title,pLocalParam->strCurAuxscreenShowInfo.Titlelen);
	}
	else
	{

	}
}

