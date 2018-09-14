#include "PhoneBookPages.h"
#include "myUnicode2PinyinTable.h"


CPhoneBookPages::CPhoneBookPages(void)
{
	memset(m_szPhoneBookSearchWordUnicode, 0, SIZE_PHONE_BOOK_SEARCH_WORD);
	m_nPhoneBookSearchWordLenUnicode = 0;

	m_nSearchPageBrowseFrom = 0;
	m_nSearchRankPageBrowseFrom = 0;
	m_nSearchResultPageBrowseFrom = 0;
	m_nSearchPageActiveIndex = -1;
	m_nSearchResultPageActiveIndex = -1;
	m_nOneNameForMultipleNum = -1;
	m_nOneNameForMultipleNumIndex = -1;

	m_bIsLoadingPhoneBook = true;
	//rank page
	m_nSearchRankPageBrowseFrom = 0;
}

CPhoneBookPages::~CPhoneBookPages(void)
{
	clearSearchResult();
	clearPhoneBook();
}

void CPhoneBookPages::init(void) 
{ 

} 

void CPhoneBookPages::deInit(void)
{
	u16 pageId = m_pBtModule->getCurPageId();
	if (pageId == PAGE_BLUETOOTH_AUDIOVOX_CONTACTS)
	{
		m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
	}

	clearSearchResult();
	clearPhoneBook();
	refreshSearchPageSearchResult(0);
	refreshSearchPagePhoneRank(0);

	memset(m_szPhoneBookSearchWordUnicode, 0, SIZE_PHONE_BOOK_SEARCH_WORD);
	m_nPhoneBookSearchWordLenUnicode = 0;

	m_nSearchPageBrowseFrom = 0;
	m_nSearchRankPageBrowseFrom = 0;
	m_nSearchResultPageBrowseFrom = 0;
	m_nSearchPageActiveIndex = -1;
	m_nSearchResultPageActiveIndex = -1;

	m_bIsLoadingPhoneBook = true;
	//rank page
	m_nSearchRankPageBrowseFrom = 0;
	
}

void CPhoneBookPages::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
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

void CPhoneBookPages::initUi(void)
{
	LOGD("m_pBtParam->nNationalDistinction:%d",m_pBtParam->nNationalDistinction);
	if(m_pBtParam->nNationalDistinction == NATIONAL_CHINA || m_pBtParam->nNationalDistinction == NATIONAL_UNKNOW)//china needn't 
    {
        setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SWITCH,false);
        setVisible(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_GO_TO_ENGLISH_KEY_BOARD,false);
    }

	/*
	switch(m_pBtParam->nNationalDistinction)
	{
			case NATIONAL_CHINA://CN
				m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ENGLISH;
			break;
			case NATIONAL_RUSSIA://Russian
				m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_RUSSIA;
			break;
			case NATIONAL_ARAB://Arabic
				m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ARAB;
			break;
			case NATIONAL_ISRAEL://Hebrew
				m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ISRAEL;
			break;
			default:
				m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage = KEY_BOARD_LANGUAGE_ENGLISH;
			break;
	}
	*/
}

bool CPhoneBookPages::pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = false;

	bRet = phoneBookSearchPage(id, e, p, len);
	if (bRet)
		return true;

	bRet = phoneBookSearchResultPage(id, e, p, len);
	if (bRet)
		return true;
	
	bRet = phoneBookRankSearchPage(id, e, p, len);
	if (bRet)
		return true;
	
	return bRet;
}

bool CPhoneBookPages::phoneBookSearchPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
		//ÌøÒ³
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_BACK:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_BACK:
		clickSearchPageGoBack(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SWITCH:
		clickSearchPageIsRaelKeyBoardEntrance(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_GO_TO_ENGLISH_KEY_BOARD:
		clickSearchPageEnglishKeyBoardEntrance(e);
		break;
		//ËÑË÷œá¹û
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_3:
		clickSearchPageSearchResultItem(id, e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_PRE_PAGE:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_PAGE_UP:
		clickSearchPagePrePage(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_NEXT_PAGE:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_PAGE_DOWN:
		clickSearchPageNextPage(e);
		break;
	//ŒüÅÌ
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DELETE://ÍËžñŒü
		clickSearchPageBackspace(e);
		break;
	//Ó¢ÎÄ
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_A:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_B:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_C:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_D:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_E:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_F:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_G:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_H:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_I:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_J:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_K:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_L:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_M:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_N:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_O:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_P:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_Q:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_R:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_S:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_T:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_U:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_V:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_W:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_X:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_Y:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_Z:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_BLANK:
	//ÒÔÉ«ÁÐ
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_9:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_10:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_11:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_12:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_13:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_14:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_15:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_16:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_17:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_18:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_19:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_20:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_21:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_22:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_23:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_24:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_25:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_26:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_27:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_31:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_BLANK:
	//¶íÂÞË¹ŒüÅÌ
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_9:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_10:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_11:

	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_9:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_10:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_11:

	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_9:
	//°¡À­²®
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_9:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_10:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_11:

	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_9:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_10:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_11:

	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_5:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_9:
		clickSearchPageKeyPanel(id, e);
		break;
	case CONTROLID_BLUETOOTH_PHONE_BOOK_RANK_SWITCH:
			clickPhoneBookPageToRankPage(e);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

bool CPhoneBookPages::phoneBookSearchResultPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_BACK:
		clickSearchResultPageGoBack(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_PREV:
		//clickSearchResultPagePrePage(e);
		clickSearchResultPagePrePage_New(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_NEXT:
		//clickSearchResultPageNextPage(e);
		clickSearchResultPageNextPage_New(e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_2:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_3:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_4:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_5:
		clickSearchResultPageNameItem(id, e);
		break;
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_6:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_7:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_8:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_9:
	case CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_10:
		clickSearchResultPageNumItem(id, e);
		break;
		//ÌøÒ³
	default:
		bRet = false;
		break;
	}//switch(id)

	return bRet;
}

void CPhoneBookPages::clickSearchPageGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
			
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchPageBackspace(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			if (getLoadPhoneBookStatus())
				return;

			if (m_nPhoneBookSearchWordLenUnicode >= 2)
			{
				if(e == MOUSE_STATUS_UP)
				{
					m_szPhoneBookSearchWordUnicode[m_nPhoneBookSearchWordLenUnicode - 1] = 0;
					m_szPhoneBookSearchWordUnicode[m_nPhoneBookSearchWordLenUnicode - 2] = 0;
					m_nPhoneBookSearchWordLenUnicode -= 2;
				}
				else if(e == MOUSE_STATUS_TIMER)
				{
					memset(m_szPhoneBookSearchWordUnicode, 0, SIZE_PHONE_BOOK_SEARCH_WORD);
					m_nPhoneBookSearchWordLenUnicode = 0;				
				}
				setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);
				setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_KEY_WORD_INPUT, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);
			}

			if(m_pBtParam->m_nBtLanguageType != 0x00)
				beginAccurateSearchKeyWord();
			else
				beginSearchKeyWord();
		}
		break;
		default:
		break;
	}
}

void CPhoneBookPages::clearSearchResultData()
{
	while(m_nPhoneBookSearchWordLenUnicode>=2)
	{
		m_szPhoneBookSearchWordUnicode[m_nPhoneBookSearchWordLenUnicode - 1] = 0;
		m_szPhoneBookSearchWordUnicode[m_nPhoneBookSearchWordLenUnicode - 2] = 0;
		m_nPhoneBookSearchWordLenUnicode -= 2;
	}
	setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);
	setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_KEY_WORD_INPUT, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);

	if(m_pBtParam->m_nBtLanguageType != 0x00)
		beginAccurateSearchKeyWord();
	else
		beginSearchKeyWord();
}

void CPhoneBookPages::clickSearchPageKeyPanel(u32 id, E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			if(m_nPhoneBookSearchWordLenUnicode > SIZE_PHONE_BOOK_SEARCH_WORD - 4)
				return;
			if (getLoadPhoneBookStatus())
				return;
			
			wchar_t r = getPhoneBookKeyBoardKeyNameById(e, id);

			//////////////////////////////////////////////////////////////////////////
			int i = 0;
			u8 szLog[4] = {0};
			memcpy(szLog, &r, 4);
			LOGD("[%s] 0 [0x%x] 1 [0x%x] 2 [0x%x] 3 [0x%x]", __FUNCTION__,  szLog[0], szLog[1], szLog[2], szLog[3]);
			//////////////////////////////////////////////////////////////////////////
			if (r != 0 && r != L'~')
			{
				u8 *p = (u8*)&r;
				m_szPhoneBookSearchWordUnicode[m_nPhoneBookSearchWordLenUnicode++] = p[0];
				m_szPhoneBookSearchWordUnicode[m_nPhoneBookSearchWordLenUnicode++] = p[1];
				setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);
				setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_KEY_WORD_INPUT, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);			

				if( m_pBtParam->m_nBtLanguageType != 0x00){
					beginAccurateSearchKeyWord();
				}
				else{
					beginSearchKeyWord();
				}
			}
		}
		break;
	default:
		break;
	}//switch(e)
}

