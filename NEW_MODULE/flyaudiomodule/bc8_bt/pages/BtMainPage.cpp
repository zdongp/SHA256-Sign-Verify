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
	
	case CONTROLID_MENU_BT:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_JUMP_MAIN:
		clickEntrance(e);
		break;
	case CONTROLID_INCOMING_CALL_PROMPT_BOX:
		clickEntranceBtMainPage(e);
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
	//°ÎºÅÃæ°å
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
	//œÓÌý
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL://jie ting
		clickAnswer(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP://gua duan
		clickHandup(e);
		break;
	//À¶ÑÀµçÔŽ
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NO_BLUETOOTH:
		clickBtPower(e);
		break;
	//ÉùÔŽ
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER://onle one
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER:
	case CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER:
		clickAudioFromFlyDevice(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER://onle one
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER:
	case CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER:
		clickAudioFromMobile(e);
		break;
	//Âó¿Ë·ç
	case CONTROLID_BLUETOOTH_AUDIOVOX_MIC:
		//btVoiceRecgCtl(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SPKAER_LEFT:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_SPKAER_RIGHT:
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE:
	case CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_MUTE_MIC:
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
	//BC8
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_BLUETOOTH_NAME_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_BLUETOOTH_NAME_2:
		break;
	case CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_KEYBOARD_HIDDEN:
		showOrHiddenTalkingPopUp(true);
		showCallInTalkingKeyboardHiddenButton(0x00);
		break;
	case CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_KEYBOARD_SHOW:
		showCallInTalkingKeyboardHiddenButton(0x01);
		showOrHiddenTalkingPopUp(false);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
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

void CBtMainPage::clickEntranceBtMainPage(E_MOUSE_STATUS e)
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
		m_pBtModule->setPage(PAGE_MENU);
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

void CBtMainPage::clickPhoneBookPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
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
				}

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
			   	
			   	if(m_pBtApp->m_pBtPhoneBookPages->m_bIsLoadingPhoneBook == false)
				{
					m_pBtApp->m_pBtPhoneBookPages->clearSearchResultData();	
				}
		}
		break;
		default:break;
	}//switch(e)
}

void CBtMainPage::clickCallHistoryPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			if(HFP_CONNECT_STATUS_CONNECTED == m_pBtParam->m_eHfpConnectStatus){
				m_pBtParam->m_iselectPhoneBook = BT_PBAP_SYNC_PATH_ALL_CALLHISTORY;
				m_pBtApp->m_pCallRecordPages->SwitchSelectRecordType(BT_PBAP_SYNC_PATH_ALL_CALLHISTORY);
				m_pBtApp->m_pCallRecordPages->getAndShowCallRecords(BT_PBAP_SYNC_PATH_ALL_CALLHISTORY);
				m_pBtApp->m_pCallRecordPages->getAndShowCallRecords_New(BT_PBAP_SYNC_PATH_ALL_CALLHISTORY);
			}
			m_pBtModule->setPage(PAGE_BLUETOOTH_MOBILE_RECORD);
		}
		break;
		default:
		break;
	}
}

void CBtMainPage::clickBtSettingPageEntrance(E_MOUSE_STATUS e)
{

	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			g_pClsBtBC6Adapter->setToBtChipQuerySpkAndMicVolume();
			m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_PAIR_SETTING);
		}
		break;
	default:
		break;
	}
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

void CBtMainPage::clickOpenBtMicGainTest(char *param)
{
	if(strcmp(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,DEF_SET_AUDIO_OPEN_SWITCH) == 0)
	{
		LOGD("[%s] BtCallin_SetAudio_TestSwitch:%d",__FUNCTION__,BtCallin_SetAudio_TestSwitch);
		BtCallin_SetAudio_TestSwitch = true;
							
		m_pBtHal->clearPhoneNumInput();
		refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
		m_pBtHal->bohong_test(m_pBtParam->m_nMicVolume ,m_pBtParam->m_nSpkVolume,9);
		return;
	}
	
	if(BtCallin_SetAudio_TestSwitch == true)
	{
		LOGD("[%s] BtCallin_SetAudio_TestSwitch:%d",__FUNCTION__,BtCallin_SetAudio_TestSwitch);
		if(strcmp(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,DEF_SET_AUDIO_CLOSE_SWITCH) == 0){
			BtCallin_SetAudio_TestSwitch = false;
			m_pBtHal->clearPhoneNumInput();
			refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
			return;
		}
	}

}

