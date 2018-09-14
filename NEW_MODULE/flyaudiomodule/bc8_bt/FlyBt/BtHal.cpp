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
	LOGD("[%s] [%s]",__FILE__ , __FUNCTION__);
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
	
	g_pClsBtBC6Adapter->init(m_pBtHal,m_pBtApp,m_pBtParam);
	g_pClsBtJniSdk->init(m_pBtHal,m_pBtApp,m_pBtParam,m_pBtModule);
	
}

void CBtHal::analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len)
{
	LOGD("[%s]: cmd = [0x%x] ", __FUNCTION__,  cmd);
	switch(cmd)
	{
		case 0xE3://BC08
			separateCmd_((char*)p,len);
			break;
		case 0x10:
			getHfpPowerState(p[0]);
		default:
			break;
	}
}

void CBtHal::separateCmd_(char *p,int len)//BC8
{
	outPutLog(__FUNCTION__,  "p:", (u8*)p, len);

	char *pFrom = p;
	int nLess = len;
	while(true)
	{
		int nFrom = 0, nTo = 0;
		nFrom = g_pClsBtBC6Adapter->findCharIndex((unsigned char*)pFrom, nLess, '\r');//0d
		if (-1 == nFrom)
			break;
		nFrom++;

		
		nTo = g_pClsBtBC6Adapter->findCharIndex((unsigned char*)pFrom, nLess, '\n');//0a
		if (-1 == nTo)
			break;

		g_pClsBtBC6Adapter->analyseAnsCmd_(pFrom,nTo - 1);
		nLess = nLess - nTo - 1;
		pFrom = pFrom + nTo + 1;

		if (nLess <= 0)
			break;
				
	}

}

void CBtHal::analyseAgentMessage(moduleid_t id, u8 *p, u8 len)
{
}

void CBtHal::getHfpPowerState(char state)
{

   	LOGD("[%s] cState:%d",__FUNCTION__, state);

	m_pBtModule->sendToFlyJniSdkPowerState(state);
	m_pBtApp->btToApp_SendBtPowerState(state);
	g_pClsBtJniSdk->sendToAppBtSwitchStatus(state);

	if(m_pBtParam->m_bIsPowerOn == state)
		return;
	m_pBtParam->m_bIsPowerOn = state;
	
	if(state == 0x00)
	{
		clearAfterHfpPowerOff();
	}
	else
	{
		initParamAfterHfpPowerOn();
	}
    
}

void CBtHal::clearAfterHfpPowerOff()
{
	setDefaultParamAfterHfpPowerOff();
	clearHistoryAfterHFPDisconnect();
	clearPhoneNumInput();
	getA2DPStatus(0);
	m_pBtApp->m_pBtMainPage->DisplayingMuteButtonState();
	m_pBtModule->btToApp_SendConnectState(0);
	m_pBtParam->m_listBtDevicesHavePaired.clear();
	m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH);
	m_pBtModule->deleteNativeTimer(TIME_ID_ONE_TOUCH_SPEED_CONNECT_SWITCH);
			
	m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired(0);
	m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired_New(0);
	FormatBtMacAddress((char*)"",0);
	m_pBtApp->m_pA2DPpages->ToUI_aboutSupportMusicBrowsings(false);

	m_pBtParam->m_tempListHistoryCall.clear();
}

void CBtHal::setDefaultParamAfterHfpPowerOff()
{
	m_pBtParam->m_bIsLocalBtDeviceInitOk=false;
	m_pBtParam->m_bIsMicOpen = true;
	m_pBtParam->m_eHfpConnectStatus = HFP_CONNECT_STATUS_DISCONNECT;
	m_pBtParam->m_ePhoneStatus=BT_PHONE_STATUS_FREE;
	
	m_pBtApp->setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NO_BLUETOOTH,0);	
	m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DISABLE);
	m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_TURNED_OFF);
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE_TEXT,(u8*)"", 0);
	m_pBtApp->setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_NAME_TEXT,(u8*)"", 0);
	m_pBtApp->setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_SET_BLUETOOTH_MAC_TEXT,(u8*)"", 0);

	m_pBtParam->emTempHfpConnectStatus = HFP_CONNECT_STATUS_DISCONNECT;
	m_pBtParam->emTempHfpTalkingTransferSet = HFP_AUDIO_SOURCE_UNKNOW;
	m_pBtParam->emTempHfpPhoneStatus = BT_PHONE_STATUS_FREE;
	m_pBtParam->m_SendMessageBuf.count = 0;
	m_pBtModule->deleteNativeTimer(TIMER_BC8_NOTRECEIVE);
	m_pBtParam->m_bCanSendData = true;
	m_pBtParam->m_bVoiceRecgStatus = 0x00;
	
}

void CBtHal::initParamAfterHfpPowerOn()
{
	m_pBtParam->nCallCount = CALLING_COUNT_FREE;
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE_TEXT,(u8*)m_pBtParam->szLocalBtDevice_PinCode, strlen(m_pBtParam->szLocalBtDevice_PinCode));
	m_pBtApp->m_pBtDevicePages->clickDisplaySetDeviceNameToUi((u8*)m_pBtParam->szLocalBtDevice_Name,(u32)strlen(m_pBtParam->szLocalBtDevice_Name));

	g_pClsBtBC6Adapter->setToBtChipQueryHavePairDevices();
	g_pClsBtBC6Adapter->setToBtChipQueryLocalBtMacAddr();

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

void CBtHal::getHfpConnectStatus(E_HFP_CONNECT_STATUS e)
{
   	LOGD("[%s] E_HFP_CONNECT_STATUS:%d",__FUNCTION__,e);
	if(e == m_pBtParam->m_eHfpConnectStatus)
	{
		return;
	}

	if(HFP_CONNECT_STATUS_CONNECTING != e)
		m_pBtParam->m_eHfpConnectStatus = e;
	
	if(HFP_CONNECT_STATUS_CONNECTING == e)
	{
		//g_pClsBtBC6Adapter->setToBtChipStartPairMode();
	}
	else if(HFP_CONNECT_STATUS_CONNECTED == e)
	{
		m_pBtParam->cUpdataPhoneBookCountIndex = 0;
   		g_pClsBtBC6Adapter->setToBtChipQueryBtChipName();
		m_pBtModule->golf_sendToCarScreen_PhoneConnState(1);
		m_pBtModule->btToOtherModule_Auxscreen_Phone_status(0x00);
		refreshParamAfterHFPConnected();

		g_pClsBtBC6Adapter->setToBtChipSyncAllCallLog();

		m_pBtHal->syncInitCallRecordAllTime();
		m_pBtParam->m_bSetRecordTimeSign = true;
		m_pBtHal->syncInitCallRecord();
		
		m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(1);
		m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(1);
		
		g_pClsBtBC6Adapter->setToBtChipQueryHavePairDevices();
		g_pClsBtBC6Adapter->setToBtChipQueryA2dpStatus();

		if((m_pBtModule->getCurPageId() == PAGE_BLUETOOTH_AUDIOVOX_SEARCH_FRAME) || (m_pBtModule->getCurPageId() == PAGE_BLUETOOTH_AUDIOVOX_SEARCH)|| (m_pBtModule->getCurPageId() == PAGE_BLUETOOTH_PHONEPAIR) || (m_pBtModule->getCurPageId() == PAGE_BLUETOOTH_PAIRING_DIALOG_BOX))
		{
			if(m_pBtModule->getPrePageId() == PAGE_BLUETOOTH_A2DP && m_pBtParam->bA2DP_To_DevicePageBackButton){

			}
			else{
				m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
			}
		}
		m_pBtModule->btToModule_golf_updatePhoneBook();
		
		m_pBtParam->bIsSpeedConnectState = false;
		m_pBtModule->deleteNativeTimer(TIME_ID_ONE_TOUCH_SPEED_CONNECT_SWITCH);

	}
	else if(HFP_CONNECT_STATUS_DISCONNECT == e) 
	{
	  	clearHistoryAfterHFPDisconnect();
	}

	m_pBtParam->emTempHfpConnectStatus = e;
}

void CBtHal::refreshParamAfterHFPConnected()
{
	m_pBtParam->m_listPhoneBook.clear();
	m_pBtHal->clearListHistoryCall();
	memset(&m_pBtParam->st_UserInforsOnetouchDial,0,sizeof(ST_CALL_RECORD_ONE_USER_INFO));
	
	m_pBtParam->m_nBtConnectSign = 0;
	m_pBtParam->m_listBtDevicesHavePaired.clear();
	m_pBtModule->btToApp_SendConnectState(1);
	m_pBtModule->ToOSDandAPPaboutConnectState(1);
	m_pBtModule->sendToFlyJniSdkConnectState(1);
	m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_CONNECTED_DEVICES);

	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,1);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1,1);

	getHfpPhoneStatus(BT_PHONE_STATUS_FREE);
	g_pClsBtJniSdk->sendToAppBtConnectStatus(0x01);
}

void CBtHal::clearHistoryAfterHFPDisconnect()
{
	setParamAfterHFPDisconnect();
	clearPhoneBookAndHistoryCall(); 
	clearAfterHandup();
	m_pBtApp->m_pBtMainPage->refreshBTAudioFromFlyDeviceOrFromMobile(HFP_AUDIO_SOURCE_UNKNOW);
	m_pBtApp->m_pCallRecordPages->clearCallHistoryTypeStatus();
	m_pBtApp->m_pBtMainPage->refreshAnswerHandup(BT_PHONE_STATUS_FREE);
	//m_pBtApp->m_pBtMainPage->refreshBTManyCallInfo(0);
	m_pBtApp->m_pBtMainPage->CallingAndWaitingFunction_DisplayingToUI(MULTI_CALL_FREE);
	//m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH);
	getHfpPhoneStatus(BT_PHONE_STATUS_FREE);
	//m_pBtModule->deleteNativeTimer(TIMER_BC06_SYNC_CALL_LOGS_FREE);
	m_pBtApp->m_pA2DPpages->clearA2DPInfo();
	m_pBtModule->btToModule_NotifyCenter_StopRing();
	m_pBtModule->sendToFlyJniSdkConnectState(0);
	m_pBtHal->getA2DPPlayOrStopStatus(1);
	m_pBtModule->deleteNativeTimer(TIMER_SET_CALLING_TIMES_1);
	m_pBtModule->deleteNativeTimer(TIMER_BC06_A2DPTIME);
	m_pBtModule->deleteNativeTimer(TIMER_BC06_AUTOCONNECT);
	m_pBtApp->m_pCallRecordPages->showLoadingCallLogTips(0);
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_CALL_RECORED);
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_CALL_RECORED_CLEAR);
	if(m_pBtParam->m_nBtConnectSign == 1)
	{
		m_pBtModule->btToApp_SendConnectState(0);

		if(m_pBtParam->emTempHfpConnectStatus != HFP_CONNECT_STATUS_CONNECTING){
			m_pBtModule->ToOSDandAPPaboutConnectState(0);
		}
	}
	m_pBtModule->golf_sendToCarScreen_PhoneConnState(0);
	m_pBtHal->getA2DPStatus(false);

	m_pBtParam->m_bSetBookTimeSign = false;
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_INIT_PHONE_BOOK);
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_INIT_PHONE_BOOK_ALL_TIME);

	m_pBtParam->m_bSetRecordTimeSign = false;
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_INIT_CALL_RECORED);
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_INIT_CALL_RECORED_ALL_TIME);
	m_pBtApp->m_pBtPhoneBookPages->clearOneNameForMultNumShow();
	m_pBtModule->deleteNativeTimer(TIMER_SET_VOICE_DAILING_STATUS);
	m_pBtParam->m_bVoiceRecgStatus = 0x00;
	m_pBtHal->supportVoiceStatus(0x00);
	g_pClsBtJniSdk->sendToAppBtConnectStatus(0x00);
	g_pClsBtJniSdk->sendToAppBtPhoneStatus((u8)m_pBtParam->m_ePhoneStatus);

	m_pBtModule->btToOtherModule_Auxscreen_Phone_status(0x07);
	m_pBtModule->btClearAuxscreenA2DPInfors();
}

