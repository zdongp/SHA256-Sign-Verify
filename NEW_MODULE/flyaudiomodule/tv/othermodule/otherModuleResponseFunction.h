#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define PLAY_STATE_PLAY 0X01


void moduleToTV_FromSystem_Message(u8* param,int len);//来自systemmodule的消息
void moduleToTV_FromKey_Message(u8* param, int len);//来自keymodule的消息
void moduleToTV_FromAudiovideo_Message(unsigned char *param, unsigned char len);
void moduleToTV_FromExternalCtrl_Message(unsigned char *param, unsigned char len);
void moduleToTV_FromSystem_BrakeState(u8 nBrakeState);//刹车状态
void moduleToTV_FromSystem_TVModuleExited(u8 nExited);//是否有电视盒
void moduleToTV_FromSystem_PrepareToShupDown();//准备关机
void moduleToTV_FromSystem_ResetToDefaultSetting();//恢复出厂设置
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
