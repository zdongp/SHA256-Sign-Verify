#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include"moduleID.h"
#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "pageID.h"
#include "param.h"



//Jump Specify Page
void systemToModule_NotifySystem_JumpPage(short nPageID)
{
	 u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&nPageID,2);
     makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_SYSTEM,buf,3);
}
//Jump Pre Page
void systemToModule_NotifySystem_JumpPrePage(void)
{
	 u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_SYSTEM,buf,2);
}

void systemToModule_NotifySystem_SwithModule(u8 moduleId){
	u8 buf[] = {0x81, moduleId};

	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_SYSTEM, buf, 2);
}

//Restore Defaults
void systemToModule_NotifyAllModule_RestoreDefaults()
{
	u8 ModuleBuf[] = {MODULE_ID_AUDIOVIDEO,MODULE_ID_SYSTEM,MODULE_ID_KEY,MODULE_ID_RADIO,MODULE_ID_DVD,MODULE_ID_TPMS,
		              MODULE_ID_BACK,MODULE_ID_TV,MODULE_ID_BT,MODULE_ID_IPOD,MODULE_ID_MEDIA,
					  MODULE_ID_BLCD,MODULE_ID_AUX,MODULE_ID_AUXSCREEN,MODULE_ID_CENTER};
	int i = 0;
	for(i=0;i < (int)dim(ModuleBuf);i++)
	{
        unsigned char buf[2] = {0x2C, 0x02}; //CMD:0x29 Restore Defaults
		makeAndSendMessageToModule(MODULE_ID_SYSTEM,ModuleBuf[i],buf,2);
	}
}
//Reboot
void systemToModule_NotifyAllModule_Reboot()
{
	u8 ModuleBuf[] = {MODULE_ID_AUDIOVIDEO,MODULE_ID_SYSTEM,MODULE_ID_KEY,MODULE_ID_RADIO,MODULE_ID_DVD,MODULE_ID_TPMS,
		              MODULE_ID_BACK,MODULE_ID_TV,MODULE_ID_BT,MODULE_ID_IPOD,MODULE_ID_MEDIA,
					  MODULE_ID_BLCD,MODULE_ID_AUX,MODULE_ID_AUXSCREEN,MODULE_ID_CENTER};
	int i = 0;
	for(i=0;i<(int)dim(ModuleBuf);i++)
	{
        unsigned char buf[2] = {SYSTEM_NOTIFY_REBOOT, 0x00}; //CMD:0x10 Reboot
		makeAndSendMessageToModule(MODULE_ID_SYSTEM,ModuleBuf[i],buf,2);
	}
}
//ACC ON
void systemToModule_NotifyAllModule_AccOn()
{
	u8 ModuleBuf[] = {MODULE_ID_AUDIOVIDEO,MODULE_ID_SYSTEM,MODULE_ID_KEY,MODULE_ID_RADIO,MODULE_ID_DVD,MODULE_ID_TPMS,
		              MODULE_ID_BACK,MODULE_ID_TV,MODULE_ID_BT,MODULE_ID_IPOD,MODULE_ID_MEDIA,
					  MODULE_ID_BLCD,MODULE_ID_AUX,MODULE_ID_AUXSCREEN,MODULE_ID_CENTER};
	int i = 0;
	for(i=0;i<(int)dim(ModuleBuf);i++)
	{
        unsigned char buf[2] = { SYSTEM_NOTIFY_ACCON, 0x00}; //CMD:0x30 ACC ON
		makeAndSendMessageToModule(MODULE_ID_SYSTEM,ModuleBuf[i],buf,2);
	}
}
//ACC OFF
void systemToModule_NotifyAllModule_AccOff()
{
	u8 ModuleBuf[] = {MODULE_ID_AUDIOVIDEO,MODULE_ID_SYSTEM,MODULE_ID_KEY,MODULE_ID_RADIO,MODULE_ID_DVD,MODULE_ID_TPMS,
		              MODULE_ID_BACK,MODULE_ID_TV,MODULE_ID_BT,MODULE_ID_IPOD,MODULE_ID_MEDIA,
					  MODULE_ID_BLCD,MODULE_ID_AUX,MODULE_ID_AUXSCREEN,MODULE_ID_CENTER};
	int i = 0;
	for(i=0;i<(int)dim(ModuleBuf);i++)
	{
        unsigned char buf[2] = {SYSTEM_NOTIFY_ACCOFF, 0x00}; //CMD:0x31 ACC OFF
		makeAndSendMessageToModule(MODULE_ID_SYSTEM,ModuleBuf[i],buf,2);
	}
}