void CBtHal::setParamAfterHFPDisconnect()
{
	m_pBtParam->bHandleStopSearchState = false;
	m_pBtParam->m_nBtConnectSign += 1;
	m_pBtParam->bItsAddCalls = false;
	m_pBtApp->m_pBtMainPage->AddCallsToUI(m_pBtParam->bItsAddCalls);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_2,0);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BACKGROUND_TEXT_1,0);
	m_pBtApp->setGroupNumber(CONTROLID_BLUETOOTH_AUDIOVOX_NEW_SEACH_FRAME_BACKGROUND_TEXT_1,0);
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_MAIN_CALL_IN_OR_OUT, (u8*)"",0);
	m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, STRINGID_BT_INPUT_PHONE_NUMBER);
	m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE,0);
	m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_MUTE_MIC,0);
	getCurConnectedBtDeviceName("", 0);
	if(m_pBtParam->m_bIsPowerOn == 1)
	{
		if(m_pBtParam->bIsSpeedConnectState)
		{
		}
		else
		{
			m_pBtApp->setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, STRINGID_BT__DEVICE_DEVICE_IS_DISCONNECTED);
		}
	}
	if(0==(m_pBtParam->m_listBtDevicesHavePaired).size() && m_pBtParam->m_bIsPowerOn == 1)
	{
		m_pBtApp->setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BOTTOM_TEXT, (u8*)"", 0);
	}

	m_pBtParam->bAfterDialingSyncCallLogs = false;
	m_pBtParam->bNoA2dpChannelPlay = false;
	m_pBtParam->bIsPairBox = false;
	m_pBtParam->m_listCallLog_All.clear();
	m_pBtParam->m_listCallLog_Miss.clear();
	m_pBtParam->m_listCallLog_Dialed.clear();
	m_pBtParam->m_listCallLog_Riceived.clear();
}

void CBtHal::clearPhoneBookAndHistoryCall()
{
	//clear Phone list and refresh
	m_pBtParam->m_listPhoneBook.clear();
	m_pBtParam->m_listHistoryCall.clear();
	m_pBtParam->m_listHistoryCall_Miss.clear();		 
	m_pBtParam->m_listHistoryCall_Dialed.clear();	
	m_pBtParam->m_listHistoryCall_Riceived.clear();
	
	m_pBtApp->m_pBtPhoneBookPages->m_mapPhoneNumUserInfo.clear();//utf8
	m_pBtApp->m_pBtPhoneBookPages->m_listPhoneNumUserInfoHaveSelected.clear();
	//m_pBtApp->m_pBtPhoneBookPages->refreshSearchPageSearchResult(0);

	m_pBtApp->m_pBtPhoneBookPages->m_mapPhoneNumRankUserInfo.clear();//utf8
	m_pBtApp->m_pBtPhoneBookPages->m_listPhoneNumRankUserInfoHaveSelected.clear();
	m_pBtApp->m_pBtPhoneBookPages->m_listPhoneNumAccurateSearch.clear();
	
	m_pBtHal->m_pBtApp->m_pBtPhoneBookPages->m_bIsLoadingPhoneBook=true;
	m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(0);	
	
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

	//m_pBtApp->setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1,false);
	//m_pBtApp->setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_2,false);
	//m_pBtApp->setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_3,false);
	//clear calllog history and refresh

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

	for(int r=0;r<5;r++)
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

void CBtHal::getHfpDialingTransferPosStatus(E_BT_PHONE_STATUS e)
{
	switch(e)
	{
		case BT_PHONE_STATUS_RECEIVE_BULETOOTH:
		{
			m_pBtHal->getHfpAudioSource(HFP_AUDIO_SOURCE_CAR);
			m_pBtApp->m_pBtMainPage->refreshBTAudioFromFlyDeviceOrFromMobile(HFP_AUDIO_SOURCE_CAR);
			
			if(m_pBtParam->emTempHfpPhoneStatus ==  BT_PHONE_STATUS_TALKING)
				m_pBtModule->btToOtherModule_Auxscreen_Phone_status(0x03);
		}
		break;
		case BT_PHONE_STATUS_RECEIVE_PHONE:
		{
			m_pBtHal->getHfpAudioSource(HFP_AUDIO_SOURCE_MOBILE);
			m_pBtApp->m_pBtMainPage->refreshBTAudioFromFlyDeviceOrFromMobile(HFP_AUDIO_SOURCE_MOBILE);
			
			if(m_pBtParam->emTempHfpPhoneStatus ==  BT_PHONE_STATUS_TALKING)
				m_pBtModule->btToOtherModule_Auxscreen_Phone_status(0x06);
		}
		break;
		default:break;
	}
}

void CBtHal::SyncPhoneBookSIM()
{
	if(m_pBtParam->bAfterDialingSyncCallLogs == false){
		g_pClsBtBC6Adapter->setToBtChipSyncPhoneBookSIM();
	}

	m_pBtParam->bAfterDialingSyncCallLogs = false;
}

void CBtHal::getHfpDiallingFree_SyncCallLogs(E_BT_PHONE_STATUS e)
{
	if(e == BT_PHONE_STATUS_FREE)
	{
		m_pBtModule->setNativeTimer(2000,1,TIMER_BC06_SYNC_CALL_LOGS_FREE);
	}
}

void CBtHal::getHfpPhoneStatus(E_BT_PHONE_STATUS e)
{
	E_BT_PHONE_STATUS em = e;
	LOGD("[%s] PhoneStatus=%x CallCount=%x",__FUNCTION__,em,m_pBtParam->nCallCount);
	if(em == BT_PHONE_STATUS_FREE)
	{
		setFm1388Switch(true);
		m_pBtParam->bHangUpAutoDailin = false;
		memset(m_pBtParam->m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemInName,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemOutNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemOutName,0,PHONE_NUm_nNPUT_MAX_SIZE);

		if(m_pBtParam->nCallCount == CALLING_COUNT_ONLY){
			m_pBtParam->nCallCount = CALLING_COUNT_FREE;
		}
		else if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL){
			m_pBtParam->nCallCount = CALLING_COUNT_ONLY;
		}
		g_pClsBtJniSdk->sendToAppBtPhoneStatus(0x00);
	}
	else if(em == BT_PHONE_STATUS_CALL_IN)
	{
		memset(m_pBtParam->m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		if(m_pBtParam->nCallCount == CALLING_COUNT_ONLY){
			m_pBtParam->nCallCount = CALLING_COUNT_MUTIL;
		}
		else if(m_pBtParam->nCallCount == CALLING_COUNT_FREE){
			m_pBtParam->nCallCount = CALLING_COUNT_ONLY;
		}
		g_pClsBtJniSdk->sendToAppBtPhoneStatusAndNum(0x01,m_pBtParam->m_strTemInNum,strlen(m_pBtParam->m_strTemInNum),m_pBtParam->m_strTemInName,strlen(m_pBtParam->m_strTemInName));
	}
	else if(em == BT_PHONE_STATUS_CALL_OUT)
	{
		memset(m_pBtParam->m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		if(m_pBtParam->nCallCount == CALLING_COUNT_ONLY){
			m_pBtParam->nCallCount = CALLING_COUNT_MUTIL;
		}
		else if(m_pBtParam->nCallCount == CALLING_COUNT_FREE){
			m_pBtParam->nCallCount = CALLING_COUNT_ONLY;
		}
		g_pClsBtJniSdk->sendToAppBtPhoneStatusAndNum(0x02,m_pBtParam->m_strTemOutNum,strlen(m_pBtParam->m_strTemOutNum),m_pBtParam->m_strTemOutName,strlen(m_pBtParam->m_strTemOutName));
	}
	else if(em == BT_PHONE_STATUS_TALKING)
	{
		analyCallData(m_pBtParam->m_strTemCallingNum,strlen(m_pBtParam->m_strTemCallingNum));

		memset(m_pBtParam->m_strTemInNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemInName,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemOutNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemOutName,0,PHONE_NUm_nNPUT_MAX_SIZE);
		g_pClsBtJniSdk->sendToAppBtPhoneStatus(0x03);				
		setFm1388Switch(false);
	}
	else if(em == BT_PHONE_STATUS_CALL_IN_FROM_THIRD ||
			em == BT_PHONE_STATUS_CALL_MEETING)
	{
		m_pBtParam->nCallCount = CALLING_COUNT_MUTIL;
	}

	LOGD("[%s] m_pBtParam->nCallCount=%x",__FUNCTION__,m_pBtParam->nCallCount);

	if(em == BT_PHONE_STATUS_FREE ||
	em == BT_PHONE_STATUS_CALL_IN ||
	em == BT_PHONE_STATUS_CALL_OUT ||
	em == BT_PHONE_STATUS_TALKING)
	{
			m_pBtParam->m_ePhoneStatus = em;
			m_pBtModule->sendToFlyJniSdkPhoneStatus(m_pBtParam->m_ePhoneStatus);   
	}

	if(em != m_pBtParam->emTempHfpPhoneStatus)
	{
		if(BT_PHONE_STATUS_TALKING == em)
			m_pBtModule->btToModule_NotifyExternalctrl_VoiceSwitchCtrl(0x00);
		else 
			m_pBtModule->btToModule_NotifyExternalctrl_VoiceSwitchCtrl(0x01);
	}

	if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
	{
		getHfpPhoneStatus_Multi_Call(em);
		return;
	}

	m_pBtParam->bItsAddCalls = false;
	m_pBtApp->m_pBtMainPage->AddCallsToUI(m_pBtParam->bItsAddCalls);
	m_pBtApp->m_pBtMainPage->CallingAndWaitingFunction_DisplayingToUI(MULTI_CALL_FREE);
		

	if(em == BT_PHONE_STATUS_FREE)
	{
		m_pBtParam->bSpecialHangUpIsStillOnHold = false;
		memset(m_pBtParam->m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->m_strTemWaitingName,0,PHONE_NUm_nNPUT_MAX_SIZE);

		m_pBtParam->str_CallInfor[0].m_bIsMicOpenState = true;
		m_pBtParam->str_CallInfor[0].nCaller_State = CALL_RELEASED;
		memset(m_pBtParam->str_CallInfor[0].cCaller_numb,0,PHONENUM_OR_PHONENAME_MAX_LEN);
		m_pBtParam->str_CallInfor[0].nCaller_numbLen = 0;
		memset(m_pBtParam->str_CallInfor[0].cCaller_name,0,PHONENUM_OR_PHONENAME_MAX_LEN);
		m_pBtParam->str_CallInfor[0].nCaller_nameLen= 0;

		m_pBtParam->str_CallInfor[1].m_bIsMicOpenState = true;
		m_pBtParam->str_CallInfor[1].nCaller_State = CALL_RELEASED;
		memset(m_pBtParam->str_CallInfor[1].cCaller_numb,0,PHONENUM_OR_PHONENAME_MAX_LEN);
		m_pBtParam->str_CallInfor[1].nCaller_numbLen = 0;
		memset(m_pBtParam->str_CallInfor[1].cCaller_name,0,PHONENUM_OR_PHONENAME_MAX_LEN);
		m_pBtParam->str_CallInfor[1].nCaller_nameLen= 0;
		
		analyCallData("",0);
		memset(m_pBtParam->m_strFirstCallNum, 0, PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->szPhoneNumCallInOrOut, 0, PHONE_NUm_nNPUT_MAX_SIZE);
		m_pBtApp->m_pBtMainPage->AddCallsAndMergeButtonSwitchToUI(true);
		m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_FREE,true,false,(char *)"",(char *)"");

		m_pBtApp->m_pBtMainPage->showCallInTalkingKeyboardHiddenButton(0x00);
		m_pBtApp->m_pBtMainPage->showOrHiddenTalkingPopUp(false);
		
		m_pBtParam->emTempHfpTalkingTransferSet = HFP_AUDIO_SOURCE_UNKNOW;
		clearAfterHandup();
		m_pBtParam->m_bIsMicOpen = true;
		m_pBtApp->m_pBtMainPage->DisplayingMuteButtonState();
		
		m_pBtModule->btToModule_NotifyCenter_StopRing();
		m_pBtApp->m_pBtMainPage->refreshBTAudioFromFlyDeviceOrFromMobile(HFP_AUDIO_SOURCE_UNKNOW);
		
		clearPhoneNumInput();
		
		setToHalMobileStatus(0);

		LOGD("[%s] m_pBtParam->m_bAutoJump=%x",__FUNCTION__,m_pBtParam->m_bAutoJump);	
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
				LOGD("[%s] CurPageID:%x",__FUNCTION__,CurPageID);
				if(CurPageID == PAGE_BLUETOOTH_MAIN)
				{
					int PrePageID = m_pBtModule->getPrePageId();
					LOGD("[%s] PrePageID:%x",__FUNCTION__,PrePageID);
					if(PrePageID == PAGE_GPS_PAGE)
					{
						m_pBtModule->setPrePage();
						m_pBtParam->m_bAutoJump = false;
					}
				}
			}
		}

		m_pBtParam->bSpecialCaseBackPage = false;
	}
	else if(em == BT_PHONE_STATUS_CALL_IN)
	{
		m_pBtApp->setStringById(CONTROLID_BLUETOOTH_MAIN_CALL_IN_OR_OUT, STRINGID_BT_CALL_IN);
		setToHalMobileStatus(1);
		m_pBtModule->btToModule_NotifyCenter_StartRing((u8)2);
		if(!m_pBtModule->getBackCarStatus())
		{
				int CurPageID = m_pBtModule->getCurPageId();
				if(CurPageID != PAGE_BLUETOOTH_MAIN && CurPageID != PAGE_BACK_NOVIDEO && CurPageID != PAGE_BACK_VIDEO)
				{
					m_pBtParam->m_ePhoneStatus = BT_PHONE_STATUS_CALL_IN;
					#ifdef MSM_ANDROID_ISR_NEW_FUNCTION
					if(m_pBtApp->DontDisplayWindowPromptAboutT123Video())
					{
						m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);  
						m_pBtParam->m_bAutoJump = true;
					}
					#else
					m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);  
					m_pBtParam->m_bAutoJump = true;
					#endif
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
	else if(em == BT_PHONE_STATUS_CALL_OUT)
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
	else if(em == BT_PHONE_STATUS_TALKING)
	{
		m_pBtModule->btToModule_NotifyCenter_StopRing();
		m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(false,NULL);
		m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_TALKING,true,true,m_pBtParam->str_CallInfor[0].cCaller_name,m_pBtParam->str_CallInfor[0].cCaller_numb);
		setToHalMobileStatus(3);
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		///Phone calling,answer the phone side,the sound is switched to the phone side!/////
		LOGD("----%d %d %d",m_pBtParam->m_eHfpAudioSource,m_pBtParam->emTempHfpPhoneStatus,m_pBtParam->emTempHfpTalkingTransferSet);
	 	if(m_pBtParam->m_eHfpAudioSource == HFP_AUDIO_SOURCE_CAR)
	 	{
		 	if(m_pBtParam->emTempHfpTalkingTransferSet != HFP_AUDIO_SOURCE_CAR)
			{
			 	if(m_pBtParam->emTempHfpPhoneStatus == BT_PHONE_STATUS_CALL_IN)
				{
					m_pBtModule->setNativeTimer(200,1,TIMER_BC06_SET_TRANSFER_DIALING);
			 	}
		 	}
	 	}

		if(!m_pBtModule->getBackCarStatus())
		{
			int CurPageID = m_pBtModule->getCurPageId();
			if(CurPageID != PAGE_BLUETOOTH_MAIN)
			{
				if(!m_pBtParam->tempHideBtPage)
				{
					m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN); 
					m_pBtParam->m_bAutoJump = true;
				}
			} 
		}
	}
			

	if(em == BT_PHONE_STATUS_FREE ||
	em == BT_PHONE_STATUS_CALL_IN ||
	em == BT_PHONE_STATUS_CALL_OUT ||
	em == BT_PHONE_STATUS_TALKING)
	{ 
		m_pBtParam->emTempHfpPhoneStatus = em;
	}
	
	m_pBtApp->m_pBtMainPage->refreshAnswerHandup(em);

	
	m_pBtModule->btToModule_NotifyAUXScreen_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus); //AUXScreen BT Phone State
	m_pBtModule->btToModule_NotifyBackVideo_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->btToModule_NotifyAudiovideo_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->btToModule_NotifySystem_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtApp->btToApp_SendBtPhoneState((u8)m_pBtParam->m_ePhoneStatus);
    m_pBtModule->golf_sendToCarScreen_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->golf_sendToCarScreen_PhoneNumInTheSpecialState((u8)m_pBtParam->m_ePhoneStatus, (u8*)m_pBtParam->szPhoneNumCallInOrOut, strlen(m_pBtParam->szPhoneNumCallInOrOut));

	switch(m_pBtParam->m_ePhoneStatus)
	{
		case BT_PHONE_STATUS_FREE:
		{
			m_pBtModule->btToOtherModule_Auxscreen_Phone_status(0x04);
			m_pBtModule->deleteNativeTimer(TIMER_SET_CALLING_TIMES_1);
			m_pBtModule->HoldingTimes_1(2);
		}
		break;
		case BT_PHONE_STATUS_CALL_IN:
		case BT_PHONE_STATUS_CALL_OUT:
		case BT_PHONE_STATUS_TALKING:
		{
			m_pBtModule->btToOtherModule_Auxscreen_Phone_Number((u8*)m_pBtParam->szPhoneNumCallInOrOut, strlen(m_pBtParam->szPhoneNumCallInOrOut));
			m_pBtModule->btToOtherModule_Auxscreen_Phone_Name((u8*)m_pBtParam->cStrCallPeopleName, strlen(m_pBtParam->cStrCallPeopleName));

			m_pBtModule->btToOtherModule_Auxscreen_Phone_status((u8)m_pBtParam->m_ePhoneStatus);
			if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_TALKING){
				m_pBtModule->HoldingTimes_1(0);
				m_pBtModule->setNativeTimer(TIMER_CALLING_TIMES,0,TIMER_SET_CALLING_TIMES_1);
				
				if(m_pBtParam->m_eHfpAudioSource == HFP_AUDIO_SOURCE_MOBILE)
					m_pBtModule->btToOtherModule_Auxscreen_Phone_status(0x06);
			}
		}
		break;
	}
}

