#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

void SystemModuleToExtcar_about_carinforvoice(u8 state);
void moduleToExtcar_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToExtcar_FromExternalCtrl_Message(unsigned char *param, unsigned char len);
void moduleToExtcar_FromAudioVideo(unsigned char *p, int len);
void moduleToExtcar_FromBackCar_Message(unsigned char *param, unsigned char len);
void moduleToExtcar_FromKey_Message(unsigned char *param, unsigned char len);
void moduleToExtcar_FromBT_Message(unsigned char *p, int nLen);
void moduleToExtcar_FromAutomate(u8 *param, int len);
void moduleToExtcar_From_Public_AC_Message(u8 *p, int nLen);
void moduleToExtcar_From_Public_SYNC_Message(u8 *p, int nLen);
void moduleToExtcar_From_Public_Center_Message(u8 *p, int nLen);
void moduleToExtcar_FromGPS(u8 *param, int len);


#endif