void CBtMainPage::clickDialPanel(u32 id, E_MOUSE_STATUS e)
{
    LOGD("[%s]",__FUNCTION__);
	
    if(!m_pBtModule->isCanCtrlMainPageFirstLayerWidget())
		return;
		
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			int n = id - CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_0;
			char szButtonMap[13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', '+'};

			if (MOUSE_STATUS_TIMER == e && 0 == n)//³€°Ž 0 ŸÍÊÇ +
				n = 12;
			
			switch(m_pBtModule->getBtPhoneStatus())
			{
			case BT_PHONE_STATUS_FREE:
				{
					LOGD("getBtPhoneStatus : BT_PHONE_STATUS_FREE");
					if (m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUM_MAX_SIZE)
						break;
						
					m_pBtParam->m_stPhoneNumInput.szcPhoneNum[m_pBtParam->m_stPhoneNumInput.dwLen] = szButtonMap[n];
					m_pBtParam->m_stPhoneNumInput.dwLen++;
					
					refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);

					clickOpenAllModule_debug(m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
					clickOpenBtMicGainTest(m_pBtParam->m_stPhoneNumInput.szcPhoneNum);

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
					if(m_pBtParam->bItsAddCalls)
					{
						if (m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUM_MAX_SIZE)
							break;

						m_pBtParam->m_stPhoneNumInput.szcPhoneNum[m_pBtParam->m_stPhoneNumInput.dwLen] = szButtonMap[n];
						m_pBtParam->m_stPhoneNumInput.dwLen++;
						refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
						refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
					}
					else
					{
						if (m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUm_nNPUT_MAX_SIZE)
							break;
						
						m_pBtParam->m_stPhoneNumInput.szcPhoneNum[m_pBtParam->m_stPhoneNumInput.dwLen] = szButtonMap[n];
						m_pBtParam->m_stPhoneNumInput.dwLen++;
						
						refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
						
						m_pBtParam->m_bCanSendData = true;
						g_pClsBtBC6Adapter->setToBtChipDialNumMore((char*)&szButtonMap[n],1);
					}
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
    LOGD("[%s] E_MOUSE_STATUS:%d",__FUNCTION__,e);				
	if(HFP_CONNECT_STATUS_CONNECTED !=  m_pBtModule->getBtConnectStatus())
		return;
	
	switch(e)
	{
	case MOUSE_STATUS_UP:
	{
		   	LOGD("m_pBtParam->nCallCount:%d",m_pBtParam->nCallCount);
			if (m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
			{
				LOGD("[%s] m_pBtParam->str_CallInfor[1].nCaller_State",__FUNCTION__,m_pBtParam->str_CallInfor[1].nCaller_State);
				if(m_pBtModule->getBtPhoneStatus() == BT_PHONE_STATUS_CALL_IN)
				{
					g_pClsBtBC6Adapter->setToBtChipHangSpeakingAndReceiveAnother();
					setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL,1);
					showCallInOrCallOutInfoPanel(false, NULL);
					return;
				}
			}
			
			switch(m_pBtModule->getBtPhoneStatus())
			{
				case BT_PHONE_STATUS_FREE:
				{
					if(m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUM_MIN_SIZE)
					{//°ÎºÅ³öÈ¥
						u8 number[PHONE_NUm_nNPUT_MAX_SIZE];
						memset(number,0,PHONE_NUm_nNPUT_MAX_SIZE);
						memcpy(number, m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
						
						m_pBtParam->m_bCanSendData = true;
						
						g_pClsBtBC6Adapter->setToBtChipDialNum((char*)number, m_pBtParam->m_stPhoneNumInput.dwLen);

						memset(m_pBtParam->m_stPhoneNumInput.szcName,0, PHONE_NUM_NAME_MAX_SIZE);
						m_pBtParam->m_stPhoneNumInput.dwNameLen = 0;
						m_pBtHal->getHfpPhoneNumCallInOrOut(BT_PHONE_STATUS_CALL_OUT,(char*)number,m_pBtParam->m_stPhoneNumInput.dwLen);

						m_pBtParam->m_ePhoneStatus = BT_PHONE_STATUS_CALL_OUT;
						ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_CALL_OUT,true,true,m_pBtParam->m_stPhoneNumInput.szcName,m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
						refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
						m_pBtHal->setToHalMobileStatus(2);
					}
					else if(m_pBtParam->m_stPhoneNumInput.dwLen == 0)//
					{
						if(m_pBtParam->nCallCount == CALLING_COUNT_FREE)
						{
							u32 nNu = strlen(m_pBtParam->st_UserInforsOnetouchDial.szUserNo);
							LOGD("nNu:%d",nNu);
							if(nNu > 0)
							{
								memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,m_pBtParam->st_UserInforsOnetouchDial.szUserNo,nNu);
						     	m_pBtParam->m_stPhoneNumInput.dwLen = nNu;
								
								u32 nNa = strlen(m_pBtParam->st_UserInforsOnetouchDial.szUserName);
								LOGD("nNa:%d",nNa);
								if(nNa > 0)
								{
									m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME, (u8*)(m_pBtParam->st_UserInforsOnetouchDial.szUserName), nNa);
									setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_NAME,true);  
								}
								
						     	m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
								refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
							}
						}
					}
				}
				break;
				case BT_PHONE_STATUS_CALL_IN:
					{
						clickBtAboutDialInFunction_IntermediateProcessing();
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
								LOGD("[%s] m_pBtParam->m_stPhoneNumInput.szcPhoneNum:%s",__FUNCTION__,m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
								memcpy(number, m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);

								m_pBtParam->m_bCanSendData = true;
								g_pClsBtBC6Adapter->setToBtChipDialNum((char*)number, m_pBtParam->m_stPhoneNumInput.dwLen);

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

void CBtMainPage::clickBtAboutDialInFunction_IntermediateProcessing()
{
	m_pBtParam->emTempHfpTalkingTransferSet = HFP_AUDIO_SOURCE_CAR;
	g_pClsBtBC6Adapter->setToBtChipAnswerCallIn();
}

void CBtMainPage::clickHandup(E_MOUSE_STATUS e)
{
	LOGD("[%s] E_MOUSE_STATUS:%x",__FUNCTION__,e);
	E_BT_PHONE_STATUS em = m_pBtModule->getBtPhoneStatus();
	if(e == MOUSE_STATUS_DOWN)
	{
		if(em == BT_PHONE_STATUS_CALL_IN ||
		em == BT_PHONE_STATUS_CALL_OUT ||
		em == BT_PHONE_STATUS_CALL_IN_FROM_THIRD ||
		em == BT_PHONE_STATUS_TALKING)
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_ACTIVATED);
		}
	}
	else if(e == MOUSE_STATUS_UP)
	{
		if(em == BT_PHONE_STATUS_CALL_IN ||
		em == BT_PHONE_STATUS_CALL_OUT ||
		em == BT_PHONE_STATUS_TALKING)
		{

			LOGD("[%s] m_pBtParam->nCallCount:%d,m_pBtParam->em_MultiCallstate:%d",__FUNCTION__,m_pBtParam->nCallCount,m_pBtParam->em_MultiCallstate);
			if(m_pBtParam->nCallCount > CALLING_COUNT_ONLY)
			{
				m_pBtParam->emTempHfpTalkingTransferSet = HFP_AUDIO_SOURCE_CAR;
				if(em == BT_PHONE_STATUS_CALL_IN)
				{
					m_pBtModule->btToModule_NotifyCenter_StopRing();
					m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(false,NULL);
					m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_TALKING,true,true,m_pBtParam->str_CallInfor[0].cCaller_name,m_pBtParam->str_CallInfor[0].cCaller_numb);
					memset(m_pBtParam->m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
					g_pClsBtBC6Adapter->setToBtChipHandUpHandPhone();
				}
				else if(em == BT_PHONE_STATUS_CALL_OUT)
				{
					m_pBtModule->btToModule_NotifyCenter_StopRing();
					m_pBtApp->m_pBtMainPage->showCallInOrCallOutInfoPanel(false,NULL);
					m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_TALKING,true,true,m_pBtParam->str_CallInfor[0].cCaller_name,m_pBtParam->str_CallInfor[0].cCaller_numb);
					m_pBtParam->bSpecialHangUpIsStillOnHold = true;
					memset(m_pBtParam->m_strTemWaitingNum,0,PHONE_NUm_nNPUT_MAX_SIZE);
					g_pClsBtBC6Adapter->setToBtChipHangUpSpeakingAndReceiveAnother();
				}
				else if(em == BT_PHONE_STATUS_TALKING)
				{
					if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_MEETING_TEL)
						g_pClsBtBC6Adapter->setToBtChipHangUpCall();
					else
						g_pClsBtBC6Adapter->setToBtChipHangUpSpeakingAndReceiveAnother();
				}
			}
			else//if(m_pBtParam->nCallCount > CALLING_COUNT_ONLY)
			{
				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DEFAULT);
				g_pClsBtBC6Adapter->setToBtChipHangUpCall();
			}
		}
	}
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
			if (m_pBtParam->m_eHfpAudioSource == HFP_AUDIO_SOURCE_CAR)
				return;

			refreshBTAudioFromFlyDeviceOrFromMobile(HFP_AUDIO_SOURCE_CAR);
			g_pClsBtBC6Adapter->setToBtChipVoiceSwitchToBtChip();
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

			LOGD("[%s] m_pBtParam->m_eHfpAudioSource:%x",__FUNCTION__,m_pBtParam->m_eHfpAudioSource);
			if (m_pBtParam->m_eHfpAudioSource == HFP_AUDIO_SOURCE_MOBILE)
				return;

			refreshBTAudioFromFlyDeviceOrFromMobile(HFP_AUDIO_SOURCE_MOBILE);
			g_pClsBtBC6Adapter->setToBtChipVoiceSwitchToMobilePhone();
		}
		break;
		default:
		break;
	}
}