void CPhoneBookPages::clickSearchPagePrePage(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nPreStartBrowse = -1;
			nPreStartBrowse = m_nSearchPageBrowseFrom;
			m_nSearchPageBrowseFrom = max(0, m_nSearchPageBrowseFrom - SEARCH_RESULT_LIST_DISPLAY_NUM);

			if (nPreStartBrowse == m_nSearchPageBrowseFrom)
				return;

			refreshSearchPageSearchResult(m_nSearchPageBrowseFrom);
			
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchPageNextPage(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_nSearchPageBrowseFrom;

			m_nSearchPageBrowseFrom += SEARCH_RESULT_LIST_DISPLAY_NUM;
			if (m_nSearchPageBrowseFrom >= (int)m_listPhoneNumUserInfoHaveSelected.size())
				m_nSearchPageBrowseFrom -= SEARCH_RESULT_LIST_DISPLAY_NUM;
			LOGD("nNextStartBrowse : d   m_nSearchPageBrowseFrom :%d",nNextStartBrowse,m_nSearchPageBrowseFrom);
			if(nNextStartBrowse == m_nSearchPageBrowseFrom)
				return;

			refreshSearchPageSearchResult(m_nSearchPageBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchPageSearchResultItem(u32 id, E_MOUSE_STATUS e)
{
	if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_IN || m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_OUT)
		return;
	if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
		return;

	static int i = 0, j = 0, m = 0;
	static list<ST_PhoneBookUserInfo>::iterator itFrom;
	static list<ST_PhoneBookUserInfo>::iterator itTo;
	static list<ST_PhoneBookUserInfo>::iterator it;

	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			i = 0, j = 0, m = 0;

			if (id >= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1 && id <= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_3)
				i = id - CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1;
			else if (id >= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1 && id <= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_3)
				i = id - CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1;

			m = i;
			i = m_nSearchPageBrowseFrom + i;

			itFrom = m_listPhoneNumUserInfoHaveSelected.begin();
			itTo = m_listPhoneNumUserInfoHaveSelected.end();

			//ÕÒ¶ÔÓŠµÚÒ»ÏîÒªÏÔÊŸ
			j = 0;
			for (it = itFrom; it != itTo; it++)
			{
				if (i == j)
					break;
				j++;
			}

			if (it != itTo)
			{
				setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1, (1 << m) & 1);
				setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_2, (1 << m) & 2);
				setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_3, (1 << m) & 4);

				setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1, (1 << m) & 1);
				setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_2, (1 << m) & 2);
				setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_3, (1 << m) & 4);
			}
		}
		break;
	case MOUSE_STATUS_UP:
		{
			if (it != itTo)
			{
				setDigitalData(id, 0);

				int k = 0;
				for (k = 0; k < SEARCH_RESULT_LIST_DISPLAY_NUM; k++)
				{
					if (k < it->nPhoneNumInfoCount)
					{
						setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_6 + k, (u8*)it->szstPhoneNumInfo[k].szPhoneNumUtf8, strlen(it->szstPhoneNumInfo[k].szPhoneNumUtf8));
						memset(&m_szStrPhoneNumOfOneNameShowUtf8[k], 0, PHONE_NUM_MAX_SIZE * 4);
						memcpy(&m_szStrPhoneNumOfOneNameShowUtf8[k], it->szstPhoneNumInfo[k].szPhoneNumUtf8, strlen(it->szstPhoneNumInfo[k].szPhoneNumUtf8));
					}
					else
					{
						setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_6 + k, (u8*)"", 0);
						memset(&m_szStrPhoneNumOfOneNameShowUtf8[k], 0, PHONE_NUM_MAX_SIZE * 4);
					}

					
				}

				if (it->nPhoneNumInfoCount == 1)
				{
					memset(&(m_pBtParam->m_stPhoneNumInput), 0, sizeof(ST_PHONE_NUM));
					
					int nLen = strlen(it->szstPhoneNumInfo[0].szPhoneNumUtf8);
					memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, (u8*)it->szstPhoneNumInfo[0].szPhoneNumUtf8, nLen);
					m_pBtParam->m_stPhoneNumInput.dwLen = nLen;
						
					memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserNameUtf8, strlen(it->szUserNameUtf8));	
					if(m_pBtParam->nCallCount != CALLING_COUNT_FREE)
		        	{
		            	m_pBtParam->bItsAddCalls = true;
						m_pBtApp->m_pBtMainPage->AddCallsToUI(m_pBtParam->bItsAddCalls);
		        	}
					
					m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_FREE,true,true,it->szUserNameUtf8,m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
					m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
					m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
				}
				else if (it->nPhoneNumInfoCount > 1)
				{
					/*
					m_nOneNameForMultipleNum = i - (i%5);
					m_nOneNameForMultipleNumIndex = i;
					memset(m_szStrPhoneNumOfOneName_Name, 0, SIZE_PHONE_BOOK_SEARCH_WORD * 4);
					memcpy(m_szStrPhoneNumOfOneName_Name, it->szUserNameUtf8, strlen(it->szUserNameUtf8));
					setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT,(u8 *) it->szUserNameUtf8,  strlen(it->szUserNameUtf8));
					refreshSearchResultPageSearchResult_New(m_nOneNameForMultipleNum);
					m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_CONTACTS);
					*/
					getNameListTagAndInfo(i,it->szUserNameUtf8);
				}
			}
		}
		break;
	default:
		break;
	}
}

//phoneBookSearchResultPage
void CPhoneBookPages::clickSearchResultPageGoBack(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			//clickSearchPageIsRaelKeyBoardEntrance(e);
			m_pBtModule->setPrePage();
			clearOneNameForMultNumShow();
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchResultPagePrePage(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nPreStartBrowse = -1;
			nPreStartBrowse = m_nSearchResultPageBrowseFrom;
			m_nSearchResultPageBrowseFrom = max(0, m_nSearchResultPageBrowseFrom - SEARCH_RESULT_LIST_DISPLAY_NUM);

			if (nPreStartBrowse == m_nSearchResultPageBrowseFrom)
				return;

			refreshSearchResultPageSearchResult(m_nSearchResultPageBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchResultPageNextPage(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_nSearchResultPageBrowseFrom;

			m_nSearchResultPageBrowseFrom += SEARCH_RESULT_LIST_DISPLAY_NUM;
			if (m_nSearchResultPageBrowseFrom >= (int)m_listPhoneNumUserInfoHaveSelected.size())
				m_nSearchResultPageBrowseFrom -= SEARCH_RESULT_LIST_DISPLAY_NUM;

			if(nNextStartBrowse == m_nSearchResultPageBrowseFrom)
				return;

			refreshSearchResultPageSearchResult(m_nSearchResultPageBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchResultPageNameItem(u32 id, E_MOUSE_STATUS e)
{
	static int i = 0, j = 0, m = 0, k = 0;
	static list<ST_PhoneBookUserInfo>::iterator itFrom;
	static list<ST_PhoneBookUserInfo>::iterator itTo;
	static list<ST_PhoneBookUserInfo>::iterator it;
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			i = 0, j = 0, m = 0, k = 0;

			if (id >= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 && id <= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_5)
				i = id - CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1;

			m = i;
			//i = m_nSearchResultPageBrowseFrom + i;
			i = m_nOneNameForMultipleNum + i;
			itFrom = m_listPhoneNumUserInfoHaveSelected.begin();
			itTo = m_listPhoneNumUserInfoHaveSelected.end();
			//ÕÒ¶ÔÓŠµÚÒ»ÏîÒªÏÔÊŸ
			j = 0;
			for (it = itFrom; it != itTo; it++)
			{
				if (i == j)
					break;
				j++;
			}
			if (it != itTo)
			{
				for (k = 0; k < 5; k++)
					setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 + k, (1 << m) & (int)pow(2.0, k * 1.0));
			}
		}
		break;
	case MOUSE_STATUS_UP:
		{
			if (it != itTo)
			{
				for (k = 0; k < 5; k++)
				{
					if (k < it->nPhoneNumInfoCount)
					{
						setUtf8String(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_6 + k, (u8*)it->szstPhoneNumInfo[k].szPhoneNumUtf8, strlen(it->szstPhoneNumInfo[k].szPhoneNumUtf8));
						memset(&m_szStrPhoneNumOfOneNameShowUtf8[k], 0, PHONE_NUM_MAX_SIZE * 4);
						int nLen = strlen(it->szstPhoneNumInfo[k].szPhoneNumUtf8);
						if(nLen >(PHONE_NUM_MAX_SIZE * 4))
							nLen = PHONE_NUM_MAX_SIZE * 4;
						memcpy(&m_szStrPhoneNumOfOneNameShowUtf8[k], it->szstPhoneNumInfo[k].szPhoneNumUtf8, nLen);
					}
					else
					{
						setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_6 + k, (u8*)"", 0);
						memset(&m_szStrPhoneNumOfOneNameShowUtf8[k], 0, PHONE_NUM_MAX_SIZE * 4);
					}
				}
			}
			memset(m_szStrPhoneNumOfOneName_Name, 0, SIZE_PHONE_BOOK_SEARCH_WORD * 4);
			memcpy(m_szStrPhoneNumOfOneName_Name, it->szUserNameUtf8, strlen(it->szUserNameUtf8));
			m_nOneNameForMultipleNum = i - (i%5);
			m_nOneNameForMultipleNumIndex  = i;
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchResultPageNumItem(u32 id, E_MOUSE_STATUS e)
{
	int iIndex = id - CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_6;
	if (strlen(m_szStrPhoneNumOfOneNameShowUtf8[iIndex]) == 0)
	{
		return;
	}

	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			setAnalogData(id, PIC_WIDGET_STATUS_ACTIVATED);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			memset(&(m_pBtParam->m_stPhoneNumInput), 0, sizeof(ST_PHONE_NUM));
			int nLen = strlen(m_szStrPhoneNumOfOneNameShowUtf8[iIndex]);
			memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_szStrPhoneNumOfOneNameShowUtf8[iIndex], nLen);
			m_pBtParam->m_stPhoneNumInput.dwLen = nLen;

			//m_pBtApp->m_pBtMainPage->refreshPhoneNumInput(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, m_pBtParam->m_stPhoneNumInput.dwLen);
			//m_pBtApp->m_pBtMainPage->DisplayInputDialPhoneName(m_szStrPhoneNumOfOneName_Name);
			m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_FREE,true,true,m_szStrPhoneNumOfOneName_Name,m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
			m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtParam->m_ePhoneStatus);
			setAnalogData(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, PIC_WIDGET_STATUS_DEFAULT);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL, WIDGET_CTRL_ENABLE);
			m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchPageEnglishKeyBoardEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
			if (m_nPhoneBookSearchWordLenUnicode != 0)
			{
				memset(m_szPhoneBookSearchWordUnicode, 0, SIZE_PHONE_BOOK_SEARCH_WORD);
				m_nPhoneBookSearchWordLenUnicode = 0;
				setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);
			}
			
			if (!getLoadPhoneBookStatus())
			{
				if( m_pBtParam->m_nBtLanguageType != 0x00)
					beginAccurateSearchKeyWord();
				else
					beginSearchKeyWord();
			}
			else
			{
				//if(m_pBtParam->m_ePhoneDownloadState  == STATE_PHONE_MSG_DOWNLOADING)
				//{
					refreshLoadPhoneBookStatus(1);
				//}
			}
			
			m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_EGLISH);
		}
		break;
		default:
		break;
	}
}

void CPhoneBookPages::clickSearchPageIsRaelKeyBoardEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			/*<<<<<<<<<<<--------------------[BEN]------------------------------------*/
			/*when you change the different language version pageID, it needs to empty the search input*/
			m_pBtApp->m_pBtPhoneBookPages->clearSearchResultData();	
			memset(m_szPhoneBookSearchWordUnicode,0,sizeof(SIZE_PHONE_BOOK_SEARCH_WORD));
			
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, (u8*)"", 0);
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_KEY_WORD_INPUT, (u8*)"", 0);
			/*------------------------------------END------------------------>>>>>>>>>>>*/
			m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_ISRAEL);
		}
		break;
	default:
		break;
	}
}

