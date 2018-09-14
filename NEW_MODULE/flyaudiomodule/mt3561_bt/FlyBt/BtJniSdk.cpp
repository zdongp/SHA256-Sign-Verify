#include "BtHal.h"
#include "BtApp.h" 
#include "BtParam.h"
#include "BtJniSdk.h"

#define MESSAGETYPE_STATUS			0x00
#define MESSAGETYPE_CONTROL		0x01
/*******************SDKprotocol***********************/
#define CMDTYPESTATUS 				0x00
#define CMDTYPECONTRL				0x01

#define BT_STATUS_INFO				0x01
#define BT_STATUS_SWITCH				0x00
#define BT_STATUS_CONNECT			0x01
#define BT_STATUS_PHONE_STATE		0x02


#define BT_PHONE_BOOK_INFO			0x02
#define BT_A2DP_SONG_INFO			0x03


CBtJniSdk::CBtJniSdk(void)
{
}
CBtJniSdk::~CBtJniSdk(void)
{
}
void CBtJniSdk::init(CBtHal *p1,CBtApp *p2,CBtParam *p3,CBtModule *p4)
{
	m_pBtHal = p1;
	m_pBtApp = p2;
	m_pBtParam = p3;
	m_pBtModule = p4;
}
void CBtJniSdk::getSdkToModuleMessage(u8 *p,int len)
{
	LOGD("[%s] MessageType:%x ---p[1]:%x",__FUNCTION__,p[0],p[1]);
	switch(p[0])
	{
		case MESSAGETYPE_STATUS:
			analysSdkToBtStatusMessage(p+1,len -1);
		break;
		case MESSAGETYPE_CONTROL:
			analysSdkToBtContrlMessage(p+1,len -1);
		break;
		default:break;
	}
}

void CBtJniSdk::analysSdkToBtStatusMessage(u8 *p,u8 len)
{
	switch(p[0])
	{
		case 0x00:
			{
				btSwitchStatusTag = true;
				sendToAppBtSwitchStatus(m_pBtParam->m_bIsPowerOn);
			}
			break;
		  case 0x01:
			  {
			  	btConnectStatusTag = true;
				sendToAppBtConnectStatus(m_pBtParam->m_eHfpConnectStatus);
			  }
			  break;
		  case 0x02:
			  {
				btPhoneStatusTag	 = true;
				sendToAppBtPhoneStatus((u8)m_pBtParam->m_ePhoneStatus);
			  }
			  break;
		  case 0x03:
			  {
				SendBookTag = true;
				if(m_pBtParam->m_listPhoneBook.size() != 0 && !m_pBtApp->m_pBtPhoneBookPages->getLoadPhoneBookStatus())
					sendToAppPhoneBookInfo();
				else 
					sendToAppPhoneBookLoadStatus(0x00);		
			}
			break;
		  default:break;
	}
}
  
void CBtJniSdk::analysSdkToBtContrlMessage(u8 *p,u8 len)
{
	switch(p[0])
		{
			case 0x01:
			{
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
			}
			break;
			case 0x02:
				m_pBtModule->GPS_aboutCareLand_PTT(&p[1],len -1);
			break;
			case 0x03:
			{
				if(p[1] == 0x00)
					m_pBtHal->setToHalBtPower(0x00);
				else if(p[1] == 0x01)
					m_pBtHal->setToHalBtPower(0x01);
			}
			break;
			case 0x04:
			{
				if(p[1] == 0x01)
					m_pBtApp->m_pA2DPpages->clickA2dpMainPageEntrance(MOUSE_STATUS_UP);
			}
			break;
			case 0x07:
			{
				if(p[1] == 0x01)
					m_pBtApp->m_pBtMainPage->clickHandup(MOUSE_STATUS_UP);
				else if(p[1] == 0x00)
				{
					if(m_pBtModule->getBtPhoneStatus() ==  BT_PHONE_STATUS_CALL_IN)
						m_pBtApp->m_pBtMainPage->clickAnswer(MOUSE_STATUS_UP);
				}
			}
			break;
			case 0x08:
			{
				m_pBtParam->tempHideBtPage = true;
				m_pBtModule->GPS_aboutCareLand_PTT(&p[1],len -1);
			}
			break;
			case 0x09:
			{
				m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);
			}
			break;
			case 0x0b:
				m_pBtHal->getHfpPhoneStatus((E_BT_PHONE_STATUS) p[1]);
				break;
			default:break;
		}

}

