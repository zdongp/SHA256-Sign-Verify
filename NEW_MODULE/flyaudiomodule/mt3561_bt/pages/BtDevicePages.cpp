#include "BtDevicePages.h"

CBtDevicePages::CBtDevicePages(void)
{
}

CBtDevicePages::~CBtDevicePages(void)
{
}

//init
void CBtDevicePages::init(void)
{

}

void CBtDevicePages::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{
	m_pBtApp	 = (CBtApp *)pFlyApp; 
	m_pBtModule  = (CBtModule *)pFlyModule; 
	m_pBtHal	 = (CBtHal *)pFlyHal; 
	m_pBtParam   = (CBtParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;
}

void CBtDevicePages::initUi(void)
{
	clickDeviceDisplayAutoConnect(m_pBtParam->bIsAutoConnect);
}
//
bool CBtDevicePages::pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = false;

	bRet = btDeviceMainPage(id, e, p, len);
	if (bRet)
		return bRet;

	bRet = btDeviceSearchPage(id, e, p, len);
	if (bRet)
		return bRet;

	bRet = btDeviceSettingPage(id, e, p, len);
	if (bRet)
		return bRet;

	bRet = btDevicePinCodePage(id, e, p, len);
	if (bRet)
		return bRet;

	bRet = btDeviceNameEditPage(id, e, p, len);
	if (bRet)
		return bRet;
	
	bRet = btPhoneDevicePairPage(id, e, p, len);
	if (bRet)
		return bRet;

	bRet = btPhoneDevicePairDialogBox(id, e, p, len);
	if (bRet)
		return bRet;


	return bRet;
}
//
bool CBtDevicePages::btDeviceMainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;
	LOGD("btDeviceMainPage id:%x e:%x",id,e);
	switch(id)
	{
		//跳页
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACK:
		clickDeviceMainPageGoBack(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_SEARCH:
		clickDeviceMainPageSearchPageEntrance(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_SETTINGS:
		clickDeviceMainPageSettingPageEntrance(e);
		break;
		//删除设备
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_5:
		clickDeviceMainDeleteDeviceHasPaired(e, id - CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_6:
		clickDeviceMainDeleteDeviceHasPaired_New(e, id - CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_ALL:
		clickDeviceMainDeleteDevicesHavePaired(e);
		break;
		//已经配对过的设备
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_5:
	clickDeviceMainDevicesHavePairedListItem(e, id - CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1);	
	break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_6:
		clickDeviceMainDevicesHavePairedListItem_New(e, id - CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1);
		break;

		//删除与否
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_OK:
		clickDeviceMainDeleteDeviceHasPairedOk(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_CANCEL:
		clickDeviceMainDeleteDeviceHasPairedCancel(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_TIPOK:
		clickPinCodeTipBoxOk();
		break;
	//BC8
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BC8_PAIRING_CONNECTIONG_PROMPT_SURE:
		clickPinCodeTipBoxOk_Pairing_Connection_Prompt_BC8();
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CBtDevicePages::btDeviceSearchPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
		//跳页
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_BACK:
		clickDeviceSearchPageGoBack(e);
		break;
		//搜索到的设备
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT_6:
		clickDeviceSearchPageDeviceItem(id, e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_8:
		clickDeviceSearchPageDeviceItem_New(id, e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_PREV:
		clickDeviceSearchPagePrePage_New(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_NEXT:
		clickDeviceSearchPageNextPage_New(e);
		break;
		//翻页
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_PREV:
		clickDeviceSearchPagePrePage(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_NEXT:
		clickDeviceSearchPageNextPage(e);
		break;
		//刷新
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_REFRESH:
		clickDeviceSearchPageSearchDevice(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CBtDevicePages::btDeviceSettingPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
       
	bool bRet = true;
	switch(id)
	{
		//跳页
	case CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE_BACK:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageGoBack();
		break;
		//设置
	case CONTROLID_BLUETOOTH_AUDIOVOX_AUTO_CONNET:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageAutoConnectOn();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE:	
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageBtDevicePinCodeEditEntrance();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_EDITOR:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageBtDeviceNameEditEntrance();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_DAZHONG_BLACKRED_MIC_UP:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageMicVolumeUp();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_DAZHONG_BLACKRED_MIC_DOWN:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageMicVolumeDown();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_MIC_UP:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageMicVolumeUp();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_MIC_DOWN:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageMicVolumeDown();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_UP:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageMicVolumeUp();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_DOWN:
		if(e == MOUSE_STATUS_UP)
		clickDeviceSettingPageMicVolumeDown();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_PRESS_BTNAMECONTRID:
       if(e == MOUSE_STATUS_TIMER)
	   		clickDeviceSettingPageMicGainPage();
       break;
	  
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_BTMIC_PARAM_SETPAGE_BACK:
	  if(e == MOUSE_STATUS_UP)
	  		clickDeviceSettingPageMicPageBack();
	  break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CBtDevicePages::btDevicePinCodePage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
		//跳页
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_BACK:
		if(e == MOUSE_STATUS_UP)
		clickDevicePinCodeEditPageGoBack();
		break;
		//输入
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_0:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_9:
		if(e == MOUSE_STATUS_UP)
		clickDevicePinCodeEditPageDialPanel(id);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_DELETE:
		if(e == MOUSE_STATUS_UP || e == MOUSE_STATUS_TIMER)
		clickDevicePinCodeEditPageBackspace(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_OK:
		if(e == MOUSE_STATUS_UP)
		clickDevicePinCodeEditPageOK();
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CBtDevicePages::btDeviceNameEditPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_0:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_4 :
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_9:
		if(e == MOUSE_STATUS_UP || e == MOUSE_STATUS_TIMER)
		clickDeviceNameEditPageDialPanel(e,id - CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_0);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_A:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_B:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_C:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_D:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_E:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_F:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_G:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_H:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_I:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_J:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_K:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_L:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_M:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_N:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_O:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_P:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_Q:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_R:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_S:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_T:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_U:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_V:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_W:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_X:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_Y:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_Z:
		if(e == MOUSE_STATUS_UP || e == MOUSE_STATUS_TIMER)
		clickDeviceNameEditPageDialPanel(e,id - CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_A + 10);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_OK:
		if(e == MOUSE_STATUS_UP)
		clickDeviceNameEditPageOK();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_DELETE:
		if(e == MOUSE_STATUS_UP || e == MOUSE_STATUS_TIMER)
		clickDeviceNameEditPageBackspace(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_BACK:
		if(e == MOUSE_STATUS_UP)
		clickDeviceNameEditPageGoBack();
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CBtDevicePages::btPhoneDevicePairPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
		
	case CONTROLID_BLUETOOTH_AUDIOVOX_PHONEPAIR_BACK:
		if(e == MOUSE_STATUS_UP)
		clickPhoneDevicePairPageGoBack(e);
		break;

	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CBtDevicePages::btPhoneDevicePairDialogBox(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CONTROLID_BLUETOOTH_PAIRING_BOX_PAIRING_SURE:
		if(e == MOUSE_STATUS_UP)
			clickDevicePairDialogBoxOK();
		break;
	case CONTROLID_BLUETOOTH_PAIRING_BOX_PAIRING_CHANCE:
		if(e == MOUSE_STATUS_UP)
			clickDevicePairDialogBoxChance();
		break;
	case CONTROLID_BLUETOOTH_PAIRING_BOX_BACK:
		if(e == MOUSE_STATUS_UP)
			clickDevicePairDialogBoxGoBack();
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;

}

void CBtDevicePages::clickDevicePairDialogBoxOK()
{
	m_pBtParam->bIsStopPairing = false;
	g_pClsBtAdapter->setBtPairConfirm(0x01);
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);
}
void CBtDevicePages::clickDevicePairDialogBoxChance()
{
	m_pBtParam->bIsStopPairing = false;
	m_pBtParam->bIsPairBox = false;
	g_pClsBtAdapter->setBtPairConfirm(0x00);
	m_pBtModule->setPrePage();
	ShowOrHideHasBeenPairingPage(false);
}

void CBtDevicePages::clickDevicePairDialogBoxGoBack()
{
	m_pBtParam->bIsStopPairing = false;
	g_pClsBtAdapter->setBtPairConfirm(0x00);
	m_pBtModule->setPrePage();
	ShowOrHideHasBeenPairingPage(false);
}
/***********************************************************************/
void CBtDevicePages::clickDisplaySetDeviceNameToUi(u8 *param,u32 len)
{
	LOGD("[%s] param:%s",__FUNCTION__,param);
	setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_NAME_TEXT,param, len);
}

/***********************************************************************/
void CBtDevicePages::ShowBtMacAddress(char *strData,int len)
{
	LOGD("[%s] param:%s",__FUNCTION__,strData);
	setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_MAC_TEXT,(u8*)strData, (u32)len);
}

void CBtDevicePages::refreshBtDeviceSearchStatus(E_BT_DEVICE_SEARCH_STATUS e)
{
      switch(e)
      {
       case BT_DEVICE_SEARCH_STATUS_SEARCHING:
		{
			LOGD("[%s] BT_DEVICE_SEARCH_STATUS_SEARCHING",__FUNCTION__);
			m_pBtParam->m_btDevicesHaveNum = 0;
			setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT1, STRINGID_BT__DEVICE_INQUIRING);
		   	setUtf8String((u32)(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_PERCENTAGE), (u8*)"", 0);
       }
		break;
	case BT_DEVICE_SEARCH_STATUS_SEARCHED_DEVICE_COUNT:
		{      
			LOGD("[%s] BT_DEVICE_SEARCH_STATUS_SEARCHED_DEVICE_COUNT",__FUNCTION__);
			setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT1, STRINGID_BT__DEVICE_DEVICES_FOUND);
		}
		break;
	case BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH:
	   {
		   	LOGD("[%s] BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH",__FUNCTION__);
			if(!m_pBtParam->bPairingStatus)
				setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT1, STRINGID_BT__DEVICE_INQUIRY_TERMINATES_DEVICES_FOUND);
			char str[256]={0};   
			sprintf(str,"(%d)",m_pBtParam->m_btDevicesHaveNum);
			setUtf8String((u32)(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_PERCENTAGE), (u8*)str, strlen(str));
		}
		break;
	 }
	
}

void CBtDevicePages::refreshBtDevicesListHaveSearched(int n)
{
    printf("\n[refreshBtDevicesListHaveSearched] n:%d",n);
	m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom = n;
	int i = 0, j = 0;

	list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHaveSearched.begin();
	list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHaveSearched.end();

	for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
	{
		if (i < n)
		{	
			i++;
			continue;
		}

		setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT_2 + j,(u8*)it->deviceName,it->nameLen);
		j++;

		if (j >= BT_DEVICE_SEARCHED_PAGE_ITEM_NUM)
			break;
	}

	for (i = j; i < BT_DEVICE_SEARCHED_PAGE_ITEM_NUM; i++)
	{
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT_2 + i, (u8*)"", 0);
	}
}

void CBtDevicePages::refreshBtDevicesListHavePaired(int n)
{
	LOGD("[%s]",__FUNCTION__);
	m_pBtParam->m_nBtDevicesHavePairedListBrowseFrom = n;
	int i = 0, j = 0;

	list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
	list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

	for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
	{
		if (i < n)
			continue;
		setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1 + j,(u8*)it->deviceName,it->nameLen);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1+j,true);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+j, (short)0);
	   	setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+j,true);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+j,1);
		j++;

		if (j >= BT_DEVICE_PAIR_PAGE_ITEM_NUM)
			break;
	}

	for (i = j; i < BT_DEVICE_PAIR_PAGE_ITEM_NUM; i++)
	{
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1 + i, (u8*)"", 0);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+i, (short)0);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+i,false);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+i,0);
	}

}