static bool bState1=false;
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

			if (!bState1){
				bState1 = true;
				g_pClsBtBC6Adapter->setToBtChipVoiceSwitchToMicOpenBC8();
			}
			else{
			 	bState1= false;
				g_pClsBtBC6Adapter->setToBtChipVoiceSwitchToMicOpenBC8();
			}
		}
		break;
	default:
		break;
	}
}

void CBtMainPage::clickSwitchCall(E_MOUSE_STATUS e)
{
	if(HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
		return;
	if(m_pBtParam->nCallCount < CALLING_COUNT_MUTIL)
		return;
	if(m_pBtParam->em_MultiCallstate != MULTI_CALL_STATE_CALLING_OR_WAITING)
		return;
	
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			//refreshBTManyCallInfo(i);
			if(m_pBtParam->str_CallInfor[1].nCaller_State == ACTIVE_CALL)
			m_pBtApp->m_pBtMainPage->CallingAndWaitingFunction_DisplayingToUI(MULTI_CALL_2_1);
			else if(m_pBtParam->str_CallInfor[0].nCaller_State == ACTIVE_CALL)
			m_pBtApp->m_pBtMainPage->CallingAndWaitingFunction_DisplayingToUI(MULTI_CALL_1_2);	
			
			m_pBtParam->m_bCanSendData = true;
			g_pClsBtBC6Adapter->setToBtChipHangSpeakingAndReceiveAnother();

			SwitchCallsToUI(0);
		}
		break;
	case MOUSE_STATUS_DOWN:
		SwitchCallsToUI(1);
		break;
	default:
		break;
	}
}

