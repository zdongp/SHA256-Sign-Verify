#ifndef __OTHER_MODULE_RESPONSE_COMMAND_H__
#define __OTHER_MODULE_RESPONSE_COMMAND_H__

#include "global.h"
#include "flytypes.h"

void otherModuleInit(void);
void otherModuleDeInit(void);
//void analyseOtherModuleMessage(char sendModuleId, unsigned char *param, unsigned char len);
void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len);

void OtherModuleToRadio_AnalyseSystem(unsigned char *pBuf, int nLen);
void OtherModuleToRadio_AnalyseAudioAndVideo(unsigned char *pBuf, int nLen);
void OtherModuleToRadio_AnalyseKey(unsigned char *pBuf, int nLen);
void OtherModuleToRadio_AnalyseExternalCtrl(unsigned char *pBuf, int nLen);
void moduleToRadio_FromAutomate(u8 *param, int len);
void moduleToRadio_FromCenter_Message(u8 *param, int len);
void moduleToRadio_FromAuxcreen_Message(u8 *buf, int len);

void OtherModuleResponse_ProcessPanelKey_MENU();     //Menu
void OtherModuleResponse_ProcessPanelKey_AV();       //AV
void OtherModuleResponse_ProcessPanelKey_RADIO();
void OtherModuleResponse_ProcessPanelKey_FM1();      //FM1
void OtherModuleResponse_ProcessPanelKey_FM2();      //FM2
void OtherModuleResponse_ProcessPanelKey_AM();       //AM
void OtherModuleResponse_ProcessPanelKey_FM();       //FM
void OtherModuleResponse_ProcessPanelKey_SEEK_INC(); //SEEK_INC
void OtherModuleResponse_ProcessPanelKey_SEEK_DEC(); //SEEK_DEC
void OtherModuleResponse_ProcessPanelKey_TUNE_INC(); //TUNE_INC
void OtherModuleResponse_ProcessPanelKey_TUNE_DEC(); //TUNE_DEC
void OtherModuleResponse_ProcessPanelKey_SEEK_INC_TIMER(void);
void OtherModuleResponse_ProcessPanelKey_SEEK_DEC_TIMER(void);

void Get_SystemAccOn(void);
void Get_SystemAccOff(void); 

void ExternalResponseToRadio_Open();
void ExternalResponseToRadio_Close();
void ExternalResponseToRadio_Open_No_Jump();

void ExternalResponseToRadio_Listen_TheSpecificRadioName(unsigned char *pBuf, int nLen);
void ExternalResponseToRadio_SearchChannel(unsigned char *pBuf, int nLen);
void ExternalResponseToRadio_SetFrequency_FM(unsigned char *pBuf, int nLen);
void ExternalResponseToRadio_SetFrequency_AM(unsigned char *pBuf, int nLen);
void  ExternalResponseToRadio_SetFrequency();
void externalResponseToRadio_Number_num(u8 buff);

void analyseTimerHandleMessage(u8 *p, u8 len);
void analyseAuxcreenSetRadioBandValue(u8 param);

#endif
