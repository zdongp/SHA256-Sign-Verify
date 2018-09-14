#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"
#include "moduleParamResponse.h"
#include "param.h"

#include <flymoduleApi_internal.h>


#include <time.h>

void InitDriver()//³õÊ¼»¯
{
	Set_DVRInitDriver();
	if(pLocalParam->uDvrModule_is_T123 == 1){
	Set_DVR_SoftWareImitateKeyCtrl(DetectingMode);
	}
}

void Set_DVRInitDriver()
{
	u8 buf[] = {0x01,0x01};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void Set_DVR_SoftWareImitateKeyCtrl(u8 uKey)
{
	unsigned char buf[] = {0x03,uKey};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void Set_CurTime()
{
	struct tm *ptm;
	long ts;
	ts = time(NULL);
	ptm=localtime(&ts);
	u8 year = (u8)((ptm->tm_year+1900)-2000);
	if((ptm->tm_year+1900)-2013 < 0)
		year = 13;
		
	u8 mon  = (u8)(ptm->tm_mon+1);
	u8 day  = (u8)(ptm->tm_mday);
	u8 hour = (u8)(ptm->tm_hour);
	u8 min  = (u8)(ptm->tm_min);
	u8 sec  = (u8)(ptm->tm_sec);
	LOGD("Set_CurTime year:%d mon:%d day:%d hour:%d min:%d sec:%d",year,mon,day,hour,min,sec);
	u8 buf[]={0x13,year,mon,day,hour,min,sec};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,7);

	//makeAndSendMessageToHal(HAL_ID_DVR,buf,10);
}

void setToHalSyncTime(u8 y, u8 month, u8 d, u8 h, u8 m, u8 s)
{
	u8 szMsg[7] = {0};
	szMsg[0] = 0x13;
	szMsg[1] = y;
	szMsg[2] = month;
	szMsg[3] = d;
	szMsg[4] = h;
	szMsg[5] = m;
	szMsg[6] = s;

	makeAndSendMessageToHal(HAL_ID_DVR, szMsg, sizeof(szMsg));
}

void SetToHal_DVR_USB_Carema_Recording(u8 uKey)
{
	u8 buf[] = {0x40,uKey};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_Carema_Photograph()
{
	u8 buf[] = {0x41,0x01};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);

}

void SetToHal_DVR_USB_Carema_SetResolution(char *param)
{
	char buf[STRING_MAX_LEN+1];
	memset(buf,0,sizeof(buf));

	buf[0] = 0x42;
	memcpy(&buf[1],param,strlen(param));
	
	makeAndSendMessageToHal(HAL_ID_DVR,(u8*)buf,strlen(buf));
}

void SetToHal_DVR_USB_Carema_SetRecordingTimes(u16 sParam)
{
	u8 buf[] = {0x43,0x00,0x00};
	buf[1]=(u8)((sParam >> 8) & 0xff);
	buf[2]=(u8)(sParam & 0xff);
	makeAndSendMessageToHal(HAL_ID_DVR,buf,3);
}

void SetToHal_DVR_USB_Carema_GetVesion()
{
	u8 buf[] = {0x44,0x00};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_Carema_SetStorageSize(u32 sParam)
{
	u8 buf[] = {0x45,0x00,0x00,0x00,0x00};
	buf[1]=(u8)((sParam >> 24) & 0xff);
	buf[2]=(u8)((sParam >> 16) & 0xff);
	buf[3]=(u8)((sParam >> 8) & 0xff);
	buf[4]=(u8)(sParam & 0xff);
	makeAndSendMessageToHal(HAL_ID_DVR,buf,5);
}

void SetToHal_DVR_USB_Carema_SetStoragePath(unsigned char* buf,int len)
{
	unsigned char* pSendBuf = (u8*)malloc(len+1);
	pSendBuf[0] = 0x46;//cmd
	memcpy(pSendBuf+1,buf,len);
	makeAndSendMessageToHal(HAL_ID_DVR,pSendBuf,len+1);
	free(pSendBuf);
}

void SetToHal_DVR_USB_CaremaParamEnd()
{
	u8 buf[] = {0x47,0x00};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_CaremaParamGetSupportResolutions()
{
	u8 buf[] = {0x48,0x00};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_CaremaVideoParam(u8 uType,u8 uData)
{
	u8 buf[] = {0x60,0x00,0x00};
	buf[1] = uType;
	buf[2] = uData;
	makeAndSendMessageToHal(HAL_ID_DVR,buf,3);
}

void SetToHal_DVR_USB_Carema_SwitchOneRecording(u8 uKey)
{
	u8 buf[] = {0x61,uKey};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_Carema_SwitchEmergencyCollision(u8 uKey)
{
	u8 buf[] = {0x62,uKey};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_Carema_MemoryCard_ToFormat(u8 uP)
{
	u8 buf[] = {0x63,uP};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_Carema_RecordingTextKeepTimes_EC(u8 uP)
{
	u8 buf[] = {0x64,uP};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_BackCar_Carema_Protocol_CVBS_OR_USB(u8 uP)
{
	u8 buf[] = {0x65,uP};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_Carema_RecordingSensitivity(u8 uP)
{
	u8 buf[] = {0x66,uP};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}

void SetToHal_DVR_USB_Carema_RecordingVideoLock(u8 uP)
{
	u8 buf[] = {0x67,uP};
	makeAndSendMessageToHal(HAL_ID_DVR,buf,2);
}


