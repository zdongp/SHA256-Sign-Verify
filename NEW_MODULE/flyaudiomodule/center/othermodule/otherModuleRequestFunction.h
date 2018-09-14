#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__



void centerToModule_NotifySystem_jumpPage(u16 pageId);
void centerToModule_NotifySystem_jumpPrePage(void);
void centerToModule_NotifySystem_Hardware_JumpPrePage(void);
void centerToModule_NotifySystem_EnterThreePartyApp(void);
void centerToModule_NotifySystem_EnterHomePage(void);
void centerToModule_NotifySystem_EnterNonHomePage(void);
void centerToModule_NotifySystem_DebugPanelType(unsigned char panelType);
void centerToModule_NotifyOSD_SetOSDHidden(void);
void centerToModule_NotifyAudiovideo_GpsSoundState(unsigned char state);
void centerToModule_NotifySystem_ReturnToPage(unsigned char *pageid, int len);
void centerToModule_NotifySystem_DisplayBarCode(void);
void centerToModule_NotifySystem_BrightnessBlackPageClick(void);
void centerToModule_NotifyBackExitscreenPage(void);
void centerToModule_NotifyBackOnlyEnterscreen(void);
void centerToModule_NotifyBackEnterLeftscreen(void);
void centerToModule_NotifyAudiovideo_GpsSoundState(unsigned char state);
void centerToModule_NotifyAudiovideo_AppRequestMixedVoice(unsigned char mixed);
void centerToModule_NotifyAudiovideo_SimulationOfGPS_Process_RequestMixedVoice(unsigned char mixed);


void centerToModule_NotifyBackEnterAllscreen(void);
void centerToModule_NotifyBackExitAllscreen(void);
void centerToModule_NotifyBackEnterFrontscreen(void);
void centerToModule_NotifyBackEnterBehindscreen(void);
void centerToModule_NotifyBackEnterRigthscreen(void);
void centerToModule_NotifySystem_EnterGpsPage(void);
void centerToModule_NotifySystem_Brightness(unsigned char brightness);
void centerToModule_NotifySystem_ScreenOff_Brightness(unsigned char brightness);
void centerToModule_NotifySystem_SIMPhoneStatus(char status);
void centerToModule_NotifyBT_SIMPhoneStatus(char status);
//void centerToModule_NotifyBT_HelpSet(void);
//void centerToModule_NotifyBT_HelpPhone(unsigned char state);
//void centerToModule_NotifyBT_State();
void centerToModule_NotifySystem_BrightnessBlackPageClick(void);

void centerToModule_NotifyAudiovideo_AndroidIntentAction_MediaPlay_States(u8 state);

void centerToModule_NotifyOtherModule_FromAndroid_Power_OnOrOff_0s(u8 state);
void centerToModule_NotifyService_FromAndroid_Acc_OnOrOff_30s(u8 state);
void centerToModule_NotifyService_FromAndroid_FastToSwitichMachine_60s(u8 state);

void centerToModule_NotifyService_FromAndroid_PingLoop(u8 state);
void centerToModule_NotifyService_FromAndroid_15DaysReset(u8 *param,int len);

void centerToModule_NotifyFlyRemoteOnline_FromAndroid_FastToSwitichMachine_60s(u8 state);

void centerToModule_NotifyAudiovideo_SetThirdChannel();
void centerToModule_NotifySystem_SysTimeFormat(u8 p);
void centerToModule_NotifyExtcar_FordTCU_Request(u8 p);

#endif