void CBtDevicePages::showDialogBox_Pairing(u8 *p1,int len1,u8 *p2,int len2)
{
	if(!m_pBtParam->m_bIsPowerOn)
		return;
	ShowOrHideHasBeenPairingPage(true);
	setUtf8String(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_PINCODE,p1,len1);
	setUtf8String(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_NAME,p2,len2);

	if(m_pBtModule->getCurPageId() != PAGE_BLUETOOTH_PAIRING_DIALOG_BOX){
		m_pBtModule->setPage(PAGE_BLUETOOTH_PAIRING_DIALOG_BOX);
	}
}

void CBtDevicePages::ShowOrHideHasBeenPairingPage(bool b)
{
	if(b)
		ShowOrHideHasBeenPairingPromptBoxPage(false);
		
	setUpdateUI(false);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_DIALOG_GROUND,b);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_1,b);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_2,b);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_3,b);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_PINCODE,b);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_NAME,b);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_PAIRING_SURE,b);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_PAIRING_CHANCE,b);
	if(!b)
	{
		setUtf8String(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_PINCODE,(u8*)"",0);
		setUtf8String(CONTROLID_BLUETOOTH_PAIRING_BOX_TEXT_NAME,(u8*)"",0);
	}
	setUpdateUI(true);
}

void CBtDevicePages::ShowOrHideHasBeenPairingPromptBoxPage(bool b)
{
	setUpdateUI(false);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_DIALOG_1_GROUND,b);
	setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_DIALOG_1_TXT,b);
	if(b)
	setStringById(CONTROLID_BLUETOOTH_PAIRING_BOX_DIALOG_1_TXT, STRINGID_BT__DEVICE_PAIRING_CONNECTION_BEGIN);
	setUpdateUI(true);
}

