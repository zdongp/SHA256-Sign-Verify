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
	setSerialMicrophoneVolumeToUI(m_pBtParam->m_nMicVolume);
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
		clickDeviceSettingPageGoBack();
		break;
		//设置
	case CONTROLID_BLUETOOTH_AUDIOVOX_AUTO_CONNET:
		clickDeviceSettingPageAutoConnectOn();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE:		
		clickDeviceSettingPageBtDevicePinCodeEditEntrance();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_EDITOR:
		clickDeviceSettingPageBtDeviceNameEditEntrance();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_DAZHONG_BLACKRED_MIC_UP:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_DAZHONG_BLACKRED_MIC_DOWN:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_MIC_UP:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_MIC_DOWN:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_UP:
	case CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_DOWN:
		clickDeviceSettingPageMicVolume(id - CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_UP);
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
		clickDevicePinCodeEditPageDialPanel(id);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_DELETE:
		clickDevicePinCodeEditPageBackspace(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CODE_OK:
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
		clickDeviceNameEditPageDialPanel(e,id - CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_A + 10);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_OK:
		clickDeviceNameEditPageOK();
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_DELETE:
		clickDeviceNameEditPageBackspace(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_BACK:
		clickDeviceNameEditPageGoBack();
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}
//device main page
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
						m_pBtParam->bHandleStopSearchState = true;
		              	g_pClsBtBC6Adapter->setToBtChipStopSearchBtDevice();
					}
					else
					{
						m_pBtParam->bHandleStopSearchState = false;
						m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCHING);
						g_pClsBtBC6Adapter->setToBtChipStartSearchBtDevice(); 
					}
                                 
					m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH);
				}

			}
			break;
		default:
			break;
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
			/*if (index >= m_pBtParam->m_vectBtDeviceHadPaired.size())
				return;
			
			m_pBtParam->m_nDeleteDeviceIndexSelected = index;
			m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_DELETE_ONE_DEVICE_HAS_PAIRED;
			showTipBox(true);*/
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
			int k = m_pBtParam->m_listBtDevicesHavePaired.size();
			LOGD("[%s] k:%d",__FUNCTION__,k);
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
						memcpy(straddr,it->deviceAddr,it->addrLen);
						g_pClsBtBC6Adapter->setToBtChipConnectHFP((char*)it->deviceAddr, it->addrLen);
						LOGD("[%s] ,click=%d",__FUNCTION__,i);
						break;
					}
					i++;
				}
				setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_CONNECTING_TO_DEVICE);
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
							m_pBtApp->m_pA2DPpages->setA2DPPause();
							usleep(200*1000);
							g_pClsBtBC6Adapter->setToBtChipDisConnectHFPAndA2DP();
						}
						else
						{
							m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_SPEED_ONE_TOUCH_PAIRED;
							memset(m_pBtParam->str_addrSpeedConnect,0,sizeof(FLY_BT_PAIRING_ADDRS_MAX_LEN));
							memcpy(m_pBtParam->str_addrSpeedConnect,it->deviceAddr,it->addrLen);
							LOGD("[%s] ,addrSpeedConnect=%s",__FUNCTION__,m_pBtParam->str_addrSpeedConnect);
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

//device search page
void CBtDevicePages::clickDeviceSearchPageGoBack(E_MOUSE_STATUS e)
{
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);	
	g_pClsBtBC6Adapter->setToBtChipStopSearchBtDevice();
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

			if (!m_pBtModule->isBtDeviceSearchFinish()){
				m_pBtParam->bHandleStopSearchState = true;
                g_pClsBtBC6Adapter->setToBtChipStopSearchBtDevice();
			}
			else{
				m_pBtParam->bHandleStopSearchState = false;
				m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCHING);
				g_pClsBtBC6Adapter->setToBtChipStartSearchBtDevice(); 
			}
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceSearchPagePrePage(E_MOUSE_STATUS e)
{
	//if (!m_pBtModule->isBtDeviceSearchFinish())
	//	return;

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

	//if (!m_pBtModule->isBtDeviceSearchFinish())
	//	return;

	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom;

			m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom += SEARCH_LIST_DISPLAY_NUM;
			if (m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom >= (int)m_pBtParam->m_listBtDevicesHaveSearched.size())
		       {
				m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom -= SEARCH_LIST_DISPLAY_NUM;
				return;
			}

			if(nNextStartBrowse == m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom)
				return;
			LOGD("[%s] m_nBtDevicesHaveSearchedListBrowseFrom:%d ",__FUNCTION__,m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);
			refreshBtDevicesListHaveSearched(m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CBtDevicePages::clickDeviceSearchPageDeviceItem(u32 id, E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			int n = m_pBtParam->m_listBtDevicesHaveSearched.size();
			if(n <= 0)return;
			
			memset(m_pBtParam->szTemBtDevicePinCode,0,sizeof(m_pBtParam->szTemBtDevicePinCode));
			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_FRAME,(u8*)m_pBtParam->szTemBtDevicePinCode, strlen(m_pBtParam->szTemBtDevicePinCode));

			g_pClsBtBC6Adapter->setToBtChipStopSearchBtDevice();
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
					memset(m_pBtParam->uSetConnectbtAddr,0,sizeof(FLY_BT_DEVICE_ADDRS_MAX_LEN));
					memcpy(m_pBtParam->uSetConnectbtAddr,it->deviceAddr,it->addrLen);
					
					int Counts = m_pBtParam->m_listBtDevicesHavePaired.size();
					LOGD("[%s] Counts:%d (%d %d)",__FUNCTION__,Counts,k,j);
					if(Counts > 0)
					{
						int i = 0;
						list<BluetoothDevice>::iterator itFrom1 = m_pBtParam->m_listBtDevicesHavePaired.begin();
						list<BluetoothDevice>::iterator itTo1 = m_pBtParam->m_listBtDevicesHavePaired.end();

						for (list<BluetoothDevice>::iterator it1 = itFrom1; it1 != itTo1; it1++)
						{
							LOGD("[%s] (%d %d)   [(%s) (%s)]",__FUNCTION__,i,n,it->deviceAddr,it1->deviceAddr);
							if(strcmp((char*)(it->deviceAddr),(char*)it1->deviceAddr) == 0)
							{
								m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);
								break;
							}

							if(i >= (Counts - 1))
							{
								m_pBtParam->bIsSelectPairing = true;
								//g_pClsBtBC6Adapter->setToBtChipConnectHFP((char*)it->deviceAddr,it->addrLen);
								ShowOrHideHasBeenPairingPromptBoxPage(true);
								m_pBtModule->setPage(PAGE_BLUETOOTH_PAIRING_DIALOG_BOX);
								break;
							}
							
							i++;
						}
					}
					else//if(Counts > 0)
					{
						m_pBtParam->bIsSelectPairing = true;
						//g_pClsBtBC6Adapter->setToBtChipConnectHFP((char*)it->deviceAddr,it->addrLen);
						ShowOrHideHasBeenPairingPromptBoxPage(true);
						m_pBtModule->setPage(PAGE_BLUETOOTH_PAIRING_DIALOG_BOX);
					}
					break;
				}
				else //if (k == j)
				{
					k++;
				}
			}
			
		}
		break;
	default:
		break;
	}
}
//device setting page
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
	
	g_pClsBtBC6Adapter->setToBtChipSetAutoConnect(m_pBtParam->bIsAutoConnect);
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

