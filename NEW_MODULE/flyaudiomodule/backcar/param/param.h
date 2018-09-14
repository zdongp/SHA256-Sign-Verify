#ifndef __PARAM_H__
#define __PARAM_H__

#define BACK_CAR_MOVE_LINE_RANGE	 10

enum Em_Backcar_TraceType{TraceType_0,TraceType_1,TraceType_2};

typedef struct {
	
	u8 bIsIsrCountry;
	u8 bIsInBackCar;
	u8 cCurPosOfLine;
	u8 cMaxRangeOfLine;
	u8 bIsBackCarRadarCanSee;
    u8 u_CarType;
	u8 bBackstate;
	u8 bBackVideostate;
	u8 saveBackCar;
	//u8 b_AutoEnterBack;
	u8 EnterAllScreen;
	char c_carName[20];
	u8 udialin;//��������
	bool bBackVideo_SetColor;
	u8   cBackcarWarnTextTime;
	bool bBackcarThreeAngle;
	u8 nBackVisionAngle;
	u8 uTempWarningDontShow;

	Em_Backcar_TraceType e_Backcar_TraceType;
	u8 uVideoZoomInOrOut;

}back_local_param_t;

typedef struct{
	u8 cCurPosOfLine;
}back_global_param_t;


extern back_local_param_t *pLocalParam;
extern back_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);
int getSystemSkinType();











#endif
