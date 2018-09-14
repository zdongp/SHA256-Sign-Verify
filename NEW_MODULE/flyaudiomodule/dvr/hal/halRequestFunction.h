#ifndef __HAL_REQUEST_COMMAND_H__
#define __HAL_REQUEST_COMMAND_H__

void InitDriver(void);//≥ı ºªØ
void Set_DVR_SoftWareImitateKeyCtrl(u8 uKey);
void Set_CurTime();
void Set_DVRInitDriver();
void systemToHal_SetDVROrTV(u8 cKey);
void setToHalSyncTime(u8 y, u8 month, u8 d, u8 h, u8 m, u8 s);

void SetToHal_DVR_USB_Carema_Recording(u8 uKey);
void SetToHal_DVR_USB_Carema_Photograph();
void SetToHal_DVR_USB_Carema_SetResolution(char *param);
void SetToHal_DVR_USB_Carema_SetRecordingTimes(u16 sParam);
void SetToHal_DVR_USB_Carema_SetStorageSize(u32 sParam);
void SetToHal_DVR_USB_Carema_SetStoragePath(unsigned char* buf,int len);

void SetToHal_DVR_USB_Carema_GetVesion();
void SetToHal_DVR_USB_CaremaParamEnd();
void SetToHal_DVR_USB_CaremaParamGetSupportResolutions();
void SetToHal_DVR_USB_CaremaVideoParam(u8 uType,u8 uData);
void SetToHal_DVR_USB_Carema_SwitchOneRecording(u8 uKey);
void SetToHal_DVR_USB_Carema_MemoryCard_ToFormat(u8 uP);
void SetToHal_DVR_USB_Carema_SwitchEmergencyCollision(u8 uKey);
void SetToHal_DVR_USB_Carema_RecordingTextKeepTimes_EC(u8 uP);
void SetToHal_DVR_BackCar_Carema_Protocol_CVBS_OR_USB(u8 uP);
void SetToHal_DVR_USB_Carema_RecordingSensitivity(u8 uP);
void SetToHal_DVR_USB_Carema_RecordingVideoLock(u8 uP);

#endif
