#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__


void moduleToDVR_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToDVR_FromAudiovideo_Message(unsigned char *param, unsigned char len);
void moduleToDVR_FromKey_Message(unsigned char *param, unsigned char len);
void moduleToDVR_FromBT_Message(unsigned char *param, unsigned char len);
void moduleToDvr_FromAutomate(u8 *param, int len);
void moduleToDvr_FromCenter(u8 *param, int len);

void Get_BrakeState(u8 state);
void IsInDVRMode(u8 *param);
void LeaveDVR();
void EnterDVR();

void KeyMsgAV();
void KeyMsgSEEK_TUNE_INC();
void KeyMsgSEEK_TUNE_DEC();

void moduleToDvr_FromAudiovideo_GetVolumeOsdCtrl();
void moduleToDvr_FromExternalCtrl_Message(unsigned char *param,unsigned char len);

#endif