void CBtDevicePages::clickDeviceMainPageGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		if(m_pBtParam->bA2DP_To_DevicePageBackButton)
		{
			if(HFP_CONNECT_STATUS_CONNECTED == m_pBtModule->getBtConnectStatus())
			{
				m_pBtModule->setPage(PAGE_BLUETOOTH_A2DP);
			}
			else
			{
				m_pBtModule->setPage(PAGE_BLUETOOTH_NO_A2DP);
			}
		}
		else 
		{
			m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
		}    
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceMainPageSearchPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			if (!m_pBtModule->isPowerOn())
			{  
				return;
			}
			if(!UI_MouseDown_MultiPair_Main_Search())
				return;
			if (HFP_CONNECT_STATUS_CONNECTED == m_pBtModule->getBtConnectStatus())
			{
				m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_SEARCH_PAIRED;
			
				showTipBox(TIP_BOX_NAME_SEARCH_PAIRED,true);
			}
			else
			{
				m_pBtParam->m_listBtDevicesHaveSearched.clear();
			    	refreshBtDevicesListHaveSearched(0);
				refreshBtDevicesListHaveSearched_New(0);

				if (!m_pBtModule->isBtDeviceSearchFinish())
				{
	          			g_pClsBtAdapter->requestBtSearchDevice(0x00);
					g_pClsBtAdapter->requestBtSearchDevice(0x01);
				}
				else
				{
					g_pClsBtAdapter->requestBtSearchDevice(0x01);
				}
                             	refreshBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCHING);
				m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH);

				m_pBtModule->deleteNativeTimer(TIMER_DELAY_CONNECTION_DEVICE_PAGE_TIME);
				memset(m_pBtParam->selecteDeviceAddr,0,FLY_BT_PAIRING_ADDRS_MAX_LEN);
				m_pBtParam->selecteDeviceAddrLen = 0;
			}

		}
			break;
		default:
			break;
	}
}
bool CBtDevicePages::UI_MouseDown_MultiPair_Main_Search()
{
	if (m_pBtParam->m_bShowTipsDlg)
	{
		return false;
	}
	return true;
}

