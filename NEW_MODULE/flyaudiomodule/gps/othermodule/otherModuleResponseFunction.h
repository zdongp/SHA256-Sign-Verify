#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__



void moduleToGps_FromKey_Message(unsigned char *param, unsigned char len);

void moduleToGps_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToGps_FromExternalCtrl_Message(unsigned char *param, unsigned char len);
void moduleToGps_FromAutomate(u8 *param, int len);

#endif
