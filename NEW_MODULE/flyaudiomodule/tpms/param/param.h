#ifndef __PARAM_H__
#define __PARAM_H__

#include <vector>
#include "CNotifyAndResponseFlyJniSdk.h"

using namespace std;
typedef struct
{
	u32 u32_tire_pressure;
	int u32_temperature;/*u32��Ϊint����,�п����¶�Ϊ����*/
	bool b_battery_low;
	bool b_update;
	/*<<<<<<<<<---------[BEN] ADD---------------*/
	int min_pressure_abnormal_times;
	int  max_pressure_abnormal_times;

	int u32_battery_low_power_times;
	int u32_temperature_times;
	
	u32 u32_pre_tire_pressure;
	int u32_pre_temperature;
	bool b_pre_battery_low;	
	/*----------------------END------>>>>>>>>>>*/
}TPMS_Data;


enum emClearData{emClearData_FL,emClearData_RL,emClearData_FR,emClearData_RR,emClearData_NO};
enum emTireNum{emTire_FL,emTire_FR,emTire_RL,emTire_RR,emTire_NONE};
enum emAlarmType {Alarm_Close=0x00,Alarm_Text=0x01,Alarm_Voice=0x02}; 
enum emTemperatureUint {Temp_Uint_C=0x00,Temp_Uint_F=0x01}; 
enum emPressureUint {Pressure_PSI=0x00,Pressure_KPA=0x01,Pressure_BAR = 0x02}; 

//新协议7500 III OSD Ctrl  
enum emOsdControlCommand	{FL_Power_Low=0x00,FR_Power_Low=0x01,RL_Power_Low=0x02,RR_Power_Low=0x03,FL_Temperature_High=0x10,FR_Temperature_High=0x11,RL_Temperature_High=0x12,RR_Temperature_High=0x13,
FL_Pressure_High=0x20,FR_Pressure_High=0x21,RL_Pressure_High=0x22,RR_Pressure_High=0x23,FL_Pressure_Low=0x30,FR_Pressure_Low=0x31,RL_Pressure_Low=0x32,RR_Pressure_Low=0x33};




//Default value 
#define TPMS_DEFAULT_MAX_ALARM_TEMPERATURE  70
#define TPMS_DEFAULT_MAX_ALARM_TIRE_PRESSURE 450
#define TPMS_DEFAULT_MIN_ALARM_TIRE_PRESSURE 260

#define TPMS_MAX_TEMPERATURE_TOP 90
#define TPMS_MAX_TEMPERATURE_LOW 30
#define TPMS_MAX_TIRE_PRESSURE_TOP 600
#define TPMS_MAX_TIRE_PRESSURE_LOW 380
#define TPMS_MIN_TIRE_PRESSURE_TOP 360
#define TPMS_MIN_TIRE_PRESSURE_LOW 160
#define TPMS_DEFAULT_BATTERY 120

/*<<<<<<<<<<----------[BEN] ADD----------------*/
#define TPMS_UP_TO_WARMING_TIMES	5
/*----------------------END----->>>>>>>>>>>>>>*/

//IDS STRING
#define IDS_INFO_LF 27
#define IDS_INFO_LR 28
#define IDS_INFO_RF 29
#define IDS_INFO_RR 30

#define IDS_INFO_PATOOHIGH 31
#define IDS_INFO_PATOOLOW 32
#define IDS_INFO_TPMSTOOHIGH 33
#define IDS_INFO_LOWBATTERY 34

#define IDS_TPMS_TIPS_TYPE_1 35
#define IDS_TPMS_TIPS_TYPE_2 36
#define IDS_TPMS_TIPS_TYPE_3 37

#define IDS_TEMPERATURE_UNIT_C 38
#define IDS_TEMPERATURE_UNIT_F 39
#define IDS_TIRE_PRESSURE_UNIT_KPA 40
#define IDS_TIRE_PRESSURE_UNIT_PSI 41

typedef struct {
    int u32_tpms_max_alarm_temperature; //Max Temperature
    u32 u32_tpms_max_alarm_tire_pressure; //Max tire pressure 
    u32 u32_tpms_min_alarm_tire_pressure; //Min tire pressure
    u8 u8_tpms_termerature_uint;
    u8 u8_tpms_tire_pressure_uint;

	TPMS_Data tpms_data[4];
    u8 u8_tpms_alarm_type;//������ʽ
	
    u8 u8_tpms_clear_data;

	bool u8_tpms_bInitState;
	u8 u8_tpms_pair;

	u8 u8_CurAlarmValue;

	bool bCanRing;	// Ctrl ring time
	u8 curTire;
	u8 swapTire;
	u32 tireSignIDArr[4];
	bool swapbtn; /*�û���ť�Ƿ��ܰ�*/
	/*��̥����״̬˵��*/
	/* 0x01 ��ѹ�ͱ��� 0x02 �¶ȸ߱��� 0x04 ̥ѹ�߱��� 0x08 ̥ѹ�ͱ��� */
	u8 ucFLAlarmstate; 
	u8 ucFRAlarmstate;
	u8 ucRLAlarmstate;
	u8 ucRRAlarmstate;

	u32 curAlarmTextID;
	vector<u32> vecAlarmText;

	u32 curAlarmRingID;
	vector<u8> vecAlarmRing;

	u8 ucTpmsPairStatus;
	
	int publicTp_data[4];
	int publicTm_data[4];
}tpms_local_param_t;

typedef struct{
}tpms_global_param_t;

extern tpms_local_param_t localParam;
extern tpms_global_param_t globalParam;
extern TPMS_Data local_TPMS_Data[4];


extern tpms_local_param_t *pLocalParam;
extern tpms_global_param_t *pGlobalParam;
extern CNotifyAndResponseFlyJniSdk g_clsTpms;


void readParameter(void);
void saveParameter(void);

typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
uni16_size_t uni16_strlen(const unicode16_t *uni16);
unicode16_t ansi_to_unicode16(const unsigned char ansi);
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);





#endif

