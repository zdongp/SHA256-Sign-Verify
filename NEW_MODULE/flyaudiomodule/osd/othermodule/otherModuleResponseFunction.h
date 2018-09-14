#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__


void anyModuleToOsdModue_Dispatch_Msg(u8 *param, u8 len);
void CenterModuleToOsdModule_Dispatch_Msg(u8 *param, u8 len); 
void moduleToOsd_FromSystem_Message(u8 *param, u8 len);
void Handle_SystemMessage();
void backCarToOsdModule_Dispatch_Msg(u8 *param, u8 len);
void moduleToOsd_FromMedia_Message(u8 *param, u8 len);  // jing  2013-8-1 mp3 osd
void Handle_Osd_Message(u8 *param, u8 len);  // jing 2013-8-12 low bettery osd
void Handle_Bettery_Timer_ToChick(void);  // jing 2013-8-12 low bettery osd


/*
void moduleToDvd_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToDvd_FromAudiovideo_Message(unsigned char *param, unsigned char len);
void moduleToDvd_FromKey_Message(unsigned char *param, unsigned char len);
void moduleToDvd_FromBlcd_Message(unsigned char *param, unsigned char len);
*/

//T123_chipLogic
void ToT123_OSD_DisplayingValue(u8 *param, u8 len);
void ToT123_CtrlDropingDownOSD_DisplayingOrHide(u8 *param, u8 len);
void AboutNewLogic_HideOrDisplayingOSD(u8 param);
void audiovideoToOsdModule_ViewSwitch_Message(u8 *param, u8 len);
void moduleToOsd_FromTPMS_Message(u8 *param, u8 len);
void moduleToOsd_FromRadio_Message(u8 *param, u8 len);
void moduleToOsd_FromDVD_Message(u8 *param, u8 len);
void moduleToOsd_FromAUX_Message(u8 *param, u8 len);
void moduleToOsd_FromTV_Message(u8 *param, u8 len);
void moduleToOsd_FromDVR_Message(u8 *param, u8 len);
void moduleToOsd_FromAC_Message(u8 *param);
void moduleToOsd_FromAudioVideo_Message(u8* param,u8 len);
//////////////////////////////////////
void SetTimerOfHideOSD();//��ʼ��ʱ��
void KillTimerOfHideOSD();//ֹͣ��ʱ��
void ShowSubTitleCmdProc(int nNewOSDContent);//��ʾ����osd����
void SetVideoSetting(unsigned char cParam);//����Driver����Ƶ��ɫ����
bool IsSubTitleOSD(int iOSDConnect);//�ж�OSD�Ƿ�����λOSD
void BackToBkGndPage();
void TimerSetVideo();//�ö�ʱ������
void Get_PageChangeMessage(int LeavePageID,int EnterPageID,int Param);
void Get_DropDownOsdMessage(u8 osdContent);//edited by ygp
void Get_SetOSDUIValue(u8* param,int len);



/////////////////////////////////////

#endif
