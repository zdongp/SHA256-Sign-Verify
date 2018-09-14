#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

/*
void moduleToDvd_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToDvd_FromAudiovideo_Message(unsigned char *param, unsigned char len);
void moduleToDvd_FromKey_Message(unsigned char *param, unsigned char len);
void moduleToDvd_FromBlcd_Message(unsigned char *param, unsigned char len);
*/

void Get_Bluetooth_PhoneState(unsigned char *param, unsigned char len);
void Get_Bluetooth_CallInfro(unsigned char *param, int len);

#endif