void CBtDevicePages::showTipBox(E_TIP_BOX_NAME e, bool bShow)
{
	int szMap[32] = {0};
	szMap[TIP_BOX_NAME_DELETE_ALL_DEVICES_HAVE_PAIRED] = STRINGID_BT__DEVICE_DELETE_ALL;
	szMap[TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED] = STRINGID_BT__DEVICE_DELETE_ONE;
	szMap[TIP_BOX_NAME_UNKNOW] = STRING_CARINFO_DATA_UNKNOW;
	szMap[TIP_BOX_NAME_SEARCH_PAIRED] = STRINGID_BT__DEVICE_FIRST_DISCONNECT;

	bool bVisible = bShow;

	setUpdateUI(false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_TEXT, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_OK, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_CANCEL, bVisible);
	setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_TEXT, szMap[e]);
	setUpdateUI(true);

	if(bVisible)
	{
		m_pBtParam->m_bShowTipsDlg = true;
	}
	else
	{
		m_pBtParam->m_bShowTipsDlg = false;
	}
}

void CBtDevicePages::clickDeviceMainPageSettingPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING);
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceMainDeleteDeviceHasPaired(E_MOUSE_STATUS e, int index)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+index, (short)1);
			m_pBtParam->m_nDeleteOneBtDevice = index;
			
			m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED;
			
			showTipBox(TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED,true);
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceMainDeleteDevicesHavePaired(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			if(m_pBtParam->m_listBtDevicesHavePaired.empty())
				return;
			
			m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_DELETE_ALL_DEVICES_HAVE_PAIRED;
			
			showTipBox(TIP_BOX_NAME_DELETE_ALL_DEVICES_HAVE_PAIRED,true);
		}
		break;
		default:
		break;
	}
}

void CBtDevicePages::clickDeviceMainDevicesHavePairedListItem(E_MOUSE_STATUS e, int index)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1 + index,0);
			m_pBtParam->m_nClickHasPairedDeviceIndex=index;
			int k = m_pBtParam->m_listBtDevicesHavePaired.size();
			if(k < index + 1)
				return;
			if (HFP_CONNECT_STATUS_DISCONNECT == m_pBtModule->getBtConnectStatus())
			{
				char straddr[FLY_BT_PAIRING_ADDRS_MAX_LEN] = {0};
			
				int i = 0;
				list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
				list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

				for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
				{
					if(i == index)
					{
						//memcpy(straddr,it->deviceAddr,it->addrLen);
						//g_pClsBtAdapter->btInitiativeConnectDevice((u8 *)it->deviceAddr,it->addrLen);
						m_pBtHal->delayConnectionDevicePage();
						memcpy(m_pBtParam->selecteDeviceAddr,it->deviceAddr,it->addrLen);
						m_pBtParam->selecteDeviceAddrLen = it->addrLen;
						setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_CONNECTING_TO_DEVICE);
						break;
					}
					i++;
				}
				
			}
			else if(HFP_CONNECT_STATUS_CONNECTED == m_pBtModule->getBtConnectStatus())
			{
				char straddr[FLY_BT_PAIRING_ADDRS_MAX_LEN] = {0};
			
				int i = 0;
				list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
				list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

				for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
				{
					if(i == index)
					{
						memcpy(straddr,it->deviceAddr,it->addrLen);
						if(strcmp(m_pBtParam->szRemodeBtDeviceHasConnectedAddr,straddr) == 0)
						{
							g_pClsBtAdapter->btInitiativeDisconnection((u8 *)it->deviceAddr,it->addrLen);
						}
						else
						{
							m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_SEARCH_PAIRED;
							showTipBox(TIP_BOX_NAME_SEARCH_PAIRED,true);
						}
						LOGD("zhq[%s] ,click=%d",__FUNCTION__,i);
						break;
					}
					i++;
				}
				
			}
		}
		break;
		case MOUSE_STATUS_DOWN:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1 + index,1);
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceMainDeleteDeviceHasPairedOk(E_MOUSE_STATUS e)
{
switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			clickTipBoxOk();
		}
		break;
	default:
		break;
	}

}

void CBtDevicePages::clickTipBoxOk()
{
	bool bVisible = false;
	setUpdateUI(false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_TEXT, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_OK, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_CANCEL, bVisible);
	m_pBtParam->m_bShowTipsDlg = false;
	setUpdateUI(true);

	switch(m_pBtParam->m_eTipBoxName)
	{
	case TIP_BOX_NAME_SEARCH_PAIRED:
		{
			g_pClsBtAdapter->btInitiativeDisconnection((u8 *)m_pBtParam->szRemodeBtDeviceHasConnectedAddr,strlen(m_pBtParam->szRemodeBtDeviceHasConnectedAddr));
			setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_DEVICE_IS_DISCONNECTED);
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,0);
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1,0);
		}
		break;
	case TIP_BOX_NAME_DELETE_ALL_DEVICES_HAVE_PAIRED:
		{
			m_pBtModule->deleteNativeTimer(TIMER_DELAY_CONNECTION_DEVICE_PAGE_TIME);
			memset(m_pBtParam->selecteDeviceAddr,0,FLY_BT_PAIRING_ADDRS_MAX_LEN);
			m_pBtParam->selecteDeviceAddrLen = 0;
			
			m_pBtApp->m_pA2DPpages->setA2DPPause();			
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,0);
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1,0);
			
			m_pBtParam->m_listBtDevicesHavePaired.clear();

			g_pClsBtAdapter->deleteAllPairRecord();

			refreshBtDevicesListHavePaired(0);
			refreshBtDevicesListHavePaired_New(0);
			setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, (u8*)"", 0);
		}
		break;
	case TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED:
		{
			if(m_pBtParam->m_listBtDevicesHavePaired.size()== 1)
			{
				setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, (u8*)"", 0);
			}
			int n = m_pBtParam->m_nDeleteOneBtDevice;
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+n, (short)0);
	   	 	setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+n,false);
	    		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+n,0);
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1 + n, (u8*)"", 0);

			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+n, (short)0);
	   	 	setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+n,false);
	    		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+n,0);
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1 + n, (u8*)"", 0);
			
			int i = 0;
			list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
			list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

			for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
			{
				if(i == n)
				{
					if(!strcmp((char *)it->deviceAddr,(char *)m_pBtParam->selecteDeviceAddr))
					{
						m_pBtModule->deleteNativeTimer(TIMER_DELAY_CONNECTION_DEVICE_PAGE_TIME);
						memset(m_pBtParam->selecteDeviceAddr,0,FLY_BT_PAIRING_ADDRS_MAX_LEN);
						m_pBtParam->selecteDeviceAddrLen = 0;
					}
				
					g_pClsBtAdapter->deleteAPairRecord(it->deviceAddr,it->addrLen);
					m_pBtParam->m_listBtDevicesHavePaired.erase(it);
					m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired(0);
					refreshBtDevicesListHavePaired_New(0);
					break;
				}
				i++;
			}
		}
		break;
	default:
		break;
	}	
}

