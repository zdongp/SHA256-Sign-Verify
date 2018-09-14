#pragma once

#include "FlyObject.h"
#include "BtDefine.h"

class CBtHal;
class CBtApp;
class CBtParam;

class CBtAdapter
{
public:
	CBtAdapter(void);
	virtual ~CBtAdapter(void);

public:
	//初始化
	//virtual void init(CBtHal *p) = 0;
	virtual void init(CBtHal *p1,CBtApp *p2,CBtParam *p3)=0;
	virtual void deInit(void) = 0;
	virtual bool hspAndHfpResponse(char *p, int len);//1.14 HSP HFP 应答
	virtual bool a2dpAndAvrcpResponse(char *p, int len);//1.15 A2dp/Avrcp 应答
	virtual bool phoneBookAndCallRecordResponse(char *p, int len);//1.16 电话本、通知记录应答
	virtual bool sppVirtualSeriesResponse(char *p, int len);//1.17 SPP 虚拟串口 应答
	virtual bool sdpBtSearchResponse(char *p, int len);//1.22 SDP 蓝牙搜索应答
	virtual bool otherResponse(char *p, int len);//1.23 其他应答
	//请求指令
	virtual void setToBtChipAtCmd(char *p, int len);
	//1.4 HSP/HFP 操作指令
	virtual void setToBtChipStartPairMode(void);//进入配对模式
	virtual void setToBtChipEndPairMode(void);//退出配对模式
	virtual void setToBtChipConnectHFP(void);//连接最后一个配对设备
	virtual void setToBtChipConnectHFP(int index);//连接配对列表<index>设备
	virtual void setToBtChipConnectHFP(char *p, int len);//连接指定地址设备
	virtual void setToBtChipDisConnectHFPAndA2DP(void);//断开HFP和A2DP
	virtual void setToBtChipAnswerCallIn(void);//接听来电
	virtual void setToBtChipRefuseCallIn(void);//拒接来电
	virtual void setToBtChipHangUpCall(void);//挂断电话
	virtual void setToBtChipReDial(void);//重拨
	virtual void setToBtChipStartVoiceDial(void);//开始语音拨号
	virtual void setToBtChipCancleVoiceDial(void);//取消语音拨号
	virtual void setToBtChipMicrophoneOpenCloseSwitch(void);//麦克风打开/关闭
	virtual void setToBtChipVoiceDeviceSwitch(void);//音频切换
	virtual void setToBtChipVoiceSwitchToMobilePhone(void);//音频切换到手机
	virtual void setToBtChipVoiceSwitchToBtChip(void);//音频切换到蓝牙
	virtual void setToBtChipCtrlSpkVolume(int vol);//调节蓝牙SPK音量
	virtual void setToBtChipCtrlMicVolume(int vol);//调节蓝牙MIC音量
	virtual void setToBtChipCtrlGainData(void);
	virtual void setToBtChipDialNum(char *p, int len);//拨打电话
	virtual void setToBtChipDialNumMore(char *p, int len);//通话过程中再次拔号，比如分机号、自动语音服务等
	virtual void setToBtChipQueryHfpStatus(void);//查询HFP状态
	virtual void setToBtChipHandUpHandPhone(void);//挂断挂起中、等待中的电话
	virtual void setToBtChipHangUpSpeakingAndReceiveAnother(void);//挂断当前电话，接听等待中的电话
	virtual void setToBtChipHangSpeakingAndReceiveAnother(void);//挂起当前电话，接听挂起的电话
	virtual void setToBtChipStartMobilePhoneMeeting(void);//开始电话会议 
	//1.5 A2DP 操作指令
	virtual void setToBtChipMusicPlay(void);//音乐播放
	virtual void setToBtChipMusicPause(void);//音乐暂停 
	virtual void setToBtChipMusicStop(void);//停止音乐 
	virtual void setToBtChipNextSong(void);//下一曲
	virtual void setToBtChipPreSong(void);//上一曲
	virtual void setToBtChipQueryA2dpStatus(void);//查询 A2DP 状态 
	virtual void setToBtChipQueryAvrcpStatus(void);//查询 AVRCP 状态 
	virtual void setToBtChipConnectAvDeviceRecently(void);//连接最近一次连接过的AV设备 
	virtual void setToBtChipDisConnectA2DP(void);//断开 A2DP 连接 
	virtual void setToBtChipFastForward(int index);//1 work, 0 stop
	virtual void setToBtChipRewind(int index);//1 work, 0 stop
	virtual void setToBtChipQueryA2dpInfo(void);//<歌曲名><歌手><时间><列号><总歌曲数量>
	virtual void setToBtChipA2dpMusicMute(void);
	virtual void setToBtChipA2dpMusicUnmute(void);
	//1.6 电话本、电话记录下载操作指令
	virtual void setToBtChipSyncPhoneBookSIM(void);//同步电话本（SIM）
	virtual void setToBtChipSyncPhoneBookMobilePhone(void);//同步电话本（手机）
	virtual void setToBtChipSyncHaveDialRecord(void);//同步手机内存中的已拨电话号码/本地保存
	virtual void setToBtChipSyncHaveAnswerCallIn(void);//同步手机内存中的已接电话号码/本地保存
	virtual void setToBtChipSyncMissAnswerCallIn(void);//同步手机内存中的未接电话号码/本地保存
	virtual void setToBtChipLoadNextNItem(int n);//向下读取n个条目
	virtual void setToBtChipLoadPreNItem(int n);//向上读取n个条目
	virtual void setToBtChipLoadAllItem(void);//下载全部条目
	virtual void setToBtChipLoadStop(void);//停止下载
	virtual void setToBtChipAgreeOppRequestAndStartLoad(void);//同意 OPP 请求并开始下载
	virtual void setToBtChipRefuseOppRequest(void);//拒绝 OPP 请求
	virtual void setToBtChipLoadPause(void);//暂停下载
	virtual void setToBtChipLoadResume(void);//继续下载
	//1.7 SPP 蓝牙虚拟串口指令
	virtual void setToBtChipConnectSPP(char *p, int len);//连接指定地址 spp
	virtual void setToBtChipDisconnectSPP(void);//断开所有 spp 地址
	virtual void setToBtChipDisconnectSPP(char *p, int len);//断开指定地址连接
	virtual void setToBtChipQuerySppStatus(void);//查询所有 spp 通道
	virtual void setToBtChipQuerySppStatus(char *p, int len);//查询指定地址状态
	//1.8 MAP 短信管理指令
	//1.9 HID 触摸操控指令
	//1.10 OPP/FTP 文件传输指令
	//1.11 PAN 网络连接指令
	//1.12 SDP 蓝牙搜索指令
	virtual void setToBtChipStartSearchBtDevice(void);//搜索蓝牙设备
	virtual void setToBtChipStopSearchBtDevice(void);//停止搜索蓝牙设备
	virtual void setToBtChipConnectSearchDevice(char *p, int len);//连接搜索设备
	//1.13 其它功能操作指令
	virtual void setToBtChipResetBtChip(void);//复位模块
	virtual void setToBtChipEraseDevicePairRecord(int index);//清除指定设备配对记录
	virtual void setToBtChipEraseDevicePairRecord(void);//清除所有配对记录
	virtual void setToBtChipQueryBtChipVersion(void);//查询模块版本号
	virtual void setToBtChipModifyBtChipName(char *p, int len);//修改设备名
	virtual void setToBtChipQueryBtChipName(void);//查询当前设备名
	virtual void setToBtChipModifyBtChipPairCode(char *p, int len);//修改配对码
	virtual void setToBtChipQueryBtChipPairCode(void);//查询当前配对码
	virtual void setToBtChipQueryLocalBtMacAddr(void);//查询本地蓝牙地址
	virtual void setToBtChipQueryHavePairDevices(void);//查询与模块已配对过的设备列表
	virtual void setToBtChipQueryAutoPickupAndAutoReconnect(void);//查询来电自动接听/模块上电自动重连设置
	virtual void setToBtChipOpenAutoConnectAfterPowerOn(void);//开启上电自动重连
	virtual void setToBtChipCloseAutoConnectAfterPowerOn(void);//关闭上电自动重连
	virtual void setToBtChipOpenAutoPickup(void);//开启来电自动接听
	virtual void setToBtChipCloseAutoPickup(void);//关闭来电自动接听
	virtual void setToBtChipOpenBt(void);//打开蓝牙
	virtual void setToBtChipCloseBt(void);//关闭蓝牙
	virtual void setToBtChipQueryCurConnectBtDeviceMacAddr(void);//查询当前连接设备的蓝牙地址
	virtual void setToBtChipQueryCurConnectBtDeviceName(void);//查询当前连接设备的蓝牙名字
	virtual void setToBtChipQuerySpkAndMicVolume(void);//查询 SPK 及 MIC 音量
	virtual void setToBtChipQueryBatteryPowerAndSignalQuantity(void);//查询电池/信号量
	virtual void setToBtChipMicGain(char p);
	virtual void setToBtChipQueryMicGainValue(void);
	//assist
	void outPutUtf8StringToTerminal(char *p, int len);
};