void CBtDevicePages::clickDeviceSettingPageAutoConnectOff(E_MOUSE_STATUS e)
{
	
}

void CBtDevicePages::clickDeviceSettingPageBtDeviceNameEditEntrance()
{
	if(m_pBtParam->m_bIsPowerOn == 0x00)
		return;
	memset(m_pBtParam->szTemBtDeviceName,0,sizeof(m_pBtParam->szTemBtDeviceName));
	setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_DISPLAY,(u8*)"", 0);
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_BTNAME_EDITOR);
}

void CBtDevicePages::clickDeviceSettingPageBtDevicePinCodeEditEntrance()
{
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_CODE);
}

void CBtDevicePages::clickDeviceSettingPageMicVolume(u8 p)
{
	int nT = m_pBtParam->m_nMicVolume;

	if(p == 0)
	{
		if(nT >= MAX_BC8_MIC_VALUE)
		return;
	
		nT++;
	}
	else if(p == 1)
	{
		if(nT <= 0)
			return;

		nT--;
	}

	if(nT == nTemMicValue)
		return;
	nTemMicValue = nT;
	
	g_pClsBtBC6Adapter->setToBtChipCtrlMicVolume(nT);
	setSerialMicrophoneVolumeToUI(nT);
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

//device pin code page

void CBtDevicePages::setSerialMicrophoneVolumeGainToUI(int nParam)
{
    char ansiBuf[16];
    memset(ansiBuf, 0, 16);
    sprintf((char*)ansiBuf,"%d",nParam);
    setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_MIC, (u8*)ansiBuf, strlen(ansiBuf));
}

