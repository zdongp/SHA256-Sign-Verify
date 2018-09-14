#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

//#include "flycenter_mediaplayer.h"
//void mediaplayer_start(unsigned char ringid);
//void mediaplayer_stop(void);

//	void call_C_start(struct flycentermediaplayer* mp, unsigned char ringid);
//	void call_C_stop(struct flycentermediaplayer* mp);

#define KEY_MENU	0X02
#define KEY_AV		0X03
#define KEY_DVD		0X04
#define KEY_CDC		0X05
#define KEY_RADIO	0X06
#define KEY_IPOD	0X07
#define KEY_BT		0X08
#define KEY_AC		0X09
#define KEY_TV		0X0A
#define KEY_FM1		0X0B
#define KEY_FM2		0X0C
#define KEY_AM		0X0D
#define KEY_FM		0X0E
#define KEY_CALL	0X31
#define KEY_CALL_REJECT	0X32
#define KEY_OPEN	0X34
#define KEY_SEEK_INC	0X38
#define KEY_SEEK_DEC	0X39
#define KEY_TUNE_DOWN	0X3A
#define KEY_TUNE_INC	0X3B
#define KEY_TUNE_DEC	0X3C


#define PLAY_STATE_STOP 0X00
#define PLAY_STATE_PLAY	0X01
#define PLAY_STATE_PAUSE	0X02
#define PLAY_STATE_SCAN	0X03
#define PLAY_STATE_SLOW	0X04
#define PLAY_STATE_RESEVE	0X05
#define PLAY_STATE_STILL	0X06
#define PLAY_STATE_WAIT_UI	0X07
#define PLAY_STATE_NOSTATE  0x09


void moduleToCenter_FromBT_Message(unsigned char *param, unsigned char len);

void moduleToIpod_FromSystem_Message(unsigned char *param, unsigned char len);


void moduleToIpod_FromKey_Message(unsigned char *param, unsigned char len);

void moduleToIpod_FromAudiovideo_Message(unsigned char *param, unsigned char len);
void moduleToIpod_FromAutomate(u8 *param, int len);


void GetIPODConnect(int bConnect);

//进入ipod页面
void EnterIPOD();
//离开ipod页面
void LeaveIPOD();
void moduleToIpod_FromKey_GetPanelKey(unsigned char keyValue);

void otherModuleResponse_ProcessPanelKey_AV();

#endif
