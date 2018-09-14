/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "BtHal.h"
#include "BtParam.h"
#include "BtApp.h"


CBtHal::CBtHal(void)
{
}

CBtHal::~CBtHal(void)
{
}

void CBtHal::init(void)
{
	// ��������������
	LOGD("[%s] [%s] dyb",__FILE__ , __FUNCTION__);
}

void CBtHal::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{
	m_pBtApp	 = (CBtApp *)pFlyApp; 
	m_pBtModule  = (CBtModule *)pFlyModule; 
	m_pBtHal	 = (CBtHal *)pFlyHal; 
	m_pBtParam   = (CBtParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;	
	g_pClsBtAdapter->init(m_pBtHal,m_pBtApp,m_pBtParam,m_pBtModule);
	g_pClsBtJniSdk->init(m_pBtHal,m_pBtApp,m_pBtParam,m_pBtModule);
}

void CBtHal::setToHalBtMsg(char *p, int len)
{
	if(p[0] == 0x01 && p[1] == 0x01 && p[2] == 0x01&& len == 3)
	{
		makeAndSendMessageToHal(HAL_ID_BT, (u8*)p, len);
	}
	else if(!m_pBtParam->bInitState)
		return;
	u8 szMsg[FLY_BT_DEVICE_END_CMD_MAX_LEN] = {0};
	if(len > (FLY_BT_DEVICE_END_CMD_MAX_LEN - 1))
		len = FLY_BT_DEVICE_END_CMD_MAX_LEN - 1;
	printf("\n[BT] setToHalBtMsg:");
	LOGD("\n[BT] setToHalBtMsg:");
	g_pClsBtAdapter->debugPrintf((u8 *)p,len);
	m_pBtApp->setCommand(0x09FFFF,(u8*)p, len);
/*
	if(len == 3)
	{
		if(p[0] == 0x01 && p[1] == 0x01 && p[2] == 0x01)
			makeAndSendMessageToHal(HAL_ID_BT, (u8*)p, len);
	}
*/
}

void CBtHal::analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len)
{
	printf("\n[BT] [analyseHalMessage] :0x%x ",cmd);
	g_pClsBtAdapter->debugPrintf(p,len);
	separateCmd(cmd,(char *)p,len);
}

void CBtHal::separateCmd(u8 rescmd,char *p,int len)//nf
{
	if(len <= 0)
		return;
	switch(rescmd)
	{
		case 0x01:
			separateCmd_Generalcommands(p,len);
		break;
		case 0x02:
			separateCmd_BluetoothCommands(p,len);
		break;
		case 0x03:
			separateCmd_BluetoothPairingCommands(p,len);
		break;
		case 0x04:
			separateCmd_BluetoothConnectionCommands(p,len);
		break;
		case 0x05:
			separateCmd_BluetoothPhoneCommands(p,len);
		break;
		case 0x06:
			separateCmd_PlayerManagement(p,len);
		break;
		case 0x07:
			separateCmd_PhonebookManagementCommands(p,len);
		break;
		default:break;
	}
}

void CBtHal::separateCmd_Generalcommands(char *p,int len)
{
	switch(p[0])
	{
		case 0x01:
		{
			if(p[1] == 0x00){
			}
			else if(p[1] == 0x01)
			{
				m_pBtParam->bInitState = true;
				setToHalBtPower(0x01);
			}
		}
		break;
		case 0x02:
			m_pBtHal->getLocalBtDeviceVersion(&p[1], len - 1);
		break;
		case 0x03:
		{
			if(p[1] == 0)
			{
				getHfpPowerState(0x01);
			}
			else if(p[1] == 1)
			{
				getHfpPowerState(0x00);
			}
			else if(p[1] == 2)
				setToHalBtPower(0x01);
			else if(p[1] == 3)
				setToHalBtPower(0x00);
		}
		break;
		case 0x04:
		{
		}
		break;
		default:break;
	}
}
void CBtHal::separateCmd_BluetoothCommands(char *p,int len)
{
	switch(p[0])
	{
		case 0x01:
		{
			if(p[1] == 0x00)
				printf("[BT] dang qian ke jian ce\n");
			else if(p[1] == 0x01)
				printf("[BT] dang qian bu ke jian ce\n");
		}
		break;
		case 0x02:
			m_pBtHal->getLocalBtDeviceAddr(p + 1, len - 1);
		break;
		case 0x03:
			printf("[BT] Bt_Name: %s\n",p+1);
			m_pBtHal->getLocalBtDeviceName(p + 1, len - 1);
		break;
		case 0x04:
		{
			m_pBtParam->bIsAutoConnect = p[1];
			m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_AUTO_CONNET,p[1]);
		}
		break;
		case 0x05:
		{
			if(p[1] == 0x00)
			{
				m_pBtParam->bHandleStopSearchState = false;
				getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCHING);
				printf("[BT] kai shi sou suo !!\n");
			}
			else if(p[1] == 0x01)
			{
				m_pBtParam->bHandleStopSearchState = false;
				getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCHING);
			}
			else if(p[1] == 0x02)
			{
				getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH);
				m_pBtParam->bHandleStopSearchState = true;
			}	
		}
		break;
		case 0x06:
		{
			new_SearchedDeviceCounts(p + 1,len - 1);
		}
		break;case 0x07:
			getLocalBtDeviceAddrFormated(p + 1, len - 1);
		break;
		case 0x09:
		{
			new_getLocalBtDevicePinCode(p+1,len -1);
		}
		break;
		default:break;
	}

}
void CBtHal::separateCmd_BluetoothPairingCommands(char *p,int len)
{
	switch(p[0])
	{
		case 0x01:
		{		
		}
		break;
		
		case 0x02:
		{
			m_pBtParam->nPairRecordTotal = p[1];
			m_pBtParam->m_listBtDevicesHavePaired.clear();
		}
		break;
		
		case 0x03:
		{
			if(p[1] == 0x00)
			{
				m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT1, STRINGID_BT__DEVICE_PAIRING_CONNECTION_ERROR);
				m_pBtParam->bPairingStatus = false;
			}
			else if(p[1] == 0x01)
			{
				m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT1, STRINGID_BT__DEVICE_PAIRING_CONNECTION_BEGIN);
				m_pBtParam->bPairingStatus = true;
			}
			else if(p[1] == 0x02)
			{
				m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT1,0);
				m_pBtParam->bPairingStatus = false;
			}
		}
		break;
		
		case 0x04:
			printf("[BT] pei dui mo shi: %d\n",p[1]);
		break;
		
		case 0x05:
		{	
			char szPincode[128] = {0};
			int nPincodeLen = 0;
			char szPairingName[128] = {0};
			int nPairingNameLen = p[1];
			int nDataLen = len-2;
			int nTo = g_pClsBtAdapter->Inside_FindIndexFromStr((u8 *)(p + 2),nDataLen,0xFF,0);
			if(nTo >= 0)
			{
				memcpy(szPairingName,p + 2 +(nTo+1),nPairingNameLen);
			}
			nPairingNameLen = nDataLen - (nTo +1 + nPairingNameLen);
			if(nPairingNameLen > 0)
			{
				memcpy(szPincode,p + 2 +(nTo+1+nPairingNameLen),nPairingNameLen);
			}
			printf("[BT] PhoneBTname: %s\n",szPairingName);
			m_pBtHal->getPairingModeInfors_Bi_directional(szPincode,nPincodeLen,szPairingName,nPairingNameLen);
			if(m_pBtParam->tempAutoMatetsg = true)
			{
				m_pBtParam->bIsPairBox = true;
			}
			//g_pClsBtAdapter->setBtPairConfirm(0x01);
		}
		break;
		case 0x07:
			{
				new_getpairDeviceRecord((u8 *) (p+1),len -1);
				if(p[1] ==( m_pBtParam->nPairRecordTotal -1) && m_pBtParam->m_eHfpConnectStatus == HFP_CONNECT_STATUS_CONNECTED)
				{
					new_getCurConnectDeviceName(m_pBtParam->szRemodeBtDeviceHasConnectedAddr);
				}
			}
		break;
		case 0x08:
			{	
				int nFF = g_pClsBtAdapter->findCharIndex((unsigned char*)p, len, 0xFF);
				int addrLen = len -nFF -1;
				getBtDeleteStatus(p+(nFF+1),addrLen);
			}
			break;
		default:break;
	}
}
void CBtHal::separateCmd_BluetoothConnectionCommands(char *p,int len)
{
	switch(p[0])
	{
		case 0x01:
		{
			if(p[1] == 0x00)
			{
				m_pBtHal->getHfpConnectStatus(HFP_CONNECT_STATUS_DISCONNECT);
			}
			else if(p[1] == 0x01)
			{
				m_pBtHal->getHfpConnectStatus(HFP_CONNECT_STATUS_CONNECTING);
			}
			else if(p[1] == 0x02)
			{
				m_pBtHal->getHfpConnectStatus(HFP_CONNECT_STATUS_CONNECTED);
			}
			else if(p[1] == 0x03)
			{
				printf("[BT] zhengzaiduankailianjie!\n");
			}
		}
		break;
		case 0x02:
		{
			//m_pBtHal->getCurConnectedBtDeviceName(p + 1, len - 1);
			//m_pBtHal->BtDeviceNameOfThedeviceconnectedToTheinsidepagesAndtheRealPairIsNotTheSame();
		}
		break;
		case 0x03:
		{
			getCurConnectedBtDeviceAddr(p + 1, len - 1);
			saveCurConnectedBtDeviceAddr(p + 1, len - 1);
			//new_getCurConnectDeviceName(p+1);
		}
		break;
		case 0x04:
		{
			m_pBtParam->m_nMobileBattery = p[1];
			m_pBtModule->golf_sendToCarScreen_batteryStrength(m_pBtParam->m_nMobileBattery);
		}
		break;
		case 0x05:
		{
			m_pBtParam->m_nMobileSignal = p[1];
			m_pBtModule->golf_sendToCarScreen_signalState(m_pBtParam->m_nMobileSignal);
		}
		break;
		default:break;
	}
}
void CBtHal::separateCmd_BluetoothPhoneCommands(char *p,int len)
{
	switch(p[0])
	{
		case 0x01:
			getCurPhoneStatusForHal(p+1,len -1);
		break;
		case 0x02:
		{
			if(p[1] == 0x00)
				getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_BULETOOTH);
			else if(p[1] == 0x01)
				getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_PHONE);
		}
		break;
		case 0x03:
		{
		/*
			bool bMicOpenState = false;
			if (p[1] == 0x01)
			{
				bMicOpenState = false;
			}
			else if(p[1] == 0x00)
			{
				bMicOpenState = true;
				
			}
		*/
			m_pBtHal->getHfpMicStatus(p[1]);
		}
		break;
		default:break;
	}
}