/*****************************SendToSDKFunction************************************/
 void CBtJniSdk::sendToFlyJniSdkService(u8 moduleId, u8 *p, int len)
 {
	 static u8 szMsg[256] = {0};
	 szMsg[0] = moduleId;
 
	 if(len > 256)
		 len = 256;
	 
	 memcpy(szMsg + 1, p, len);
	 m_pBtApp->setCommand(0x51FFFE, szMsg, len + 1);
 }
 void CBtJniSdk::sendToAppBtSwitchStatus(u8 p)
 {
 	if(!btSwitchStatusTag)
		return;
	 LOGD("[%s] p:%x", __FUNCTION__,p);
	 u8 szMsg[4] = {CMDTYPESTATUS,BT_STATUS_INFO,BT_STATUS_SWITCH, p};
	 sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, 4);
 }

 void CBtJniSdk::sendToAppBtConnectStatus(u8 p)
 {
 	if(!btConnectStatusTag)
		return;
	 LOGD("[%s] p:%x", __FUNCTION__,p);
	 u8 szMsg[4] = {CMDTYPESTATUS,BT_STATUS_INFO,BT_STATUS_CONNECT, p};
	 sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, 4);
 }

 void CBtJniSdk::sendToAppBtPhoneStatus(u8 p)
 {
 	if(!btPhoneStatusTag)
		return;
	 u8 szMsg[4] = {CMDTYPESTATUS,BT_STATUS_INFO,BT_STATUS_PHONE_STATE, p};
	 sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, 4);
 }

 void CBtJniSdk::sendToAppBtPhoneStatusAndNum(u8 p,char *num,u8 nuLen,char *name ,u8 naLen)
 {
 	if(!btPhoneStatusTag)
		return;
	u8 szMsg[230] = {0};
	szMsg[0] = CMDTYPESTATUS;
	szMsg[1] = BT_STATUS_INFO;
	szMsg[2] = BT_STATUS_PHONE_STATE;
	szMsg[3] = p;
	if(nuLen > 128)
		nuLen = 128;
	memcpy(szMsg+4,num,nuLen);
	u8 len = nuLen + 4;
	
	szMsg[len] = 0xff;
	
	if(naLen > 128)
		nuLen = 128;
	memcpy(szMsg+len+1,name,naLen);
	u8 allLen = len +1 +naLen;
	
	 sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, allLen);
 }

 void CBtJniSdk::sendToAppPhoneBookInfo()
 {
 	if(!SendBookTag)
		return;
	 char bookBuf[257];
	 int nameLen = 0;
	 int noLen = 0;
	 sendToAppPhoneBookLoadStatus(0x01);
	 list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itFrom = m_pBtParam->m_listPhoneBook.begin();
	 list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itTo = m_pBtParam->m_listPhoneBook.end();
	 list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator it;
	 for (it = itFrom; it != itTo; it++)
	 {
		 memset(bookBuf,0,sizeof(bookBuf));
		 nameLen = strlen(it->szUserName);
		 memcpy(bookBuf,it->szUserName,nameLen);
		 bookBuf[nameLen]  = 0xFF;
		 noLen = strlen(it->szUserNo);
		 memcpy(bookBuf + (nameLen+1),it->szUserNo,noLen);
		 int allLen = nameLen + noLen + 1;
		 sendToAppBtPhoneBook((u8 *)bookBuf,allLen);
	 }
	 sendToAppPhoneBookLoadStatus(0x02);
 }


 void CBtJniSdk::sendToAppBtPhoneBook(u8 *date,int len)
 {
	if(!SendBookTag)
		return;
	u8 szMsg[256*3];
	if(len >= 256 * 3)
		len = 256*3 -1;
	memset(szMsg,0,sizeof(szMsg));
	szMsg[0] = CMDTYPESTATUS;
	szMsg[1] = BT_PHONE_BOOK_INFO;
	szMsg[2] = 0x01;
	memcpy(szMsg + 3,date,len);
	sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, len + 3);
 }

 void CBtJniSdk::sendToAppPhoneBookLoadStatus(u8 cState)
 {
 	if(!SendBookTag)
		return;
	u8 szMsg[4] = {CMDTYPESTATUS,BT_PHONE_BOOK_INFO,0x02, cState};
	sendToFlyJniSdkService(MODULE_SDK_BT, szMsg, 4);
 }

