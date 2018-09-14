#include "BtMainPage.h"

CBtMainPage::CBtMainPage(void)
{
}

CBtMainPage::~CBtMainPage(void)
{
}

void CBtMainPage::init(void) 
{ 

} 

void CBtMainPage::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
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

void CBtMainPage::initUi(void)
{
	m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_FREE);
}

bool CBtMainPage::pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	// 跳页
	case CONTROLID_MENU_BT:
		clickEntrance(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_BACK:
		clickGoBack(e);
		break;
	case CONTROLID_BLUETOOTH_MAIN_DEVICE:
		clickDeviceMainPageEntrance(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CALL_LOG:
		clickCallHistoryPageEntrance(e);
		break;
	case CONTROLID_BLUETOOTH_MAIN_CONTACTS:
		clickPhoneBookPageEntrance(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_SETTINGS:
		clickBtSettingPageEntrance(e);
		break;
	//拔号面板
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_0:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_9:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_XIN:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_JING:
		clickDialPanel(id, e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_DELETE:
		clickBackspace(e);
		break;
	//接听
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL://jie ting
		clickAnswer(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP://gua duan
		clickHandup(e);
		break;
	//蓝牙电源
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NO_BLUETOOTH:
		clickBtPower(e);
		break;
	//声源
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER:
		clickAudioFromFlyDevice(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER:
		clickAudioFromMobile(e);
		break;
	//麦克风
	case CONTROLID_BLUETOOTH_AUDIOVOX_MIC:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SPKAER_LEFT:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SPKAER_RIGHT:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE:
		clickCalling_MicMute(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_SWITCH_CALL:
		clickSwitchCall(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_ADD_CALLS:
		clickAddCalls(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MERGE:
		clickMergeCalls(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_PAIRING:
		if(m_pBtParam->m_bIsPowerOn == 1)
		{
			clickPhonePairing(e);
		}
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_BLUETOOTH_NAME_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_BLUETOOTH_NAME_2:
		clickUsingWhichDevice(id - CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_BLUETOOTH_NAME_1,e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_JUMP_MAIN:
		clickEntrance(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}





void CBtMainPage::refreshLocalBtDeviceVersion(char* BtVersion,int len)
{  
	setUtf8String(CONTROLID_COPYRIGHT_BLUETOOTH, (u8*)BtVersion, len);
}

void CBtMainPage::refreshRemodeBtDeviceName(u8 *param,u32 len)
{
	setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_BLUETOOTH_NAME, param, len);
}

void CBtMainPage::showCallInOrCallOutInfoPanel(bool bShow, ST_PHONE_NUM *pstPhoneNum)
{
	LOGD("[%s] bShow = [%s], phone num = [%s]", __FUNCTION__,  bShow ? "Yes" : "No", pstPhoneNum->szcPhoneNum);

	setUpdateUI(false);
	if (bShow)
	{
		if ( BT_PHONE_STATUS_CALL_IN == m_pBtParam->emPhoneStatusBallon)
		{
			setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT2, STRINGID_BT_CALL_IN);
		}
		else
			setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT2, STRINGID_BT_CALL_OUT);
		
		if (pstPhoneNum)
		{	
			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT1, (u8*)pstPhoneNum->szcPhoneNum, pstPhoneNum->dwLen);
			m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT3, (u8*)pstPhoneNum->szcName, strlen(pstPhoneNum->szcName));
		}	
		else	
		{
			setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT1, (u8*)"--", strlen("--"));
			setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT3, (u8*)"--", strlen("--"));
		}
		
		
	}

	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT1, bShow);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT2, bShow);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND_TEXT3, bShow);
	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MIN_BACKGROUND, bShow);

	setUpdateUI(true);
}

void CBtMainPage::DisplayInputDialPhoneTextPrompt(E_BT_PHONE_STATUS nCallState)
{
	LOGD("[%s] E_BT_PHONE_STATUS:%d",__FUNCTION__,nCallState);
	int nStringID = 0;
	switch(nCallState)
	{
		case BT_PHONE_STATUS_FREE:
			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEXT, (u8 *)"",0);
			return;
		break;
	    case BT_PHONE_STATUS_TALKING://calling
	    {
    	    	//setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEXT, (u8 *)"",0);
    	    	nStringID = STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED;
	    }
    	break;
    	case BT_PHONE_STATUS_CALL_OUT://outing
    	    nStringID = STRINGID_BT_CALL_OUT;
		break;
    	case BT_PHONE_STATUS_CALL_IN://incoming
    	   	nStringID = STRINGID_BT_CALL_IN;
		break;
	}

	setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEXT, nStringID);

}