void CBtHal::separateCmd_PlayerManagement(char *p,int len)
{
	printf("[BT] A2DP:%d %d %d\n",p[0],p[1],p[2]);
	switch(p[0])
	{
		case 0x01:
		{
			if(p[1] == 0x00)
			{
				GetA2DPPlayOrStopState_switch(2);
			}
			else if(p[1] == 0x01)
				m_pBtApp->m_pA2DPpages->clearA2DPInfo();
			else if(p[1] == 0x02)
			{
				GetA2DPPlayOrStopState_switch(1);
			}
		}
		break;
		case 0x02:
		break;
		case 0x03:
		break;
		case 0x04:
		{
			if(m_pBtParam->m_bSupport_A2DP)
				analyseSongInfo(p+1,len -1);
		}
		break;
		case 0x05:
		{
			if(p[1] == 0x00)
			{
				new_getA2DPStatus(false);
				printf("[BT] show disConnect!\n");
			}
			else if(p[1] == 0x01)
			{
				new_getA2DPStatus(true);
				new_initParamAfterA2DPConnected();
			}
			else if(p[2] == 0x02)
				printf("[BT] show Connecting!\n");
		}
		break;
		case 0x07:
			GetA2dpAudioFucseState(p[1]);
		break;
		default:break;
	}
}

void CBtHal::analyticalSongsDatas(char *p,int len)
{
	int ID3_Len = len;

	char songTitle[FLY_BT_MUSIC_INFOR_MAX_LEN] = {0};
	int titleLen = 0;
	
	char author[FLY_BT_MUSIC_INFOR_MAX_LEN] = {0};
	int authorLen = 0;
	
	char album[FLY_BT_MUSIC_INFOR_MAX_LEN] = {0};
	int albumLen = 0;
	
	int nFF1 = 0;
	nFF1 = g_pClsBtAdapter->findCharIndex((u8 *)p,ID3_Len,0xFF);
	
	if(-1 != nFF1)
	{
		titleLen = nFF1;
		if(titleLen > FLY_BT_MUSIC_INFOR_MAX_LEN)
			titleLen = FLY_BT_MUSIC_INFOR_MAX_LEN;
	
		if(titleLen > 0)
			memcpy(songTitle,p,titleLen);
	}
	
	int nFF2 = 0;
	nFF2 = g_pClsBtAdapter->findCharIndex((u8 *)(p + nFF1 + 1),ID3_Len - titleLen - 1,0xFF);
	if(-1 != nFF2)
	{
		authorLen = nFF2;
		if(authorLen > FLY_BT_MUSIC_INFOR_MAX_LEN)
			authorLen = FLY_BT_MUSIC_INFOR_MAX_LEN;
	
		if(authorLen > 0)
			memcpy(author,(p + nFF1 + 1),authorLen);
	}  
	
	int nFF3 = 0;
	nFF3 = g_pClsBtAdapter->findCharIndex((u8 *)(p + nFF1 + 1 + nFF2 + 1),ID3_Len - titleLen - 1 - authorLen - 1,0xFF);
	if(-1 != nFF2)
	{
		albumLen = nFF3;
		if(albumLen > FLY_BT_MUSIC_INFOR_MAX_LEN)
			albumLen = FLY_BT_MUSIC_INFOR_MAX_LEN;
	
		if(albumLen > 0)
			memcpy(album,p + nFF1 + 1 + nFF2 + 1,albumLen);
	} 
	
	m_pBtHal->getA2DPInfo(songTitle,titleLen,author,authorLen,album,albumLen);

}

void CBtHal::separateCmd_PhonebookManagementCommands(char *p,int len)
{
	if(m_pBtParam->m_eHfpConnectStatus != HFP_CONNECT_STATUS_CONNECTED)
		return;

	switch(p[0])
	{
		case 0x01:
		{ 
		}
		break;
		case 0x02:
		{
			if(p[1] == 0x00 || p[1] == 0x01)
			{
				new_CreatePhoneBookList(p+3,len -3);
			}
			else if(p[1] == 0x02 || p[1] == 0x03 || p[1] == 0x04)
			{
				new_CreateCallRecordList(p+1,len -1);
			}
		}
		break;
		case 0x03:
			new_getPhoneBookLoadState(p[2],p[1]);
		break;
		default:break;
	}
}

void CBtHal::setToHalBtPower(u8 p)
{
	if(p == 0)
	{
		g_pClsBtAdapter->requestBtTurnONorOFF(0x00);
	}
	else
		g_pClsBtAdapter->requestBtTurnONorOFF(0x01);
	setToHalBtPowerStatus(p);
}

void CBtHal::getHfpPowerState(char state)
{
	printf("[BT] [getHfpPowerState] cState:%d\n", state);
	if(m_pBtParam->m_bIsPowerOn == state)
		return;
	m_pBtParam->m_bIsPowerOn = state;
	m_pBtModule->sendToFlyJniSdkPowerState(state);
	m_pBtApp->btToApp_SendBtPowerState(state);
	g_pClsBtJniSdk->sendToAppBtSwitchStatus(state);
	if(state == 0x00)
	{
		clearAfterHfpPowerOff();
	}
	else
	{
		initParamAfterHfpPowerOn();
		m_pBtApp->m_pBtDevicePages->setAutoConnect(m_pBtParam->bIsAutoConnect);
		new_initParamAfterHfpPowerOn();
	}  
}

void CBtHal::new_initParamAfterHfpPowerOn()
{	
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE_TEXT,(u8*)m_pBtParam->szLocalBtDevice_PinCode, strlen(m_pBtParam->szLocalBtDevice_PinCode));
	m_pBtApp->m_pBtDevicePages->clickDisplaySetDeviceNameToUi((u8*)m_pBtParam->szLocalBtDevice_Name,(u32)strlen(m_pBtParam->szLocalBtDevice_Name));
	m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NO_BLUETOOTH,1);
	if(m_pBtParam->m_listBtDevicesHavePaired.empty())
	{
		m_pBtApp->setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, (u8*)"", 0);
	}
	else
	{
		m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_DEVICE_IS_DISCONNECTED);
	}
	getBtInfoAfterHfpPowerOn();
}

void CBtHal::getBtInfoAfterHfpPowerOn()
{
	if(true == m_pBtParam->bInitState)
	{
		g_pClsBtAdapter->setBtPincode((u8 *)m_pBtParam->szLocalBtDevice_PinCode,4);
		g_pClsBtAdapter->setDeviceBtName((u8*)m_pBtParam->szLocalBtDevice_Name,strlen(m_pBtParam->szLocalBtDevice_Name));
		g_pClsBtAdapter->setBtAutomateConnect(m_pBtParam->bIsAutoConnect);
				
		g_pClsBtAdapter->requestBtPairRecord();
		g_pClsBtAdapter->setBtPairMode(0x00);
		//g_pClsBtAdapter->requestBtName();
		g_pClsBtAdapter->requestBtAddr();
		g_pClsBtAdapter->requestBtversion();
		g_pClsBtAdapter->setBtCanbeDetected(0x01);
	}
}

void CBtHal::getLocalBtDeviceVersion(char *p, int len)
{
	memset(m_pBtParam->szLocalBtDeviceVersion, 0, sizeof(m_pBtParam->szLocalBtDeviceVersion));
	memcpy(m_pBtParam->szLocalBtDeviceVersion, p, len);
	m_pBtApp->m_pBtMainPage->refreshLocalBtDeviceVersion(m_pBtParam->szLocalBtDeviceVersion,len);
}

void CBtHal::getLocalBtDeviceAddr(char *p, int len)
{
	memset(m_pBtParam->szLocalBtDeviceAddr, 0, sizeof(m_pBtParam->szLocalBtDeviceAddr));
	memcpy(m_pBtParam->szLocalBtDeviceAddr, p, len);
	FormatBtMacAddress(p,len);
}
void CBtHal::getLocalBtDeviceAddrFormated(char *p, int len)
{
	WithoutColonBtMacAddress(p,len);
	
	m_pBtApp->btToApp_SendBtMac((u8 *)p,len);
	m_pBtApp->m_pBtDevicePages->ShowBtMacAddress(p,len);
}
void CBtHal::WithoutColonBtMacAddress(char *strData,int str_len)
{
	if(str_len <= 0)
		return;

	char to[FLY_BT_DEVICE_ADDRS_MAX_LEN];
	memset(to,0,sizeof(to));
	int i = 0, j = 0;
	while (i < str_len)
	{
		if (strData[i] != ':')
		{
			to[j++] = strData[i];
		}

		i++;
	}
	to[j] = '\0';

	memset(m_pBtParam->szLocalBtDeviceAddr, 0, sizeof(m_pBtParam->szLocalBtDeviceAddr));
	memcpy(m_pBtParam->szLocalBtDeviceAddr, to, strlen(to));
	printf("[BT] Bt Addr:%s(%d)\n",m_pBtParam->szLocalBtDeviceAddr,strlen(m_pBtParam->szLocalBtDeviceAddr));
}

void CBtHal::FormatBtMacAddress(char *strData,int str_len)
{
	char strCommand[256]={0};
	if(str_len != 0)
	{
		int i=0;
		char strCommand1[256]={0};
		char strCommand2[1] = {':'};
		char strCommand3[2] = {0};
		while(i <= str_len-1)
		{
			if((str_len-i) >= 2)
			{
				strncat(strCommand1,strData+i,sizeof(strCommand3));

				if((str_len-i) > 2)
				{
					strncat(strCommand1,strCommand2,sizeof(strCommand2));
				}
			}
			else
			{
				strncat(strCommand1,strData+i,sizeof(strCommand2));
			}
 
				i = i+2;
			}
			
			sprintf(strCommand,"%s",strCommand1);	
	}
	else
	{
		sprintf(strCommand,"NULL",strData);	
	}

	ToUIBtDeviceAddr((u8 *)strCommand,strlen(strCommand));
	m_pBtApp->m_pBtDevicePages->ShowBtMacAddress(strCommand,strlen(strCommand));
}

void CBtHal::ToUIBtDeviceAddr(u8 *p, int len)
{
	char property[PROPERTY_VALUE_MAX] = {0};
	sprintf(property, "%s",p);
	//m_pBtParam->property_set(FLY_BT_DEVICE_ADDR, property);
	m_pBtApp->btToApp_SendBtMac(p,len);
}

void CBtHal::getLocalBtDeviceName(char *p, int len)
{
	if(true == m_pBtParam->bInitState)
	{
		memset(m_pBtParam->szLocalBtDevice_Name,0,sizeof(m_pBtParam->szLocalBtDevice_Name));
		memcpy(m_pBtParam->szLocalBtDevice_Name, p, len);

		m_pBtApp->m_pBtDevicePages->clickDisplaySetDeviceNameToUi((u8*)p,(u32)len);

		m_pBtModule->golf_sendToCarScreen_mobileOperatorName((u8*)p,(u32)len);
	}
}

void CBtHal::getBtDeviceSearchStatus(E_BT_DEVICE_SEARCH_STATUS e)
{
    printf("[BT] [getBtDeviceSearchStatus] E_BT_DEVICE_SEARCH_STATUS:%d\n",e);
	m_pBtParam->m_eBtDeviceSearchStatus = e;
	m_pBtApp->m_pBtDevicePages->refreshBtDeviceSearchStatus(e);
}

