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
#define IDS_PLAYLIST_SEARCH "�����б�"
#define IDS_ARTIST_SEARCH "����"
#define IDS_ALBUM_SEARCH "ר��"
#define IDS_SONG_SEARCH "����"
*/


#define IDS_PLAYLIST_SEARCH 0xAD,0x64,0x3E,0x65,0x17,0x52,0x68,0x88
#define IDS_ARTIST_SEARCH 0x4C,0x6B,0x4B,0x62
#define IDS_ALBUM_SEARCH 0x13,0x4E,0x91,0x8F
#define IDS_SONG_SEARCH 0x4C,0x6B,0xF2,0x66

#define STRING_BUF_MAX_LEN 30

typedef struct 
{
	int iType;// 0 ���� 1 playList 2 artist 3 album 4 Genre 5 Song  6 Composer
	int iSum;//ָ����������
	int iCurPos;//��ǰλ��
	int iShowPos;//��ʾλ��
}TypeListInfo;

typedef struct //��ipod�������������һ��3��Ŀ¼  0 ��Ŀ¼�Ǹ�Ŀ¼  ������playlistĿ¼
                 // artist Ŀ¼ albumĿ¼  �� songĿ¼  1��Ŀ¼ ��������ظ������Ŀ¼ songĿ¼��ֱ�Ӿ��Ǹ���
				 //2��Ŀ¼����ӦĿ¼  songĿ¼û��2��Ŀ¼
{
	int iCurBrowsefolder;//0 Ϊ��Ŀ¼ 1 Ϊ Ŀ¼ 2 Ϊ�ļ�
	int icurBrowseType;//0 Ϊplaylist  1 Ϊartist 2 Ϊalbum 3 Ϊsong
	int icurTypeSum;//��ǰ����Ŀ¼������
	int icurTypeShowPos;//��ǰ����Ŀ¼��ʾ����λ��
	int icurTypePos;//��ǰ�����Ŀ¼
	int icurFileSum;//��ǰ����������
	int iCurFileShowPos;//��ǰ������ʾ����λ��
	int iCurFilePos;//��ǰ����������λ��
}BrowseInfo;


typedef struct {

	int userConnected;//�û��Ƿ��������ӶϿ�
	int browseSongPos;//��¼�õ��������Ƶ�λ��
	BrowseInfo browseInfo;//��¼���Ŀ¼�����Ϣ
    int enter;//�Ƿ��ǽ���ipod �״εõ�����״̬��Ϣ
	int playStatus;//��¼����״̬  00 stop   01  playing 02 paused
	int trackSum;//��¼��ǰ�б����������
	int curTrack;//��¼��ǰ���Ÿ�������λ��
	int rand;// 00 off  01  songs  02  albums
	int RPT;// 00 off   01 one song 02 all song
	TypeListInfo typeListInfo;//��¼���ڲ������͵������Ϣ
	int search;//�Ƿ���ipod ��������
	int browseEnable[5][2];
	int initPlayStatus;//��ʼ��״̬�Ƿ�Ϊ����
	int IPODConnect;//IPOD�Ƿ�����
	int airMode;//��ʾIPOD�Ƿ���AirMode
	int IPODMode;//��ʾ�Ƿ���IPOD״̬
//
	int showSubOSD;//�Ƿ���ʾ�����˵�

	int contolPlayStatus;//���ſ��� Ҫ�ﵽ��״̬�� ��Ҫ��̫�������ɿ��ƴ���

	int position;
	int cmdlength;
	unsigned char commandBuff[256];//��Ϣ������	
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