void CBtMainPage::refreshPhoneNumInput(char *p, u32 len)
{
    LOGD("[%s] len:%d",__FUNCTION__,len);
	if (0 == len){
		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, STRINGID_BT_INPUT_PHONE_NUMBER);
	}
	else{
		m_pBtApp->setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, (u8*)p,len);
	}
}

void CBtMainPage::DisplayingMuteButtonState()
{

	if (m_pBtParam->muteSwicthState )
		{
			m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE,1);
		}
	else
		{
		m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE,0);
		}
}

void CBtMainPage::refreshBTAudioFromFlyDeviceOrFromMobile(char cFlag)
{
	setUpdateUI(false);
	if(cFlag == 0x01)
	{
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER,true);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,false);

		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER,0);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER,1);
		
	        setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER,true);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER,true);
	}
	else if(cFlag == 0x02)
	{	
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,0);
       		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,true);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER,false);

		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER,1);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER,0);

		
	   	setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER,true);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER,true);
	}
	else if(cFlag == 0x00)
	{
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,2);
	        setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,true);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER,false);


		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER,0);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER,0);

		
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER,true);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER,true);
	}
	setUpdateUI(true);

}

void CBtMainPage::refreshBTManyCallInfo(int cFlag)
{
	LOGD("zhq[%s] ------>cFlag===%d",__FUNCTION__,cFlag);
	char one[32] = "10086";
	char two[32] = "10010";
	int onelen = strlen(one);
	int twolen = strlen(two);
	
	setUpdateUI(false);
	if(cFlag == 0x00)
	{
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL,1);
		
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_UP,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_UP,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_DOWN,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,0);	

		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, STRINGID_BT_INPUT_PHONE_NUMBER);
	}
	else if(cFlag == 0x01)
	{	
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL,1);
		
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_UP,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_DOWN,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,0);
			
		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP, STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,1);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,1);

		setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL,(u8*)m_pBtParam->m_strFirstCallNum,strlen(m_pBtParam->m_strFirstCallNum));
	}
	else if(cFlag == 0x02)
	{
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_DOWN,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,1);

		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP, STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED);
		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN, STRINGID_BT__DEVICE_MANYPEOPLECALL_WAITING);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,1);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,1);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,0);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_UP,2);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,1);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,0);
		setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,(u8*)m_pBtParam->m_strFirstCallNum,strlen(m_pBtParam->m_strFirstCallNum));
		setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,(u8*)two,twolen);
	}
	else if(cFlag == 0x03)
	{
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL,0);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_DOWN,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,1);
		setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,1);

		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP, STRINGID_BT__DEVICE_MANYPEOPLECALL_WAITING);
		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN, STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_UP,1);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,1);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,0);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,2);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,0);
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,1);
		setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,(u8*)m_pBtParam->m_strFirstCallNum,strlen(m_pBtParam->m_strFirstCallNum));
		setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,(u8*)two,twolen);
	}
	setUpdateUI(true);

}

void CBtMainPage::refreshAnswerHandup(E_BT_PHONE_STATUS e)
{   
	setUpdateUI(false);

	switch(e)
	{
	case BT_PHONE_STATUS_FREE:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DISABLE);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, WIDGET_CTRL_DISABLE);

			if(HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
			{    
				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DISABLE);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_DISABLE);
			}
			else
			{    
				if(m_pBtParam->m_stPhoneNumInput.dwLen < PHONE_NUM_MIN_SIZE)
				{
					setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DISABLE);
					setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_DISABLE);
				}
				else
				{  
					setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DEFAULT);
					setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_ENABLE);
				}
			}
		}
		break;
	case BT_PHONE_STATUS_CALL_IN:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DEFAULT);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_ENABLE);
			
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DEFAULT);	
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, WIDGET_CTRL_ENABLE);
		}
		break;
	case BT_PHONE_STATUS_CALL_OUT:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DISABLE);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_DISABLE);
				
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DEFAULT);	
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, WIDGET_CTRL_ENABLE);
		}
		break;
	case BT_PHONE_STATUS_TALKING:
		{
			if(m_pBtParam->bItsAddCalls)
			{
				if((HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus()) || (m_pBtParam->m_stPhoneNumInput.dwLen < 3))
				{
					setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL,PIC_WIDGET_STATUS_DISABLE);
					setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL,WIDGET_CTRL_DISABLE);
				}
				else
				{
					setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL,PIC_WIDGET_STATUS_DEFAULT);
					setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL,WIDGET_CTRL_ENABLE);
				}
			}
			else 
			{
				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DISABLE);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_DISABLE);
				
				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DEFAULT);	
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, WIDGET_CTRL_ENABLE);
			}
		}
		break;
	default:
		break;
	}

	setUpdateUI(true);
}

