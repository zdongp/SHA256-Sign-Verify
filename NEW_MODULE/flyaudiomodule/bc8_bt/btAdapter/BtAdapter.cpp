#include "BtAdapter.h"

CBtAdapter::CBtAdapter(void)
{
}

CBtAdapter::~CBtAdapter(void)
{
}

bool CBtAdapter::hspAndHfpResponse(char *p, int len){return true;}//1.14 HSP HFP 应答
bool CBtAdapter::a2dpAndAvrcpResponse(char *p, int len){return true;}//1.15 A2dp/Avrcp 应答
bool CBtAdapter::phoneBookAndCallRecordResponse(char *p, int len){return true;}//1.16 电话本、通知记录应答
bool CBtAdapter::sppVirtualSeriesResponse(char *p, int len){return true;}//1.17 SPP 虚拟串口 应答
bool CBtAdapter::sdpBtSearchResponse(char *p, int len){return true;}//1.22 SDP 蓝牙搜索应答
bool CBtAdapter::otherResponse(char *p, int len){return true;}//1.23 其他应答
//请求指令
void CBtAdapter::setToBtChipAtCmd(char *p, int len){}
//1.4 HSP/HFP 操作指令
void CBtAdapter::setToBtChipStartPairMode(void){}//进入配对模式
void CBtAdapter::setToBtChipEndPairMode(void){}//退出配对模式
void CBtAdapter::setToBtChipConnectHFP(void){}//连接最后一个配对设备
void CBtAdapter::setToBtChipConnectHFP(int index){}//连接配对列表<index>设备
void CBtAdapter::setToBtChipConnectHFP(char *p, int len){}//连接指定地址设备
void CBtAdapter::setToBtChipDisConnectHFPAndA2DP(void){}//断开HFP和A2DP
void CBtAdapter::setToBtChipAnswerCallIn(void){}//接听来电
void CBtAdapter::setToBtChipRefuseCallIn(void){}//拒接来电
void CBtAdapter::setToBtChipHangUpCall(void){}//挂断电话
void CBtAdapter::setToBtChipReDial(void){}//重拨
void CBtAdapter::setToBtChipStartVoiceDial(void){}//开始语音拨号
void CBtAdapter::setToBtChipCancleVoiceDial(void){}//取消语音拨号
void CBtAdapter::setToBtChipMicrophoneOpenCloseSwitch(void){}//麦克风打开/关闭
void CBtAdapter::setToBtChipVoiceDeviceSwitch(void){}//音频切换
void CBtAdapter::setToBtChipVoiceSwitchToMobilePhone(void){}//音频切换到手机
void CBtAdapter::setToBtChipVoiceSwitchToBtChip(void){}//音频切换到蓝牙
void CBtAdapter::setToBtChipCtrlSpkVolume(int vol){}//调节蓝牙SPK音量
void CBtAdapter::setToBtChipCtrlMicVolume(int vol){}//调节蓝牙MIC音量
void CBtAdapter::setToBtChipCtrlGainData(void){}

void CBtAdapter::setToBtChipDialNum(char *p, int len){}//拨打电话
void CBtAdapter::setToBtChipDialNumMore(char *p, int len){}//通话过程中再次拔号，比如分机号、自动语音服务等
void CBtAdapter::setToBtChipQueryHfpStatus(void){}//查询HFP状态
void CBtAdapter::setToBtChipHandUpHandPhone(void){}//挂断挂起中、等待中的电话
void CBtAdapter::setToBtChipHangUpSpeakingAndReceiveAnother(void){}//挂断当前电话，接听等待中的电话
void CBtAdapter::setToBtChipHangSpeakingAndReceiveAnother(void){}//挂起当前电话，接听挂起的电话
void CBtAdapter::setToBtChipStartMobilePhoneMeeting(void){}//开始电话会议 
//1.5 A2DP 操作指令
void CBtAdapter::setToBtChipMusicPlay(void){}//音乐播放
void CBtAdapter::setToBtChipMusicPause(void){}//音乐暂停 
void CBtAdapter::setToBtChipMusicStop(void){}//停止音乐 
void CBtAdapter::setToBtChipNextSong(void){}//下一曲
void CBtAdapter::setToBtChipPreSong(void){}//上一曲
void CBtAdapter::setToBtChipQueryA2dpStatus(void){}//查询 A2DP 状态 
void CBtAdapter::setToBtChipQueryAvrcpStatus(void){}//查询 AVRCP 状态 
void CBtAdapter::setToBtChipConnectAvDeviceRecently(void){}//连接最近一次连接过的AV设备 
void CBtAdapter::setToBtChipDisConnectA2DP(void){}//断开 A2DP 连接 
void CBtAdapter::setToBtChipFastForward(int index){}//1 work, 0 stop
void CBtAdapter::setToBtChipRewind(int index){}//1 work, 0 stop
void CBtAdapter::setToBtChipQueryA2dpInfo(void){}//<歌曲名><歌手><时间><列号><总歌曲数量>
void CBtAdapter::setToBtChipA2dpMusicMute(void){}
void CBtAdapter::setToBtChipA2dpMusicUnmute(void){}

