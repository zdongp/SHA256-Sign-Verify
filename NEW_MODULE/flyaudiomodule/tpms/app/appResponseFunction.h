#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

void appToTpms_Back_MouseUp(u32 funcID);
//Menu
void appToTpms_EnterTPMS_MouseUp();
void appToTpms_SetUp_MouseUp();
void appToTpms_Pair_MouseUp();
void appToTpms_MeterDigitalInfo_MouseUp();
void appToTpms_Copyright_MouseUp();

void UpdateBattery(u32 ctrlID, bool bLow);
void UpdateData(u32 ctrlID, bool bPair);
void tpms_Temperature_Update(u32 ctrlID, int nData);
void tpms_TirePressure_Update(u32 ctrlID, int nData);




//Setup1
void appToTpms_SetDefaultValue_MouseUp(u32 funcID);
void appToTpms_RegulateAlarmValue(u32 funcID);

void appToTpms_TopTemperature_Inc_MouseUp();
void appToTpms_TopTemperature_Dec_MouseUp();

void appToTpms_TopTirePressure_Inc_MouseUp();
void appToTpms_TopTirePressure_Dec_MouseUp();

void appToTpms_LowTirePressure_Inc_MouseUp();
void appToTpms_LowTirePressure_Dec_MouseUp();

void appToTpms_Unit_Temperature_MouseUp(u32 funcID);
void appToTpms_Unit_TirePressure_MouseUp(u32 funcID);

void appToTpms_NextPage_MouseUp();

//Setup2
void appToTpms_AlarmType_Up_MouseUp();
void appToTpms_AlarmType_Down_MouseUp();

void appToTpms_Clear_MouseUP(u32 funcID);
void appToTpms_Clear_FL_MouseUp();
void appToTpms_Clear_FR_MouseUp();
void appToTpms_Clear_RL_MouseUp();
void appToTpms_Clear_RR_MouseUp();


void appToTpms_PrePage_MouseUp();

void appToTpms_Clean_OK();
void appToTpms_Clean_Cancel();

void Clean_TireData(u8 tireNub);






//----------------------------------

int tpms_Temperature_C_To_F(double nData);
int tpms_Temperature_F_To_C(double nData);
int tpms_TirePressure_Kpa_To_Psi(int nData);
int tpms_TirePressure_Psi_To_Kpa(int nData);



void tpms_Set_MaxAlarm_Temperature(int nData);
void tpms_Set_MaxAlarm_TirePressure(int nData);
void tpms_Set_MinAlarm_TirePressure(int nData);

void tpms_Set_Temperature_Unit();
void tpms_Set_Tire_Pressure_Unit();
void tpms_Set_AlarmType();

void tpmsToUI_setAlarm_TextShow(u8 command);
void tpmsToUI_Load();

void tpmsToT123_setAlarm(u8 command);

void tpmstToUI_Infor_scroll(u8 data);
void Pair_Mode(bool pair);


void appToTpms_DisplayButton(u8 index);
void appToTpms_MainDisplayTpmsBtn_TireSelect(u8 index);
void appToTpms_MainDisplayTpmsBtn_Ensure(void);
void appToTpms_MainDisplayTpmsBtn_Cancel(void);

void clearAlarmText(u8 command);
void pushAlarmTextIdToQueue(u32 alarmTextId);
void pushAlarmRingIdToQueue(u8 alarmRingId);

void popAlarmTextIdToQueue(void);
void popAlarmRingIdToQueue(void);

void public_Tpms_TirePressure_Update(u32 ctrlID,int nData);
void public_Tpms_Temperature_Update(u32 ctrlID,int nData);

#endif