void CBtHal::new_SearchedDeviceCounts(char *p, int len)
{
	char szAddr[FLY_BT_PAIRING_ADDRS_MAX_LEN] = {0};
	char szName[FLY_BT_PAIRING_NAME_MAX_LEN] = {0};
	int nameLen = p[0];
	int addrLen = len - 2 - nameLen;
	
	printf("[BT] nameLen: %d\n",nameLen);
	
	if(nameLen > FLY_BT_PAIRING_NAME_MAX_LEN)
		nameLen = FLY_BT_PAIRING_NAME_MAX_LEN;
	memcpy(szName, p + 2, nameLen);

	if(nameLen > FLY_BT_PAIRING_ADDRS_MAX_LEN)
		nameLen = FLY_BT_PAIRING_ADDRS_MAX_LEN;
	memcpy(szAddr, p + 2 + nameLen,addrLen);

	printf("[BT] Search for Bluetooth devices. add = [%s], name = [%s]\n", szAddr, szName);
	
	m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCHED_DEVICE_COUNT);
	m_pBtHal->getBtDeviceHasSearch(szAddr, addrLen, szName, nameLen);
}

void CBtHal::getBtDeviceHasSearch(char *pAddr, int addrLen, char *pName, int nameLen)
{
	if(m_pBtParam->m_listBtDevicesHaveSearched.size() > 0){
		if(WhetherThereIsCurrentlyDuplicateDeviceSearchList(pAddr,addrLen))
			return;
	}
	
	BluetoothDevice t;
	memset(&t, 0, sizeof(BluetoothDevice));
	int n = strlen(pName);
	if(n == 0)
	{
		memcpy(t.deviceName, pAddr, addrLen);
		t.nameLen = addrLen;
	}
	else
	{
		memcpy(t.deviceName, pName, nameLen);
		t.nameLen = nameLen;
	}
	memcpy(t.deviceAddr, pAddr, addrLen);
	t.addrLen =  addrLen;
	
	m_pBtParam->m_listBtDevicesHaveSearched.push_back(t);
	m_pBtParam->m_btDevicesHaveNum = m_pBtParam->m_listBtDevicesHaveSearched.size();
	char str[256]={0};   
	sprintf(str,"(%d)",m_pBtParam->m_btDevicesHaveNum);
	
	if(m_pBtParam->m_btDevicesHaveNum > 0)
	{
		m_pBtApp->setUtf8String((u32)(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_PERCENTAGE), (u8*)str, strlen(str));
	}
		

	m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHaveSearched(m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);
	m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHaveSearched_New(m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);

}

bool CBtHal::WhetherThereIsCurrentlyDuplicateDeviceSearchList(s8 *cAddr,s32 nAddrLen)
{
	bool b = false;
	
	list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHaveSearched.begin();
	list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHaveSearched.end();

	for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
	{
		if((strcmp(cAddr,(char *)it->deviceAddr) == NULL) && (nAddrLen == it->addrLen))
		{	
			b = true;
			continue;
		}
	}

	return b;
}
void CBtHal::new_getBtDeviceHasPaired(int index, char *pAddr, int addrLen, char *pName, int nameLen)
{	
	if(addrLen <= 0)
		return;
	if(addrLen > FLY_BT_PAIRING_ADDRS_MAX_LEN)
		addrLen = FLY_BT_PAIRING_ADDRS_MAX_LEN;
	if(nameLen > FLY_BT_PAIRING_NAME_MAX_LEN)
		nameLen = FLY_BT_PAIRING_NAME_MAX_LEN;
	
	if(index >= 0)
	{
		BluetoothDevice t;
		memset(&t, 0, sizeof(BluetoothDevice));

		t.index = index;
		t.addrLen=addrLen;
		t.nameLen=nameLen;
		memcpy(t.deviceAddr, pAddr, addrLen);
		memcpy(t.deviceName, pName, nameLen);
		int i = 0, j = 0;
		list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
		list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

		if(m_pBtParam->m_listBtDevicesHavePaired.size() > 0)
		{
			for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
			{
				if(strcmp((char *)t.deviceAddr,(char *)it->deviceAddr) == 0)
				{
					return;
				}
				
				j++;
				if(strcmp((char *)t.deviceAddr,m_pBtParam->szRemodeBtDeviceHasConnectedAddr) == 0)
				if (j >= BT_DEVICE_PAIR_PAGE_ITEM_NUM_NEW)
				break;
			}
		}
		if(strcmp((char *)t.deviceAddr,m_pBtParam->szRemodeBtDeviceHasConnectedAddr) == 0)
			t.curConnectDevice = false;
		else
			t.curConnectDevice = true;
		m_pBtParam->m_listBtDevicesHavePaired.push_back(t);
		m_pBtParam->m_listBtDevicesHavePaired.sort();
		m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired(0);
		m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired_New(0);
	}
}

void CBtHal::getPairingModeInfors_Bi_directional(char *cP1,int nP1Len,char *cP2,int nP2Len)
{
	if(!m_pBtModule->isBtDeviceSearchFinish())
	{
		g_pClsBtAdapter->requestBtSearchDevice(0x00);
	}
						
	memset(&m_pBtParam->str_BtPairing,0,sizeof(BT_PairingInfors));

	memcpy(m_pBtParam->str_BtPairing.szPairingPincode,cP1,nP1Len);
	memcpy(m_pBtParam->str_BtPairing.szPairingName,cP2,nP2Len);
	m_pBtParam->str_BtPairing.nPairingPincodeLen = nP1Len;
	m_pBtParam->str_BtPairing.nPairingNameLen = nP2Len;

	m_pBtApp->m_pBtDevicePages->showDialogBox_Pairing((u8*)cP1,nP1Len,(u8*)cP2,nP2Len);
}


void CBtHal::getHfpConnectStatus(E_HFP_CONNECT_STATUS e)
{
	if(e == m_pBtParam->m_eHfpConnectStatus)
		return;
		
    	LOGD("[%s] E_HFP_CONNECT_STATUS:%d",__FUNCTION__,e);

	//m_pBtParam->m_eHfpConnectStatus = e;
	
	if(HFP_CONNECT_STATUS_CONNECTING==e)
	{
	}
	else if(HFP_CONNECT_STATUS_CONNECTED==e)
	{
		m_pBtParam->m_eHfpConnectStatus = e;
		m_pBtParam->emTempHfpConnectStatus = e;
		m_pBtModule->golf_sendToCarScreen_PhoneConnState(1);
		refreshParamAfterHFPConnected();
		new_initParamAfterHFPConnected();
		if((m_pBtModule->getCurPageId() == PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME) || (m_pBtModule->getCurPageId() == PAGE_BLUETOOTH_AUDIOVOX_SEARCH)|| (m_pBtModule->getCurPageId() == PAGE_BLUETOOTH_PHONEPAIR))
		{
			if((m_pBtModule->getPrePageId() == PAGE_BLUETOOTH_A2DP || m_pBtModule->getPrePageId() == PAGE_BLUETOOTH_NO_A2DP) && m_pBtParam->bA2DP_To_DevicePageBackButton)
			{
				m_pBtModule->setPage(PAGE_BLUETOOTH_A2DP);
			}
			else{
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
			}
		}
		m_pBtModule->btToModule_golf_updatePhoneBook();
	}
	else 
	{
		m_pBtParam->m_eHfpConnectStatus = e;
		m_pBtParam->emTempHfpConnectStatus = e;
	  	clearHistoryAfterHFPDisconnect();
	}

	//m_pBtParam->emTempHfpConnectStatus = e;
}

void CBtHal::getCurConnectedBtDeviceAddr(char *p, int len)
{
	memset(m_pBtParam->szRemodeBtDeviceHasConnectedAddr, 0, sizeof(m_pBtParam->szRemodeBtDeviceHasConnectedAddr));
	memcpy(m_pBtParam->szRemodeBtDeviceHasConnectedAddr, p, len);
}

void CBtHal::new_getCurConnectDeviceName(char *addr)
{
	u8 strName[FLY_BT_PAIRING_NAME_MAX_LEN] = {0};
	int nameLen = 0;
	int i = 0;
	int nPairedCount = m_pBtParam->m_listBtDevicesHavePaired.size();
	if(nPairedCount  < 1)
		return;
	list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
	list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

	for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
	{
		if(!strncmp(addr,(char *)it->deviceAddr,it->addrLen))
		{
			nameLen = it->nameLen;
			if(nameLen < 0)
				return;
			memcpy(strName,it->deviceName,nameLen);
			break;
		}
		i++;
	}
	
	memset(m_pBtParam->szRemodeBtDeviceHasConnectedName, 0, sizeof(m_pBtParam->szRemodeBtDeviceHasConnectedName));
	memcpy(m_pBtParam->szRemodeBtDeviceHasConnectedName, strName, nameLen);
	m_pBtModule->sendToFlyJniSdkRemoteDeviceName(m_pBtParam->szRemodeBtDeviceHasConnectedName, nameLen);
	m_pBtApp->m_pBtMainPage->refreshRemodeBtDeviceName((u8 *)m_pBtParam->szRemodeBtDeviceHasConnectedName,(u32)nameLen);

	//GOLF
	m_pBtModule->btToModule_golf_phoneName(strName, nameLen);
}

