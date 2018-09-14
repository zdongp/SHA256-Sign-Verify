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
	//��ʼ��
	//virtual void init(CBtHal *p) = 0;
	virtual void init(CBtHal *p1,CBtApp *p2,CBtParam *p3)=0;
	virtual void deInit(void) = 0;
	virtual bool hspAndHfpResponse(char *p, int len);//1.14 HSP HFP Ӧ��
	virtual bool a2dpAndAvrcpResponse(char *p, int len);//1.15 A2dp/Avrcp Ӧ��
	virtual bool phoneBookAndCallRecordResponse(char *p, int len);//1.16 �绰����֪ͨ��¼Ӧ��
	virtual bool sppVirtualSeriesResponse(char *p, int len);//1.17 SPP ���⴮�� Ӧ��
	virtual bool sdpBtSearchResponse(char *p, int len);//1.22 SDP ��������Ӧ��
	virtual bool otherResponse(char *p, int len);//1.23 ����Ӧ��
	//����ָ��
	virtual void setToBtChipAtCmd(char *p, int len);
	//1.4 HSP/HFP ����ָ��
	virtual void setToBtChipStartPairMode(void);//�������ģʽ
	virtual void setToBtChipEndPairMode(void);//�˳����ģʽ
	virtual void setToBtChipConnectHFP(void);//�������һ������豸
	virtual void setToBtChipConnectHFP(int index);//��������б�<index>�豸
	virtual void setToBtChipConnectHFP(char *p, int len);//����ָ����ַ�豸
	virtual void setToBtChipDisConnectHFPAndA2DP(void);//�Ͽ�HFP��A2DP
	virtual void setToBtChipAnswerCallIn(void);//��������
	virtual void setToBtChipRefuseCallIn(void);//�ܽ�����
	virtual void setToBtChipHangUpCall(void);//�Ҷϵ绰
	virtual void setToBtChipReDial(void);//�ز�
	virtual void setToBtChipStartVoiceDial(void);//��ʼ��������
	virtual void setToBtChipCancleVoiceDial(void);//ȡ����������
	virtual void setToBtChipMicrophoneOpenCloseSwitch(void);//��˷��/�ر�
	virtual void setToBtChipVoiceDeviceSwitch(void);//��Ƶ�л�
	virtual void setToBtChipVoiceSwitchToMobilePhone(void);//��Ƶ�л����ֻ�
	virtual void setToBtChipVoiceSwitchToBtChip(void);//��Ƶ�л�������
	virtual void setToBtChipCtrlSpkVolume(int vol);//��������SPK����
	virtual void setToBtChipCtrlMicVolume(int vol);//��������MIC����
	virtual void setToBtChipCtrlGainData(void);
	virtual void setToBtChipDialNum(char *p, int len);//����绰
	virtual void setToBtChipDialNumMore(char *p, int len);//ͨ���������ٴΰκţ�����ֻ��š��Զ����������
	virtual void setToBtChipQueryHfpStatus(void);//��ѯHFP״̬
	virtual void setToBtChipHandUpHandPhone(void);//�ҶϹ����С��ȴ��еĵ绰
	virtual void setToBtChipHangUpSpeakingAndReceiveAnother(void);//�Ҷϵ�ǰ�绰�������ȴ��еĵ绰
	virtual void setToBtChipHangSpeakingAndReceiveAnother(void);//����ǰ�绰����������ĵ绰
	virtual void setToBtChipStartMobilePhoneMeeting(void);//��ʼ�绰���� 
	//1.5 A2DP ����ָ��
	virtual void setToBtChipMusicPlay(void);//���ֲ���
	virtual void setToBtChipMusicPause(void);//������ͣ 
	virtual void setToBtChipMusicStop(void);//ֹͣ���� 
	virtual void setToBtChipNextSong(void);//��һ��
	virtual void setToBtChipPreSong(void);//��һ��
	virtual void setToBtChipQueryA2dpStatus(void);//��ѯ A2DP ״̬ 
	virtual void setToBtChipQueryAvrcpStatus(void);//��ѯ AVRCP ״̬ 
	virtual void setToBtChipConnectAvDeviceRecently(void);//�������һ�����ӹ���AV�豸 
	virtual void setToBtChipDisConnectA2DP(void);//�Ͽ� A2DP ���� 
	virtual void setToBtChipFastForward(int index);//1 work, 0 stop
	virtual void setToBtChipRewind(int index);//1 work, 0 stop
	virtual void setToBtChipQueryA2dpInfo(void);//<������><����><ʱ��><�к�><�ܸ�������>
	virtual void setToBtChipA2dpMusicMute(void);
	virtual void setToBtChipA2dpMusicUnmute(void);
	//1.6 �绰�����绰��¼���ز���ָ��
	virtual void setToBtChipSyncPhoneBookSIM(void);//ͬ���绰����SIM��
	virtual void setToBtChipSyncPhoneBookMobilePhone(void);//ͬ���绰�����ֻ���
	virtual void setToBtChipSyncHaveDialRecord(void);//ͬ���ֻ��ڴ��е��Ѳ��绰����/���ر���
	virtual void setToBtChipSyncHaveAnswerCallIn(void);//ͬ���ֻ��ڴ��е��ѽӵ绰����/���ر���
	virtual void setToBtChipSyncMissAnswerCallIn(void);//ͬ���ֻ��ڴ��е�δ�ӵ绰����/���ر���
	virtual void setToBtChipLoadNextNItem(int n);//���¶�ȡn����Ŀ
	virtual void setToBtChipLoadPreNItem(int n);//���϶�ȡn����Ŀ
	virtual void setToBtChipLoadAllItem(void);//����ȫ����Ŀ
	virtual void setToBtChipLoadStop(void);//ֹͣ����
	virtual void setToBtChipAgreeOppRequestAndStartLoad(void);//ͬ�� OPP ���󲢿�ʼ����
	virtual void setToBtChipRefuseOppRequest(void);//�ܾ� OPP ����
	virtual void setToBtChipLoadPause(void);//��ͣ����
	virtual void setToBtChipLoadResume(void);//��������
	//1.7 SPP �������⴮��ָ��
	virtual void setToBtChipConnectSPP(char *p, int len);//����ָ����ַ spp
	virtual void setToBtChipDisconnectSPP(void);//�Ͽ����� spp ��ַ
	virtual void setToBtChipDisconnectSPP(char *p, int len);//�Ͽ�ָ����ַ����
	virtual void setToBtChipQuerySppStatus(void);//��ѯ���� spp ͨ��
	virtual void setToBtChipQuerySppStatus(char *p, int len);//��ѯָ����ַ״̬
	//1.8 MAP ���Ź���ָ��
	//1.9 HID �����ٿ�ָ��
	//1.10 OPP/FTP �ļ�����ָ��
	//1.11 PAN ��������ָ��
	//1.12 SDP ��������ָ��
	virtual void setToBtChipStartSearchBtDevice(void);//���������豸
	virtual void setToBtChipStopSearchBtDevice(void);//ֹͣ���������豸
	virtual void setToBtChipConnectSearchDevice(char *p, int len);//���������豸
	//1.13 �������ܲ���ָ��
	virtual void setToBtChipResetBtChip(void);//��λģ��
	virtual void setToBtChipEraseDevicePairRecord(int index);//���ָ���豸��Լ�¼
	virtual void setToBtChipEraseDevicePairRecord(void);//���������Լ�¼
	virtual void setToBtChipQueryBtChipVersion(void);//��ѯģ��汾��
	virtual void setToBtChipModifyBtChipName(char *p, int len);//�޸��豸��
	virtual void setToBtChipQueryBtChipName(void);//��ѯ��ǰ�豸��
	virtual void setToBtChipModifyBtChipPairCode(char *p, int len);//�޸������
	virtual void setToBtChipQueryBtChipPairCode(void);//��ѯ��ǰ�����
	virtual void setToBtChipQueryLocalBtMacAddr(void);//��ѯ����������ַ
	virtual void setToBtChipQueryHavePairDevices(void);//��ѯ��ģ������Թ����豸�б�
	virtual void setToBtChipQueryAutoPickupAndAutoReconnect(void);//��ѯ�����Զ�����/ģ���ϵ��Զ���������
	virtual void setToBtChipOpenAutoConnectAfterPowerOn(void);//�����ϵ��Զ�����
	virtual void setToBtChipCloseAutoConnectAfterPowerOn(void);//�ر��ϵ��Զ�����
	virtual void setToBtChipOpenAutoPickup(void);//���������Զ�����
	virtual void setToBtChipCloseAutoPickup(void);//�ر������Զ�����
	virtual void setToBtChipOpenBt(void);//������
	virtual void setToBtChipCloseBt(void);//�ر�����
	virtual void setToBtChipQueryCurConnectBtDeviceMacAddr(void);//��ѯ��ǰ�����豸��������ַ
	virtual void setToBtChipQueryCurConnectBtDeviceName(void);//��ѯ��ǰ�����豸����������
	virtual void setToBtChipQuerySpkAndMicVolume(void);//��ѯ SPK �� MIC ����
	virtual void setToBtChipQueryBatteryPowerAndSignalQuantity(void);//��ѯ���/�ź���
	virtual void setToBtChipMicGain(char p);
	virtual void setToBtChipQueryMicGainValue(void);
	//assist
	void outPutUtf8StringToTerminal(char *p, int len);
};
