/* fengxingxing    2015/7/22      */

#include <stdio.h>
#include <stdlib.h>

#include "CNotifyAndResponseFlyJniSdk.h"

#include "otherModuleRequestCommand.h"
#include "otherModuleResponseCommand.h"
#include "appResponseFunction.h"
#include "appRequestCommand.h"

#include "halRequestFunction.h"
#include "param.h"
//#include "global.h"

CNotifyAndResponseFlyJniSdk:: CNotifyAndResponseFlyJniSdk(void)
{

}

CNotifyAndResponseFlyJniSdk:: ~CNotifyAndResponseFlyJniSdk(void)
{


}

void CNotifyAndResponseFlyJniSdk::getFlyJniSdkMessage(u8* p, u8 len)
{	
	switch(p[0])
	{
		case 0x01:
			appToRadio_TurnOFF_MouseUp();
		break;
		case 0x02:
		{
			pLocalParam->bUiButtonDownNoShow = false;
			appToRadio_Scan_Inc_MouseUp();
		}
		break;
		case 0x03:
		{				
			pLocalParam->bUiButtonDownNoShow = false;
			appToRadio_Scan_Dec_MouseUp();
		}
		break;
		case 0x04:
			appToRadio_Scan_MouseUp();
		break;
		case 0x05:
		{
			pLocalParam->bUiButtonDownNoShow = false;
			OtherModuleResponse_ProcessPanelKey_SEEK_DEC();
			
		}
		break;
		case 0x06:
		{
			pLocalParam->bUiButtonDownNoShow = false;
			OtherModuleResponse_ProcessPanelKey_SEEK_INC();
		}
		break;
		case 0x07:
		{
			pLocalParam->bUiButtonDownNoShow = false;
			if(p[1] == 0){
				appToRadio_RadioChannel_MouseUp(AM);
			}
			else if(p[1] == 1){
				appToRadio_RadioChannel_MouseUp(FM1);
			}
		}
		break;
		case 0x08:
		{
			LOGD("[%s] Channel:%d len:%d",__FUNCTION__,p[1],len);
			if(len != 6)return;
			
			pLocalParam->bUiButtonDownNoShow = false;

			int nFrequency = 0;
			nFrequency += (int)((p[2] << 24) & 0xFF000000);
			nFrequency += (int)((p[3] << 16) & 0xFF0000);
			nFrequency += (int)((p[4] << 8) & 0xFF00);
			nFrequency += (int)(p[5] & 0xFF);
			LOGD("[%s] nFrequency:%d",__FUNCTION__,nFrequency);

			
			if(p[1] == 0){
				appToRadio_RadioChannel_MouseUp(AM);
				sprintf((char *)pLocalParam->inputFrequency.frequencyNumber,"%s",  nFrequency);
			}
			else if(p[1] == 1){
				appToRadio_RadioChannel_MouseUp(FM1);

				double lfFrequency = (double)(nFrequency / 100.0);
				sprintf((char *)pLocalParam->inputFrequency.frequencyNumber,"%.2lf",  lfFrequency);
			}
			
			pLocalParam->inputFrequency.len = len - 2;
			
			appToRadio_Analyze_FrequencyMessage();
			clearInputFreq();
		}
		break;
		case 0x09:
		{
			if(p[1] == 0){
				radioTohal_SetSensitivity(1);
			}
			else if(p[1] == 1){
				radioTohal_SetSensitivity(0);
			}
			else if(p[1] == 2){
				radioTohal_SetSensitivity(2);
			}
		}
		break;
		case 0xFE:
			analyseFormSdkMessageRadio(p+1,len -1);
		break;
		case 0xFF:
			analyseSdkToRadioPlayCtrlMessage(p+1,len -1);
		break;
		default:break;
	}
}

void CNotifyAndResponseFlyJniSdk:: sendToSdkFreNum(u16 freNum)
{
	LOGD("Enter function : [%s],freNum:%d",__FUNCTION__,freNum);
	u8 buf[32] = {0};
	buf[0] = 0x02;
	memcpy(&buf[1],&freNum,2);
	 makeAndSendMessageToModule(MODULE_ID_RADIO,MODULE_ID_FLYJNISDK,buf,3);
}

void CNotifyAndResponseFlyJniSdk:: sendToSdkFreSection(u8 nChannel)
{	
	LOGD("Enter function : [%s],nChannel:%d",__FUNCTION__,nChannel);
	u8 buf[32] = {0};
	buf[0] = 0x01;
	buf[1] = nChannel;
	 makeAndSendMessageToModule(MODULE_ID_RADIO,MODULE_ID_FLYJNISDK,buf,2);

}

void CNotifyAndResponseFlyJniSdk::sendToSdkRadioPowerStatus(u8 nState)
{
	LOGD("Enter function : [%s]",__FUNCTION__);
	u8 buf[32] = {0};
	buf[0] = 0x00;
	buf[1] = nState;
	 makeAndSendMessageToModule(MODULE_ID_RADIO,MODULE_ID_FLYJNISDK,buf,2);

}