void CBtHal::getHfpPhoneStatus(E_BT_PHONE_STATUS e)
{
	LOGD("[%s] PhoneStatus=%x",__FUNCTION__,e);
	switch(e)
	{
		case BT_PHONE_STATUS_FREE:
		case BT_PHONE_STATUS_CALL_IN:
		case BT_PHONE_STATUS_CALL_OUT:
		case BT_PHONE_STATUS_TALKING: 
			m_pBtParam->m_ePhoneStatus = e;
			//m_pBtModule->sendToFlyJniSdkPhoneStatus(m_pBtParam->m_ePhoneStatus);
			//g_pClsBtJniSdk->sendToAppBtPhoneStatus((u8)m_pBtParam->m_ePhoneStatus);
		break;
	}

	if(e != m_pBtParam->emTempHfpPhoneStatus)
	{
		if(BT_PHONE_STATUS_FREE == e)
			m_pBtModule->btToModule_NotifyExternalctrl_VoiceSwitchCtrl(0x01);
		else
			m_pBtModule->btToModule_NotifyExternalctrl_VoiceSwitchCtrl(0x00);
	}
		
	switch(e)
	{
		case BT_PHONE_STATUS_FREE:
		{
			m_pBtParam->emTempHfpTalkingTransferSet = HFP_SET_UNKNOWN_SIDE;
			clearAfterHandup();
			m_pBtParam->muteSwicthState = false;
			m_pBtApp->m_pBtMainPage->DisplayingMuteButtonState();
			m_pBtModule->btToModule_NotifyCenter_StopRing();
			m_pBtApp->m_pBtMainPage->refreshBTAudioFromFlyDeviceOrFromMobile(0);
			clearPhoneNumInput();
			m_pBtApp->m_pBtMainPage->refreshBTManyCallInfo(0);
			setToHalMobileStatus(0);

			printf("[BT] [getHfpPhoneStatus] m_pBtParam->m_bAutoJump=%x\n",m_pBtParam->m_bAutoJump);	
			if(m_pBtParam->m_bAutoJump == true)
			{		
				int CurPageID = m_pBtModule->getCurPageId();
				if(CurPageID == PAGE_BLUETOOTH_MAIN)
					m_pBtModule->setPrePage();
				m_pBtParam->m_bAutoJump = false;
			}
			else
			{
				if(!m_pBtParam->bSpecialCaseBackPage)
				{
					int CurPageID = m_pBtModule->getCurPageId();
					if(CurPageID == PAGE_BLUETOOTH_MAIN)
					{
						int PrePageID = m_pBtModule->getPrePageId();
						if(PrePageID == PAGE_GPS_PAGE)
						{
							m_pBtModule->setPrePage();
							m_pBtParam->m_bAutoJump = false;
						}
					}
				}
			}

			m_pBtParam->bSpecialCaseBackPage = false;
			if(m_pBtParam->tempHideBtPage)
				m_pBtParam->tempHideBtPage = false;
			m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_FREE,true,false,(char *)"",(char *)"");
		}
		break;
		case BT_PHONE_STATUS_CALL_IN:
		{
			if(m_pBtParam->tempHideBtPage)
				m_pBtParam->tempHideBtPage = false;
			m_pBtApp->setStringById(CONTROLID_BLUETOOTH_MAIN_CALL_IN_OR_OUT, STRINGID_BT_CALL_IN);
			setToHalMobileStatus(1);
			if(m_pBtApp->getPlayRingStatus())
				m_pBtModule->btToModule_NotifyCenter_StartRing((u8)2);
			if(!m_pBtModule->getBackCarStatus())
			{
					int CurPageID = m_pBtModule->getCurPageId();
					if(CurPageID != PAGE_BLUETOOTH_MAIN && CurPageID != PAGE_BACK_NOVIDEO && CurPageID != PAGE_BACK_VIDEO)
					{
					    m_pBtParam->m_ePhoneStatus = BT_PHONE_STATUS_CALL_IN;
						m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);  
						m_pBtParam->m_bAutoJump = true;
					}
					else if(CurPageID == PAGE_BLUETOOTH_MAIN)
					{
						m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN); 
					}
			}
			else
			{
				if(m_pBtParam->m_ePhoneStatus != BT_PHONE_STATUS_CALL_IN)
				{
					m_pBtParam->m_bAutoJump  = false;
				}
			}
			m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_CALL_IN,true,true,m_pBtParam->m_strTemInName,m_pBtParam->m_strTemInNum);
		}
		break;
		case BT_PHONE_STATUS_CALL_OUT:
		{
			if(!m_pBtModule->getBackCarStatus())
			{
				int CurPageID = m_pBtModule->getCurPageId();
				if(CurPageID != PAGE_BLUETOOTH_MAIN)
				{
					m_pBtParam->m_ePhoneStatus = BT_PHONE_STATUS_CALL_OUT;
					if(!m_pBtParam->tempHideBtPage)
					{
						m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN); 
						m_pBtParam->m_bAutoJump = true;
					}
				} 
				else if(CurPageID == PAGE_BLUETOOTH_MAIN)
				{
					if(m_pBtParam->m_ePhoneStatus != BT_PHONE_STATUS_CALL_OUT)
						m_pBtParam->m_bAutoJump = false;
				}
			}
			
		   	m_pBtApp->setStringById(CONTROLID_BLUETOOTH_MAIN_CALL_IN_OR_OUT, STRINGID_BT_CALL_OUT);
			setToHalMobileStatus(2);
			m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_CALL_OUT,true,true,m_pBtParam->m_strTemOutName,m_pBtParam->m_strTemOutNum);
		}
		break;
		case BT_PHONE_STATUS_TALKING:
		{
			if(m_pBtApp->getPlayRingStatus())
				m_pBtModule->btToModule_NotifyCenter_StopRing();
			m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(false,NULL);

			//m_pBtApp->m_pBtMainPage->refreshBTManyCallInfo(1);
			
			setToHalMobileStatus(3);
			m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_TALKING,true,true,m_pBtParam->cStrCallPeopleName,m_pBtParam->szPhoneNumCallInOrOut);
		}
		break;
		default:
		break;
	}
			
	switch(e)
	{
		case BT_PHONE_STATUS_FREE:
		case BT_PHONE_STATUS_CALL_IN:
		case BT_PHONE_STATUS_CALL_OUT:
		case BT_PHONE_STATUS_TALKING: 
			m_pBtParam->emTempHfpPhoneStatus = e;
		break;
	}

	m_pBtApp->m_pBtMainPage->DisplayInputDialPhoneTextPrompt(e);
	m_pBtApp->m_pBtMainPage->refreshAnswerHandup(e);

	
	m_pBtModule->btToModule_NotifyAUXScreen_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus); //AUXScreen BT Phone State
	m_pBtModule->btToModule_NotifyBackVideo_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->btToModule_NotifyAudiovideo_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->btToModule_NotifySystem_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtApp->btToApp_SendBtPhoneState((u8)m_pBtParam->m_ePhoneStatus);
    m_pBtModule->golf_sendToCarScreen_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->golf_sendToCarScreen_PhoneNumInTheSpecialState((u8)m_pBtParam->m_ePhoneStatus, (u8*)m_pBtParam->szPhoneNumCallInOrOut, strlen(m_pBtParam->szPhoneNumCallInOrOut));
}

void CBtHal::clearAfterHandup()
{
	m_pBtApp->setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT1, (u8*)"", 0);
	m_pBtApp->setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT2, (u8*)"", 0);
	m_pBtApp->setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT3, (u8*)"", 0);
	m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(false,0);
		
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(""), 0);
	m_pBtApp->setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,false);
		
       m_pBtApp->m_pBtMainPage->DisplayInputDialPhoneTextPrompt(BT_PHONE_STATUS_FREE);
	clearPhoneNumInput();
	memset(m_pBtParam->m_strTemOutNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_pBtParam->m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
}

void CBtHal::clearPhoneNumInput()
{
	memset(&(m_pBtParam->m_stPhoneNumInput), 0, sizeof(ST_PHONE_NUM));
	memset(&(m_pBtParam->m_stPhoneNumCallIn), 0, sizeof(ST_PHONE_NUM));
	m_pBtApp->m_pBtMainPage->refreshPhoneNumInput((char*)"", 0);
}

void CBtHal::setToHalMobileStatus( int callStatus )
{
	LOGD("[%s] callStatus:%d",__FUNCTION__,callStatus);
	unsigned char buf[]={0xA0,0x00};
	buf[1]=callStatus;
	makeAndSendMessageToHal(HAL_ID_BT,buf,2);
}

void CBtHal::getHfpPhoneNumCallInOrOut(E_BT_PHONE_STATUS e,char *pNo, int len)
{
	m_pBtParam->emPhoneStatusBallon = e;
	int rlen = len;
	if(rlen < 0)
		return;
	
	memset(m_pBtParam->m_strFirstCallNum, 0, PHONE_NUm_nNPUT_MAX_SIZE);
	memcpy(m_pBtParam->m_strFirstCallNum, pNo, rlen);
	memset(m_pBtParam->szPhoneNumCallInOrOut, 0, PHONE_NUm_nNPUT_MAX_SIZE);
	memcpy(m_pBtParam->szPhoneNumCallInOrOut, pNo, rlen);

	ST_PHONE_NUM phoneNum;	
	memset(&phoneNum,0,sizeof(ST_PHONE_NUM));
	memcpy(phoneNum.szcPhoneNum,m_pBtParam->szPhoneNumCallInOrOut,strlen(m_pBtParam->szPhoneNumCallInOrOut));

	getPhoneCallinOrCalloutPeopleName(m_pBtParam->szPhoneNumCallInOrOut);
	phoneNum.dwLen=strlen(m_pBtParam->szPhoneNumCallInOrOut);

	memcpy(phoneNum.szcName,m_pBtParam->cStrCallPeopleName,strlen(m_pBtParam->cStrCallPeopleName));
	m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(true,&phoneNum);

	m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(phoneNum.szcPhoneNum, phoneNum.dwLen);

}

void CBtHal::getPhoneCallinOrCalloutPeopleName(char *pnum)
{
	int n = strlen(pnum);
	int s = m_pBtParam->m_listPhoneBook.size();
	memset(m_pBtParam->cStrCallPeopleName,0,sizeof(m_pBtParam->cStrCallPeopleName));
	if(s < 1 || n < 1)
		return;
	LOGD("[%s]pnum=%s  n=%d",__FUNCTION__,pnum,n);
	
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itFrom = m_pBtParam->m_listPhoneBook.begin();
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itTo = m_pBtParam->m_listPhoneBook.end();
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator it;
	for (it = itFrom; it != itTo; it++)
	{
		if((strncmp(it->szUserNo,pnum,n) == 0) && (strlen(it->szUserNo) == n))
		{
			memcpy(m_pBtParam->cStrCallPeopleName,it->szUserName,strlen(it->szUserName));
			m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(m_pBtParam->cStrCallPeopleName), strlen(m_pBtParam->cStrCallPeopleName));
			m_pBtApp->setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);
			return;
		}
	}
}
/************************************************/
void CBtHal::getCallName(char *input_Num,char *out_Name)
{
	int n = strlen(input_Num);
	int s = m_pBtParam->m_listPhoneBook.size();
	memset(m_pBtParam->cStrCallPeopleName,0,sizeof(m_pBtParam->cStrCallPeopleName));
	if(s < 1 || n < 1)
		return;
	LOGD("[%s]input_Num=%s  n=%d",__FUNCTION__,input_Num,n);
	
	if(!searchNameAtPhoneBook(input_Num,out_Name))
	{
		if(strlen(out_Name) == 0)
		{
			if(m_pBtParam->nNationalDistinction == NATIONAL_ISRAEL)
			{
				char tempszUserNo[CALL_HISTORY_NUMBER_MAX_LEN];
				memset(tempszUserNo,0,CALL_HISTORY_NUMBER_MAX_LEN);
				if(!strncmp(input_Num,"0",1))
				{
					memcpy(tempszUserNo,"+972",4);
					memcpy(tempszUserNo+4,(input_Num + 1),n-1);
				}
				else if(!strncmp(input_Num,"+972",4))
				{
					memcpy(tempszUserNo,"0",1);
					memcpy(tempszUserNo+1,(input_Num + 4),n-4);
				}
				LOGD("[%s]tempszUserNo=%s  n=%d",__FUNCTION__,tempszUserNo,strlen(tempszUserNo));
				searchNameAtPhoneBook(tempszUserNo,out_Name);
			}	
		}
	}

}