//Notify Sound Module
void systemToModule_NotifySoundModule_SysInitStatus(u8 u8_status)
{
	unsigned char buf[] = {0xE4, 0x00};
	buf[1] = u8_status;
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_AUDIOVIDEO,buf,2);
}
void systemToModule_NotifySoundModule_StartupVol(u8 u8_status)
{
	unsigned char buf[] = {0xE0, 0x00};
	buf[1] = u8_status;
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_AUDIOVIDEO,buf,2);
}
void systemToModule_NotifySoundModule_GPSVoicePrompt(u8 u8_status)
{
	unsigned char buf[] = {0xE2, 0x00};
	buf[1] = u8_status;
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_AUDIOVIDEO,buf,2);
}
void systemToModule_NotifyRadio()
{
    u8 buf[]={0x48,0x00};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_RADIO,buf,2);
}

//Notify Some Module
void systemToModule_NotifySomeModule_ChangePage(u8 u8_Module,u16 u16_LewPage,u16 u16_EnterPage,u8 u8_Param)
{
	if(u16_EnterPage == u16_LewPage)//��ƵOSD�����Զ���ʧ����
		return;


	unsigned char buf[] = {SYSTEM_NOTIFY_CHANGEPAGE,0x00,0x00,0x00,0x00,0x00};
	memcpy(&buf[1],&u16_LewPage,2);
	memcpy(&buf[3],&u16_EnterPage,2);
	buf[5] = u8_Param;
	if(u16_LewPage==PAGE_DVD_VIDEO_CONTROL
		||u16_LewPage==PAGE_DVD_VIDEO_SET
		||u16_LewPage==PAGE_TV_VIDEO_CONTROL
		||u16_LewPage==PAGE_DVD_VIDEO_SET
		 ||u16_LewPage==PAGE_AUX_VIDEO_CONTROL
		 ||u16_LewPage==PAGE_AUX_VIDEO_SET
		 ||u16_LewPage==PAGE_AUX_VIDEO
		 ||u16_LewPage==PAGE_AUX)
		{
		 unsigned char buf[] = {0x38,0x00};
		 LOGD("---systemToModule_NotifySomeModule_ChangePage----u16_LewPage=%x---u16_EnterPage=%x",u16_LewPage,u16_EnterPage);
		 makeAndSendMessageToModule(MODULE_ID_SYSTEM,u8_Module,buf,2);
		}

	makeAndSendMessageToModule(MODULE_ID_SYSTEM,u8_Module,buf,6);

}

void systemToModule_NotifyService_BarcodeInfors(u8 *p,u32 len)
{
	u8 buf[128] = {0x00};
	buf[0] = 0x02;
	if(len > 127)
		len = 127;
	
	memcpy(&buf[1],p,len);
	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_SERVICE, buf, len + 1);
}

void systemCallParrotBT_aboutSerialDataUIFunction(u32 u32_ctrID,u8* param,int len)
{
	u8 buf[50];
	memset(buf,0,sizeof(buf));
	
	buf[0]=0x2e;
	memcpy(&buf[1],&u32_ctrID,4);

	if(len > (50 - 5))
		len = (50 - 5);
	
	memcpy(&buf[5],param,len);

	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_BT, buf, sizeof(buf));

}

