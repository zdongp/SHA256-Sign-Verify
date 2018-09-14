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

	//phoneBookSearchPage
	void clickSearchPageEnglishKeyBoardEntrance(E_MOUSE_STATUS e);
	void clickSearchPageIsRaelKeyBoardEntrance(E_MOUSE_STATUS e);
	void clickSearchPageGoBack(E_MOUSE_STATUS e);
	void clickSearchPageBackspace(E_MOUSE_STATUS e);
	void clickSearchPageKeyPanel(u32 id, E_MOUSE_STATUS e);
	void clickSearchPagePrePage(E_MOUSE_STATUS e);
	void clickSearchPageNextPage(E_MOUSE_STATUS e);
	void clickSearchPageSearchResultItem(u32 id, E_MOUSE_STATUS e);
	//phoneBookSearchResultPage
	void clickSearchResultPageGoBack(E_MOUSE_STATUS e);
	void clickSearchResultPagePrePage(E_MOUSE_STATUS e);
	void clickSearchResultPageNextPage(E_MOUSE_STATUS e);
	void clickSearchResultPageNameItem(u32 id, E_MOUSE_STATUS e);
	void clickSearchResultPageNumItem(u32 id, E_MOUSE_STATUS e);
	//work
	wchar_t getPhoneBookKeyBoardKeyNameById(E_MOUSE_STATUS e, int id);
	void beginSearchKeyWord(void);

	void clearPhoneBook(void);
	void clearSearchResult(void);

	void refreshSearchPageSearchResult(int nFrom);
	void refreshSearchResultPageSearchResult(int nFrom);
	void refreshLoadPhoneBookStatus(u32 id);

	void getAllPhoneBookLoadDone(void);

	//assist
	int findSubString(u8 *pShortString, int nShortStringLen, u8 *pLongString, int nLongStringLen);
	int findSubStringInPinyin(u8 *pShortString, int nShortStringLen, u8 *pLongString, int nLongStringLen);
	int findSubStringInUnicodePhoneBook(u8 *pShortString, int nShortStringLen, u8 *pLongString, int nLongStringLen, int &nMatchWeight);
	bool getLoadPhoneBookStatus(void);
	bool isSearchKeyWordEmpty();
	u16 getCurPageId(void);
	u16 getPrePageId(void);
	void createSearchPhoneBook(void);
	int ucs2_2_ansiJustForSearchKeyWord(u8 *pSrc, int nSrcLen, u8 *pDst, int nDstLen);
	int getLengthOfUnicodeString(char *p, int len);
	int getHanZiMatchWeight(int i);
	void sortMapPhoneNumUserInfoHaveSelected(void);
	void clearSearchResultData();
	void showLoadingPhoneBookTips(u32 strTips);

		/*******BC08 RANK*******/
	void UnicoTopinyin(u8 *pLongString,int *cFirst,E_KEY_BOARD_LANGUAGE curLanguage);
	bool phoneBookRankSearchPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	void clickPhoneBookRankPageEntrance(E_MOUSE_STATUS e);
	void clickPhoneBookPageToRankPage(E_MOUSE_STATUS e);
	void clearRankSearchResultData();
	void clearRankSearchResult(void);
	void beginSearchRankKeyWord();
	void refreshSearchPagePhoneRank(int nFrom);
	void clickSearchPageRankPrePage(E_MOUSE_STATUS e);
	void clickSearchPageRankNextPage(E_MOUSE_STATUS e);
	void clickPhoneBookRankPageLeftOrRight(u32 id);
	void setEnglishShowOrHide(int page,int key);
	void setIsraelShowOrHide(int page,int key);
	void initsetIsraelShowOrHide(void);
	void initsetEnglishShowOrHide(void);
	void clickSearchRankPageEnglishKey(E_MOUSE_STATUS e);
	void clickSearchRankPageIsraelKey(E_MOUSE_STATUS e);
	void clickSearchRankPageSearchResultItem(u32 id, E_MOUSE_STATUS e);
	void SearchRankKeyWord(u32 id);
	void clickSearchPageRankKeyPanel(u32 id, E_MOUSE_STATUS e);

	void beginAccurateSearchKeyWord();
	int  findAccurateKeyWord(u8 *pLongString, int nLongStringLen,u8 *keyWord,int len);
	void getPhoneNumDetailInfo(char *name,int nameLen,char *number,int numLen);
	void btAccurateSearchKeyWord(u8 *szSearchWordUtf8,int nLenUtf8);
	void btNoAccurateSearchKeyWord(u8 *szSearchWordUtf8,int nLenUtf8,u8 *szSearchWordAnsi,int nLenAnsi);
	void getOneNameForMoreNum_List(ST_PhoneBookUserInfo stNode);
	void refreshSearchResultPageSearchResult_New(int nFrom);
	void clickSearchResultPagePrePage_New(E_MOUSE_STATUS e);
	void clickSearchResultPageNextPage_New(E_MOUSE_STATUS e);
	void clearOneNameForMultNumShow();
	void getNameListTagAndInfo(int i,char *szUserNameUtf8);
	void getOneNameForMoreNum_List_New(ST_PhoneBookUserInfo stNode);
public:
	u8 m_szPhoneBookSearchWordUnicode[SIZE_PHONE_BOOK_SEARCH_WORD];
	int m_nPhoneBookSearchWordLenUnicode;

	map<int, ST_PhoneBookUserInfo* > m_mapPhoneNumUserInfo;				//utf8
	list<ST_PhoneBookUserInfo> m_listPhoneNumUserInfoHaveSelected;		//utf8
	
	//RANK
	map<int, ST_PhoneBookRankUserInfo* > m_mapPhoneNumRankUserInfo;				//utf8
	list<ST_PhoneBookRankUserInfo> m_listPhoneNumRankUserInfoHaveSelected;
	//Accurate Search
	list<Bt_Book_Accurate_Search> m_listPhoneNumAccurateSearch;
	char m_szStrPhoneNumOfOneNameShowUtf8[5][PHONE_NUM_MAX_SIZE * 4];
	char m_szStrPhoneNumOfOneName_Name[128*4];

	int m_nSearchPageBrowseFrom;
	int m_nSearchResultPageBrowseFrom;
	int m_nSearchPageActiveIndex;
	int m_nSearchResultPageActiveIndex;
	//BC08 RANK
	int m_nSearchRankPageBrowseFrom;
	int m_nSearchRankleftOrRight;

	bool m_bIsLoadingPhoneBook;

	int m_nOneNameForMultipleNumIndex;
	int m_nOneNameForMultipleNum;

//BC8
public:
	void createSearchPhoneBook2(void);
	
public:
	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
};
