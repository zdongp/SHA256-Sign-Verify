/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "BtApp.h" 
#include "types_def.h"
#include "commonFunc.h"
CBtApp::CBtApp() 
{ 
} 

CBtApp::~CBtApp() 
{ 
} 
 
void CBtApp::init(void) 
{ 
	LOGD("[%s] [%s] dyb", __FILE__, __FUNCTION__);
} 

void CBtApp::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{ 
	m_pBtApp	 = (CBtApp *)pFlyApp; 
	m_pBtModule  = (CBtModule *)pFlyModule; 
	m_pBtHal	 = (CBtHal *)pFlyHal; 
	m_pBtParam   = (CBtParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;

	m_pBtMainPage = new CBtMainPage();
	m_pBtMainPage->initObject(pFlyApp, pFlyHal, pFlyModule, pFlyParam);

	m_pBtDevicePages = new CBtDevicePages();
	m_pBtDevicePages->initObject(pFlyApp, pFlyHal, pFlyModule, pFlyParam);

	m_pBtPhoneBookPages = new CPhoneBookPages();
	m_pBtPhoneBookPages->initObject(pFlyApp, pFlyHal, pFlyModule, pFlyParam);

	m_pA2DPpages = new CA2DPpages();
	m_pA2DPpages->initObject(pFlyApp, pFlyHal, pFlyModule, pFlyParam);

	m_pCallRecordPages = new CCallRecordPages();
	m_pCallRecordPages->initObject(pFlyApp, pFlyHal, pFlyModule, pFlyParam);

	m_pMusicBrowsingPage = new CMusicBrowsingPage();
	m_pMusicBrowsingPage->initObject(pFlyApp, pFlyHal, pFlyModule, pFlyParam);

	m_pBtConnectionSetPages = new CBtConnectionSetPages();
	m_pBtConnectionSetPages->initObject(pFlyApp, pFlyHal, pFlyModule, pFlyParam);
} 

void CBtApp::processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	LOGD("[%s] id = [0x%x], mouseStatus = [%s]", __FUNCTION__, id, getMouseMessageType(e));
	if(id == 0x09FFFF && e == 0xFF)
	{
		m_pBtHal->separateCmd(p[0],(char *)(p+1),len-1); 
	}
	g_pClsBtAdapter->debugPrintf(p,len);	

	bool bRet = false;
	bRet =	m_pBtMainPage->pageMsgDispatch(id, e, p, len);
	if (bRet)
		return;

	bRet =	m_pBtDevicePages->pageMsgDispatch(id, e, p, len);
	if (bRet)
		return;

	bRet =	m_pBtPhoneBookPages->pageMsgDispatch(id, e, p, len);
	if (bRet)
		return;

	bRet=m_pCallRecordPages->pageMsgDispatch(id, e, p, len);
	if (bRet)
		return;
	
	bRet =	m_pA2DPpages->pageMsgDispatch(id, e, p, len);
	if (bRet)
		return;

	bRet = m_pMusicBrowsingPage->pageMsgDispatch(id, e, p, len);
	if (bRet)
		return;

	bRet = m_pBtConnectionSetPages->pageMsgDispatch(id, e, p, len);
	if (bRet)
		return;

}

void CBtApp::initUi()
{
	m_pBtMainPage->initUi();
	m_pBtDevicePages->initUi();
	m_pBtPhoneBookPages->initUi();
	m_pCallRecordPages->initUi();
	m_pA2DPpages->initUi();
}

void CBtApp::btToApp_SendConnectState(unsigned char state)
{
	LOGD("[%s] connectState state:%x",__FUNCTION__,state);
	u8 param[] = {0x3d, 0x01,0x00};
	if(state==0x01)
	{
		param[2]=0x01;
	}
	setCommand(0x00000000,param, 3);
}

void CBtApp::btToApp_SendPairState(unsigned char state)
{
	LOGD("[%s] PairState state:%x",__FUNCTION__,state);
	u8 param[] = {0x3d, 0x02,0x00};
	if(state==0x01)
	{
		param[2]=0x01;
	}
	setCommand(0x00000000,param, 3);
}