//1.6 电话本、电话记录下载操作指令
void CBtAdapter::setToBtChipSyncPhoneBookSIM(void){}//同步电话本（SIM）
void CBtAdapter::setToBtChipSyncPhoneBookMobilePhone(void){}//同步电话本（手机）
void CBtAdapter::setToBtChipSyncHaveDialRecord(void){}//同步手机内存中的已拨电话号码/本地保存
void CBtAdapter::setToBtChipSyncHaveAnswerCallIn(void){}//同步手机内存中的已接电话号码/本地保存
void CBtAdapter::setToBtChipSyncMissAnswerCallIn(void){}//同步手机内存中的未接电话号码/本地保存
void CBtAdapter::setToBtChipLoadNextNItem(int n){}//向下读取n个条目
void CBtAdapter::setToBtChipLoadPreNItem(int n){}//向上读取n个条目
void CBtAdapter::setToBtChipLoadAllItem(void){}//下载全部条目
void CBtAdapter::setToBtChipLoadStop(void){}//停止下载
void CBtAdapter::setToBtChipAgreeOppRequestAndStartLoad(void){}//同意 OPP 请求并开始下载
void CBtAdapter::setToBtChipRefuseOppRequest(void){}//拒绝 OPP 请求
void CBtAdapter::setToBtChipLoadPause(void){}//暂停下载
void CBtAdapter::setToBtChipLoadResume(void){}//继续下载
//1.7 SPP 蓝牙虚拟串口指令
void CBtAdapter::setToBtChipConnectSPP(char *p, int len){}//连接指定地址 spp
void CBtAdapter::setToBtChipDisconnectSPP(void){}//断开所有 spp 地址
void CBtAdapter::setToBtChipDisconnectSPP(char *p, int len){}//断开指定地址连接
void CBtAdapter::setToBtChipQuerySppStatus(void){}//查询所有 spp 通道
void CBtAdapter::setToBtChipQuerySppStatus(char *p, int len){}//查询指定地址状态
//1.8 MAP 短信管理指令
//1.9 HID 触摸操控指令
//1.10 OPP/FTP 文件传输指令
//1.11 PAN 网络连接指令
//1.12 SDP 蓝牙搜索指令
void CBtAdapter::setToBtChipStartSearchBtDevice(void){}//搜索蓝牙设备
void CBtAdapter::setToBtChipStopSearchBtDevice(void){}//停止搜索蓝牙设备
void CBtAdapter::setToBtChipConnectSearchDevice(char *p, int len){}//连接搜索设备
//1.13 其它功能操作指令
void CBtAdapter::setToBtChipResetBtChip(void){}//复位模块
void CBtAdapter::setToBtChipEraseDevicePairRecord(int index){}//清除指定设备配对记录
void CBtAdapter::setToBtChipEraseDevicePairRecord(void){}//清除所有配对记录
void CBtAdapter::setToBtChipQueryBtChipVersion(void){}//查询模块版本号
void CBtAdapter::setToBtChipModifyBtChipName(char *p, int len){}//修改设备名
void CBtAdapter::setToBtChipQueryBtChipName(void){}//查询当前设备名
void CBtAdapter::setToBtChipModifyBtChipPairCode(char *p, int len){}//修改配对码
void CBtAdapter::setToBtChipQueryBtChipPairCode(void){}//查询当前配对码
void CBtAdapter::setToBtChipQueryLocalBtMacAddr(void){}//查询本地蓝牙地址
void CBtAdapter::setToBtChipQueryHavePairDevices(void){}//查询与模块已配对过的设备列表
void CBtAdapter::setToBtChipQueryAutoPickupAndAutoReconnect(void){}//查询来电自动接听/模块上电自动重连设置
void CBtAdapter::setToBtChipOpenAutoConnectAfterPowerOn(void){}//开启上电自动重连
void CBtAdapter::setToBtChipCloseAutoConnectAfterPowerOn(void){}//关闭上电自动重连
void CBtAdapter::setToBtChipOpenAutoPickup(void){}//开启来电自动接听
void CBtAdapter::setToBtChipCloseAutoPickup(void){}//关闭来电自动接听
void CBtAdapter::setToBtChipOpenBt(void){}//打开蓝牙
void CBtAdapter::setToBtChipCloseBt(void){}//关闭蓝牙
void CBtAdapter::setToBtChipQueryCurConnectBtDeviceMacAddr(void){}//查询当前连接设备的蓝牙地址
void CBtAdapter::setToBtChipQueryCurConnectBtDeviceName(void){}//查询当前连接设备的蓝牙名字
void CBtAdapter::setToBtChipQuerySpkAndMicVolume(void){}//查询 SPK 及 MIC 音量
void CBtAdapter::setToBtChipQueryBatteryPowerAndSignalQuantity(void){}//查询电池/信号量
void CBtAdapter::setToBtChipMicGain(char p){}
void CBtAdapter::setToBtChipQueryMicGainValue(void){}

void CBtAdapter::outPutUtf8StringToTerminal(char *p, int len)
{
	char szDebug[128] = {0};

	if (len >= 128)
		len = 127;

	memcpy(szDebug, p, len);
}
