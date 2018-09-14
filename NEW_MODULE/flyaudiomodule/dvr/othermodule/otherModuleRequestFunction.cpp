
#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#include "param.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "moduleParamResponse.h"
#include "moduleID.h"
#include "halResponseFunction.h"
#include "timer_interface.h"
#include "halRequestFunction.h"

//��ָ��ҳ
void dvrToModule_NotifySystem_JumpPage(u16 nPageId){
	 //pLocalParam->m_wCurrentPage = nPageId;
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&nPageId,2);
     makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_SYSTEM,buf,3);
}
//��ǰһҳ
void dvrToModule_NotifySystem_JumpPrePage(void){
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_SYSTEM,buf,3);
}

void dvrToModule_NotifyAuxscreen_State(char state){
	unsigned char buff[] = {0x23, state};
	makeAndSendMessageToModule(MODULE_ID_AUXSCREEN, MODULE_ID_AUXSCREEN, buff, 2);
}

void dvrtodnv(void)
{
	u8 szMsg[2] = {0x01, 0x00};

	makeAndSendMessageToModule(MODULE_ID_DVR, MODULE_ID_DNV, szMsg, 2);
}

void dvrToModule_NotifyAutoMate_State(char resCmd,u8 *param,u8 len){
    if(len == 0)return;
	int nLen = (int)(len+2);
	u8 *pBuff = (u8*)malloc(nLen);
	pBuff[0]=0x00;
	pBuff[1]=resCmd;
	memcpy(pBuff+2,param,len);
	makeAndSendMessageToModule(MODULE_ID_DVR, MODULE_ID_AUTOMATE, pBuff, nLen);
	free(pBuff);
	pBuff = NULL;
}

void dvrToModule_NotifyOSD_aboutT123_VideoOSD_videoset_Button(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X53,0x00,0x03};
	buf[1]=swtich_button;
	buf[2]=button_status;
	LOGD("Module_dvr button info :0x53 button id=%x,status=%x",swtich_button,button_status);
	makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_OSD,buf,3);

}


void dvrToModule_NotifyOSD_aboutT123_VideoOSD_dvrMenu_Button(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X50,0x00,0x03};
	buf[1]=swtich_button;
	buf[2]=button_status;
	LOGD("Module_dvr button info :0x50 button id=%x,status=%x",swtich_button,button_status);
	makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_OSD,buf,3);

}

void dvrToModule_NotifyOSD_aboutT123_VideoOSD_recordPlay_Button(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X51,0x00,0x03};
	buf[1]=swtich_button;
	buf[2]=button_status;
	LOGD("Module_dvr button info :0x51 button id=%x,status=%x",swtich_button,button_status);

	makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_OSD,buf,3);

}

void dvrToModule_NotifyOSD_aboutT123_VideoOSD_timeset_Button(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X52,0x00,0x03};
	buf[1]=swtich_button;
	buf[2]=button_status;
	LOGD("Module_dvr button info :0x52 button id=%x,status=%x",swtich_button,button_status);
	makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_OSD,buf,3);

}

void dvrToModule_NotifyOSD_SetYMDaboutT123_VideoOSD(int nYMD)
{
	u8 buf[10] = {0x00};
	buf[0]=0x53;
	memcpy(&buf[1],&nYMD,3);
	makeAndSendMessageToModule(MODULE_ID_DVR,MODULE_ID_OSD,buf,4);
}

void setTimerSyncTimeToDVR(void)
{
	DeleteTimer(TIMER_ID_SYNC_TIME_TO_DVR);
	SetTimer(TIMER_CYCLE_SYNC_TIME_TO_DVR, 0, TIMER_ID_SYNC_TIME_TO_DVR);

	LOGD("[%s]", __FUNCTION__);
}

void killTimerSyncTimeToDVR(void)
{
	DeleteTimer(TIMER_ID_SYNC_TIME_TO_DVR);

	LOGD("[%s]", __FUNCTION__);
}

void syncTimeToDVR(void)
{
	LOGD("[%s]", __FUNCTION__);

	time_t now;
	struct tm *timenow;

	time(&now);
	timenow = localtime(&now);

	LOGD("[%s] %s", __FUNCTION__, asctime(timenow));

	int y = 0, month = 0, d = 0, h = 0, m = 0, s = 0, as = 0;

	y = timenow->tm_year + 1900;
	month = timenow->tm_mon + 1;
	d = timenow->tm_mday;

	h = timenow->tm_hour;
	m = timenow->tm_min;
	s = timenow->tm_sec;
		
	u8 yt = (y < 2013) ? 13 : (y - 2000);
	setToHalSyncTime(yt, month, d, h, m, s);
		
}

void dvrToModule_NotifySystem_BackCarProtocolState(u8 state)
{
	u8 buff[] = {0x00, state};
	makeAndSendMessageToModule(MODULE_ID_DVR, MODULE_ID_SYSTEM, buff, 2);
}


