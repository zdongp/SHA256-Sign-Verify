#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
#include <commonFunc.h>
#include "moduleParamResponse.h"


#define FLY_SET_LANGUAGETYPE_T123 "fly.set.LanguageType.t123"
#define FLY_SET_BACKCAR_THREE_ANGLES "fly.set.backcar.threeangle"
#define FLY_SET_ACOSD_NOSHOW "fly.set.acosd.noshow"

#define FLY_MODULE_IS_T123 "fly.module.is.T123"

osd_local_param_t localParam;
osd_local_param_t *pLocalParam = (osd_local_param_t*)&localParam;

osd_global_param_t globalParam;
osd_global_param_t *pGlobalParam = (osd_global_param_t*)&globalParam;

void readParameter(void){
    LOGD("OSD readParameter");
    OSDModule_SetDefaultParam();
    char property[PROPERTY_VALUE_MAX];

	property_get(FLY_MODULE_IS_T123,property,"0");
	sscanf(property,"%d", &pLocalParam->uModuleOsd_is_T123);

	property_get(FLY_SET_LANGUAGETYPE_T123,property,"0");
	sscanf(property,"%d", &pLocalParam->nLanguageType);
	LOGD("readParameter----pLocalParam->nLanguageType:%d",pLocalParam->nLanguageType);

	property_get(FLY_SET_BACKCAR_THREE_ANGLES,property,"0");
	sscanf(property,"%d", &pLocalParam->bBackcarThreeAngle);

	property_get(FLY_SET_ACOSD_NOSHOW,property,"0");
	sscanf(property,"%d", &pLocalParam->bNoShowACosdState);

}

void saveParameter(void){
    LOGD("OSD saveParameter");
    char property[PROPERTY_VALUE_MAX];

	sprintf(property,"%d", pLocalParam->nLanguageType);
    property_set(FLY_SET_LANGUAGETYPE_T123,property);
    LOGD("saveParameter----pLocalParam->nLanguageType:%d",pLocalParam->nLanguageType);

	sprintf(property,"%d", pLocalParam->bNoShowACosdState);
    property_set(FLY_SET_ACOSD_NOSHOW,property);
}
