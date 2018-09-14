#ifndef __PARAM_H__
#define __PARAM_H__
#include "acJniSdk.h"

/////////////////////////////////////////////////////////////
enum E_AC_COLD_MODE {AC_COLD_MODE_OFF, AC_COLD_MODE_ON, AC_COLD_MODE_UNKNOW};/*A/CÄ£Ê½*/
enum E_AC_REAR_WINDOW_HEAT_MODE{AC_REAR_WINDOW_HEAT_MODE_OFF, AC_REAR_WINDOW_HEAT_MODE_ON, AC_REAR_WINDOW_HEAT_MODE_UNKNOW};/*ï¿½ó´°¼ï¿½ï¿½ï¿½*/
enum E_AC_WIND_TO_WINDOW_MODE{ AC_WIND_TO_WINDOW_MODE_OFF, AC_WIND_TO_WINDOW_MODE_ON, AC_WIND_TO_WINDOW_MODE_UNKNOW};/*ï¿½ï¿½ï¿½ï¿½Ä£Ê½*/
enum E_AC_OUT_RECYCLE_MODE{AC_OUT_RECYCLE_MODE_OFF, AC_OUT_RECYCLE_MODE_ON,  AC_OUT_RECYCLE_MODE_UNKNOW};/*ï¿½ï¿½Ñ­ï¿½ï¿½*/
enum E_AC_AC_MODE{AC_AC_MODE_OFF, AC_AC_MODE_ON, AC_AC_MODE_UNKNOW};/*ï¿½Õµï¿½ï¿½ï¿½ï¿½ï¿½*/
enum E_AC_AUTO_MODE{AC_AUTO_MODE_OFF, AC_AUTO_MODE_ON, AC_AUTO_MODE_UNKNOW};/*ï¿½Ô¶ï¿½Ä£Ê½(AUTO)*/
enum E_AC_WIND_FACE{AC_WIND_FACE_DOWN_WINDOW, AC_WIND_FACE_FRONT_DOWN,  AC_WIND_FACE_DOWN, AC_WIND_FACE_FRONT,  AC_WIND_FACE_WINDOW, AC_WIND_FACE_UNKNOW};/*ï¿½ï¿½ï¿½ï¿½Ä£Ê½*/
enum E_AC_CTRL_MODE{AC_CTRL_MODE_DOUBLE, AC_CTRL_MODE_SINGLE, AC_CTRL_MODE_UNKNOW};/*Í¬ï¿½ï¿½Ä£Ê½(SYNC)*/


//GOFL ADD^M
enum E_AC_WIND_TO_FACE_MODE{ AC_WIND_TO_FACE_MODE_OFF, AC_WIND_TO_FACE_MODE_ON, AC_WIND_TO_FACE_MODE_UNKNOW};/*<B4><B5><C1><B3>Ä£Ê½*/
enum E_AC_WIND_TO_FEET_MODE{ AC_WIND_TO_FEET_MODE_OFF, AC_WIND_TO_FEET_MODE_ON, AC_WIND_TO_FEET_MODE_UNKNOW};/*<B4><B5><BD><C5>Ä£Ê½*/
enum E_AC_DEGREE_UNIT{AC_DEGREE_UNIT_C, AC_DEGREE_UNIT_F, AC_DEGREE_UNIT_UNKNOW};
#define DEFAULT_N_A_GOLF       "--"


////////////////////////////////////////////////////////////
#define MAX_NUM 16

extern CAcJniSdk g_pClsAcJniSdk;