wchar_t CPhoneBookPages::getPhoneBookKeyBoardKeyNameById(E_MOUSE_STATUS e, int id)
{
	wchar_t r = L'~';

	//Ó¢ÎÄ
	if (id >= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_A && id <= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_Z)
	{
		int i = id - CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_A;

		switch(e)
		{
		case MOUSE_STATUS_UP:
			{
				static wchar_t szMap[26] = {L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J', L'K', L'L', L'M', L'N', L'O', L'P', 
					L'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X', L'Y', L'Z'};

				r = szMap[i];	
			}
			break;
		case MOUSE_STATUS_TIMER:
			{
				static wchar_t szMap[26] = {L'@', L':', L'"', L'&', L'3', L'*', L'-', L'+', L'8', L'=', L'(', L')', L'/', L';', L'9', L'0', 
					L'1', L'4', L'#', L'5', L'7', L'\'', L'2', L'$', L'6', L'_'};

				r = szMap[i];	
			}
			break;
		default:
			break;
		}
	}
	else if(id == CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_BLANK || id == CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_BLANK)
	{
		switch(e)
		{
		case MOUSE_STATUS_UP:
			{
				r = (wchar_t)L' ';
			}
			break;
		default:
			break;
		}
	}

	//ÒÔÉ«ÁÐ
	if (id >= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_1 && id <= CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_31)
	{
		int i = id - CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_HEBREW_1;

		switch(e)
		{
		case MOUSE_STATUS_UP:
			{
				static wchar_t szMap[32] = {L'×§', L'×š', L'×', L'×', L'×', L'×', L'×', L'×€', L'×©', L'×', L'×', L'×', L'×¢', L'×', L'×', L'×', 
					L'×', L'×£', L'×', L'×¡', L'×', L'×', L'× ', L'×', L'×Š', L'×ª', L'×¥', L'?', L'?', L'?', L'×³', L'?'};
				r = szMap[i];	
			}
			break;
		case MOUSE_STATUS_TIMER:
			{
				static wchar_t szMap[32] = {L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'@', L'#', L'&', L'*', L',', L'.', L'?', L'(', 
					L')', L'0', L'_', L'$', L'"', L':', L';', L'+', L'-', L'=', L'/', L'?', L'?', L'?', L'1', L'?'};
				r = szMap[i];	
			}
			break;
		default:
			break;
		}	
	}

	//°¡À­²®
	if ((id >= CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_1) && (id <= CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_3_9))
	{
		int i = id - CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_1;
		
		switch (e)
		{
		case MOUSE_STATUS_UP:
			{
				static wchar_t szMap[31] = {L'\u0636', L'\u0635', L'\u062b', L'\u0642', L'\u0641', L'\u063a', L'\u0639', L'\u0665', L'\u062e', L'\u062d', L'\u062c', 
					L'\u0634', L'\u0633', L'\u064a', L'\u0628', L'\u0644', L'\u0627', L'\u062a', L'\u0646', L'\u0645', L'\u0643', L'\u0637', 
					L'\u0630', L'\u0621', L'\u0631', L'\u0649', L'\u0629', L'\u0648', L'\u0632', L'\u0638', L'\u062f'};

				r = szMap[i];	
			}
			break;
		case MOUSE_STATUS_TIMER:
			{
				static wchar_t szMap[31] = {L'1',L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0',L'?', 
					L'@', L'#', L'&', L'*',  L',', L'.', L'?', L'(', L')',L'?',L'?',
					L'_', L'$', L'"', L':', L';', L'+', L'-', L'=', L'/'};
			
				if ((id==CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_1_11) || (id ==CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_10) \
					|| (id==CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_ARAB_2_11))	
				{
					LOGD("[%s]  LINE = [%d]", __FUNCTION__,  __LINE__);
					r = 0;
				}
				else
				{
					r = szMap[i];	
				}
			}
			break;
		default:
			break;
		}
	}
	//¶íÂÞË¹
	if ((id >= CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_1) && (id <= CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_9))
	{
		int i = id - CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_1;
		switch (e)
		{
		case MOUSE_STATUS_UP:
			{												
				static wchar_t szMap[31] = {L'\u0446', L'\u0443', L'\u043a', L'\u0435', L'\u043d', L'\u0433', L'\u0448', L'\u0449', L'\u0437', L'\u0445', L'\u044a',
					L'\u0444', L'\u044b', L'\u0432', L'\u0430', L'\u043f', L'\u0440', L'\u043e', L'\u043b', L'\u0434', L'\u0436', L'\u044d',
					L'\u044f', L'\u0447', L'\u0441', L'\u043c', L'\u0438', L'\u0442', L'\u044c', L'\u0431', L'\u044e'};

				r = szMap[i];	
			}

			break;
		case MOUSE_STATUS_TIMER:
			{
				static wchar_t szMap[12] = {L'1',L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0',L'\u0439',L'\u0451'};
				if ((id>=CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_1) && (id <=CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_2_10))	
				{
					r = szMap[i-11];
				}
				else if (id==CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_3_5)
				{
					r = szMap[10];
				}
				else if (id == CONTROLID_BLUETOOTH_AUDIOVOX_KDYBOORD_RUSSIA_1_4)
				{
					r = szMap[11];
				}
				else
				{
					r = 0;	
				}
			}
			break;
		default:
			break;
		}
	}
	
	LOGD("[%s]  r = [0x%x], id = [0x%x]", __FUNCTION__,  r, id);

	return r;
}

void CPhoneBookPages::beginSearchKeyWord()
{
	LOGD("[%s] phone num has [%d]", __FUNCTION__,  m_mapPhoneNumUserInfo.size());

	clearSearchResult();

	u8 szSearchWordUtf8[SIZE_PHONE_BOOK_SEARCH_WORD] = {0};
	u8 szSearchWordAnsi[SIZE_PHONE_BOOK_SEARCH_WORD] = {0};
	int nLenUtf8 = ucs2_2_utf8(m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode, szSearchWordUtf8, sizeof(szSearchWordUtf8));

	int nLenAnsi = 0;
	int CurPageID = 0;
	int paramLen=0;
	m_pBtModule->getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,(u8*)&paramLen);
	if(CurPageID != PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_ISRAEL){
		nLenAnsi = ucs2_2_ansiJustForSearchKeyWord(m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode, szSearchWordAnsi, sizeof(szSearchWordAnsi));
	}

	if (getLoadPhoneBookStatus())
		return;

	map<int, ST_PhoneBookUserInfo* >::iterator itFrom = m_mapPhoneNumUserInfo.begin();
	map<int, ST_PhoneBookUserInfo* >::iterator itTo = m_mapPhoneNumUserInfo.end();
	for (map<int, ST_PhoneBookUserInfo* >::iterator it = itFrom; it != itTo; it++)
	{
		
		int r = 0;
		r = findSubString(szSearchWordUtf8, nLenUtf8, (u8*)it->second->szUserNameUtf8, strlen(it->second->szUserNameUtf8));

		if (r != -1)
		{
			ST_PhoneBookUserInfo stNode = *(it->second);
			getOneNameForMoreNum_List_New(stNode);
		}
		else
		{
			int nMatchWeight = 0;
			char *pName = (char*)it->second->szUserNameUnicode;
			
			if (nLenUtf8 != 0 && nLenAnsi == 0)//ËµÃ÷Ã»ÓÐÓ¢ÎÄ×ÖÄž
			{
				r = -1;
			}
			else
			{
				r = findSubStringInUnicodePhoneBook(szSearchWordAnsi, nLenAnsi, (u8*)pName, 2 * getLengthOfUnicodeString(pName, FILE_PHONECMD_MAX_LEN), nMatchWeight);
			}
			
			if (r != -1)
			{
				ST_PhoneBookUserInfo stNode = *(it->second);
				stNode.nUserNameMatchWeight = nMatchWeight;
				getOneNameForMoreNum_List_New(stNode);
			}
		}
		
	}
	m_listPhoneNumUserInfoHaveSelected.sort();
	refreshSearchPageSearchResult(0);
}

void CPhoneBookPages::clearPhoneBook(void)
{
	map<int, ST_PhoneBookUserInfo* >::iterator itFrom;
	map<int, ST_PhoneBookUserInfo* >::iterator itTo;

	if (!m_mapPhoneNumUserInfo.empty())
	{
		itFrom = m_mapPhoneNumUserInfo.begin();
		itTo = m_mapPhoneNumUserInfo.end();
		for (map<int, ST_PhoneBookUserInfo* >::iterator it = itFrom; it != itTo; it++)
		{
			delete it->second;
		}
		m_mapPhoneNumUserInfo.erase(itFrom, itTo);	//Ê¹ÓÃÇ°Çå¿Õ
	}
}

void CPhoneBookPages::clearSearchResult(void)
{
	if (!m_listPhoneNumUserInfoHaveSelected.empty())
	{
		m_listPhoneNumUserInfoHaveSelected.clear();
	}
}

void CPhoneBookPages::refreshSearchPageSearchResult(int nFrom)
{
    LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);
	   
	setUpdateUI(false);

	int nBrowseFileNum = m_listPhoneNumUserInfoHaveSelected.size();

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_RESULT_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;

	m_nSearchPageBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_PhoneBookUserInfo>::iterator itFrom = m_listPhoneNumUserInfoHaveSelected.begin();
	list<ST_PhoneBookUserInfo>::iterator itTo = m_listPhoneNumUserInfoHaveSelected.end();
	list<ST_PhoneBookUserInfo>::iterator it;
	//ÕÒ¶ÔÓŠµÚÒ»ÏîÒªÏÔÊŸ
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	//Ë¢ SEARCH_LIST_DISPLAY_NUM Ïî
	for (i = nFrom; i < nFrom + SEARCH_RESULT_LIST_DISPLAY_NUM; i++)
	{     
	
		if (j >= nFrom && it != itTo)
		{
			char *pData = (char*)it->szUserNameUtf8;
			int len = strlen(pData);
			char *pNumb = (char*)it->szstPhoneNumInfo[0].szPhoneNumUtf8;
			int numLen = strlen(pNumb);

			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1 + k, (u8*)pData, len);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1+k,true);
			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NUM_1 + k, (u8*)pNumb, numLen);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NUM_1+k,true);

			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1 + k, (u8*)pData, len);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1+k,true);
			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NUM_1 + k, (u8*)pNumb, numLen);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NUM_1+k,true);
			it++, j++;
		}
		else
		{
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1 + k, (u8*)"", 0);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1+k,false);
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NUM_1 + k, (u8*)"", 0);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NUM_1+k,false);

			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1 + k, (u8*)"", 0);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1+k,false);
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NUM_1 + k, (u8*)"", 0);
			setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NUM_1+k,false);
		}
		
		k++;
	}

	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_1, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_2, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_DISPLAY_NAME_3, 0);

	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_1, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_2, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_DISPLAY_NAME_3, 0);
	
	setUpdateUI(true);
	
}

void CPhoneBookPages::refreshSearchResultPageSearchResult(int nFrom)
{
	setUpdateUI(false);

	int nBrowseFileNum = m_listPhoneNumUserInfoHaveSelected.size();

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_RESULT_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;

	m_nSearchResultPageBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_PhoneBookUserInfo>::iterator itFrom = m_listPhoneNumUserInfoHaveSelected.begin();
	list<ST_PhoneBookUserInfo>::iterator itTo = m_listPhoneNumUserInfoHaveSelected.end();
	list<ST_PhoneBookUserInfo>::iterator it;
	//ÕÒ¶ÔÓŠµÚÒ»ÏîÒªÏÔÊŸ
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	//Ë¢ SEARCH_LIST_DISPLAY_NUM Ïî
	for (i = nFrom; i < nFrom + SEARCH_RESULT_LIST_DISPLAY_NUM; i++)
	{
		if (j >= nFrom && it != itTo)
		{
			char *pData = (char*)it->szUserNameUtf8;
			int len = strlen(pData);

			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 + k, (u8*)pData, len);
			//setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1+k,true);
			it++, j++;
		}
		else
		{
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 + k, (u8*)"", 0);
			//setCtrlEnable(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1+k,false);
		}

		k++;
	}

	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_2, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_3, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_4, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_5, 0);

	if (m_nSearchResultPageActiveIndex >= m_nSearchResultPageBrowseFrom && m_nSearchResultPageActiveIndex < m_nSearchResultPageBrowseFrom + SEARCH_RESULT_LIST_DISPLAY_NUM)
	{
		int n = m_nSearchResultPageActiveIndex % SEARCH_RESULT_LIST_DISPLAY_NUM;
		setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 + n, 1);
	}

	setUpdateUI(true);
}

void CPhoneBookPages::refreshLoadPhoneBookStatus(u32 id)
{
	LOGD("[%s] id [%x]", __FUNCTION__,  id);

	if (id != 0)
	{
		m_bIsLoadingPhoneBook = true;
	}
	else
	{
		m_bIsLoadingPhoneBook = false;
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, (u8*)"", 0);
	}
}

void CPhoneBookPages::getAllPhoneBookLoadDone(void)
{
	LOGD("[%s]", __FUNCTION__);
	createSearchPhoneBook();

	if(m_pBtParam->m_nBtLanguageType != 0x00)
		beginAccurateSearchKeyWord();
	else
		beginSearchKeyWord();
}

inline void getNext(const char *p, int len, int *next) 
{
	int i = 0, j = -1;
	next[0] = -1;
	while(i != len)
	{
		if(j == -1 || p[i] == p[j])
			next[++i] = ++j;
		else
			j = next[j];
	}
}

