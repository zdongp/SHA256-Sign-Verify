#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamStruct.h"
#include "moduleParamRequest.h"

extern void sendGetOtherModuleParam(moduleParam_t *pModuleParam);
moduleParam_t moduleParam;

void getOtherModuleParam(char moduleId, char paramId, unsigned char *param, unsigned char *paramLen){
	moduleParam_t *pModuleParam;

	pModuleParam = (moduleParam_t *)&moduleParam;

	memset(pModuleParam, 0x00, sizeof(moduleParam_t));

	pModuleParam->moduleID = (unsigned char)moduleId;
	pModuleParam->paramID = (unsigned char)paramId;

	sendGetOtherModuleParam(pModuleParam);

	*paramLen = pModuleParam->paramLen;
	memcpy(param, pModuleParam->parambuf, *paramLen);
}