bool CBtHal::searchNameAtPhoneBook(char *input_Num,char *out_Name)
{
	bool bTag = false;
	int n = strlen(input_Num);
	int s = m_pBtParam->m_listPhoneBook.size();
	int y = m_pBtParam->m_listHistoryCall.size();

	if(s >= 1)
	{
		list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itFrom = m_pBtParam->m_listPhoneBook.begin();
		list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itTo = m_pBtParam->m_listPhoneBook.end();
		list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator it;
		for (it = itFrom; it != itTo; it++)
		{
			if((strncmp(it->szUserNo,input_Num,n) == 0) && (strlen(it->szUserNo) == n))
			{
				memcpy(out_Name,it->szUserName,strlen(it->szUserName));
				bTag = true;
				break;
			}
		}
	}
	
	if(strlen(out_Name) == 0)
	{
		if(y >= 1)
		{
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = m_pBtParam->m_listHistoryCall.begin();
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = m_pBtParam->m_listHistoryCall.end();
			list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
			for (it = itFrom; it != itTo; it++)
			{
				if((strncmp(it->szUserNo,input_Num,n) == 0) && (strlen(it->szUserNo) == n))
				{
					memcpy(out_Name,it->szUserName,strlen(it->szUserName));
					bTag = true;
					break;
				}
			}
		}
	}

	return bTag;
}

void CBtHal::getHfpDialingTransferPosStatus(E_BT_PHONE_STATUS e)
{
	switch(e)
	{
		case BT_PHONE_STATUS_RECEIVE_BULETOOTH:
		{
			m_pBtHal->getHfpAudioSource(HFP_AUDIO_SOURCE_BT);
			m_pBtApp->m_pBtMainPage->refreshBTAudioFromFlyDeviceOrFromMobile(2);
		}
		break;
		case BT_PHONE_STATUS_RECEIVE_PHONE:
		{
			m_pBtHal->getHfpAudioSource(HFP_AUDIO_SOURCE_MOBILE);
			m_pBtApp->m_pBtMainPage->refreshBTAudioFromFlyDeviceOrFromMobile(1);
		}
		break;
		default:break;
	}
}

void CBtHal::getHfpAudioSource(E_HFP_AUDIO_SOURCE e)
{
	m_pBtParam->m_eHfpAudioSource = e;
}

void CBtHal::getHfpMicStatus(bool state)
{
	m_pBtParam->muteSwicthState = state;
	m_pBtApp->m_pBtMainPage->DisplayingMuteButtonState();
}

void CBtHal::GetA2DPPlayOrStopState_switch(char state)
{
	u16  nCurSoundMode = 0;
	u8	nCurSoundModelen = 0;
	m_pBtModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8*)&nCurSoundMode,&nCurSoundModelen);

	if(state == 2)
	{
		if(nCurSoundMode == 0x0d)
		{
			g_pClsBtAdapter->A2dpAudioOutputCtrlSwitch(0x01);
		}
	}

	if(state == 2 && m_pBtParam->m_bIsA2dpOnPlayState == false)
	{
		if(nCurSoundMode != 0x0d)
		{
			m_pBtParam->bNoA2dpChannelPlay = true;
		}
	}	
	
	getA2DPPlayOrStopStatus(state);
}

void CBtHal::getA2DPPlayOrStopStatus(char state)
{
	m_pBtModule->sendToFlyJNiSdkBtMusicStatus(state);
	if (state == 1)
	{
		m_pBtParam->m_bIsA2dpOnPlayState = false;
		m_pBtParam->bNoA2dpChannelPlay = false;
	}
	else
	{
		m_pBtParam->m_bIsA2dpOnPlayState = true;
	}
}

void CBtHal::getA2DPInfo(char *singName,int singNameLen,char* author,int authorLen,char* album,int singAlbumLen)
{
	memset(m_pBtParam->musicAuthor,0,sizeof(m_pBtParam->musicAuthor));
	memset(m_pBtParam->musicName,0,sizeof(m_pBtParam->musicName));
	memset(m_pBtParam->musicAlbum,0,sizeof(m_pBtParam->musicAlbum));

	if(authorLen != 0)
	memcpy(m_pBtParam->musicAuthor,author,authorLen);

	if(singNameLen != 0)
	memcpy(m_pBtParam->musicName,singName,singNameLen);

	if(singAlbumLen != 0)
	memcpy(m_pBtParam->musicAlbum,album,singAlbumLen);

	m_pBtModule->sendToFlyJniSdkBtMusicSong( singName,singNameLen);
	m_pBtModule->sendToFlyJniSdkBtMusicSonger( author,authorLen);
	
	m_pBtApp->m_pA2DPpages->displyA2DPInfo();
}

void CBtHal::new_getA2DPStatus(u8 b)
{
	if(m_pBtParam->m_bSupport_A2DP == b)
		return;
	//if(m_pBtParam->m_eHfpConnectStatus  != HFP_CONNECT_STATUS_CONNECTED)
	//	return;
	m_pBtParam->m_bSupport_A2DP = b;
	m_pBtModule->sendToFlyJNiSdkBtSupportA2DP(b);
	u16 CurPageID = m_pBtModule->getCurPageId();
	if(b)
	{
		u16 PrePageID = m_pBtModule->getPrePageId();
		u16  nCurSoundMode = 0;
		u8  nCurSoundModelen = 0;
		m_pBtModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8*)&nCurSoundMode,&nCurSoundModelen);
		if((CurPageID == PAGE_BLUETOOTH_NO_A2DP) || (CurPageID == PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME && (PrePageID == PAGE_BLUETOOTH_NO_A2DP || PrePageID == PAGE_BLUETOOTH_A2DP)))
		{
			m_pBtParam->bA2DP_To_DevicePageBackButton = false;
			m_pBtModule->setPage(PAGE_BLUETOOTH_A2DP);
			return;	
		}
		if(nCurSoundMode == 0x0d && (CurPageID != PAGE_BLUETOOTH_A2DP && CurPageID != PAGE_BLUETOOTH_NO_A2DP))
		{
			m_pBtParam->bA2DP_To_DevicePageBackButton = false;
		}
	}
	else{
		if(CurPageID == PAGE_BLUETOOTH_A2DP){
			m_pBtModule->setPage(PAGE_BLUETOOTH_NO_A2DP);
		}
		m_pBtParam->curIsFolder = 0;
		m_pBtParam->m_TheFolderlistSongBrowsing.clear();
		m_pBtParam->m_theSongs.clear();
		m_pBtApp->m_pMusicBrowsingPage->ClearPlaylistsText();
	}
}

void CBtHal::new_initParamAfterA2DPConnected()
{	
	g_pClsBtAdapter->requestBtPlayStatus();
	g_pClsBtAdapter->requestBtMusicInfo();
	g_pClsBtAdapter->requestBtPlayModeStatus();
	u16  nCurSoundMode = 0;
	u8  nCurSoundModelen = 0;
	m_pBtModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8*)&nCurSoundMode,&nCurSoundModelen);
	printf("[BT] %s CurSoundMode:%x \n",__FUNCTION__,nCurSoundMode);
	if(nCurSoundMode == 0x0d)
		{
			m_pBtApp->m_pA2DPpages->setA2DPPlay();
		}
}

void CBtHal::new_getPhoneBookAndRecord(u8 b)
{	
	g_pClsBtAdapter->requestBtPhoneBook(b);
}

void CBtHal::PhonebookDownloadFinish(void)
{
	getLoadPhoneBookFinishStatus();	
	m_pBtApp->m_pBtPhoneBookPages->getAllPhoneBookLoadDone();
	m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(0);
}

void CBtHal::getLoadPhoneBookFinishStatus(void)
{
  	m_pBtApp->m_pBtPhoneBookPages->m_bIsLoadingPhoneBook=false;
}

void CBtHal::AnalyzeContactsExtendedName(char *strParam1_In)
{
	int nContactNameLen = strlen(strParam1_In);
	InitContactsExtendedNameParamValue();
	if((nContactNameLen == 4 && strcmp(strParam1_In,";;;;") == 0) || (nContactNameLen == 1 && strcmp(strParam1_In,";") == 0))
    {
	    return;
    }

	m_pBtParam->extended_Infor.PBName_CompleteTotal_Len  = nContactNameLen;

	
	int nTo_Pre = g_pClsBtAdapter->Inside_FindIndexFromStr((u8 *)strParam1_In,nContactNameLen, ';',0);
	if(nTo_Pre < 0)
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Prefix,strParam1_In,nContactNameLen);
		m_pBtParam->extended_Infor.PBName_Prefix_Len= nContactNameLen;
		return;
	}
	else if(nTo_Pre == 0)
	{
	}
	else
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Prefix,strParam1_In,nTo_Pre);
		m_pBtParam->extended_Infor.PBName_Prefix_Len= nTo_Pre;
	}
	if(nTo_Pre + 1 == nContactNameLen)
	{
		return;
	}

	int nTo_First = g_pClsBtAdapter->Inside_FindIndexFromStr((u8 *)strParam1_In,nContactNameLen, ';', nTo_Pre+1);
	if(nTo_First < 0)
	{
		memcpy(m_pBtParam->extended_Infor.PBName_First,strParam1_In+nTo_Pre+1,nContactNameLen-nTo_Pre-1);
		m_pBtParam->extended_Infor.PBName_First_Len = nContactNameLen-nTo_Pre-1;
		
		return;
	}
	else if(nTo_First == nTo_Pre +1)
	{
	}
	else 
	{
		memcpy(m_pBtParam->extended_Infor.PBName_First,strParam1_In+nTo_Pre+1,nTo_First -nTo_Pre - 1);
		m_pBtParam->extended_Infor.PBName_First_Len = nTo_First -nTo_Pre - 1;
	}
	
	int nTo_Mid = g_pClsBtAdapter->Inside_FindIndexFromStr((u8 *)strParam1_In,nContactNameLen, ';',nTo_First + 1);
	if(nTo_Mid < 0)
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Mid,strParam1_In + nTo_First + 1,nContactNameLen - nTo_First - 1);
		m_pBtParam->extended_Infor.PBName_Mid_Len = nContactNameLen - nTo_First - 1;

		return;
	}
	else if(nTo_Mid == nTo_First+1)
	{
	}
	else
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Mid,strParam1_In + nTo_First + 1,nTo_Mid - nTo_First - 1);
		m_pBtParam->extended_Infor.PBName_Mid_Len = nTo_Mid - nTo_First - 1;
	}

	int nTo_Last = g_pClsBtAdapter->Inside_FindIndexFromStr((u8 *)strParam1_In,nContactNameLen, ';', nTo_Mid+1);
	if(nTo_Last < 0)
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Last,strParam1_In+nTo_Mid+1,nContactNameLen-nTo_Mid-1);
		m_pBtParam->extended_Infor.PBName_Last_Len = nContactNameLen-nTo_Mid-1;

		return;
	}
	else if(nTo_Last == nTo_Mid+1)
	{
	}
	else
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Last,strParam1_In+nTo_Mid+1,nTo_Last -nTo_Mid - 1);
		m_pBtParam->extended_Infor.PBName_Last_Len = nTo_Last-nTo_Mid-1;
	}
	if(nContactNameLen == nTo_Last + 1)
	{
	}
	else
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Suffix,strParam1_In+nTo_Last + 1,nContactNameLen - nTo_Last - 1);
		m_pBtParam->extended_Infor.PBName_Suffix_Len= nContactNameLen - nTo_Last - 1;
	}
	
}
void CBtHal::InitContactsExtendedNameParamValue(void)
{
	m_pBtParam->extended_Infor.PBName_CompleteTotal_Len = 0;
	
	memset(m_pBtParam->extended_Infor.PBName_Prefix,0,PHONENUM_OR_PHONENAME_MAX_LEN);
	m_pBtParam->extended_Infor.PBName_Prefix_Len = 0;

	memset(m_pBtParam->extended_Infor.PBName_First,0,PHONENUM_OR_PHONENAME_MAX_LEN);
	m_pBtParam->extended_Infor.PBName_First_Len = 0;
	
	memset(m_pBtParam->extended_Infor.PBName_Mid,0,PHONENUM_OR_PHONENAME_MAX_LEN);
	m_pBtParam->extended_Infor.PBName_Mid_Len = 0;
	
	memset(m_pBtParam->extended_Infor.PBName_Last,0,PHONENUM_OR_PHONENAME_MAX_LEN);
	m_pBtParam->extended_Infor.PBName_Last_Len = 0;
	
	memset(m_pBtParam->extended_Infor.PBName_Suffix,0,PHONENUM_OR_PHONENAME_MAX_LEN);
	m_pBtParam->extended_Infor.PBName_Suffix_Len = 0;
}

