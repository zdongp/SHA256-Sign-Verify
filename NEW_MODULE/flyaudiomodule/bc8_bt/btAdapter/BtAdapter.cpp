#include "BtAdapter.h"

CBtAdapter::CBtAdapter(void)
{
}

CBtAdapter::~CBtAdapter(void)
{
}

bool CBtAdapter::hspAndHfpResponse(char *p, int len){return true;}//1.14 HSP HFP Ӧ��
bool CBtAdapter::a2dpAndAvrcpResponse(char *p, int len){return true;}//1.15 A2dp/Avrcp Ӧ��
bool CBtAdapter::phoneBookAndCallRecordResponse(char *p, int len){return true;}//1.16 �绰����֪ͨ��¼Ӧ��
bool CBtAdapter::sppVirtualSeriesResponse(char *p, int len){return true;}//1.17 SPP ���⴮�� Ӧ��
bool CBtAdapter::sdpBtSearchResponse(char *p, int len){return true;}//1.22 SDP ��������Ӧ��
bool CBtAdapter::otherResponse(char *p, int len){return true;}//1.23 ����Ӧ��
//����ָ��
void CBtAdapter::setToBtChipAtCmd(char *p, int len){}
//1.4 HSP/HFP ����ָ��
void CBtAdapter::setToBtChipStartPairMode(void){}//�������ģʽ
void CBtAdapter::setToBtChipEndPairMode(void){}//�˳����ģʽ
void CBtAdapter::setToBtChipConnectHFP(void){}//�������һ������豸
void CBtAdapter::setToBtChipConnectHFP(int index){}//��������б�<index>�豸
void CBtAdapter::setToBtChipConnectHFP(char *p, int len){}//����ָ����ַ�豸
void CBtAdapter::setToBtChipDisConnectHFPAndA2DP(void){}//�Ͽ�HFP��A2DP
void CBtAdapter::setToBtChipAnswerCallIn(void){}//��������
void CBtAdapter::setToBtChipRefuseCallIn(void){}//�ܽ�����
void CBtAdapter::setToBtChipHangUpCall(void){}//�Ҷϵ绰
void CBtAdapter::setToBtChipReDial(void){}//�ز�
void CBtAdapter::setToBtChipStartVoiceDial(void){}//��ʼ��������
void CBtAdapter::setToBtChipCancleVoiceDial(void){}//ȡ����������
void CBtAdapter::setToBtChipMicrophoneOpenCloseSwitch(void){}//��˷��/�ر�
void CBtAdapter::setToBtChipVoiceDeviceSwitch(void){}//��Ƶ�л�
void CBtAdapter::setToBtChipVoiceSwitchToMobilePhone(void){}//��Ƶ�л����ֻ�
void CBtAdapter::setToBtChipVoiceSwitchToBtChip(void){}//��Ƶ�л�������
void CBtAdapter::setToBtChipCtrlSpkVolume(int vol){}//��������SPK����
void CBtAdapter::setToBtChipCtrlMicVolume(int vol){}//��������MIC����
void CBtAdapter::setToBtChipCtrlGainData(void){}

void CBtAdapter::setToBtChipDialNum(char *p, int len){}//����绰
void CBtAdapter::setToBtChipDialNumMore(char *p, int len){}//ͨ���������ٴΰκţ�����ֻ��š��Զ����������
void CBtAdapter::setToBtChipQueryHfpStatus(void){}//��ѯHFP״̬
void CBtAdapter::setToBtChipHandUpHandPhone(void){}//�ҶϹ����С��ȴ��еĵ绰
void CBtAdapter::setToBtChipHangUpSpeakingAndReceiveAnother(void){}//�Ҷϵ�ǰ�绰�������ȴ��еĵ绰
void CBtAdapter::setToBtChipHangSpeakingAndReceiveAnother(void){}//����ǰ�绰����������ĵ绰
void CBtAdapter::setToBtChipStartMobilePhoneMeeting(void){}//��ʼ�绰���� 
//1.5 A2DP ����ָ��
void CBtAdapter::setToBtChipMusicPlay(void){}//���ֲ���
void CBtAdapter::setToBtChipMusicPause(void){}//������ͣ 
void CBtAdapter::setToBtChipMusicStop(void){}//ֹͣ���� 
void CBtAdapter::setToBtChipNextSong(void){}//��һ��
void CBtAdapter::setToBtChipPreSong(void){}//��һ��
void CBtAdapter::setToBtChipQueryA2dpStatus(void){}//��ѯ A2DP ״̬ 
void CBtAdapter::setToBtChipQueryAvrcpStatus(void){}//��ѯ AVRCP ״̬ 
void CBtAdapter::setToBtChipConnectAvDeviceRecently(void){}//�������һ�����ӹ���AV�豸 
void CBtAdapter::setToBtChipDisConnectA2DP(void){}//�Ͽ� A2DP ���� 
void CBtAdapter::setToBtChipFastForward(int index){}//1 work, 0 stop
void CBtAdapter::setToBtChipRewind(int index){}//1 work, 0 stop
void CBtAdapter::setToBtChipQueryA2dpInfo(void){}//<������><����><ʱ��><�к�><�ܸ�������>
void CBtAdapter::setToBtChipA2dpMusicMute(void){}
void CBtAdapter::setToBtChipA2dpMusicUnmute(void){}

