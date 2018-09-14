#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "halRequestFunction.h"

extern "C"{
#include "unicodestring.h"
};

void syncToApp_SetSYNCMenuEnable(void){
	setAnalogData(CONTROLID_MENU_SYNV,0);
	setControllable(CONTROLID_MENU_SYNV,true);
}

void syncToApp_SetSYNCMenuDisable(void){
	setAnalogData(CONTROLID_MENU_SYNV,2);
	setControllable(CONTROLID_MENU_SYNV,false);
}