void CBtHal::ToUI_FormalityOfContacts(char *strParam1_out)
{
	strcpy(strParam1_out,"");
	if(m_pBtParam->extended_Infor.PBName_CompleteTotal_Len == 0)
	{
		return;
	}

	int nLen1 = m_pBtParam->extended_Infor.PBName_Prefix_Len;
	int nLen2 = m_pBtParam->extended_Infor.PBName_First_Len;
	int nLen3 = m_pBtParam->extended_Infor.PBName_Mid_Len;
	int nLen4 = m_pBtParam->extended_Infor.PBName_Last_Len;
	int nLen5 = m_pBtParam->extended_Infor.PBName_Suffix_Len;
	int nStrParam1_out_len = 0;
	
	LOGD("[%s] m_pBtParam->m_nBtLanguageType:%d",__FUNCTION__,m_pBtParam->m_nBtLanguageType);
	char cSpace[1] = {' '};
	
    if(m_pBtParam->m_nBtLanguageType == 0)//If the language is chinese,contacts's name don't change and is not blank.
    {
	    	if(nLen1 != 0){
	    		memcpy(strParam1_out,m_pBtParam->extended_Infor.PBName_Prefix,sizeof(m_pBtParam->extended_Infor.PBName_Prefix));
				nStrParam1_out_len = nLen1;
	    	}
			if(nLen2 != 0){
				if(nStrParam1_out_len != 0){
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_First,sizeof(m_pBtParam->extended_Infor.PBName_First));
					nStrParam1_out_len = nStrParam1_out_len+nLen2;
				}
				else
				{
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_First,sizeof(m_pBtParam->extended_Infor.PBName_First));
					nStrParam1_out_len = nLen2;
				}
			}

			if(nLen3 != 0)
			{
				if(nStrParam1_out_len != 0){
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Mid,sizeof(m_pBtParam->extended_Infor.PBName_Mid));
					nStrParam1_out_len = nStrParam1_out_len+nLen3;
				}
				else
				{
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Mid,sizeof(m_pBtParam->extended_Infor.PBName_Mid));
					nStrParam1_out_len = nLen3;
				}
			}
			if(nLen4 != 0)
			{
				if(nStrParam1_out_len != 0){
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Last,sizeof(m_pBtParam->extended_Infor.PBName_Last));
					nStrParam1_out_len = nStrParam1_out_len+nLen4;
				}
				else
				{
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Last,sizeof(m_pBtParam->extended_Infor.PBName_Last));
					nStrParam1_out_len = nLen4;
				}
			}
			if(nLen5 != 0)
			{
				if(nStrParam1_out_len != 0){
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Suffix,sizeof(m_pBtParam->extended_Infor.PBName_Suffix));
					nStrParam1_out_len = nStrParam1_out_len+nLen5;
				}
				else
				{
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Suffix,sizeof(m_pBtParam->extended_Infor.PBName_Suffix));
					nStrParam1_out_len = nLen5;
				}
			}
			deleteSpecialCharacters(strParam1_out,' ');
    }
    else//Other Languages
    {
		 	if(nLen1 != 0){
				memcpy(strParam1_out,m_pBtParam->extended_Infor.PBName_Prefix,sizeof(m_pBtParam->extended_Infor.PBName_Prefix));
				nStrParam1_out_len = nLen1;
			}
			
			if(nLen4 != 0)
			{
				if(nStrParam1_out_len != 0){
					strncat(strParam1_out,cSpace,sizeof(cSpace));
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Last,sizeof(m_pBtParam->extended_Infor.PBName_Last));
					nStrParam1_out_len = nStrParam1_out_len+nLen4;
				}
				else
				{
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Last,sizeof(m_pBtParam->extended_Infor.PBName_Last));
					nStrParam1_out_len = nLen4;
				}
			}
			if(nLen3 != 0)
			{
				if(nStrParam1_out_len != 0){
					strncat(strParam1_out,cSpace,sizeof(cSpace));
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Mid,sizeof(m_pBtParam->extended_Infor.PBName_Mid));
					nStrParam1_out_len = nStrParam1_out_len+nLen3;
				}
				else
				{
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Mid,sizeof(m_pBtParam->extended_Infor.PBName_Mid));
					nStrParam1_out_len = nLen3;
				}
			}
			if(nLen2 != 0){
				if(nStrParam1_out_len != 0){
					strncat(strParam1_out,cSpace,sizeof(cSpace));
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_First,sizeof(m_pBtParam->extended_Infor.PBName_First));
					nStrParam1_out_len = nStrParam1_out_len+nLen2;
				}
				else
				{
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_First,sizeof(m_pBtParam->extended_Infor.PBName_First));
					nStrParam1_out_len = nLen2;
				}
			}
			if(nLen5 != 0)
			{
				if(nStrParam1_out_len != 0){
					strncat(strParam1_out,cSpace,sizeof(cSpace));
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Suffix,sizeof(m_pBtParam->extended_Infor.PBName_Suffix));
					nStrParam1_out_len = nStrParam1_out_len+nLen5;
				}
				else
				{
					strncat(strParam1_out,m_pBtParam->extended_Infor.PBName_Suffix,sizeof(m_pBtParam->extended_Infor.PBName_Suffix));
					nStrParam1_out_len = nLen5;
				}
			}
    }
}

void CBtHal::getPhoneBookOneItem(char *pUserName, int userNameLen, char *pUserNo, int userNoLen)
{
	LOGD("[BT] [getPhoneBookOneItem] [%s (%d)]   [%s (%d)]\n",pUserName,userNameLen,pUserNo,userNoLen);
	
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itFrom = m_pBtParam->m_listPhoneBook.begin();
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itTo = m_pBtParam->m_listPhoneBook.end();
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator it;
	for (it = itFrom; it != itTo; it++)
	{
		if(!(strncmp(it->szUserNo,pUserNo,userNoLen)) && (strlen(it->szUserNo) == userNoLen))
			return;
	}
	ST_PHONE_BOOK_ONE_USER_INFO t;
	memset(&t, 0, sizeof(ST_PHONE_BOOK_ONE_USER_INFO));

	memcpy(t.szUserName, pUserName, userNameLen);
	memcpy(t.szUserNo, pUserNo, userNoLen);

	m_pBtParam->m_listPhoneBook.push_back(t);
}
void CBtHal::clearAfterHfpPowerOff()
{
	clearHistoryAfterHFPDisconnect();
	setDefaultParamAfterHfpPowerOff();
	clearPhoneNumInput();
	new_getA2DPStatus(false);
	m_pBtApp->m_pBtMainPage->DisplayingMuteButtonState();
	m_pBtModule->btToApp_SendConnectState(0);
	m_pBtParam->m_listBtDevicesHavePaired.clear();			
	m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired(0);
	m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired_New(0);
	FormatBtMacAddress((char*)"",0);
	m_pBtParam->m_tempListHistoryCall.clear();
}

void CBtHal::setDefaultParamAfterHfpPowerOff()
{
	m_pBtParam->muteSwicthState = false;
	m_pBtParam->m_eHfpConnectStatus = HFP_CONNECT_STATUS_DISCONNECT;
	m_pBtParam->m_ePhoneStatus=BT_PHONE_STATUS_FREE;
	m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NO_BLUETOOTH,0);	
	m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DISABLE);
	m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_TURNED_OFF);
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE_TEXT,(u8*)"", 0);
	m_pBtApp->setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_NAME_TEXT,(u8*)"", 0);
	m_pBtApp->setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_MAC_TEXT,(u8*)"", 0);
	m_pBtParam->emTempHfpConnectStatus = HFP_CONNECT_STATUS_DISCONNECT;
	m_pBtParam->emTempHfpTalkingTransferSet = HFP_SET_UNKNOWN_SIDE;
	m_pBtParam->emTempHfpPhoneStatus = BT_PHONE_STATUS_FREE;
}

void CBtHal::initParamAfterHfpPowerOn()
{
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE_TEXT,(u8*)m_pBtParam->szLocalBtDevice_PinCode, strlen(m_pBtParam->szLocalBtDevice_PinCode));
	m_pBtApp->m_pBtDevicePages->clickDisplaySetDeviceNameToUi((u8*)m_pBtParam->szLocalBtDevice_Name,(u32)strlen(m_pBtParam->szLocalBtDevice_Name));
	m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NO_BLUETOOTH,1);
	if(m_pBtParam->m_listBtDevicesHavePaired.empty())
	{
		m_pBtApp->setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, (u8*)"", 0);
	}
	else
	{
		m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_DEVICE_IS_DISCONNECTED);
	}
}

void CBtHal::refreshParamAfterHFPConnected()
{
	m_pBtParam->m_listPhoneBook.clear();
	m_pBtParam->m_listHistoryCall.clear();

	m_pBtParam->m_listBtDevicesHavePaired.clear();
	m_pBtModule->btToApp_SendConnectState(1);
	m_pBtModule->ToOSDandAPPaboutConnectState(1);
	g_pClsBtJniSdk->sendToAppBtConnectStatus(0x01);
	m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_CONNECTED_DEVICES);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,1);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1,1);
	getHfpPhoneStatus(BT_PHONE_STATUS_FREE);
}

