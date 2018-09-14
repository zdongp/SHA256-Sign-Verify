#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__



void appToaircondition_Parameter(unsigned char *param, unsigned char paramLen);

void appToaircondition_EnterMainPage_MouseUp(void);
void appToaircondition_BackPage_MouseUp();
void appToaircondition_ReturnMenuPage_MouseUp(void);

void setWindSpeedAdd();
void setPublicWindSpeedAddOrDec(u8 param);
void setWindSpeedLow();
void setLeftTemperatureAdd();
void setLeftTemperatureAddOrLow(u8 RorL,u8 param);
void setLeftTemperatureLow();
void setRightTemperatureAdd();
void setRightTemperatureLow();
void setACSwitchOff_ON();
void setMaxACOff_ON();
void setAutoSwitchStatus();
void setLoopModeStatus();
void setDualStatus();
void setAcSwitchStatus();
void setRearWindowHeatingStates();
void setWindModeStates();
void setPublicWindModeStates();
void setPublicWindModeStatesForBody(u8 param);


void setFWindowHeatingStates();
void setWindModeStatus(u8 param);
void setLoopModeOfDirect(u8 param);
void setHeatSeatStatus_L();
void setHeatSeatStatus_R();
void setAcHeatSeatGrade_L();
void setAcHeatSeatGrade_R();
void setFrontWindowBlowMax();
void setRearAirconditionSwtich();
void setRearAirconditionControlLock();
void setRearAirconditionWindSpeedControl(u8 p);
void setRearAirconditionTempeartrueControl(u8 p);



void DisplayRearAcSwitchStatus(u8 s);
void DisplayUI_RearAcTempRank(u8 s);
void DisplayRearAcControlLockStatus(u8 s);
void appToaircondition_EnterAcSetPage_MouseUp(void);
void appToaircondition_Set_Page_Back_MouseUp();
void appToaircondition_AutoSwitch_BackRow_MouseUp();
void DisplayRearAcAutoStatus(u8 s);




#endif
