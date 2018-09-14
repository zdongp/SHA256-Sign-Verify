#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
//#include <cutils/properties.h>
#include "types_def.h"
#include "commonFunc.h"
#include <android/log.h>
#include <ctype.h>
#include <string.h>
#include "moduleParamStruct.h"

#define FLY_TV_BRAKESTATE "fly.tv.brakestate"
#define FLY_TV_TVMODULEEXITE "fly.tv.tvmoduleexite"
#define FLY_TV_TVDriverInit "fly.tv.tvdriverinit"


local_param_t localParam;
local_param_t *pLocalParam = (local_param_t*)&localParam;

global_param_t globalParam;
global_param_t *pGlobalParam = (global_param_t*)&globalParam;


void initReadParameter(int filesize){
	//û��Ҫ����Ĳ���
}
void initSaveParameter(void){
	//TVû��Ҫ����Ĳ���
}
void readParameter(void){

	LOGD("+++++++TV+++readParameter+++++++");

	char property[PROPERTY_VALUE_MAX];

	//property_get(FLY_TV_BRAKESTATE,property,"1");
	//sscanf(property,"%d", &pLocalParam->nIsBrakeState);

	//property_get(FLY_TV_TVMODULEEXITE,property,"0");
	//sscanf(property,"%d", &pLocalParam->nIsTVModuleExite);

	//property_get(FLY_TV_TVDriverInit,property,"0");
	//sscanf(property,"%d", &pLocalParam->nIsTVDriverInit);
}

void saveParameter(void){

	LOGD("++++++TV+++saveParameter+++++");

	char property[PROPERTY_VALUE_MAX];

	//sprintf(property,"%d", pLocalParam->nIsBrakeState);
	//property_set(FLY_TV_BRAKESTATE,property);

	//sprintf(property,"%d", pLocalParam->nIsTVModuleExite);
	//property_set(FLY_TV_TVMODULEEXITE,property);

	//sprintf(property,"%d", pLocalParam->nIsTVDriverInit);
	//property_set(FLY_TV_TVDriverInit,property);

}
