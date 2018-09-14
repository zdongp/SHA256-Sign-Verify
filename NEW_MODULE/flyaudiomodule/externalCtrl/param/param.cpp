#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
#include "moduleParamResponse.h"



local_param_t localParam;
local_param_t *pLocalParam = (local_param_t*)&localParam;

global_param_t globalParam;
global_param_t *pGlobalParam = (global_param_t*)&globalParam;


void readParameter(void){
	externalctrlModule_SetDefaultParam();
}

void saveParameter(void){

}