void CBtMainPage::clickAddCalls(E_MOUSE_STATUS e)
{
	if(HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
		return;
	if(m_pBtModule->getBtPhoneStatus() != BT_PHONE_STATUS_TALKING)
		return;
	if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
		return;

	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
		    if(m_pBtParam->bItsAddCalls)
		    {
		       m_pBtParam->bItsAddCalls = false;

		       if(m_pBtParam->str_CallInfor[0].nCaller_State== ACTIVE_CALL)
		       {
		            ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_TALKING,true,true,m_pBtParam->str_CallInfor[0].cCaller_name,m_pBtParam->str_CallInfor[0].cCaller_numb);
		       }
		       else if(m_pBtParam->str_CallInfor[1].nCaller_State == ACTIVE_CALL)
		       {
		            ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_TALKING,true,true,m_pBtParam->str_CallInfor[1].cCaller_name,m_pBtParam->str_CallInfor[1].cCaller_numb);
		       }
		    }
		    else
		    {
		        m_pBtParam->bItsAddCalls = true;
		        ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_FREE,true,false,(char *)"",(char *)"");

				memset(m_pBtParam->m_stPhoneNumInput.szcPhoneNum,0, PHONE_NUm_nNPUT_MAX_SIZE);
				m_pBtParam->m_stPhoneNumInput.dwLen = 0;
				memset(m_pBtParam->m_stPhoneNumInput.szcName,0, PHONE_NUM_NAME_MAX_SIZE);
				m_pBtParam->m_stPhoneNumInput.dwNameLen = 0;
		    }

		    AddCallsToUI(m_pBtParam->bItsAddCalls);
		}
		break;
		default:break;
	}
}

void CBtMainPage::DisplayInputDialPhoneName(s8 *str_name)
{
    int str_NameLen = strlen(str_name);
	
	if(str_NameLen == 0)
	{
	    LOGD("DisplayInputDialPhoneName----NULL----");
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
	    LOGD("DisplayInputDialPhoneNumber----NULL----");
	    ///if(pLocalParam->ucMobileStatus != 3)
        ///{
        ///    DisplayInputDialPhoneName((s8 *)"");
        ///}
        
	   // memset(pLocalParam->m_strPhoneNumber,0,sizeof(pLocalParam->m_strPhoneNumber));
		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, STRINGID_BT_INPUT_PHONE_NUMBER);
	}
	else
	{
	    LOGD("app DisplayInputDialPhoneNumber ----> str_number = |%s|----**----|%d|---",str_number,str_NumberLen);
		setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL,(u8 *)str_number,str_NumberLen);
	}
}

void CBtMainPage::ActShowCallingInfor_aboutWhenOnlyOneCall(E_BT_PHONE_STATUS nCallState,bool bShowInputNumbDialog,bool bShowName_Prompt,s8 *strName,s8 *strNumber)
{
	LOGD("[%s] nCallState:%d,bShowName_Prompt:%d bShowInputNumbDialog:%d",__FUNCTION__,nCallState,bShowName_Prompt,bShowInputNumbDialog);
	
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

void CBtMainPage::AddCallsToUI(bool bState)
{
    setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_ADD_CALLS,bState);
}

void CBtMainPage::SwitchCallsToUI(bool bState)
{
	setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_SWITCH_CALL,bState);
}

void CBtMainPage::clickMergeCalls(E_MOUSE_STATUS e)
{
	if(HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
		return;
	if(m_pBtParam->nCallCount < CALLING_COUNT_MUTIL)
		return;
	if(m_pBtParam->em_MultiCallstate == MULTI_CALL_STATE_MEETING_TEL)
		return;
	
	switch(e)
	{
		case MOUSE_STATUS_UP:
			{
				if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
				{
					g_pClsBtBC6Adapter->setToBtChipStartMobilePhoneMeeting();
					DisplayingMergeButtonToUI(0);
				}
			}
			break;
		case MOUSE_STATUS_DOWN:
			DisplayingMergeButtonToUI(1);
			break;
		default:break;
	}
}

void CBtMainPage::DisplayingMergeButtonToUI(int nAnalog)
{
    setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MERGE,nAnalog);
}

void CBtMainPage::AddCallsAndMergeButtonSwitchToUI(bool bItsCtrable)
{
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_ADD_CALLS,bItsCtrable);
    setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_ADD_CALLS,bItsCtrable);

    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MERGE,!bItsCtrable);
    setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MERGE,!bItsCtrable);
}

void CBtMainPage::UI_Parrot_ManyPeopleCall_1(u32 strFlag)
{
    if(strFlag == 0)
    {
        setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,(u8 *)"",0);
    }
    else
    {
        setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP, strFlag);
    }
}

void CBtMainPage::UI_Parrot_ManyPeopleCall_2(u32 strFlag)
{
    if(strFlag == 0)
    {
        setUtf8SerialData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,(u8 *)"",0);
    }
    else
    {
        setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN, strFlag);
    }
}

