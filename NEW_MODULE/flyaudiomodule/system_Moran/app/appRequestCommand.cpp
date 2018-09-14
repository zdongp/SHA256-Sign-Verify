#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "messageQueue.h"
#include "appRequestCommand.h"

//#include <cutils/properties.h>

extern "C"
{
#include "unicodestring.h"
};

extern "C"{
#include "flyopen.h"
};

extern void sendMessageToApp(appMessage_t *pAppMsg);


static appMessage_t appMessage;

void makeAndSendMessageToUI(u32 ctrlId, u8 ctrlType, u8 *param, int len){
	appMessage_t *pAppMessage;
	u8 *messageBuffer;

	pAppMessage = (appMessage_t *)&appMessage;
	messageBuffer = pAppMessage->messagebuf;

	memset(pAppMessage, 0x00, sizeof(appMessage_t));

	messageBuffer[0] = 0xFF;
	messageBuffer[1] = 0x55;
	messageBuffer[2] = (u8)(len + 6);
	messageBuffer[3] = (u8)((ctrlId >> 24) & 0xFF);
	messageBuffer[4] = (u8)((ctrlId >> 16) & 0xFF);
	messageBuffer[5] = (u8)((ctrlId >> 8) & 0xFF);
	messageBuffer[6] = (u8)(ctrlId & 0xFF);
	messageBuffer[7] = ctrlType;
	memcpy(&messageBuffer[8], param, len);

	pAppMessage->messageLen = (u8)(len + 9);

	sendMessageToApp(pAppMessage);
}

/******************************************************************************/

void setDigitalData(u32 ctrlId, int enable){
	u8 param = 0;
	if(enable){
		param = 1;
	}

	makeAndSendMessageToUI(ctrlId, UI_CONTROL_TYPE_DIGITAL, &param, 1);
}

void setAnalogData(u32 ctrlId, int analog){
	u8 param[4] = { 0x00, 0x00, 0x00, 0x00};

	param[0] = (u8)((analog >> 24) & 0xFF);
	param[1] = (u8)((analog >> 16) & 0xFF);
	param[2] = (u8)((analog >> 8) & 0xFF);
	param[3] = (u8)(analog & 0xFF);
	makeAndSendMessageToUI(ctrlId, UI_CONTROL_TYPE_ANALOG, param, 4);
}

void setSerialData(u32 ctrlId, u8 *buffer, int len){
	u8 *buf = buffer;
	makeAndSendMessageToUI(ctrlId, UI_CONTROL_TYPE_SERIAL, buf, len);
}

void setCommand(u32 ctrlId, u8 *param, int paramLen){
	u8 *buf = param;

	makeAndSendMessageToUI(ctrlId, UI_CONTROL_TYPE_PARAMSET, buf, paramLen);
}

void setAnsiSerialData(u32 id, u8 *p, u32 len)
{
	u32 dwAnsiBufLen = strlen((char*)p);
	u8 *pUnicodeBuf = (u8*)malloc(dwAnsiBufLen * 2 + 2);
	memset(pUnicodeBuf, 0, dwAnsiBufLen * 2 + 2);
	u32 dwUnicodeBufLen = ansi_str_to_unicode16(p, (unsigned short*)pUnicodeBuf);
	setSerialData(id, pUnicodeBuf, dwUnicodeBufLen * 2);
	free(pUnicodeBuf);
}

/******************************************************************************/
void jumpPage(u16 pageId){
		return;
	LOGI("Final JumpToPage:0x%04X",pageId);
	
	if(pLocalParam->fd<0){
		LOGD("pLocalParam->fd<0");
		return;
	}

	if(c_lock(pLocalParam->fd)<0)
		LOGD("error: %s with errno: %d\n",strerror(errno),errno);

	//char temp[92];
	//do
	//{
	//	property_get("cn.fly.tempLock", temp, "1");
	//}
	//while(temp[0] == '0');
	//property_set("cn.fly.tempLock", "0");

	c_write_dev(pLocalParam->fd,(short)pageId);

	if(c_unlock(pLocalParam->fd)<0)
		LOGD("error: %s with errno: %d\n",strerror(errno),errno);

	if(pageId == 0x0f)
	{
		usleep(600000);
	}
}

void setVisible(u32 ctrlId, int visible){
	u8 param[2] = { 0x00, 0x00};

	if(visible){
		param[1] = 0x01;
	}

	setCommand(ctrlId, param, 2);
}

void setControllable(u32 ctrlId, int controllable){
	u8 param[2] = { 0x10, 0x00};
	if(controllable){
		param[1] = 0x01;
	}
	setCommand(ctrlId, param, 2);
}

void setGroupNumber(u32 ctrlId, u8 groupIndex){		// ÉèÖÃ¶ÔÏóÏÔÊŸµÚŒž×éÍŒÆ¬ÐÅÏ¢
	u8 param[2] = {0x20, 0x00};
	param[1] = groupIndex;
	setCommand(ctrlId, param, 2);
}

