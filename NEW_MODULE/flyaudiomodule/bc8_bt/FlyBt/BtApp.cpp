/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "BtApp.h" 

CBtApp::CBtApp() 
{ 
} 

CBtApp::~CBtApp() 
{ 
} 
 
void CBtApp::init(void) 
{ 
	// ???????
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
} 

void CBtApp::processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	LOGD("[%s] id = [0x%x], mouseStatus = [%s]", __FUNCTION__, id, getMouseMessageType(e));

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
	setUtf8SerialData(id, p, len);
}

void CBtApp::MakeCallingInforsToUI(E_BT_PHONE_STATUS e,ST_PHONE_NUM *pst)
{
	u8 param[256] = {0x00};
	u32 len = 0;
	
	param[len++] = (u8)e;
	
	u32 nNa = strlen(pst->szcName);
	u32 nNu = strlen(pst->szcPhoneNum);

	u8 szUnicodeNum[64];
	memset(szUnicodeNum,0,sizeof(szUnicodeNum));
	int nRetNumLen = utf8_2_ucs2((u8*)pst->szcPhoneNum, nNu, szUnicodeNum, sizeof(szUnicodeNum));
	nRetNumLen = nRetNumLen + 2;
	memcpy(&param[len],szUnicodeNum,nRetNumLen);
	len += nRetNumLen;

	param[len++] = 0xFF;

	if(nNa > 0)
	{
		u8 szUnicodeName[256];
		memset(szUnicodeName,0,sizeof(szUnicodeName));
		int nRetNamLen = utf8_2_ucs2((u8*)pst->szcName, nNa, szUnicodeName, sizeof(szUnicodeName));
		nRetNamLen = nRetNamLen + 2;
		
		if(nRetNamLen > 190)
			nRetNamLen = 190;
		memcpy(&param[len],szUnicodeName,nRetNamLen);
		
		len += nRetNamLen;
	}

	btToApp_CallingInfors(param,len);
}

void CBtApp::btToApp_CallingInfors(u8 *buf,u32 len)
{
	u8 param[260] = {0x00};
	param[0]=0x3d;
	param[1]=0x10;

	if(len > 260)
		len = 258;

	memcpy(&param[2],buf,len);
	setCommand(0x00000000,param, len + 2);
}

void CBtApp::btToApp_CallingWindowPrompt(u8 p)
{
	u8 param[] = {0x3d, 0x11,0x00};
	param[2]=p;
	setCommand(0x00000000,param, 3);
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

void CBtApp::SendBtMacToSdk(u8 *param,u32 len)
{
	m_pBtModule->sendToFlyJNiSdkBtMac(param,len);
}

void CBtApp::SendBtNameToSdk(u8 *param,u32 len)
{
	m_pBtModule->sendToFlyJNiSdkBtName(param,len);
}

void CBtApp::SendConnectedBtMacToSdk(u8 *param,u32 len)
{
	m_pBtModule->sendToFlyJNiSdkConnectedBtMac(param,len);
}

void CBtApp::SendConnectedBtNameToSdk(u8 *param,u32 len)
{
	m_pBtModule->sendToFlyJNiSdkConnectedBtName(param,len);
}

bool CBtApp::DontDisplayWindowPromptAboutT123Video()
{
	bool bUn = false;

	if(m_pBtParam->uModuleBt_is_T123 == 0)
		return bUn;

	/*
	u16 nCurSoundMode = 0;
	u8  nCurSoundModelen = 0;
	m_pBtModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8*)&nCurSoundMode,&nCurSoundModelen);
	LOGD("[%s] nCurSoundMode:%d",__FUNCTION__,nCurSoundMode);
	switch(nCurSoundMode)
	{
		case CHANNEL_DVD_VIDEO:
		case CHANNEL_CDC_VIDEO:
		case CHANNEL_AUX_VIDEO:
		case CHANNEL_IPOD_VIDEO:
		case CHANNEL_TV_VIDEO:
		case CHANNEL_DVR_VIDEO:
		case CHANNEL_DNV_VIDEO:
			bUn = true;
		break;
	}
	*/

	switch(m_pBtModule->getCurPageId())
	{
		case PAGE_DVD_VIDEO:
		case PAGE_DVD_VIDEO_CONTROL:
		case PAGE_DVD_VIDEO_SET:
		case PAGE_BACK_VIDEO:
		case PAGE_BACK_FULL_VIDEO:
		case PAGE_BACK_FULL_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO:
		case PAGE_TV_VIDEO:
		case PAGE_TV_VIDEO_CONTROL:
		case PAGE_TV_VIDEO_SET:
		case PAGE_AUX_VIDEO_CONTROL:
		case PAGE_AUX_VIDEO_SET:
		case PAGE_DRIVING_RECORD_MENU:
		case PAGE_DRIVING_RECORD_TIME_SET:
		case PAGE_DRIVING_RECORD_SET:
		case PAGE_DRIVING_RECORD_PALY:
		case PAGE_DRIVING_CHANGHE_DVR_VIDEO_SET_OSD:
		case PAGE_DRIVING_CHANGHE_DVR_SET_OSD:
		case PAGE_DNV_VIEW_BACK_BROUND:
		case PAGE_DNV_VIEW:
		case PAGE_DNV_PLAY:
		case PAGE_DNV_PAUSE:
		case PAGE_OTHER_DVR_BACKGROUND:
		case PAGE_OTHER_DVR_MAIN:			
		case PAGE_OTHER_DVR_COLOR_SET:		
			bUn = true;
		break;
	}

	return bUn;
}
