#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamResponse.h"
#include "moduleParamRequest.h"



void Get_DVRDriverInitParam(u8 cInitOrder)
{
	LOGD("Get_DVRDriverInitParam pLocalParam->bDVRDriverInit:%x",pLocalParam->bDVRDriverInit);
	//if((cInitOrder == 0x01) && (pLocalParam->bDVRDriverInit != true))
	//	Set_DVRInitDriver();
}

void Get_DVRDriverInitState(u8 cState)
{
	if(cState == 0x01){
		pLocalParam->bDVRDriverInit = true;
	}
	else{
		pLocalParam->bDVRDriverInit = false;
		dvrToApp_SetDVRMenuDisable();
	}
}

void Get_DVRModuleExistState(u8 cState){
	if(cState == 0x00){
		if(pLocalParam->bDVRModuleState)
		{
			pLocalParam->bStopVideo = false;
		}
		
		dvrToModule_NotifyAuxscreen_State(0x00);	
		dvrToApp_SetDVRMenuDisable();
		
		pLocalParam->bDVRModuleState = false;

		if(pLocalParam->bEnterDVRModuleMark){
			u16 CurPageID = 0;
			u8	CurPageIDLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
			if(CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
			{
				if(CurPageID == PAGE_DRIVING_RECORD_MENU || CurPageID == PAGE_DRIVING_RECORD_PALY || CurPageID == PAGE_DRIVING_RECORD_SET || CurPageID == PAGE_DRIVING_RECORD_TIME_SET || CurPageID == PAGE_DRIVING_RECORD_VIDEO)
				{
					//dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_MENU);
					dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_NO_SIGN);
				}
			}
		}
	}
	else if(cState == 0x01){	
		dvrToApp_SetDVRMenuEnable();
		pLocalParam->bDVRModuleState = true;
	}
}