typedef struct {
	int nOsdStatusMark;
	int bSpeedMarkToOSD;
	
	char leftTemperatureStr[MAX_NUM];
	char rightTemperatureStr[MAX_NUM];
	u16 leftTempValue;
	u16 rightTempValue;
	char leftTempStr[MAX_NUM];
	char rightTempStr[MAX_NUM];

	unsigned char ucSpeed;
	unsigned char ucAcState;

	int iAuTo;

	int bOff;
	int bAc;
	int bInitAc;
	int bBackNext;
	int bFront;
	int bDown;
	int bMax;
	int bBackUp;
	int bLoop;
	int bDual;
	int bSync;
	int bRear_Lock;
	int bAc_max;

	int seatHeatersLeft;
	int seatHeatersRight;
    bool bACAccOn;
	int nToyotaAcOff;
	u8 uToyotaAuto_State;
	u8 ucToyotaAOrCState;
	u8 ucToyotaSpeed;
	u8 uToyotaAcSwitchPos;
	int usToyotaLeftTempValue;
	int usToyotaRightTempValue;
	u8 uToyotaRearWindow_heatState;
	u16 usToyotaLeftTempOSD;
	u16 usToyotaRightTempOSD;

	u8 fks_uinnerLoopState;
	u8 fks_uMaxUpState;
	u8 fks_uAutoState;
	u8 fks_uAcState;
	u8 fks_uAcSwitch;
	u8 fks_uDown;
	u8 fks_uUp;
	u8 fks_uFront;
	u8 fks_uWindSpeed;
	u8 fks_uMaxAcState;
	float fks_fLeftTemperature;
	float fks_fRightTemperature;


	u8 SiYu_uWindSpeed;
	u8 SiYu_uRear;
	u8 SiYu_uAcSwitch;
	u8 SiYu_uLoopState;

	/////////////////////////////////////////////////////////////////////////////////////////////
    //byd
	E_AC_COLD_MODE e_byd_ac_cold_mode;
	E_AC_REAR_WINDOW_HEAT_MODE e_byd_ac_rear_window_heat_mode;
	E_AC_WIND_TO_WINDOW_MODE e_byd_ac_wind_to_window_mode;
	E_AC_OUT_RECYCLE_MODE e_byd_ac_out_recycle_mode;
	E_AC_AC_MODE e_byd_ac_ac_mode;
	E_AC_AUTO_MODE e_byd_ac_auto_mode;
	E_AC_WIND_FACE e_byd_ac_wind_face;
	E_AC_CTRL_MODE e_byd_ac_ctrl_mode;

	u8 u8_byd_wind_level;
	u8 u8_byd_degree_left;
	u8 u8_byd_degree_right;
	s16 s16_byd_degree_out;
	bool bACCanShow;

	//golf
		E_AC_COLD_MODE e_golf_ac_cold_mode;
		E_AC_AC_MODE e_golf_ac_ac_mode;
		E_AC_AUTO_MODE e_golf_ac_auto_mode;
		E_AC_CTRL_MODE e_golf_ac_ctrl_mode;
		E_AC_WIND_TO_WINDOW_MODE e_golf_ac_wind_to_window_mode;
		E_AC_WIND_TO_FACE_MODE e_golf_ac_wind_to_face_mode;
		E_AC_WIND_TO_FEET_MODE e_golf_ac_wind_to_feet_mode;
		E_AC_DEGREE_UNIT e_golf_ac_degree_unit;
		u8 u8_golf_seat_degree_left;
		u8 u8_golf_seat_degree_right;
		u8 u8_golf_degree_left;
		u8 u8_golf_degree_right;
		u8 u8_golf_wind_level;
		bool golf_timer_state;
       //crv
	E_AC_COLD_MODE e_crv_ac_cold_mode;
	E_AC_REAR_WINDOW_HEAT_MODE e_crv_ac_rear_window_heat_mode;
	E_AC_OUT_RECYCLE_MODE e_crv_ac_out_recycle_mode;
	E_AC_AC_MODE e_crv_ac_ac_mode;
	E_AC_AUTO_MODE e_crv_ac_auto_mode;
	E_AC_WIND_FACE e_crv_ac_wind_face;
	E_AC_CTRL_MODE e_crv_ac_ctrl_mode;
	u8 u8_crv_wind_level;
	u8 u8_crv_degree_left;
	u8 u8_crv_degree_right;
	/*******Public Ac Info*******/
	u8 acWindMode;
	u8 acSwitchStatus;
	u8 acMaxSwitchStatus;
	u8 acAUTOSwitchStatus;
	u8 acRMistRemovalStatus;
	u8 acFMistRemovalStatus;
	u8 acFrontWindowBlowMaxStatus;
	u8 acLoopMode;
	u8 acSYNCStatus;
	u8 acWindSpeed;
	u8 acMaxWindSpeed;
	u8 acMinWindSpeed;
	int acTempL;
	int acTempR;
	int acMaxTemp;
	int acMinTemp;
	u8 AorCSwitchStatus;
	u8 acHeatSeatStatusR;
	u8 acHeatSeatStatusL;
	u8 acHeatSeatGradeL;
	u8 acHeatSeatGradeR;
	u8 acTempDataDigits;
	u8 acTempDataUnit;
	//mistra
	u8 ucMistraAOrCState;

	//RearAircondition
	u8 RearAcSwitchStatus;
	u8 RearAcControlLockStatus;
	
	u8 RearAcMinTempLevel;
	u8 RearAcMaxTempLevel;
	u8 RearAcTempValue;
	
	u8 RearAcWindSpeed;
	u8 RearAcMaxWindSpeed;
	u8 RearAcMinWindSpeed;

	u8 RearAcAutoStatus;
	int RearAcMinTempV;
	int RearAcMaxTempV;
	u8 RearAcTempDataDigits;
	u8 RearAcTempDataUnit;
	int RearAcTempV;
	//////////////////////////////////////////////////////////////////////////////////////////////
}local_param_t;


