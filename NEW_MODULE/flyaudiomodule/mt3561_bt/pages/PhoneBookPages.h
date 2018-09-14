#pragma once
#include "BtParam.h"

class CBtApp;
class CBtModule;
class CBtHal;
class CBtParam;

class CPhoneBookPages : public CFlyApp
{
public:
	CPhoneBookPages(void);
	~CPhoneBookPages(void);

public:
	//init
	void init(void);
	void deInit();
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	bool pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	
	//
	void initUi(void);

	bool phoneBookSearchPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool phoneBookSearchResultPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool phoneBookRankSearchPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	void getAllPhoneBookLoadDone(void);
	void createSearchPhoneBook(void);
	void beginSearchKeyWord();
	void clearSearchResult(void);
	int ucs2_2_ansiJustForSearchKeyWord(u8 *pSrc, int nSrcLen, u8 *pDst, int nDstLen);
	bool getLoadPhoneBookStatus(void);
	int findSubString(u8 *pShortString, int nShortStringLen, u8 *pLongString, int nLongStringLen); 
	int findSubStringInUnicodePhoneBook(u8 *pShortString, int nShortStringLen, u8 *pLongString, int nLongStringLen, int &nMatchWeight);
	void refreshSearchPageSearchResult(int nFrom);
	void showLoadingPhoneBookTips(u32 strTips);
	void clearSearchResultData();
	void clickSearchPageGoBack(E_MOUSE_STATUS e);
	void clickSearchPageIsRaelKeyBoardEntrance(E_MOUSE_STATUS e);
	void clickSearchPageEnglishKeyBoardEntrance(E_MOUSE_STATUS e);
	void beginAccurateSearchKeyWord();
	void btAccurateSearchKeyWord(u8 *szSearchWordUtf8,int nLenUtf8);
	int findAccurateKeyWord(u8 *pLongString, int nLongStringLen,u8 *keyWord,int len);
	void btNoAccurateSearchKeyWord(u8 *szSearchWordUtf8,int nLenUtf8,u8 *szSearchWordAnsi,int nLenAnsi);
	void refreshLoadPhoneBookStatus(u32 id);
	void clickSearchPageSearchResultItem(u32 id, E_MOUSE_STATUS e);
	void refreshSearchResultPageSearchResult(int nFrom);
	void clickSearchPagePrePage(E_MOUSE_STATUS e);
	void clickSearchPageNextPage(E_MOUSE_STATUS e);
	void clickSearchPageBackspace(E_MOUSE_STATUS e);
	void clickSearchPageKeyPanel(u32 id, E_MOUSE_STATUS e);
	wchar_t getPhoneBookKeyBoardKeyNameById(E_MOUSE_STATUS e, int id);
	void clearRankSearchResultData();
	void clearRankSearchResult(void);
	void beginSearchRankKeyWord();
	void refreshSearchPagePhoneRank(int nFrom);
	void clickPhoneBookPageToRankPage(E_MOUSE_STATUS e);
	void initsetIsraelShowOrHide(void);
	void initsetEnglishShowOrHide(void);
	void setIsraelShowOrHide(int page,int key);
	void setEnglishShowOrHide(int page,int key);
	void clickSearchResultPageGoBack(E_MOUSE_STATUS e);
	void clickSearchResultPagePrePage(E_MOUSE_STATUS e);
	void clickSearchResultPageNextPage(E_MOUSE_STATUS e);
	void clickSearchResultPageNameItem(u32 id, E_MOUSE_STATUS e);
	void clickSearchResultPageNumItem(u32 id, E_MOUSE_STATUS e); 
	void clickSearchPageRankPrePage(E_MOUSE_STATUS e);
	void clickSearchPageRankNextPage(E_MOUSE_STATUS e);
	void clickPhoneBookRankPageLeftOrRight(u32 id);
	void clickSearchRankPageEnglishKey(E_MOUSE_STATUS e);
	void clickSearchRankPageSearchResultItem(u32 id, E_MOUSE_STATUS e);
	void clickSearchPageRankKeyPanel(u32 id, E_MOUSE_STATUS e);
	void SearchRankKeyWord(u32 id);
	void clickPhoneBookRankPageEntrance(E_MOUSE_STATUS e);
	void clickSearchRankPageIsraelKey(E_MOUSE_STATUS e);
	void getPhoneNumDetailInfo(char *name,int nameLen,char *number,int numLen);
	void clearPhoneBook(void);
	int getLengthOfUnicodeString(char *p, int len);
	int getHanZiMatchWeight(int i);
	void UnicoTopinyin(u8 *pLongString,int *cFirst,E_KEY_BOARD_LANGUAGE curLanguage);
public:
	u8 m_szPhoneBookSearchWordUnicode[SIZE_PHONE_BOOK_SEARCH_WORD];
	char m_szStrPhoneNumOfOneNameShowUtf8[SEARCH_RESULT_LIST_DISPLAY_NUM][PHONE_NUM_MAX_SIZE * 4];
	int m_nPhoneBookSearchWordLenUnicode;
	map<int, ST_PhoneBookUserInfo* > m_mapPhoneNumUserInfo;
	list<ST_PhoneBookUserInfo> m_listPhoneNumUserInfoHaveSelected;
	bool m_bIsLoadingPhoneBook;
	int m_nSearchPageBrowseFrom;
	list<Bt_Book_Accurate_Search> m_listPhoneNumAccurateSearch;
	int m_nSearchPageActiveIndex;
	int m_nSearchResultPageBrowseFrom;
	int m_nSearchResultPageActiveIndex;
	list<ST_PhoneBookRankUserInfo> m_listPhoneNumRankUserInfoHaveSelected;
	map<int, ST_PhoneBookRankUserInfo* > m_mapPhoneNumRankUserInfo;	
	int m_nSearchRankleftOrRight;
	int m_nSearchRankPageBrowseFrom;
public:
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
};
