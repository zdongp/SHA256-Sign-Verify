#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include "types_def.h"
#include "commonFunc.h"
#include "global.h"
#include "appResponseFunction.h"
#include "timer_interface.h"
#include "pageID.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "param.h"
#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"
#include "halRequestFunction.h"
//#include <cutils/properties.h>
#include "moduleParamResponse.h"


int TimerHandlerCenter(timer_t timerId){

	switch((s64)timerId)
	{
		case ACCON_STOP_DYNAMICLOGO://ACCON�ص���̬LOGO
		{
			LOGD("ACCON_STOP_DYNAMICLOGO");
			property_set("ctl.stop","bootanim");
		}
		break;
		case OSD_TIMER_BARCODE_SYS_DISPLAY:
		{
	    	systemToModule_NotifyOSD_OSD_barcode();
			//SystemModule_ReadBarCode();
		}
		break;
		case DVD_SWITCH_TIMERID:
		{
		
	     if(pLocalParam->u8_Sys_StandbyStatus==0)
		 	     return 0;
		 	     
		  switch(getCurPage())
		   {
		    case PAGE_STANDBY:
			     anyModuleToSysModule_Switch_PrePage();
			     break;
		    default:break;
		   }

		    
			LOGD("DVD_SWITCH_TIMERID getCurPage():%x-",getCurPage());
			if(getCurPage()== PAGE_THIRD_PAGE)
				pLocalParam->b_NeedLaunchThirdApp = true;
			else
				pLocalParam->b_NeedLaunchThirdApp = false;
			LOGD("settimer pLocalParam->b_NeedLaunchThirdApp:%x",pLocalParam->b_NeedLaunchThirdApp);
			char property[64];
			sprintf(property,"%d", pLocalParam->b_NeedLaunchThirdApp);
     		property_set(FLY_SET_NEEDLAUNCH,property);
				
			switch_Page(PAGE_STANDBY);
		}
		break;
		case STANDY_TIMER:
		{
			systemToHal_StandyState(pLocalParam->u8_Sys_StandbyStatus,pLocalParam->u8_Sys_StandbyStatus1);
		}
		break;
		case APP_TIMER:
		{
			System_ReturnAppStandyState(false);
		}
		break;
		case AUX_TIME_DISPLAY:
		{
	   		SystemModuleToAUX_DisplaySystemTime();
		}
		break;
		case MCU_CLOSING_BOX:
			UI_Display_MCS_MassageFunction_closing_PromptBox(0);
		break;
		case MCU_PAGE_TIMEOUT:
			systemToModule_NotifySystem_JumpPrePage();
		break;
		default:break;
	}
	
	return 0;
}

void initTimerCenter(timer_handler_function func){
	u8 buf[] = {0x10,0x00,0x00,0x00,0x00};

    buf[1] = ((u64)func >> 24) & 0xFF;
    buf[2] = ((u64)func >> 16) & 0xFF;
    buf[3] = ((u64)func >> 8) & 0xFF;
    buf[4] = (u64)func & 0xFF;


    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_TIMER,buf,5);

}

int SetTimer(int nElaspe_ms, int nMode, int timerId){
	u8 buf[10];

	buf[0] = 0x20;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    buf[5] = (nElaspe_ms >> 24) & 0xFF;
    buf[6] = (nElaspe_ms >> 16) & 0xFF;
    buf[7] = (nElaspe_ms >> 8) & 0xFF;
    buf[8] = nElaspe_ms & 0xFF;

	buf[9] = (u8)nMode;
    
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_TIMER,buf,10);

    return 0;

}

int DeleteTimer(int timerId){
	u8 buf[5];

	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    //LOGD("MODULE_ID_SYSTEM:->MODULE_ID_TIMER:%x",timerId);
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_TIMER,buf,5);

    return 0;

}