int CPhoneBookPages::findSubString(u8 *pShortString, int nShortStringLen, u8 *pLongString, int nLongStringLen)
{
	if (nShortStringLen <= 0)
	{
		return 0;
	}

	int szMapNext[128] = {0};
	getNext((char*)pLongString, nShortStringLen, szMapNext);

	int i = 0, j = 0;

	while(i != nLongStringLen && j != nShortStringLen)
	{
		bool bMatchOk = false;

		if (j == -1)
			bMatchOk = true;
		else
		{
			if (pLongString[i] == pShortString[j])
				bMatchOk = true;
			else
			{
				if (pLongString[i] >= 'a' && pLongString[i] <= 'z' && ((pLongString[i] - 32) == pShortString[j]))
					bMatchOk = true;
			}
		}

		if(bMatchOk)
			i++,j++;
		else
			j = szMapNext[j];

		if(nShortStringLen == j)
			return i - j;
	}
	//LOGD("[%s] nLongStringLen = [%d], nShortStringLen = [%d]", __FUNCTION__,  nLongStringLen, nShortStringLen);

	//////////////Way 2////////////////////////////////////////////////
	/*
	int i = 0, j = 0;

	for (i = 0; i <= nLongStringLen - nShortStringLen; i++)
	{
		for (j = 0; j < nShortStringLen; j++)
		{
			int k = i + j;
			if (pLongString[k] >= 'a' && pLongString[k] <= 'z' && ((pLongString[k] - 32) == pShortString[j]))
				continue;
			else
			{
				if (pLongString[k] != pShortString[j])
					break;
			}
		}
		if (j == nShortStringLen)
			return i;
	}
	*/
	//////////////////////////////////////////////////////////////////////////

	return -1;
}

int CPhoneBookPages::findSubStringInPinyin(u8 *pShortString, int nShortStringLen, u8 *pLongString, int nLongStringLen)
{
	if (nShortStringLen <= 0)
	{
		return 0;
	}

	int i = 0, j = 0;
	char f = pShortString[j];
	
	for (i = 0; i < nLongStringLen; i++)
	{
		if (pLongString[i] == f)
		{
			j++;

			if (j >= nShortStringLen)
			{
				return 0;
			}

			f = pShortString[j];
		}
	}

	return -1;
}

int CPhoneBookPages::findSubStringInUnicodePhoneBook(u8 *pShortString, int nShortStringLen, u8 *pLongString, int nLongStringLen, int &nMatchWeight)
{
	if (nShortStringLen <= 0)
	{
		return 0;
	}

	int dwUnicodeBufLen = nLongStringLen / 2;
	
	int i = 0;
	int j = 0;
	for (i = 0; i < dwUnicodeBufLen; i++)
	{
		int oneWord = 0;
		memcpy(&oneWord, pLongString + i * 2, 2);

		if (oneWord > 0 && oneWord <= 127)//±ê×Œ×Ö·ûŒ¯
		{
			if (pShortString[j] == oneWord)
			{
				nMatchWeight += getHanZiMatchWeight(i);
				j++;
			}
		}
		else if (oneWord >= FIRST_HANZI_UNICODE && oneWord <= LAST_HANZI_UNICODE)//ºº×Ö
		{
			oneWord -= FIRST_HANZI_UNICODE;
			char const *pHanZiPinyin = g_szMapUnicode2Pinyin[oneWord];

			int nLenHanZiPinyin = strlen(pHanZiPinyin);
			u8 szOnePinyin[128] = {0};
			int m = 0, n = 0;
			int nMatchLevel = 0;
			int t = j;

			for (m = 0; m < nLenHanZiPinyin; m++)
			{
				bool bOneWordHave = false;

				if (pHanZiPinyin[m] >= 'a' && pHanZiPinyin[m] <= 'z')
				{
					szOnePinyin[n] = pHanZiPinyin[m];
					n++;
				}
				else
				{
					if (n > 0)//Éú²úÁËÒ»žöÆŽÒô
					{
						bOneWordHave = true;
					}
				}

				if (m == nLenHanZiPinyin - 1 && n > 0)//Éú²úÁËÒ»žöÆŽÒô
				{
					bOneWordHave = true;
				}

				if (bOneWordHave)
				{
					int k = 0;
					bool bMatch = false;
					j = t;

					for (k = 0; k < n; k++)
					{
						if (k == 0 && pShortString[j] == szOnePinyin[k])//ÆŽÒôÊ××ÖÄž 
						{
							j++;
							bMatch = true;
							continue;
						}

						if (pShortString[j] != szOnePinyin[k])
							break;
						else
							j++;
					}

					if (k != n && bMatch)//Ê××ÖÄžÆ¥Åäµ«²»È«Æ¥Åä
					{
						if (nMatchLevel < 1)
						{
							nMatchLevel = 1;
						}
					}

					if (k == n)//È«Æ¥Åä
					{
						nMatchLevel = 2;
						break;
					}

					n = 0;
					memset(szOnePinyin, 0, sizeof(szOnePinyin));
				}//if (bOneWordHave)
			}//for (m = 0; m < nLenHanZiPinyin; m++)

			if (nMatchLevel == 1)//Ö»ÊÇÊ××ÖÄžÆ¥Åä
				j = t + 1;

			if (nMatchLevel == 1 || nMatchLevel == 2)//Ê××ÖÄžÆ¥Åä»òÕßÈ«Æ¥Åä
			{
				nMatchWeight += getHanZiMatchWeight(i);
			}
			
		}//else if (oneWord >= FIRST_HANZI_UNICODE && oneWord <= LAST_HANZI_UNICODE)//ºº×Ö

		if (j >= nShortStringLen)//ÕÒµœ
		{
			return 0;
		}
	}

	return -1;
}

bool CPhoneBookPages::getLoadPhoneBookStatus(void)
{
	LOGD("[%s] loading ? [%s]", __FUNCTION__,  m_bIsLoadingPhoneBook ? "Yes" : "No");

	return m_bIsLoadingPhoneBook;
}

bool CPhoneBookPages::isSearchKeyWordEmpty()
{
	bool bRet = false;

	if (m_nPhoneBookSearchWordLenUnicode == 0)
		bRet = true;

	LOGD("[%s] [%s]", __FUNCTION__,  bRet ? "Yes" : "No");

	return bRet;
}

void CPhoneBookPages::createSearchPhoneBook(void)
{
	if (NULL ==m_pBtParam)
		{
			LOGD("[%s] list come in",__FUNCTION__);
			return;
		}

	//×ª»»³É×ÔŒºµÄ map
	//LOGD("[%s] list begin",__FUNCTION__);
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itVecFrom = m_pBtParam->m_listPhoneBook.begin();
	//LOGD("[%s] list mid ",__FUNCTION__);
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itVecTo = m_pBtParam->m_listPhoneBook.end();
	//LOGD("[%s] list end ",__FUNCTION__);
	int i = 1;
	
	for (list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itVec = itVecFrom; itVec != itVecTo; itVec++)
	{       

		//LOGD("[%s] i = [%d] start ",__FUNCTION__, i);
		int j = 0;
		int flag=-1;
		int n = 1;
		
        char oldUserName[128]={0};
	    ST_PhoneBookUserInfo *pPhoneBookUserInfo = new ST_PhoneBookUserInfo();
		memset(pPhoneBookUserInfo, 0, sizeof(ST_PhoneBookUserInfo));
		ST_PhoneBookRankUserInfo *pPhoneBookRankUserInfo = new ST_PhoneBookRankUserInfo();
		memset(pPhoneBookRankUserInfo, 0, sizeof(ST_PhoneBookRankUserInfo));
		
		memcpy(pPhoneBookUserInfo->szUserNameUtf8, itVec->szUserName, strlen(itVec->szUserName));
		utf8_2_ucs2((u8*)pPhoneBookUserInfo->szUserNameUtf8, strlen(pPhoneBookUserInfo->szUserNameUtf8), (u8*)pPhoneBookUserInfo->szUserNameUnicode, sizeof(pPhoneBookUserInfo->szUserNameUnicode));

		memcpy(pPhoneBookRankUserInfo->szUserNameUtf8, itVec->szUserName, strlen(itVec->szUserName));
		utf8_2_ucs2((u8*)pPhoneBookRankUserInfo->szUserNameUtf8, strlen(pPhoneBookRankUserInfo->szUserNameUtf8), (u8*)pPhoneBookRankUserInfo->szUserNameUnicode, sizeof(pPhoneBookRankUserInfo->szUserNameUnicode));
	
		//LOGD("[%s] [%s]",__FUNCTION__,pPhoneBookUserInfo->szUserNameUtf8);
		pPhoneBookUserInfo->nPhoneNumInfoCount =1;
        memcpy(pPhoneBookUserInfo->szstPhoneNumInfo[0].szPhoneNumUtf8, itVec->szUserNo, strlen(itVec->szUserNo));
		m_mapPhoneNumUserInfo[i] = pPhoneBookUserInfo;
		
		//BC08 Rank page map
		int key;			
		UnicoTopinyin((u8*)pPhoneBookRankUserInfo->szUserNameUnicode,&key,m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage);
		pPhoneBookRankUserInfo->key = key;	
		pPhoneBookRankUserInfo->nPhoneNumInfoCount = 1;
		memcpy(pPhoneBookRankUserInfo->szstPhoneNumInfo[0].szPhoneNumUtf8, itVec->szUserNo, strlen(itVec->szUserNo));
		m_mapPhoneNumRankUserInfo[i] = pPhoneBookRankUserInfo;

		flag=i;
		i++;

		//LOGD("[%s] i = [%d] end ",__FUNCTION__, i);
	}
	
}

int CPhoneBookPages::ucs2_2_ansiJustForSearchKeyWord(u8 *pSrc, int nSrcLen, u8 *pDst, int nDstLen)
{
	int i = 0, j = 0;
	for (i = 0; i < nSrcLen; i += 2)
	{
		if (0 == pSrc[i + 1])
		{
			u8 r = pSrc[i];

			if (r >= 'A' && r <= 'Z')
				r += 32;

			pDst[j] = r;
			j++;
		}
	}

	return j;
}

int CPhoneBookPages::getLengthOfUnicodeString(char *p, int len)
{
	int nRet = 0;

	int i;
	int j = len >> 1;
	for (i = 0; i <= j; i++)
	{
		if (p[i * 2] != 0)
		{
			nRet++;
		}
		else
			break;
	}
	
	return nRet;
}

int CPhoneBookPages::getHanZiMatchWeight(int i)
{
	int nMatchWeight = 0;
	
	if (i <= 21)
	{
		nMatchWeight = (HAN_ZI_MATCH_WEIGHT >> i);
	}
	else
	{
		nMatchWeight = 1;
	}

	return nMatchWeight;
}

void CPhoneBookPages::showLoadingPhoneBookTips(u32 strTips)
{
    if(strTips != 0)
    {
        setStringById(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, STRINGID_BT__DEVICE_CONTACTS_LOADING);
		LOGD("[%s]    SHOW",__FUNCTION__);
	}
	else
	{
	    setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, (u8*)"", 0);
		LOGD("[%s]    HID",__FUNCTION__);
	}
}