void CBtHal::clearHistoryAfterHFPDisconnect()
{
	setParamAfterHFPDisconnect();
	clearPhoneBookAndHistoryCall(); 
	clearAfterHandup();
	m_pBtApp->m_pBtMainPage->refreshBTAudioFromFlyDeviceOrFromMobile(0);
	m_pBtApp->m_pCallRecordPages->clearCallHistoryTypeStatus();
	m_pBtApp->m_pBtMainPage->refreshAnswerHandup(BT_PHONE_STATUS_FREE);
	m_pBtApp->m_pBtMainPage->refreshBTManyCallInfo(0);
	m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH);
	getHfpPhoneStatus(BT_PHONE_STATUS_FREE);
	m_pBtApp->m_pA2DPpages->clearA2DPInfo();
	m_pBtModule->btToModule_NotifyCenter_StopRing();
	g_pClsBtJniSdk->sendToAppBtConnectStatus(0x00);
	m_pBtHal->getA2DPPlayOrStopStatus(1);

	m_pBtModule->btToApp_SendConnectState(0);
	if(m_pBtParam->emTempHfpConnectStatus != m_pBtParam->m_eHfpConnectStatus)
		m_pBtModule->ToOSDandAPPaboutConnectState(0);
	
	m_pBtModule->golf_sendToCarScreen_PhoneConnState(0);
	new_getA2DPStatus(false);
	m_pBtModule->deleteNativeTimer(TIMER_DELAY_CONNECTION_DEVICE_PAGE_TIME);
	memset(m_pBtParam->selecteDeviceAddr,0,FLY_BT_PAIRING_ADDRS_MAX_LEN);
	m_pBtParam->selecteDeviceAddrLen = 0;
	m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(0);
	m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(0);
	g_pClsBtJniSdk->sendToAppBtPhoneStatus((u8)m_pBtParam->m_ePhoneStatus);
}

void CBtHal::setParamAfterHFPDisconnect()
{
	m_pBtParam->bHandleStopSearchState = true;
	m_pBtParam->bItsAddCalls = false;
	m_pBtApp->m_pBtMainPage->AddCallsToUI(m_pBtParam->bItsAddCalls);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_2,0);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,0);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1,0);
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_MAIN_CALL_IN_OR_OUT, (u8*)"",0);
	m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, STRINGID_BT_INPUT_PHONE_NUMBER);
	m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE,0);
	getCurConnectedBtDeviceName("", 0);
	if(m_pBtParam->m_bIsPowerOn == 1)
	{
		m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_DEVICE_IS_DISCONNECTED);
	}
	if(0==(m_pBtParam->m_listBtDevicesHavePaired).size() && m_pBtParam->m_bIsPowerOn == 1)
	{
		m_pBtApp->setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, (u8*)"", 0);
	}
	m_pBtParam->bNoA2dpChannelPlay = false;
	m_pBtParam->bIsPairBox = false;
	memset(m_pBtParam->szRemodeBtDeviceHasConnectedAddr, 0, sizeof(m_pBtParam->szRemodeBtDeviceHasConnectedAddr));
	//m_pBtParam->m_bSupport_A2DP = false;
}

void CBtHal::getCurConnectedBtDeviceName(char *p, int len)
{
	memset(m_pBtParam->szRemodeBtDeviceHasConnectedName, 0, sizeof(m_pBtParam->szRemodeBtDeviceHasConnectedName));
	if(len != 0){
		memcpy(m_pBtParam->szRemodeBtDeviceHasConnectedName, p, len);
	}
	
	m_pBtModule->sendToFlyJniSdkRemoteDeviceName(p, len);
	m_pBtApp->m_pBtMainPage->refreshRemodeBtDeviceName((u8 *)p,(u32)len);
	m_pBtModule->btToModule_golf_phoneName((u8*)p, len);
}

void CBtHal::clearPhoneBookAndHistoryCall()
{

	m_pBtParam->m_listPhoneBook.clear();
	m_pBtParam->m_listHistoryCall.clear();
	m_pBtParam->m_listHistoryCall_Miss.clear();		 
	m_pBtParam->m_listHistoryCall_Dialed.clear();	
	m_pBtParam->m_listHistoryCall_Riceived.clear();

	
	m_pBtApp->m_pBtPhoneBookPages->m_mapPhoneNumUserInfo.clear();//utf8
	m_pBtApp->m_pBtPhoneBookPages->m_listPhoneNumUserInfoHaveSelected.clear();

	m_pBtApp->m_pBtPhoneBookPages->m_mapPhoneNumRankUserInfo.clear();//utf8
	m_pBtApp->m_pBtPhoneBookPages->m_listPhoneNumRankUserInfoHaveSelected.clear();
	m_pBtApp->m_pBtPhoneBookPages->m_listPhoneNumAccurateSearch.clear();
		
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_2 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_3 , (u8*)"", 0);

	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NUM_1 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NUM_2 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NUM_3 , (u8*)"", 0);

	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_2 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_3 , (u8*)"", 0);
	
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NUM_1 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NUM_2 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NUM_3 , (u8*)"", 0);

	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_2 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_3 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_4 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_5 , (u8*)"", 0);
	
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_2 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_3 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_4 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_5 , (u8*)"", 0);

	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_1 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_2 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_3 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_4 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_5 , (u8*)"", 0);
	
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_1 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_2 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_3 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_4 , (u8*)"", 0);
	m_pBtApp->setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_5 , (u8*)"", 0);

	for(int r=0;r<SEARCH_LIST_DISPLAY_NUM;r++)
	{
		m_pBtApp->m_pCallRecordPages->setDataToUI_bt_aboutCallLogName_Displaying( r, (char *)"");
		m_pBtApp->m_pCallRecordPages->setDataToUI_bt_aboutCallLogNumber_Displaying(r,(char *)"");
		m_pBtApp->m_pCallRecordPages->setDataToUI_bt_aboutCallLogCallTime_Displaying(r,(char *)"");
		m_pBtApp->m_pCallRecordPages->setDataToUI_bt_aboutCallLogClassIcon_Displaying(r,0);
	}
	for(int r=0;r<SEARCH_LIST_DISPLAY_NUM_NEW;r++)
	{
		m_pBtApp->m_pCallRecordPages->setDataToUI_bt_aboutCallLogName_Displaying_New( r, (char *)"");
		m_pBtApp->m_pCallRecordPages->setDataToUI_bt_aboutCallLogNumber_Displaying_New(r,(char *)"");
		m_pBtApp->m_pCallRecordPages->setDataToUI_bt_aboutCallLogCallTime_Displaying_New(r,(char *)"");
		m_pBtApp->m_pCallRecordPages->setDataToUI_bt_aboutCallLogClassIcon_Displaying_New(r,0);
	}
	
}

void CBtHal::deleteSpecialCharacters(char *str,char ch)
{
    char * p=str;
    int i=0;
    while( (*p) != 0 ){ 
        if((*p) != ch){
            str[i++]=*p;
        }  
        p++;   
    }  
    str[i]=0;
}

void CBtHal::setToHalInit(void)
{
	m_pBtModule->deleteNativeTimer(TIMER_ACC_ON_BT_INIT);
	m_pBtModule->setNativeTimer(5000,1,TIMER_ACC_ON_BT_INIT);
	//g_pClsBtAdapter->btInitCommand();
}

void CBtHal::new_initParamAfterHFPConnected()
{	
	new_getPhoneBookAndRecord(0x01);
	g_pClsBtAdapter->requestBtPairRecord();
}

void  CBtHal::new_getpairDeviceRecord(u8 *p,int len)
{
	char szAddr[FLY_BT_PAIRING_ADDRS_MAX_LEN];
	memset(szAddr,0,sizeof(szAddr));
	
	char szName[FLY_BT_PAIRING_NAME_MAX_LEN];
	memset(szName,0,sizeof(szName));
	int nSzNameLen = 0;
	int nSzAddrLEn = 0;

	int index = p[0];

	int nTo = g_pClsBtAdapter->Inside_FindIndexFromStr(p+2, len, 0xFF, 0);
	printf("[BT] nameLen: %d\n",nTo);
	if(nTo > 0)
	{
		nSzNameLen = nTo;
		memcpy(szName, p + 2, nSzNameLen);
	}
	nSzAddrLEn = len -2 -nSzNameLen - 1;
	memcpy(szAddr, p + 2 + nSzNameLen +1,nSzAddrLEn);
	
	if(nSzNameLen > FLY_BT_PAIRING_NAME_MAX_LEN)
		nSzNameLen = FLY_BT_PAIRING_NAME_MAX_LEN;
	new_getBtDeviceHasPaired(index, szAddr,nSzAddrLEn, szName, nSzNameLen);		
}
void CBtHal::new_getPhoneBookLoadState(char p,char tag)
{
	switch(p)
		{
			case 0x00:
				{
					printf("[BT] book start load!!\n");
					if(tag == 0x01)
					{
						if(m_pBtParam->m_listHistoryCall.size() == 0)
						{
							m_pBtApp->m_pBtPhoneBookPages->refreshLoadPhoneBookStatus(0x01);
							m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(1);
							m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(1);
						}
					}
					else if(tag == 0x00)
						m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(1);
				}
				break;
			case 0x01:
				{
					if(tag == 0x01)
						m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(0);
					else if(tag == 0x00)
						m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(0);
				}
			case 0x02:
				{
					if(tag == 0x00)//phonebook finish
					{
						m_pBtHal->PhonebookDownloadFinish();
						m_pBtApp->SendPhoneNumToAppEndTag();
						if(m_pBtParam->m_listPhoneBook.size() != 0)
							g_pClsBtJniSdk->sendToAppPhoneBookInfo();
					}
					else if(tag == 0x01)//records finish
					{
						m_pBtApp->m_pCallRecordPages->createListHistoryCall();	
		 				m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(0);
						if(m_pBtParam->m_listPhoneBook.size() == 0)
							new_getPhoneBookAndRecord(0x00);
					}
				}
				break;
			case 0x03:
				{
					if(tag == 0x00)
					{
						new_getPhoneBookAndRecord(0x00);
					}
					else if(tag == 0x01)
					{
						new_getPhoneBookAndRecord(0x01);
					}
				}
			default:
				break;
		}
}