void CBtHal::getHfpPhoneStatus_Multi_Call(E_BT_PHONE_STATUS e)
{
	LOGD("[%s] e:%d",__FUNCTION__,e);
	switch(e)
	{
		case BT_PHONE_STATUS_FREE:
		{
		}
		break;
		case BT_PHONE_STATUS_CALL_IN:
		{
			m_pBtApp->setStringById(CONTROLID_BLUETOOTH_MAIN_CALL_IN_OR_OUT, STRINGID_BT_CALL_IN);
			//setToHalMobileStatus(1);
			m_pBtModule->btToModule_NotifyCenter_StartRing((u8)2);
			if(!m_pBtModule->getBackCarStatus())
			{
					int CurPageID = m_pBtModule->getCurPageId();
					if(CurPageID != PAGE_BLUETOOTH_MAIN && CurPageID != PAGE_BACK_NOVIDEO && CurPageID != PAGE_BACK_VIDEO)
					{
						m_pBtParam->m_ePhoneStatus = BT_PHONE_STATUS_CALL_IN;

						#ifdef MSM_ANDROID_ISR_NEW_FUNCTION
						if(m_pBtApp->DontDisplayWindowPromptAboutT123Video())
						{
							m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);  
							m_pBtParam->m_bAutoJump = true;
						}
						#else
						m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);  
						m_pBtParam->m_bAutoJump = true;
						#endif
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
			m_pBtApp->m_pBtMainPage->refreshAnswerHandup(BT_PHONE_STATUS_CALL_IN);
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
						m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN); 
					m_pBtParam->m_bAutoJump = true;
				} 
				else if(CurPageID == PAGE_BLUETOOTH_MAIN)
				{
					if(m_pBtParam->m_ePhoneStatus != BT_PHONE_STATUS_CALL_OUT)
						m_pBtParam->m_bAutoJump = false;
				}
			}

			m_pBtApp->setStringById(CONTROLID_BLUETOOTH_MAIN_CALL_IN_OR_OUT, STRINGID_BT_CALL_OUT);
			//setToHalMobileStatus(2);
			m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_CALL_OUT,true,true,m_pBtParam->m_strTemInName,m_pBtParam->m_strTemInNum);
			m_pBtApp->m_pBtMainPage->refreshAnswerHandup(BT_PHONE_STATUS_CALL_OUT);
		}
		break;
		case BT_PHONE_STATUS_TALKING: 
		{
			if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_CALLING_OR_WAITING || 
				m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_MEETING_TEL)
			{
				m_pBtModule->btToModule_NotifyCenter_StopRing();
				m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_FREE,false,false,(char *)"",(char *)"");

				LOGD("[%s] nCaller_State1:%d",__FUNCTION__,m_pBtParam->str_CallInfor[0].nCaller_State);
				LOGD("[%s] nCaller_State2:%d",__FUNCTION__,m_pBtParam->str_CallInfor[1].nCaller_State);

				if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_MEETING_TEL)
				{
					m_pBtApp->m_pBtMainPage->CallingAndWaitingFunction_DisplayingToUI(MULTI_CALL_MEETING_TEL);
				}
				else
				{
					if(m_pBtParam->str_CallInfor[1].nCaller_State == ACTIVE_CALL)
					m_pBtApp->m_pBtMainPage->CallingAndWaitingFunction_DisplayingToUI(MULTI_CALL_1_2);
					else if(m_pBtParam->str_CallInfor[0].nCaller_State == ACTIVE_CALL)
					m_pBtApp->m_pBtMainPage->CallingAndWaitingFunction_DisplayingToUI(MULTI_CALL_2_1);
				}
				
				m_pBtHal->getHfpMicStatus(true);
				m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(false,NULL);
				setToHalMobileStatus(3);
				m_pBtApp->m_pBtMainPage->AddCallsAndMergeButtonSwitchToUI(false);
			}
			
			m_pBtApp->m_pBtMainPage->refreshAnswerHandup(BT_PHONE_STATUS_TALKING);
		}
		break;
		default:
		break;
	}//switch(e)

	memset(m_pBtParam->m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
	memset(m_pBtParam->m_strTemWaitingName,0,PHONE_NUm_nNPUT_MAX_SIZE);

	m_pBtModule->btToModule_NotifyAUXScreen_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->btToModule_NotifyBackVideo_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->btToModule_NotifyAudiovideo_BT_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtApp->btToApp_SendBtPhoneState((u8)m_pBtParam->m_ePhoneStatus);
	

   	m_pBtModule->golf_sendToCarScreen_PhoneState((u8)m_pBtParam->m_ePhoneStatus);
	m_pBtModule->golf_sendToCarScreen_PhoneNumInTheSpecialState((u8)m_pBtParam->m_ePhoneStatus, (u8*)m_pBtParam->szPhoneNumCallInOrOut, strlen(m_pBtParam->szPhoneNumCallInOrOut));

	switch(m_pBtParam->m_ePhoneStatus)
	{
		case BT_PHONE_STATUS_FREE:
		{
		}
		break;
		case BT_PHONE_STATUS_CALL_IN:
		case BT_PHONE_STATUS_CALL_OUT:
		case BT_PHONE_STATUS_TALKING:
		{
			m_pBtModule->btToOtherModule_Auxscreen_Phone_Number((u8*)m_pBtParam->szPhoneNumCallInOrOut, strlen(m_pBtParam->szPhoneNumCallInOrOut));
			m_pBtModule->btToOtherModule_Auxscreen_Phone_Name((u8*)m_pBtParam->cStrCallPeopleName, strlen(m_pBtParam->cStrCallPeopleName));
			m_pBtModule->btToOtherModule_Auxscreen_Phone_status((u8)m_pBtParam->m_ePhoneStatus);
		}
		break;
	}

}