void CPhoneBookPages::createSearchPhoneBook2(void)
{
	if (NULL ==m_pBtParam)
		{
			LOGD("[%s] list come in",__FUNCTION__);
			return;
		}

	//×ª»»³É×ÔŒºµÄ map
	//LOGD("[%s] list begin",__FUNCTION__);
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itVecFrom = m_pBtParam->m_listPhoneBook_BC8.begin();
	//LOGD("[%s] list mid ",__FUNCTION__);
	list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itVecTo = m_pBtParam->m_listPhoneBook_BC8.end();
	//LOGD("[%s] list end ",__FUNCTION__);
	int i = 1;
	
	for (list<ST_PHONE_BOOK_ONE_USER_INFO>::iterator itVec = itVecFrom; itVec != itVecTo; itVec++)
	{       

		//LOGD("[%s] i = [%d] start ",__FUNCTION__, i);
		int j = 0;
		int flag=-1;
		int n = 1;
		
        char oldUserName[128]={0};
	    ST_PhoneBookUserInfo *pPhoneBookUserInfo = new ST_PhoneBookUserInfo();
		memset(pPhoneBookUserInfo, 0, sizeof(ST_PhoneBookUserInfo));

		memcpy(pPhoneBookUserInfo->szUserNameUtf8, itVec->szUserName, strlen(itVec->szUserName));
		utf8_2_ucs2((u8*)pPhoneBookUserInfo->szUserNameUtf8, strlen(pPhoneBookUserInfo->szUserNameUtf8), (u8*)pPhoneBookUserInfo->szUserNameUnicode, sizeof(pPhoneBookUserInfo->szUserNameUnicode));
		//LOGD("[%s] [%s]",__FUNCTION__,pPhoneBookUserInfo->szUserNameUtf8);
		
		pPhoneBookUserInfo->nPhoneNumInfoCount =1;
        memcpy(pPhoneBookUserInfo->szstPhoneNumInfo[0].szPhoneNumUtf8, itVec->szUserNo, strlen(itVec->szUserNo));
		m_mapPhoneNumUserInfo[i] = pPhoneBookUserInfo;
		flag=i;
		i++;

		//LOGD("[%s] i = [%d] end ",__FUNCTION__, i);
	}
	

}

void CPhoneBookPages::UnicoTopinyin(u8 *pLongString,int *cFirst,E_KEY_BOARD_LANGUAGE curLanguage)
{
	int oneWord = 0;
	memcpy(&oneWord, pLongString, 2);
	
	if ((oneWord >= FIRST_SPECIAL_UNICODE && oneWord <= LAST_SPECIAL_UNICODE) || (oneWord >= FIRST_SPECIAL1_UNICODE && 
	oneWord <= LAST_SPECIAL1_UNICODE) || (oneWord >= FIRST_SPECIAL2_UNICODE && oneWord <= LAST_SPECIAL2_UNICODE) || 
	(oneWord >= FIRST_SPECIAL3_UNICODE && oneWord <= LAST_SPECIAL3_UNICODE))						//Special characters
	{
		*cFirst = (char)pLongString[0] + 7000;
	}
	else if (oneWord >= FIRST_NUMBER_UNICODE && oneWord <= LAST_NUMBER_UNICODE)													//NUMBER	
	{
		if(curLanguage == KEY_BOARD_LANGUAGE_ENGLISH || 
			curLanguage == KEY_BOARD_LANGUAGE_RUSSIA ||
			curLanguage == KEY_BOARD_LANGUAGE_ARAB ||
			curLanguage == KEY_BOARD_LANGUAGE_ISRAEL)
		{
			*cFirst = (int)pLongString[0] + 3000;
		}
		
	}
	
	else if ((oneWord >= FIRST_ENGLISH_UNICODE && oneWord<= LAST_ENGLISH_UNICODE) || 
		(oneWord >= FIRST_ENGLISH1_UNICODE && oneWord <= LAST_ENGLISH1_UNICODE))					//ENGLISH	
	{
		if(curLanguage == KEY_BOARD_LANGUAGE_ENGLISH)
		{
			*cFirst = (int)pLongString[0] + 1000;
		}
		else if(curLanguage == KEY_BOARD_LANGUAGE_RUSSIA ||
			curLanguage == KEY_BOARD_LANGUAGE_ARAB ||
			curLanguage == KEY_BOARD_LANGUAGE_ISRAEL)
			{
				*cFirst = (int)pLongString[0] + 2000;
			}
		if(oneWord >= FIRST_ENGLISH_UNICODE && oneWord<= LAST_ENGLISH_UNICODE )
			*cFirst = *cFirst + 32;
	}
	
	else if (oneWord >= FIRST_HANZI_UNICODE && oneWord <= LAST_HANZI_UNICODE)				//HANZI	
	{
			oneWord -= FIRST_HANZI_UNICODE;
			char const *pHanZiPinyin = g_szMapUnicode2Pinyin[oneWord];
			if(curLanguage == KEY_BOARD_LANGUAGE_ENGLISH)
			{
				*cFirst = (char)pHanZiPinyin[0] + 1000;
			}
			else if(curLanguage == KEY_BOARD_LANGUAGE_RUSSIA ||
				curLanguage == KEY_BOARD_LANGUAGE_ARAB ||
				curLanguage == KEY_BOARD_LANGUAGE_ISRAEL)
			{
				*cFirst = (int)pLongString[0] + 6000;
			}
	}
	
	else if(oneWord >=FIRST_HEBREW_UNICODE && oneWord<=LAST_HEBREW_UNICODE)					//HEBREW	
	{
		int len = sizeof(pLongString);
		if(curLanguage == KEY_BOARD_LANGUAGE_ENGLISH ||
			curLanguage == KEY_BOARD_LANGUAGE_ARAB)
			{
				*cFirst = (int)pLongString[0] + 5000;
			}
		else if(curLanguage == KEY_BOARD_LANGUAGE_RUSSIA)
			{
				*cFirst = (int)pLongString[0] + 4000;
			}
		else if(curLanguage == KEY_BOARD_LANGUAGE_ISRAEL)
			{
				*cFirst = (int)pLongString[0] +1000;
			}
	}
	
	else if(oneWord >=FIRST_RUSSIAN_UNICODE && oneWord<=LAST_RUSSIAN_UNICODE)				//RUSSIAN		
	{
		int len = sizeof(pLongString);
		if(curLanguage == KEY_BOARD_LANGUAGE_ENGLISH ||
			curLanguage == KEY_BOARD_LANGUAGE_ARAB || 
			curLanguage == KEY_BOARD_LANGUAGE_ISRAEL)
		{
			*cFirst = (int)pLongString[0] + 4000;
			
		}
		else if(curLanguage == KEY_BOARD_LANGUAGE_RUSSIA)
		{
			*cFirst = (int)pLongString[0] + 1000;
		}
	}
	
	else if((oneWord >= FIRST_ARABIC_UNICODE && oneWord <= LAST_ARABIC_UNICODE) || 						
		(oneWord >= FIRST_ARABIC1_UNICODE && oneWord <= LAST_ARABIC1_UNICODE))					//ARABIC
	{																				
		int len = sizeof(pLongString);
		if(curLanguage == KEY_BOARD_LANGUAGE_ENGLISH)
		{
			*cFirst = (int)pLongString[0] + 6000;
		}
		else if(curLanguage == KEY_BOARD_LANGUAGE_RUSSIA ||
			curLanguage == KEY_BOARD_LANGUAGE_ISRAEL)
			{
				*cFirst = (int)pLongString[0] + 5000;
			}
		else if(curLanguage == KEY_BOARD_LANGUAGE_ARAB)
			{
				*cFirst = (int)pLongString[0] + 1000;
			}
	}
}


bool CPhoneBookPages::phoneBookRankSearchPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	bool bRet = true;

	switch(id)
	{
		//English Page
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_TO_BOOK:
			clickPhoneBookRankPageEntrance(e);
		break;

		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_PREV:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_PREV:
			clickSearchPageRankPrePage(e);
		break;
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_NEXT:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_NEXT:
			clickSearchPageRankNextPage(e);
		break;

		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_LEFT:	
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_RIGHT:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_LEFT:		
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_RIGHT:
			if(e == MOUSE_STATUS_UP)
				clickPhoneBookRankPageLeftOrRight(id);
		break;

		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_LANGUAGE:
			clickSearchRankPageEnglishKey(e);
		break;

		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1:		
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_2:		
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_3:		
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_4:		
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_5:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1:		
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_2:		
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_3:		
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_4:		
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_5:
			clickSearchRankPageSearchResultItem(id,e);
		break;

		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A:			
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +1:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +2:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +3:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +4:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +5:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +6:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +7:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +8:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +9:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +10:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +11:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +12:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +13:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +14:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +15:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +16:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +17:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +18:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +19:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +20:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +21:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +22:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +23:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +24:
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_Z:					
		case CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_OTHER:
		//ISR
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1:				
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +1:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +2:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +3:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +4:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +5:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +6:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +7:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +8:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +9:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +10:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +11:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +12:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +13:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +14:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +15:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +16:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +17:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +18:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +19:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +20:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +21:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +22:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +23:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +24:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +25:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_27:
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_OTHER:
			clickSearchPageRankKeyPanel(id,e);
		break;
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_TO_BOOK:
			clickPhoneBookRankPageEntrance(e);
		break;
		case CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_LANGUAGE:
			clickSearchRankPageIsraelKey(e);
		break;
		default:
		bRet = false;
		break;
	}
	return bRet;
}


void CPhoneBookPages::clickPhoneBookRankPageEntrance(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
				m_pBtApp->m_pBtPhoneBookPages->clearSearchResultData();	

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
		}
		break;
		default:break;
	}
}


void CPhoneBookPages::clickPhoneBookPageToRankPage(E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_UP:
		{
				clearRankSearchResultData();	
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
						{
							int nAll = CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_OTHER - CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A + 1;
							for(int i = 0 ;i < nAll; i++)
							{ 
								setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +i,0);
							}
							m_pBtModule->setPage(PAGE_BLUETOOTH_PHONE_BOOK_ENGLISH_RANK_PAGE);
							initsetEnglishShowOrHide();
			   			}
						break;
					case KEY_BOARD_LANGUAGE_ISRAEL:
					case KEY_BOARD_LANGUAGE_ARAB:
					case KEY_BOARD_LANGUAGE_RUSSIA:
						{							
							int nAllI = CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_OTHER - CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 + 1;
							for(int i = 0 ;i < nAllI; i++)
							{ 
								setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +i,0); 
							}
							m_pBtModule->setPage(PAGE_BLUETOOTH_PHONE_BOOK_ISRAEL_RANK_PAGE);
							initsetIsraelShowOrHide();
						}
						break;
					default:break;
			   	}  
		}
		break;
		default:break;
	}
}

void CPhoneBookPages::clearRankSearchResultData()
{
	while(m_nPhoneBookSearchWordLenUnicode>=2)
	{
		m_szPhoneBookSearchWordUnicode[m_nPhoneBookSearchWordLenUnicode - 1] = 0;
		m_szPhoneBookSearchWordUnicode[m_nPhoneBookSearchWordLenUnicode - 2] = 0;
		m_nPhoneBookSearchWordLenUnicode -= 2;
	}
	setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_DISPLAY, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);
	setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_SEARCH_TWO_KEY_WORD_INPUT, (u8*)m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode);
	beginSearchRankKeyWord();
}