void Get_DVRChooseWhichPage(u8 cMode)
{
	LOGD("Get_DVRChooseWhichPage m_LMode:%d  bEnterDVRModuleMark:%x pLocalParam->bMute:%x",pLocalParam->m_LMode,pLocalParam->bEnterDVRModuleMark,pLocalParam->bMute);
	u16 CurPageID = 0;
	u8	CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
	
	switch(cMode)
	{
		case 0x00:
		{
			if((pLocalParam->m_LMode != VideoMode) && pLocalParam->bEnterDVRModuleMark)
			{
				if(CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
					dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
				pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_VIDEO;////////
				pLocalParam->bPlayOrPause = false;
				pLocalParam->m_LMode = -1;
			}
			pLocalParam->m_iPresentMode = VideoMode;
		}
		break;
		case 0x01:
		{
			if((pLocalParam->m_LMode != RePlayMode) && pLocalParam->bEnterDVRModuleMark)
			{
				if(CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
					dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_VIDEO);
				pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_PALY;////////
				pLocalParam->bPlayOrPause = false;
				if(!pLocalParam->bMute)
					Set_DVR_SoftWareImitateKeyCtrl(MUTE);
				pLocalParam->m_LMode = -1;
			}
			pLocalParam->m_iPresentMode = RePlayMode;
		}
		break;
		case 0x02:
		{
			if((pLocalParam->m_LMode != SetTimeMode) && pLocalParam->bEnterDVRModuleMark)
			{
				if(CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
					dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_TIME_SET);
				pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_TIME_SET;/////////
				pLocalParam->bPlayOrPause = false;
				if(!pLocalParam->bMute)
					Set_DVR_SoftWareImitateKeyCtrl(MUTE);
				pLocalParam->m_LMode = -1;
			}
			pLocalParam->m_iPresentMode = SetTimeMode;
		}
		break;
		case 0x03:
		{
			if((pLocalParam->m_LMode != SetVideoMode) && pLocalParam->bEnterDVRModuleMark)
			{
				if(CurPageID != PAGE_BACK_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO && CurPageID != PAGE_BACK_FULL_VIDEO_CONTROL)//倒车的时候不能切页
					dvrToModule_NotifySystem_JumpPage(PAGE_DRIVING_RECORD_SET);
				pLocalParam->m_wCurrentPage = PAGE_DRIVING_RECORD_SET;///////////////
				pLocalParam->bPlayOrPause = false;
				if(!pLocalParam->bMute)
					Set_DVR_SoftWareImitateKeyCtrl(MUTE);
				pLocalParam->m_LMode = -1;
			}
			pLocalParam->m_iPresentMode = SetVideoMode;
		}
		break;
		default:break;
	}
	
	LOGD("Get_DVRChooseWhichPage bPlayOrPause:%x  m_LMode:%d  m_iPresentMode:%d",pLocalParam->bPlayOrPause,pLocalParam->m_LMode,pLocalParam->m_iPresentMode);
}

void Get_DVRResolution(u8 cPuf)
{
}

void Get_DVRLanguage(u8 cPuf)
{
}

void Get_DVRRecorderVideoState(u8 cState)
{
	if(cState == 0x00){
		pLocalParam->bStopVideo = false;
		dvrToModule_NotifyAuxscreen_State(0x01);
	}
	else if(cState == 0x01){
		pLocalParam->bStopVideo = true;
		dvrToModule_NotifyAuxscreen_State(0x02);
	}
}

void Get_DVRRecordState(u8 cState)
{
}

void Get_DVRAutoMate(char resCmd,u8 *param,u8 len)
{
    dvrToModule_NotifyAutoMate_State(resCmd,param,len);
}

void Get_UsbCameraError(u8 *param,u8 len)
{
		switch(param[0])
		{
			case 0x01://recording
			break;
			case 0x02://end record
			break;
			case 0x03://
			break;
			case 0x04:
				pLocalParam->uIdIsDevice_F = CAMERA_NO_DEVICE;
			break;
			case 0x05:
			break;
			case 0x06:
			break;
			case 0x07:
			break;
			case 0x08:
			{
				pLocalParam->uIdIsDevice_F = CAMERA_YES_DEVICE;
				pLocalParam->emUsbCameraBrand = CAMERA_BRAND_SONIX;

				//SetToHal_DVR_USB_Carema_GetVesion();
				//SetToHal_DVR_USB_CaremaParamGetSupportResolutions();
				UsbCameraParamVariable_Real_To_Temp();

				//SetToHal_DVR_USB_Carema_SetRecordingTimes((u16)(pLocalParam->emUsbCameraRecordingTimes)*60);
				//SetToHal_DVR_USB_Carema_SetStorageSize((u32)(pLocalParam->emUsbCameraStorageSize)*1024);
				//ToHal_DVR_USB_Carema_StorageFilePath(pLocalParam->emUsbCameraStoragePath);
				//ToHal_DVR_USB_Carema_Resolution(pLocalParam->emUsbCameraResolution);
				
				UI_Usb_Camera_ApplyButton_IsControllable(false);
				//SetToHal_DVR_USB_CaremaParamEnd();

				//UI_Usb_Camera_Show_Setting_Info();

				//LOGD("---pLocalParam->bCurIsUsbCameraRecording:%d",pLocalParam->bCurIsUsbCameraRecording);
				//if(pLocalParam->bCurIsUsbCameraRecording == true){
					//init_Camera_Recording(pLocalParam->bCurIsUsbCameraRecording);
				//}
			}
			break;
			case 0x09:
			{
				pLocalParam->uIdIsDevice_F = CAMERA_YES_DEVICE;
				pLocalParam->emUsbCameraBrand = CAMERA_BRAND_UNKNOW;
				//SetToHal_DVR_USB_Carema_GetVesion();
				//SetToHal_DVR_USB_CaremaParamGetSupportResolutions();
				UsbCameraParamVariable_Real_To_Temp();

				//SetToHal_DVR_USB_Carema_SetRecordingTimes((u16)(pLocalParam->emUsbCameraRecordingTimes)*60);
				//SetToHal_DVR_USB_Carema_SetStorageSize((u32)(pLocalParam->emUsbCameraStorageSize)*1024);
				//ToHal_DVR_USB_Carema_StorageFilePath(pLocalParam->emUsbCameraStoragePath);
				//ToHal_DVR_USB_Carema_Resolution(pLocalParam->emUsbCameraResolution);
				
				UI_Usb_Camera_ApplyButton_IsControllable(false);
				//SetToHal_DVR_USB_CaremaParamEnd();
				
				//UI_Usb_Camera_Show_Setting_Info();
			}
			break;
			case 0x0E:
			case 0x0F:
			break;
			case 0x10://SD_state_no.
				ToUI_USB_CaremaSdcardStatePromt(0);
			break;
			case 0x11://SD_state_yes.
				ToUI_USB_CaremaSdcardStatePromt(1);
			break;
			case 0x12://recording_state_no.
				ToUI_USB_CaremaRecordingStatePromt(0);
			break;
			case 0x13://recording_state_yes.
				ToUI_USB_CaremaRecordingStatePromt(1);
			break;
			case 0x14://sd_card space is not full.
				ToUI_USB_CaremaSdcardStatePromt(1);
			break;
			case 0x15://sd_card space is full.
				ToUI_USB_CaremaSdcardStatePromt(2);
			break;
			case 0x16://yes
			{
				pLocalParam->bCurIsUsbCameraVideoLock = true;
				ToUI_USB_CaremaRecordingLockStatePromt(1);
				ToUI_USB_CaremaRecordingLockStateButton(0x01);
			}
			break;
			case 0x17://no
			{
				pLocalParam->bCurIsUsbCameraVideoLock = false;
				ToUI_USB_CaremaRecordingLockStatePromt(0);
				ToUI_USB_CaremaRecordingLockStateButton(0x00);
			}
			break;
			default:break;
		}

		switch(param[0])
		{
			case 0x50://Format SD Success
				GetAsyncInforsToFormatPromtDialog(0);
				break;
			case 0x51://Format SD error
				GetAsyncInforsToFormatPromtDialog(1);
				break;
			default:break;
		}

		switch(param[0])
		{
			case 0x081://recording
			break;
			case 0x082://end record
			break;
			case 0x083://
			break;
			case 0x084:
				pLocalParam->uIdIsDevice_R = CAMERA_NO_DEVICE;
			break;
			case 0x085:
			break;
			case 0x086:
			break;
			case 0x087:
			break;
			case 0x088:
			{
				pLocalParam->uIdIsDevice_R = CAMERA_YES_DEVICE;
				pLocalParam->emUsbCameraBrand = CAMERA_BRAND_SONIX;
				UsbCameraParamVariable_Real_To_Temp();

				UI_Usb_Camera_ApplyButton_IsControllable(false);
			}
			break;
			case 0x089:
			{
				pLocalParam->uIdIsDevice_R = CAMERA_YES_DEVICE;
				pLocalParam->emUsbCameraBrand = CAMERA_BRAND_UNKNOW;
	
				UsbCameraParamVariable_Real_To_Temp();
				
				UI_Usb_Camera_ApplyButton_IsControllable(false);
			}
			break;
			default:break;
		}

	//if(pLocalParam->uIdIsDevice_F == CAMERA_NO_DEVICE && pLocalParam->uIdIsDevice_R == CAMERA_NO_DEVICE)
	//{
	//	pLocalParam->emUsbCameraIsExistDevice = CAMERA_NO_DEVICE;
	//}
	//else
	//{
	//	pLocalParam->emUsbCameraIsExistDevice = CAMERA_YES_DEVICE;
	//}

	if(pLocalParam->uIdIsDevice_F == CAMERA_YES_DEVICE)
	{
		
		pLocalParam->emUsbCameraIsExistDevice = CAMERA_YES_DEVICE;
	}
	else
	{
		pLocalParam->emUsbCameraIsExistDevice = CAMERA_NO_DEVICE;
	}
}

void Get_UsbCameraInitInfors(u8 *param,int len)
{
	if((len <= 1) || (strcmp((char*)(param),"") == 0))
		return;

//	dyb_log_output("Get_UsbCameraInitInfors ", "param:", (char*)param, len, printLog, TAG);
	
	u8 uBuffer[STRING_MAX_LEN];
	int nBuffer_len;
	int nFrom = 0;
	int nTo = 0;

	while(nTo != -1){
		LOGD("[%s] nFrom:(%d)",__FUNCTION__,nFrom);
		int nTo = Inside_FindIndexFromStr(param + nFrom, len - nFrom,';',0);
		LOGD("[%s] nTo:(%d)",__FUNCTION__,nTo);
		if((len - nFrom) <= 0) return;
		
		if(nTo != 0)
		{
			memset(uBuffer,0,sizeof(uBuffer));
			nBuffer_len = 0;
			
			if((nTo == -1) && (len - nFrom) > 0)
			{
				memcpy(uBuffer,param + nFrom,len - nFrom);
				nBuffer_len = len - nFrom;
			}
			else
			{
				memcpy(uBuffer,param + nFrom,nTo);
				nBuffer_len = nTo;
			}
			
//			dyb_log_output("Get_UsbCameraInitInfors ", "uBuffer: ", (char*)uBuffer, nBuffer_len, printLog, TAG);
			analyseHalMessage_DVR(uBuffer[0],uBuffer+1,nBuffer_len-1);
		}

		if(len - nFrom - nBuffer_len <= 0)
			return;
				
		nFrom = nTo+nFrom;
		nFrom++;
	}
}

void Get_UsbCameraRecordingState(u8 uId,u8 *param)
{
	if(uId == 0x00)
	{
		if(param[0] == 1)
		pLocalParam->uIdIsDevice_R = CAMERA_NO_DEVICE;
		else if(param[0] == 0)
		pLocalParam->uIdIsDevice_R = CAMERA_YES_DEVICE;
	}
	
	if(uId == 0x01)
	{
		if(param[0] == 1)
		pLocalParam->uIdIsDevice_F = CAMERA_NO_DEVICE;
		else if(param[0] == 0)
		pLocalParam->uIdIsDevice_F = CAMERA_YES_DEVICE;
	}

	//if(pLocalParam->uIdIsDevice_F == CAMERA_NO_DEVICE && pLocalParam->uIdIsDevice_R == CAMERA_NO_DEVICE)
	//{
	//	pLocalParam->emUsbCameraIsExistDevice = CAMERA_NO_DEVICE;
	//}
	//else
	//{
	//	pLocalParam->emUsbCameraIsExistDevice = CAMERA_YES_DEVICE;
	//}

	if(pLocalParam->uIdIsDevice_F == CAMERA_YES_DEVICE)
	{
		
		pLocalParam->emUsbCameraIsExistDevice = CAMERA_YES_DEVICE;
	}
	else
	{
		pLocalParam->emUsbCameraIsExistDevice = CAMERA_NO_DEVICE;
	}
	
	
	switch(uId)
	{
		case 0x00://Rear
			{
				if(pLocalParam->stUsbCameraWhichOne[USB_CAMERA_WHICH_R].bIsUsbCameraRecording ==  param[1])
					return;

				pLocalParam->stUsbCameraWhichOne[USB_CAMERA_WHICH_R].bIsUsbCameraRecording =  param[1];
			}
			break;
		case 0x01://Front
			{
				if(pLocalParam->stUsbCameraWhichOne[USB_CAMERA_WHICH_F].bIsUsbCameraRecording == param[1])
					return;

				pLocalParam->stUsbCameraWhichOne[USB_CAMERA_WHICH_F].bIsUsbCameraRecording = param[1];

				dvrToApp_SetDVR_RecordingDisPlay(param[1]);
			}
			break;
		default:break;
	}

	pLocalParam->bCurIsUsbCameraRecording = pLocalParam->stUsbCameraWhichOne[USB_CAMERA_WHICH_F].bIsUsbCameraRecording;
}

void Get_UsbCameraPhotograph(u8 uId,u8 *param)
{
}

void Get_UsbCameraResolutionData(u8 uId,u8 *param,int len)
{
	E_DVR_USB_CAMERA_RESOLUTION emTem = UsbCameraParam_Resolution_String_To_EM(param+1);
	if(emTem != 0xff){
		pLocalParam->emUsbCameraResolution = emTem;//emTem;
		UsbCameraParamVariable_Real_To_Temp();
		UI_Usb_Camera_Resolution(emTem);
	}
}

void Get_UsbCameraRecordingTimes(u8 uId,u8 *param,int len)
{
	u16 sTemp = 0;
	sTemp += (u16)((param[1] << 8) & 0xFF00);
	sTemp += (u16)(param[2] & 0xFF);
	
	if(sTemp == 0)
		return;

	E_DVR_USB_CAMERA_RECORDING_TIMES emT = (E_DVR_USB_CAMERA_RECORDING_TIMES)(sTemp/60);
	switch(emT)
	{
		case CAMERA_RECORDING_TIMES_2M:
		case CAMERA_RECORDING_TIMES_3M:
		case CAMERA_RECORDING_TIMES_5M:
		case CAMERA_RECORDING_TIMES_10M:
			break;
		default:
			return;
			break;
	}
	
	pLocalParam->emUsbCameraRecordingTimes = emT;
	UsbCameraParamVariable_Real_To_Temp();
	UI_Usb_Camera_Recording_Times(pLocalParam->emUsbCameraRecordingTimes);
}

void Get_UsbCameraStorageSize(u8 uId,u8 *param,int len)
{
	u32 sTemp = 0;
	sTemp += (u32)((param[1] << 24) & 0xFF000000);
	sTemp += (u32)((param[2] << 16) & 0xFF0000);
	sTemp += (u32)((param[3] << 8) & 0xFF00);
	sTemp += (u32)(param[4] & 0xFF);
	if(sTemp == 0)
		return;
	
	E_DVR_USB_CAMERA_STORAGE_SIZE emT = (E_DVR_USB_CAMERA_STORAGE_SIZE)(sTemp/1024);
	switch(emT)
	{
		case CAMERA_STORAGE_SIZE_2G:
		case CAMERA_STORAGE_SIZE_4G:
		case CAMERA_STORAGE_SIZE_8G:
		case CAMERA_STORAGE_SIZE_16G:
			break;
		default:
			return;
			break;
	}
	pLocalParam->emUsbCameraStorageSize = emT;
	UsbCameraParamVariable_Real_To_Temp();
	UI_Usb_Camera_Storage_Size(pLocalParam->emUsbCameraStorageSize);
}

void Get_UsbCameraStoragePath(u8 uId,u8 *param,int len)
{
	LOGD("[%s] param:%s",__FUNCTION__,param+1);
	E_DVR_USB_CAMERA_STORAGE_PATH uCmd = UsbCameraParam_StorageFilePath_String_To_EM((char*)(param+1));
	if(uCmd == CAMERA_STORAGE_PATH_SDCARD)
	{
		if(param[0] != 0x00)
		{
			pLocalParam->bCurIsUsbCameraIsSdCard = true;
		}
		else if(param[0] == 0x00)
		{
			pLocalParam->bCurIsUsbCameraIsSdCard = false;
		}
	}

	if(uCmd == 0xff)
		return;

	if(pLocalParam->emUsbCameraStoragePath == (E_DVR_USB_CAMERA_STORAGE_PATH)uCmd)
		return;

	if(uCmd == CAMERA_STORAGE_PATH_SDCARD)
	{
		if(param[0] != 0x00)
		{
			dvr_NotifyApp_SdCard_State(0x00,0x01);
		}
	}
	
	pLocalParam->emUsbCameraStoragePath = (E_DVR_USB_CAMERA_STORAGE_PATH)uCmd;
	UsbCameraParamVariable_Real_To_Temp();
	DisplayUI_Usb_Camera_Storage_Path(param+1,len);
}

int Inside_FindIndexFromStr(const u8 *pSrc, int nSrcLen, u8 cLetter, int nStart)
{
	int i;
	for (i = nStart; i < nSrcLen; i++){
		if (cLetter == pSrc[i]){
			return i;
		}
	}
	return -1;
}


void Get_UsbCameraSupportResolutions(u8 uId,u8 *param,int len)
{
	int nLen = strlen((char*)param);
	if((nLen <= 1) || (strcmp((char*)(param),"") == 0))
		return;

	LOGD("[%s] %s (%d)",__FUNCTION__,param,nLen);
	u8 uBuffer[STRING_MAX_LEN];
	int nBuffer_len;
	int nFrom = 0;
	int nTo = 0;
	int nU = 0;
	memset(pLocalParam->uDvrIsSupportResolutions,0,sizeof(pLocalParam->uDvrIsSupportResolutions));
	pLocalParam->nDvrIsSupportResolutionsCounts = 0;
	
	while(-1 != nTo)
	{
		LOGD("[%s] nFrom:(%d)",__FUNCTION__,nFrom);
		int nTo = Inside_FindIndexFromStr(param + nFrom, nLen - nFrom, ',',0);
		LOGD("[%s] nTo:(%d)",__FUNCTION__,nTo);
		if(nTo != 0)
		{
			memset(uBuffer,0,sizeof(uBuffer));
			nBuffer_len = 0;
			
			if((nTo == -1) && (nLen - nFrom) > 0)
			{
				memcpy(uBuffer,param + nFrom,nLen - nFrom);
			}
			else
			{
				memcpy(uBuffer,param + nFrom,nTo);
			}
			nBuffer_len = strlen((char*)uBuffer);
			LOGD("[%s] uBuffer:%s (%d)",__FUNCTION__,uBuffer,nBuffer_len);
			
			E_DVR_USB_CAMERA_RESOLUTION p = UsbCameraParam_Resolution_String_To_EM(uBuffer);
			if(p != 0xFF)
			{
				if(pLocalParam->nDvrIsSupportResolutionsCounts > D_IS_SUPPORT_RESOLUTION_MAX)
					return;
				
				pLocalParam->uDvrIsSupportResolutions[nU] = (u8)p;
				nU++;
				pLocalParam->nDvrIsSupportResolutionsCounts = nU;
				LOGD("[%s] pLocalParam->nDvrIsSupportResolutionsCounts:(%d)",__FUNCTION__,pLocalParam->nDvrIsSupportResolutionsCounts);
			}
		}

		if(nLen - nFrom - nBuffer_len <= 0)
			return;
				
		nFrom = nTo+nFrom;
		nFrom++;
	}


	if(pLocalParam->nDvrIsSupportResolutionsCounts == 0)
		return;
	
	for(int n = 0;n < pLocalParam->nDvrIsSupportResolutionsCounts;n++)
	{
		if(pLocalParam->uDvrIsSupportResolutions[n] == (u8)pLocalParam->emUsbCameraResolution)
		{
			LOGD("[%s] pLocalParam->emUsbCameraResolution:(%d)",__FUNCTION__,pLocalParam->emUsbCameraResolution);
			ToHal_DVR_USB_Carema_Resolution(pLocalParam->emUsbCameraResolution);
			break;
		}
	}
	
}

void Get_UsbCameraVideoParam(u8 uId,u8 *param)
{
	if(param[0] != 0)
		return;

	u8  uType = param[1];
	u8  uData = param[2];
	
	u8 uLevel = 0xff;
	
	if(UsbCamera_SetVideoParam_Data_To_Level((E_DVR_USB_CAMERA_SET_VIDEO_TPYE)uType,uData,&uLevel))
	{
		if(uLevel != 0xff)
		{
			DisplayingUI_GetUsbCameraVideoSettingParam((E_DVR_USB_CAMERA_SET_VIDEO_TPYE)uType,uLevel);
			switch(uType)
			{
				case TPYE_VIDEO_COLOR:
					pLocalParam->uUsbCameraVideoColor_Level = uLevel;
					break;
				case TPYE_VIDEO_CHROMINANCE:
					pLocalParam->uUsbCameraVideoChrominance_Level = uLevel;
					break;
				case TPYE_VIDEO_BRIGHTNESS:
					pLocalParam->uUsbCameraVideoBrightness_Level = uLevel;
					break;
				case TPYE_VIDEO_CONTRAST_GAUGE:
					pLocalParam->uUsbCameraVideoContrastGauge_Level = uLevel;
					break;
				default:break;
			}
		}
	}
}

void Get_UsbCameraSwitchOneRecordingMod(u8 uId,u8 *param)
{
	if((E_DVR_USB_CAMERA_WHICH_ROAD)uId == USB_CAMERA_WHICH_ROAD_DOUBLE)
	{
		if(pLocalParam->uIdIsDevice_F == CAMERA_NO_DEVICE || pLocalParam->uIdIsDevice_R == CAMERA_NO_DEVICE)
		{
			pLocalParam->bCurIsSurportUsbCameraIsSdCard = true;
		}
		else
		{
			pLocalParam->bCurIsSurportUsbCameraIsSdCard = false;
		}
	}

	if(pLocalParam->emDvrUsbCameraWhichRoad != (E_DVR_USB_CAMERA_WHICH_ROAD)uId)
	{
		if((E_DVR_USB_CAMERA_WHICH_ROAD)uId == USB_CAMERA_WHICH_ROAD_DOUBLE)
		{
			if(pLocalParam->uIdIsDevice_F == CAMERA_NO_DEVICE || pLocalParam->uIdIsDevice_R == CAMERA_NO_DEVICE)
			{
				dvr_NotifyApp_SdCard_State(0x01,0x01);
			}
		}
		pLocalParam->emDvrUsbCameraWhichRoad = (E_DVR_USB_CAMERA_WHICH_ROAD)uId;
		UsbCameraParamVariable_Real_To_Temp();
		UI_Usb_Camera_Mono_Road(pLocalParam->emDvrUsbCameraWhichRoad);
	}
}

void Get_UsbCameraMemoryCardToFormatInfor(u8 *p)
{
	switch(p[0])
	{
		case 0x00://No SD
			break;
		case 0x01://doing
			break;
		default:break;
	}

	GetSyncInforsToFormatPromtDialog(p[0]);
}

void Get_UsbCameraMemoryCardToSwitchEmergencyCollision(u8 param)
{
	pLocalParam->uCurEmergencyCollisionSwitchStatus = param;
	if(param == 0)
	{
		setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_EMERGENCY_COLLISION_SWITCH, true);
	}
	else if(param == 1)
	{
		setDigitalData(CONTROLID_DRIVING_USB_CAREMA_SETTING_EMERGENCY_COLLISION_SWITCH, false);
	}
}

