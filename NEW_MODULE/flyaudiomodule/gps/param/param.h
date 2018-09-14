#ifndef __PARAM_H__
#define __PARAM_H__

typedef struct {
	int auto_gps_voice_enable;

	int m_nLanguageId;
}gps_local_param_t;

//typedef struct{
	
//}osd_global_param_t;


extern gps_local_param_t *pLocalParam;
//extern osd_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
