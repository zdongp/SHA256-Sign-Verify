#ifndef __MODULE_PARAM_RESPONSE_H__
#define __MODULE_PARAM_RESPONSE_H__



#define FLY_GPS_RUNING				"fly.gps.run" //�����Ƿ���״̬

///////2013-05-02 Beginning, the new structure to use definition///05-09changing////
///UI-->Module///
#define PAGEACTION_ENTER_FLYAPP		0xFF01
#define PAGEACTION_BACK_KEY			0xFF02

#define PAGEACTION_SPECIAL_PREPAGE_DVR_LIST     0xFF04

#define PAGEACTION_ENTER_THIRDAPP 	0xFF11
#define PAGEACTION_ENTER_MEDIAAPP	0xFF21
#define PAGEACTION_ENTER_GPSAPP		0xFF31
#define PAGEACTION_ENTER_3GPHONEAPP	0xFF41

#define PAGEACTION_ENTER_DDBOX_CARLIFE_APP	0xFF91

#define PAGEACTION_ENTER_NO_SPEECH_APP	0xFC01
#define PAGEACTION_ENTER_NO_NAVIGATION_APP	0x1111


////Module_UI////
#define PAGE_FINISH_FLYAPP		0xFF00
#define PAGE_FINISH_MEDIAAPP	0xFF20
#define PAGE_FINISH_GPSAPP      0xFF30

//////////////////////////////////////////////////////////////////////////


int module_extendInterface(char *buffer, int len);
void moduleParameterInit(void);
void moduleParameterDeInit(void);
void SystemModule_SetDefaultParam();
void SystemModule_InitByConfig();
void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen);
void moduleParameterReInit(void);


//2012-03-14
void SystemModule_Process_AccOff();
void SystemMoudule_Process_AccOn();
void SystemModule_Process_Reset();
void SystemModule_Process_ResetDefault();
void ReadAllNaviNameAndPath();
void ReadAllNaviNameAndFlyapdataConfigPath();
void SystemModule_CheckCarMode(void);
void halToSystem_ChooseCarMode(int ctrID,u8 *pBuf, u8 len);


void SystemModule_initVoltageProtection();
void SystemModule_SetMachineInit_FanState();
void SystemModule_SetMachineInit_CPUState();
void initBackModeUI(void);

void SystemModule_ReadParam_aboutMPEG();
void SystemModule_ReadDeviceNode_aboutUUID();
void SystemModuleToUI_DisplayingUUID(char *buf);
void SystemModuleToUI_aboutStartupVolume();
void SystemModuleToUI_aboutPanelLight();

void SystemModuleToUI_setVisible(void);
void SystemModule_NavigationBootingRunMod();
void SystemModule_Init_TriggerType_SetVisible();  //zhq add

void SystemModuleParam_CheckCarMode(void);
void ReadLogoStyleFile();

void NavigationBootingRunMod(u8 p);

void ReadAllReturnToHomeForPageList();
bool judgmentReturnHomePage(u16 curPage);

#endif