void CBtMainPage::CallingAndWaitingFunction_DisplayingToUI(E_CUR_MULTI_HELD_STATE em)
{
    bool bHandle_name1 = false;
    bool bIcon1 = false;
    bool bStr_Control_1 = false;
    bool bHandle_number1 = false;
    
    bool bHandle_name2 = false;
    bool bIcon2 = false;
    bool bStr_Control_2 = false;
    bool bHandle_number2 = false;
    
    s32 nAnalogDataCall_Name_1 = 0;
    s32 nAnalogDataCall_Name_2 = 0;
    s32 nAnalogDataIphoneIcon_Up = 0;
    s32 nAnalogDataIphoneIcon_Down = 0;
    u8 nAnalogDataNumberUp = 0;
    u8 nAnalogDataNumberDown = 0;
    
    int nAnalogStr_ControlUp = 0;
    int nAnalogStr_ControlDown = 0;
    u32 nStr_Prompt_Call_1 = 0;
    u32 nStr_Prompt_Call_2 = 0;
    
    s8 str_call_name1[256] = {0};
    s8 str_call_name2[256] = {0};
    s8 str_call_num1[256] = {0};
    s8 str_call_num2[256] = {0};


    LOGD("[%s] nCallState:%d",__FUNCTION__,em);


    switch(em)
    {
        case MULTI_CALL_FREE:
            bHandle_name1 = false;
            bIcon1 = false;
            bStr_Control_1 = false;
            bHandle_number1 = false;
            bHandle_name2 = false;
            bIcon2 = false;
            bStr_Control_2 = false;
            bHandle_number2 = false;
            nAnalogDataCall_Name_1 = 0;
            nAnalogDataCall_Name_2 = 0;
            nAnalogDataIphoneIcon_Up = 0;
            nAnalogDataIphoneIcon_Down = 0;
            nAnalogDataNumberUp = 0;
            nAnalogDataNumberDown = 0;
            nAnalogStr_ControlUp = 0;
            nAnalogStr_ControlDown = 0;
            nStr_Prompt_Call_1 = 0;
            nStr_Prompt_Call_2 = 0;
        break;
        case MULTI_CALL_2_1:
            bHandle_name1 = true;
            bIcon1 = true;
            bStr_Control_1 = true;
            bHandle_number1 = true;
            bHandle_name2 = true;
            bIcon2 = true;
            bStr_Control_2 = true;
            bHandle_number2 = true;
            nAnalogDataCall_Name_1 = 1;
            nAnalogDataCall_Name_2 = 0;
            nAnalogDataIphoneIcon_Up = 1;
            nAnalogDataIphoneIcon_Down = 2;
            nAnalogDataNumberUp = 0;
            nAnalogDataNumberDown = 1;
            nAnalogStr_ControlUp = 0;
            nAnalogStr_ControlDown = 1;
            nStr_Prompt_Call_1 = STRINGID_BT__DEVICE_MANYPEOPLECALL_WAITING;
            nStr_Prompt_Call_2 = STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED;
            memcpy(str_call_name1,m_pBtParam->str_CallInfor[0].cCaller_name,sizeof(m_pBtParam->str_CallInfor[0].cCaller_name));
            memcpy(str_call_name2,m_pBtParam->str_CallInfor[1].cCaller_name,sizeof(m_pBtParam->str_CallInfor[1].cCaller_name));
            memcpy(str_call_num1,m_pBtParam->str_CallInfor[0].cCaller_numb,sizeof(m_pBtParam->str_CallInfor[0].cCaller_numb));
            memcpy(str_call_num2,m_pBtParam->str_CallInfor[1].cCaller_numb,sizeof(m_pBtParam->str_CallInfor[1].cCaller_numb));
        break;
        case MULTI_CALL_1_2:
            bHandle_name1 = true;
            bIcon1 = true;
            bStr_Control_1 = true;
            bHandle_number1 = true;
            bHandle_name2 = true;
            bIcon2 = true;
            bStr_Control_2 = true;
            bHandle_number2 = true;
            nAnalogDataCall_Name_1 = 0;
            nAnalogDataCall_Name_2 = 1;
            nAnalogDataIphoneIcon_Up = 2;
            nAnalogDataIphoneIcon_Down = 1;
            nAnalogDataNumberUp = 1;
            nAnalogDataNumberDown = 0;
            nAnalogStr_ControlUp = 1;
            nAnalogStr_ControlDown = 0;
            nStr_Prompt_Call_1 = STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED;
            nStr_Prompt_Call_2 = STRINGID_BT__DEVICE_MANYPEOPLECALL_WAITING;
            memcpy(str_call_name1,m_pBtParam->str_CallInfor[0].cCaller_name,sizeof(m_pBtParam->str_CallInfor[0].cCaller_name));
            memcpy(str_call_name2,m_pBtParam->str_CallInfor[1].cCaller_name,sizeof(m_pBtParam->str_CallInfor[1].cCaller_name));
            memcpy(str_call_num1,m_pBtParam->str_CallInfor[0].cCaller_numb,sizeof(m_pBtParam->str_CallInfor[0].cCaller_numb));
            memcpy(str_call_num2,m_pBtParam->str_CallInfor[1].cCaller_numb,sizeof(m_pBtParam->str_CallInfor[1].cCaller_numb));

        break;
        case MULTI_CALL_MEETING_TEL:
            bHandle_name1 = true;
            bIcon1 = true;
            bStr_Control_1 = true;
            bHandle_number1 = true;
            bHandle_name2 = true;
            bIcon2 = true;
            bStr_Control_2 = true;
            bHandle_number2 = true;
            nAnalogDataCall_Name_1 = 1;
            nAnalogDataCall_Name_2 = 1;
            nAnalogDataIphoneIcon_Up = 2;
            nAnalogDataIphoneIcon_Down = 2;
            nAnalogDataNumberUp = 1;
            nAnalogDataNumberDown = 1;
            nAnalogStr_ControlUp = 1;
            nAnalogStr_ControlDown = 1;
            nStr_Prompt_Call_1 = STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED;
            nStr_Prompt_Call_2 = STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED;
            memcpy(str_call_name1,m_pBtParam->str_CallInfor[0].cCaller_name,sizeof(m_pBtParam->str_CallInfor[0].cCaller_name));
            memcpy(str_call_name2,m_pBtParam->str_CallInfor[1].cCaller_name,sizeof(m_pBtParam->str_CallInfor[1].cCaller_name));
            memcpy(str_call_num1,m_pBtParam->str_CallInfor[0].cCaller_numb,sizeof(m_pBtParam->str_CallInfor[0].cCaller_numb));
            memcpy(str_call_num2,m_pBtParam->str_CallInfor[1].cCaller_numb,sizeof(m_pBtParam->str_CallInfor[1].cCaller_numb));

        break;
    }
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_UP,bHandle_name1);
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_UP,bIcon1);
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,bStr_Control_1);
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,bHandle_number1);
    
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_DOWN,bHandle_name2);
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,bIcon2);
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,bStr_Control_2);
    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,bHandle_number2);


    setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_UP,nAnalogDataCall_Name_1);
    setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_UP,nAnalogDataIphoneIcon_Up);
    setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_UP,nAnalogStr_ControlUp);
    setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,nAnalogDataNumberUp);
    UI_Parrot_ManyPeopleCall_1(nStr_Prompt_Call_1);
    setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_UP,(u8 *)str_call_name1,strlen(str_call_name1));
    setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_UP,(u8 *)str_call_num1,strlen(str_call_num1));

    
    setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_DOWN,nAnalogDataCall_Name_2);
    setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_IPHONE_ICON_DOWN,nAnalogDataIphoneIcon_Down);
    setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MANYPEOPLECALL_STR_DOWN,nAnalogStr_ControlDown);
    setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,nAnalogDataNumberDown);
    UI_Parrot_ManyPeopleCall_2(nStr_Prompt_Call_2);
    setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEL_NAME_DOWN,(u8 *)str_call_name2,strlen(str_call_name2));
    setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL_DOWN,(u8 *)str_call_num2,strlen(str_call_num2));

}

