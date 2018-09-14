#ifndef __OTHER_MODULE_RESPONSE_COMMAND_H__
#define __OTHER_MODULE_RESPONSE_COMMAND_H__

#include "global.h"
#include <flytypes.h>

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len);

void OtherModuleToBackCar_AnalyseSystem(unsigned char *pBuf, int nLen);
void OtherModuleToBackCar_AnalyseKey(unsigned char *pBuf, int nLen);
void OtherModuleToBackCar_AnalyseBluetooth(unsigned char * pBuf,int nLen);//处理倒车来电
void OtherModuleToBackCar_AnalyseAudiovideo(unsigned char * pBuf,int nLen);
void OtherModuleToBackCar_AnalyseOsd(unsigned char * pBuf,int nLen);
void OtherModuleToBackCar_AnalyseAutomate(unsigned char * pBuf,int nLen);
void moduleToBackCar_FromAudiovideo_GetOsdVideoSetting(unsigned char type, unsigned char value);

void Get_SystemVideoState(u8 bIsBacking, u8 bIsHaveVideo);//视频状态
void Get_SystemWakeUp(void);
void Get_SystemSleep(void);

void Get_SystemAccOn(void);
void Get_SystemAccOff(void);

bool IsCanJumpBackVidePage(u8 uCmd1,u8 uCmd2);

/*---------------添加倒车雷达数据接受*/
//void Get_Radar_Info(u8 pBuf,int nLen);

void Get_System_Video_TraceType(u8 p);
void Get_Extcar_Message_Public(u8 *p,u8 len);
void analysePublicCarInfoToBackCarSet(u8 *p,u8 len);







#endif
