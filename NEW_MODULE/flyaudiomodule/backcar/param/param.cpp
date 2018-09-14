#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <commonFunc.h>
#include <ctype.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
#include "moduleParamResponse.h"
#include "controlID.h"
#include "otherModuleResponseFunction.h"
#include "pageID.h"
#include "appRequestCommand.h"
#include "otherModuleRequestCommand.h"

#include "timer_interface.h"

#define   FLY_CARNAME          "fly.carName"
#define FLY_BACKCAR_WARNINGTEXT_TIME  "fly.backcar.warningtext.time"
#define FLY_SET_BACKCAR_THREE_ANGLES "fly.set.backcar.threeangle"
#define FLY_SET_BACKCAR_VISIONANGLE "fly.set.backcar.visionangle"
#define FLY_SET_BACKCAR_WARNINGDONTSHOW "fly.backcar.Warning.NoShow"
#define FLY_SET_BACKCAR_TRACE_TYPE "fly.backcar.traceType"
#define FLY_BT_GET_COUNTRYNAME          "fly.module.getCountryName" /*��ISRAEL��*/



back_local_param_t localParam;
back_local_param_t *pLocalParam = (back_local_param_t*)&localParam;

back_global_param_t globalParam;
back_global_param_t *pGlobalParam = (back_global_param_t*)&globalParam;

void initReadParameter(int filesize)
{
	pLocalParam->cCurPosOfLine = pGlobalParam->cCurPosOfLine;
}

void initSaveParameter(void)
{
	pGlobalParam->cCurPosOfLine = pLocalParam->cCurPosOfLine;
}

void readParameter(void){
	ModuleParamResponse_InitParam();
	char property[PROPERTY_VALUE_MAX];

	static char cGetCountryName[128] = {0};
	property_get(FLY_BT_GET_COUNTRYNAME,property,NULL);
	sscanf(property,"%s", &cGetCountryName);
	LOGD("read cGetCountryName:%s",cGetCountryName);
	if(strcmp(cGetCountryName,"ISRAEL") == 0)
	{
		pLocalParam->bIsIsrCountry = 1;
	}
	
   	property_get(FLY_CARNAME,property,"0");
	sscanf(property,"%s",pLocalParam->c_carName);

	property_get(FLY_BACKCAR_WARNINGTEXT_TIME,property,"3");
	sscanf(property,"%d", &pLocalParam->cBackcarWarnTextTime);
	LOGD("[%s] pLocalParam->cBackcarWarnTextTime %d",__FUNCTION__,pLocalParam->cBackcarWarnTextTime);


	property_get(FLY_SET_BACKCAR_THREE_ANGLES,property,"0");
	sscanf(property,"%d", &pLocalParam->bBackcarThreeAngle);
	LOGD("[%s]pLocalParam->bBackcarThreeAngle %d",__FUNCTION__,pLocalParam->bBackcarThreeAngle);

	property_get(FLY_SET_BACKCAR_VISIONANGLE,property,"1");
	sscanf(property,"%d", &pLocalParam->nBackVisionAngle);
	LOGD("[%s] pLocalParam->nBackVisionAngle %d",__FUNCTION__,pLocalParam->nBackVisionAngle);

	property_get(FLY_SET_BACKCAR_WARNINGDONTSHOW,property,"0");
	sscanf(property,"%d",&pLocalParam->uTempWarningDontShow);
	LOGD("[%s] pLocalParam->uTempWarningDontShow:%d",__FUNCTION__,pLocalParam->uTempWarningDontShow);

	property_get(FLY_SET_BACKCAR_TRACE_TYPE,property,"0");
	sscanf(property,"%d",&pLocalParam->e_Backcar_TraceType);
}

void saveParameter(void)
{
	char property[PROPERTY_VALUE_MAX];
	sprintf(property,"%d", pLocalParam->cBackcarWarnTextTime);
	property_set(FLY_BACKCAR_WARNINGTEXT_TIME,property);

	sprintf(property,"%d", pLocalParam->nBackVisionAngle);
	property_set(FLY_SET_BACKCAR_VISIONANGLE,property);

	sprintf(property,"%d", pLocalParam->e_Backcar_TraceType);
	property_set(FLY_SET_BACKCAR_TRACE_TYPE,property);

}
int getSystemSkinType()
{
	char property[PROPERTY_VALUE_MAX];
	int systemSkinType = 0;
	property_get("fly.system.page.type",property,"0");
	sscanf(property,"%d",&systemSkinType);
	return systemSkinType;
}
