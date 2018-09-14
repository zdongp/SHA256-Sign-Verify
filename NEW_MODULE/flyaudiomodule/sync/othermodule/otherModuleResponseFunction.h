#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

void moduleToSYNC_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToSYNC_FromEXTCAR_Message(u8 *param,u8 len);
void moduleToSYNC_FromAudiovideo_Message(u8 *param,u8 len);
void moduleToSYNC_FromKey_Message(u8 *param,u8 len);
void moduleToSYNC_FromExternalCtrl_Message(u8 *param,u8 len);

void moduleToSYNC_FromAudiovideo_Get_SoundVideoMode(u8 param);
void moduleToSYNC_Fromkey_Get_KeyValue(u8 param);
void moduleToSYNC_FromCenter_Message(u8 *param,u8 len);
void moduleToSync_FromAutomate(u8 *param, int len);

void Sync_getStandbyState(u8 param);


#endif