void systemToModule_NotifySomeModule_BrakeCarStatus(u8 u8Status)
{
	u8 ModuleBuf[] = {MODULE_ID_DVD,
		              MODULE_ID_TV,
		              MODULE_ID_IPOD,
		              MODULE_ID_MEDIA,
					  MODULE_ID_AUX};
	int i = 0;
	for(i=0;i<(int)dim(ModuleBuf);i++)
	{
		unsigned char buf[] = {0x09,u8Status};
		makeAndSendMessageToModule(MODULE_ID_SYSTEM,ModuleBuf[i],buf,2);
	}
}
void systemToModule_NotifySomeModule_StandbyStatus(u8 u8Status)
{
	u8 ModuleBuf[] = {MODULE_ID_DVD,
					  MODULE_ID_AUDIOVIDEO,MODULE_ID_AUX,MODULE_ID_IPOD};
	int i = 0;
	for(i=0;i<(int)dim(ModuleBuf);i++)
	{
		unsigned char buf[] = {0x0E,u8Status};
		makeAndSendMessageToModule(MODULE_ID_SYSTEM,ModuleBuf[i],buf,2);
	}
}
void systemToModule_NotifySomeModule_GPSAutoRunStatus(u8 u8Status)
{
	u8 ModuleBuf[] = {MODULE_ID_KEY,
					  MODULE_ID_CENTER};
	int i = 0;
	for(i=0;i<(int)dim(ModuleBuf);i++)
	{
		unsigned char buf[] = {0xE2,u8Status};
		makeAndSendMessageToModule(MODULE_ID_SYSTEM,ModuleBuf[i],buf,2);
	}
}


//Notify Radio Module
void systemToModule_NotifyRadioModule_PressKey_AV()
{
	unsigned char buf[] = {0x03};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_RADIO,buf,1);
}

//Notify Key Module
//Notify Key Whether Lcd Close Or Not
void systemToModule_NotifyKeyModule_WhetherLcdClose(bool bStatus)
{
	unsigned char buf[] = {0x05,bStatus};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_KEY,buf,2);
}


//Notify BackCar Module
void systemToModule_NotifyBackModule_BackCarStatus(u8 bStatus, u8 bVideo)
{
	unsigned char buf[] = {0x21,bStatus,bVideo};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_BACK,buf,3);
}

void systemToModule_NotifyBackModule_BackCarVideoRefLineDisplaySet(u8 bStatus)
{
	unsigned char buf[] = {0x22,bStatus};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_BACK,buf,2);
}

void systemToModule_NotifyBackModule_BackCarVideoTraceLineDisplaySet(u8 bStatus)
{
	unsigned char buf[] = {0x23,bStatus};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_BACK,buf,2);
}

void systemToModule_NotifyBackModule_BackCarRadarStatus(unsigned char status){
	unsigned char buf[] = {0x43, status};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_BACK, buf, 2);
}

//Notify TPMS Module
void systemToModule_NotifyTPMSModule_MagnitudeOfVoltage(u8 u8_Param)
{
	unsigned char buf[] = {0x0B,u8_Param};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_TPMS,buf,2);
}
void systemToModule_NotifyTPMSModule_WhetherTPMSExist(u8 u8_Param)
{
	unsigned char buf[] = {0x0F,u8_Param};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_TPMS,buf,2);
}


//Notify TV Module
void systemToModule_NotifyTVModule_WhetherTVExist(u8 u8_Param)
{
	unsigned char buf[] = {0x0E,u8_Param};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_TV,buf,2);
}


//Notify AUX Module
void systemToModule_NotifyAUXModule_AUXVideo(u8 u8_Param)
{
	unsigned char buf[] = {0x28,u8_Param};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_AUX,buf,2);
}

void systemToModule_NotifyDVRModule_DVRVideo(u8 u8_param)
{
	unsigned char buf[] = {0x2C,u8_param};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_DVR,buf,2);
}

void systemToModule_NotifyDVRModule_LewOrEnterDVR()
{
	unsigned char buf[] = {0x2D,0x00};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_DVR,buf,2);
}


void SystemModuleToAUX_DisplaySystemTime()
{
	time_t now;
	struct tm *timenow;
	time(&now);
	timenow=localtime(&now);
	u8 buf[5];

	buf[0]=0xA0;
	buf[1]=timenow->tm_sec;
	buf[2]=timenow->tm_min;
	buf[3]=timenow->tm_hour;

	if(pLocalParam->uSystemTimeFormat == 0)
	buf[4]=24;
	else if(pLocalParam->uSystemTimeFormat == 1)
	buf[4]=12;

	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_AUXSCREEN,buf,5);
}