void CBtDevicePages::clickDeviceMainDeleteDeviceHasPairedCancel(E_MOUSE_STATUS e)
{
switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			clickTipBoxCancle();
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickTipBoxCancle()
{
	bool bVisible = false;
	setUpdateUI(false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_TEXT, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_OK, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_CANCEL, bVisible);
	m_pBtParam->m_bShowTipsDlg = false;
	
	int j = 0;
	for(;j <= 4;j++)
	{
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+j, (short)0);
	}
	int k = 0;
	for(;k <= 5;k++)
	{
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+j, (short)0);
	}
	setUpdateUI(true);
}

void CBtDevicePages::clickPinCodeTipBoxOk()
{
	showPinCodeTipBox(0);
	memset(m_pBtParam->szTemBtDevicePinCode,0,sizeof(m_pBtParam->szTemBtDevicePinCode));
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_FRAME,(u8*)m_pBtParam->szTemBtDevicePinCode, strlen(m_pBtParam->szTemBtDevicePinCode));
}

void CBtDevicePages::showPinCodeTipBox( bool bShow)
{

	bool bVisible = bShow;

	setUpdateUI(false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_TIPBACKGROUND, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_TIPTEXT, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_TIPOK, bVisible);
	setUpdateUI(true);
}

void CBtDevicePages::clickPinCodeTipBoxOk_Pairing_Connection_Prompt_BC8()
{
	showTipBox_BC8(false);
}
void CBtDevicePages::showTipBox_BC8(bool bShow)
{
	bool bVisible = bShow;

	setUpdateUI(false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BC8_PAIRING_CONNECTIONG_PROMPT_GROUND, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BC8_PAIRING_CONNECTIONG_PROMPT_TXT_1, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BC8_PAIRING_CONNECTIONG_PROMPT_TXT_2, bVisible);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BC8_PAIRING_CONNECTIONG_PROMPT_SURE, bVisible);
	setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BC8_PAIRING_CONNECTIONG_PROMPT_TXT_1,STRINGID_BT__DEVICE_CONNECTED_DEVICES_THE_LARGEST_1);
	setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BC8_PAIRING_CONNECTIONG_PROMPT_TXT_2,STRINGID_BT__DEVICE_CONNECTED_DEVICES_THE_LARGEST_2);
	setUpdateUI(true);

	if(bVisible)
	{
		m_pBtParam->m_bShowTipsDlg = true;
	}
	else
	{
		m_pBtParam->m_bShowTipsDlg = false;
	}
}

void CBtDevicePages::clickDeviceSearchPageGoBack(E_MOUSE_STATUS e)
{
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);	
	g_pClsBtAdapter->requestBtSearchDevice(0x00);
}

