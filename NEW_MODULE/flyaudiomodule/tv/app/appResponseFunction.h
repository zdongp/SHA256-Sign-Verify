#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

void appToTV_CtrlMenu_MouseUp(u32 nFuncID);//����ҳ�ĵ����¼�
void appToTV_VideoSet_MouseUp(u32 nFuncID);//��Ƶ���õĵ����¼�
void appToTV_JumpPage_MouseUp(u32 nFuncID);//��ҳ�����¼�

void appToTV_VideoOSD_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType);
void appToTV_VideoOSDColorSet_ButtonMessageToT123ChipLocation(int ctrlId,u8 ctrlType);

#endif
