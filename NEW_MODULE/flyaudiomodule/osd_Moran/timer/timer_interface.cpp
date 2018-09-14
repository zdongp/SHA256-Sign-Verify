#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 
#include <param.h>

#include "global.h"
#include "pageID.h"
#include "timer_interface.h"
#include "otherModuleRequestCommand.h"
#include "appRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "halRequestFunction.h"

//timer_t timerIDList[20]; //use to save timer id;
extern int vol_flag; // extern form osd/othermodule/otherModuleResponseFunction.cpp
extern int drop_flag;
extern int LOWBETTERY_DISPLAY_TIME;  //  jing 2013-8-12 delimit low bettery display time (ms)
extern int LOWBETTERY_CLOSE_TIME;  //  jing 2013-8-12 delimit low bettery close time (ms)

int m_nTimerSubTitle = 0;
int m_nTimerOSDPage = 0;
int m_timerSettingVideo = 0;

int TimerHandlerCenter(timer_t timerId){
	LOGI("[%s] timerId:%x",__FUNCTION__,timerId);
	int iCurOSDContent = pLocalParam->m_nCurOSDContent;
	switch((s64)timerId)
	{   
	    case OSD_TIMER_DROP_DOWN_DISPLAY:
	    {
		   LOGD("timer subtitle timeout");
		   //KillTimer(NULL,m_nTimerSubTitle);
		  // m_nTimerSubTitle = 0;
		   if(IsSubTitleOSD(iCurOSDContent))
			 ShowHideOSD(iCurOSDContent,false);
	    }
	    break;
	   case OSD_TIMER_SETTING_VIDEO:
	   {
		   LOGD("\nosd get timer set video");
		   TimerSetVideo();
	   }
	   break;
	   case OSD_TIMER_OSD_PAGE_DISPLAY:
	   {
		   LOGD("timer osd page timeout iCurOSDContent:%x",iCurOSDContent);
		   //KillTimer(NULL,m_nTimerOSDPage);
		   //m_nTimerOSDPage = 0;
		   if (!IsSubTitleOSD(iCurOSDContent))
		   {
		       if(iCurOSDContent == OSD_BACK_Color)
		       {
		           Get_PageChangeMessage(PAGE_BACK_VIDEO_T123COLORSET_PAGE,PAGE_BACK_VIDEO,1);
		           osdToModule_NotifyBackCar_ShowSetColorButton(0);
		       }
		       else
		       {
    			   ShowHideOSD(iCurOSDContent,false);
    			   BackToBkGndPage();
			   }
		   }
	   }
	   break;
	   case OSD_TIMER_DROP_DOWN_SWITCH:
	   {
	        pLocalParam->bDropDownOSD_Switch = true;
	   }
	   break;
	   
	   case OSD_TIMER_COME_IN_BACK_CAR:
	   		ShowHideOSD(OSD_BACK,true);
		break;
	}
	
	return 0;
}

void initTimerCenter(timer_handler_function func){
	LOGI("pFunc:%x", func);
	u8 buf[] = {0x10,0x00,0x00,0x00,0x00};
    
    buf[1] = ((u64)func >> 24) & 0xFF;
    buf[2] = ((u64)func >> 16) & 0xFF;
    buf[3] = ((u64)func >> 8) & 0xFF;
    buf[4] = (u64)func & 0xFF;

    
    makeAndSendMessageToModule(MODULE_ID_OSD,MODULE_ID_TIMER,buf,5);
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
    
    makeAndSendMessageToModule(MODULE_ID_OSD,MODULE_ID_TIMER,buf,10);

    
    return 0;
}

int DeleteTimer(int timerId){
	u8 buf[5];
	
	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    makeAndSendMessageToModule(MODULE_ID_OSD,MODULE_ID_TIMER,buf,5);
    
    return 0;
}



