#ifndef __PARAM_H__
#define __PARAM_H__

#define FILE_FOLDER_NAME_MAX_LEN		256
#define FILE_FOLDER_ITEM_MAX_COUNT		5

#define TRACKLIST_ITEM_COUNT		20
#define FILE_FOLDER_ITEM_COUNT		5
//moupeng 2015/7/30
#include "CNotifyAndResponseFlyJniSdk.h"

typedef struct {
	int len;
	u8 name[FILE_FOLDER_NAME_MAX_LEN];
}file_folder_name_t;

typedef struct {
	u16 localIndex;
	u16 globalIndex;
	int isFile;
	int isBlank;
	file_folder_name_t name;
}file_folder_item_info_t;

typedef struct {
	u16 totalTitle;
	u16 curTitle;
	u16 totalTrack;
	u16 curTrack;

	//////11-11//////
	int trackList_Enable;
	int folder_Enable;
	//////11-11/////
	
	u8 	escapeTimeHour;
	u8 	escapeTimeMin;
	u8 	escapeTimeSec;

	u8 	discType;
	u8 	fileType;

	u8 	playStatus;
	u8 	playSpeed; 

	u8 	imageRatio; 

	u8 	curPlayDevice;
	u8 	deviceType;
	u8 	deviceStatus;

	u8 	isRoot;
	u16	fileNumOfCurFolder;
	u16	folderNumOfCurFolder;	

	file_folder_name_t curPlayFile;
	file_folder_name_t curPlayFolder;
	file_folder_name_t curBrowseFolder;

	file_folder_item_info_t fileFolderItem[FILE_FOLDER_ITEM_COUNT];

	int brakeEnable;

	//////////////////////7///////////////////////////
	int GetOPENMsg;
	int GetCLOSEMsg;//weather get closing msg
	int browsePos;//UI��ǰ�����λ��
	u16 FileBrowsePos;	//�ļ����λ��
	u8 PlayBack;			//ѭ��ģʽ
	u8 ImageSize;			//ͼ�����

	int bUSBtoDVD;
	int bSoundRun;
	int bPull_Sek_OSD;
	//dyb
	int bInDVD;	 //�Ƿ���DVDģʽ��
	int bDVDMenuEnable;
	int nPreDisState;
	int bLoadAndPlayVedio;
	int bVideo;
	int StoreTheAudioMode;
	int IsShowFullScreen;
	int SaveVideoMode;//�������Ƶ ����
	
	//
	int TypeNum;
	int IsVideoItem;
	int IsShowOSD;
	int lastBrowsePos;//���һ�������λ
	int IsPlayForBLCD;  //�ں������ֵ�ʱ�� �Ƿ�ɿ�DVD  8-15

	int curPlayFileIndex;  //��ǰ���Ÿ�����ȫ������
	u16	curFileFolderIndex;
	/////////////////////////7//////////////////////////

	int flag;	//�������϶� �Ƿ�ִ�в�ѯ�ı�־

	int displayTraceInfo;

	int saveCtemp;
	/*
	u16	curFileFolderIndex;
	int	browsePos;
	int lastBrowsePos;  //���һ�����λ��
	int curPlayFileIndex;  //��ǰ���Ÿ�����ȫ������
	int flag;	//�������϶� �Ƿ�ִ�в�ѯ�ı�־
	int SaveVideoMode; //������Ƶ����

	
	int showRowIndex;	//��ס�ڼ��еĸ���ȫ������ʹ�뵱ǰ���ŵĸ�����ȫ�������뵱
	int StoreTheAudioMode;		//�����Ƿ�ʹ��Ƶ���Ƿ���Ƶ
	/////////ll/////////////

	///////////////16/////////////////
	int bInDVD;   //�Ƿ���DVDģʽ��
//	int bTrackListEnable;
//	int bFolderEnable;
	int bDVDMenuEnable;
	int nPreDisState;
	int bLoadAndPlayVedio;
	int bVideo;
	int bIsShowFullScreen;

	//���Ʋ���
	int bUSBtoDVD;
	int bSoundRun;
	int bBreak_Enable;  //�Ƿ�ɲ��
	int bPull_Sek_OSD;
	int SaveVideoMode;

	int IsPlayForBLCD;
	*/
	u8 u_DisplayOsdDevType;
	u8 u_DisplayOsdPlayStatus;
	//bool isKeyEvent; 
	bool isSliderEvent;

	u8 shuffle_stat;
	u8 rpt_stat;
	u8 scan_Stat;
	u8 	uTemdiscOpenStatus;
}dvd_local_param_t;

typedef struct{
	
	int cTemp;
}dvd_global_param_t;


extern dvd_local_param_t *pLocalParam;
extern dvd_global_param_t *pGlobalParam;
extern CNotifyAndResponseFlyJniSdk g_clsDvd;

void readParameter(void);
void saveParameter(void);



typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
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
