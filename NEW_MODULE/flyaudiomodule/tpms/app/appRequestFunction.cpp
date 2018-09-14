#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"


void tpmsToApp_SetTPMSMenuIsEnable(u8 state)
{
	if(state == 1){
		setAnalogData(CONTROLID_MENU_TPMS,0);
		setControllable(CONTROLID_MENU_TPMS,true);
	}
	else{
		setAnalogData(CONTROLID_MENU_TPMS,2);
		setControllable(CONTROLID_MENU_TPMS,false);
	}
}

