#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "messageQueue.h"
#include "appRequestCommand.h"

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

void setUpdateUI(unsigned char update){
	u8 param[] = { 0xFE, 0x00};

	if(update){
		param[1] = 0x01;
	}

	setCommand(0x00000000, param, 2);
}

void setStringText(u32 ctrlId, u32 stringId){
	u8 param[5] = {0xC0, 0x00, 0x00, 0x00,0x00};

	param[1] = (u8)(stringId >> 24) & 0xff;
	param[2] = (u8)(stringId >> 16) & 0xff;
	param[3] = (u8)(stringId >>  8) & 0xff;
	param[4] = (u8)(stringId >>  0) & 0xff;

	setCommand(ctrlId, param, 5);
}