// Notify Ipod Module
void systemToModule_NotifyIpod_ExitIpol(u8 u8_Param)
{
    pLocalParam->b_Sys_Ipod=u8_Param;
	unsigned char buf[] = {0x70,0x00};
	buf[1] = u8_Param;
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_IPOD,buf,2);
}


//Notify GPS
void systemToGPSRun_NotifyGPSRun_AutoRunMsg(bool bStatus)
{
    unsigned char buf[] = {0x40,bStatus};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_GPS,buf,2);
}

void systemToGPSRun_NotifyGPS_15sJumpPage()
{
	u8 buf[] = { 0x41, 0x00};
   makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_GPS,buf,2);
}

// Notify OSD Module
// jing 2013-8-12 low bettery osd {
void systemToModule_NotifyOSD_Low_Bettery(u8 u8_Parm)
{
	u8 buf[] = {0x40,u8_Parm};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_OSD,buf,2);
}

void systemToModule_NotifyOSD_IsHaveRadarData(u8 HaveRadarData){
	u8 buf[] = {0x27,HaveRadarData};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_OSD,buf,2);
}
// jing 2013-8-12 low bettery osd }
void systemToModule_NotifyOSD_OSD_barcode(){
    u8 buf[] = {0xFD,0x00};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_OSD,buf,2);
}

void systemToModule_NotifyOSD_backcar_RadarDirectAndLevel(u8 u8_Parm1,u8 u8_Parm2)
{
	u8 buf[] = {0x26,u8_Parm1,u8_Parm2};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_OSD,buf,3);
}

void systemToModule_NotifyOSD_backcar_carRadar_SwitchRadarcarPage(u8 u8_Parm){
	u8 buf[] = {0x22,u8_Parm};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_OSD,buf,2);
}

void systemToModule_NotifyOSD_backcar_carRadar_DisplayingAndHander(u8 u8_Parm)
{
	u8 buf[] = {0x27,u8_Parm};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_OSD,buf,2);
}


/*****************************************************************************************/
void systemToModule_NotifyOSD_OSDDebug_Info(u8 *buffer, u8 len){
	u8 buf[len+1];
	memset(buf,0,len+1);
	buf[0] = 0xFE;
	memcpy(&buf[1], buffer, len);

	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_OSD,buf,len+1);
}

void systemToModule_NotifyOSD_OSDDebugInfo_Switch(void){
	u8 buf[] = {0xFF, 0x00};

	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_OSD,buf,2);
}

void systemToModule_NotifyGps_DayOrNight(u8 u8_Param){
	u8 buf[]={0x56,u8_Param};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_GPS,buf,2);
}

void systemToModule_NotifyDNV_DayOrNight(u8 p)
{
	u8 szMsg[] = {0x03, p};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_DNV, szMsg, sizeof(szMsg));
}

void systemToModule_NotifyServiceModule_ChangeCarMode(u8 u8_Param)
{
	u8 buf[] = { 0x00, u8_Param};
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_SERVICE,buf,2);
}

void systemToModule_NotifyServiceModule_StandbyState(u8 u8_Param)
{
	u8 buf[] = { 0x01, u8_Param};
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_SERVICE,buf,2);
}

void SendDeviceStateToOSDDebug(void)
{
	u8 buf[256]={0};
	buf[0]=0x04;
	char strSound[128]={0};
	sprintf(strSound,"AUX:%d,     TV:%d,     TPMS:%d,     IPOD:%d",
		pLocalParam->u8_Sys_AUXVideo,pLocalParam->u8_Sys_WhetherTVExist,pLocalParam->u8_Sys_WhetherTPMSExist,pLocalParam->b_Sys_Ipod);
	memcpy(&buf[1],strSound,strlen(strSound));
	
	u8 len=strlen(strSound)+2;
	
	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_SYSTEM, buf,len);
}
void SendBackcarInfoAndDiaInStateToOSDDebug(void)
{
	u8 buf[256]={0};
	buf[0]=0x05;
	char strSound[128]={0};
	
	sprintf(strSound,"3G_DialIn:%d,  BackCarStatus:%d,  BackCarVideo:%d,  BackCarradar:%d",
		pLocalParam->b_3G_DialIn,pLocalParam->b_Sys_BackCarStatus,pLocalParam->b_Sys_BackCarVideo,pLocalParam->b_hal_radar);
	memcpy(&buf[1],strSound,strlen(strSound));
	u8 len=strlen(strSound)+2;
	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_SYSTEM, buf,len);
}