void CNotifyAndResponseFlyJniSdk::analyseFormSdkMessageRadio(u8 *param, int len)
{
	switch(param[0])
	{
		case 0x01:
		{
			if(param[1] == 0x00)
				ExternalResponseToRadio_Close();
			else if(param[1] == 0x01)
				ExternalResponseToRadio_Open();
			else if(param[1] == 0x02)
				ExternalResponseToRadio_Open_No_Jump();
		}
		break;
		case 0x02:
			if(param[1] == 0x00)
			{
				appToRadio_RadioChannel_MouseUp(0x00);
			}
			else if(param[1] == 0x01)
			{
				appToRadio_RadioChannel_MouseUp(0x02);
			}
			break;
		case 0x03:
			sdkToRadioSetChannelAndFre(param+1,len -1);
			break;
		case 0x00:
			analyseSdkRequitRadioInfo(param[1]);
			break;
		case 0x04:
			analyseSdkRequitSetRadioScan(param[1]);
			break;
		default:break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseSdkRequitRadioInfo(u8 param)
{
	switch(param)
	{
		case 0x01: //get Switch Status
			sendToApp_RadioSwitch(pLocalParam->bIsRadioPowerOn);
			break;
		case 0x02: //get F/Am and Fre
			sdkGetCurRadioChanelAndfre();
			break;
		default:
			LOGD("[%s] :%x",__FUNCTION__,param);
			break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseSdkRequitSetRadioScan(u8 param)
{
	switch(param)
	{
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x03:
			radioTohal_ScanCtrl(param);
			break;
		case 0x04:
			sdkToModuleSetRepeatScan();
			break;
		case 0x05:
		case 0x06:
			radioTohal_ScanCtrl(param);
			break;
		default:
			LOGD("[%s] :%x",__FUNCTION__,param);
			break;
	}
}


/*****************************/
void CNotifyAndResponseFlyJniSdk::sendToAppRadioSatusInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = MESSAGETYPE_STATUS;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToRadioFlyJniSdkService(MODULE_SDK_RADIO, szMsg,len+1);
}
/****************************/
void CNotifyAndResponseFlyJniSdk::sendToApp_RadioSwitch(u8 param)
{
	u8 buf[] = {0x01,param};
	sendToAppRadioSatusInfo(buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToApp_RadioChanelAndFre(u8 param,u16 fre)
{
	u8 buf[4] = {0};
	buf[0] = 0x02;
	buf[1] = param;
	memcpy(buf+2,&fre,2);
	sendToAppRadioSatusInfo(buf,4);
}

void CNotifyAndResponseFlyJniSdk::sendToApp_RadioScanChanelAndFre(u8 param,u16 fre)
{
	u8 buf[4] = {0};
	buf[0] = 0x03;
	buf[1] = param;
	memcpy(buf+2,&fre,2);
	sendToAppRadioSatusInfo(buf,4);
}

void CNotifyAndResponseFlyJniSdk::sdkGetCurRadioChanelAndfre()
{
	u16 wFrequency = pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].wCurFrequency ;
	wFrequency = (wFrequency >> 8) + ((wFrequency & 0xFF) << 8);
	if(pLocalParam->eRadioChannel == FM1 || pLocalParam->eRadioChannel == FM2)
		sendToApp_RadioChanelAndFre(0x00,wFrequency);
	else 
		sendToApp_RadioChanelAndFre(0x01,wFrequency);
}

void CNotifyAndResponseFlyJniSdk::sendToSdkRadioScanChanelAndfre(u16 param)
{
	u16 wFrequency = param;
	wFrequency = (wFrequency >> 8) + ((wFrequency & 0xFF) << 8);
	if(pLocalParam->eRadioChannel == FM1 || pLocalParam->eRadioChannel == FM2)
		sendToApp_RadioScanChanelAndFre(0x00,wFrequency);
	else 
		sendToApp_RadioScanChanelAndFre(0x01,wFrequency);
}

void CNotifyAndResponseFlyJniSdk::sendToApp_RadioScanStatus(u8 param)
{
	u8 buf[] = {0x04,param};
	sendToAppRadioSatusInfo(buf,2);
}

/****************************/
void CNotifyAndResponseFlyJniSdk::sdkToRadioSetChannelAndFre(u8 *param ,int len)
{
	u8 tempChannel = 0x00;
	if(param[0] == 0x00)
		tempChannel =0x01;
	 else if(param[0] == 0x01)
	 	tempChannel = 0x03;
	 else 
	 {
	 	LOGD("[%s] error data: %x",param[0]);
	 	return;
	 }
	 u16 tempFre = param[1] + (param[2]*256);
	radioTohal_SetChannelAndFre(tempChannel,tempFre);
}

/*************ctrl radio play sdk message************/
void CNotifyAndResponseFlyJniSdk::analyseSdkToRadioPlayCtrlMessage(u8 *param,int len)
{
	if(param[0] == 0x00)
	{
		switch(param[1])
		{
			case 0x00://Prev
			OtherModuleResponse_ProcessPanelKey_SEEK_DEC();
			break;
			case 0x01://Next
			OtherModuleResponse_ProcessPanelKey_SEEK_INC();
			break;
			case 0x02://pause
			ExternalResponseToRadio_Close();
			break;
			case 0x03://play
			ExternalResponseToRadio_Open_No_Jump();
			break;
			case 0x04://stop
			ExternalResponseToRadio_Close();
			break;
			default:break;
		}
	}
}