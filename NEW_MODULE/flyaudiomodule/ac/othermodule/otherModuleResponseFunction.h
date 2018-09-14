#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__



void Set_InitMsg();
void GetParamOfACShow();

void Get_System_AccOn();
void Get_System_AccOff();
void halToSystem_Galaxy_AccOn();
void halToSystem_Galaxy_AccOff();
int moduleToAIRCONDITION_FromSystem_Message(unsigned char *param, unsigned char len);
int moduleToAIRCONDITION_FromExtcar_Message(unsigned char *param, unsigned char len);
void moduleToAIRCONDITION_FromExternalCtrl_Message(unsigned char *param, unsigned char len);
void moduleToAIRCONDITION_FromAutomate_Message(u8 *param, u8 len);

int otherModule_InitACData();

void analyFocusAcData(u8* param,u8 len);

void analySiYuAcData(u8* param,u8 len);

void analyToyotaAcData(u8* param,u8 len);

void analyse_byd_ac_data(u8* param, u8 len);
void analyse_golf_ac_data(u8 *param, u8 len);
void analyse_golf_ac_ctrl(u8 param);
void analyse_golf_ac_acState(u8 p);

void analyse_HondaCRV_ac_data(u8* param, u8 len);
void analyse_Mistra_ac_data(u8 *p,u8 len);


/**************************Mistra responseFuntion*********************/
void moduleToAIRCONDITION_FromKey_Message(u8 *param,u8 len);

void halToAc_AcSwitch(u8 *p,u8 len);
void halToAc_AcTemperature(u8 *p, u8 len);
void halToAc_AcAirSpeed(u8 *p, u8 len);
void halToAc_AcWindDirection(u8 *p, u8 len);
void halToAc_AcAirCycle(u8 *p, u8 len);
void halToAc_AcRefrigeration(u8 *p, u8 len);
void halToAc_MaxRefrigeration(u8 *p, u8 len);
void halToAc_AcAutoSwitch(u8 *p, u8 len);
void halToAc_AcSyncSwitch(u8 *p, u8 len);
void halToAc_AcDemist(u8 *p, u8 len);
void halToAc_Luch(u8 *p, u8 len);
void halToAc_SeatHeating(u8 *p, u8 len);


/***********Public Ac Info Function******************/
void analyse_Public_ac_date(u8 *param, u8 len);

void getAirConditionSwitchStatus(u8 *param,u8 len);
void getAirConditionTemperatureValue(u8 *param,u8 len);
void getAirConditionWindSpeedValue(u8 *param,u8 len);	
void getAirConditionWindMode(u8 *param,u8 len);		
void getAirConditionLoopMode(u8 *param,u8 len);
void getAirConditionACSwitchStatus(u8 *param,u8 len);
void getAirConditionAUTOSwitchStatus(u8 *param,u8 len);
void getAirConditionSYNCorDUALSwitchStatus(u8 *param,u8 len);
void getAirConditionFrontGlassMistRemoval(u8 *param,u8 len);
void getAirConditionRearwindowHeatingOrGlassMistRemoval(u8 *param,u8 len);
void getAirConditionHeatSeat(u8 *param,u8 len);
void getBackSeatAirConditionLock(u8 *param,u8 len);
void getRearAirConditionSwitchStatus(u8 *param,u8 len);
void getRearAirConditionTemperatrueData(u8 *param,u8 len);
void getRearAirConditionWindSpeedData(u8 *param,u8 len);
void getRearAirConditionControlLock(u8 *param,u8 len);
void getRearAirConditionRearAcAutoStatus(u8 *param,u8 len);


void moduleToAIRCONDITION_FromJniSdk_Message(u8 *param,u8 len);
void SenfCurAcInfoToSdk();
void sendToModuleJniSdk_AcSwitch(u8 param);
void sendToModuleJniSdk_AcTemp(int min,int max,int Ltemp,int Rtemp,u8 Decimal,u8 unit);
void sendToModuleJniSdk_AcWindSpeed(u8 min,u8 max,u8 speed);
void sendToModuleJniSdk_AcWindMode(u8 param);
void sendToModuleJniSdk_AcLoopMode(u8 param);
void sendToModuleJniSdk_AcAorCStatus(u8 param);
void sendToModuleJniSdk_AcMaxAorCStatus(u8 param);
void sendToModuleJniSdk_AcAutoSwitch(u8 param);
void sendToModuleJniSdk_AcDual(u8 param);
void sendToModuleJniSdk_FrontClassMistRemoval(u8 param);
void sendToModuleJniSdk_RearWindowHeat(u8 param);   //Glass mist removal
void sendToModuleJniSdk_HeatSeatStatus(u8 tag,u8 param);
void sendToModuleJniSdk_HeatSeatGrade(u8 tag,u8 param) ;

void analysAcTempAndSendToSdk(int min, int max, int tempL, int tempR,u8 Digits,u8 unit);
void analysAcWindSpeedAndSendToSdk(u8 min, u8 max, u8 curvalue);
void sendToAcTempToSdk_Golf();


#endif
