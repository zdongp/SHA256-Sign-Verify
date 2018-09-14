#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

void moduleToTPMS_FromSystem_Message(unsigned char *param, unsigned char len);
void Get_Battery(u8 mbattery);
void moduleToTPMS_FromExternalCtrl_Message(unsigned char *param, unsigned char len);
void moduleToTpms_FromAutomate(u8 *param, int len);

void moduleToTpms_FromExtcar(u8 *param, int len);

void analysePublicTpmsHalMessage(u8 *param,u8 len);
void getPublicTirePressureInfo(u8 *param, u8 len);
void getPublicTireTemperatureInfo(u8 *param, u8 len);
void getTpmsTirePressureUint(u8 param);

#endif