void systemToModule_NotifyExtcarModule_CarInforVoiceStatus(bool state)
{
	u8 buf[] = {0x00, state};
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,buf,2);
}


void systemToModule_NotifyAUXModule_AUXChecking()
{
	unsigned char buf[] = {0x39,0x00};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_AUX,buf,2);
}


void systemToModule_NotifyBtModule_aboutStandby(u8 uState)
{
	unsigned char buf[] = {0x15,uState};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_BT,buf,2);
}



void systemToModule_NotifySyncModule_aboutFlySystem_OperatingNormal(u8 uParam)
{
	unsigned char buf[] = {0x00,uParam};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_SYNC,buf,2);
}

void systemToModule_NotifySyncModule_aboutFastStandy_SyncMediaPlay(u8 uParam)
{
	unsigned char buf[] = {0x01,uParam};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_SYNC,buf,2);
}


void setToDNVbackKey(void)
{
	u8 szMsg[2] = {0x00, 0x00};

	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_DNV, szMsg, sizeof(szMsg));
}

void setToDNVGoInto(void)
{
	u8 szMsg[2] = {0x01, 0x00};

	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_DNV, szMsg, sizeof(szMsg));
}

void setToDNVSupport(u8 p)
{
	u8 szMsg[2] = {0x02, p};

	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_DNV, szMsg, sizeof(szMsg));
}

void systemToModule_NotifyAudiovideo_SetThirdChannel(){
	u8 buf[] = {0x4d, 0x00};

	makeAndSendMessageToModule(MODULE_ID_SYSTEM, MODULE_ID_AUDIOVIDEO, buf, 2);
}

void systemToModule_NotifyExtcarModule_CarBatteryVoltAnomalyMonitoring(u8 param)
{
	u8 buf[] = {0x59, 0x00};
	buf[1] = param;
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,buf,2);
}

void systemToModule_NotifyExtcarModule_CarBatteryVolt(u8 *param)
{
	u8 buf[] = {0x60, 0x00,0x00};
	memcpy(buf+1,param,2);
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,buf,3);
}

void systemToModule_NotifyRemoteOnline_AccStatus(u8 p)
{
	u8 buf[] = {0x01,0x00};
	buf[1] = p;
    	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_REMOTEONLINE,buf,2);
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_MEDIA,buf,2);
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_BT,buf,2);
}

void systemToModule_NotifyRemoteOnline_StandbyStatus(u8 p)
{
	u8 buf[] = {0x02,0x00};
	buf[1] = p;
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_REMOTEONLINE,buf,2);
}

void systemToModule_NotifyDVR_setBackCarProtocol_CVBS_or_USB(u8 p)
{
	u8 buf[] = {0x40,0x00};
	buf[1] = p;
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_DVR,buf,2);
}
void systemToModule_NotifyBackModule_BackCarVideoTraceLine_Type_Set(u8 bStatus)
{
	unsigned char buf[] = {0x24,bStatus};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_BACK,buf,2);
}

void systemToModule_NotifyExternalctrl_SpeechEnable(u8 p)
{
	u8 buf[] = {0x01,0x00};
	buf[1] = p;
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTERNALCTRL,buf,2);
}

void systemToModule_NotifyExtcar_SetCameraDelay(u8 p)
{
	u8 buf[] = {0xf0,0x00,0x12,0x00,p};
   	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,buf,5);
}

void systemToModule_NotifyExtcar_SetTempUnit(u8 p)
{
	u8 buf[] = {0xf0,0x00,0x11,0x00,p};
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,buf,5);
}