void CBtMainPage::AddCallsToUI(bool bState)
{
    setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_ADD_CALLS,bState);
}

void CBtMainPage::clickEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		m_pBtParam->bA2DP_To_DevicePageBackButton = false;
		m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
		break;
	default:
		break;
	}
}

void CBtMainPage::clickGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		m_pBtApp->setMainPageJump();
	break;
	default:
		break;
	}
}

void CBtMainPage::clickDeviceMainPageEntrance(E_MOUSE_STATUS e)
{

	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pBtParam->bA2DP_To_DevicePageBackButton = false;
			m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME);
		}
		break;
	default:
		break;
	}
}

void CBtMainPage::clickCallHistoryPageEntrance(E_MOUSE_STATUS e)
{
	
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if(HFP_CONNECT_STATUS_CONNECTED == m_pBtParam->m_eHfpConnectStatus){
				m_pBtParam->m_emSelectedPhone=PHONEBOOK_RECV;
				m_pBtApp->m_pCallRecordPages->getAndShowCallRecords(BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY);
				m_pBtApp->m_pCallRecordPages->getAndShowCallRecords_New(BT_PBAP_SYNC_PATH_RECEIVE_CALLHISTORY);
			}
			m_pBtModule->setPage(PAGE_BLUETOOTH_MOBILE_RECORD);
		}
		break;
	default:
		break;
	}
}

void CBtMainPage::clickPhoneBookPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			if(m_pBtApp->m_pBtPhoneBookPages->m_bIsLoadingPhoneBook && 
				(HFP_CONNECT_STATUS_CONNECTED ==  m_pBtModule->getBtConnectStatus()))
					m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(1);
				else
					m_pBtApp->m_pBtPhoneBookPages->clearSearchResultData();	
				m_pBtApp->m_pBtPhoneBookPages->refreshSearchPageSearchResult(0);

				switch(m_pBtParam->nNationalDistinction)
				{
					case NATIONAL_ISRAEL:
					       	if(m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage == KEY_BOARD_LANGUAGE_ISRAEL)
					        {
					              m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ISRAEL;
					        }
					        else if(m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage == KEY_BOARD_LANGUAGE_ENGLISH)
					        {
					             m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ENGLISH;
					        }
					break;
				       case NATIONAL_CHINA:
				           	m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ENGLISH;
					  	 break;
					case NATIONAL_ARAB:
						m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ARAB;
						break;
					case NATIONAL_RUSSIA:
						m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_RUSSIA;
						break;
				       default:
			           m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ENGLISH;
			       break;
				}//switch(m_pBtParam->nNationalDistinction)

			   switch(m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage)
			   	{
			   		case KEY_BOARD_LANGUAGE_ENGLISH:
						m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_EGLISH);
						break;
					case KEY_BOARD_LANGUAGE_ISRAEL:
					case KEY_BOARD_LANGUAGE_ARAB:
					case KEY_BOARD_LANGUAGE_RUSSIA:
						m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_ISRAEL);
						break;
					default:break;
			   	}       
		}
		break;
		default:break;
	}//switch(e)
}

void CBtMainPage::clickBtSettingPageEntrance(E_MOUSE_STATUS e)
{

	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING);
		}
		break;
	default:
		break;
	}
}

