#include "BtHal.h"
#include "BtApp.h" 
#include "BtParam.h"
#include "BtAdapter.h"

CBtAdapter::CBtAdapter(void)
{
}
CBtAdapter::~CBtAdapter(void)
{
}
void CBtAdapter::init(CBtHal *p1,CBtApp *p2,CBtParam *p3,CBtModule *p4)
{
	m_pBtHal = p1;
	m_pBtApp = p2;
	m_pBtParam = p3;
	m_pBtModule = p4;
}

void CBtAdapter::btInitCommand()
{
	printf("[BT] Init\n");
	u8 buf[3] = {0x01,0x01,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtversion()
{
	printf("[BT] requestBtversion\n");
	u8 buf[3] = {0x01,0x02,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtTurnONorOFF(u8 p)
{
	printf("[BT] requestBtTurnONorOFF\n");
	u8 buf[3] = {0x01,0x03,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtCanbeDetected()
{
	u8 buf[3] = {0x02,0x01,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtAddr()
{
	u8 buf[3] = {0x02,0x02,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtName()
{
	u8 buf[3] = {0x02,0x03,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::setBtAutomateConnect(u8 p)
{
	u8 buf[3] = {0x02,0x04,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtSearchDevice(u8 p)
{
	u8 buf[3] = {0x02,0x05,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::requestBtAutoConnectStatus()
{
	u8 buf[3] = {0x02,0x06,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::setBtCanbeDetected(u8 p)
{
	u8 buf[3] = {0x02,0x07,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::setDeviceBtName(u8 *buf,u8 len)
{
	//u8 nameLen = FLY_BT_DEVICE_NAME_MAX_LEN +2;
	u8 nameBuf[FLY_BT_DEVICE_NAME_MAX_LEN +2] = {0};
	nameBuf[0] = 0x02;
	nameBuf[1] = 0x08;
	memcpy(nameBuf+2,buf,len);
	m_pBtHal->setToHalBtMsg((char *)nameBuf, len+2);
}

void CBtAdapter::setBtPincode(u8 *p,int len)
{
	u8 buf[6] = {0};
	buf[0] = 0x02;
	buf[1] = 0x09;
	memcpy(buf+2,p,4);
	m_pBtHal->setToHalBtMsg((char *)buf, 6);
}

void CBtAdapter::requestBtPairRecord()
{
	u8 buf[3] = {0x03,0x01,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtPairDevice(u8 *p,int len)
{
	//int tempLen = len + 2;
	u8 buf[256] = {0};
	buf[0] = 0x03;
	buf[1] = 0x02;
	memcpy(&buf[2],p,len);
	m_pBtHal->setToHalBtMsg((char *)buf, len+2);
}

void CBtAdapter::setBtPairConfirm(u8 p)
{
	u8 buf[3] = {0x03,0x03,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::setBtPairMode(u8 p)
{
	u8 buf[3] = {0x03,0x04,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::deleteAllPairRecord()
{
	u8 buf[3] = {0x03,0x05,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::deleteAPairRecord(u8 *p,int len)
{
	//int tempLen = len + 2;
	u8 buf[256] = {0};
	buf[0] = 0x03;
	buf[1] = 0x06;
	memcpy(&buf[2],p,len);
	m_pBtHal->setToHalBtMsg((char *)buf, len +2);
}

void CBtAdapter::setBtCancelPair(u8 *p,int len)
{
	//int tempLen = len + 2;
	u8 buf[256] = {0};
	buf[0] = 0x03;
	buf[1] = 0x07;
	memcpy(&buf[2],p,len);
	m_pBtHal->setToHalBtMsg((char *)buf, len+2);
}

void CBtAdapter::btInitiativeConnectDevice(u8 *p,int len)
{
	//int tempLen = len + 2;
	u8 buf[256] = {0};
	buf[0] = 0x04;
	buf[1] = 0x01;
	memcpy(&buf[2],p,len);
	m_pBtHal->setToHalBtMsg((char *)buf, len+2);	
}

void CBtAdapter::btInitiativeDisconnection(u8 *p,int len)
{
	//int tempLen = len +2;
	u8 buf[256] = {0};
	buf[0] = 0x04;
	buf[1] = 0x02;
	memcpy(&buf[2],p,len);
	m_pBtHal->setToHalBtMsg((char *)buf, len +2);
}

void CBtAdapter::btCallOperation_HandUp(void)
{
	u8 buf[3] = {0x05,0x01,0x00};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::btCallOperation_Answer(void)
{
	u8 buf[3] = {0x05,0x01,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::btCallOperation_CallOut(u8 *p,int len)
{
	u8 buf[131] = {0};
	buf[0] = 0x05;
	buf[1] = 0x01;
	buf[2] = 0x02;
	memcpy(&buf[3],p,len);
	m_pBtHal->setToHalBtMsg((char *)buf, len+3);
}
void CBtAdapter::btCallOperation_Save(void)
{
	u8 buf[3] = {0x05,0x01,0x03};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::btCallOperation_Redial(void)
{
	u8 buf[3] = {0x05,0x01,0x04};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::btHfpCmdSendDtmf(u8 p)
{
	u8 buf[4] = {0x05,0x01,0x05,0x00};
	buf[3] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 4);
}

void CBtAdapter::btAnswerformCarOrPhone(u8 p)
{
	u8 buf[3] = {0x05,0x02,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::setBtMicMute(u8 p)
{
	u8 buf[3] = {0x05,0x03,0x00};
	buf[2] =p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::setBtVolume(u8 p)
{
	u8 buf[3] = {0x05,0x05,0x00};
	buf[2] =p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::setBtMicVolume(u8 p)
{
	u8 buf[3] = {0x05,0x06,0x00};
	buf[2] =p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::btAvrcpControl(u8 p)
{
	u8 buf[3] = {0x06,0x01,0x00};
	buf[2] =p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::btCyclePlayControl(u8 p)
{
	u8 buf[3] = {0x06,0x02,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::btRandomPlay(u8 p)
{
	u8 buf[3] = {0x06,0x03,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtMusicInfo()
{
	u8 buf[3] = {0x06,0x04,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}

void CBtAdapter::requestBtPlayStatus()
{
	u8 buf[3] = {0x06,0x05,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::requestBtPlayModeStatus()
{
	u8 buf[3] = {0x06,0x06,0x01};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::A2dpAudioOutputCtrlSwitch(u8 p)
{
	u8 buf[] = {0x06,0x07,p};
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::requestBtPhoneBook(u8 p)
{
	u8 buf[3] = {0x07,0x01,0x00};
	buf[2] = p;
	m_pBtHal->setToHalBtMsg((char *)buf, 3);
}
void CBtAdapter::debugPrintf(u8 *buf,int len)
{
	int i = 0;
	for(i = 0;i < len; i++)
	{
		LOGD("0x%x ",buf[i]);
	}
	printf("\n");
}


int CBtAdapter::findCharIndex(unsigned char *p, int len, unsigned char d)
{
	int i = 0;

	for (i = 0; i < len; i++)
	{
		if (p[i] == d)
		{
			return i;
		}
	}

	return -1;
		
}

int CBtAdapter::Inside_FindIndexFromStr(const u8 *pSrc, int nSrcLen, u8 cLetter, int nStart){
	int i;
	for (i = nStart; i < nSrcLen; i++){
		if (cLetter == pSrc[i]){
			return i;
		}
	}
	return -1;
}