void CPhoneBookPages::clearRankSearchResult(void)
{
	if (!m_listPhoneNumRankUserInfoHaveSelected.empty())
	{
		m_listPhoneNumRankUserInfoHaveSelected.clear();
	}
}
void CPhoneBookPages::beginSearchRankKeyWord()
{
	LOGD("[%s] phone num has [%d]", __FUNCTION__,  m_mapPhoneNumUserInfo.size());
	
	clearRankSearchResult();
	
	int CurPageID = 0;
	int paramLen=0;
	m_pBtModule->getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,(u8*)&paramLen);
	if (getLoadPhoneBookStatus())
		return;
	map<int, ST_PhoneBookRankUserInfo* >::iterator itFrom = m_mapPhoneNumRankUserInfo.begin();
	map<int, ST_PhoneBookRankUserInfo* >::iterator itTo = m_mapPhoneNumRankUserInfo.end();
	for (map<int, ST_PhoneBookRankUserInfo* >::iterator it = itFrom; it != itTo; it++)
	{
		ST_PhoneBookRankUserInfo stNode = *(it->second);
		m_listPhoneNumRankUserInfoHaveSelected.push_back(stNode);
	}
	m_listPhoneNumRankUserInfoHaveSelected.sort();
	refreshSearchPagePhoneRank(0);
}

void CPhoneBookPages::refreshSearchPagePhoneRank(int nFrom)
{
    LOGD("[%s] nFrom:%d",__FUNCTION__,nFrom);
	   
	setUpdateUI(false);

	int nBrowseFileNum = m_listPhoneNumRankUserInfoHaveSelected.size();

	if (nFrom >= nBrowseFileNum)
		nFrom -= SEARCH_RANK_RESULT_LIST_DISPLAY_NUM;

	if (nFrom < 0)
		nFrom = 0;

	m_nSearchRankPageBrowseFrom = nFrom;

	int i = 0, j = 0, k = 0;
	list<ST_PhoneBookRankUserInfo>::iterator itFrom = m_listPhoneNumRankUserInfoHaveSelected.begin();
	list<ST_PhoneBookRankUserInfo>::iterator itTo = m_listPhoneNumRankUserInfoHaveSelected.end();
	list<ST_PhoneBookRankUserInfo>::iterator it;
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	
	for (i = nFrom; i < nFrom + SEARCH_RANK_RESULT_LIST_DISPLAY_NUM; i++)
	{     
	
		if (j >= nFrom && it != itTo)
		{
			char *pData = (char*)it->szUserNameUtf8;
			char *pNumb = (char*)it->szstPhoneNumInfo[0].szPhoneNumUtf8;
			int len = strlen(pData);
			int numLen = strlen(pNumb);

			setUtf8SerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1 + k, (u8*)pData, len);
			setCtrlEnable(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1+k,true);
			setUtf8SerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_1 + k, (u8*)pNumb, numLen);
			setCtrlEnable(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_1+k,true);
			
			setUtf8SerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1 + k, (u8*)pData, len);
			setCtrlEnable(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1+k,true);
			setUtf8SerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_1 + k, (u8*)pNumb, numLen);
			setCtrlEnable(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_1+k,true);
			it++, j++;
		}
		else
		{
			setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1 + k, (u8*)"", 0);
			setCtrlEnable(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1+k,false);
			setSerialData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_1 + k, (u8*)"", 0);
			setCtrlEnable(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NUM_1+k,false);
			
			setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1 + k, (u8*)"", 0);
			setCtrlEnable(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1+k,false);
			setSerialData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_1 + k, (u8*)"", 0);
			setCtrlEnable(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NUM_1+k,false);
		}
		
		k++;
	}

	setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1, 0);
	setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_2, 0);
	setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_3, 0);
	setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_4, 0);
	setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_5, 0);

	setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1, 0);
	setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_2, 0);
	setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_3, 0);
	setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_4, 0);
	setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_5, 0);
	
	setUpdateUI(true);
	
}

void CPhoneBookPages::clickSearchPageRankPrePage(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nPreStartBrowse = -1;
			nPreStartBrowse = m_nSearchRankPageBrowseFrom;
			m_nSearchRankPageBrowseFrom = max(0, m_nSearchRankPageBrowseFrom - SEARCH_RANK_RESULT_LIST_DISPLAY_NUM);
			if (nPreStartBrowse == m_nSearchRankPageBrowseFrom)
				return;
			refreshSearchPagePhoneRank(m_nSearchRankPageBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchPageRankNextPage(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_nSearchRankPageBrowseFrom;

			m_nSearchRankPageBrowseFrom += SEARCH_RANK_RESULT_LIST_DISPLAY_NUM;
			if (m_nSearchRankPageBrowseFrom >= (int)m_listPhoneNumRankUserInfoHaveSelected.size())
				m_nSearchRankPageBrowseFrom -= SEARCH_RANK_RESULT_LIST_DISPLAY_NUM;
			if(nNextStartBrowse == m_nSearchRankPageBrowseFrom)
				return;

			refreshSearchPagePhoneRank(m_nSearchRankPageBrowseFrom);
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickPhoneBookRankPageLeftOrRight(u32 id)
{
	int prepage = 0;
	prepage = m_nSearchRankleftOrRight;
	if(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_LEFT == id || CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_LEFT == id)
		m_nSearchRankleftOrRight--;
	else if(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_RIGHT == id || CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_RIGHT == id)
			m_nSearchRankleftOrRight++;
	else if(0 == id)
		m_nSearchRankleftOrRight = 1;
	int fourth = 4, Third =3,Second = 2,First = 1;
	if(m_nSearchRankleftOrRight == 0)
		m_nSearchRankleftOrRight = fourth;
	if(m_nSearchRankleftOrRight== 5)
		m_nSearchRankleftOrRight= First;

	setUpdateUI(false);
	if(PAGE_BLUETOOTH_PHONE_BOOK_ENGLISH_RANK_PAGE == m_pBtModule->getCurPageId())
	{
		setEnglishShowOrHide(m_nSearchRankleftOrRight,1);
		setEnglishShowOrHide(prepage,0);
		
	}
	if(PAGE_BLUETOOTH_PHONE_BOOK_ISRAEL_RANK_PAGE== m_pBtModule->getCurPageId())
	{
		setIsraelShowOrHide(m_nSearchRankleftOrRight,1);
		setIsraelShowOrHide(prepage,0);
	}
	setUpdateUI(true);
}

void CPhoneBookPages::setEnglishShowOrHide(int page,int key)
{
	switch(page)
	{
		case 1:
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A , key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +1, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +2, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +3, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +4, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +5, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +6, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +7, key);
			break;
		case 2:
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +8, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +9, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +10, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +11, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +12, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +13, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +14, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +15, key);
			break;
		case 3:
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +16, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +17, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +18, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +19, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +20, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +21, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +22, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +23, key);
			break;
		case 4:
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +24, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +25, key);
			setVisible(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +26, key);
			break;
		}
}
void CPhoneBookPages::setIsraelShowOrHide(int page,int key)
{
	switch(page)
	{
		case 1:
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +1,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +2,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +3,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +4,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +5,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +6,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +7,key);
			break;
		case 2:
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +8,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +9,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +10,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +11,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +12,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +13,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +14,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +15,key);
			break;
		case 3:
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +16,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +17,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +18,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +19,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +20,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +21,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +22,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +23,key);
			break;
		case 4:
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +24,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +25,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +26,key);
			setVisible(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +27,key);
			break;
	}
}

void CPhoneBookPages::initsetIsraelShowOrHide(void)
{
	setIsraelShowOrHide(1,1);
	setIsraelShowOrHide(2,0);
	setIsraelShowOrHide(3,0);
	setIsraelShowOrHide(4,0);
	m_nSearchRankleftOrRight = 1;
}
void CPhoneBookPages::initsetEnglishShowOrHide(void)
{
	setEnglishShowOrHide(1,1);
	setEnglishShowOrHide(2,0);
	setEnglishShowOrHide(3,0);
	setEnglishShowOrHide(4,0);
	m_nSearchRankleftOrRight = 1;
}


void CPhoneBookPages::clickSearchRankPageEnglishKey(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{	
			clearRankSearchResultData();
			m_pBtModule->setPage(PAGE_BLUETOOTH_PHONE_BOOK_ISRAEL_RANK_PAGE);

			int nAll = CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_OTHER - CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A + 1;
			for(int i = 0 ;i < nAll; i++)
			{	
				setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +i,0);
			}
			initsetEnglishShowOrHide();
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchRankPageIsraelKey(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			clearRankSearchResultData();
			m_pBtModule->setPage(PAGE_BLUETOOTH_PHONE_BOOK_ENGLISH_RANK_PAGE);

			int nAll = CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_OTHER - CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 + 1;
			for(int i = 0 ;i < nAll; i++)
			{	
				setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +i,0);
			}
			initsetIsraelShowOrHide();
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchRankPageSearchResultItem(u32 id, E_MOUSE_STATUS e)
{
	LOGD("[%s] nFrom:%x",__FUNCTION__,id);
	if(m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_IN || m_pBtParam->m_ePhoneStatus == BT_PHONE_STATUS_CALL_OUT)
		return;
	if(m_pBtParam->nCallCount == CALLING_COUNT_MUTIL)
		return;

	static int i = 0, j = 0, m = 0;
	static list<ST_PhoneBookRankUserInfo>::iterator itFrom;
	static list<ST_PhoneBookRankUserInfo>::iterator itTo;
	static list<ST_PhoneBookRankUserInfo>::iterator it;

	switch(e)
	{
		case MOUSE_STATUS_DOWN:
		{
			i = 0, j = 0, m = 0;

			if (id >= CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1 && id <= CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_5)
				i = id - CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_DISPLAY_NAME_1;
			else if (id >= CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1 && id <= CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_5)
				i = id - CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_DISPLAY_NAME_1;

			m = i;
			i = m_nSearchRankPageBrowseFrom + i;

			itFrom = m_listPhoneNumRankUserInfoHaveSelected.begin();
			itTo = m_listPhoneNumRankUserInfoHaveSelected.end();

			//ÕÒ¶ÔÓŠµÚÒ»ÏîÒªÏÔÊŸ
			j = 0;
			for (it = itFrom; it != itTo; it++)
			{
				if (i == j)
					break;
				j++;
			}

			
			
			if (it != itTo)
			{
				setDigitalData(id,1);
			}
			
		}
		break;
		case MOUSE_STATUS_UP:
		{
			if (it != itTo)
			{
				//LOGD("[%s] phone name = [%s]", __FUNCTION__,  it->szUserNameUtf8);
				//LOGD("[%s] nPhoneNumInfoCount = [%d]", __FUNCTION__,  it->nPhoneNumInfoCount);

				setDigitalData(id,0);

				if (it->nPhoneNumInfoCount == 1)
				{
					memset(&(m_pBtParam->m_stPhoneNumInput), 0, sizeof(ST_PHONE_NUM));
					
					int nLen = strlen(it->szstPhoneNumInfo[0].szPhoneNumUtf8);
					memcpy(m_pBtParam->m_stPhoneNumInput.szcPhoneNum, (u8*)it->szstPhoneNumInfo[0].szPhoneNumUtf8, nLen);
					m_pBtParam->m_stPhoneNumInput.dwLen = nLen;
						
					memcpy(m_pBtParam->m_stPhoneNumInput.szcName, it->szUserNameUtf8, strlen(it->szUserNameUtf8));
						
					if(m_pBtParam->nCallCount != CALLING_COUNT_FREE)
		        	{
		            	m_pBtParam->bItsAddCalls = true;
						m_pBtApp->m_pBtMainPage->AddCallsToUI(m_pBtParam->bItsAddCalls);
		        	}
					
					m_pBtApp->m_pBtMainPage->ActShowCallingInfor_aboutWhenOnlyOneCall(BT_PHONE_STATUS_FREE,true,true,it->szUserNameUtf8,m_pBtParam->m_stPhoneNumInput.szcPhoneNum);
					m_pBtApp->m_pBtMainPage->refreshAnswerHandup(m_pBtModule->getBtPhoneStatus());
					m_pBtModule->setPage(PAGE_BLUETOOTH_MAIN);
				}
			}
		}
		break;
		default:break;
	}

}

void CPhoneBookPages::clickSearchPageRankKeyPanel(u32 id, E_MOUSE_STATUS e)
{
	switch(e)
	{
		case MOUSE_STATUS_DOWN:
			{
				SearchRankKeyWord(id);
			}
			break;
		default:
			break;
	}//switch(e)
}

void CPhoneBookPages::SearchRankKeyWord(u32 id)
{
	LOGD("[%s] phone num has [%d]", __FUNCTION__,  m_mapPhoneNumUserInfo.size());
	
	clearRankSearchResult();
	if (getLoadPhoneBookStatus())
		return;
	m_nSearchRankPageBrowseFrom = 0;
	u32 firstWord = 0;
	
	if(id >= CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A && id <= CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_OTHER)				//ENGLISH HANZI
	{	
		int nAll = CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_OTHER - CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A + 1;
		for(int i = 0 ;i < nAll; i++)
		{
			if(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +i != id) 
			setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +i,0);
			else
			setDigitalData(CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_A +i, 1);	
		}
		firstWord = id - 0x93000 + 81;
	}

	if(id >= CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 && id <= CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_OTHER)		//ISRAEL
	{
		int nAllI = CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_OTHER- CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 + 1;
		for(int i = 0 ;i < nAllI; i++)
		{
			if(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +i != id) 
			setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +i,0);
			else
			setDigitalData(CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_1 +i, 1);	
		}
		firstWord = id - 0x93100 + 192;
	}
	
	map<int, ST_PhoneBookRankUserInfo* >::iterator itFrom = m_mapPhoneNumRankUserInfo.begin();
	map<int, ST_PhoneBookRankUserInfo* >::iterator itTo = m_mapPhoneNumRankUserInfo.end();
	for (map<int, ST_PhoneBookRankUserInfo* >::iterator it = itFrom; it != itTo; it++)
	{
		int key;
		UnicoTopinyin((u8*)it->second->szUserNameUnicode,&key,m_pBtParam->m_ePhoneBookKeyBoardSearchLanguage);
		if(id == CONTROLID_BLUETOOTH_ENGLISH_PHONE_BOOK_RANK_OTHER || id == CONTROLID_BLUETOOTH_ISRAEL_PHONE_BOOK_RANK_OTHER)
		{
			if((key  > 3000 && key < 4000) || (key > 7000))
			{
				ST_PhoneBookRankUserInfo stNode = *(it->second);
				m_listPhoneNumRankUserInfoHaveSelected.push_back(stNode);
				continue;
			}
		}
		else
		{
			if(key > 1000 && key <2000)
				key = key - 1000;
			else if(key > 2000 && key <3000)
				key = key - 2000;
			else if(key > 4000 && key <5000)
				 key = key - 4000;
			else if(key > 5000 && key <6000)
				key = key - 5000;
			else if(key > 6000 && key <7000)
				key = key - 6000;
			//LOGD("hhhhhhhhh : %s",it->second->szUserNameUtf8);
			//LOGD("key : %d",key);
			//LOGD("firstWord: %d",firstWord);
			if (key == firstWord)
			{
				ST_PhoneBookRankUserInfo stNode = *(it->second);
				m_listPhoneNumRankUserInfoHaveSelected.push_back(stNode);
			}
		}
	}
	m_listPhoneNumRankUserInfoHaveSelected.sort();
	refreshSearchPagePhoneRank(0);
}