void CBtMainPage::clickDialPanel(u32 id, E_MOUSE_STATUS e)
{
    if(!m_pBtModule->isCanCtrlMainPageFirstLayerWidget())
		return;
		
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			int n = id - CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_0;
			char szButtonMap[13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', '+'};

			if (MOUSE_STATUS_TIMER == e && 0 == n)//长按 0 就是 +
				n = 12;
			
			switch(m_pBtModule->getBtPhoneStatus())
			{
			case BT_PHONE_STATUS_FREE:
				{
					if (m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUM_MAX_SIZE)
						break;
						
					m_pBtParam->m_stPhoneNumInput.szcPhoneNum[m_pBtParam->m_stPhoneNumInput.dwLen] = szButtonMap[n];
					m_pBtParam->m_stPhoneNumInput.dwLen++;

					refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);

					clickOpenAllModule_debug(m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
					
					refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
					setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)"", 0);
				}
				break;
			case BT_PHONE_STATUS_CALL_IN:
				break;
			case BT_PHONE_STATUS_CALL_OUT:
				break;
			case BT_PHONE_STATUS_TALKING:
				{
					if (m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUm_nNPUT_MAX_SIZE)
						break;
					m_pBtParam->m_stPhoneNumInput.szcPhoneNum[m_pBtParam->m_stPhoneNumInput.dwLen] = szButtonMap[n];
					m_pBtParam->m_stPhoneNumInput.dwLen++;
					refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
					g_pClsBtAdapter->btHfpCmdSendDtmf(szButtonMap[n]);
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}//switch(e)
}

void CBtMainPage::clickBackspace(E_MOUSE_STATUS e)
{
	if(!m_pBtModule->isCanCtrlMainPageFirstLayerWidget())
		return;
	
	switch(e)
	{
	case MOUSE_STATUS_UP:
	//case MOUSE_STATUS_TIMER:
		{
			if(m_pBtParam->m_stPhoneNumInput.dwLen <= 0)
				return;

			m_pBtParam->m_stPhoneNumInput.szcPhoneNum[m_pBtParam->m_stPhoneNumInput.dwLen - 1] = 0;
			m_pBtParam->m_stPhoneNumInput.dwLen--;

			refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
			refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)"", 0);
		}
		break;
	case MOUSE_STATUS_TIMER:
		{
			if(m_pBtParam->m_stPhoneNumInput.dwLen <= 0)
				return;

			memset(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,0,sizeof(m_pBtParam->m_stPhoneNumInput.szcPhoneNum));
			m_pBtParam->m_stPhoneNumInput.dwLen = 0;

			refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
			refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)"", 0);
		}
		break;
	default:
		break;
	}
}

void CBtMainPage::clickAnswer(E_MOUSE_STATUS e)
{				
	if(HFP_CONNECT_STATUS_CONNECTED !=  m_pBtModule->getBtConnectStatus())
		return;
	
	switch(e)
	{
	case MOUSE_STATUS_UP:
	{
		switch(m_pBtModule->getBtPhoneStatus())
		{
			case BT_PHONE_STATUS_FREE:
				{
					if(m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUM_MIN_SIZE)
					{//拔号出去
						u8 number[PHONE_NUm_nNPUT_MAX_SIZE];
						memset(number,0,PHONE_NUm_nNPUT_MAX_SIZE);
						memcpy(number, m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
			
						g_pClsBtAdapter->btCallOperation_CallOut(number,m_pBtParam->m_stPhoneNumInput.dwLen);
						m_pBtHal->setToHalMobileStatus(2);
						m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_OUT,(char*)number,m_pBtParam->m_stPhoneNumInput.dwLen);
					}
					
				}
				break;
			case BT_PHONE_STATUS_CALL_IN:
				{//接听
					g_pClsBtAdapter->btCallOperation_Answer();
					showCallInOrCallOutInfoPanel(false, NULL);
				}
				break;
			case BT_PHONE_STATUS_TALKING:
				{
					if(m_pBtParam->bItsAddCalls)
					{
						if(m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUM_MIN_SIZE)
						{
							m_pBtParam->bItsAddCalls = false;
							AddCallsToUI(m_pBtParam->bItsAddCalls);
							
							u8 number[PHONE_NUm_nNPUT_MAX_SIZE] = {0};
							memcpy(number, m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);

							//m_pBtParam->m_bCanSendData = true;
							g_pClsBtAdapter->btCallOperation_CallOut(number,m_pBtParam->m_stPhoneNumInput.dwLen);
							m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_OUT,(char*)number,m_pBtParam->m_stPhoneNumInput.dwLen);

							m_pBtParam->m_ePhoneStatus = BT_PHONE_STATUS_CALL_OUT;
							refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
							m_pBtModule->getBtPhoneStatus();

							ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_CALL_OUT,true,true,m_pBtParam->m_stPhoneNumInput.szcName,m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
						}
					}
				
				}
				break;
			default:
				break;
		}//switch(m_pBtModule->getBtPhoneStatus())
	}
	break;//case MOUSE_STATUS_UP:
	case MOUSE_STATUS_DOWN:
	{
		if(m_pBtParam->str_CallInfor[1].nCaller_State == WAITING_CALL)
		{
			setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL,1);
			return ;
		}
		if((m_pBtParam->str_CallInfor[0].nCaller_State == HELD_CALL && m_pBtParam->str_CallInfor[1].nCaller_State == ACTIVE_CALL ) ||
			(m_pBtParam->str_CallInfor[0].nCaller_State == ACTIVE_CALL && m_pBtParam->str_CallInfor[1].nCaller_State == HELD_CALL))
		{
			setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL,1);
			return ;
		}
		switch(m_pBtModule->getBtPhoneStatus())
		{
			case BT_PHONE_STATUS_FREE:
				break;
			case BT_PHONE_STATUS_CALL_IN:
				break;
			case BT_PHONE_STATUS_CALL_OUT:
				return;
				break;
			case BT_PHONE_STATUS_TALKING:
				return;
				break;
			default:
				return;
				break;
		}
		setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL,1);
	}
	break;//case MOUSE_STATUS_DOWN:
	default:
	break;
	}//switch(e)
}