void CBtDevicePages::clickDeviceSearchPageDeviceItem(u32 id, E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			int n = m_pBtParam->m_listBtDevicesHaveSearched.size();
			if(n <= 0)return;
			
			if(m_pBtParam->bHandleStopSearchState == false)
				g_pClsBtAdapter->requestBtSearchDevice(0x00);
			int f = m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom;
			int i = id - CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT_2;
			int j = f + i;

			list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHaveSearched.begin();
			list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHaveSearched.end();

			int k = 0;
			for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
			{
				if (k == j)
				{
				   	m_pBtParam->btAddr1 = it->deviceAddr;
					m_pBtParam->btAddrLen1 = it->addrLen;
					g_pClsBtAdapter->requestBtPairDevice(m_pBtParam->btAddr1,m_pBtParam->btAddrLen1);
					setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT1, STRINGID_BT__DEVICE_PAIRING_CONNECTION_BEGIN);
					break;
				}
				else//if (k == j)
					k++;
			}
			
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceSearchPagePrePage(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nPreStartBrowse = -1;			
			nPreStartBrowse = m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom;
			m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom = max(0,m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom - SEARCH_LIST_DISPLAY_NUM);

			if (nPreStartBrowse == m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom)
				return;
			refreshBtDevicesListHaveSearched(m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceSearchPageNextPage(E_MOUSE_STATUS e)
{
	LOGD("[%s] (int)m_pBtParam->m_listBtDevicesHaveSearched.size() = [%d]", __FUNCTION__, (int)m_pBtParam->m_listBtDevicesHaveSearched.size());
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom;

			m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom += BT_DEVICE_SEARCHED_PAGE_ITEM_NUM;
			if (m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom >= (int)m_pBtParam->m_listBtDevicesHaveSearched.size())
		       {
				m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom -= BT_DEVICE_SEARCHED_PAGE_ITEM_NUM;
				return;
			}

			if(nNextStartBrowse == m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom)
				return;
			refreshBtDevicesListHaveSearched(m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceSearchPageSearchDevice(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pBtParam->m_listBtDevicesHaveSearched.clear();
			refreshBtDevicesListHaveSearched(0);
			refreshBtDevicesListHaveSearched_New(0);
			if(m_pBtParam->bPairingStatus == true)
			{
				g_pClsBtAdapter->setBtCancelPair(m_pBtParam->btAddr1,m_pBtParam->btAddrLen1);
			}
			if (!m_pBtModule->isBtDeviceSearchFinish()){
             			 g_pClsBtAdapter->requestBtSearchDevice(0x00);
				 g_pClsBtAdapter->requestBtSearchDevice(0x01);
			}
			else{
				g_pClsBtAdapter->requestBtSearchDevice(0x01);
			}
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceSettingPageGoBack()
{
	m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
}

void CBtDevicePages::clickDeviceSettingPageAutoConnectOn()
{
	if(m_pBtParam->bIsAutoConnect == 0)
	{
		m_pBtParam->bIsAutoConnect = 1;
		clickDeviceDisplayAutoConnect(m_pBtParam->bIsAutoConnect);
	}
	else
	{
		m_pBtParam->bIsAutoConnect = 0;
		clickDeviceDisplayAutoConnect(m_pBtParam->bIsAutoConnect);
	}
	
	g_pClsBtAdapter->setBtAutomateConnect(m_pBtParam->bIsAutoConnect);
}

void CBtDevicePages::clickDeviceDisplayAutoConnect(bool  bMode)
{
	if (bMode)
	{
		setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_AUTO_CONNET,true);
	}else
	{
		setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_AUTO_CONNET,false);
	}
}

void CBtDevicePages::clickDeviceSettingPageBtDevicePinCodeEditEntrance()
{
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_CODE);
}

void CBtDevicePages::clickDeviceSettingPageBtDeviceNameEditEntrance()
{
	if(m_pBtParam->m_bIsPowerOn == 0x00)
		return;
	memset(m_pBtParam->szTemBtDeviceName,0,sizeof(m_pBtParam->szTemBtDeviceName));
	setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_DISPLAY,(u8*)"", 0);
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_BTNAME_EDITOR);
}
void CBtDevicePages::setSerialMicrophoneVolumeGainToUI(int nParam)
{
    char ansiBuf[16];
    memset(ansiBuf, 0, 16);
    sprintf((char*)ansiBuf,"%d",nParam);
    setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_MIC, (u8*)ansiBuf, strlen(ansiBuf));
}

void CBtDevicePages::clickDeviceSettingPageMicVolumeUp()
{
	 if(m_pBtParam->n_MicGain_Volue >= 0x0f)return;
        	m_pBtParam->n_MicGain_Volue++;
	g_pClsBtAdapter->setBtMicVolume(m_pBtParam->n_MicGain_Volue);
	setSerialMicrophoneVolumeGainToUI(m_pBtParam->n_MicGain_Volue);
}

void CBtDevicePages::clickDeviceSettingPageMicVolumeDown()
{
	if(m_pBtParam->n_MicGain_Volue <= 0)return;
             m_pBtParam->n_MicGain_Volue--;

	g_pClsBtAdapter->setBtMicVolume(m_pBtParam->n_MicGain_Volue);
	setSerialMicrophoneVolumeGainToUI(m_pBtParam->n_MicGain_Volue);

}

void CBtDevicePages::clickDeviceSettingPageMicGainPage()
{
	if(!m_pBtParam->m_bIsPowerOn)
		return;
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_BTMIC_PARAM_SETPAGE);
}

void CBtDevicePages::clickDeviceSettingPageMicPageBack()
{
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING);
}

void CBtDevicePages::clickDevicePinCodeEditPageGoBack()
{
	m_pBtModule->setPrePage();
}

void CBtDevicePages::clickDevicePinCodeEditPageDialPanel(u32 id)
{
    int index=id-CONTROLID_BLUETOOTH_AUDIOVOX_CODE_0;
    if(strlen(m_pBtParam->szTemBtDevicePinCode) > 7)
	   	return;
	char strTmp[64]={0};
	sprintf(strTmp,"%d",index);
	strcat(m_pBtParam->szTemBtDevicePinCode , strTmp);
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_FRAME,(u8*)m_pBtParam->szTemBtDevicePinCode, strlen(m_pBtParam->szTemBtDevicePinCode));
}

void CBtDevicePages::clickDevicePinCodeEditPageBackspace(E_MOUSE_STATUS e)
{

	if (strlen(m_pBtParam->szTemBtDevicePinCode) >= 1)
	{
		if(e == MOUSE_STATUS_UP)
			m_pBtParam->szTemBtDevicePinCode[strlen(m_pBtParam->szTemBtDevicePinCode)-1] = '\0';
		else if(e == MOUSE_STATUS_TIMER)
			memset(m_pBtParam->szTemBtDevicePinCode,0,sizeof(m_pBtParam->szTemBtDevicePinCode));
	}
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_FRAME,(u8*)m_pBtParam->szTemBtDevicePinCode, strlen(m_pBtParam->szTemBtDevicePinCode));
}

