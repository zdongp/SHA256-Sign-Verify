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
	//��ʼ��
	//void init(CBtHal *p);
	void init(CBtHal *p1,CBtApp *p2,CBtParam *p3);
	void deInit(void);
	bool hspAndHfpResponse(char *p, int len);//1.14 HSP HFP Ӧ��
	bool a2dpAndAvrcpResponse(char *p, int len);//1.15 A2dp/Avrcp Ӧ��
	bool phoneBookAndCallRecordResponse(char *p, int len);//1.16 �绰����֪ͨ��¼Ӧ��
	bool sppVirtualSeriesResponse(char *p, int len);//1.17 SPP ���⴮�� Ӧ��
	bool sdpBtSearchResponse(char *p, int len);//1.22 SDP ��������Ӧ��
	bool otherResponse(char *p, int len);//1.23 ����Ӧ��
	//����ָ��
	void setToBtChipAtCmd(char *p, int len);
	//1.4 HSP/HFP ����ָ��
	void setToBtChipStartPairMode(void);
	void setToBtChipEndPairMode(void);
	void setToBtChipConnectHFP(void);//�������һ������豸
	void setToBtChipConnectHFP(int index);//��������б�<index>�豸
	void setToBtChipConnectHFP(char *p, int len);//����ָ����ַ�豸
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
	void setToBtChipDialNumMore(char *p, int len);//ͨ���������ٴΰκţ�����ֻ��š��Զ����������
	void setToBtChipQueryHfpStatus(void);
	void setToBtChipHandUpHandPhone(void);//�ҶϹ����С��ȴ��еĵ绰
	void setToBtChipHangUpSpeakingAndReceiveAnother(void);//�Ҷϵ�ǰ�绰�������ȴ��еĵ绰
	void setToBtChipHangSpeakingAndReceiveAnother(void);//����ǰ�绰����������ĵ绰
	void setToBtChipStartMobilePhoneMeeting(void);
	//1.5 A2DP ����ָ��
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
	void setToBtChipQueryA2dpInfo(void);//<������><����><ʱ��><�к�><�ܸ�������>
	void setToBtChipA2dpMusicMute(void);
	void setToBtChipA2dpMusicUnmute(void);
	//1.6 �绰�����绰��¼���ز���ָ��
	void setToBtChipSyncPhoneBookSIM(void);
	void setToBtChipSyncPhoneBookMobilePhone(void);
	void setToBtChipSyncHaveDialRecord(void);//ͬ���ֻ��ڴ��е��Ѳ��绰����/���ر���
	void setToBtChipSyncHaveAnswerCallIn(void);//ͬ���ֻ��ڴ��е��ѽӵ绰����/���ر���
	void setToBtChipSyncMissAnswerCallIn(void);//ͬ���ֻ��ڴ��е�δ�ӵ绰����/���ر���
	void setToBtChipLoadNextNItem(int n);
	void setToBtChipLoadPreNItem(int n);
	void setToBtChipLoadAllItem(void);
	void setToBtChipLoadStop(void);
	void setToBtChipAgreeOppRequestAndStartLoad(void);
	void setToBtChipRefuseOppRequest(void);
	void setToBtChipLoadPause(void);
	void setToBtChipLoadResume(void);
	//1.7 SPP �������⴮��ָ��
	void setToBtChipConnectSPP(char *p, int len);//
	void setToBtChipDisconnectSPP(void);
	void setToBtChipDisconnectSPP(char *p, int len);
	void setToBtChipQuerySppStatus(void);
	void setToBtChipQuerySppStatus(char *p, int len);
	//1.8 MAP ���Ź���ָ��
	//1.9 HID �����ٿ�ָ��
	//1.10 OPP/FTP �ļ�����ָ��
	//1.11 PAN ��������ָ��
	//1.12 SDP ��������ָ��
	void setToBtChipStartSearchBtDevice(void);
	void setToBtChipStopSearchBtDevice(void);
	//void setToBtChipConnectSearchDevice(char *p, int len);
	//1.13 �������ܲ���ָ��
	void setToBtChipResetBtChip(void);
	void setToBtChipEraseDevicePairRecord(int index);//���ָ���豸��Լ�¼
	void setToBtChipEraseDevicePairRecord(void);//���������Լ�¼
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
