#ifndef __PARAM_H__
#define __PARAM_H__
#include "global.h"


struct MediaData
{
	u8  cPlayState;
	u32 sTotalTime;
	u32 sPlayTime;
	u8 strSongName[256];
	int nSongNameLen;
	u8 strSongArtist[256];
	int nSongArtistLen;
	u8 strSongAlbum[256];
	int nSongAlbumLen;
	u32 nCurAndTotalTrack;
};

struct A2dpData
{
	u8  cPlayState;
	u32 sTotalTime;
	u32 sPlayTime;
	u8 strSongName[256];
	int nSongNameLen;
	u8 strSongArtist[256];
	int nSongArtistLen;
	u8 strSongAlbum[256];
	int nSongAlbumLen;
	u32 nCurAndTotalTrack;
};

struct AuxscreenShowData
{
	char PlayState[256];
	u8 PlayStatelen;
	char TotalTime[256];
	u8 TotalTimelen;
	char PlayTime[256];
	u8 PlayTimelen;
	char Title[256];
	u8 Titlelen;
	char Artist[256];
	u8 Artistlen;
	char Album[256];
	u8 Albumlen;
	char CurAndTotalTrack[256];
	u8 CurAndTotalTracklen;
	char RadioFre[256];
	u8 RadioFrelen;
	char RadioChannel[256];
	u8 RadioChannellen;
	char RadioRecord[256];
	u8 RadioRecordlen;
};
typedef struct {
 	u8 nCurPlayingModule;//当前播放的模块
	u8 nIsAuxscreenExited;//是否存在小屏模块，不存在可以认为没有
	MediaData mediaData;
	A2dpData a2dpData;
	AuxscreenShowData strCurAuxscreenShowInfo;
	int nAuxScreenCanSendChinese;
}auxscreen_local_param_t;

typedef struct{
	
}auxscreen_global_param_t;


extern auxscreen_local_param_t *pLocalParam;
extern auxscreen_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
