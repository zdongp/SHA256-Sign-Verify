#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "pageID.h"
#include "moduleParamRequest.h"

void ipodToModule_NotifySystem_jumpPage(u16 pageId){
	u8 buf[] = {0x82, 0x00, 0x00};
	
	memcpy(&buf[1], &pageId, 2);
	
	makeAndSendMessageToModule(MODULE_ID_IPOD, MODULE_ID_SYSTEM, buf, 3);
}

void ipodToModule_NotifySystem_jumpPrePage(void){
	u8 buf[] = {0x83, 0x00};
	
	makeAndSendMessageToModule(MODULE_ID_IPOD, MODULE_ID_SYSTEM, buf, 2);
}

void ipodToModule_NotifySystem_SwitchModule(){
	u8 buf[] = {0x81, MODULE_ID_IPOD};
    makeAndSendMessageToModule(MODULE_ID_IPOD, MODULE_ID_SYSTEM,buf,2);
}

void ipodToModule_NotifyOsd_DisplayOSDIpodInfo(u16 track,u16 trackSum){

	u16 curPage = 0;
	unsigned char curPageLen = 2;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);

	if (curPage == PAGE_IPOD || curPage == PAGE_IPOD_SEARCH)
		{
			return;
		}
	u8 buf[] = {0x02, 0x20, 0x00,0x00,0x00,0x00};

	buf[2] = (track >> 8) & 0xFF;
	buf[3] = track & 0xFF;
	buf[4] = (trackSum>> 8) & 0xFF;
	buf[5] = trackSum & 0xFF;
	
	makeAndSendMessageToModule(MODULE_ID_IPOD,MODULE_ID_OSD,buf,6);
}



/*
void centerToModule_NotifySystem_Hardware_JumpPrePage(void){
	u8 buf[] = {0x84, 0x00};
	
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_EnterThreePartyApp(void){
	u8 buf[] = {0x85, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_EnterHomePage(void){
	u8 buf[] = {0x86, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_EnterGpsPage(void){
	u8 buf[] =  {0x87, 0x00};
	
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_EnterNonHomePage(void){
	u8 buf[] = {0x88, 0x00};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_ReturnToPage(unsigned char *pageid,int len){
	u8 buf[len+1];
	buf[0] = 0x89;
	memcpy(&buf[1], pageid, len);
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, len+1);
}

void centerToModule_NotifySystem_DebugPanelType(unsigned char panelType){
	u8 buf[] = {0xF0, panelType};
	
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}

void centerToModule_NotifySystem_Brightness(unsigned char brightness){
	u8 buf[] = {0xF2, brightness};
		
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);

}

void centerToModule_NotifySystem_BrightnessBlackPageClick(void){
	u8 buf[] = {0x00, 0x01};

	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_SYSTEM, buf, 2);
}


void centerToModule_NotifyOSD_SetOSDHidden(void){
	u8 buf[] = {0x0F, 0x00};
	
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_OSD, buf, 2);
}




void centerToModule_NotifyAudiovideo_GpsSoundState(unsigned char state){
	u8 buf[] = {0x01, state};
	
	makeAndSendMessageToModule(MODULE_ID_CENTER, MODULE_ID_AUDIOVIDEO, buf, 2);
}
*/