void CBtHal::getPhoneNumCallIn(ST_PHONE_NUM *phoneNum)
{
	memset(&(m_pBtParam->m_stPhoneNumInput),0,sizeof(ST_PHONE_NUM));
	m_pBtParam->m_stPhoneNumInput.dwLen=phoneNum->dwLen;
	memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,phoneNum->szcPhoneNum,phoneNum->dwLen);
}

void CBtHal::clearPhoneNumInput()
{
	memset(&(m_pBtParam->m_stPhoneNumInput), 0, sizeof(ST_PHONE_NUM));
	memset(&(m_pBtParam->m_stPhoneNumCallIn), 0, sizeof(ST_PHONE_NUM));

	//m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(false, NULL);
	m_pBtApp->m_pBtMainPage->refreshPhoneNumInput((char*)"", 0);
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
}

void CBtHal::getHfpPhoneNumCallInOrOut(E_BT_PHONE_STATUS e,char *pNo, int len)
{
	m_pBtParam->emPhoneStatusBallon = e;
	int rlen = len;
	if(rlen < 0)
		return;
	
	memset(m_pBtParam->m_strFirstCallNum, 0, PHONE_NUm_nNPUT_MAX_SIZE);
	memcpy(m_pBtParam->m_strFirstCallNum, pNo, rlen);
	LOGD("[%s] m_strFirstCallNum=%s",__FUNCTION__,m_pBtParam->m_strFirstCallNum);
	
	memset(m_pBtParam->szPhoneNumCallInOrOut, 0, PHONE_NUm_nNPUT_MAX_SIZE);
	memcpy(m_pBtParam->szPhoneNumCallInOrOut, pNo, rlen);
	ST_PHONE_NUM phoneNum;	
	memset(&phoneNum,0,sizeof(ST_PHONE_NUM));
	memcpy(phoneNum.szcPhoneNum,m_pBtParam->szPhoneNumCallInOrOut,strlen(m_pBtParam->szPhoneNumCallInOrOut));
	getPhoneCallinOrCalloutPeopleName_Temp(m_pBtParam->szPhoneNumCallInOrOut);

	phoneNum.dwLen=strlen(m_pBtParam->szPhoneNumCallInOrOut);
	memcpy(phoneNum.szcName,m_pBtParam->cStrCallPeopleName,strlen(m_pBtParam->cStrCallPeopleName));
	m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(true,&phoneNum);
	m_pBtApp->m_pBtMainPage->PopUp_V_Scereen_showDailingInformations(true,m_pBtParam->emPhoneStatusBallon,&phoneNum);
	
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
		//LOGD("zhq it->szUserNo=%s",it->szUserNo);
		if((strncmp(it->szUserNo,pnum,n) == 0) && (strlen(it->szUserNo) == n))
		{
			memcpy(m_pBtParam->cStrCallPeopleName,it->szUserName,strlen(it->szUserName));
			m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(m_pBtParam->cStrCallPeopleName), strlen(m_pBtParam->cStrCallPeopleName));
			m_pBtApp->setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);
			LOGD("[%s]m_pBtParam->cStrCallPeopleName=%s",__FUNCTION__,m_pBtParam->cStrCallPeopleName);
			memset(m_pBtParam->m_stPhoneNumInput.szcName,0,PHONE_NUM_NAME_MAX_SIZE);
			m_pBtParam->m_stPhoneNumInput.dwNameLen = 0;
			int nNumLen = strlen(it->szUserName);
			memcpy(m_pBtParam->m_stPhoneNumInput.szcName,it->szUserName,nNumLen);
			m_pBtParam->m_stPhoneNumInput.dwNameLen = nNumLen;
			return;
		}
	}
}

void CBtHal::getPhoneCallinOrCalloutPeopleName_Temp(char *input_Num)
{
	int n = strlen(input_Num);
	int s = m_pBtParam->m_listPhoneBook.size();
	memset(m_pBtParam->cStrCallPeopleName,0,sizeof(m_pBtParam->cStrCallPeopleName));
	if(s < 1 || n < 1)
		return;
	LOGD("[%s]input_Num=%s  n=%d",__FUNCTION__,input_Num,n);

	char tem_Name[PHONE_NUM_NAME_MAX_SIZE] = {0};
	if(searchNameAtPhoneBook(input_Num,tem_Name))
	{
	}
	else
	{
		if(strlen(tem_Name) == 0)
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
				LOGD("[%s]tempszUserNo=%s  len=%d",__FUNCTION__,tempszUserNo,strlen(tempszUserNo));
				searchNameAtPhoneBook(tempszUserNo,tem_Name);
				LOGD("[%s]tem_Name=%s",__FUNCTION__,tem_Name);
			}	
		}
	}

	if(strlen(tem_Name) == 0)
		return;
	
	memcpy(m_pBtParam->cStrCallPeopleName,tem_Name,strlen(tem_Name));
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(m_pBtParam->cStrCallPeopleName), strlen(m_pBtParam->cStrCallPeopleName));
	m_pBtApp->setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);
	LOGD("[%s]m_pBtParam->cStrCallPeopleName=%s",__FUNCTION__,m_pBtParam->cStrCallPeopleName);

	memset(m_pBtParam->m_stPhoneNumInput.szcName,0,PHONE_NUM_NAME_MAX_SIZE);
	m_pBtParam->m_stPhoneNumInput.dwNameLen = 0;
	int nNamLen = strlen(tem_Name);
	memcpy(m_pBtParam->m_stPhoneNumInput.szcName,tem_Name,nNamLen);
	m_pBtParam->m_stPhoneNumInput.dwNameLen = nNamLen;
}

void CBtHal::getHfpAudioSource(E_HFP_AUDIO_SOURCE e)
{
	m_pBtParam->m_eHfpAudioSource = e;
	g_pClsBtJniSdk->sendToAppReceiveSound(e);
}

void CBtHal::getHfpSpkAndMicVolume(int nSpkVolume, int nMicVolume)
{
	LOGD("[%s] nSpkVolume,nMicVolume:(%d %d)",__FUNCTION__,nSpkVolume,nMicVolume);
	m_pBtParam->m_nSpkVolume = nSpkVolume;
	m_pBtParam->m_nMicVolume = nMicVolume;

	m_pBtApp->m_pBtDevicePages->setSerialMicrophoneVolumeToUI(nMicVolume);
}

/////////////////////////////////////////////////////////////////////////////////////////////
void CBtHal::bohong_test(int nCommand1,int nCommand2,int tag)
{
    char strCommand[256]={0};
	if(tag == 1 || tag == 2)
	{
	}
	
    if(tag == 1)
	sprintf(strCommand,"(Tx)AT*AVOL=%d,0,%d",5,nCommand1);
	else if(tag == 2)
	sprintf(strCommand,"(Rx)AT*AVOL=%d,0,%d",2,nCommand1);
    else if(tag == 3)
	sprintf(strCommand,"AT*AADC=1,%d",nCommand1);
	else if(tag == 4)
	sprintf(strCommand,"AT*AADC=2,%d",nCommand1);
	else if(tag == 5)
	sprintf(strCommand,"AVOL=%d AADC=%d",nCommand1,nCommand2);
    else if(tag == 6)
	sprintf(strCommand,"(A2DP)AT*AVOL=%d,0,%d",10,nCommand1);
	else if(tag == 7)
	sprintf(strCommand,"AVOL=%d AADC=%d",nCommand1,nCommand2);
	else if(tag == 8)
	sprintf(strCommand,"AVOL=%d AADC=%d",nCommand1,nCommand2);
	else if(tag == 9){
	g_pClsBtBC6Adapter->setToBtChipCtrlGainData();
	sprintf(strCommand,"Set To MIC AADC ...");
	}

	m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(strCommand, strlen(strCommand));
}

void CBtHal::bohong_test_AVOL_Tx(int cotrl)
{
     if(cotrl == CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_XIN)
     {
     }
     if(cotrl == CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_JING)
     {
     }
     //bohong_test(m_pBtParam->m_nMicVolume,0,1); 
}

bool CBtHal::bohong_test_HHHHH(int ctrlId,char ctrlType)
{
	/*
    if(ctrlType == UIACTION_MOUSETIMER && ctrlId == CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_0)
    {
         bohong_test_SACC_Switch();
         
         return true;
    }
	else if(ctrlType == UIACTION_MOUSEUP && (ctrlId == CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_UP || 
            ctrlId == CONTROLID_BLUETOOTH_AUDIOVOX_SET_MICROPHONE_VOLUME_DOWN))
	{
        if(nSACC == 0)
        bohong_test_AVOL_Tx(ctrlId);
        else if(nSACC == 1)
        bohong_test_AVOL_Rx(ctrlId);
        else if(nSACC == 2)
        bohong_test_AVOL_MutiPlay(ctrlId);

		return true;
	}
    else if(ctrlType == UIACTION_MOUSEUP && (ctrlId == CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_XIN || ctrlId == CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_JING))
    {
        if(nSACC == 0)
        bohong_testAADC(ctrlId);
        else if(nSACC == 1 || nSACC == 2)
        bohong_testAADC2(ctrlId);

        return true;
    }
*/

	if(ctrlType == 0x10 && (ctrlId == CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_XIN || ctrlId == CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_JING))
    {
		 bohong_test_AVOL_Tx(ctrlId);
        return true;
    }


     
    return false;

}

/////////////////////////////////////////////////////////////////////////////////////////////


void CBtHal::getHfpMicStatus(bool state)
{
	m_pBtParam->m_bIsMicOpen = state;
	LOGD("[%s] m_pBtParam->m_bIsMicOpen:%d",__FUNCTION__,m_pBtParam->m_bIsMicOpen);
	m_pBtApp->m_pBtMainPage->DisplayingMuteButtonState();
	g_pClsBtJniSdk->sendToAppMicStatus(state);

	if(!state)
		m_pBtModule->btToOtherModule_Auxscreen_Phone_status(0x05);
	else
		m_pBtModule->btToOtherModule_Auxscreen_Phone_status(0x03);
}

void CBtHal::getBtDeviceSearchStatus(E_BT_DEVICE_SEARCH_STATUS e)
{
       LOGD("[%s] E_BT_DEVICE_SEARCH_STATUS:%d",__FUNCTION__,e);
	m_pBtParam->m_eBtDeviceSearchStatus = e;

	m_pBtApp->m_pBtDevicePages->refreshBtDeviceSearchStatus(e);
}


void CBtHal::getBtDeviceHasSearch(char *pAddr, int addrLen, char *pName, int nameLen)
{

	if(WhetherThereIsCurrentlyDuplicateDeviceSearchList(pAddr,addrLen))
		return;
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
	//memcpy(t.deviceName, pName, nameLen);
	t.addrLen =  addrLen;
	//t.nameLen = nameLen;

	m_pBtParam->m_listBtDevicesHaveSearched.push_back(t);
	m_pBtParam->m_btDevicesHaveNum = m_pBtParam->m_listBtDevicesHaveSearched.size();
	char str[256]={0};   
	sprintf(str,"(%d)",m_pBtParam->m_btDevicesHaveNum);
	
	if(m_pBtParam->m_btDevicesHaveNum > 0)
	{
		m_pBtApp->setUtf8String((u32)(CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_PERCENTAGE), (u8*)str, strlen(str));
	}
		

	m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHaveSearched(0);
	m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHaveSearched_New(m_pBtParam->m_nBtDevicesHaveSearchedListBrowseFrom);

}

