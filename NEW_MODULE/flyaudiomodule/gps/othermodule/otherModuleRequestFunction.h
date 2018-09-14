#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__


void gpsToModule_NotifySystem_jumpPage(u16 pageId);
void gpsToModule_NotifySystem_jumpPrePage(void);

void gpsToModule_NotifyDVDModule_jumpPage(void);
void gpsToModule_NotifyTVModule_jumpPage();
void gpsToModule_NotifyAuxModule_jumpPage();
void gpsToModule_NotifyAuxscreen_NaviInformation(u8 *param,int len);
void gpsToModule_NotifyOSD_aboutSwitchingLanguage(u8 param1,u8 param2);
void gpsToModule_NotifyBT_aboutPTT(u8 *param,u8 len);
void gpsToModule_NotifyBT_aboutSwitchingLanguage(u8 param1,u8 param2);
void gpsToModule_NotifyAuxscreen_GaodeMap_Information(u8 *param,int len);
void gpsToModule_NotifyExtcar_aboutSwitchingLanguage(u8 param);


#endif