void CBtApp::btToApp_SendBtPhoneState(unsigned char state)
{
	LOGD("[%s] Callstate:%x",__FUNCTION__,state);
	u8 param[] = {0x3d, 0x03,0x00};
	param[2]=state;
	setCommand(0x00000000,param, 3);
}

void CBtApp::btToApp_SendBtPowerState(unsigned char state)
{
	LOGD("[%s] Powerstate:%x",__FUNCTION__,state);
	u8 param[] = {0x3d, 0x04,0x01};
	param[2]=state;
	setCommand(0x00000000,param, 3);
}

void CBtApp::btToApp_SendBtMac(u8 *param,int len)
{
	LOGD("[%s] Macparam:%s",__FUNCTION__,param);

	u8 *szMsg = (u8*)malloc(sizeof(u8)*(len+2));
	if(szMsg == NULL){
		return;	
	}
	szMsg[0] = 0x3d;
	szMsg[1] = 0x07;
	memcpy(&szMsg[2], param, len);
	setCommand(0x00000000,szMsg,len+2);
	free(szMsg);
}


void CBtApp::SwitchToSetData(u32 id, u8 *p, u32 len)
{ 
}

void CBtApp::setMainPageJump(void)
{
	unsigned char wPrePage;
	u8 len;
	m_pBtModule->getOtherModuleParam(MODULE_ID_SYSTEM, PREV_PAGE, (u8*)&wPrePage, &len);
	if(wPrePage == PAGE_MENU)
		m_pBtModule->setPrePage();
	else
		m_pBtModule->setPage(PAGE_MENU);
}

void CBtApp::SendPhoneNumToApp(char *tempInof,int len)
{
	if(len >= 256*3)
		len = 256*3 - 1;
	char phoneBookInfo[256*3];
	memset(phoneBookInfo,0,sizeof(phoneBookInfo));
	phoneBookInfo[0] = 0x0d;
	memcpy(phoneBookInfo + 1, tempInof , len);
	m_pBtModule->sendToFlyJNiSdkBtPhoneBook((u8 *)phoneBookInfo,len + 1);
	LOGD("[%s] phoneBookInfo:%s",__FUNCTION__,phoneBookInfo);
}

void CBtApp::SendPhoneNumToAppEndTag(void)
{
	LOGD("%s",__FUNCTION__);
	u8 szMsg[2] = {0x0e,0x01};
	m_pBtModule->sendToFlyJNiSdkBtPhoneBook((u8 *)szMsg,2);
}

void CBtApp::SendPhoneNumToSdk(char *tempInof,int len)
{
	if(len >= 256*3)
		len = 256*3 - 1;
	char phoneBookInfo[256*3];
	memset(phoneBookInfo,0,sizeof(phoneBookInfo));
	phoneBookInfo[0] = 0x11;
	memcpy(phoneBookInfo + 1, tempInof , len);
	m_pBtModule->sendToFlyJNiSdkBtPhoneBook((u8 *)phoneBookInfo,len + 1);
	LOGD("[%s] phoneBookInfo:%s",__FUNCTION__,phoneBookInfo);
}

void CBtApp::sendToFlyJniSdkPhoneBookInfo()
{
	char bookBuf[257];
	int nameLen = 0;
	int noLen = 0;
	m_pBtModule->sendToFlyJniSdkPhoneBookLoadStatus(0x01);
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
		m_pBtApp->SendPhoneNumToSdk(bookBuf,allLen);
	}
	m_pBtModule->sendToFlyJniSdkPhoneBookLoadStatus(0x02);
}
u8 CBtApp::getPlayRingStatus()
{
	char property[PROPERTY_VALUE_MAX] = {0};
	u8 RingStatus = 0;
	property_get("fly.play.ring.status", property, "1");
	sscanf(property,"%d", &RingStatus);
	return RingStatus;
}