void CBtDevicePages::setSerialMicrophoneVolumeToUI(int nParam)
{
    char ansiBuf[16];
    memset(ansiBuf, 0, 16);
    sprintf((char*)ansiBuf,"%d",nParam);
    setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_TEXT, (u8*)ansiBuf, strlen(ansiBuf));
}

void CBtDevicePages::clickDevicePinCodeEditPageGoBack()
{
	m_pBtModule->setPrePage();
}

void CBtDevicePages::clickDevicePinCodeEditPageDialPanel(u32 id)
{
	LOGD("[%s] id:%d ",__FUNCTION__,id);
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

//
void CBtDevicePages::clickDeviceNameEditPageGoBack()
{
	m_pBtModule->setPrePage();
}

void CBtDevicePages::clickDeviceNameEditPageDialPanel(E_MOUSE_STATUS e,u32 id)
{
    LOGD("[%s] id:%d",__FUNCTION__,id);
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
	LOGD("[%s] len:%d",__FUNCTION__,strlen(m_pBtParam->szTemBtDeviceName));
	
	clickDisplayDeviceNameKeyboardToUi((u8*)m_pBtParam->szTemBtDeviceName, strlen(m_pBtParam->szTemBtDeviceName));
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

void CBtDevicePages::clickDeviceNameEditPageOK()
{
	g_pClsBtBC6Adapter->setToBtChipModifyBtChipName(m_pBtParam->szTemBtDeviceName, strlen(m_pBtParam->szTemBtDeviceName));
	m_pBtModule->setPrePage();
}

void CBtDevicePages::clickDisplaySetDeviceNameToUi(u8 *param,u32 len)
{
	LOGD("[%s] param:%s",__FUNCTION__,param);
	setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_NAME_TEXT,param, len);
}

void CBtDevicePages::clickDisplayDeviceNameKeyboardToUi(u8 *param,u32 len)
{
	setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_KEYBOARD_EDITOR_DISPLAY,param, len);
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
	case TIP_BOX_NAME_SPEED_ONE_TOUCH_PAIRED:
		{
			m_pBtParam->bIsSpeedConnectState = true;
			m_pBtApp->m_pA2DPpages->setA2DPPause();
			usleep(200*1000);
			g_pClsBtBC6Adapter->setToBtChipDisConnectHFPAndA2DP();

			setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_CONNECTING_TO_DEVICE);
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,0);

			m_pBtModule->deleteNativeTimer(TIME_ID_ONE_TOUCH_SPEED_CONNECT_SWITCH);
			m_pBtModule->setNativeTimer(TIMES_ONE_TOUCH_SPEED_CONNECT_SWITCH,1,TIME_ID_ONE_TOUCH_SPEED_CONNECT_SWITCH);
		}
		break;
	case TIP_BOX_NAME_SEARCH_PAIRED:
		{
			m_pBtApp->m_pA2DPpages->setA2DPPause();
			usleep(200*1000);
			g_pClsBtBC6Adapter->setToBtChipDisConnectHFPAndA2DP();

			setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_DEVICE_IS_DISCONNECTED);
			
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,0);
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1,0);
			LOGD("DUANKAI  LIANJIE ");
		}
		break;
	case TIP_BOX_NAME_DELETE_ALL_DEVICES_HAVE_PAIRED:
		{
			m_pBtApp->m_pA2DPpages->setA2DPPause();
			usleep(200*1000);
			g_pClsBtBC6Adapter->setToBtChipDisConnectHFPAndA2DP();
							
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,0);
			m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1,0);
			m_pBtParam->m_listBtDevicesHavePaired.clear();		
			g_pClsBtBC6Adapter->setToBtChipEraseDevicePairRecord_BC8();

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
			
			if(HFP_CONNECT_STATUS_CONNECTED == m_pBtModule->getBtConnectStatus() && (n == 0))
			{
				m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,0);
			}
			
			g_pClsBtBC6Adapter->setToBtChipEraseDevicePairRecord(1+n);
			m_pBtParam->m_listBtDevicesHavePaired.clear();
			g_pClsBtBC6Adapter->setToBtChipQueryHavePairDevices();
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
	setUpdateUI(true);
	int k = 0;
	for(;k <= 5;k++)
	{
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_DELETE_1+j, (short)0);
	}
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
    LOGD("[%s] n:%d",__FUNCTION__,n);
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

		if (j >= BT_DEVICE_SEARCHED_PAGE_ITEM_NUM)
			break;
	}

	for (i = j; i < BT_DEVICE_SEARCHED_PAGE_ITEM_NUM; i++)
	{
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1 + i, (u8*)"", 0);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+i, (short)0);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+i,false);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_1+i,0);
	}

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
void CBtDevicePages::clickPinCodeTipBoxOk()
{
	showPinCodeTipBox(0);
	memset(m_pBtParam->szTemBtDevicePinCode,0,sizeof(m_pBtParam->szTemBtDevicePinCode));
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_FRAME,(u8*)m_pBtParam->szTemBtDevicePinCode, strlen(m_pBtParam->szTemBtDevicePinCode));
}

