#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define PLAY_STATE_PLAY 0X01


void moduleToTV_FromSystem_Message(u8* param,int len);//����systemmodule����Ϣ
void moduleToTV_FromKey_Message(u8* param, int len);//����keymodule����Ϣ
void moduleToTV_FromAudiovideo_Message(unsigned char *param, unsigned char len);
void moduleToTV_FromExternalCtrl_Message(unsigned char *param, unsigned char len);
void moduleToTV_FromSystem_BrakeState(u8 nBrakeState);//ɲ��״̬
void moduleToTV_FromSystem_TVModuleExited(u8 nExited);//�Ƿ��е��Ӻ�
void moduleToTV_FromSystem_PrepareToShupDown();//׼���ػ�
void moduleToTV_FromSystem_ResetToDefaultSetting();//�ָ���������
void moduleToTV_FromSystem_ACCOn();//ACCOn
void moduleToTV_FromSystem_ACCOff();//ACCOff
void moduleToTV_FromKey_PannelKey(u8 nKeyValue);//ACCOff
void moudleToTV_FromKey_AV();
void moduleToTV_FromKey_Menu();
void moduleToTV_FromKey_TuneSeek(u8 nFlag);
void halToSystem_Galaxy_AccOn();
void halToSystem_Galaxy_AccOff();
void moduleToTV_FromSystem_Navil();
void moduleToTv_FromAutomate(u8 *param, int len);

#endif
