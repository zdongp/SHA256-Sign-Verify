#include <stdio.h>
#include <stdlib.h>
#include <commonFunc.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
#include "moduleParamResponse.h"

#define FLY_EXTCAR_DA_ZHONG_SEND_CHINESE_TO_CAR_SCREEN		"fly.extcar.cnswitch"

auxscreen_local_param_t localParam;
auxscreen_local_param_t *pLocalParam = (auxscreen_local_param_t*)&localParam;


void readParameter(void){
	setDefaultParam();

	char property[PROPERTY_VALUE_MAX];
	property_get(FLY_EXTCAR_DA_ZHONG_SEND_CHINESE_TO_CAR_SCREEN,property, "1");
	sscanf(property,"%d", &pLocalParam->nAuxScreenCanSendChinese);
}

void saveParameter(void){
}
