#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"


void osdToModule_NotifySystem_jumpPage(u16 pageId){
	u8 buf[] = {0x82, 0x00, 0x00};
	
	memcpy(&buf[1], &pageId, 2);
	
	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_SYSTEM, buf, 3);
}

void osdToModule_NotifySystem_jumpPrePage(void){
	u8 buf[] = {0x83, 0x00};
	
	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_SYSTEM, buf, 2);
}


void osdToModule_NotifyBackCar_ShowSetColorButton(u8 state){
	u8 buf[] = {0x00, state};
	
	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_BACK, buf, 2);
}