void CBtDevicePages::clickDevicePinCodeEditPageOK()
{
	if(strlen(m_pBtParam->szTemBtDevicePinCode) == 4)
	{
		g_pClsBtAdapter->setBtPincode((u8 *)m_pBtParam->szTemBtDevicePinCode,4);
		memset(m_pBtParam->szTemBtDevicePinCode,0,sizeof(m_pBtParam->szTemBtDevicePinCode));
		setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_FRAME,(u8*)m_pBtParam->szTemBtDevicePinCode, strlen(m_pBtParam->szTemBtDevicePinCode));
		m_pBtModule->setPrePage();
	}
	else
	{
		showPinCodeTipBox(1);
	}
}

void CBtDevicePages::clickDeviceNameEditPageDialPanel(E_MOUSE_STATUS e,u32 id)
{
	if(strlen(m_pBtParam->szTemBtDeviceName) >= (FLY_BT_DEVICE_NAME_MAX_LEN-26))
		return;
	
	char strTmp[FLY_BT_DEVICE_NAME_MAX_LEN];
	memset(strTmp,0,sizeof(strTmp));
	
	if(id<10)
	{
		sprintf(strTmp,"%d",id);
	}
	else 
	{
		if(e == MOUSE_STATUS_UP){
			static u8 szCharMap[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm','n','o','p','q','r','s','t','u','v','w','x','y','z'};
			sprintf(strTmp,"%c",szCharMap[id-10]);
		}
		else if(e == MOUSE_STATUS_TIMER){
			static u8 szCharMap[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
			sprintf(strTmp,"%c",szCharMap[id-10]);
		}
	}
		
	strcat(m_pBtParam->szTemBtDeviceName , strTmp);
	clickDisplayDeviceNameKeyboardToUi((u8*)m_pBtParam->szTemBtDeviceName, strlen(m_pBtParam->szTemBtDeviceName));
}
void CBtDevicePages::clickDisplayDeviceNameKeyboardToUi(u8 *param,u32 len)
{
	setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_DISPLAY,param, len);
}
void CBtDevicePages::clickDeviceNameEditPageOK()
{
	if(m_pBtParam->szTemBtDeviceName  != NULL)
		g_pClsBtAdapter->setDeviceBtName((u8*)m_pBtParam->szTemBtDeviceName,strlen(m_pBtParam->szTemBtDeviceName));
	m_pBtModule->setPrePage();
}
void CBtDevicePages::clickDeviceNameEditPageBackspace(E_MOUSE_STATUS e)
{
	if (strlen(m_pBtParam->szTemBtDeviceName) >= 1)
	{
		if(e == MOUSE_STATUS_UP)
			m_pBtParam->szTemBtDeviceName[strlen(m_pBtParam->szTemBtDeviceName)-1] = '\0';
		else if(e == MOUSE_STATUS_TIMER)
			memset(m_pBtParam->szTemBtDeviceName,0,sizeof(m_pBtParam->szTemBtDeviceName));
	}
	
	clickDisplayDeviceNameKeyboardToUi((u8*)m_pBtParam->szTemBtDeviceName, strlen(m_pBtParam->szTemBtDeviceName));
}

void CBtDevicePages::clickDeviceNameEditPageGoBack()
{
	m_pBtModule->setPrePage();
}

void CBtDevicePages::clickPhoneDevicePairPageGoBack(E_MOUSE_STATUS e)
{
	m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);	
	//m_pBtParam->_w_bPairing = false;
}

void CBtDevicePages::getSystemParam_changePage(u8 *buff)
{
	u16 leavePageID = buff[0] + buff[1] * 0x100;
	u16 enterPageID = buff[2] +buff[3] * 0x100;
	int pageParam = buff[4];
	LOGD("[%s] enterPageID:%x,leavePageID:%x",__FUNCTION__,enterPageID,leavePageID);
}

void CBtDevicePages::setAutoConnect(u8 tag)
{
	if(m_pBtParam->szRemodeBtDeviceLastConnectedAddr[0] != '\0')
	{
		if(tag == 0x01)
		{
			g_pClsBtAdapter->btInitiativeConnectDevice((u8 *)m_pBtParam->szRemodeBtDeviceLastConnectedAddr ,strlen(m_pBtParam->szRemodeBtDeviceLastConnectedAddr ));
		}
	}
}

void CBtDevicePages::clickDeviceSearchPageDeviceItem_New(u32 id, E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			int n = m_pBtParam->m_listBtDevicesHaveSearched.size();
			if(n <= 0)return;
			
			if(m_pBtParam->bHandleStopSearchState == false)
				g_pClsBtAdapter->requestBtSearchDevice(0x00);
			int f = m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom;
			int i = id - CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_2;
			int j = f + i;

			list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHaveSearched.begin();
			list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHaveSearched.end();

			int k = 0;
			for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
			{
				if (k == j)
				{
				   	m_pBtParam->btAddr1 = it->deviceAddr;
					m_pBtParam->btAddrLen1 = it->addrLen;
					g_pClsBtAdapter->requestBtPairDevice(m_pBtParam->btAddr1,m_pBtParam->btAddrLen1);
					setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_TEXT1, STRINGID_BT__DEVICE_PAIRING_CONNECTION_BEGIN);
					break;
				}
				else//if (k == j)
					k++;
			}
			
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::refreshBtDevicesListHaveSearched_New(int n)
{
    printf("\n[refreshBtDevicesListHaveSearched_New] n:%d",n);
	m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom = n;
	int i = 0, j = 0;

	list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHaveSearched.begin();
	list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHaveSearched.end();

	for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
	{
		if (i < n)
		{	
			i++;
			continue;
		}

		setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_2 + j,(u8*)it->deviceName,it->nameLen);
		j++;

		if (j >= 7)
			break;
	}

	for (i = j; i < 7; i++)
	{
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_TEXT_2 + i, (u8*)"", 0);
	}
}

