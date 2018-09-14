#pragma once
#include "BtAdapter.h"




class CBtApp;
class CBtHal;
class CBtAdapter;
class CBtParam;

class CBtBC6Adapter : public CBtAdapter
{
	SINGLETON_IMPLEMENT(CBtBC6Adapter)
private:
	CBtBC6Adapter(void);
public:
	virtual ~CBtBC6Adapter(void);

public:
	//初始化
	//void init(CBtHal *p);
	void init(CBtHal *p1,CBtApp *p2,CBtParam *p3);
	void deInit(void);
	bool hspAndHfpResponse(char *p, int len);//1.14 HSP HFP 应答
	bool a2dpAndAvrcpResponse(char *p, int len);//1.15 A2dp/Avrcp 应答
	bool phoneBookAndCallRecordResponse(char *p, int len);//1.16 电话本、通知记录应答
	bool sppVirtualSeriesResponse(char *p, int len);//1.17 SPP 虚拟串口 应答
	bool sdpBtSearchResponse(char *p, int len);//1.22 SDP 蓝牙搜索应答
	bool otherResponse(char *p, int len);//1.23 其他应答
	//请求指令
	void setToBtChipAtCmd(char *p, int len);
	//1.4 HSP/HFP 操作指令
	void setToBtChipStartPairMode(void);
	void setToBtChipEndPairMode(void);
	void setToBtChipConnectHFP(void);//连接最后一个配对设备
	void setToBtChipConnectHFP(int index);//连接配对列表<index>设备
	void setToBtChipConnectHFP(char *p, int len);//连接指定地址设备
	void setToBtChipDisConnectHFPAndA2DP(void);
	void setToBtChipAnswerCallIn(void);
	void setToBtChipRefuseCallIn(void);
	void setToBtChipHangUpCall(void);
	void setToBtChipReDial(void);
	void setToBtChipStartVoiceDial(void);
	void setToBtChipCancleVoiceDial(void);
	void setToBtChipMicrophoneOpenCloseSwitch(void);
	void setToBtChipVoiceDeviceSwitch(void);
	void setToBtChipVoiceSwitchToMobilePhone(void);
	void setToBtChipVoiceSwitchToBtChip(void);
	void setToBtChipVoiceSwitchToMicOpen(void);
	void setToBtChipVoiceSwitchToMicClose(void);
	void setToBtChipCtrlSpkVolume(int vol);
	void setToBtChipCtrlMicVolume(int vol);
	void setToBtChipCtrlGainData(void);
	void setToBtChipDialNum(char *p, int len);
	void setToBtChipDialNumMore(char *p, int len);//通话过程中再次拔号，比如分机号、自动语音服务等
	void setToBtChipQueryHfpStatus(void);
	void setToBtChipHandUpHandPhone(void);//挂断挂起中、等待中的电话
	void setToBtChipHangUpSpeakingAndReceiveAnother(void);//挂断当前电话，接听等待中的电话
	void setToBtChipHangSpeakingAndReceiveAnother(void);//挂起当前电话，接听挂起的电话
	void setToBtChipStartMobilePhoneMeeting(void);
	//1.5 A2DP 操作指令
	void setToBtChipMusicPlay(void);
	void setToBtChipMusicPause(void);
	void setToBtChipMusicStop(void);
	void setToBtChipNextSong(void);
	void setToBtChipPreSong(void);
	void setToBtChipQueryA2dpStatus(void);
	void setToBtChipQueryAvrcpStatus(void);
	void setToBtChipConnectAvDeviceRecently(void);
	void setToBtChipDisConnectA2DP(void);
	void setToBtChipFastForward(int index);//1 work, 0 stop
	void setToBtChipRewind(int index);//1 work, 0 stop
	void setToBtChipQueryA2dpInfo(void);//<歌曲名><歌手><时间><列号><总歌曲数量>
	void setToBtChipA2dpMusicMute(void);
	void setToBtChipA2dpMusicUnmute(void);
	//1.6 电话本、电话记录下载操作指令
	void setToBtChipSyncPhoneBookSIM(void);
	void setToBtChipSyncPhoneBookMobilePhone(void);
	void setToBtChipSyncHaveDialRecord(void);//同步手机内存中的已拨电话号码/本地保存
	void setToBtChipSyncHaveAnswerCallIn(void);//同步手机内存中的已接电话号码/本地保存
	void setToBtChipSyncMissAnswerCallIn(void);//同步手机内存中的未接电话号码/本地保存
	void setToBtChipLoadNextNItem(int n);
	void setToBtChipLoadPreNItem(int n);
	void setToBtChipLoadAllItem(void);
	void setToBtChipLoadStop(void);
	void setToBtChipAgreeOppRequestAndStartLoad(void);
	void setToBtChipRefuseOppRequest(void);
	void setToBtChipLoadPause(void);
	void setToBtChipLoadResume(void);
	//1.7 SPP 蓝牙虚拟串口指令
	void setToBtChipConnectSPP(char *p, int len);//
	void setToBtChipDisconnectSPP(void);
	void setToBtChipDisconnectSPP(char *p, int len);
	void setToBtChipQuerySppStatus(void);
	void setToBtChipQuerySppStatus(char *p, int len);
	//1.8 MAP 短信管理指令
	//1.9 HID 触摸操控指令
	//1.10 OPP/FTP 文件传输指令
	//1.11 PAN 网络连接指令
	//1.12 SDP 蓝牙搜索指令
	void setToBtChipStartSearchBtDevice(void);
	void setToBtChipStopSearchBtDevice(void);
	//void setToBtChipConnectSearchDevice(char *p, int len);
	//1.13 其它功能操作指令
	void setToBtChipResetBtChip(void);
	void setToBtChipEraseDevicePairRecord(int index);//清除指定设备配对记录
	void setToBtChipEraseDevicePairRecord(void);//清除所有配对记录
	void setToBtChipQueryBtChipVersion(void);
	void setToBtChipModifyBtChipName(char *p, int len);
	void setToBtChipQueryBtChipName(void);
	void setToBtChipModifyBtChipPairCode(char *p, int len);
	void setToBtChipQueryBtChipPairCode(void);
	void setToBtChipQueryLocalBtMacAddr(void);
	void setToBtChipQueryHavePairDevices(void);
	void setToBtChipQueryAutoPickupAndAutoReconnect(void);
	void setToBtChipSetAutoConnect(bool bState);
	void setToBtChipOpenAutoConnectAfterPowerOn(void);
	void setToBtChipCloseAutoConnectAfterPowerOn(void);
	void setToBtChipOpenAutoPickup(void);
	void setToBtChipCloseAutoPickup(void);
	void setToBtChipOpenBt(void);
	void setToBtChipCloseBt(void);
	void setToBtChipQueryCurConnectBtDeviceMacAddr(void);
	void setToBtChipQueryCurConnectBtDeviceName(void);
	void setToBtChipQuerySpkAndMicVolume(void);
	void setToBtChipQueryBatteryPowerAndSignalQuantity(void);
	void setToBtChipMicGain(char p);
	void setToBtChipQueryMicGainValue(void);
	
