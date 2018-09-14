#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

//#include "flycenter_mediaplayer.h"
void mediaplayer_start(unsigned char ringid);
//void mediaplayer_stop(void);

//	void call_C_start(struct flycentermediaplayer* mp, unsigned char ringid);
//	void call_C_stop(struct flycentermediaplayer* mp);

void moduleToCenter_FromBT_Message(unsigned char *param, unsigned char len);
void moduleToCenter_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToCenter_FromTPMS_Message(unsigned char *param, unsigned char len);
void moduleToCenter_FromExtCar_Message(unsigned char *param, unsigned char len);
void moduleToCenter_FromSYNC_Message(unsigned char *param, unsigned char len);
void moduleToCenter_FromDNV_Message(u8 *p, u8 len);
void moduleToCenter_FromAutomate(u8 *param, int len);

#endif