void CBtMainPage::SpecialProblems_DuringAcallling_TheSecondPhoneCalling_SuddenlyGetHandleUpInfor()
{
    ///Message_Parrot_SendMobileStatus(pLocalParam->ucMobileStatus);
    setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP,0);
    setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP,1);
}


void CBtMainPage::DisplayingMuteButtonState()
{
	if (m_pBtParam->m_bIsMicOpen)
	{
		m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE,0);
		m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_MUTE_MIC,0);
	}
	else
	{
		m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_MUTE,1);
		m_pBtApp->setAnalogData((u32)CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_MUTE_MIC,1);
	}
}

void CBtMainPage::refreshPhoneNumInput(char *p, u32 len)
{
    LOGD("[%s] len:%d",__FUNCTION__,len);
	if (0 == len){
		setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, STRINGID_BT_INPUT_PHONE_NUMBER);
	}
	else{
		m_pBtApp->setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, (u8*)p,len);
		//setAnsiSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_TEL, (u8*)p, len);
	}
}

void CBtMainPage::refreshAnswerHandup(E_BT_PHONE_STATUS e)
{   
	setUpdateUI(false);

	switch(e)
	{
	case BT_PHONE_STATUS_FREE:
		{
			LOGD("[%s]",__FUNCTION__);
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, PIC_WIDGET_STATUS_DISABLE);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP, WIDGET_CTRL_DISABLE);

		       LOGD("[%s]  ConnectStatus: %d",__FUNCTION__,m_pBtModule->getBtConnectStatus());
			if(HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
			{    
			       
				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DISABLE);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_DISABLE);
			}
			else
			{     
				LOGD("[%s] PhoneNumLen  %d",__FUNCTION__,m_pBtParam->m_stPhoneNumInput.dwLen);
				if((m_pBtParam->m_stPhoneNumInput.dwLen == 0) || (m_pBtParam->m_stPhoneNumInput.dwLen >= PHONE_NUM_MIN_SIZE))
				{
					setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DEFAULT);
					setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_ENABLE);
				}
				else if((m_pBtParam->m_stPhoneNumInput.dwLen > 0) && (m_pBtParam->m_stPhoneNumInput.dwLen < PHONE_NUM_MIN_SIZE))
				{
					setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DISABLE);
					setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_DISABLE);
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
			LOGD("[%s] m_pBtParam->bItsAddCalls:%d",__FUNCTION__,m_pBtParam->bItsAddCalls);
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

void CBtMainPage::showCallInOrCallOutInfoPanel(bool bShow, ST_PHONE_NUM *pstPhoneNum)
{
	LOGD("[%s] bShow = [%s], phone num = [%s]", __FUNCTION__,  bShow ? "Yes" : "No", pstPhoneNum->szcPhoneNum);

	setUpdateUI(false);
	//setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DISPLAY_DELETE, bShow ? WIDGET_CTRL_DISABLE : WIDGET_CTRL_ENABLE);
	//setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CALL_LOG, bShow ? WIDGET_CTRL_DISABLE : WIDGET_CTRL_ENABLE);

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

	#ifdef MSM_ANDROID_ISR_NEW_FUNCTION
	if(bShow)
	{
		m_pBtApp->m_pBtMainPage->IncomingCallWindowPromt(m_pBtParam->emPhoneStatusBallon,true,m_pBtModule->getCurPageId());
	}
	else
	{
		m_pBtApp->m_pBtMainPage->IncomingCallWindowPromt(m_pBtParam->emPhoneStatusBallon,false,m_pBtModule->getCurPageId());
	}
	#endif
	
}

