#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 


#include "global.h"
#include "appResponseFunction.h"
#include "timer_interface.h"
#include "pageID.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "halRequestFunction.h"
#include "param.h"
#include "moduleParamResponse.h"
#include "appRequestFunction.h"

int TimerHandlerCenter(timer_t timerId){
	
		switch((s64)timerId)
		{
				case DVR_OSD_TIMER_HIDDEN_DISPLAY:
				{
				}
				break;
				case TIMER_ID_SYNC_TIME_TO_DVR:
				{	
					static int nCyleSyncCount = 0;
					static int snPreSec = 0; 
					static int snSendTimes = SYNC_DVR_TIME_TIMES;
	
					if (pLocalParam->m_bSystemStartNeedSyncTimeToDNV)
						nCyleSyncCount++;
	
					time_t now;
					struct tm *timenow;
	
					time(&now);
					timenow = localtime(&now);
	
					//LOGD("[%s] %s", __FUNCTION__, asctime(timenow));
	
					int y = 0, month = 0, d = 0, h = 0, m = 0, s = 0, as = 0;
	
					y = timenow->tm_year + 1900;
					month = timenow->tm_mon + 1;
					d = timenow->tm_mday;
	
					h = timenow->tm_hour;
					m = timenow->tm_min;
					s = timenow->tm_sec;
	
					as = y * 3600 * 8 +  month * 3600 * 4 + d * 3600 * 2 + h * 3600 + m * 60 + s;
	
					//LOGD("[%s] y = %d month = %d d = %d h = %d m = %d s = %d", __FUNCTION__, y & 0xFF, month, d, h, m, s);
					// 1  min or other time sync one time
					if (pLocalParam->m_bSystemStartNeedSyncTimeToDNV && (nCyleSyncCount * TIMER_CYCLE_SYNC_TIME_TO_DVR / 1000 >= SYNC_DNV_TIME_CYCLE))
					{
						LOGD("[%s]	1  min or other time sync one time", __FUNCTION__);
	
						
				
						u8 yt = (y < 2013) ? 13 : (y - 2000);
						setToHalSyncTime(yt, month, d, h, m, s);
						snSendTimes -= 1;
	
						if (snSendTimes == 0)
						{
							snSendTimes = SYNC_DVR_TIME_TIMES;
							pLocalParam->m_bSystemStartNeedSyncTimeToDNV = false;
						}
	
						nCyleSyncCount = 0;
					}
					//time change too more
					if (abs(as - snPreSec) >= 2 * (TIMER_CYCLE_SYNC_TIME_TO_DVR / 1000))
					{
						LOGD("[%s] sec change more than normal, so sync time to dnv", __FUNCTION__);
	
						u8 yt = (y < 2013) ? 13 : (y - 2000);
						setToHalSyncTime(yt, month, d, h, m, s);
						//appToDvr_Menu_Button_UsbCamera_YMD(yt, month, d);
						//appToDvr_Menu_Button_UsbCamera_HMS(h, m, s);
					}
	
					snPreSec = as;
		
				}break;
				case DVR_USB_CAMERY_NO_SDCARD:
				{
					LOGD("pLocalParam->bCurIsUsbCameraIsSdCard:%d",pLocalParam->bCurIsUsbCameraIsSdCard);
					if(pLocalParam->bCurIsUsbCameraIsSdCard){
						dvr_NotifyApp_SdCard_State(0x00,0x01);
					}
				}
				break;
				case DVR_USB_CAMERY_NO_SURPORTS_DOUBLE_RECORDING:
				{
					LOGD("pLocalParam->bCurIsSurportUsbCameraIsSdCard:%d",pLocalParam->bCurIsSurportUsbCameraIsSdCard);
					if(pLocalParam->bCurIsSurportUsbCameraIsSdCard)
					{
						dvr_NotifyApp_SdCard_State(0x01,0x01);
					}
				}
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

    
    makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_TIMER,buf,5);
}

int SetTimer(int nElaspe_ms, int nMode, int timerId){
	if(timerId == DVR_OSD_TIMER_HIDDEN_DISPLAY)
	{
		nMode = 1;
	}
	
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
    
    makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_TIMER,buf,10);

    return 0;
}

int DeleteTimer(int timerId){
	
	u8 buf[5];
	
	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_TIMER,buf,5);
	//LOGD("DeleteTimer Success!");
    return 0;
}



