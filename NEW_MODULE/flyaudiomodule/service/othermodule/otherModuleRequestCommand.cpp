#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "messageQueue.h"
#include "otherModuleRequestCommand.h"

extern void sendMessageToModule(moduleMessage_t *pModuleMsg);
extern void sendMessageToBroadcast(unsigned char *buffer, int len);


moduleMessage_t moduleMessage;

void makeAndSendMessageToModule(unsigned char sendModuleId, unsigned char arrivedModuleId, unsigned char *buffer, int len){
	unsigned char *messageBuffer;
	moduleMessage_t *pModuleMessage;
	
	pModuleMessage = (moduleMessage_t *)&moduleMessage;
	
	memset(pModuleMessage, 0x00, sizeof(moduleMessage_t));
	
	messageBuffer = pModuleMessage->messagebuf;
	pModuleMessage->sendModuleID = sendModuleId;
	pModuleMessage->arrivedModuleID = arrivedModuleId;
		
	memcpy(messageBuffer, buffer, len);
	
	pModuleMessage->messageLen = len;
	
	sendMessageToModule(pModuleMessage);
}


void makeAndSendMessageToBroadcast(unsigned char *buffer, int len)
{
	sendMessageToBroadcast(buffer, len);
}

