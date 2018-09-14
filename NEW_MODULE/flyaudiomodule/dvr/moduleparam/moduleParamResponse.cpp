#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "moduleParamResponse.h"
#include "otherModuleRequestFunction.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "timer_interface.h"
#include "appRequestCommand.h"


void moduleParameterInit(void){
}

void moduleParameterDeInit(void){
	saveParameter();
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
	}
}

void SetDefaultParam(){
	pLocalParam->bIsChangHe = 0;
	pLocalParam->bDVRDriverInit = false;
	pLocalParam->bDVRModuleState = true;
	pLocalParam->m_iPresentMode = 0;
	pLocalParam->bEnterDVRModuleMark = false;
	pLocalParam->bStopVideo = false;
	pLocalParam->m_wCurrentPage = 0;
	pLocalParam->bEnterDVRModuleMark = false;
	pLocalParam->bMute = true;
	pLocalParam->bPlayOrPause = false;
	pLocalParam->bBrake = false;
	pLocalParam->m_LMode = -1;

	pLocalParam->m_bSystemStartNeedSyncTimeToDNV = true;

	pLocalParam->stUsbCameraWhichOne[USB_CAMERA_WHICH_R].bIsUsbCameraRecording = false;
	pLocalParam->stUsbCameraWhichOne[USB_CAMERA_WHICH_F].bIsUsbCameraRecording = false;
	pLocalParam->emDvrUsbCameraWhichRoad = USB_CAMERA_WHICH_ROAD_SINGLE;
	pLocalParam->bCurIsUsbCameraRecording = false;
		
	pLocalParam->emUsbCameraResolution = DVR_USB_CAMERA_RESOLUTION_1280X720P;
	pLocalParam->emUsbCameraRecordingTimes = CAMERA_RECORDING_TIMES_2M;
	pLocalParam->emUsbCameraStorageSize = CAMERA_STORAGE_SIZE_4G;
	pLocalParam->emUsbCameraStoragePath = CAMERA_STORAGE_PATH_SDCARD;
	pLocalParam->emUsbCameraIsExistDevice = CAMERA_NO_DEVICE;
	pLocalParam->emUsbCameraBrand = CAMERA_BRAND_UNKNOW;
	memset(pLocalParam->uDvrIsSupportResolutions,0,D_IS_SUPPORT_RESOLUTION_MAX);
	pLocalParam->nDvrIsSupportResolutionsCounts = 0;
	pLocalParam->uUsbCameraVideoColor_Level = 0xff;
	pLocalParam->uUsbCameraVideoChrominance_Level = 0xff;
	pLocalParam->uUsbCameraVideoBrightness_Level = 0xff;
	pLocalParam->uUsbCameraVideoContrastGauge_Level = 0xff;
	pLocalParam->bCurIsUsbCameraIsSdCard = false;
	pLocalParam->bCurIsSurportUsbCameraIsSdCard = false;
	pLocalParam->bCurIsDvrInit = true;

	pLocalParam->uIdIsDevice_F = CAMERA_NO_DEVICE;
	pLocalParam->uIdIsDevice_R = CAMERA_NO_DEVICE;

	pLocalParam->uCurEmergencyCollisionSwitchStatus = 0;
	pLocalParam->uCurEmergencyCollisionKeepTimes = 2;

	pLocalParam->bCurIsUsbCameraVideoLock = false;
}

void initByConfig(void){
	LOGD("dvr initByConfig");
	SetDefaultParam();
	readParameter();
	InitDriver();
	
	if(!pLocalParam->bDVRModuleState)
	{
		dvrToApp_SetDVRMenuDisable();
	}

	UsbCameraParamVariable_Real_To_Temp();
	//UI_Usb_Camera_Show_Setting_Info();

	//UI_Usb_Camera_Mono_Road(pLocalParam->emDvrUsbCameraWhichRoad);
	
}

void init_Camera_Recording(u8 state)
{
	SetToHal_DVR_USB_Carema_Recording(state);
	dvrToApp_SetDVR_RecordingDisPlay(state);
}

void moduleParameterReInit(void){
	LOGD("Module_dvr moduleParameterReInit");

}
int module_extendInterface(char *buffer, int len){
	int extendCmd = buffer[0];
	int extendParam = buffer[1];
	LOGD("***********************dvr module_extendInterface:%x,%x",extendCmd,extendParam);
	switch(extendCmd)
	{
		case 0x2C:
		{
			if(extendParam == 0x00)//acc off
			{
				pLocalParam->m_bSystemStartNeedSyncTimeToDNV = false;

				if(pLocalParam->uDvrModule_is_T123 == 1){
					killTimerSyncTimeToDVR();
				  	saveParameter();
				}
			}
			else if(extendParam == 0x01)//reset 
			{
				saveParameter();
			}
			else if(extendParam == 0x02)//default set
			{
				SetDefaultParam();
				saveParameter();
			}
		}
		break;
		case 0x2D:
			if(extendParam == 0x00) //acc on
			{ 				
				pLocalParam->bEnterDVRModuleMark = false;//行车记录仪休眠起来不进入

				pLocalParam->m_bSystemStartNeedSyncTimeToDNV = true;

				if(pLocalParam->uDvrModule_is_T123 == 1){
					setTimerSyncTimeToDVR();
					syncTimeToDVR();
				}
			}
			break;
		case 0xFD:
			{
				//initTimerCenter(&TimerHandlerCenter);
				
				initByConfig();
				
				if(pLocalParam->uDvrModule_is_T123 == 1){
					setTimerSyncTimeToDVR();
					syncTimeToDVR();
				}
			}
			break;
		default:break;
	}
	
	return 0;
}