void CPhoneBookPages::beginAccurateSearchKeyWord()
{
	clearSearchResult();
	u8 szSearchWordUtf8[SIZE_PHONE_BOOK_SEARCH_WORD] = {0};
	u8 szSearchWordAnsi[SIZE_PHONE_BOOK_SEARCH_WORD] = {0};
	int nLenUtf8 = ucs2_2_utf8(m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode, szSearchWordUtf8, sizeof(szSearchWordUtf8));

	int nLenAnsi = 0;
	int CurPageID = 0;
	int paramLen=0;
	m_pBtModule->getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,(u8*)&paramLen);
	if(CurPageID != PAGE_BLUETOOTH_AUDIOVOX_PHONE_BOOK_SEARCH_ISRAEL){
		nLenAnsi = ucs2_2_ansiJustForSearchKeyWord(m_szPhoneBookSearchWordUnicode, m_nPhoneBookSearchWordLenUnicode, szSearchWordAnsi, sizeof(szSearchWordAnsi));
	}
	if (getLoadPhoneBookStatus())
		return;
	btAccurateSearchKeyWord(szSearchWordUtf8,nLenUtf8);
	btNoAccurateSearchKeyWord(szSearchWordUtf8,nLenUtf8,szSearchWordAnsi,nLenAnsi);
	refreshSearchPageSearchResult(0);
}


int CPhoneBookPages::findAccurateKeyWord(u8 *pLongString, int nLongStringLen,u8 *keyWord,int len)
{
	if(nLongStringLen <= 0 || len > nLongStringLen)
		return 0;
	if(sizeof((char *)pLongString) == 0)
		return 0;
	u8 pShortString[PHONENUM_OR_PHONENAME_MAX_LEN];
	memset(pShortString,0,PHONENUM_OR_PHONENAME_MAX_LEN);
	memcpy(pShortString,pLongString,nLongStringLen);
	for(int j = 0;j<nLongStringLen;j++ )
	{	
		if (pShortString[j] >= 'a' && pShortString[j] <= 'z')
		{	
			pShortString[j] = pShortString[j] - 32;
		}
	}
	int tempLen = nLongStringLen - len;
	if(!strncmp((char *)pShortString ,(char *)keyWord,len))
	{
		return 1;
	}
	return 0;
}

void CPhoneBookPages::getPhoneNumDetailInfo(char *name,int nameLen,char *number,int numLen)
{
	Bt_Book_Accurate_Search t;
	t.stDetailedInfo.PBName_CompleteTotal_Len = m_pBtParam->extended_Infor.PBName_CompleteTotal_Len;

	memset(t.stDetailedInfo.PBName_Prefix,0,PHONE_NUM_NAME_MAX_SIZE);
	memcpy(t.stDetailedInfo.PBName_Prefix,m_pBtParam->extended_Infor.PBName_Prefix,m_pBtParam->extended_Infor.PBName_Prefix_Len);
	t.stDetailedInfo.PBName_Prefix_Len = m_pBtParam->extended_Infor.PBName_Prefix_Len;

	memset(t.stDetailedInfo.PBName_First,0,PHONE_NUM_NAME_MAX_SIZE);
	memcpy(t.stDetailedInfo.PBName_First,m_pBtParam->extended_Infor.PBName_First,m_pBtParam->extended_Infor.PBName_First_Len);
	t.stDetailedInfo.PBName_First_Len = m_pBtParam->extended_Infor.PBName_First_Len;

	memset(t.stDetailedInfo.PBName_Mid,0,PHONE_NUM_NAME_MAX_SIZE);
	memcpy(t.stDetailedInfo.PBName_Mid,m_pBtParam->extended_Infor.PBName_Mid,m_pBtParam->extended_Infor.PBName_Mid_Len);
	t.stDetailedInfo.PBName_Mid_Len = m_pBtParam->extended_Infor.PBName_Mid_Len;

	memset(t.stDetailedInfo.PBName_Last,0,PHONE_NUM_NAME_MAX_SIZE);
	memcpy(t.stDetailedInfo.PBName_Last,m_pBtParam->extended_Infor.PBName_Last,m_pBtParam->extended_Infor.PBName_Last_Len);
	t.stDetailedInfo.PBName_Last_Len = m_pBtParam->extended_Infor.PBName_Last_Len;

	memset(t.stDetailedInfo.PBName_Suffix,0,PHONE_NUM_NAME_MAX_SIZE);
	memcpy(t.stDetailedInfo.PBName_Suffix,m_pBtParam->extended_Infor.PBName_Suffix,m_pBtParam->extended_Infor.PBName_Suffix_Len);
	t.stDetailedInfo.PBName_Suffix_Len = m_pBtParam->extended_Infor.PBName_Suffix_Len;

	t.nPhoneNumInfoCount = 1;
	memset(t.szUserNameUtf8,0,PHONE_NUM_NAME_MAX_SIZE);
	memcpy(t.szUserNameUtf8,name,nameLen);
	memset(t.szstPhoneNumInfo[0].szPhoneNumUtf8,0,PHONE_NUM_NAME_MAX_SIZE);
	memcpy(t.szstPhoneNumInfo[0].szPhoneNumUtf8,number,numLen);
	m_listPhoneNumAccurateSearch.push_back(t);
}

void CPhoneBookPages::btAccurateSearchKeyWord(u8 *szSearchWordUtf8,int nLenUtf8)
{
	m_listPhoneNumUserInfoHaveSelected.clear();
	static int tempNameMatchWeight = 0;
	if(strlen((char *)szSearchWordUtf8) != 0)
	{
		list<Bt_Book_Accurate_Search>::iterator itFrom = m_listPhoneNumAccurateSearch.begin();
		list<Bt_Book_Accurate_Search>::iterator itTo = m_listPhoneNumAccurateSearch.end();
		list<Bt_Book_Accurate_Search>::iterator it;

		ST_PhoneBookUserInfo t;

		for(int i=0; i < 5; i++)
		{
			for (it = itFrom; it != itTo; it++)
			{	
				tempNameMatchWeight = 0;
				switch(i)
				{
					case 0:
						if(findAccurateKeyWord((u8 *)it->stDetailedInfo.PBName_Prefix,it->stDetailedInfo.PBName_Prefix_Len,szSearchWordUtf8,nLenUtf8))
							tempNameMatchWeight = 5;
					break;
					case 1:
						if(findAccurateKeyWord((u8 *)it->stDetailedInfo.PBName_Last,it->stDetailedInfo.PBName_Last_Len,szSearchWordUtf8,nLenUtf8))
							tempNameMatchWeight = 4;
					break;
					case 2:
						if(findAccurateKeyWord((u8 *)it->stDetailedInfo.PBName_Mid,it->stDetailedInfo.PBName_Mid_Len,szSearchWordUtf8,nLenUtf8))
							tempNameMatchWeight = 3;
					break;
					case 3:
						if(findAccurateKeyWord((u8 *)it->stDetailedInfo.PBName_First,it->stDetailedInfo.PBName_First_Len,szSearchWordUtf8,nLenUtf8))
							tempNameMatchWeight = 2;
					break;
					case 4:
						if(findAccurateKeyWord((u8 *)it->stDetailedInfo.PBName_Suffix,it->stDetailedInfo.PBName_Suffix_Len,szSearchWordUtf8,nLenUtf8))
							tempNameMatchWeight = 1;
					break;
				}
				if(tempNameMatchWeight != 0)
				{
					list<ST_PhoneBookUserInfo>::iterator itFrom1 = m_listPhoneNumUserInfoHaveSelected.begin();
					list<ST_PhoneBookUserInfo>::iterator itTo1 = m_listPhoneNumUserInfoHaveSelected.end();
					list<ST_PhoneBookUserInfo>::iterator it1;
					for (it1 = itFrom1; it1 != itTo1; it1 ++)
					{
						if(!strncmp(it1->szstPhoneNumInfo[0].szPhoneNumUtf8,it->szstPhoneNumInfo[0].szPhoneNumUtf8,strlen(it->szstPhoneNumInfo[0].szPhoneNumUtf8))&& 
							(strlen(it->szstPhoneNumInfo[0].szPhoneNumUtf8) == strlen(it1->szstPhoneNumInfo[0].szPhoneNumUtf8)))
							return;
					}
					memset(&t, 0, sizeof(ST_PhoneBookUserInfo));
					memcpy(t.szUserNameUtf8 , it->szUserNameUtf8,strlen(it->szUserNameUtf8));
					memset(t.szstPhoneNumInfo[0].szPhoneNumUtf8, 0, sizeof(t.szstPhoneNumInfo[0].szPhoneNumUtf8));
					memcpy(t.szstPhoneNumInfo[0].szPhoneNumUtf8, it->szstPhoneNumInfo[0].szPhoneNumUtf8,strlen(it->szstPhoneNumInfo[0].szPhoneNumUtf8));
					t.nPhoneNumInfoCount = it->nPhoneNumInfoCount;
					//m_listPhoneNumUserInfoHaveSelected.push_back(t);
					getOneNameForMoreNum_List_New(t);
				}
				
			}
		}
	}
}

