#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

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

void moduleToMedia_FromKey_Message(unsigned char *param, unsigned char len);

int isInMediaPage();
int isInMediaOtherPage(); 
void moduleToMedia_FromSystemMessage(unsigned char *param, unsigned char len);
void moduleToMedia_ProcessPanelKey_AV(void);
void moduleToMedia_PanKB_Media();
void moduleToMedia_FromAudioVideoMessage(u8 *param, u8 len);
void moduleToMedia_FromAudioVideo_GetSoundChannel(u8 nSoundChannel);
void moduleToMedia_FromExternalCtrlMessage(u8 *param, u8 len);
void moduleToMedia_FromAutomate(u8 *param, int len);
void moduleToMedia_FromJniSdk(u8 *param, int len);
void getVoiceStatusFromExternalctrl(u8 param);


#endif