//1.16 碌莽禄掳卤鸥/脥拧禄掳艗脟脗艗 脫艩沤冒
void CBtHal::getPhoneBookSyncStatus(bool b)
{
	m_pBtParam->m_bRemodeMobilePhoneBookSyncOk = b;
}

void CBtHal::getPhoneBookOneItem(char *pUserName, int userNameLen, char *pUserNo, int userNoLen)
{
    LOGD("[%s] [%s (%d)]   [%s (%d)] ",__FUNCTION__,pUserName,userNameLen,pUserNo,userNoLen);
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
			//LOGD("[%s] strParam1_out1:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);
			
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
			//LOGD("[%s] strParam1_out2:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);

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
			//LOGD("[%s] strParam1_out3:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);

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
			//LOGD("[%s] strParam1_out4:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);
				
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
			//LOGD("[%s] strParam1_out5:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);
		
			deleteSpecialCharacters(strParam1_out,' ');
			//LOGD("[%s] strParam1_out:%s",__FUNCTION__,strParam1_out);
    }
    else//Other Languages
    {

		 	if(nLen1 != 0){
				memcpy(strParam1_out,m_pBtParam->extended_Infor.PBName_Prefix,sizeof(m_pBtParam->extended_Infor.PBName_Prefix));
				nStrParam1_out_len = nLen1;
			}
			//LOGD("[%s] strParam1_out1:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);
			
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
			//LOGD("[%s] strParam1_out4:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);
		
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
			//LOGD("[%s] strParam1_out3:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);
		
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
			//LOGD("[%s] strParam1_out2:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);
			
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
			//LOGD("[%s] strParam1_out5:%s len:%d",__FUNCTION__,strParam1_out,nStrParam1_out_len);
   		
			//LOGD("[%s] strParam1_out:%s",__FUNCTION__,strParam1_out);
    }
}


void CBtHal::AnalyzeContactsExtendedName(char *strParam1_In)
{
	int nContactNameLen = strlen(strParam1_In);
	//LOGD("[%s] strParam1_In:%s nContactNameLen:%d",__FUNCTION__,strParam1_In,nContactNameLen);

	InitContactsExtendedNameParamValue();
	if((nContactNameLen == 4 && strcmp(strParam1_In,";;;;") == 0) || (nContactNameLen == 1 && strcmp(strParam1_In,";") == 0))
    {
	    return;
    }

	m_pBtParam->extended_Infor.PBName_CompleteTotal_Len  = nContactNameLen;

	int nTo_First = g_pClsBtBC6Adapter->Inside_FindIndexFromStr((u8 *)strParam1_In,nContactNameLen, ';', 0);
	if(nTo_First < 0)
	{
		memcpy(m_pBtParam->extended_Infor.PBName_First,strParam1_In,nContactNameLen);
		m_pBtParam->extended_Infor.PBName_First_Len = nContactNameLen;
		
		return;
	}
	else if(nTo_First == 0)
	{
	}
	else 
	{
		memcpy(m_pBtParam->extended_Infor.PBName_First,strParam1_In,nTo_First);
		m_pBtParam->extended_Infor.PBName_First_Len = nTo_First;
	}

	if(nTo_First + 1 == nContactNameLen)
	{
		return;
	}
	
	int nTo_Last = g_pClsBtBC6Adapter->Inside_FindIndexFromStr((u8 *)strParam1_In,nContactNameLen, ';', nTo_First+1);
	if(nTo_Last < 0)
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Last,strParam1_In+nTo_First+1,nContactNameLen-nTo_First-1);
		m_pBtParam->extended_Infor.PBName_Last_Len = nContactNameLen-nTo_First-1;

		return;
	}
	else if(nTo_Last == nTo_First+1)
	{
	}
	else
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Last,strParam1_In+nTo_First+1,nTo_Last -nTo_First - 1);
		m_pBtParam->extended_Infor.PBName_Last_Len = nTo_Last-nTo_First-1;
	}

	int nTo_Mid = g_pClsBtBC6Adapter->Inside_FindIndexFromStr((u8 *)strParam1_In,nContactNameLen, ';',nTo_Last + 1);
	if(nTo_Mid < 0)
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Mid,strParam1_In + nTo_Last + 1,nContactNameLen - nTo_Last - 1);
		m_pBtParam->extended_Infor.PBName_Mid_Len = nContactNameLen - nTo_Last - 1;

		return;
	}
	else if(nTo_Mid == 0)
	{
	}
	else
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Mid,strParam1_In + nTo_Last + 1,nTo_Mid - nTo_Last - 1);
		m_pBtParam->extended_Infor.PBName_Mid_Len = nTo_Mid - nTo_Last - 1;
	}

	int nTo_Pre = g_pClsBtBC6Adapter->Inside_FindIndexFromStr((u8 *)strParam1_In,nContactNameLen, ';',nTo_Mid + 1);
	if(nTo_Pre < 0)
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Prefix,strParam1_In + nTo_Mid + 1,nContactNameLen - nTo_Mid - 1);
		m_pBtParam->extended_Infor.PBName_Prefix_Len= nContactNameLen - nTo_Mid - 1;
		return;
	}
	else if(nTo_Pre == 0)
	{
	}
	else
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Prefix,strParam1_In + nTo_Mid + 1,nTo_Pre - nTo_Mid - 1);
		m_pBtParam->extended_Infor.PBName_Prefix_Len= nTo_Pre - nTo_Mid - 1;
	}

	if(nContactNameLen == nTo_Pre + 1)
	{
	}
	else
	{
		memcpy(m_pBtParam->extended_Infor.PBName_Suffix,strParam1_In+nTo_Pre + 1,nContactNameLen - nTo_Pre - 1);
		m_pBtParam->extended_Infor.PBName_Suffix_Len= nContactNameLen - nTo_Pre - 1;
	}
}



void CBtHal::getHistoryCallOneItem(char type,char *pUserName, int userNameLen, char *pUserNo, int userNoLen,char *pUserTime,int userTimeLen)
{
	if(type == '0')
		return;
	ST_CALL_RECORD_ONE_USER_INFO t;
	memset(&t, 0, sizeof(ST_CALL_RECORD_ONE_USER_INFO));
	t.CBType=type;
	memcpy(t.szUserName, pUserName, userNameLen);
	memcpy(t.szUserNo, pUserNo, userNoLen);
	memcpy(t.CBTime, pUserTime, userTimeLen);
	
	LOGD("[%s]	type:%c, UserName:%s , UserNo: %s,	UserTime:%s",__FUNCTION__, t.CBType,t.szUserName,t.szUserNo,t.CBTime);
	
	//m_pBtParam->m_listHistoryCall.push_back(t);
	m_pBtParam->m_tempListHistoryCall.push_back(t);

	//if((m_pBtParam->m_tempListHistoryCall.size() == 1) && (m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_FREE)){
	//	memset(&m_pBtParam->st_UserInforsOnetouchDial,0,sizeof(ST_CALL_RECORD_ONE_USER_INFO));
	//	m_pBtParam->st_UserInforsOnetouchDial.CBType=type;
	//	memcpy(m_pBtParam->st_UserInforsOnetouchDial.szUserName, pUserName, userNameLen);
	//	memcpy(m_pBtParam->st_UserInforsOnetouchDial.szUserNo, pUserNo, userNoLen);
	//	memcpy(m_pBtParam->st_UserInforsOnetouchDial.CBTime, pUserTime, userTimeLen);
	//}
}

void CBtHal::getLoadPhoneBookFinishStatus(void)
{
     LOGD("[%s]  loading  Finished", __FUNCTION__);

    m_pBtHal->m_pBtApp->m_pBtPhoneBookPages->m_bIsLoadingPhoneBook=false;
	
}

//1.23 脝盲脣没脫艩沤冒
//脌沤碌莽脳脭露炉艙脫脤媒/ 脛拢驴茅脡脧碌莽脳脭露炉 脰脴脕卢脡猫脰脙

void CBtHal::getLocalBtDeviceAutoConnectState(char *p, int len)
{
	if (!strncmp(p, "MF10", 4))//脌沤碌莽脳脭露炉艙脫脤媒隆垄脛拢驴茅脡脧碌莽脳脭露炉脰脴脕卢脡猫脰脙
	{
		m_pBtParam->bIsAutoConnect = true;	
	}
	else if(!strncmp(p, "MF00", 4))
	{
		m_pBtParam->bIsAutoConnect = false;
	}
	m_pBtApp->m_pBtDevicePages->clickDeviceDisplayAutoConnect(m_pBtParam->bIsAutoConnect);
	LOGD("[%s]  m_pBtParam->bIsAutoConnect:%d", __FUNCTION__,m_pBtParam->bIsAutoConnect);
}

void CBtHal::getLocalBtDeviceVersion(char *p, int len)
{
	g_pClsBtBC6Adapter->setToBtChipQueryMicGainValue();
	
	memset(m_pBtParam->szLocalBtDeviceVersion, 0, sizeof(m_pBtParam->szLocalBtDeviceVersion));
	memcpy(m_pBtParam->szLocalBtDeviceVersion, p, len);

	m_pBtApp->m_pBtMainPage->refreshLocalBtDeviceVersion(m_pBtParam->szLocalBtDeviceVersion,len);
}

void CBtHal::getLocalBtDeviceName(char *p, int len)
{
	memset(m_pBtParam->szLocalBtDevice_Name,0,sizeof(m_pBtParam->szLocalBtDevice_Name));
	memcpy(m_pBtParam->szLocalBtDevice_Name, p, len);

	m_pBtApp->m_pBtDevicePages->clickDisplaySetDeviceNameToUi((u8*)p,(u32)len);
	m_pBtApp->SendBtNameToSdk((u8*)p,(u32)len);

	m_pBtModule->golf_sendToCarScreen_mobileOperatorName((u8*)p,(u32)len);
}

void CBtHal::getLocalBtDevicePinCode(char *p, int len)
{
  	memset(m_pBtParam->szLocalBtDevice_PinCode, 0, sizeof(m_pBtParam->szLocalBtDevice_PinCode));
	memcpy(m_pBtParam->szLocalBtDevice_PinCode, p, len);

	LOGD("[%s] p:%s",__FUNCTION__,p);
	m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_PIN_CODE_TEXT,(u8*)p, len);
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
	property_set(FLY_BT_DEVICE_ADDR, property);

	m_pBtApp->btToApp_SendBtMac(p,len);
}

void CBtHal::getLocalBtDeviceAddr(char *p, int len)
{
	memset(m_pBtParam->szLocalBtDeviceAddr, 0, sizeof(m_pBtParam->szLocalBtDeviceAddr));
	memcpy(m_pBtParam->szLocalBtDeviceAddr, p, len);
	FormatBtMacAddress(p,len);

	m_pBtApp->SendBtMacToSdk((u8 *)p,len);
}

void CBtHal::getBtDeviceHasPaired(int index, char *pAddr, int addrLen, char *pName, int nameLen)
{
	if(addrLen <= 0)
		return;
	if(addrLen > FLY_BT_PAIRING_ADDRS_MAX_LEN)
		addrLen = FLY_BT_PAIRING_ADDRS_MAX_LEN;
	if(nameLen > FLY_BT_PAIRING_NAME_MAX_LEN)
		nameLen = FLY_BT_PAIRING_NAME_MAX_LEN;
	
	if(index > 48)
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
					LOGD("[%s] it->deviceAddr=%s,t.deviceAddr=%s ",__FUNCTION__,it->deviceAddr,t.deviceAddr);
					return;
				}
				
				j++;
				if (j >= BT_DEVICE_SEARCHED_PAGE_ITEM_NUM)
					break;
			}
		}
		
		m_pBtParam->m_listBtDevicesHavePaired.push_back(t);

		m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired(0);
		m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired_New(0);
		
		LOGD("[%s] mx t.deviceName:%s",__FUNCTION__,t.deviceName);
	}
}

