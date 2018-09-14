#ifndef __PARAM_H__
#define __PARAM_H__

typedef struct {
	unsigned char uModuleOsd_is_T123;
	int osddebuginfo_switch;
	int osdsettime;

	unsigned char uKey_OSDEvent;//Drop OSD display track and DVD track non-corresponding problem
	int m_nCurOSDContent;  //
	int m_nVideoSettingItem;
	int m_timerSettingVideo;
	unsigned char  m_haveRadar;
	unsigned char nLanguageType;
	bool     bOnSystemPage;
	bool     bBackcarThreeAngle;
	bool bDropDownOSD_Switch;
	bool bNoShowACosdState;
}osd_local_param_t;

typedef struct{
}osd_global_param_t;


extern osd_local_param_t *pLocalParam;
extern osd_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
