#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__


//void osdToModule_NotifySystem_jumpPage(u16 pageId);
//void osdToModule_NotifySystem_jumpPrePage(void);

void airconditionToModule_NotifySystem_jumpPage(u16 pageID);
void airconditionToModule_NotifySystem_JumpPrePage(void);
void airconditionToModule_NotifySystem_SwitchModule(void);//����AV KEY

void airconditionToModule_NotifyOsd_DisplayACTitle();//显示下拉OSD
void airconditionToModule_NotifyOsd_DisplayOSDACInfor(u16 leftTempValue,u16 rightTempValue,u8 unit,u8 ucSpeed,u8 ucAcState);
void ACToModule_NotifyOsd_DisplayOSDACInfor_Q(u16 leftTempValue,u16 rightTempValue,unsigned char ucSpeed,unsigned char ucAcState);

void sendAcMessageacToOtherModule(u8 *param,u8 len);
void setAcSwitchToHal(u8 param);
void acToHalTempMessage(u8 *param,u8 len);

void acToHalwindMessage(u8 *param,u8 len);
void acToHalWindModeMessage(u8 *param,u8 len);
void acToHalLoopModeMessage(u8 *param,u8 len);
void acToHalACswitchMessage(u8 *param,u8 len);
void acToHalAutoSwitchMessage(u8 *param,u8 len);
void acToHalDualSwitchMessage(u8 *param,u8 len);
void acToHalMistRemovalMessage(u8 *param,u8 len);

void acToHalRearWindowHeatingMessage(u8 *param,u8 len);
void acToHalRearHeatSeatMessage(u8 *param,u8 len);
void acToHalAirConditionLockMessage(u8 *param,u8 len);
void setAcTemperature(int tempL,int tempR,int min,int max,u8 tag,u8 unit);
void setPublicAcTemperature(u8 RorL,u8 param);
void setAcwindSpeed(u8 param,u8 min,u8 max);
void setpublicAcwindSpeed(u8 param);
void setAcwindMode(u8 param);
void setPublicAcwindMode();
void setPublicAcwindModeForBody(u8 param);

void setAcLoopMode(u8 param);
void setAcAorCSwitch(u8 param);
void setAcAorCMaxSwitch(u8 param);
void setAcAutoSwitch(u8 param);
void setAcDualSwitch(u8 param);
void setAcFWindowHeating(u8 param);
void setAcRearWindowHeating(u8 param);
void setAcInfoToSdk(u8 *param,int len);
void setAcHeatSeatSwitch(u8 LorR,u8 param);
void acToHalHeatSeatMessage(u8 *param,u8 len);
void setAcHeatSeatGrade(u8 RorL,u8 param);
void setAcFrontWindowBlowMax(u8 param);

//RearAC
void setRearAcSwitchToHal(u8 param);
void setRearAcTempeartrueControl(u8 param);
void acToHalRearAcTempeartrueCtrlMessage(u8 *param,u8 len);
void setRearAcWindSpeed(u8 param);
void acToHalRearAcWindSpeedMessage(u8 *param,u8 len);
void setRearAcControlLockToHal(u8 param);
void setAcAutoSwitchBackRow(u8 param);







#endif
