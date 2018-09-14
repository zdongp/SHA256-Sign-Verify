#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "halRequestFunction.h"
#include "moduleParamResponse.h"
#include "param.h"
#include "otherModuleResponseFunction.h"
void moduleParameterInit(void){//参数初始化
}
void setDefaultParam(void)
{
	pLocalParam->nCurPlayingModule = 0x00;
    pLocalParam->nIsAuxscreenExited = 0x01;

	//媒体数据初始化
	pLocalParam->mediaData.cPlayState=0;
	pLocalParam->mediaData.sTotalTime=0;
	pLocalParam->mediaData.sPlayTime=0;
	memset(pLocalParam->mediaData.strSongName,0,256);
	pLocalParam->mediaData.nSongNameLen = 0;
	memset(pLocalParam->mediaData.strSongArtist,0,256);
	pLocalParam->mediaData.nSongArtistLen = 0;
	memset(pLocalParam->mediaData.strSongAlbum,0,256);
	pLocalParam->mediaData.nSongAlbumLen = 0;
	pLocalParam->mediaData.nCurAndTotalTrack=0;

	pLocalParam->a2dpData.cPlayState=0;
	pLocalParam->a2dpData.sTotalTime=0;
	pLocalParam->a2dpData.sPlayTime=0;
	memset(pLocalParam->a2dpData.strSongName,0,256);
	pLocalParam->a2dpData.nSongNameLen = 0;
	memset(pLocalParam->a2dpData.strSongArtist,0,256);
	pLocalParam->a2dpData.nSongArtistLen = 0;
	memset(pLocalParam->a2dpData.strSongAlbum,0,256);
	pLocalParam->a2dpData.nSongAlbumLen = 0;
	pLocalParam->a2dpData.nCurAndTotalTrack=0;
	
	pLocalParam->strCurAuxscreenShowInfo.PlayStatelen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.PlayState,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayState));
	
	pLocalParam->strCurAuxscreenShowInfo.TotalTimelen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.TotalTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.TotalTime));
	
	pLocalParam->strCurAuxscreenShowInfo.PlayTimelen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.PlayTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayTime));
	
	pLocalParam->strCurAuxscreenShowInfo.Titlelen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.Title,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Title));
	
	pLocalParam->strCurAuxscreenShowInfo.Artistlen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.Artist,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Artist));
	
	pLocalParam->strCurAuxscreenShowInfo.Albumlen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.Album,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Album));
	
	pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTracklen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack));
	
	pLocalParam->strCurAuxscreenShowInfo.RadioFrelen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.RadioFre,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.RadioFre));
	
	pLocalParam->strCurAuxscreenShowInfo.RadioChannellen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.RadioChannel,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.RadioChannel));
	
	pLocalParam->strCurAuxscreenShowInfo.RadioRecordlen = 0;
	memset(pLocalParam->strCurAuxscreenShowInfo.PlayState,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayState));
	memset(pLocalParam->strCurAuxscreenShowInfo.TotalTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.TotalTime));
	memset(pLocalParam->strCurAuxscreenShowInfo.PlayTime,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.PlayTime));
	memset(pLocalParam->strCurAuxscreenShowInfo.Title,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.Title));
	memset(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.CurAndTotalTrack));
	memset(pLocalParam->strCurAuxscreenShowInfo.RadioFre,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.RadioFre));
	memset(pLocalParam->strCurAuxscreenShowInfo.RadioChannel,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.RadioChannel));
	memset(pLocalParam->strCurAuxscreenShowInfo.RadioRecord,0,sizeof(pLocalParam->strCurAuxscreenShowInfo.RadioRecord));
	
	
	
}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& auxscreen moduleParameterReInit");
	moduleParameterInit();
}
int module_extendInterface(char *buffer, int len){//测试用
	char extenCmd = buffer[0];
	char extenParam = buffer[1];
	LOGD("************************auxscreen module_extendInterface:%d,%d",extenCmd,extenParam);
	switch(extenCmd)
	{
	 case 0x2C: //ACC Off Or Reset Or Default 44
		{
			if(extenParam == 0x00) //Acc Off
			{
			}
			else if(extenParam == 0x01)//Reset
			{ 
				moduleToAuxScreen_Show_Message();
			}
			else if(extenParam == 0x02)//Reset default
			{
			}
		 }
		 break;
	 case 0x2D: //ACC On 45
	 	{
			moduleToAuxScreen_Show_Message();
	 	}
		 break;
	 case 0xFD:
		{
			auxScreenToHal_Init();//初始化 
		}
		break;
	 default:break;
	 }
	return 0;

}

void moduleParameterDeInit(void){

}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:
			break;
	}
}

