#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "messageQueue.h"
#include "appRequestCommand.h"

extern void sendMessageToApp(appMessage_t *pAppMsg);


static appMessage_t appMessage;

void makeAndSendMessageToUI(int controlId, u8 controlType, u8 *param, int len){
	appMessage_t *pAppMessage;
	u8 *messageBuffer;

	pAppMessage = (appMessage_t *)&appMessage;
	messageBuffer = pAppMessage->messagebuf;

	memset(pAppMessage, 0x00, sizeof(appMessage_t));

	messageBuffer[0] = 0xFF;
	messageBuffer[1] = 0x55;
	messageBuffer[2] = (u8)(len + 6);
	messageBuffer[3] = (u8)((controlId >> 24) & 0xFF);
	messageBuffer[4] = (u8)((controlId >> 16) & 0xFF);
	messageBuffer[5] = (u8)((controlId >> 8) & 0xFF);
	messageBuffer[6] = (u8)(controlId & 0xFF);
	messageBuffer[7] = controlType;
	memcpy(&messageBuffer[8], param, len);

	pAppMessage->messageLen = (u8)(len + 9);

	sendMessageToApp(pAppMessage);
}

void setDigitalData(int controlId, int enable){
	u8 param = 0;
	if(enable){
		param = 1;
	}

	makeAndSendMessageToUI(controlId, UI_CONTROL_TYPE_DIGITAL, &param, 1);
}

void setAnalogData(int controlId, int analog){
	u8 param[4] = { 0x00, 0x00, 0x00, 0x00};

	param[0] = (u8)((analog >> 24) & 0xFF);
	param[1] = (u8)((analog >> 16) & 0xFF);
	param[2] = (u8)((analog >> 8) & 0xFF);
	param[3] = (u8)(analog & 0xFF);

	makeAndSendMessageToUI(controlId, UI_CONTROL_TYPE_ANALOG, param, 4);
}
void setSerialData(int controlId, u8 *buffer, int len){
	u8 *buf = buffer;

	makeAndSendMessageToUI(controlId, UI_CONTROL_TYPE_SERIAL, buf, len);
}

void setCommand(int controlId, u8 *param, int paramLen){
	u8 *buf = param;

	makeAndSendMessageToUI(controlId, UI_CONTROL_TYPE_PARAMSET, buf, paramLen);
}




void setVisible(int controlId, int visible){
	u8 param[2] = { 0x00, 0x00};

	if(visible){
		param[1] = 0x01;
	}

	setCommand(controlId, param, 2);
}

void setControllable(int controlId, int controllable){
	u8 param[2] = { 0x10, 0x00};

	if(controllable){
		param[1] = 0x01;
	}

	setCommand(controlId, param, 2);
}

void setValues(int controlId, int values){
	u8 param[5] = {0x20,0x00,0x00,0x00,0x00};

	param[1] = (values >> 24) && 0xff;
	param[2] = (values >> 16) && 0xff;
	param[3] = (values >> 8) && 0xff;
	param[4] = (values >> 0) && 0xff;

	setCommand(controlId, param, 5);
}