void setProgressRange(u32 ctrlId, int range){	// setValues(); ÉèÖÃ¹ö¶¯ÌõµÄ×îŽóÖµ
	u8 param[5] = {0x60,0x00,0x00,0x00,0x00};
	param[1] = (u8)(range >> 24) & 0xff;
	param[2] = (u8)(range >> 16) & 0xff;
	param[3] = (u8)(range >> 8) & 0xff;
	param[4] = (u8)(range >> 0) & 0xff;
	setCommand(ctrlId, param, 5);
}

void setExProgressRange(u32 ctrlId, int xRange, int yRange){
	u8 param[9] = {0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	param[1] = (u8)(xRange >> 24) & 0xff;
	param[2] = (u8)(xRange >> 16) & 0xff;
	param[3] = (u8)(xRange >>  8) & 0xff;
	param[4] = (u8)(xRange >>  0) & 0xff;

	param[5] = (u8)(yRange >> 24) & 0xff;
	param[6] = (u8)(yRange >> 16) & 0xff;
	param[7] = (u8)(yRange >>  8) & 0xff;
	param[8] = (u8)(yRange >>  0) & 0xff;

	setCommand(ctrlId, param, 9);
}

void setExProgressPos(u32 ctrlId, int xPos, int yPos){
	u8 param[9] = {0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	param[1] = (u8)(xPos >> 24) & 0xff;
	param[2] = (u8)(xPos >> 16) & 0xff;
	param[3] = (u8)(xPos >>  8) & 0xff;
	param[4] = (u8)(xPos >>  0) & 0xff;

	param[5] = (u8)(yPos >> 24) & 0xff;
	param[6] = (u8)(yPos >> 16) & 0xff;
	param[7] = (u8)(yPos >>  8) & 0xff;
	param[8] = (u8)(yPos >>  0) & 0xff;

	setCommand(ctrlId, param, 9);
}

void setExProgressSinglePos(u32 ctrlId, u8 direct, int pos){
	u8 param[6] = {0x72, direct, 0x00,  0x00, 0x00, 0x00};

	param[2] = (u8)(pos >> 24) & 0xff;
	param[3] = (u8)(pos >> 16) & 0xff;
	param[4] = (u8)(pos >>  8) & 0xff;
	param[5] = (u8)(pos >>  0) & 0xff;

	setCommand(ctrlId, param, 6);
}


void setStringText(u32 ctrlId, u32 stringId){
	u8 param[5] = {0xC0, 0x00, 0x00, 0x00,0x00};

	param[1] = (u8)(stringId >> 24) & 0xff;
	param[2] = (u8)(stringId >> 16) & 0xff;
	param[3] = (u8)(stringId >>  8) & 0xff;
	param[4] = (u8)(stringId >>  0) & 0xff;
	LOGD("SYSTEM:setStringText~~~param:%x,%x,%x,%x,%x",param[0],param[1],param[2],param[3],param[4]);
	setCommand(ctrlId, param, 5);
}

void setOsdController(u8 osdType, u8 len, u8* osdParam){
	u8 *param;

	param = (u8*)malloc(sizeof(u8)*(len+3));
	if(param == NULL){
		return;
	}

	param[0] = 0x02;
	param[1] = osdType;
	param[2] = len;
	memcpy(&param[3], osdParam, len);

	setCommand(0x00000000, param, len+3);
}

void setOsdHidden(void){
	unsigned char param;
	setOsdController(0x00, 0, &param);
}

void setOsdVolume(unsigned char vol){
	unsigned char volume = vol;
	setOsdController(0x01, 1, &volume);
}

void setOsdInfoControl(u8 *param, u8 len){
	setCommand(0x00000000, param, len);
}

void setAndroidSTDKey(u8 keyval){
	u8 param[] = {0x03, keyval};

	setCommand(0x00000000, param, 2);
}

void setPanelKeyToAndroid(u8 panel_key){
	u8 param[] = {0x04, panel_key};

	setCommand(0x00000000, param, 2);
}

void setShowDebugInfo(u8 *buffer, u8 len){
	u8 param[len+1];

	param[0] = 0xF0;
	memcpy(&param[1], buffer, len);

	setCommand(0x00000000, param, len+1);
}
void setShowStandbyOSD(u8 panel_key)
{
    u8 param[] = {0x90, panel_key};

	setCommand(0x00000000, param, 2);
}
void setShowCloseScreenOSD(u8 panel_key)
{
    u8 param[] = {0x91, panel_key};

	setCommand(0x00000000, param, 2);
}

void setScreenBrightnessCtrl(unsigned char brightness){
	u8 param[] = {0xF2, 0x00};

	param[1] = brightness;
	setCommand(0x00000000, param, 2);
}

void setUpdateUI(unsigned char update){
	u8 param[] = { 0xFE, 0x00};

	if(update){
		param[1] = 0x01;
	}

	setCommand(0x00000000, param, 2);
}


void System_NotifyApp12_24()
{
   u8 buf[]={0x82,0x03};
   setCommand(0x00000000,buf,2);
}

void System_ReturnAppStandyState(bool bstandby)
{
   u8 buf[]={0x04,0xf8};
   	if(!bstandby)
		buf[1] = 0xf9;
   setCommand(0x00000000,buf,2);
}


void System_NotifyApp_HourInc()
{
   u8 buf[]={0x82,0x04};
   setCommand(0x00000000,buf,2);
}
void System_NotifyApp_HourDec()
{
   u8 buf[]={0x82,0x05};
   setCommand(0x00000000,buf,2);
}
void System_NotifyApp_MutInc()
{
   u8 buf[]={0x82,0x06};
   setCommand(0x00000000,buf,2);
}
void System_NotifyApp_MutDec()
{
   u8 buf[]={0x82,0x07};
   setCommand(0x00000000,buf,2);
}

void Handle_NOBarCode(void)
{
   u8 buff[]={0x02,0x81,0x00,4};
   setCommand(0x00000000,buff,4);
}

void setOneBarcode(u8 *buffer, int len)
{
	u8 buf[len+1];

	buf[0] = 0x81;
	memcpy(&buf[1], buffer, len);

	setCommand(0x00000000, buf, len+1);
}
void System_notifyApp_battery_state(u8 u8_Param)
{
   u8 buf[]={0x71,u8_Param};
   setCommand(0x00000000,buf,2);
}

void System_notifyApp_AUTO_SOUND_ON(u8 u8_Param)
{
	LOGD("u8_Param:%x",u8_Param);
	u8 buf[]={0xF7,u8_Param};
    setCommand(0x00000000,buf,2);
}

void System_notifyApp_PingLoop(u8 u8_Param)
{
	LOGD("System_notifyApp_PingLoop :%x",u8_Param);
	u8 buf[] = {0x3e, u8_Param};
	setCommand(0x00000000, buf, 2);
}

void System_notifyApp_BrakeState(u8 u8_Param)
{
	LOGD("System_notifyApp_BrakeState :%d",u8_Param);
	u8 buf[] = {0x46, u8_Param};
	setCommand(0x00000000, buf, 2);
}

void System_notifyApp_DisplayBrakecarPromtBox(u8 u8_Param)
{
	LOGD("[%s] u8_Param:%d",__FUNCTION__,u8_Param);
	u8 buf[] = {0x47, u8_Param};
	setCommand(0x00000000, buf, 2);
}

void System_notifyApp_OtaJumpPage(u8 u8_Param)
{
	u8 buf[] = {0x52, u8_Param};
	setCommand(0x00000000, buf, 2);
}

void System_notifyApp_cvbsOrUsbSwitch(u8 u8_Param)
{
	u8 buf[] = {0xa2, u8_Param};
	setCommand(0x00000000, buf, 2);
}

void System_notifyApp_EyeProtectionModeSwitch(u8 p)
{
	u8 buf[] = {0xa3, p};
	setCommand(0x00000000, buf, 2);
}

void systemToApp_getTimeFormat(void)
{
	u8 param[2] = {0x82,0xFF};
	setCommand(0x00000000, param, 2);
}

void System_notifyApp_DesktopNavigationMapInformationsSyncSwitchState(u8 u8_Param)
{
	u8 buf[3] = {0xa5, 0x01,u8_Param};
	setCommand(0x00000000, buf, sizeof(buf));
}

void System_notifyApp_ChoiceNavigationMapInformations(u8 *PackgN,u8 PackgN_Len,u8 *classN,u8 classN_Len)
{
	u8 buf[280];
	memset(buf,0,sizeof(buf));

	buf[0] = 0xa5;
	buf[1] = 0x02;

	u8 *pUnicodeBuf = (u8*)malloc((PackgN_Len)*2+2);
	memset(pUnicodeBuf, 0, (PackgN_Len)*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(PackgN, (unicode16_t*)pUnicodeBuf);
	buf[2] = nUnicodeBufLen*2;
	memcpy(&buf[3], pUnicodeBuf, nUnicodeBufLen*2);

    u8 *pUnicodeBuf1 = (u8*)malloc((classN_Len)*2+2);
	memset(pUnicodeBuf1, 0, (classN_Len)*2+2);
	int nUnicodeBufLen1 = ansi_str_to_unicode16(classN, (unicode16_t*)pUnicodeBuf1);
	u8 nT = nUnicodeBufLen1*2;
	memcpy(buf + nUnicodeBufLen*2 + 3, &nT, 1);
	memcpy(buf + nUnicodeBufLen*2 + 3 + 1, classN, nUnicodeBufLen1*2);
	
	free(pUnicodeBuf);
	free(pUnicodeBuf1);
	
	setCommand(0x00000000, buf,nUnicodeBufLen*2+nUnicodeBufLen1*2+4);
}

