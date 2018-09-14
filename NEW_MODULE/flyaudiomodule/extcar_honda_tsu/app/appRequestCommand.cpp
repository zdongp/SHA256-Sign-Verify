#include <stdio.h>
#include <stdlib.h>

#include "messageQueue.h"
#include "param.h"
#include "appRequestCommand.h"

extern "C"{
#include "unicodestring.h"
};

static appMessage_t appMessage;

extern void sendMessageToApp(appMessage_t *pAppMsg);

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

void setSerialData(u32 ctrlId, u8 *buffer, int len)
{
	u8 *buf = buffer;
	makeAndSendMessageToUI(ctrlId, UI_CONTROL_TYPE_SERIAL, buf, len);
}

void setAnsiSerialData(u32 ctrlId, u8 *buffer, int len)
{
	int nAnsiBufLen = strlen((char*)buffer);
	u8 *unicodeBuf = (u8*)malloc(nAnsiBufLen*2+2);
	memset(unicodeBuf, 0, nAnsiBufLen*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(buffer, (unicode16_t*)unicodeBuf);
	setSerialData(ctrlId,unicodeBuf,nUnicodeBufLen*2);
	free(unicodeBuf);
}

void setCommand(u32 ctrlId, u8 *param, int paramLen){
	u8 *buf = param;

	makeAndSendMessageToUI(ctrlId, UI_CONTROL_TYPE_PARAMSET, buf, paramLen);
}

/******************************************************************************/

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
	LOGD("ctrlId=0x%x,controllable=%d",ctrlId,controllable);
	setCommand(ctrlId, param, 2);
}

void setGroupNumber(u32 ctrlId, u8 groupIndex){
	u8 param[2] = {0x20, 0x00};

	param[1] = groupIndex;

	setCommand(ctrlId, param, 2);
}

void setProgressRange(u32 ctrlId, int range){
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

	setCommand(ctrlId, param, 5);
}

void setUpdateUI(u8 update){
	u8 param[] = { 0xFE, 0x00};

	if(update){
		param[1] = 0x01;
	}

	setCommand(0x00000000, param, 2);
}
/******************************************************************************/
void sendToExtcarHondaTsuFlyJniSdkService(u8 moduleId, u8 *p, u8 len)
{
	static u8 szMsg[256] = {0};
	szMsg[0] = moduleId;

	if(len > 256)
		len = 256;
	memcpy(szMsg + 1, p, len);
	setCommand(0x51FFFE, szMsg, len + 1);
}