void systemToModule_NotifyExtcarModule_AmbientLedColor_HighModelFord(u8 param)
{
	u8 buf[] = {0x04, 0xFF};
	buf[1] = param;
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,buf,sizeof(buf));
}

void systemToModule_NotifyExtcarModule_AmbientLedBrightness_HighModelFord(u8 *param)
{
	u8 buf[] = {0x05, 0xFF, 0xFF, 0xFF, 0xFF};
	memcpy(&buf[1],param,4);
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,buf,sizeof(buf));
}

void systemToModule_NotifyExtcarModule_DistanceUnit_HighModelFord(u8 param)
{
	u8 buf[] = {0x06, 0xFF};
	buf[1] = param;
    makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,buf,sizeof(buf));
}

void setPublicFord_MultiContouredSeats(u8 *param,int len)
{
	u8 szMsg[10];
	memset(szMsg,0,sizeof(szMsg));
	szMsg[0] = 0xf0;
	szMsg[1] = 0x00;
	szMsg[2] = 0x16;

	if(len > 8)
		len = 8;
	
	memcpy(szMsg+3,param,len);
	makeAndSendMessageToModule(MODULE_ID_SYSTEM,MODULE_ID_EXTCAR,szMsg,len + 3);
}

void setMultiContouredSeats_PressurePercentage_UpperLumbar(u8 p1,u8 p2)
{
	u8 szMsg[] = {0x00, 0xFF, 0xFF};
	szMsg[1] = p1;
	szMsg[2] = p2;
	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}

void setMultiContouredSeats_PressurePercentage_MiddleLumbar(u8 p1,u8 p2)
{
	u8 szMsg[] = {0x05, 0xFF, 0xFF};
	szMsg[1] = p1;
	szMsg[2] = p2;
	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}

void setMultiContouredSeats_PressurePercentage_LowerLumbar(u8 p1,u8 p2)
{
	u8 szMsg[] = {0x0A, 0xFF, 0xFF};
	szMsg[1] = p1;
	szMsg[2] = p2;
	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}

void setMultiContouredSeats_PressurePercentage_UpperBolster(u8 p1,u8 p2)
{
	u8 szMsg[] = {0x10, 0xFF, 0xFF};
	szMsg[1] = p1;
	szMsg[2] = p2;
	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}

void setMultiContouredSeats_PressurePercentage_LowerBolster(u8 p1,u8 p2)
{
	u8 szMsg[] = {0x15, 0xFF, 0xFF};
	szMsg[1] = p1;
	szMsg[2] = p2;

	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}

void setMultiContouredSeats_MassageIntensity_Lumbar(u8 p1,u8 p2)
{
	u8 szMsg[] = {0x1A, 0xFF, 0xFF};
	szMsg[1] = p1;
	szMsg[2] = p2;
	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}

void setMultiContouredSeats_MassageIntensity_Cushion(u8 p1,u8 p2)
{
	u8 szMsg[] = {0x20, 0xFF, 0xFF};
	szMsg[1] = p1;
	szMsg[2] = p2;
	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}

void setMultiContouredSeats_Control(u8 side,u8 select,u8 cmd,u8 state)
{
	u8 szMsg[] = {0x25, 0xFF, 0xFF, 0xFF, 0xFF};
	szMsg[1] = side;
	szMsg[2] = select;
	szMsg[3] = cmd;
	szMsg[4] = state;

	LOGD("[Module To MCS]:%x %x %x %x %x",szMsg[0],szMsg[1],szMsg[2],szMsg[3],szMsg[4]);

	if(pLocalParam->uMCS_Available == 0x00)
		return;
	
	if(szMsg[1] == 0xFF || szMsg[2] == 0xFF || szMsg[3] == 0xFF || szMsg[4] == 0xFF)
		return;
	
	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}

void setMultiContouredSeats_Mode(u8 p)
{
	u8 szMsg[] = {0x2A, 0xFF};
	szMsg[1] = p;
	setPublicFord_MultiContouredSeats(szMsg,sizeof(szMsg));
}