void Get_UsbCameraRecordingTextKeepTimes_EC(u8 param)
{
	if(param > USB_CAMERA_KEEP_TIMES_MAX || param < USB_CAMERA_KEEP_TIMES_MIN)
		return;

	pLocalParam->uCurEmergencyCollisionKeepTimes = param;
	ToUI_KeepTimesOfEmergencyCollision(param);
}

void Get_CurBackCarCameraProtocol(u8 p)
{
	dvrToModule_NotifySystem_BackCarProtocolState(p);
}

void Get_UsbCameraRecordingSensitivity(u8 p)
{
	ToUI_USB_CaremaSensitivityStateButton(p);
}

void Get_UsbCameraRecordingVideoLock(u8 p)
{
	pLocalParam->bCurIsUsbCameraVideoLock = p;
	ToUI_USB_CaremaRecordingLockStateButton(p);
}

void analyseUsbCameraMsg(char resCmd, unsigned char *param, unsigned char len)
{
	u8 uDeviceID = param[0];
	switch(resCmd)
	{
		case 0x40:
			Get_UsbCameraRecordingState(uDeviceID,param+1);
		break;
		case 0x41:
			Get_UsbCameraPhotograph(uDeviceID,param+1);
			break;
		case 0x42:
			Get_UsbCameraResolutionData(uDeviceID,param+1,len-1);
		break;
		case 0x43:
			Get_UsbCameraRecordingTimes(uDeviceID,param+1,len-1);
		break;
		case 0x44:
			appToDvr_UsbCameraVersion(uDeviceID,param+1,len-1);
			break;
		case 0x45:
			Get_UsbCameraStorageSize(uDeviceID,param+1,len-1);
		break;
		case 0x46:
			Get_UsbCameraStoragePath(uDeviceID,param+1,len-1);
		break;
		case 0x47:
			break;
		case 0x48:
			//Get_UsbCameraSupportResolutions(uDeviceID,param+1,len-1);
			break;
		case 0x60:
			Get_UsbCameraVideoParam(uDeviceID,param+1);
			break;
		case 0x61:
			Get_UsbCameraSwitchOneRecordingMod(uDeviceID,param+1);
			break;
		case 0x62:
			Get_UsbCameraMemoryCardToSwitchEmergencyCollision(param[0]);
			break;
		case 0x63:
			Get_UsbCameraMemoryCardToFormatInfor(param);
			break;
		case 0x64:
			Get_UsbCameraRecordingTextKeepTimes_EC(param[0]);
			break;
		case 0x65:
			Get_CurBackCarCameraProtocol(param[0]);
			break;
		case 0x66:
			Get_UsbCameraRecordingSensitivity(param[0]);
			break;
		case 0x67:
			Get_UsbCameraRecordingVideoLock(param[0]);
			break;
		case 0xa0:
			Get_UsbCameraError(param,len);
		break;
		case 0xb0:
			Get_UsbCameraInitInfors(param,len);
			break;
		default:break;	
	}

}

