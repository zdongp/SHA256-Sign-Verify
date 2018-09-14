/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "FlyHal.h"

extern void sendMessageToHal(halMessage_t *pHalMsg);

CFlyHal::CFlyHal(void)
{
}

CFlyHal::~CFlyHal(void)
{
}

void CFlyHal::deInit(void)
{

}

void CFlyHal::analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len)
{
	LOGD("[%s]", __FUNCTION__);
}

void CFlyHal::analyseAgentMessage(moduleid_t id, u8 *p, u8 len)
{
	LOGD("[%s]", __FUNCTION__);
}

void CFlyHal::makeAndSendMessageToHal(moduleid_t halId, u8 *p, u32 len)
{
	//outPutLog(__FUNCTION__, "p", p, len);
	u32 sendLen = len + 4 + 1;
	halMessage_t *pHalMessage = NULL;

	pHalMessage = &m_stHalMessage;
	memset(pHalMessage, 0, sizeof(halMessage_t));

	pHalMessage->messagebuf[0] = 0xFF;
	pHalMessage->messagebuf[1] = 0x55;
	pHalMessage->messagebuf[2] = (u8)(len + 1 + 1);
	pHalMessage->messagebuf[3] = (u8)halId;
	memcpy(&pHalMessage->messagebuf[4], p, len);

	pHalMessage->halID = halId;
	pHalMessage->messageLen = (u8)sendLen;

	sendMessageToHal(pHalMessage);
}

