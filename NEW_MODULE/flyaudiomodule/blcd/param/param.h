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
	int PlayState;	//����״̬
	u8 audioMode;	//����  ����ģʽ 
	u8 setMode;//���ú������ֵ�ģʽ 
	u8 getMode;//���غ������ֵ�ģʽ
	
	CDCtype CDCType;//CDC����
}dvd_local_param_t;

typedef struct{
	u8 savemode;
}dvd_global_param_t;


extern dvd_local_param_t *pLocalParam;
extern dvd_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
