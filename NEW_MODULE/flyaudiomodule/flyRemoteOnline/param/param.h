#ifndef __PARAM_H__
#define __PARAM_H__
#include "global.h"

#define CAR_INFORS_LEN 51

enum E_CurCD_Mode{Cur_CD_Mode_ScreenOff,Cur_CD_Mode_ScreenOn};
enum E_REMOTE_REQUEST_OBJECT{REQUEST_OBJECT_UNKNOW,REQUEST_OBJECT_FLY_DEVICE, REQUEST_OBJECT_MOBILE,REQUEST_OBJECT_WECAT};
enum E_DEVICE_LCD_STATE{DEVICE_LCDBRIGHTNESS_BLACK,DEVICE_LCDBRIGHTNESS_LOW,DEVICE_LCDBRIGHTNESS_MID,DEVICE_LCDBRIGHTNESS_HIGH};

typedef struct{
	u16 sCarModels;
	u16 sCars;

	u8 uCarDoorState;
	u8 uCarEngineDoor;

	u8 uCarDoorWindow_FL;
	u8 uCarDoorWindow_FR;
	u8 uCarDoorWindow_RL;
	u8 uCarDoorWindow_RR;

	u8 uCarDormer;
	u8 uCarDoorLock;
	u8 uCarHeadlight;
	u8 uCurCarNaviDeviceState;
	int nCurCarBatteryVoltage;
	int nAccOffCurCarBatteryVoltage;

	char uExtcarInformation[256];
	int nExtcarInfor_Len;

	char uAccOffExtcarInformation[256];
	int  nAccOffExtcarInfor_Len;

	E_DEVICE_LCD_STATE eLCDState;
	E_REMOTE_REQUEST_OBJECT eRequestObject;
	E_CurCD_Mode emCur_CD_State;

	u8 uRealAccStatus;
	
	u8 uCarHandBrake;
	u8 uCarMainDriverSeatBelt;
	int nCarOilConsumption;
	int nCarTotalMileage;
	int nCarEngineSpeed;
	int nCarInstantanousSpeed;
	int nCarWaterTempeature;
	u8 uCarFootBrake;
	u8 uCarStall;
	u8 uCarCleaningLiquid;
	int nCarResiduaMileage;
	u8 nCarAverageFuelConsumptionUnit;
	int nCarAverageFuelConsumption;
	u8 nCarTirePressureUnit;
	u8 nCarTireTempUnit;
	u8 uCarBatteryAnomalyMonitoring;
	int nCarOutsidTempeature;
	u8 uCarCopilotDriverSeatBelt;

}local_param_t;

typedef struct{
}global_param_t;

extern local_param_t localParam;
extern global_param_t globalParam;


extern local_param_t *pLocalParam;
extern global_param_t *pGlobalParam;




void readParameter(void);
void saveParameter(void);

char __intToChar(char value);
char __charToInt(char ch);
int bufferToString(char *buffer, int len, char *str);
int stringToBuffer(char *str, char *buffer);
void getProperty_acc_status(void);
void getProperty_Cur_carInfors(void);

#endif
