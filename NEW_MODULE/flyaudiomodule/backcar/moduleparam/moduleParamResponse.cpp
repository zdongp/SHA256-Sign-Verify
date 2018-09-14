#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "paramID.h"
#include "controlID.h"
#include "moduleParamResponse.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "appResponseFunction.h"

#include "timer_interface.h"
#include "halRequestFunction.h"


void moduleParameterInit(void)
{
	LOGD("[%s]",__FUNCTION__);
}

void moduleParameterDeInit(void)
{
	LOGD("[%s]",__FUNCTION__);
	//ModuleParamResponse_WriteData();
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		case BACK_CAR_STATE:
			{
				if (param)
					*param = pLocalParam->bIsInBackCar;
				if (paramLen)
					*paramLen = 1;
			}
			break;
		case BACK_CAR_RADAR_STATUS:
			if (param)
					*param = pLocalParam->bIsBackCarRadarCanSee;
				if (paramLen)
					*paramLen = 1;
			break;
		default:break;
	}
}

void ModuleParamResponse_InitByConfig(void)
{
	//ModuleParamResponse_ReadData();
	setValues(CONTROLID_BACK_VIDEO_GAUGE, pLocalParam->cMaxRangeOfLine);
	BackcarToHal_QueryBackcarVideoStatus();
	BackcarVideo_IsShowVideoColorButton(false);
	ToUI_BackCarVideo_TraceType(pLocalParam->e_Backcar_TraceType);
	backCarToModule_NotifySystem_BackCarVideoLineType((u8)pLocalParam->e_Backcar_TraceType);
	IsDisplaying_WarnintLineText(pLocalParam->uTempWarningDontShow);
}

void ModuleParamResponse_InitParam()
{
	pLocalParam->bIsIsrCountry = 0;
	pLocalParam->bIsInBackCar = false;
	pLocalParam->bBackVideostate = false;
	pLocalParam->u_CarType=0;
	pLocalParam->cCurPosOfLine = BACK_CAR_MOVE_LINE_RANGE / 2;
	pLocalParam->cMaxRangeOfLine = BACK_CAR_MOVE_LINE_RANGE;
	pLocalParam->bIsBackCarRadarCanSee = false;
	pLocalParam->bBackVideo_SetColor=true;

	pLocalParam->bBackstate = false;
	pLocalParam->saveBackCar=0x02;
	pLocalParam->EnterAllScreen=0;
	pLocalParam->udialin = false;	//��������
	pLocalParam->cBackcarWarnTextTime=3;
	pLocalParam->bBackcarThreeAngle = false;
	pLocalParam->nBackVisionAngle = 0x01;
	
	pLocalParam->uTempWarningDontShow=0;
	pLocalParam->e_Backcar_TraceType = TraceType_0;
	pLocalParam->uVideoZoomInOrOut =0x00;
}

void ModuleParamResponse_ReadData(void)
{
	readParameter();
}

void ModuleParamResponse_WriteData(void)
{
	saveParameter();
}

void moduleParameterReInit(void)
{
	LOGD("&&&&&&&&&&&&&&&&&&&& backcar moduleParameterReInit");
	ModuleParamResponse_InitParam();
	moduleParameterInit();
}
int module_extendInterface(char *buffer, int len)
{
	u8 ucSystemCmd = buffer[0];
	u8 ucSystemParam = buffer[1];
	LOGD("************************[%s]:%x,%x",__FUNCTION__,ucSystemCmd,ucSystemParam);
	switch(ucSystemCmd){
		case 0x2C: //ACC Off Or Reset Or Default
			{
				if(ucSystemParam == 0x00) //Acc Off
				{		
					ModuleParamResponse_WriteData();
				}
				else if(ucSystemParam == 0x01)
				{
					ModuleParamResponse_WriteData();
				}
				else if(ucSystemParam == 0x02)
				{
					ModuleParamResponse_InitParam();
					ModuleParamResponse_WriteData();
				}
			}
			break;
		case 0x2D: //ACC On
			{
			}
			break;
		case 0xFD:
			{
				//initTimerCenter(&TimerHandlerCenter);
				ModuleParamResponse_InitByConfig();
			}
			break;
		default:break;
	}
	
	return 0;
}