bool CBtDevicePages::btPhoneDevicePairPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
		
	case CONTROLID_BLUETOOTH_AUDIOVOX_PHONEPAIR_BACK:
		clickPhoneDevicePairPageGoBack(e);
		break;

	default:
		bRet = false;
		break;
	}

	return bRet;
}

void CBtDevicePages::clickPhoneDevicePairPageGoBack(E_MOUSE_STATUS e)
{
	m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);	
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
	g_pClsBtBC6Adapter->setToBtChipStartPairMode_BC8();
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);
}

void CBtDevicePages::clickDevicePairDialogBoxChance()
{
	m_pBtParam->bIsStopPairing = false;
	m_pBtParam->bIsPairBox = false;
	g_pClsBtBC6Adapter->setToBtChipEndPairMode_BC8();
	m_pBtModule->setPrePage();
	ShowOrHideHasBeenPairingPage(false);
}

void CBtDevicePages::clickDevicePairDialogBoxGoBack()
{
	m_pBtParam->bIsStopPairing = false;
	g_pClsBtBC6Adapter->setToBtChipEndPairMode_BC8();
	m_pBtModule->setPrePage();
	ShowOrHideHasBeenPairingPage(false);
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
	//setVisible(CONTROLID_BLUETOOTH_PAIRING_BOX_DIALOG_1_SURE,b);
	if(b){
		setStringById(CONTROLID_BLUETOOTH_PAIRING_BOX_DIALOG_1_TXT, STRINGID_BT__DEVICE_PAIRING_CONNECTION_BEGIN);
	}
	else{
		setAnsiSerialData(CONTROLID_BLUETOOTH_PAIRING_BOX_DIALOG_1_TXT, (u8*)"", 0);
	}
	setUpdateUI(true);
}

void CBtDevicePages::getSystemParam_changePage(u8 *buff)
{
	u16 leavePageID = buff[0] + buff[1] * 0x100;
	u16 enterPageID = buff[2] +buff[3] * 0x100;
	int pageParam = buff[4];
	LOGD("[%s] enterPageID:%x,leavePageID:%x",__FUNCTION__,enterPageID,leavePageID);
	if(leavePageID == PAGE_BLUETOOTH_PAIRING_DIALOG_BOX && m_pBtParam->bIsStopPairing == true)
	{
		g_pClsBtBC6Adapter->setToBtChipEndPairMode_BC8();
		ShowOrHideHasBeenPairingPage(false);
	}

	#ifdef MSM_ANDROID_ISR_NEW_FUNCTION
	switch(m_pBtParam->m_ePhoneStatus)
	{
		case BT_PHONE_STATUS_CALL_IN:
		{
			m_pBtApp->m_pBtMainPage->IncomingCallWindowPromt(m_pBtParam->m_ePhoneStatus,true,enterPageID);
		}
		break;
		default:
			m_pBtApp->m_pBtMainPage->IncomingCallWindowPromt(m_pBtParam->m_ePhoneStatus,false,enterPageID);
		break;
	}
	#endif
}

void CBtDevicePages::HideHasBeenPaired()
{
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG,false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_TEXT,false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_OK,false);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_CANCEL,false);
	m_pBtParam->m_bShowTipsDlg = false;
}

void CBtDevicePages::ShowHasBeenPaired()
{
   	setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_TEXT, STRINGID_BT__DEVICE_ALREADY_PAIRED);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG,true);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_TEXT,true);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_OK,true);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_CANCEL,true);
	m_pBtParam->m_bShowTipsDlg = true;
}

bool CBtDevicePages::UI_MouseDown_MultiPair_Main_Search()
{
	LOGD("[%s] m_bShowTipsDlg = %d ",__FUNCTION__,m_pBtParam->m_bShowTipsDlg);
	if (m_pBtParam->m_bShowTipsDlg)
	{
		return false;
	}
	return true;
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

void CBtDevicePages::ShowBtMacAddress(char *strData,int len)
{
	LOGD("[%s] param:%s",__FUNCTION__,strData);
	setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_MAC_TEXT,(u8*)strData, (u32)len);
}