void CPhoneBookPages::btNoAccurateSearchKeyWord(u8 *szSearchWordUtf8,int nLenUtf8,u8 *szSearchWordAnsi,int nLenAnsi)
{
	if (m_listPhoneNumUserInfoHaveSelected.empty())
	{
		map<int, ST_PhoneBookUserInfo* >::iterator itFrom = m_mapPhoneNumUserInfo.begin();
		map<int, ST_PhoneBookUserInfo* >::iterator itTo = m_mapPhoneNumUserInfo.end();
		for (map<int, ST_PhoneBookUserInfo* >::iterator it = itFrom; it != itTo; it++)
		{
			int r = 0;
			r = findSubString(szSearchWordUtf8, nLenUtf8, (u8*)it->second->szUserNameUtf8, strlen(it->second->szUserNameUtf8));

			if (r != -1)
			{
				ST_PhoneBookUserInfo stNode = *(it->second);
				//m_listPhoneNumUserInfoHaveSelected.push_back(stNode);
				getOneNameForMoreNum_List_New(stNode);
			}
			else
			{
				int nMatchWeight = 0;
				char *pName = (char*)it->second->szUserNameUnicode;
				
				if (nLenUtf8 != 0 && nLenAnsi == 0)
				{
					r = -1;
				}
				else
				{
					r = findSubStringInUnicodePhoneBook(szSearchWordAnsi, nLenAnsi, (u8*)pName, 2 * getLengthOfUnicodeString(pName, FILE_PHONECMD_MAX_LEN), nMatchWeight);
				}
				
				if (r != -1)
				{
					ST_PhoneBookUserInfo stNode = *(it->second);
					stNode.nUserNameMatchWeight = nMatchWeight;
					//m_listPhoneNumUserInfoHaveSelected.push_back(stNode);
					getOneNameForMoreNum_List_New(stNode);
				}
			}
		}
		m_listPhoneNumUserInfoHaveSelected.sort();
	}
}

void CPhoneBookPages::getOneNameForMoreNum_List(ST_PhoneBookUserInfo stNode)
{
       list<ST_PhoneBookUserInfo>::iterator itFrom1 = m_listPhoneNumUserInfoHaveSelected.begin();
       list<ST_PhoneBookUserInfo>::iterator itTo1 = m_listPhoneNumUserInfoHaveSelected.end();
       list<ST_PhoneBookUserInfo>::iterator it1;
       if(m_listPhoneNumUserInfoHaveSelected.size() == 0)
       {
           stNode.nPhoneNumInfoCount = 1;
           m_listPhoneNumUserInfoHaveSelected.push_back(stNode);
       }
       else
	   {
           for(it1 = itFrom1;it1 != itTo1;it1++)
           {
               if(!strncmp(it1->szUserNameUtf8,stNode.szUserNameUtf8,strlen(stNode.szUserNameUtf8)))
               {
                   int i;
                   for(i = 0;i < ONE_NAME_FOR_MULT_NUM_DISPLAY;i++)
                   {
                       if(strlen(it1->szstPhoneNumInfo[i].szPhoneNumUtf8) == 0)
                               break;
                       if(!strncmp(it1->szstPhoneNumInfo[i].szPhoneNumUtf8,stNode.szstPhoneNumInfo[0].szPhoneNumUtf8,strlen(stNode.szstPhoneNumInfo[0].szPhoneNumUtf8)))
                               return;
                       if(i == ONE_NAME_FOR_MULT_NUM_DISPLAY)
                               return;
                   }
                   memcpy(it1->szstPhoneNumInfo[i].szPhoneNumUtf8,stNode.szstPhoneNumInfo[0].szPhoneNumUtf8,strlen(stNode.szstPhoneNumInfo[0].szPhoneNumUtf8));
                   it1->nPhoneNumInfoCount = i + 1;
                   return;
               } 
           }
		   
           stNode.nPhoneNumInfoCount = 1;
           m_listPhoneNumUserInfoHaveSelected.push_back(stNode);
       }
}


void CPhoneBookPages::refreshSearchResultPageSearchResult_New(int nFrom)
{
	setUpdateUI(false);

	int nBrowseFileNum = m_listPhoneNumUserInfoHaveSelected.size();

	if (nFrom >= nBrowseFileNum)
		nFrom -= ONE_NAME_FOR_MULT_NUM_DISPLAY;

	if (nFrom < 0)
		nFrom = 0;
	m_nOneNameForMultipleNum = nFrom;
	int i = 0, j = 0, k = 0;
	list<ST_PhoneBookUserInfo>::iterator itFrom = m_listPhoneNumUserInfoHaveSelected.begin();
	list<ST_PhoneBookUserInfo>::iterator itTo = m_listPhoneNumUserInfoHaveSelected.end();
	list<ST_PhoneBookUserInfo>::iterator it;
	//ÕÒ¶ÔÓŠµÚÒ»ÏîÒªÏÔÊŸ
	for (it = itFrom; it != itTo; it++)
	{
		if (j == nFrom)
			break;
		j++;
	}
	//Ë¢ SEARCH_LIST_DISPLAY_NUM Ïî
	for (i = nFrom; i < nFrom + ONE_NAME_FOR_MULT_NUM_DISPLAY; i++)
	{
		if (j >= nFrom && it != itTo)
		{
			char *pData = (char*)it->szUserNameUtf8;
			int len = strlen(pData);

			setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 + k, (u8*)pData, len);
			it++, j++;
		}
		else
		{
			setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 + k, (u8*)"", 0);
		}

		k++;
	}

	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_2, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_3, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_4, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_5, 0);
	LOGD("HHHHH4%d	--- %d",m_nOneNameForMultipleNumIndex,m_nOneNameForMultipleNum);
	if (m_nOneNameForMultipleNumIndex >= m_nOneNameForMultipleNum && m_nOneNameForMultipleNumIndex < m_nOneNameForMultipleNum + 5)
	{
		int n = m_nOneNameForMultipleNumIndex - m_nOneNameForMultipleNum;
		setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 + n, 1);
	}

	setUpdateUI(true);
}


void CPhoneBookPages::clickSearchResultPagePrePage_New(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nPreStartBrowse = -1;
			nPreStartBrowse = m_nOneNameForMultipleNum;
			m_nOneNameForMultipleNum = max(0, m_nOneNameForMultipleNum - ONE_NAME_FOR_MULT_NUM_DISPLAY);
			if (nPreStartBrowse == m_nOneNameForMultipleNum)
				return;
			refreshSearchResultPageSearchResult_New(m_nOneNameForMultipleNum);
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clickSearchResultPageNextPage_New(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
			static int nNextStartBrowse = -1;
			nNextStartBrowse = m_nOneNameForMultipleNum;

			m_nOneNameForMultipleNum += ONE_NAME_FOR_MULT_NUM_DISPLAY;
			if (m_nOneNameForMultipleNum >= (int)m_listPhoneNumUserInfoHaveSelected.size())
				m_nOneNameForMultipleNum -= ONE_NAME_FOR_MULT_NUM_DISPLAY;

			if(nNextStartBrowse == m_nOneNameForMultipleNum)
				return;
			refreshSearchResultPageSearchResult_New(m_nOneNameForMultipleNum);
		}
		break;
	default:
		break;
	}
}

void CPhoneBookPages::clearOneNameForMultNumShow()
{
	m_nOneNameForMultipleNum = -1;
	m_nOneNameForMultipleNumIndex = -1;
	memset(m_szStrPhoneNumOfOneName_Name, 0, SIZE_PHONE_BOOK_SEARCH_WORD * 4);
	setUpdateUI(false);
	for(int k = 0;k < ONE_NAME_FOR_MULT_NUM_DISPLAY;k++)
	{
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1 + k, (u8*)"", 0);
		setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_6 + k, (u8*)"", 0);
		memset(&m_szStrPhoneNumOfOneNameShowUtf8[k], 0, PHONE_NUM_MAX_SIZE * 4);
	}
	setSerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT, (u8*)"", 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_1, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_2, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_3, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_4, 0);
	setDigitalData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT_5, 0);
	setUpdateUI(true);
}

void CPhoneBookPages::getNameListTagAndInfo(int i,char *szUserNameUtf8)
{
	m_nOneNameForMultipleNum = i - (i%ONE_NAME_FOR_MULT_NUM_DISPLAY);
	m_nOneNameForMultipleNumIndex = i;
	memset(m_szStrPhoneNumOfOneName_Name, 0, SIZE_PHONE_BOOK_SEARCH_WORD * 4);
	memcpy(m_szStrPhoneNumOfOneName_Name, szUserNameUtf8, strlen(szUserNameUtf8));
	setUtf8SerialData(CONTROLID_BLUETOOTH_AUDIOVOX_CONTACTS_TEXT,(u8 *)szUserNameUtf8,  strlen(szUserNameUtf8));
	refreshSearchResultPageSearchResult_New(m_nOneNameForMultipleNum);
	m_pBtModule->setPage(PAGE_BLUETOOTH_AUDIOVOX_CONTACTS);
}

void CPhoneBookPages::getOneNameForMoreNum_List_New(ST_PhoneBookUserInfo stNode)
{
	if(m_listPhoneNumUserInfoHaveSelected.size() == 0)
       {
           stNode.nPhoneNumInfoCount = 1;
           m_listPhoneNumUserInfoHaveSelected.push_back(stNode);
       }
	else
	{
		list<ST_PhoneBookUserInfo>::iterator it = m_listPhoneNumUserInfoHaveSelected.end();
		it--;
		
		if(!strncmp(it->szUserNameUtf8,stNode.szUserNameUtf8,strlen(stNode.szUserNameUtf8)))
	       {
			int i;
			for(i = 0;i < ONE_NAME_FOR_MULT_NUM_DISPLAY;i++)
			{
				if(!strncmp(it->szstPhoneNumInfo[i].szPhoneNumUtf8,stNode.szstPhoneNumInfo[0].szPhoneNumUtf8,strlen(stNode.szstPhoneNumInfo[0].szPhoneNumUtf8)))
				return;
				else if(i == ONE_NAME_FOR_MULT_NUM_DISPLAY)
				return;
				else if(strlen(it->szstPhoneNumInfo[i].szPhoneNumUtf8) == 0)
				break;
			}
			memcpy(it->szstPhoneNumInfo[i].szPhoneNumUtf8,stNode.szstPhoneNumInfo[0].szPhoneNumUtf8,strlen(stNode.szstPhoneNumInfo[0].szPhoneNumUtf8));
			it->nPhoneNumInfoCount = i + 1;
			return;
	       } 
	 	stNode.nPhoneNumInfoCount = 1;
		m_listPhoneNumUserInfoHaveSelected.push_back(stNode);
	}
}


