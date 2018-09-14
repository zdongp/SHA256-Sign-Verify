#ifndef __HAL_RESPONSE_COMMAND_H__
#define __HAL_RESPONSE_COMMAND_H__

#include "global.h"
#include "messageQueue.h"



void analyseHalMessage_DVR(char resCmd, unsigned char *param, unsigned char len);



void Get_DVRDriverInitParam(u8 cInitOrder);
void Get_DVRDriverInitState(u8 cState);
void Get_DVRModuleExistState(u8 cState);	//ÊÇ·ñÓÐDVRÄ£¿é
void Get_DVRChooseWhichPage(u8 cMode);
void Get_DVRResolution(u8 cPuf);
void Get_DVRLanguage(u8 cPuf);
void Get_DVRRecorderVideoState(u8 cState);
void Get_DVRRecordState(u8 cState);
void Get_DVRAutoMate(char resCmd,u8 *param,u8 len);

void analyseUsbCameraMsg(char resCmd, unsigned char *param, unsigned char len);
void Get_UsbCameraRecordingState(u8 uId,u8 *param);
void Get_UsbCameraPhotograph(u8 uId,u8 *param);
void Get_UsbCameraResolutionData(u8 uId,u8 *param,int len);
void Get_UsbCameraRecordingTimes(u8 uId,u8 *param,int len);
void Get_UsbCameraStorageSize(u8 uId,u8 *param,int len);
void Get_UsbCameraStoragePath(u8 uId,u8 *param,int len);
void Get_UsbCameraSupportResolutions(u8 uId,u8 *param,int len);
void Get_UsbCameraVideoParam(u8 uId,u8 *param);
void Get_UsbCameraSwitchOneRecordingMod(u8 uId,u8 *param);
void Get_UsbCameraMemoryCardToFormatInfor(u8 *p);
void Get_UsbCameraRecordingTextKeepTimes_EC(u8 param);
void Get_CurBackCarCameraProtocol(u8 p);
void Get_UsbCameraRecordingSensitivity(u8 p);
void Get_UsbCameraRecordingVideoLock(u8 p);

void Get_UsbCameraError(u8 *param,u8 len);
void Get_UsbCameraInitInfors(u8 *param,int len);
int Inside_FindIndexFromStr(const u8 *pSrc, int nSrcLen, u8 cLetter, int nStart);
void Get_UsbCameraMemoryCardToSwitchEmergencyCollision(u8 param);


#endif