#if 0
typedef struct{
	int m_iSoundChannel;//ï¿½ï¿½ï¿½
	s8 ACenable;//ï¿½Ç·ï¿½ï¿½ï¿½ï¿½ac
	int bInitAC;//ï¿½ï¿½ï¿½ï¿½ï¿½Ð¶ï¿½ï¿½Ç·ï¿½ï¿½Ê¼ï¿½ï¿½ac

	
	u8 ucLeftTemp[2];//left temprature
	u8 ucRightTemp[2];//right temprature
	u8 ucSpeed;//speed
	u8 ucAcState;//state

	//keep old state
	int bMax;//max
	int bFront;//front ï¿½ï¿½ï¿½ÅµÚ¶ï¿½ï¿½ï¿½
	int bDown;//down   ï¿½ï¿½ï¿½Åµï¿½ï¿½ï¿½ï¿½
	int bBackNext;//Frontdown  ï¿½ï¿½ï¿½Åµï¿½ï¿½Ä¸ï¿½  
	int bBackUp;//backup        ï¿½ï¿½ï¿½Åµï¿½ï¿½ï¿½ï¿½
	s16 sAuto;//auto
	int bLoop;//loop
	int bDual;//dual
	int bAc;//ac
	int bOff;//off
	u8 LeftTemperature[MAX_NUM];
	u8 RightTemperature[MAX_NUM];
	int nOSDStateMark;//ï¿½ï¿½ï¿½Ú±ï¿½Ê¶osdï¿½ï¿½ï¿½ï¿½×´Ì¬ï¿½Ç·ñ¶¼½ï¿½ï¿½ï¿½ï¿½ï¿½
	int bSpeedMarkToOSD;//ï¿½ï¿½ï¿½ï¿½osdï¿½ï¿½Ê¾ï¿½Ð¶ï¿½

	//11-12-3
	u8 LeftTemp[MAX_NUM];
	u8 RightTemp[MAX_NUM];
	
}air_global_param_t;
#endif

extern local_param_t *pLocalParam;
//extern air_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);



typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
// ËùÓÐº¯Êý²»¶ÔÖ¸ÕëÔ½½ç´¦Àí
// ·µ»Øunicode16µÄ×Ö·û¸öÊý
uni16_size_t uni16_strlen(const unicode16_t *uni16);
// ½«±ê×¼×Ö·û×ª»»³Éunicode16µÄ×Ö·û
unicode16_t ansi_to_unicode16(const unsigned char ansi);
// ½«±ê×¼×Ö·û´®×ª»»³Éunicode16µÄ×Ö·û´®
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);

#endif
