#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__
#define TVTOHAL_IR_PLAY     0x14
#define TVTOHAL_IR_PAUSE    0x15

void tvToHal_KeyCtrl(u8 nKey);//��������
void tvToHal_Init();//��ʼ��
void tvToHal_ImitateKeyCtrl(u8 nKey);//ģ�ⰴ��
void tvToHal_Debug();//����ģʽ
void tvToHal_VideoSetting(u8 nCmdParam);//�������
void tvToHal_IR(unsigned char IR_key);

#endif
