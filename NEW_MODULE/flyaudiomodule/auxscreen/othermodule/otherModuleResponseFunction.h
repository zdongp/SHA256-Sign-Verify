#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__


void moduleToAuxScreen_PlayingModule(u8 nModule);//��ǰ���ŵ�ģ��
void moduleToAuxScreen_PlayingInfo(u8* buf,int len);//��ǰ����ý���ʱ�����Ϣ

void moduleToAuxScreen_FromSystem_Message(unsigned char *param, unsigned char len);


void moduleToAuxScreen_FromDVD_message(unsigned char *param,unsigned char len);
void moduleToAuxScreen_FromBT_message(unsigned char *param,unsigned char len);
void moduleToAuxScreen_FromRadio_message(unsigned char *param,unsigned char len);
void moduleToAuxScreen_FromAudioVideo_message(unsigned char *param,unsigned char len);


void moduleToAuxScreen_FromMedia_Message(unsigned char *param, unsigned char len);
void moduleToAuxScreen_SendAllMediaInfoToHal(void);
void moduleToAuxScreen_SendAllA2DPInfoToHal(void);

void moduleToAuxScreen_FromGPS_Message(u8 *param,u8 len);
void moduleToAuxScreen_FromAUXscreen_message(u8 *param,u8 len);
void moduleToAuxScreen_FromExtcar_Message(u8 *param,u8 len);

void moduleToAuxScreen_Show_Message();



#endif