void CBtMainPage::ActShowCallingInfor_aboutWhenOnlyOneCall(E_BT_PHONE_STATUS nCallState,bool bShowInputNumbDialog,bool bShowName_Prompt,s8 *strName,s8 *strNumber)
{
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,bShowName_Prompt);
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL,bShowInputNumbDialog);    
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEXT,bShowName_Prompt);
    if(bShowName_Prompt)
    {
    	DisplayInputDialPhoneName(strName);
    	DisplayInputDialPhoneNumber(strNumber);
    	
    	DisplayInputDialPhoneTextPrompt(nCallState);
	}
	else
	{
       DisplayInputDialPhoneName((s8 *)"");
    	DisplayInputDialPhoneNumber((s8 *)"");
    	
    	DisplayInputDialPhoneTextPrompt(BT_PHONE_STATUS_FREE);
	}

}

void CBtMainPage::DisplayInputDialPhoneName(s8 *str_name)
{
    int str_NameLen = strlen(str_name);
	
	if(str_NameLen == 0)
	{
		setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8 *)"",0);
	}
	else
	{
	    LOGD("DisplayInputDialPhoneName---->str_name = |%s|----**----|%d|---",str_name,str_NameLen);
		setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,(u8 *)str_name,str_NameLen);
	}
}
void CBtMainPage::DisplayInputDialPhoneNumber(s8 *str_number)
{
    s32 str_NumberLen = strlen(str_number);
	
	if(str_NumberLen == 0)
	{
		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, STRINGID_BT_INPUT_PHONE_NUMBER);
	}
	else
	{
		setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL,(u8 *)str_number,str_NumberLen);
	}
}

void CBtMainPage::clickHandup(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_DOWN:
		{
			switch(m_pBtModule->getBtPhoneStatus())
			{
			case BT_PHONE_STATUS_CALL_IN:
			case BT_PHONE_STATUS_CALL_OUT:
			case PHONE_STATUS_CALL_OUTING:
			case BT_PHONE_STATUS_TALKING:
				{
					setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_ACTIVATED);
				}
				break;
			default:
				break;
			}
		}
		break;
		case MOUSE_STATUS_UP:
		{
			switch(m_pBtModule->getBtPhoneStatus())
			{
				case BT_PHONE_STATUS_CALL_IN:
				case BT_PHONE_STATUS_CALL_OUT:
				case BT_PHONE_STATUS_TALKING:
				{
					setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DEFAULT);
					g_pClsBtAdapter->btCallOperation_HandUp();	
				}
					break;
				default:
					break;
				}
		}
		break;
		default:
		break;
	}//switch(e)
}

