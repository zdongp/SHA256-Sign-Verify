#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "messageQueue.h"
#include "param.h"

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

void radioToModule_JumpToOtherModule()
{
	u8 buf[] = {0x81, MODULE_ID_RADIO};
    makeAndSendMessageToModule(MODULE_ID_RADIO, MODULE_ID_SYSTEM,buf,2);
}

//��ָ��ҳ
void radioToModule_NotifySystem_JumpPage(u16 nPageId)
{
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&nPageId,2);
     makeAndSendMessageToModule(MODULE_ID_RADIO,MODULE_ID_SYSTEM,buf,3);
}

//��ǰһҳ
void radioToModule_NotifySystem_JumpPrePage()
{
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_RADIO,MODULE_ID_SYSTEM,buf,2);
}

void radioToModule_AUXScreen_RadioFrequency(u16 wFreq)
{
	u8 buf[3];
	buf[0] = 0x31;
	memcpy(buf + 1, &wFreq, 2);
	makeAndSendMessageToModule(MODULE_ID_RADIO, MODULE_ID_AUXSCREEN, buf, 3);
}

void radioToModule_AUXScreen_RadioChannel(u8 cChannel)
{
	u8 buf[2];
	buf[0] = 0x30;
	buf[1] = cChannel;
 	makeAndSendMessageToModule(MODULE_ID_RADIO, MODULE_ID_AUXSCREEN, buf, 2);
}

void radioToModule_AUXScreen_RadioRecord(u8 cRecord)
{
	LOGD("radioToModule_AUXScreen_RadioRecord:cRecord=%d",cRecord);
	u8 buf[2];
	buf[0] = 0x32;
	buf[1] = cRecord;
	makeAndSendMessageToModule(MODULE_ID_RADIO, MODULE_ID_AUXSCREEN, buf, 2);

}

void radioToModule_AUXScreen_RadioStationName(u8 *pBuf, int nLen)
{
	int nBufLen = nLen + 1;
	u8* pBufName = (u8*)malloc(nBufLen);

	pBufName[0] = 0x33;
	memcpy(pBufName + 1, pBuf, nLen);

	makeAndSendMessageToModule(MODULE_ID_RADIO, MODULE_ID_AUXSCREEN, pBufName, nBufLen);
	free(pBufName);
	pBufName = NULL;
}

void radioToModule_NotifyOsd_ShowTitle()
{
	u8 buf[] = {0x01, 0x17};
	makeAndSendMessageToModule(MODULE_ID_RADIO,MODULE_ID_OSD,buf,2);
}
void radioToModule_NotifyOsd_ShowFrequecy(unsigned char type, unsigned short freq,u8 unit){
	u8 buf[] = {0x17, 0x00, 0x00, 0x00,unit};

	buf[1] = type;
	buf[2] = freq & 0x00FF;
	buf[3] = (freq & 0xFF00)>>8;
    buf[4] = unit;
	makeAndSendMessageToModule(MODULE_ID_RADIO,MODULE_ID_OSD,buf,5);
}


void radioToModule_NotifyAutoMate_State(char resCmd,u8 *param,u8 len){
    if(len == 0)return;
	int nLen = (int)(len+2);
	u8 *pBuff = (u8*)malloc(nLen);
	pBuff[0]=0x00;
	pBuff[1]=resCmd;
	memcpy(pBuff+2,param,len);
	makeAndSendMessageToModule(MODULE_ID_RADIO, MODULE_ID_AUTOMATE, pBuff, nLen);
	free(pBuff);
	pBuff = NULL;
}


void radioToModule_system_RadioArea(u8 code)
{
	u8 buf[2];
	buf[0] = 0x01;
	buf[1] = code;
 	makeAndSendMessageToModule(MODULE_ID_RADIO, MODULE_ID_SYSTEM, buf, 2);
}

void radioToModule_AuxscreenFreRecordList(u8 nChannel,u8 list,u8 allNum,u16 *recordeList)
{
	if(allNum == 0)
		return;
	u8 buf[500] = {0};
	buf[0] = 0x37;
	buf[1] = nChannel;
	buf[2] = list;
	int j = 0;
	for(int i = 0;i < allNum;i++)
	{
		if(recordeList[i] != 0)
		{
			int k = 0;
			k = 4 + (2*j);
			memcpy(buf + k,&recordeList[i],2);
			j ++;
		}
	}
	buf[3] = j;
	int len = 2*buf[3] +4;
	makeAndSendMessageToModule(MODULE_ID_RADIO, MODULE_ID_AUXSCREEN, buf,len);
}

void initAuxscreenFreRecordList()
{
	for(int i = 0;i < CHANNEL_NUM ;i++)
	{
		u8 Channel = i;
		u8 allNum = (pLocalParam->stszRadioChannelRecord[Channel].totalPages - 1)*CHANNEL_RECORD_NUM;
		radioToModule_AuxscreenFreRecordList(Channel,0x00,allNum,pLocalParam->stszRadioChannelRecord[Channel].wRadioFreqRecord);
	}
}
