#ifndef __PARAM_H__
#define __PARAM_H__

#define FILE_FOLDER_NAME_MAX_LEN		256
#define FILE_FOLDER_ITEM_MAX_COUNT		5

#define TRACKLIST_ITEM_COUNT		20
#define FILE_FOLDER_ITEM_COUNT		FILE_FOLDER_ITEM_MAX_COUNT

typedef struct {
	u8 nIsBrakeState;//是否有刹车状态
	u8 nIsTVModuleExite;//是否有电视模块
	u8 nIsTVDriverInit;//是否初始化完成

}local_param_t;

typedef struct{

}global_param_t;


extern local_param_t *pLocalParam;
extern global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