void CBtHal::getBtPairStatus(bool b)
{
}

void CBtHal::getA2DPStatus(bool b)
{
	LOGD("[%s] b:%d",__FUNCTION__,b);
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
			m_pBtModule->setNativeTimer(3000,1,TIMER_BC06_A2DPTIME);
			return;	
		}
		if(nCurSoundMode == 0x0d && (CurPageID != PAGE_BLUETOOTH_A2DP || CurPageID != PAGE_BLUETOOTH_NO_A2DP))
		{
			m_pBtParam->bA2DP_To_DevicePageBackButton = false;
			m_pBtModule->setNativeTimer(3000,1,TIMER_BC06_A2DPTIME);
		}

		g_pClsBtBC6Adapter->setToBtChipIsSupportMusicBrowsing();
	}
	else//if(b)
	{
		if(CurPageID == PAGE_BLUETOOTH_A2DP){
			m_pBtModule->setPage(PAGE_BLUETOOTH_NO_A2DP);
		}
	}
}


void CBtHal::getLocalBtDeviceInitFinished(void)
{
	m_pBtParam->m_bIsLocalBtDeviceInitOk = true;
	g_pClsBtBC6Adapter->setToBtChipQueryLocalBtMacAddr();
	g_pClsBtBC6Adapter->setToBtChipSetAutoConnect(m_pBtParam->bIsAutoConnect);
	g_pClsBtBC6Adapter->setToBtChipQueryHavePairDevices();	
	
	g_pClsBtBC6Adapter->setToBtChipModifyBtChipPairCode(m_pBtParam->szLocalBtDevice_PinCode,strlen(m_pBtParam->szLocalBtDevice_PinCode));
	g_pClsBtBC6Adapter->setToBtChipModifyBtChipName(m_pBtParam->szLocalBtDevice_Name, strlen(m_pBtParam->szLocalBtDevice_Name));
	g_pClsBtBC6Adapter->setToBtChipQueryBtChipName();
	g_pClsBtBC6Adapter->setToBtChipQueryBtChipPairCode();
	g_pClsBtBC6Adapter->setToBtChipQueryBtChipVersion();
}

void CBtHal::getMobileSignalAndBattery(char *nSignal,char *nBattery)
{
	char cTemSignal[3] = {0};
	char cTemBattery[3] = {0};
	memcpy(cTemSignal,nSignal,2);
	memcpy(cTemBattery,nBattery,2);
	
	m_pBtParam->m_nMobileSignal = atoi(cTemSignal);
	m_pBtParam->m_nMobileBattery = atoi(cTemBattery);

	m_pBtModule->golf_sendToCarScreen_signalState(m_pBtParam->m_nMobileSignal);
	m_pBtModule->golf_sendToCarScreen_batteryStrength(m_pBtParam->m_nMobileBattery);
	LOGD("[%s] %d %d",__FUNCTION__,m_pBtParam->m_nMobileSignal,m_pBtParam->m_nMobileBattery);
}

void CBtHal::getCurConnectedBtDeviceName(char *p, int len)
{
	memset(m_pBtParam->szRemodeBtDeviceHasConnectedName, 0, sizeof(m_pBtParam->szRemodeBtDeviceHasConnectedName));
	if(len != 0){
		memcpy(m_pBtParam->szRemodeBtDeviceHasConnectedName, p, len);
	}
	
	m_pBtModule->sendToFlyJniSdkRemoteDeviceName(p, len);
	m_pBtApp->m_pBtMainPage->refreshRemodeBtDeviceName((u8 *)p,(u32)len);

	//GOLF
	m_pBtModule->btToModule_golf_phoneName((u8*)p, len);
	m_pBtApp->SendConnectedBtNameToSdk((u8*)p,(u32)len);
	g_pClsBtJniSdk->sendToAppConnectBtName(p,len);
	m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_Connect_Bt_Name((u8*)p,(u32)len);
}

void CBtHal::getBtDeviceMicGain(char *param)
{
	m_pBtParam->n_MicGain_Volue = atoi(param); 
	LOGD("[%s] m_pBtParam->n_MicGain_Volue:%x",__FUNCTION__,m_pBtParam->n_MicGain_Volue);
	m_pBtApp->m_pBtDevicePages->setSerialMicrophoneVolumeGainToUI(m_pBtParam->n_MicGain_Volue);
}

void CBtHal::BtDeviceNameOfThedeviceconnectedToTheinsidepagesAndtheRealPairIsNotTheSame()
{
	if(strlen(m_pBtParam->szRemodeBtDeviceHasConnectedName) > 0)
	{
		if(m_pBtParam->m_listBtDevicesHavePaired.size() > 0)
		{
			list<BluetoothDevice>::iterator itCurConnected = m_pBtParam->m_listBtDevicesHavePaired.begin();
			if(strcmp(m_pBtParam->szRemodeBtDeviceHasConnectedName,(char *)itCurConnected->deviceName) != 0)
			{
				m_pBtParam->m_listBtDevicesHavePaired.clear();
				m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired(0);
				m_pBtApp->m_pBtDevicePages->refreshBtDevicesListHavePaired_New(0);
				g_pClsBtBC6Adapter->setToBtChipQueryHavePairDevices();
			}
		}
	}
}

void CBtHal::getCurConnectedBtDeviceAddr(char *p, int len)
{
	memset(m_pBtParam->szRemodeBtDeviceHasConnectedAddr, 0, sizeof(m_pBtParam->szRemodeBtDeviceHasConnectedAddr));
	memcpy(m_pBtParam->szRemodeBtDeviceHasConnectedAddr, p, len);

	m_pBtApp->SendConnectedBtMacToSdk((u8*)p,(u32)len);
}

//////////////////////////////////////////////////////////////////////////
void CBtHal::setToHalInit(void)
{
	u8 szMsg[2] = {0x01, 0x01};

	makeAndSendMessageToHal(HAL_ID_BT, szMsg, 2);
}

void CBtHal::setToHalBtPower(u8 p)
{
	if(p == 0)
	{
		g_pClsBtBC6Adapter->setToBtChipCloseBt();
	}
	
	u8 szMsg[2] = {0x10, 0x00};
	szMsg[1]=p;

	LOGD("[%s] p:%d",__FUNCTION__,p);
	makeAndSendMessageToHal(HAL_ID_BT, szMsg, sizeof(szMsg));
}

void CBtHal::setToHalBtMsg(char *p, int len)
{
	u8 szMsg[FLY_BT_DEVICE_END_CMD_MAX_LEN] = {0};

	szMsg[0] = 0xE0;

	if(len > (FLY_BT_DEVICE_END_CMD_MAX_LEN - 1))
		len = FLY_BT_DEVICE_END_CMD_MAX_LEN - 1;

	if(!judgmentPhoneCallCmd(p,len)) 
	{
		memset(m_pBtParam->m_SendMessagesStr,0,FLY_BT_DEVICE_END_CMD_MAX_LEN);
		memcpy(m_pBtParam->m_SendMessagesStr,p,len);
	
		memcpy(szMsg + 1, p, len);
		makeAndSendMessageToHal(HAL_ID_BT, szMsg, len + 1);
		return;
	}
	LOGD("[%s] m_pBtParam->m_bCanSendData=%d",__FUNCTION__,m_pBtParam->m_bCanSendData);
	if(!m_pBtParam->m_bCanSendData)
	{
		memcpy(m_pBtParam->m_SendMessageBuf.cmdGroup[m_pBtParam->m_SendMessageBuf.count].cmd,p,len);
		m_pBtParam->m_SendMessageBuf.cmdGroup[m_pBtParam->m_SendMessageBuf.count].len=len;
		m_pBtParam->m_SendMessageBuf.count += 1;
	}
	else
	{
		memset(m_pBtParam->m_SendMessagesStr,0,FLY_BT_DEVICE_END_CMD_MAX_LEN);
		memcpy(m_pBtParam->m_SendMessagesStr,p,len);
		memcpy(szMsg + 1, p, len);
		makeAndSendMessageToHal(HAL_ID_BT, szMsg, len + 1);
		
		m_pBtParam->m_bCanSendData = false;
		m_pBtModule->setNativeTimer(2000,1,TIMER_BC8_NOTRECEIVE);
	}
}


void CBtHal::getA2DPInfo(char *singName,int singNameLen,char* author,int authorLen,char* album,int singAlbumLen)
{
	//LOGD("[%s] singName:%s,author:%s album:%s",__FUNCTION__,singName,author,album);
	m_pBtModule->sendToFlyJniSdkBtMusicSong(singName,singNameLen);
	m_pBtModule->sendToFlyJniSdkBtMusicSonger(author,authorLen);
	g_pClsBtJniSdk->sendToAppBtSongInfo(singName,author,album,singNameLen,authorLen,singAlbumLen);

	if((strcmp(singName,m_pBtParam->musicName) != NULL) || (strcmp(author,m_pBtParam->musicAuthor) != NULL) || (strcmp(album,m_pBtParam->musicAlbum) != NULL))
	{	
		m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayTitle((u8 *)singName,singNameLen);
		m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayArtist((u8 *)author,authorLen);
		m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayAlbum((u8 *)album,singAlbumLen);
	}

	memset(m_pBtParam->musicAuthor,0,sizeof(m_pBtParam->musicAuthor));
	if(authorLen != 0)
		memcpy(m_pBtParam->musicAuthor,author,authorLen);

	memset(m_pBtParam->musicName,0,sizeof(m_pBtParam->musicName));
	if(singNameLen != 0)
		memcpy(m_pBtParam->musicName,singName,singNameLen);

	memset(m_pBtParam->musicAlbum,0,sizeof(m_pBtParam->musicAlbum));
	if(singAlbumLen != 0)
		memcpy(m_pBtParam->musicAlbum,album,singAlbumLen);
	
	m_pBtApp->m_pA2DPpages->displyA2DPInfo();
}

void CBtHal::getSongTrackInfor(short TotalNumber,short curSongNumber)
{
	u8 buff[4];
	memset(buff,0,sizeof(buff));
	
	buff[0] = (u8)(curSongNumber & 0xFF);
	buff[1] = (u8)((curSongNumber >> 8) & 0xFF);
	buff[2] = (u8)(TotalNumber & 0xFF);
	buff[3] = (u8)((TotalNumber >> 8) & 0xFF);
	
	m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_TrackAndTotalTrack(buff,4);
}

void CBtHal::getSongTotalTime(int p)
{
	u8 buff[4];
	memset(buff,0,sizeof(buff));
	
	int nT = p/1000;
	buff[0] = (u8)(nT & 0xFF);
	buff[1] = (u8)((nT >> 8) & 0xFF);
	buff[2] = (u8)((nT >> 16) & 0xFF);
	buff[3] = (u8)((nT >> 24) & 0xFF);
	
	m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayTotalTime(buff, 4);
}

void CBtHal::getSongPlayingTime(long int p)
{
	u8 buff[4];
	memset(buff,0,sizeof(buff));
	int nT = p/1000;
	memcpy(buff,&nT,4);
	m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_TrackPlayTime(buff, 4);
}


void CBtHal::getLocalBtDevice_SearchedDeviceCounts(char *p, int len)
{
		char szAddr[64] = {0};
		char szName[64] = {0};
				
		memcpy(szAddr, p + 2, 12);
		memcpy(szName, p + 2 + 12, len - 2 - 12 - 2);

		LOGD("[%s] SF  Search for Bluetooth devices. add = [%s], name = [%s]",__FUNCTION__, szAddr, szName);
		
		m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCHED_DEVICE_COUNT);
		m_pBtHal->getBtDeviceHasSearch(szAddr, 12, szName, len - 2 - 12 - 2);
}