void CBtHal::new_CreatePhoneBookList(char *p,int len)
{
	char szUserName[PHONENUM_OR_PHONENAME_MAX_LEN];
	int nUserNameLen = 0;
	char szUserNo[PHONENUM_OR_PHONENAME_MAX_LEN];
	int nUserNoLen = 0;
	memset(szUserName,0,sizeof(szUserName));
	memset(szUserNo,0,sizeof(szUserNo));

	int nFF = g_pClsBtAdapter->findCharIndex((unsigned char*)p, len, 0xFF);
	if (-1 != nFF && 0 != nFF)
	{
		char szTemName[PHONENUM_OR_PHONENAME_MAX_LEN];
		int nTemNameLen = nFF;
		if(nTemNameLen > PHONENUM_OR_PHONENAME_MAX_LEN)
			nTemNameLen = PHONENUM_OR_PHONENAME_MAX_LEN;
		
		memset(szTemName,0,sizeof(szTemName));
		memcpy(szTemName,p,nTemNameLen);
		
		AnalyzeContactsExtendedName(szTemName);
		ToUI_FormalityOfContacts(szUserName);
		nUserNameLen = strlen(szUserName);
		int nFF1 = g_pClsBtAdapter->findCharIndex((unsigned char*)(p + nFF + 1), len  - nFF - 1, 0xFF);
		
		if (-1 != nFF1 && 0 != nFF1)
		{
			nUserNoLen = nFF1 ;
			if(nUserNoLen > PHONENUM_OR_PHONENAME_MAX_LEN)
				nUserNoLen = PHONENUM_OR_PHONENAME_MAX_LEN;
			memcpy(szUserNo, p + nFF + 1, nUserNoLen);

			char szPhoneBooks[256];
			memset(szPhoneBooks,0,sizeof(szPhoneBooks));
			memcpy(szPhoneBooks,p,nFF+nFF1+1);
			m_pBtApp->SendPhoneNumToApp(szPhoneBooks,strlen(szPhoneBooks));

			if(nFF <= 4)
			{
				memset(szUserName,0,sizeof(szTemName));
				memcpy(szUserName,szUserNo,nUserNoLen);
				nUserNameLen = nUserNoLen;
			}
			
			getPhoneBookOneItem(szUserName, nUserNameLen, szUserNo, nUserNoLen);
			m_pBtApp->m_pBtPhoneBookPages->getPhoneNumDetailInfo(szUserName, nUserNameLen, szUserNo, nUserNoLen);
			InitContactsExtendedNameParamValue();
		}
	}
}
void CBtHal::new_CreateCallRecordList(char *p,int len)
{
	char type;
	char szUserName[CALL_HISTORY_NAME_MAX_LEN] = {0};
	int nUserNameLen = 0;
	char szUserNo[CALL_HISTORY_NUMBER_MAX_LEN] = {0};
		char time[CALL_HISTORY_TIME_MAX_LEN]={0};
	int nUserNoLen;
	int nUserTimeLen;
	switch(p[0])
	{
		case 0x02:
			type = '6';
		break;
		case 0x03:
			type = '5';
		break;
		case 0x04:
			type = '4';
		break;
		default:break;
	}
	int nFF1 = g_pClsBtAdapter->findCharIndex((unsigned char*)p + 2, len - 2, 0xFF);
	if (-1 != nFF1)
	{
		char szTemName[CALL_HISTORY_NAME_MAX_LEN];
		int nTemNameLen = nFF1;
		if(nTemNameLen > CALL_HISTORY_NAME_MAX_LEN)
			nTemNameLen = CALL_HISTORY_NAME_MAX_LEN;
		
		memset(szTemName,0,sizeof(szTemName));
		memcpy(szTemName,p + 2,nTemNameLen);

		AnalyzeContactsExtendedName(szTemName);
		ToUI_FormalityOfContacts(szUserName);
		InitContactsExtendedNameParamValue();
		nUserNameLen = strlen(szUserName);
		int nFF2 = g_pClsBtAdapter->findCharIndex((unsigned char*)(p + 2 + nFF1 + 1), len - 2 - nFF1 - 1, 0xFF);
		if(-1 != nFF2)
		{
			nUserNoLen = nFF2;
			if(nUserNoLen > CALL_HISTORY_NUMBER_MAX_LEN)
				nUserNoLen = CALL_HISTORY_NUMBER_MAX_LEN;
			
			memcpy(szUserNo, p + 2 + nFF1 + 1, nUserNoLen);
			nUserTimeLen = len - 2 - nFF1 - 1 - nFF2 - 1;
			if(nUserTimeLen < 0)
				return;
			
			if(nUserTimeLen > CALL_HISTORY_TIME_MAX_LEN)
				nUserTimeLen = CALL_HISTORY_TIME_MAX_LEN;			
			memcpy(time, p + 2 + nFF1 + 1 + nFF2 + 1, nUserTimeLen);
		}
		if(nUserNoLen < 3)
		{
			nUserNoLen = 7;
			memcpy(szUserNo, "Unknown", nUserNoLen);
		}
		m_pBtHal->GetHistoryCallOneItem(type,szUserName, nUserNameLen, szUserNo, nUserNoLen,time,nUserTimeLen);
		m_pBtApp->m_pCallRecordPages->showListHistoryCall();
	}
}

void CBtHal::new_getLocalBtDevicePinCode(char *p, int len)
{
	if(true == m_pBtParam->bInitState)
	{
		memset(m_pBtParam->szLocalBtDevice_PinCode, 0, sizeof(m_pBtParam->szLocalBtDevice_PinCode));
		memcpy(m_pBtParam->szLocalBtDevice_PinCode, p, len);

		printf("[BT] [new_getLocalBtDevicePinCode] p:%s\n",p);
		m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE_TEXT,(u8*)p, len);
	}
}

void CBtHal::getBtDeleteStatus(char *p,int len)
{
		int i = 0;
		list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
		list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

		for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
		{
			if(!strncmp((char *)it->deviceAddr,p,it->addrLen))
			{
				m_pBtParam->m_listBtDevicesHavePaired.erase(it);
				m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired(0);
				m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired_New(0);
				break;
			}
			i++;
		}
}

void CBtHal::GetA2dpAudioFucseState(u8 s)
{
	m_pBtModule->sendToAudiovideoBtA2dpAudioFocuse(s);
}
void CBtHal::GetHistoryCallOneItem(char type,char *pUserName, int userNameLen, char *pUserNo, int userNoLen,char *pUserTime,int userTimeLen)
{
	ST_CALL_RECORD_ONE_USER_INFO t;
	memset(&t, 0, sizeof(ST_CALL_RECORD_ONE_USER_INFO));
    	t.CBType=type;
	memcpy(t.szUserName, pUserName, userNameLen);
	memcpy(t.szUserNo, pUserNo, userNoLen);
	memcpy(t.CBTime, pUserTime, userTimeLen);
	
	long long int nTime = 0;
	sscanf(t.CBTime,"%lld",&nTime);
	if(userTimeLen < 4)
	{
		m_pBtParam->m_listHistoryCall.push_back(t);
	}
	else
	{
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall).begin();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall).end();
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;
		long long int nTime1 = 0;
		sscanf(itFrom->CBTime,"%lld",&nTime1);
		for (it = itFrom; it != itTo; it++)
		{
			long long int nTime2 = 0;
			sscanf(it->CBTime,"%lld",&nTime2);
			if(nTime2 == nTime)
			{
				return;
			}
		}
		if(nTime >nTime1)
		{
			m_pBtParam->m_listHistoryCall.push_front(t);
			m_pBtParam->FirOrBackTag  = true;
		}
		else
		{
			m_pBtParam->m_listHistoryCall.push_back(t);
			m_pBtParam->FirOrBackTag = false;
		}
	}
}

void CBtHal::setToHalBtPowerStatus(u8 p)
{
	u8 szMsg[2] = {0x10,p};
	makeAndSendMessageToHal(HAL_ID_BT,szMsg,2);
}

void CBtHal::saveCurConnectedBtDeviceAddr(char *p, int len)
{
	memset(m_pBtParam->szRemodeBtDeviceLastConnectedAddr, 0, sizeof(m_pBtParam->szRemodeBtDeviceLastConnectedAddr));
	memcpy(m_pBtParam->szRemodeBtDeviceLastConnectedAddr, p, len);
	m_pBtParam->saveLastConnectBtAddr();
}

void CBtHal::analyseSongInfo(char *p,int len)
{
	switch(p[0])
	{
		case 0x01:
		case 0x02:
		case 0x03:
		{
			static char songTitle[FLY_BT_MUSIC_INFOR_MAX_LEN];
			static char author[FLY_BT_MUSIC_INFOR_MAX_LEN];
			static char album[FLY_BT_MUSIC_INFOR_MAX_LEN];
			if(p[0] == 0x01)
			{
				memset(album,0,sizeof(album));
				memcpy(album,p + 1,len - 1);
				m_pBtHal->getA2DPInfo(songTitle,strlen(songTitle),author,strlen(author),album,strlen(album));
			}
			else if(p[0] == 0x02)
			{
				memset(author,0,sizeof(author));
				memcpy(author,p + 1,len - 1);
			}
			else if(p[0] == 0x03)
			{
				memset(songTitle,0,sizeof(songTitle));
				memcpy(songTitle,p + 1,len - 1);
			}
		}
		break;
		case 0xFF:
		{
			analyticalSongsDatas(p + 1,len -1);
		}
		break;
		default:
		break;
	}

}

void CBtHal::getCurPhoneStatusForHal(char *p,int len)
{
	if(p[0] == 0x00)
	{
		g_pClsBtJniSdk->sendToAppBtPhoneStatus(0x00);
		m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_FREE);
		list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it = (m_pBtParam->m_listHistoryCall).begin();
		if(strlen(it->CBTime))
			new_getPhoneBookAndRecord(0x01);
		if(m_pBtParam->muteSwicthState)
			m_pBtModule->btToModule_NotifyAudiovideo_BT_MicSwitch(0x00);
	}
	else if(p[0] == 0x01)
	{
		if(len > 1)
		{
			if(strncmp(m_pBtParam->m_strTemInNum,p + 1,len - 1))
			{
				memset(m_pBtParam->m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
				memcpy(m_pBtParam->m_strTemInNum, p + 1, len - 1);
				memset(m_pBtParam->m_strTemInName,0,PHONE_NUm_nNPUT_MAX_SIZE);
				m_pBtHal->getCallName(m_pBtParam->m_strTemInNum,m_pBtParam->m_strTemInName);
	
				m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_IN,p + 1, len - 1);
				m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_CALL_IN);	
			}
		}
		else if(len == 1)
		{
			memset(m_pBtParam->m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
			memcpy(m_pBtParam->m_strTemInNum, "unknown", 8);
			memset(m_pBtParam->m_strTemInName,0,PHONE_NUm_nNPUT_MAX_SIZE);
				
			m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_IN,"unknown", 8);
			m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_CALL_IN);
		}
		g_pClsBtJniSdk->sendToAppBtPhoneStatusAndNum(0x01,m_pBtParam->m_strTemInNum,strlen(m_pBtParam->m_strTemInNum),m_pBtParam->m_strTemInName,strlen(m_pBtParam->m_strTemInName));
	}
	else if(p[0] == 0x02)
	{
		if(len > 3)
		{
			if(strncmp(m_pBtParam->m_strTemOutNum,p + 1,len - 1))
			{
				memset(m_pBtParam->m_strTemOutNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
				memcpy(m_pBtParam->m_strTemOutNum, p + 1, len - 1);
				memset(m_pBtParam->m_strTemOutName,0,PHONE_NUm_nNPUT_MAX_SIZE);
				m_pBtHal->getCallName(m_pBtParam->m_strTemOutNum,m_pBtParam->m_strTemOutName);
				
				m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_OUT,p + 1, len - 1);
				g_pClsBtJniSdk->sendToAppBtPhoneStatusAndNum(0x02,m_pBtParam->m_strTemOutNum,strlen(m_pBtParam->m_strTemOutNum),m_pBtParam->m_strTemOutName,strlen(m_pBtParam->m_strTemOutName));
				m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_CALL_OUT);
			}
		}	
	}
	else if(p[0] == 0x03)
	{
		g_pClsBtJniSdk->sendToAppBtPhoneStatus(0x03);
		m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_TALKING);
		if(m_pBtParam->muteSwicthState)
			m_pBtModule->btToModule_NotifyAudiovideo_BT_MicSwitch(0x00);
	}
}

void CBtHal::delayConnectionDevicePage(void)
{
	m_pBtModule->deleteNativeTimer(TIMER_DELAY_CONNECTION_DEVICE_PAGE_TIME);
	m_pBtModule->setNativeTimer(1000,1,TIMER_DELAY_CONNECTION_DEVICE_PAGE_TIME);
}
