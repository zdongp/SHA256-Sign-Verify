#include <stdlib.h>
#include <stdio.h>


#include"global.h"
#include "controlID.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"

void tpmsToModule_NotifySystem_JumpPage(u16 u16_PageID)
{
    u8 buf[] = {0x82,0x00,0x00};
    memcpy(&buf[1],&u16_PageID,2);
    makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_SYSTEM,buf,3);
}
void tpmsToModule_NotifySystem_JumpPrePage(void)
{
    u8 buf[] = {0x83,0x00};
    makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_SYSTEM,buf,2);
}
void tpmsToModule_NotifySystem_SwitchModule(u8 u8_ModuleID)
{
    u8 buf[] = {0x81,u8_ModuleID};
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_SYSTEM,buf,2);

}

void StartRing(u8 ringID)
{
	LOGD("==========TPMS=====StartRing=======================");
	unsigned char buf[] = {0x04,0x00};
	buf[1] = ringID;
	makeAndSendMessageToModule(MODULE_ID_TPMS,MODULE_ID_CENTER,buf,2);
}

void StopRing()
{
	LOGD("==========TPMS=====StopRing=======================");
	u8 buf[] = {0x05,0x00};
	makeAndSendMessageToModule(MODULE_ID_TPMS,MODULE_ID_CENTER,buf,2);

}

void tpmsToModule_NotifyOSDT123_ShowTitle(){
	u8 buf[]={0x01,0x16};
	makeAndSendMessageToModule(MODULE_ID_TPMS,MODULE_ID_OSD,buf,2);
}

void Set_TPMS_OSD_Control(u8 cType)
{
	LOGD("----------------Set_TPMS_OSD_Control-----------cType:%x", cType);
	//u8 buf[]={0x02,0x38,cType};
	u8 buf[]={0x16,0x00,0x00};
	u8 tire = 0;
	u8 status=0xff;
	switch(cType){
	case 0x10:
		tire=1;
		status=1;
		break;
	case 0x11:
		tire=2;
		status=1;
		break;
	case 0x12:
		tire=3;
		status=1;
		break;
	case 0x13:
		tire=4;
		status=1;
		break;
	case 0x20:
		tire=5;
		status=1;
		break;
	case 0x21:
		tire=6;
		status=1;
		break;
	case 0x22:
		tire=7;
		status=1;
		break;
	case 0x23:
		tire=8;
		status=1;
		break;
	case 0x30:
		tire=5;
		status=0;
		break;
	case 0x31:
		tire=6;
		status=0;
		break;
	case 0x32:
		tire=7;
		status=0;
		break;
	case 0x33:
		tire=8;
		status=0;
		break;
	}
	buf[1]=tire;
	buf[2]=status;
	makeAndSendMessageToModule(MODULE_ID_TPMS,MODULE_ID_OSD,buf,3);
}