void CBtMainPage::DisplayInputDialPhoneTextPrompt(E_BT_PHONE_STATUS nCallState)
{
	LOGD("[%s] E_BT_PHONE_STATUS:%d",__FUNCTION__,nCallState);
	
	int nStringID = 0;
	if(nCallState == BT_PHONE_STATUS_FREE){
		setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEXT, (u8 *)"",0);
		return;
	}
    else if(nCallState == BT_PHONE_STATUS_TALKING){//calling
		nStringID = STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED;
    }
	else if(nCallState == BT_PHONE_STATUS_CALL_OUT){//outing
	    nStringID = STRINGID_BT_CALL_OUT;
	}
	else if(nCallState == BT_PHONE_STATUS_CALL_IN){//incoming
	   	nStringID = STRINGID_BT_CALL_IN;
	}

	setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIALED_TEXT, nStringID);

}
void CBtMainPage::refreshPhoneOrCarAnswer(E_HFP_AUDIO_SOURCE e)
{
	setUpdateUI(false);

	if (HFP_CONNECT_STATUS_CONNECTED != m_pBtModule->getBtConnectStatus())
	{
		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER, WIDGET_CTRL_DISABLE);

		setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
		setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER, WIDGET_CTRL_DISABLE);

		setAnalogData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
		setCtrlEnable(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, WIDGET_CTRL_DISABLE);

		setAnalogData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
		setCtrlEnable(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, WIDGET_CTRL_DISABLE);
	}
	else
	{
		switch(e)
		{
			case HFP_AUDIO_SOURCE_MOBILE:
			{
				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER, PIC_WIDGET_STATUS_ACTIVATED);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER, WIDGET_CTRL_DISABLE);

				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER, WIDGET_CTRL_ENABLE);

				setAnalogData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, PIC_WIDGET_STATUS_ACTIVATED);
				setCtrlEnable(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, WIDGET_CTRL_DISABLE);

				setAnalogData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
				setCtrlEnable(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, WIDGET_CTRL_ENABLE);
			}
			break;
			case HFP_AUDIO_SOURCE_CAR:
			{
				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER, WIDGET_CTRL_ENABLE);

				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER, PIC_WIDGET_STATUS_ACTIVATED);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER, WIDGET_CTRL_DISABLE);

				setAnalogData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
				setCtrlEnable(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, WIDGET_CTRL_ENABLE);

				setAnalogData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, PIC_WIDGET_STATUS_ACTIVATED);
				setCtrlEnable(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, WIDGET_CTRL_DISABLE);
			}
			break;
			case HFP_AUDIO_SOURCE_UNKNOW:
			{
				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_ANSWER, WIDGET_CTRL_DISABLE);

				setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
				setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_CAR_ANSWER, WIDGET_CTRL_DISABLE);

				setAnalogData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
				setCtrlEnable(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, WIDGET_CTRL_DISABLE);

				setAnalogData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, PIC_WIDGET_STATUS_DEFAULT);
				setCtrlEnable(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, WIDGET_CTRL_DISABLE);
			}
			break;
		}
	}

	setUpdateUI(true);
}

void CBtMainPage::refreshLocalBtDeviceVersion(char* BtVersion,int len)
{
       
	setUtf8String(CONTROLID_COPYRIGHT_BLUETOOTH, (u8*)BtVersion, len);
	
}

void CBtMainPage::refreshRemodeBtDeviceName(u8 *param,u32 len)
{
	setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_BLUETOOTH_NAME, param, len);
}

void CBtMainPage::refreshBTAudioFromFlyDeviceOrFromMobile(E_HFP_AUDIO_SOURCE cFlag)
{
	LOGD("[%s] ------>cFlag===%d",__FUNCTION__,cFlag);
	refreshPhoneOrCarAnswer(cFlag);
	
	setUpdateUI(false);
	switch(cFlag)
	{
		case HFP_AUDIO_SOURCE_MOBILE:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER,0);
			setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER,true);
			setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,false);
		}
		break;
		case HFP_AUDIO_SOURCE_CAR:
		{	
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,0);
			setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,true);
			setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER,false);
		}
		break;
		case HFP_AUDIO_SOURCE_UNKNOW:
		{
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,2);
		    setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER,true);
			setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER,false);
		}
		break;
		default:break;
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
		}
		break;
	default:
		break;
	}
}