void CBtDevicePages::clickDeviceSearchPageDeviceItem_New(u32 id, E_MOUSE_STATUS e)
	{
		switch(e)
		{
		case MOUSE_STATUS_UP:
			{
				int n = m_pBtParam->m_listBtDevicesHaveSearched.size();
				if(n <= 0)return;
				
				memset(m_pBtParam->szTemBtDevicePinCode,0,sizeof(m_pBtParam->szTemBtDevicePinCode));
				setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CODE_FRAME,(u8*)m_pBtParam->szTemBtDevicePinCode, strlen(m_pBtParam->szTemBtDevicePinCode));
	
				g_pClsBtBC6Adapter->setToBtChipStopSearchBtDevice();
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
						memset(m_pBtParam->uSetConnectbtAddr,0,sizeof(FLY_BT_DEVICE_ADDRS_MAX_LEN));
						memcpy(m_pBtParam->uSetConnectbtAddr,it->deviceAddr,it->addrLen);
					
						int Counts = m_pBtParam->m_listBtDevicesHavePaired.size();
						LOGD("[%s] Counts:%d (%d %d)",__FUNCTION__,Counts,k,j);
						if(Counts > 0)
						{
							int i = 0;
							list<BluetoothDevice>::iterator itFrom1 = m_pBtParam->m_listBtDevicesHavePaired.begin();
							list<BluetoothDevice>::iterator itTo1 = m_pBtParam->m_listBtDevicesHavePaired.end();

							for (list<BluetoothDevice>::iterator it1 = itFrom1; it1 != itTo1; it1++)
							{
								LOGD("[%s] (%d %d)	 [(%s) (%s)]",__FUNCTION__,i,n,it->deviceAddr,it1->deviceAddr);
								if(strcmp((char*)(it->deviceAddr),(char*)it1->deviceAddr) == 0)
								{
									m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);
									break;
								}

								if(i >= (Counts - 1))
								{
									m_pBtParam->bIsSelectPairing = true;
									//g_pClsBtBC6Adapter->setToBtChipConnectHFP((char*)it->deviceAddr,it->addrLen);
									ShowOrHideHasBeenPairingPromptBoxPage(true);
									m_pBtModule->setPage(PAGE_BLUETOOTH_PAIRING_DIALOG_BOX);
									break;
								}
								
								i++;
							}
						}
						else//if(Counts > 0)
						{
							m_pBtParam->bIsSelectPairing = true;
							//g_pClsBtBC6Adapter->setToBtChipConnectHFP((char*)it->deviceAddr,it->addrLen);
							ShowOrHideHasBeenPairingPromptBoxPage(true);
							m_pBtModule->setPage(PAGE_BLUETOOTH_PAIRING_DIALOG_BOX);
						}
						break;
					}
					else //if (k == j)
					{
						k++;
					}
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
	case MOUSE_STATUS_DOWN:
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
			int k = m_pBtParam->m_listBtDevicesHavePaired.size();
			LOGD("[%s] k:%d",__FUNCTION__,k);
			if(k < index + 1)
				return;
			if(HFP_CONNECT_STATUS_DISCONNECT == m_pBtModule->getBtConnectStatus())
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
						g_pClsBtBC6Adapter->setToBtChipConnectHFP((char*)it->deviceAddr, it->addrLen);
						LOGD("[%s] ,click=%d",__FUNCTION__,i);
						break;
					}
					i++;
				}
				setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_CONNECTING_TO_DEVICE);
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
							m_pBtApp->m_pA2DPpages->setA2DPPause();
							usleep(200*1000);
							g_pClsBtBC6Adapter->setToBtChipDisConnectHFPAndA2DP();
						}
						else
						{
							m_pBtParam->m_eTipBoxName = TIP_BOX_NAME_SPEED_ONE_TOUCH_PAIRED;
							memset(m_pBtParam->str_addrSpeedConnect,0,sizeof(FLY_BT_PAIRING_ADDRS_MAX_LEN));
							memcpy(m_pBtParam->str_addrSpeedConnect,it->deviceAddr,it->addrLen);
							LOGD("[%s] ,addrSpeedConnect=%s",__FUNCTION__,m_pBtParam->str_addrSpeedConnect);
			
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
		default:break;
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