//1.6 �绰�����绰��¼���ز���ָ��
void CBtAdapter::setToBtChipSyncPhoneBookSIM(void){}//ͬ���绰����SIM��
void CBtAdapter::setToBtChipSyncPhoneBookMobilePhone(void){}//ͬ���绰�����ֻ���
void CBtAdapter::setToBtChipSyncHaveDialRecord(void){}//ͬ���ֻ��ڴ��е��Ѳ��绰����/���ر���
void CBtAdapter::setToBtChipSyncHaveAnswerCallIn(void){}//ͬ���ֻ��ڴ��е��ѽӵ绰����/���ر���
void CBtAdapter::setToBtChipSyncMissAnswerCallIn(void){}//ͬ���ֻ��ڴ��е�δ�ӵ绰����/���ر���
void CBtAdapter::setToBtChipLoadNextNItem(int n){}//���¶�ȡn����Ŀ
void CBtAdapter::setToBtChipLoadPreNItem(int n){}//���϶�ȡn����Ŀ
void CBtAdapter::setToBtChipLoadAllItem(void){}//����ȫ����Ŀ
void CBtAdapter::setToBtChipLoadStop(void){}//ֹͣ����
void CBtAdapter::setToBtChipAgreeOppRequestAndStartLoad(void){}//ͬ�� OPP ���󲢿�ʼ����
void CBtAdapter::setToBtChipRefuseOppRequest(void){}//�ܾ� OPP ����
void CBtAdapter::setToBtChipLoadPause(void){}//��ͣ����
void CBtAdapter::setToBtChipLoadResume(void){}//��������
//1.7 SPP �������⴮��ָ��
void CBtAdapter::setToBtChipConnectSPP(char *p, int len){}//����ָ����ַ spp
void CBtAdapter::setToBtChipDisconnectSPP(void){}//�Ͽ����� spp ��ַ
void CBtAdapter::setToBtChipDisconnectSPP(char *p, int len){}//�Ͽ�ָ����ַ����
void CBtAdapter::setToBtChipQuerySppStatus(void){}//��ѯ���� spp ͨ��
void CBtAdapter::setToBtChipQuerySppStatus(char *p, int len){}//��ѯָ����ַ״̬
//1.8 MAP ���Ź���ָ��
//1.9 HID �����ٿ�ָ��
//1.10 OPP/FTP �ļ�����ָ��
//1.11 PAN ��������ָ��
//1.12 SDP ��������ָ��
void CBtAdapter::setToBtChipStartSearchBtDevice(void){}//���������豸
void CBtAdapter::setToBtChipStopSearchBtDevice(void){}//ֹͣ���������豸
void CBtAdapter::setToBtChipConnectSearchDevice(char *p, int len){}//���������豸
//1.13 �������ܲ���ָ��
void CBtAdapter::setToBtChipResetBtChip(void){}//��λģ��
void CBtAdapter::setToBtChipEraseDevicePairRecord(int index){}//���ָ���豸��Լ�¼
void CBtAdapter::setToBtChipEraseDevicePairRecord(void){}//���������Լ�¼
void CBtAdapter::setToBtChipQueryBtChipVersion(void){}//��ѯģ��汾��
void CBtAdapter::setToBtChipModifyBtChipName(char *p, int len){}//�޸��豸��
void CBtAdapter::setToBtChipQueryBtChipName(void){}//��ѯ��ǰ�豸��
void CBtAdapter::setToBtChipModifyBtChipPairCode(char *p, int len){}//�޸������
void CBtAdapter::setToBtChipQueryBtChipPairCode(void){}//��ѯ��ǰ�����
void CBtAdapter::setToBtChipQueryLocalBtMacAddr(void){}//��ѯ����������ַ
void CBtAdapter::setToBtChipQueryHavePairDevices(void){}//��ѯ��ģ������Թ����豸�б�
void CBtAdapter::setToBtChipQueryAutoPickupAndAutoReconnect(void){}//��ѯ�����Զ�����/ģ���ϵ��Զ���������
void CBtAdapter::setToBtChipOpenAutoConnectAfterPowerOn(void){}//�����ϵ��Զ�����
void CBtAdapter::setToBtChipCloseAutoConnectAfterPowerOn(void){}//�ر��ϵ��Զ�����
void CBtAdapter::setToBtChipOpenAutoPickup(void){}//���������Զ�����
void CBtAdapter::setToBtChipCloseAutoPickup(void){}//�ر������Զ�����
void CBtAdapter::setToBtChipOpenBt(void){}//������
void CBtAdapter::setToBtChipCloseBt(void){}//�ر�����
void CBtAdapter::setToBtChipQueryCurConnectBtDeviceMacAddr(void){}//��ѯ��ǰ�����豸��������ַ
void CBtAdapter::setToBtChipQueryCurConnectBtDeviceName(void){}//��ѯ��ǰ�����豸����������
void CBtAdapter::setToBtChipQuerySpkAndMicVolume(void){}//��ѯ SPK �� MIC ����
void CBtAdapter::setToBtChipQueryBatteryPowerAndSignalQuantity(void){}//��ѯ���/�ź���
void CBtAdapter::setToBtChipMicGain(char p){}
void CBtAdapter::setToBtChipQueryMicGainValue(void){}

void CBtAdapter::outPutUtf8StringToTerminal(char *p, int len)
{
	char szDebug[128] = {0};

	if (len >= 128)
		len = 127;

	memcpy(szDebug, p, len);
}