void CBtHal::getLocalBtDevice_SearchFinish()
{
		LOGD("[%s] SH  Search finish",__FUNCTION__);

		if(m_pBtParam->bHandleStopSearchState){
			m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCHING);
			g_pClsBtBC6Adapter->setToBtChipStartSearchBtDevice(); 
		}
		else
		{
			if(m_pBtParam->bIsSelectPairing){
				m_pBtParam->bIsSpeedConnectState = false;
				m_pBtModule->deleteNativeTimer(TIME_ID_ONE_TOUCH_SPEED_CONNECT_SWITCH);

				g_pClsBtBC6Adapter->setToBtChipConnectHFP((char*)m_pBtParam->uSetConnectbtAddr,strlen((char*)m_pBtParam->uSetConnectbtAddr));
			}

			m_pBtParam->bIsSelectPairing = false;
			m_pBtHal->getBtDeviceSearchStatus(BT_DEVICE_SEARCH_STATUS_SEARCH_FINISH);
		}

		m_pBtParam->bHandleStopSearchState = false;
}

void CBtHal::setToHalMobileStatus( int callStatus )
{
	LOGD("[%s] callStatus:%d",__FUNCTION__,callStatus);
	unsigned char buf[]={0xA0,0x00};
	buf[1]=callStatus;
	makeAndSendMessageToHal(HAL_ID_BT,buf,2);
}

void CBtHal::clearListHistoryCall()
{
	(m_pBtParam->m_listHistoryCall).clear();
}

int CBtHal::SetTimer(int nElaspe_ms, int nMode, int timerId){
	u8 buf[9];
	
	buf[0] = 0x20;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    buf[5] = (nElaspe_ms >> 24) & 0xFF;
    buf[6] = (nElaspe_ms >> 16) & 0xFF;
    buf[7] = (nElaspe_ms >> 8) & 0xFF;
    buf[8] = nElaspe_ms & 0xFF;
    
    m_pBtModule->makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_TIMER,buf,9);
    
    return 0;
}

void CBtHal::setBC06TestAutoConnect(void)
{
	if(0 == m_pBtParam->m_listBtDevicesHavePaired.size())
		return;
	if(HFP_CONNECT_STATUS_CONNECTED == m_pBtModule->getBtConnectStatus())
		return;
	if(m_pBtParam->bIsAutoConnect == 1)
	{
		list<BluetoothDevice>::iterator it = m_pBtParam->m_listBtDevicesHavePaired.begin();
		g_pClsBtBC6Adapter->setToBtChipConnectHFP((char*)it->deviceAddr,it->addrLen);
		m_pBtParam->bIsSpeedConnectState = false;
		m_pBtModule->deleteNativeTimer(TIME_ID_ONE_TOUCH_SPEED_CONNECT_SWITCH);
	}
}

void CBtHal::PhonebookDownloadFinish(void)
{
	getLoadPhoneBookFinishStatus();	
	m_pBtApp->m_pBtPhoneBookPages->getAllPhoneBookLoadDone();
	m_pBtApp->m_pBtPhoneBookPages->showLoadingPhoneBookTips(0);

	m_pBtModule->btToModule_golf_updatePhoneBook();
	if(m_pBtParam->m_listPhoneBook.size() != 0)
		g_pClsBtJniSdk->sendToAppPhoneBookInfo();
}

void CBtHal::getA2DPPlayOrStopStatus(char state)
{
	m_pBtModule->sendToFlyJNiSdkBtMusicStatus(state);
	if (state == 1)
	{
		m_pBtParam->m_bIsA2dpOnPlayState = false;
		m_pBtParam->bNoA2dpChannelPlay = false;
		LOGD("m_pBtParam->m_bIsA2dpOnPlayState = false");
		m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_PlayStatus(0x02);
	}
	else
	{
		m_pBtParam->m_bIsA2dpOnPlayState = true;
		LOGD("m_pBtParam->m_bIsA2dpOnPlayState = true");
		m_pBtModule->btToOtherModule_Auxscreen_A2DP_Cur_PlayStatus(0x01);
	}
	g_pClsBtJniSdk->sendToAppMusicPlayStatus(m_pBtParam->m_bIsA2dpOnPlayState);
}

void CBtHal::GetA2DPPlayOrStopState_switch(char state)
{
	if(state == 2 && m_pBtParam->m_bIsA2dpOnPlayState == false)
	{
		g_pClsBtBC6Adapter->setToBtChipQueryA2dpInfo();

		u16  nCurSoundMode = 0;
		u8  nCurSoundModelen = 0;
		m_pBtModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8*)&nCurSoundMode,&nCurSoundModelen);
		if(nCurSoundMode != 0x0d)
		{
			m_pBtParam->bNoA2dpChannelPlay = true;
		}
	}	
	
	getA2DPPlayOrStopStatus(state);
}

void CBtHal::Message_GetDevice_OK()
{
	LOGD("Message_GetParrot_OK %s",m_pBtParam->m_SendMessagesStr);
	if(strstr(m_pBtParam->m_SendMessagesStr,"AT#CN\r\n") != NULL)//HFP_AUDIO_SOURCE_MOBILE
	{
		m_pBtHal->getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_PHONE);		 
	}
	else if(strstr(m_pBtParam->m_SendMessagesStr,"AT#CP\r\n") != NULL)//HFP_AUDIO_SOURCE_CAR
	{
		m_pBtHal->getHfpDialingTransferPosStatus(BT_PHONE_STATUS_RECEIVE_BULETOOTH);	 
	}
	else if(strstr(m_pBtParam->m_SendMessagesStr,"AT#CT\r\n") != NULL)//bHangUpAutoDailin
	{
		m_pBtParam->bHangUpAutoDailin = true;
	}
	else if(strstr(m_pBtParam->m_SendMessagesStr,"AT#CS\r\n") != NULL)//bHangUpAutoDailin
	{
		m_pBtParam->bHangUpAutoDailin = true;
	}

	m_pBtParam->m_bCanSendData = true; 
	ActBuffCommand();
}

void CBtHal::Message_GetDevice_ERROR()
{
	m_pBtModule->deleteNativeTimer(TIMER_BC8_NOTRECEIVE);
	m_pBtParam->m_bCanSendData = true; 
	ActBuffCommand();
}

void CBtHal::IsCanSendRequestCmd(void)
{
	if(!m_pBtParam->m_bCanSendData)
	{
		m_pBtModule->setNativeTimer(2000,1,TIMER_BC8_NOTRECEIVE);
	}
}

void CBtHal::Timer_At_CannotReceive(void)
{
	m_pBtParam->m_bCanSendData = true;
	LOGD("Timer_At_CannotReceive");
	ActBuffCommand();
}

void CBtHal::ActBuffCommand(void)
{
	LOGD("---------ActBuffCommand------Start");
	LOGD("m_pBtParam->m_SendMessageBuf.count=%d",m_pBtParam->m_SendMessageBuf.count);
	if(0 == m_pBtParam->m_SendMessageBuf.count)
	{
		m_pBtParam->m_bCanSendData = true;
	} 
	else
	{	
		char str[256]={0};
		int strLen=m_pBtParam->m_SendMessageBuf.cmdGroup[0].len;
		memcpy(str,m_pBtParam->m_SendMessageBuf.cmdGroup[0].cmd,strLen);
		int x=0;
		for(;x < m_pBtParam->m_SendMessageBuf.count-1;x++){
			m_pBtParam->m_SendMessageBuf.cmdGroup[x] = m_pBtParam->m_SendMessageBuf.cmdGroup[x+1];
		}
		m_pBtParam->m_SendMessageBuf.count -= 1;
		setToHalBtMsg(str,strLen);
	}
	LOGD("---------ActBuffCommand------END");
}


void CBtHal::getPairingModeInfors_Bi_directional(char *cP1,int nP1Len,char *cP2,int nP2Len)
{
	if(!m_pBtModule->isBtDeviceSearchFinish())
	{
		m_pBtParam->bHandleStopSearchState = true;
		g_pClsBtBC6Adapter->setToBtChipStopSearchBtDevice();
	}
						
	memset(&m_pBtParam->str_BtPairing,0,sizeof(BT_PairingInfors));

	memcpy(m_pBtParam->str_BtPairing.szPairingPincode,cP1,nP1Len);
	memcpy(m_pBtParam->str_BtPairing.szPairingName,cP2,nP2Len);
	m_pBtParam->str_BtPairing.nPairingPincodeLen = nP1Len;
	m_pBtParam->str_BtPairing.nPairingNameLen = nP2Len;

	m_pBtApp->m_pBtDevicePages->showDialogBox_Pairing((u8*)cP1,nP1Len,(u8*)cP2,nP2Len);
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

void CBtHal::getPhoneCallinOrCalloutPeopleName2(char *pnum)
{
	int n = strlen(pnum);
	int s = m_pBtParam->m_listPhoneBook_BC8.size();
	memset(m_pBtParam->cStrCallPeopleName,0,sizeof(m_pBtParam->cStrCallPeopleName));
	if(s < 1 || n < 1)
		return;
	LOGD("[%s]pnum=%s  n=%d",__FUNCTION__,pnum,n);
	
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itFrom = m_pBtParam->m_listPhoneBook_BC8.begin();
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itTo = m_pBtParam->m_listPhoneBook_BC8.end();
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator it;
	for (it = itFrom; it != itTo; it++)
	{
		//LOGD("zhq it->szUserNo=%s",it->szUserNo);
		if(strncmp(it->szUserNo,pnum,n) == 0)
		{
			memcpy(m_pBtParam->cStrCallPeopleName,it->szUserName,strlen(it->szUserName));
			m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(m_pBtParam->cStrCallPeopleName), strlen(m_pBtParam->cStrCallPeopleName));
			m_pBtApp->setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);
			LOGD("[%s]m_pBtParam->cStrCallPeopleName=%s",__FUNCTION__,m_pBtParam->cStrCallPeopleName);
			return;
		}
	}
}

