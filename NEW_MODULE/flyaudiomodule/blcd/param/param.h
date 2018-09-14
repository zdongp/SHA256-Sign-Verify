#ifndef __PARAM_H__
#define __PARAM_H__

#define FILE_FOLDER_NAME_MAX_LEN		256
#define FILE_FOLDER_ITEM_MAX_COUNT		5

#define TRACKLIST_ITEM_COUNT		20
#define FILE_FOLDER_ITEM_COUNT		FILE_FOLDER_ITEM_MAX_COUNT

typedef struct 
{
	char CDCDiskType[6] ;
	char ActiveDisk;
}CDCtype;

typedef struct {

}file_folder_name_t;

typedef struct {

}file_folder_item_info_t;

typedef struct {
	int PlayState;	//播放状态
	u8 audioMode;	//刘亮  声道模式 
	u8 setMode;//设置后座娱乐的模式 
	u8 getMode;//返回后座娱乐的模式
	
	CDCtype CDCType;//CDC类型
}dvd_local_param_t;

typedef struct{
	u8 savemode;
}dvd_global_param_t;


extern dvd_local_param_t *pLocalParam;
extern dvd_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
