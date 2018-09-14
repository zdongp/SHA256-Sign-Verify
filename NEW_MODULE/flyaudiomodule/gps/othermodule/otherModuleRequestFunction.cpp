#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"


void gpsToModule_NotifySystem_jumpPage(u16 pageId){
	u8 buf[] = {0x82, 0x00, 0x00};
	memcpy(&buf[1], &pageId, 2);
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_SYSTEM, buf, 3);
}
void gpsToModule_NotifyDVDModule_jumpPage()
{
    u8 buf[] = {0x79, 0x00};
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_DVD, buf, 2);
}
void gpsToModule_NotifyTVModule_jumpPage()
{
   u8 buf[] = {0x79, 0x00};
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_TV, buf, 2);
}
void gpsToModule_NotifyAuxModule_jumpPage()
{
   	u8 buf[] = {0x79, 0x00};
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_AUX, buf, 2);
}
void gpsToModule_NotifySystem_jumpPrePage(void){
	u8 buf[] = {0x83, 0x00};
	
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_SYSTEM, buf, 2);
}

void gpsToModule_NotifyAuxscreen_NaviInformation(u8 *param,int len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x00;
	memcpy(&pBuf[1],param,len);
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_AUXSCREEN,pBuf,len+1);

}

void gpsToModule_NotifyOSD_aboutSwitchingLanguage(u8 param1,u8 param2)
{
	u8 pBuf[] = {0x00,0x00,0x00};
	pBuf[1]=param1;
	pBuf[2]=param2;
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_OSD,pBuf,sizeof(pBuf));
}

void gpsToModule_NotifyBT_aboutPTT(u8 *param,u8 len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x00;
	memcpy(&pBuf[1],param,len);
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_BT,pBuf,len+1);
}

void gpsToModule_NotifyBT_aboutSwitchingLanguage(u8 param1,u8 param2)
{
	u8 pBuf[] = {0x01,0x00,0x00};
	pBuf[1]=param1;
	pBuf[2]=param2;
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_BT,pBuf,sizeof(pBuf));
}

void gpsToModule_NotifyAuxscreen_GaodeMap_Information(u8 *param,int len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x01;
	memcpy(&pBuf[1],param,len);
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_AUXSCREEN,pBuf,len+1);
}

void gpsToModule_NotifyExtcar_aboutSwitchingLanguage(u8 param)
{
	u8 pBuf[] = {0x00,0x00};
	pBuf[1] = param;
	makeAndSendMessageToModule(MODULE_ID_GPS, MODULE_ID_EXTCAR,pBuf,sizeof(pBuf));
}