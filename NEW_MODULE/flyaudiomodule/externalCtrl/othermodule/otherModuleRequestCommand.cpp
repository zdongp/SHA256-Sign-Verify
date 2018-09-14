#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "messageQueue.h"
#include "otherModuleRequestCommand.h"

extern void sendMessageToModule(moduleMessage_t *pModuleMsg);


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

//跳到指定页
void externalCtrlToModule_NotifySystem_JumpPage(u16 nPageId)
{
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&nPageId,2);
     makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_SYSTEM,buf,3);
}

//跳到前一页
void externalCtrlToModule_NotifySystem_JumpPrePage()
{
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_SYSTEM,buf,2);
}

