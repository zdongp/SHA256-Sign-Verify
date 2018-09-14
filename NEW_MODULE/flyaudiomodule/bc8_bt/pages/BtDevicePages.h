#pragma once
#include "BtParam.h"

class CBtApp;
class CBtModule;
class CBtHal;
class CBtParam;

class CBtDevicePages :
	public CFlyApp
{
public:
	CBtDevicePages(void);
	virtual ~CBtDevicePages(void);

public:
	//init
	virtual void init(void);
	virtual void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void initUi(void);
	//
	bool pageMsgDispatch(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	//
	bool btDeviceMainPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool btDeviceSearchPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool btDeviceSettingPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool btDevicePinCodePage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool btDeviceNameEditPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool btPhoneDevicePairDialogBox(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	//device main page
	void clickDeviceMainPageGoBack(E_MOUSE_STATUS e);
	void clickDeviceMainPageSearchPageEntrance(E_MOUSE_STATUS e);
	void clickDeviceMainPageSettingPageEntrance(E_MOUSE_STATUS e);
	void clickDeviceMainDeleteDeviceHasPaired(E_MOUSE_STATUS e, int index);
	void clickDeviceMainDeleteDevicesHavePaired(E_MOUSE_STATUS e);
	void clickDeviceMainDevicesHavePairedListItem(E_MOUSE_STATUS e, int index);
	void clickDeviceMainDeleteDeviceHasPairedOk(E_MOUSE_STATUS e);
	void clickDeviceMainDeleteDeviceHasPairedCancel(E_MOUSE_STATUS e);
	//device search page
	void clickDeviceSearchPageGoBack(E_MOUSE_STATUS e);
	void clickDeviceSearchPageSearchDevice(E_MOUSE_STATUS e);
	void clickDeviceSearchPagePrePage(E_MOUSE_STATUS e);
	void clickDeviceSearchPageNextPage(E_MOUSE_STATUS e);
	void clickDeviceSearchPageDeviceItem(u32 id, E_MOUSE_STATUS e);
	//device setting page
	void clickDeviceSettingPageGoBack();
	void clickDeviceSettingPageAutoConnectOn();
	void clickDeviceSettingPageAutoConnectOff(E_MOUSE_STATUS e);
	void clickDeviceSettingPageBtDeviceNameEditEntrance();
	void clickDeviceSettingPageBtDevicePinCodeEditEntrance();
	void clickDeviceSettingPageMicVolume(u8 p);
	void clickDeviceSettingPageMicGainPage();
	void clickDeviceSettingPageMicPageBack();
	//device pin code page
	void clickDevicePinCodeEditPageGoBack();
	void clickDevicePinCodeEditPageDialPanel(u32 id);
	void clickDevicePinCodeEditPageBackspace(E_MOUSE_STATUS e);
	//
	void clickDeviceNameEditPageGoBack();
	void clickDeviceNameEditPageDialPanel(E_MOUSE_STATUS e,u32 id);
	void clickDeviceNameEditPageBackspace(E_MOUSE_STATUS e);
	void clickDeviceNameEditPageOK();
	
	void showTipBox(E_TIP_BOX_NAME e, bool bShow = true);
	void clickTipBoxOk();
	void clickTipBoxCancle();

	void refreshBtDeviceSearchStatus(E_BT_DEVICE_SEARCH_STATUS e);
	void refreshBtDevicesListHaveSearched(int n);
	void refreshBtDevicesListHavePaired(int n);
	void clickDisplaySetDeviceNameToUi(u8 *param,u32 len);
	void clickDisplayDeviceNameKeyboardToUi(u8 *param,u32 len);
	void clickDeviceDisplayAutoConnect(bool  bMode);
	void setSerialMicrophoneVolumeGainToUI(int nParam);
	void setSerialMicrophoneVolumeToUI(int nParam);
	void showPinCodeTipBox( bool bShow);
	void clickPinCodeTipBoxOk();
	bool btPhoneDevicePairPage(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	void clickPhoneDevicePairPageGoBack(E_MOUSE_STATUS e);

	//BC8
	void clickDevicePairDialogBoxOK();
	void clickDevicePairDialogBoxChance();
	void clickDevicePairDialogBoxGoBack();
	void showDialogBox_Pairing(u8 *p1,int len1,u8 *p2,int len2);
	void getSystemParam_changePage(u8 *buff);
	void HideHasBeenPaired();
	void ShowHasBeenPaired();
	bool UI_MouseDown_MultiPair_Main_Search();
	void showTipBox_BC8(bool bShow);
	void ShowOrHideHasBeenPairingPage(bool b);
	void ShowOrHideHasBeenPairingPromptBoxPage(bool b);
	void ShowBtMacAddress(char *strData,int len);
public:
	void clickPinCodeTipBoxOk_Pairing_Connection_Prompt_BC8();

	void clickDeviceSearchPageDeviceItem_New(u32 id, E_MOUSE_STATUS e);
	void refreshBtDevicesListHaveSearched_New(int n);
	void clickDeviceSearchPagePrePage_New(E_MOUSE_STATUS e);
	void clickDeviceSearchPageNextPage_New(E_MOUSE_STATUS e);

	void clickDeviceMainDeleteDeviceHasPaired_New(E_MOUSE_STATUS e, int index);
	void clickDeviceMainDevicesHavePairedListItem_New(E_MOUSE_STATUS e, int index);
	void refreshBtDevicesListHavePaired_New(int n);
	
public:
	int m_nBtDevicesHavePairedListBrowseFrom;
	int m_nBtDevicesHaveSearchedListBrowseFrom;

	CBtApp    *m_pBtApp;
	CBtModule *m_pBtModule;
	CBtHal    *m_pBtHal;
	CBtParam  *m_pBtParam;
private:
	char BtDevicePinCode[64];
};