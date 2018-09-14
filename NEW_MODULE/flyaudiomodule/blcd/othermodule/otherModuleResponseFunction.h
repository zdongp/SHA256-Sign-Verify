#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

void moduleToBlcd_FromBlcd_SetSoundVideoChannel(u8 param);
void moduleToBlcd_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToBlcd_FromAudiovideo_Message(unsigned char *param, unsigned char len);
void moduleToBlcd_FromKey_Message(unsigned char *param, unsigned char len);
void moduleToBlcd_FromDvd_Message(unsigned char *param, unsigned char len);
void moduleToBlcd_FromExternalCtrl_Message(unsigned char *param, unsigned char len);
void moduleToBlcd_FromAutomate_Message(unsigned char *param, unsigned char len);


void DispatchProcessSoundCmd(unsigned char ucState);

void DispatchProcessKeyCmd(unsigned char ucCmd);


void Get_CDC_DISC_Select(char disk);
void Show_CDC_Disc();
u8 CDC_GetDiscStr(char discNumber);
void Get_CDC_DISC_Open();
void Clean_CDC_Disc();
void Get_CDC_DISC_Type(char disk,char type);




#endif