void CBtHal::getMultiCallState(E_CUR_MULTI_CALL_STATE em)
{
	m_pBtParam->em_MultiCallstate = em;
	LOGD("[%s] m_pBtParam->em_MultiCallstate:%d",__FUNCTION__,m_pBtParam->em_MultiCallstate);

	if(em == MULTI_CALL_STATE_MEETING_TEL)
	{
		memset(m_pBtParam->tempMeetNum1,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memset(m_pBtParam->tempMeetNum2,0,PHONE_NUm_nNPUT_MAX_SIZE);
	}
}



void CBtHal::getCallName(char *input_Num,char *out_Name)
{
	int n = strlen(input_Num);
	int s = m_pBtParam->m_listPhoneBook.size();
	//memset(m_pBtParam->cStrCallPeopleName,0,sizeof(m_pBtParam->cStrCallPeopleName));
	LOGD("[%s]input_Num=%s  n=%d    s=%d",__FUNCTION__,input_Num,n,s);
	if(s < 1 || n < 1)
		return;
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

void CBtHal::analyCallData(char *num,int nLen)
{
	char cCallName[PHONENUM_OR_PHONENAME_MAX_LEN];
	memset(cCallName,0,PHONENUM_OR_PHONENAME_MAX_LEN);
	m_pBtHal->getCallName(num,cCallName);
	int nCallNameLen = strlen(cCallName);

	LOGD("[%s] m_pBtParam->nCallCount:%d",__FUNCTION__,m_pBtParam->nCallCount);
	LOGD("[%s] m_pBtParam->em_MultiCallstate:%d",__FUNCTION__,m_pBtParam->em_MultiCallstate);
	switch(m_pBtParam->nCallCount)
	{
		case CALLING_COUNT_ONLY:
		{
			if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_FREE || m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_CALLING_ONLY)
			{
				m_pBtParam->str_CallInfor[1].m_bIsMicOpenState = true;
				m_pBtParam->str_CallInfor[1].nCaller_State = CALL_RELEASED;
				memset(m_pBtParam->str_CallInfor[1].cCaller_numb,0,PHONENUM_OR_PHONENAME_MAX_LEN);
				m_pBtParam->str_CallInfor[1].nCaller_numbLen = 0;
				memset(m_pBtParam->str_CallInfor[1].cCaller_name,0,PHONENUM_OR_PHONENAME_MAX_LEN);
				m_pBtParam->str_CallInfor[1].nCaller_nameLen= 0;

				m_pBtParam->str_CallInfor[0].m_bIsMicOpenState = true;
				memset(m_pBtParam->str_CallInfor[0].cCaller_numb,0,PHONENUM_OR_PHONENAME_MAX_LEN);
				memcpy(m_pBtParam->str_CallInfor[0].cCaller_numb,num,nLen);
				m_pBtParam->str_CallInfor[0].nCaller_numbLen = nLen;
				memset(m_pBtParam->str_CallInfor[0].cCaller_name,0,PHONENUM_OR_PHONENAME_MAX_LEN);
				memcpy(m_pBtParam->str_CallInfor[0].cCaller_name,cCallName,nCallNameLen);
				m_pBtParam->str_CallInfor[0].nCaller_nameLen= nCallNameLen;

				LOGD("[%s] m_pBtParam->m_strTemWaitingNum:%s",__FUNCTION__,m_pBtParam->m_strTemWaitingNum);
				if(!strncmp(m_pBtParam->m_strTemWaitingNum,m_pBtParam->str_CallInfor[0].cCaller_numb,m_pBtParam->str_CallInfor[0].nCaller_numbLen))
				{
					m_pBtParam->str_CallInfor[0].nCaller_State = WAITING_CALL;
				}
				else
				{
					m_pBtParam->str_CallInfor[0].nCaller_State = ACTIVE_CALL;
				}
			}
		}
		break;
		case CALLING_COUNT_MUTIL:
		{
			if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_CALLING_OR_WAITING)
			{
				LOGD("[%s] m_pBtParam->m_strTemWaitingNum:%s",__FUNCTION__,m_pBtParam->m_strTemWaitingNum);
				if(m_pBtParam->str_CallInfor[1].nCaller_numbLen == 0)
				{
					m_pBtParam->str_CallInfor[0].nCaller_State = WAITING_CALL;
					
					m_pBtParam->str_CallInfor[1].m_bIsMicOpenState = true;
					m_pBtParam->str_CallInfor[1].nCaller_State = ACTIVE_CALL;
					memset(m_pBtParam->str_CallInfor[1].cCaller_numb,0,PHONENUM_OR_PHONENAME_MAX_LEN);
					memcpy(m_pBtParam->str_CallInfor[1].cCaller_numb,num,nLen);
					m_pBtParam->str_CallInfor[1].nCaller_numbLen = nLen;
					memset(m_pBtParam->str_CallInfor[1].cCaller_name,0,PHONENUM_OR_PHONENAME_MAX_LEN);
					memcpy(m_pBtParam->str_CallInfor[1].cCaller_name,cCallName,nCallNameLen);
					m_pBtParam->str_CallInfor[1].nCaller_nameLen= nCallNameLen;
				}
				else
				{
					/*
					if(!strncmp(m_pBtParam->m_strTemWaitingNum,m_pBtParam->str_CallInfor[1].cCaller_numb,nLen))
					{
						m_pBtParam->str_CallInfor[0].nCaller_State = ACTIVE_CALL;
						m_pBtParam->str_CallInfor[1].nCaller_State = WAITING_CALL;
					}
					else if(!strncmp(m_pBtParam->m_strTemWaitingNum,m_pBtParam->str_CallInfor[0].cCaller_numb,nLen))
					{
						m_pBtParam->str_CallInfor[0].nCaller_State = WAITING_CALL;
						m_pBtParam->str_CallInfor[1].nCaller_State = ACTIVE_CALL;
					}*/

					if(!strncmp(num,m_pBtParam->str_CallInfor[0].cCaller_numb,nLen))
					{
						m_pBtParam->str_CallInfor[0].nCaller_State = ACTIVE_CALL;
						m_pBtParam->str_CallInfor[1].nCaller_State = WAITING_CALL;
					}
					else if(!strncmp(num,m_pBtParam->str_CallInfor[1].cCaller_numb,nLen))
					{
						m_pBtParam->str_CallInfor[0].nCaller_State = WAITING_CALL;
						m_pBtParam->str_CallInfor[1].nCaller_State = ACTIVE_CALL;
					}
				}
			}
			else if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_MEETING_TEL)
			{
				m_pBtParam->str_CallInfor[0].m_bIsMicOpenState = true;
				m_pBtParam->str_CallInfor[0].nCaller_State = ACTIVE_CALL;
				m_pBtParam->str_CallInfor[1].m_bIsMicOpenState = true;
				m_pBtParam->str_CallInfor[1].nCaller_State = ACTIVE_CALL;
			}
		}
		break;
	}
	
	LOGD("[%s] 1 (%s)  (%s)",__FUNCTION__,m_pBtParam->str_CallInfor[0].cCaller_name,m_pBtParam->str_CallInfor[0].cCaller_numb);
	LOGD("[%s] 2 (%s)  (%s)",__FUNCTION__,m_pBtParam->str_CallInfor[1].cCaller_name,m_pBtParam->str_CallInfor[1].cCaller_numb);

}

void CBtHal::getHfpBC8Calling(char *input_Num,int len)
{
	LOGD("[%s] m_pBtParam->m_strTemCallingNum:%s",__FUNCTION__,m_pBtParam->m_strTemCallingNum);
	if(strncmp(m_pBtParam->m_strTemCallingNum,input_Num,len))
	{
		memset(m_pBtParam->m_strTemCallingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
		memcpy(m_pBtParam->m_strTemCallingNum,input_Num,len);

		m_pBtHal->getHfpPhoneStatus(BT_PHONE_STATUS_TALKING);
	}
}

void CBtHal::setSyncCallRecordTimer(void)
{
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_CALL_RECORED);
	m_pBtModule->setNativeTimer(2000,1,TIMER_SYNC_CALL_RECORED);
}

void CBtHal::syncInitPhoneBook(void)
{
	if(m_pBtParam->m_listPhoneBook.size() != 0x00)
		return;
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_INIT_PHONE_BOOK);
	m_pBtModule->setNativeTimer(4000,10,TIMER_SYNC_INIT_PHONE_BOOK);
}

void CBtHal::syncInitPhoneBookAllTime(void)
{
	if(m_pBtParam->m_listPhoneBook.size() != 0x00)
		return;
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_INIT_PHONE_BOOK_ALL_TIME);
	m_pBtModule->setNativeTimer(40000,1,TIMER_SYNC_INIT_PHONE_BOOK_ALL_TIME);
}
void CBtHal::syncInitCallRecord(void)
{
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_INIT_CALL_RECORED);
	m_pBtModule->setNativeTimer(4000,5,TIMER_SYNC_INIT_CALL_RECORED);
}

void CBtHal::syncInitCallRecordAllTime(void)
{
	m_pBtModule->deleteNativeTimer(TIMER_SYNC_INIT_CALL_RECORED_ALL_TIME);
	m_pBtModule->setNativeTimer(20000,1,TIMER_SYNC_INIT_CALL_RECORED_ALL_TIME);
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
			//if(strncmp(it->szUserNo,input_Num,n) == 0)
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
				//if(strncmp(it->szUserNo,input_Num,n) == 0)
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

void CBtHal::getVoiceDialingStatus(u8 p)
{
	m_pBtModule->deleteNativeTimer(TIMER_SET_VOICE_DAILING_STATUS);
	
	if(p == 0x00)
	{
		m_pBtParam->m_bVoiceRecgStatus = 0x00;
		m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MIC,0);
		setToHalMobileStatus(0);
	}
	else if(p == 0x01)
	{
		m_pBtParam->m_bVoiceRecgStatus = 0x01;
		m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MIC,1);
	}
}

void CBtHal::supportVoiceStatus(u8 p)
{
	if(p ==  0)
	{
		m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MIC,2);
		m_pBtApp->setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MIC, WIDGET_CTRL_DISABLE);
		m_pBtParam->m_bVioceSupportStatus = 0x00;
	}
	else if(p == 1)
	{
		m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MIC,0);
		m_pBtApp->setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MIC, WIDGET_CTRL_ENABLE);
		m_pBtParam->m_bVioceSupportStatus = 0x01;
	}
}

void CBtHal::callRecordDownloadFinish(void)
{
	m_pBtModule->btToModule_golf_updatePhoneBook();
}

void CBtHal::newGetHistoryCallOneItem(char type,char *pUserName, int userNameLen, char *pUserNo, int userNoLen,char *pUserTime,int userTimeLen)
{
	ST_CALL_RECORD_ONE_USER_INFO t;
	memset(&t, 0, sizeof(ST_CALL_RECORD_ONE_USER_INFO));
	t.CBType=type;
	memcpy(t.szUserName, pUserName, userNameLen);
	memcpy(t.szUserNo, pUserNo, userNoLen);
	memcpy(t.CBTime, pUserTime, userTimeLen);
	
	if(userTimeLen >= 8)
		t.CBTime[8] = '1';
	long long int nTime = 0;
	sscanf(t.CBTime,"%lld",&nTime);
	t.nTime = nTime;
	
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itFrom = (m_pBtParam->m_listHistoryCall).begin();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator itTo = (m_pBtParam->m_listHistoryCall).end();
	list<ST_CALL_RECORD_ONE_USER_INFO>::iterator it;

	for (it = itFrom; it != itTo; it++)
	{
		if(nTime == it->nTime)
		{
			return;
		}
	}

	m_pBtParam->m_listHistoryCall.push_front(t);
	m_pBtParam->m_listHistoryCall.sort();
	m_pBtApp->m_pCallRecordPages->showListHistoryCall();
}


bool CBtHal::judgmentPhoneCallCmd(char *p,int len)
{
	if (	!strncmp(p, "AT#CE", 5) || !strncmp(p, "AT#CF", 5) || !strncmp(p, "AT#CG", 5) ||
		!strncmp(p, "AT#CN", 5) ||!strncmp(p, "AT#CP", 5) || !strncmp(p, "AT#CO", 5) ||
		!strncmp(p, "AT#CQ", 5) ||!strncmp(p, "AT#CR", 5) || !strncmp(p, "AT#CS", 5) ||
		!strncmp(p, "AT#CT", 5) || !strncmp(p, "AT#CX", 5) ||!strncmp(p, "AT#CY", 5) ||
		!strncmp(p, "AT#CW", 5))	
		return true;
	else 
		return false;
}

void CBtHal::setFm1388Switch(bool s)
{
	LOGD("setFm1388Switch: %x",s);
	if(s == false)
		system("echo bt > /dev/fm1388_switch_mode &");
	else if(s == true)
		system("echo dueros > /dev/fm1388_switch_mode &");
}

void CBtHal::getHfpPhoneNumCallTalking(char *pNo, int len)
{
	if(len < 0)
		return;
	
	char tem_Name[PHONE_NUM_NAME_MAX_SIZE] = {0};
	ST_PHONE_NUM phoneNum;	
	memset(&phoneNum,0,sizeof(ST_PHONE_NUM));
	memcpy(phoneNum.szcPhoneNum,pNo,len);
	phoneNum.dwLen=len;
	
	getCallName(phoneNum.szcPhoneNum,tem_Name);
	memcpy(phoneNum.szcName,tem_Name,strlen(tem_Name));
	phoneNum.dwNameLen = strlen(tem_Name);
	m_pBtApp->m_pBtMainPage->PopUp_V_Scereen_showDailingInformations(true,BT_PHONE_STATUS_TALKING,&phoneNum);
	g_pClsBtJniSdk->sendToAppBtPhoneStatusAndNum(0x03,pNo,len,tem_Name,strlen(tem_Name));
}

