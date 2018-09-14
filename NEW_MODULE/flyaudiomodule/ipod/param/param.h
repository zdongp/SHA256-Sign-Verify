#ifndef __PARAM_H__
#define __PARAM_H__

extern "C"{
#include "unicodestring.h"
};

typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;

#define FILE_FOLDER_NAME_MAX_LEN		64
#define FILE_FOLDER_ITEM_COUNT		5

/*
#define IDS_PLAYLIST_SEARCH "播放列表"
#define IDS_ARTIST_SEARCH "歌手"
#define IDS_ALBUM_SEARCH "专辑"
#define IDS_SONG_SEARCH "歌曲"
*/


#define IDS_PLAYLIST_SEARCH 0xAD,0x64,0x3E,0x65,0x17,0x52,0x68,0x88
#define IDS_ARTIST_SEARCH 0x4C,0x6B,0x4B,0x62
#define IDS_ALBUM_SEARCH 0x13,0x4E,0x91,0x8F
#define IDS_SONG_SEARCH 0x4C,0x6B,0xF2,0x66

#define STRING_BUF_MAX_LEN 30

typedef struct 
{
	int iType;// 0 其他 1 playList 2 artist 3 album 4 Genre 5 Song  6 Composer
	int iSum;//指定类型数量
	int iCurPos;//当前位置
	int iShowPos;//显示位置
}TypeListInfo;

typedef struct //把ipod的浏览歌曲看成一个3层目录  0 层目录是根目录  里面有playlist目录
                 // artist 目录 album目录  和 song目录  1层目录 里面是相关各个相关目录 song目录下直接就是歌曲
				 //2层目录是相应目录  song目录没有2层目录
{
	int iCurBrowsefolder;//0 为根目录 1 为 目录 2 为文件
	int icurBrowseType;//0 为playlist  1 为artist 2 为album 3 为song
	int icurTypeSum;//当前类型目录总数量
	int icurTypeShowPos;//当前类型目录显示的首位置
	int icurTypePos;//当前浏览的目录
	int icurFileSum;//当前歌曲总数量
	int iCurFileShowPos;//当前歌曲显示的首位置
	int iCurFilePos;//当前操作歌曲的位置
}BrowseInfo;


typedef struct {

	int userConnected;//用户是否主动连接断开
	int browseSongPos;//记录得到歌曲名称的位置
	BrowseInfo browseInfo;//记录浏览目录相关信息
    int enter;//是否是进入ipod 首次得到播放状态信息
	int playStatus;//记录播放状态  00 stop   01  playing 02 paused
	int trackSum;//记录当前列表歌曲总数量
	int curTrack;//记录当前播放歌曲所在位置
	int rand;// 00 off  01  songs  02  albums
	int RPT;// 00 off   01 one song 02 all song
	TypeListInfo typeListInfo;//记录现在播放类型的相关信息
	int search;//是否在ipod 搜索界面
	int browseEnable[5][2];
	int initPlayStatus;//初始化状态是否为播放
	int IPODConnect;//IPOD是否连接
	int airMode;//表示IPOD是否在AirMode
	int IPODMode;//表示是否在IPOD状态
//
	int showSubOSD;//是否显示下拉菜单

	int contolPlayStatus;//播放控制 要达到的状态。 主要是太快操作造成控制错误

	int position;
	int cmdlength;
	unsigned char commandBuff[256];//消息缓冲区	
	unsigned char curSongName[FILE_FOLDER_NAME_MAX_LEN];

	int pingIpodSuccess;

	unicode16_t mainTotalTime[64];

	int ipodNextSongTimerING;
	//int haveIpod;
}ipod_local_param_t;

typedef struct{
	
}ipod_global_param_t;


extern ipod_local_param_t *pLocalParam;
extern ipod_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);


uni16_size_t uni16_strlen(const unicode16_t *uni16);
unicode16_t ansi_to_unicode16(const unsigned char ansi);
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);

#endif
