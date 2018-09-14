#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "halResponseFunction.h"
#include "otherModuleResponseFunction.h"


void halToAux_QueryVideo(unsigned char cFlag){

	LOGD("halToAux_QueryVideo--->pLocalParam->bBrakeState:%d", pLocalParam->bBrakeState);
	if (pLocalParam->bBrakeState == false)
		return;
		
	LOGD("halToAux_QueryVideo--->pLocalParam->bEnterAux:%d", pLocalParam->bEnterAux);
	
	if (pLocalParam->bEnterAux == true){        
		if (cFlag == true)//”– ”∆µ
		{
			//moduleToAux_FromSystem_EnterVideo();
		} 
		else
		{
			//moduleToAux_FromSystem_EnterCtrlFace();
		}
	}

}