void analyseHalMessage_DVR(char resCmd, unsigned char *param, unsigned char len)
{
	LOGD("analyseHalMessage_DVR resCmd:%x param[0]:%x param[1]:%x,param[2]:%x len:%d",resCmd,param[0],param[1],param[2],len);
	switch(resCmd)
	{
		case 0x01://返回初始化命令
			Get_DVRDriverInitParam(param[0]);
		break;
		case 0x02://返回初始状态
			Get_DVRDriverInitState(param[0]);
		break;
		case 0x03://是否有DVR模块
	 		Get_DVRModuleExistState(param[0]);
	 	break;
	 	case 0x10://返回当前状态
	 		Get_DVRChooseWhichPage(param[0]);
	 	break;
	 	case 0x11://返回分辨率
			 Get_DVRResolution(param[0]);
	 	break;
	 	case 0x12://返回语种
			Get_DVRLanguage(param[0]);
	 	break;
	 	case 0x14://返回录制视频状态
			Get_DVRRecorderVideoState(param[0]);
	 	break;
	 	case 0x15://返回录音状态
			Get_DVRRecordState(param[0]);
	 	break;
	 	case 0x16://返回升级状态
	 	break;
	 	case 0x17://工厂、产品和设备地址
	 	break;
	 	case 0x1E:
	 	    Get_DVRAutoMate(resCmd,param,len);
	 	break;

		case 0x40:
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x45:
		case 0x46:
		case 0x47:
		case 0x48:
		case 0x60:
		case 0x61:
		case 0x62:
		case 0x63:
		case 0x64:
		case 0x65:
		case 0x66:
		case 0x67:
		case 0xA0:
		case 0xB0:
			analyseUsbCameraMsg(resCmd,param,len);
			break;
	 	default:break;  
	}

}