void CBtDevicePages::clickDeviceSearchPagePrePage_New(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nPreStartBrowse = -1;			
			nPreStartBrowse = m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom;
			m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom = max(0,m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom - SEARCH_LIST_DISPLAY_NUM_NEW);

			if (nPreStartBrowse == m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom)
				return;
			refreshBtDevicesListHaveSearched_New(m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceSearchPageNextPage_New(E_MOUSE_STATUS e)
{
	LOGD("[%s] (int)m_pBtParam->m_listBtDevicesHaveSearched.size() = [%d]", __FUNCTION__, (int)m_pBtParam->m_listBtDevicesHaveSearched.size());
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom;

			m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom += BT_DEVICE_SEARCHED_PAGE_ITEM_NUM_NEW;
			if (m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom >= (int)m_pBtParam->m_listBtDevicesHaveSearched.size())
		       {
				m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom -= BT_DEVICE_SEARCHED_PAGE_ITEM_NUM_NEW;
				return;
			}

			if(nNextStartBrowse == m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom)
				return;
			refreshBtDevicesListHaveSearched_New(m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);
		}
		break;
	default:
		break;
	}
}


void CBtDevicePages::clickDeviceMainDeleteDeviceHasPaired_New(E_MOUSE_STATUS e, int index)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+index, (short)0);
			m_pBtParam->m_nDeleteOneBtDevice = index;
			
			m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED;
			
			showTipBox(TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED,true);
		}
		break;
	case MOUSE_STATUS_UNKNOW:
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+index, (short)1);
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceMainDevicesHavePairedListItem_New(E_MOUSE_STATUS e, int index)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1 + index,0);
			m_pBtParam->m_nClickHasPairedDeviceIndex=index;
			int k = m_pBtParam->m_listBtDevicesHavePaired.size();
			if(k < index + 1)
				return;
			if (HFP_CONNECT_STATUS_DISCONNECT == m_pBtModule->getBtConnectStatus())
			{
				char straddr[FLY_BT_PAIRING_ADDRS_MAX_LEN] = {0};
			
				int i = 0;
				list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
				list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

				for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
				{
					if(i == index)
					{
						//memcpy(straddr,it->deviceAddr,it->addrLen);
						//g_pClsBtAdapter->btInitiativeConnectDevice((u8 *)it->deviceAddr,it->addrLen);
						m_pBtHal->delayConnectionDevicePage();
						memcpy(m_pBtParam->selecteDeviceAddr,it->deviceAddr,it->addrLen);
						m_pBtParam->selecteDeviceAddrLen = it->addrLen;
						setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_CONNECTING_TO_DEVICE);
						break;
					}
					i++;
				}
				
			}
			else if(HFP_CONNECT_STATUS_CONNECTED == m_pBtModule->getBtConnectStatus())
			{
				char straddr[FLY_BT_PAIRING_ADDRS_MAX_LEN] = {0};
			
				int i = 0;
				list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
				list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

				for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
				{
					if(i == index)
					{
						memcpy(straddr,it->deviceAddr,it->addrLen);
						if(strcmp(m_pBtParam->szRemodeBtDeviceHasConnectedAddr,straddr) == 0)
						{
							g_pClsBtAdapter->btInitiativeDisconnection((u8 *)it->deviceAddr,it->addrLen);
						}
						else
						{
							m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_SEARCH_PAIRED;
							showTipBox(TIP_BOX_NAME_SEARCH_PAIRED,true);
						}
						LOGD("zhq[%s] ,click=%d",__FUNCTION__,i);
						break;
					}
					i++;
				}
				
			}
		}
		break;
		case MOUSE_STATUS_DOWN:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1 + index,1);
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::refreshBtDevicesListHavePaired_New(int n)
{
	LOGD("[%s]",__FUNCTION__);
	m_pBtParam->m_nBtDevicesHavePairedListBrowseFrom = n;
	int i = 0, j = 0;

	list<BluetoothDevice>::iterator itFrom = m_pBtParam->m_listBtDevicesHavePaired.begin();
	list<BluetoothDevice>::iterator itTo = m_pBtParam->m_listBtDevicesHavePaired.end();

	for (list<BluetoothDevice>::iterator it = itFrom; it != itTo; it++)
	{
		if (i < n)
			continue;
		setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1 + j,(u8*)it->deviceName,it->nameLen);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1+j,true);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+j, (short)0);
	   	setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+j,true);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+j,1);
		j++;

		if (j >= BT_DEVICE_PAIR_PAGE_ITEM_NUM_NEW)
			break;
	}

	for (i = j; i < BT_DEVICE_PAIR_PAGE_ITEM_NUM_NEW; i++)
	{
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1 + i, (u8*)"", 0);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+i, (short)0);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+i,false);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+i,0);
	}

}