void CBtMainPage::ShowOrHid_PhonePair_PromptBox(int cFlag)
{
	LOGD("[%s] cFlag = %d",__FUNCTION__,cFlag);
	setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_PHONE_PAIRING,cFlag);
	setVisible(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_BACKGROUND,cFlag);
	setVisible(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_TEXT,cFlag);
	setVisible(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_DEVICE_NAME_TEXT,cFlag);
	setVisible(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_PASSWORD_TEXT,cFlag);
	setVisible(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_DEVICE_NAME,cFlag);
	setVisible(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_PASSWORD,cFlag);
	setAnsiSerialData(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_DEVICE_NAME,(u8*)m_pBtParam->szLocalBtDevice_Name,strlen(m_pBtParam->szLocalBtDevice_Name));
	setAnsiSerialData(CONTROLID_BLUETOOTH_MAIN_PAIR_NOTICE_PASSWORD,(u8*)m_pBtParam->szLocalBtDevice_PinCode,strlen(m_pBtParam->szLocalBtDevice_PinCode));
}

void CBtMainPage::btVoiceRecgCtl(E_MOUSE_STATUS e)
{
	if(e == MOUSE_STATUS_UP)
	{
		if(m_pBtParam->m_eHfpConnectStatus != HFP_CONNECT_STATUS_CONNECTED)
			return;
		if(m_pBtParam->m_ePhoneStatus != BT_PHONE_STATUS_FREE)
			return;
		switch(m_pBtParam->m_bVoiceRecgStatus)
		{
			case 0x00:
				{
					g_pClsBtBC6Adapter->setToBtChipStartVoiceDial();
					m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MIC,1);
					m_pBtHal->setToHalMobileStatus(2);
					m_pBtModule->setNativeTimer(2000,1,TIMER_SET_VOICE_DAILING_STATUS);
					
				}
				break;
				
			case 0x01:
				{
					g_pClsBtBC6Adapter->setToBtChipCancleVoiceDial();
					m_pBtApp->setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MIC,0);
					m_pBtHal->setToHalMobileStatus(0);
				}
				break;
			default:break;
		}
	}
}

void CBtMainPage::IncomingCallWindowPromt(E_BT_PHONE_STATUS s,bool b,u32 pageID)
{
	if(b)
	{
		switch(s)
		{
			case BT_PHONE_STATUS_CALL_IN:
			{
				if(m_pBtApp->DontDisplayWindowPromptAboutT123Video())
				{
					m_pBtApp->btToApp_CallingWindowPrompt(0x00);
				}
				else if(pageID == PAGE_BLUETOOTH_MAIN || pageID == PAGE_BACK_VIDEO)
				{
					m_pBtApp->btToApp_CallingWindowPrompt(0x00);
				}
				else
				{
					ST_PHONE_NUM pstT;
					memset(&pstT,0,sizeof(ST_PHONE_NUM));
					u32 uNameLen = strlen(m_pBtParam->cStrCallPeopleName);
					u32 uNumLen = strlen(m_pBtParam->szPhoneNumCallInOrOut);

					if(uNameLen > 0)
						memcpy(pstT.szcName,m_pBtParam->cStrCallPeopleName,uNameLen);

					if(uNumLen > 0)
						memcpy(pstT.szcPhoneNum,m_pBtParam->szPhoneNumCallInOrOut,uNumLen);
					
					m_pBtApp->MakeCallingInforsToUI(m_pBtParam->emPhoneStatusBallon,&pstT);
					m_pBtApp->btToApp_CallingWindowPrompt(0x01);
				}
			}
			break;
			default:
				m_pBtApp->btToApp_CallingWindowPrompt(0x00);
			break;
		}
	}
	else
	{
		m_pBtApp->btToApp_CallingWindowPrompt(0x00);
	}
}

void CBtMainPage::PopUp_V_Scereen_showDailingInformations(bool v,E_BT_PHONE_STATUS s,ST_PHONE_NUM *pstPhoneNum)
{
	if(v)
	{
		if(s == BT_PHONE_STATUS_FREE){
		}
		else if(s == BT_PHONE_STATUS_CALL_IN){
			setStringById(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER_STATE_ICON, STRINGID_BT_CALL_IN);
		}
		else if(s == BT_PHONE_STATUS_CALL_OUT){
			setStringById(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER_STATE_ICON, STRINGID_BT_CALL_OUT);
		}
		else if(s == BT_PHONE_STATUS_TALKING){
			setStringById(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER_STATE_ICON, STRINGID_BT__DEVICE_MANYPEOPLECALL_DIALED);
		}

		if(pstPhoneNum)
		{
			setUtf8SerialData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_DIALING_NUM, (u8*)pstPhoneNum->szcPhoneNum, pstPhoneNum->dwLen);
			m_pBtApp->setUtf8SerialData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_DIALING_NAME, (u8*)pstPhoneNum->szcName, strlen(pstPhoneNum->szcName));
		}
		else
		{
			setAnsiSerialData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_DIALING_NUM, (u8*)"--", strlen("--"));
			setAnsiSerialData(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_DIALING_NAME, (u8*)"--", strlen("--"));
		}
	}
	
	showOrHiddenTalkingPopUp(v);
}

void CBtMainPage::showCallInTalkingKeyboardHiddenButton(u8 param)
{
	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_KEYBOARD_HIDDEN, param);
}

void CBtMainPage::showOrHiddenTalkingPopUp(bool p)
{
	setUpdateUI(false);
	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_DIALING_NUM, p);
	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_DIALING_NAME, p);
	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER_STATE_ICON, p);

	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_PHONE_ANSWER, p);
	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_CAR_ANSWER, p);
	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_KEYBOARD_SHOW, p);
	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN_MUTE_MIC, p);
	setVisible(CONTROLID_BLUETOOTH_CALL_POP_UP_V_SCREEN, p);
	setUpdateUI(true);
}

