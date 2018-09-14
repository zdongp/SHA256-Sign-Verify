#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__
//���¶��巢�� hal ����Ϣ

void radioTohal_InitCmd(u8 nState);//��ʼ������
void radioTohal_ImitateKey(u8 nState);//ģ�ⰴ��
void radioTohal_Frequency(u16 nFrequency);//����������Ƶ��
void radioTohal_Frequency_Inc(u8 nState);//Ƶ������
void radioTohal_Frequency_Dec(u8 nState);//Ƶ�ʼ���
void radioTohal_ScanCtrl(u8 nState);//ɨ�����
void radioTohal_RadioSwitch_Power(u8 nState);//����������
void radioTohal_RadioSwitch_AF(u8 nState);//AF ����
void radioTohal_RadioSwitch_TA(u8 nState);//TA ����
void radioTohal_RadioDebugText(u8 nState);//Debug ͨ��
void rdaioToHal_Scan(int cmd);
void radioTohal_Frequency2(u16 nFrequency);

void radioTohal_SetSensitivity(u8 state);
void radioTohal_SetChannelAndFre(u8 nChannel,u16 nFrequency);

void radioTohal_InitParamCmd(u8 *param,int len);

#endif