void CBtMainPage::clickBtPower(E_MOUSE_STATUS e)
{  
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			bool bState = m_pBtModule->isPowerOn();
	
			if (bState){	
				m_pBtHal->setToHalBtPower(0x00);				
			}
			else{
				m_pBtHal->setToHalBtPower(0x01);
			}
		}
		break;
	default:
		break;
	}
}

void CBtMainPage::clickAudioFromMobile(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if(HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
				return;

			E_BT_PHONE_STATUS e = m_pBtModule->getBtPhoneStatus();
			if (BT_PHONE_STATUS_TALKING != e)
				return;
			if (m_pBtParam->m_eHfpAudioSource == HFP_AUDIO_SOURCE_MOBILE)
				return;
			g_pClsBtAdapter->btAnswerformCarOrPhone(0x01);

		}
		break;
	default:
		break;
	}
}

void CBtMainPage::clickAudioFromFlyDevice(E_MOUSE_STATUS e)
{	
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if(HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
				return;

			E_BT_PHONE_STATUS e = m_pBtModule->getBtPhoneStatus();
			if (BT_PHONE_STATUS_TALKING != e)
				return;
			
			LOGD("[%s] m_pBtParam->m_eHfpAudioSource:%x",__FUNCTION__,m_pBtParam->m_eHfpAudioSource);
			if (m_pBtParam->m_eHfpAudioSource == HFP_AUDIO_SOURCE_BT)
				return;
			g_pClsBtAdapter->btAnswerformCarOrPhone(0x00);

		}
		break;
	default:
		break;
	}
}
void CBtMainPage::clickCalling_MicMute(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if(HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
				return;

			E_BT_PHONE_STATUS em_PhoneStatus = m_pBtModule->getBtPhoneStatus();
			if (!(BT_PHONE_STATUS_TALKING == em_PhoneStatus))
				return;

			if (m_pBtParam->muteSwicthState){
				m_pBtModule->btToModule_NotifyAudiovideo_BT_MicSwitch(0x00);
				g_pClsBtAdapter->setBtMicMute(0x00);
			}
			else{
				m_pBtModule->btToModule_NotifyAudiovideo_BT_MicSwitch(0x01);
				g_pClsBtAdapter->setBtMicMute(0x01);
			}
		}
		break;
	default:
		break;
	}
}

void CBtMainPage::clickSwitchCall(E_MOUSE_STATUS e)
{
}
void CBtMainPage::clickAddCalls(E_MOUSE_STATUS e)
{
	
}
void CBtMainPage::clickMergeCalls(E_MOUSE_STATUS e)
{

}
void CBtMainPage::clickPhonePairing(E_MOUSE_STATUS e)
{  
	if(m_pBtParam->m_bIsPowerOn == 0)
		return;
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pBtModule->setPage(PAGE_BLUETOOTH_PHONEPAIR);
			setAnsiSerialData(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_DEVICE_NAME,(u8*)m_pBtParam->szLocalBtDevice_Name,strlen(m_pBtParam->szLocalBtDevice_Name));
			setAnsiSerialData(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_PASSWORD,(u8*)m_pBtParam->szLocalBtDevice_PinCode,strlen(m_pBtParam->szLocalBtDevice_PinCode));
			//m_pBtParam->_w_bPairing = true;
			//m_pBtParam->iPairedStatus = 0;
		}
		break;
	default:
		break;
	}
}
void CBtMainPage::clickUsingWhichDevice(u8 param,E_MOUSE_STATUS e)
{
}

void CBtMainPage::clickOpenAllModule_debug(char *param)
{
	bool bIsOpen = false;
	if(strcmp(param,KEYWORD_MODE_OPEN_LOGCAT) == 0)
	{
		bIsOpen = true;
	}
	else if(strcmp(param,KEYWORD_MODE_CLOSE_LOGCAT) == 0)
	{
		bIsOpen = false;
	}
	else
	{
		return;
	}

	for(int i = 0; i < DBG_ALL_MODULE_COUNT;i++)
	{
		char property[PROPERTY_VALUE_MAX] = {0};
		sprintf(property, "%d",bIsOpen);
		property_set(g_dbgAllModuleProperty[i], property);
	}

	memset(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,0,sizeof(m_pBtParam->m_stPhoneNumInput.szcPhoneNum));
	m_pBtParam->m_stPhoneNumInput.dwLen = 0;
	refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
}

