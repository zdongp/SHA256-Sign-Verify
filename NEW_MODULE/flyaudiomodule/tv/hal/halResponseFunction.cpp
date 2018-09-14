#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "moduleParamStruct.h"
//·ÖÎöÃüÁî
void analyseHalMessage_TV(u8 uCmd,u8* param,int len){

	 LOGD("analyseHalMessage_TV+++++%x", uCmd);
	 
     switch(uCmd){
	     case 0x01:
		     break;
	     case 0x02:
		    pLocalParam->nIsTVDriverInit = param[0];
                  break;
	     case 0x03:
		     break;
     }
}
