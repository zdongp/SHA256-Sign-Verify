#pragma once
#include "FlyJniSdkModule.h"

class CFlyJniSdkModule;
class CFlyJniSdkModuleBt :
	public CFlyJniSdkModule
{
public:
	CFlyJniSdkModuleBt(void);
	virtual ~CFlyJniSdkModuleBt(void);

	void getBtMessage(u8 *p, u8 len);
	void getAppCtrlMessage(u8 *p, u8 len);

	void onBlueToothPowerStatus(u8 p);						//蓝牙电源状态监听
	void onBlueToothConnectStatus(u8 p);						//蓝牙连接状态监听
	void onBlueToothPairStatus(u8 p);				//蓝牙远程设备名字监听
	void onBlueToothPhoneStatus(u8 p);						//蓝牙电话状态监听
	void onBlueToothCallingName(u8 *p, int len);
	void onBlueToothCallingNumber(u8 *p, int len);

	//moupeng 2015/7/28
    void onBlueToothMusicTrank(u8 *p, int len);
	void onBlueToothMusicArtist(u8 *p, int len);
	void onBlueToothMusicAlbum(u8 *p, int len);
	//moupeng 2015/7/29
	void onBlueToothMusicStatus(u8 p);
	void onBlueToothSupportMusic(u8 p);
	void onBlueToothCallingMicState(u8 p);

	//控制项
	void setToBlueToothPowerOn(u8 p);					//调节蓝牙电源
	void setToBlueToothReceivePhoneCall();			//接听电话
	void setToBlueToothRejectPhoneCall();				//拒听电话
	//moupeng 2015/7/29
	void   setToBlueToothNextMusic();
	void   setToBlueToothPreMusic();
	void   setToBlueToothStopMusic();
	void   setToBlueToothPauseMusic();
	void   setToBlueToothPlayMusic();

	//MTK-Bt Init info
	void   analysMtkAppBtstatus(u8 *p,u8 len);
	void 	setToMTK_BlueToothToOtherModule_bt(u8 *p,u8 nLen);
	void 	getOtherModule_aboutBt_ToBtApp(U8 *p,u8 nLen);
	void seekFlyJniSdkTokeySdk(u8 p);
	void tuneFlyJniSdkTokeySdk(u8 p);
	void steeringWheelBtKeyFlyJniSdkTokeySdk(u8 p);

	void onBlueToothPhoneBookInfo(u8 *p,int len);
	void onBlueToothPhoneBookEndTag(u8 p);
	void setToBlueToothFromQujiaDial(u8 *p,int len);

	void setToBlueToothHundUpOrAnswer(u8 param);
	void mtkThirdPartyJumpSetPage(void);
	void setToBlueToothFromMtkDial(u8 *p,int len);
	void setToBlueToothFromHideBtPage(u8 p);
	void thirdPartyJumpSetPage(void);
	/*****************NEW PROTOCOL***********************/
	void analyseAppMessageType(u8 *p, u8 len);
	void analyseReturnStatusMassage(u8 *p, u8 len);
	void analyseControlBtOperationMassage(u8 *p, u8 len);
	void analyseSdkBtBasicInfo(u8 *p, u8 len);
	void analyseSdkBtPhoneBookInfo(u8 *p, u8 len);
	void sendToAppBtConnectStatus(u8 p);
	void sendToAppBtPhoneCallStatus(u8 p);
	void sendToAppPhoneBookLoadState(u8 p);

	void setToBtGetBtSwitchStatus();
	void setToBtGetBtConnectStatus();
	void setToBtGetBtPhoneCallStatus();
	void setToBtSetBtJumpToBtMainPage();
	void sendToAppPhoneBookInfo(u8 *p,int len);
	void setToBtGetBtPhoneBookInfo();
	void setToBtGetBtSongInfo(u8 param);
	void setToBtGetBtName(u8 param);
	void setToBtGetBtMusicStatus(u8 param);
	void setToBtGetBtRecetveSound(u8 param);
    void setToBtGetBtMicStatus(u8 param);

	
	void setToBlueToothFromDial(u8 *p,int len);
	
	void setToBtSetBtAccONorOFF(u8 p);
	void setToBtSetBtJumpToBtMusicPage(u8 p);
	void setToBtSetBtHangUp(u8 p);
	void setToBlueToothFromDialAndHideBtPage(u8 *p,int len);
	void setToBtSetBtJumpToBtDevicePage();
	void setToBtSetBtMusicPlay(u8 param);
	void setToBtSetBtPhoneCallStatus(u8 param);
};