	int findCharIndex(unsigned char* p, int len, unsigned char d);
	int Inside_FindIndexFromStr(const u8 *pSrc, int nSrcLen, u8 cLetter, int nStart);

	void loadCallLog();
	void setToBtChipSyncAllCallLog(void);

	//BC8
	void analyseAnsCmd_(char *p, int len);
	void setToBtChipSetCurUsingWhichDevice(int index);
	void setToBtChipGetMusicBrowsingList(int nStart,int nEnd);
	void setToBtChipChangeMusicWhichListPath(int nLevel,char *msb,char *lsb);
	void setToBtChipSetWhichTheSong(char *msb,char *lsb);
	void setToBtChipIsSupportMusicBrowsing(void);
	void setToBtChipConnectedDeviceCounts(void);
	void setToBtChipVoiceSwitchToMicOpenBC8(void);
	void setToBtChipEraseDevicePairRecord_BC8(void);
	void setToBtChipStartPairMode_BC8(void);
	void setToBtChipEndPairMode_BC8(void);
	void setToBtChipAvConnect_BC8(void);
	void setToBtChipAvDisConnect_BC8(void);
	void TestsetToBtChipSetCurUsingWhichDevice(char *p, int len);
	void setWhetherTheBluetoothDeivceSupportsDualConnection(int index);
	void setSyncCallRecord(void);
	void setClearSyncCallRecord(void);
private:
	CBtHal *m_pBtHal;
	CBtApp *m_pBtApp;
	CBtParam *m_pBtParam;
};
