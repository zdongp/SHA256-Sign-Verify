#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"




dvd_local_param_t localParam;
dvd_local_param_t *pLocalParam = (dvd_local_param_t*)&localParam;

dvd_global_param_t globalParam;
dvd_global_param_t *pGlobalParam = (dvd_global_param_t*)&globalParam;


void initReadParameter(int filesize){

}


void initSaveParameter(void){

	pGlobalParam->savemode= pLocalParam->setMode;

}



void readParameter(void){

}

void saveParameter(void){

}
