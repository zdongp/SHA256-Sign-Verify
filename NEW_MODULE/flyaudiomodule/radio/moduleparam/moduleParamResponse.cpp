#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "appResponseCommand.h"
#include "appRequestCommand.h"
#include "moduleParamResponse.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "otherModuleRequestCommand.h"


void ModuleParamRadioIDChangePara(u8 iID)
{
	switch(iID)
	{
		case 0x00://China
		{
			pLocalParam->st_RadioInitParamInfors[0].usFreqMin = 8740;
			pLocalParam->st_RadioInitParamInfors[0].usFreqMax = 10800;
			pLocalParam->st_RadioInitParamInfors[0].uFreqManualStep = 5;
			pLocalParam->st_RadioInitParamInfors[0].uFreqScanStep = 10;

			/*
			pFlyRadioInfo->radioInfo.iFreqFMMin = 8750;
			pFlyRadioInfo->radioInfo.iFreqFMMax = 10800;
			pFlyRadioInfo->radioInfo.iFreqFMManualStep = 5;
			pFlyRadioInfo->radioInfo.iFreqFMScanStep = 10;

			if (CAR_IX45 == pFlyAllInOneInfo->pMemory_Share_Common->iCarName)
			{
				pFlyRadioInfo->radioInfo.iFreqAMMin = 531;
			}
			else
			{
				pFlyRadioInfo->radioInfo.iFreqAMMin = 522;
			}
			pFlyRadioInfo->radioInfo.iFreqAMMax = 1620;
			pFlyRadioInfo->radioInfo.iFreqAMManualStep = 9;
			pFlyRadioInfo->radioInfo.iFreqAMScanStep = 9;
			*/
			
			pLocalParam->st_RadioInitParamInfors[2].usFreqMin = 522;
			pLocalParam->st_RadioInitParamInfors[2].usFreqMax = 1620;
			pLocalParam->st_RadioInitParamInfors[2].uFreqManualStep = 9;
			pLocalParam->st_RadioInitParamInfors[2].uFreqScanStep = 9;
		}
		break;
		case 0x01://USA
		{
			/*
			pFlyRadioInfo->radioInfo.iFreqFMMin = 8750;
			pFlyRadioInfo->radioInfo.iFreqFMMax = 10790;
			pFlyRadioInfo->radioInfo.iFreqFMManualStep = 5;
			pFlyRadioInfo->radioInfo.iFreqFMScanStep = 20;

			pFlyRadioInfo->radioInfo.iFreqAMMin = 530;
			pFlyRadioInfo->radioInfo.iFreqAMMax = 1720;
			pFlyRadioInfo->radioInfo.iFreqAMManualStep = 10;
			pFlyRadioInfo->radioInfo.iFreqAMScanStep = 10;
			*/

			pLocalParam->st_RadioInitParamInfors[0].usFreqMin = 8750;
			pLocalParam->st_RadioInitParamInfors[0].usFreqMax = 10790;
			pLocalParam->st_RadioInitParamInfors[0].uFreqManualStep = 5;
			pLocalParam->st_RadioInitParamInfors[0].uFreqScanStep = 20;

			pLocalParam->st_RadioInitParamInfors[2].usFreqMin = 522;
			pLocalParam->st_RadioInitParamInfors[2].usFreqMax = 1720;
			pLocalParam->st_RadioInitParamInfors[2].uFreqManualStep = 10;
			pLocalParam->st_RadioInitParamInfors[2].uFreqScanStep = 10;
		}
		break;
		case 0x02://S.Amer-1
		{
			/*
			pFlyRadioInfo->radioInfo.iFreqFMMin = 8750;
			pFlyRadioInfo->radioInfo.iFreqFMMax = 10800;
			pFlyRadioInfo->radioInfo.iFreqFMManualStep = 10;
			pFlyRadioInfo->radioInfo.iFreqFMScanStep = 10;

			pFlyRadioInfo->radioInfo.iFreqAMMin = 530;
			pFlyRadioInfo->radioInfo.iFreqAMMax = 1710;
			pFlyRadioInfo->radioInfo.iFreqAMManualStep = 10;
			pFlyRadioInfo->radioInfo.iFreqAMScanStep = 10;
			*/


			pLocalParam->st_RadioInitParamInfors[0].usFreqMin = 8750;
			pLocalParam->st_RadioInitParamInfors[0].usFreqMax = 10800;
			pLocalParam->st_RadioInitParamInfors[0].uFreqManualStep = 10;
			pLocalParam->st_RadioInitParamInfors[0].uFreqScanStep = 10;

			pLocalParam->st_RadioInitParamInfors[2].usFreqMin = 530;
			pLocalParam->st_RadioInitParamInfors[2].usFreqMax = 1710;
			pLocalParam->st_RadioInitParamInfors[2].uFreqManualStep = 10;
			pLocalParam->st_RadioInitParamInfors[2].uFreqScanStep = 10;
		}
		break;
		case 0x03://S.Amer-2
		{
			/*
			pFlyRadioInfo->radioInfo.iFreqFMMin = 8750;
			pFlyRadioInfo->radioInfo.iFreqFMMax = 10800;
			pFlyRadioInfo->radioInfo.iFreqFMManualStep = 10;
			pFlyRadioInfo->radioInfo.iFreqFMScanStep = 10;

			pFlyRadioInfo->radioInfo.iFreqAMMin = 520;
			pFlyRadioInfo->radioInfo.iFreqAMMax = 1600;
			pFlyRadioInfo->radioInfo.iFreqAMManualStep = 5;
			pFlyRadioInfo->radioInfo.iFreqAMScanStep = 5;
			*/

			pLocalParam->st_RadioInitParamInfors[0].usFreqMin = 8750;
			pLocalParam->st_RadioInitParamInfors[0].usFreqMax = 10800;
			pLocalParam->st_RadioInitParamInfors[0].uFreqManualStep = 10;
			pLocalParam->st_RadioInitParamInfors[0].uFreqScanStep = 10;

			pLocalParam->st_RadioInitParamInfors[2].usFreqMin = 522;
			pLocalParam->st_RadioInitParamInfors[2].usFreqMax = 1600;
			pLocalParam->st_RadioInitParamInfors[2].uFreqManualStep = 5;
			pLocalParam->st_RadioInitParamInfors[2].uFreqScanStep = 5;
		}
		break;
		case 0x04://KOREA
		{
			/*
			pFlyRadioInfo->radioInfo.iFreqFMMin = 8810;
			pFlyRadioInfo->radioInfo.iFreqFMMax = 10790;
			pFlyRadioInfo->radioInfo.iFreqFMManualStep = 5;
			pFlyRadioInfo->radioInfo.iFreqFMScanStep = 20;

			pFlyRadioInfo->radioInfo.iFreqAMMin = 531;
			pFlyRadioInfo->radioInfo.iFreqAMMax = 1620;
			pFlyRadioInfo->radioInfo.iFreqAMManualStep = 9;s
			pFlyRadioInfo->radioInfo.iFreqAMScanStep = 9;
			*/

			pLocalParam->st_RadioInitParamInfors[0].usFreqMin = 8810;
			pLocalParam->st_RadioInitParamInfors[0].usFreqMax = 10790;
			pLocalParam->st_RadioInitParamInfors[0].uFreqManualStep = 5;
			pLocalParam->st_RadioInitParamInfors[0].uFreqScanStep = 20;

			pLocalParam->st_RadioInitParamInfors[2].usFreqMin = 531;
			pLocalParam->st_RadioInitParamInfors[2].usFreqMax = 1620;
			pLocalParam->st_RadioInitParamInfors[2].uFreqManualStep = 9;
			pLocalParam->st_RadioInitParamInfors[2].uFreqScanStep = 9;
		}
		break;
		case 0x05://Thailand
		{
			/*
			pFlyRadioInfo->radioInfo.iFreqFMMin = 8750;
			pFlyRadioInfo->radioInfo.iFreqFMMax = 10800;
			pFlyRadioInfo->radioInfo.iFreqFMManualStep = 5;
			pFlyRadioInfo->radioInfo.iFreqFMScanStep = 25;

			pFlyRadioInfo->radioInfo.iFreqAMMin = 531;
			pFlyRadioInfo->radioInfo.iFreqAMMax = 1602;
			pFlyRadioInfo->radioInfo.iFreqAMManualStep = 9;
			pFlyRadioInfo->radioInfo.iFreqAMScanStep = 9;
			*/

			pLocalParam->st_RadioInitParamInfors[0].usFreqMin = 8750;
			pLocalParam->st_RadioInitParamInfors[0].usFreqMax = 10800;
			pLocalParam->st_RadioInitParamInfors[0].uFreqManualStep = 5;
			pLocalParam->st_RadioInitParamInfors[0].uFreqScanStep = 25;

			pLocalParam->st_RadioInitParamInfors[2].usFreqMin = 531;
			pLocalParam->st_RadioInitParamInfors[2].usFreqMax = 1602;
			pLocalParam->st_RadioInitParamInfors[2].uFreqManualStep = 9;
			pLocalParam->st_RadioInitParamInfors[2].uFreqScanStep = 9;
		}
		break;
		case 0x06://Russia
		{
			/*
			pFlyRadioInfo->radioInfo.iFreqFMMin = 8750;
			pFlyRadioInfo->radioInfo.iFreqFMMax = 10800;
			pFlyRadioInfo->radioInfo.iFreqFMManualStep = 5;
			pFlyRadioInfo->radioInfo.iFreqFMScanStep = 5;

			pFlyRadioInfo->radioInfo.iFreqAMMin = 530;
			pFlyRadioInfo->radioInfo.iFreqAMMax = 1610;
			pFlyRadioInfo->radioInfo.iFreqAMManualStep = 9;
			pFlyRadioInfo->radioInfo.iFreqAMScanStep = 9;
			*/

			pLocalParam->st_RadioInitParamInfors[0].usFreqMin = 8750;
			pLocalParam->st_RadioInitParamInfors[0].usFreqMax = 10800;
			pLocalParam->st_RadioInitParamInfors[0].uFreqManualStep = 5;
			pLocalParam->st_RadioInitParamInfors[0].uFreqScanStep = 5;

			pLocalParam->st_RadioInitParamInfors[2].usFreqMin = 530;
			pLocalParam->st_RadioInitParamInfors[2].usFreqMax = 1610;
			pLocalParam->st_RadioInitParamInfors[2].uFreqManualStep = 9;
			pLocalParam->st_RadioInitParamInfors[2].uFreqScanStep = 9;
		}
		break;
		case 0x07:
		{
			pLocalParam->st_RadioInitParamInfors[0].usFreqMin = 8750;
			pLocalParam->st_RadioInitParamInfors[0].usFreqMax = 10800;
			pLocalParam->st_RadioInitParamInfors[0].uFreqManualStep = 5;
			pLocalParam->st_RadioInitParamInfors[0].uFreqScanStep = 10;
			
			pLocalParam->st_RadioInitParamInfors[2].usFreqMin = 522;
			pLocalParam->st_RadioInitParamInfors[2].usFreqMax = 1620;
			pLocalParam->st_RadioInitParamInfors[2].uFreqManualStep = 9;
			pLocalParam->st_RadioInitParamInfors[2].uFreqScanStep = 9;
		}
		break;
		default:
			break;
	}//switch(iID)

	pLocalParam->fmBeginFreq = pLocalParam->st_RadioInitParamInfors[0].usFreqMin;
	pLocalParam->fmEndFreq = pLocalParam->st_RadioInitParamInfors[0].usFreqMax;
	pLocalParam->amBeginFreq = pLocalParam->st_RadioInitParamInfors[2].usFreqMin;
	pLocalParam->amEndFreq = pLocalParam->st_RadioInitParamInfors[2].usFreqMax;

	LOGD("\n[%s] Radio Area ID---->%d",__FUNCTION__,iID);
	LOGD("\n[%s] Radio Area DefaultParam:(%d %d %d %d)",__FUNCTION__,pLocalParam->fmBeginFreq,pLocalParam->fmEndFreq,pLocalParam->amBeginFreq,pLocalParam->amEndFreq);
}

void ModuleParamDefaultFreqToUI(void)
{
	u16 wFrequency = pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency;
	wFrequency = (wFrequency >> 8) + ((wFrequency & 0xFF) << 8);

	if(FM1 == pLocalParam->eRadioChannel || FM2 == pLocalParam->eRadioChannel)
	{
		if(pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency == 0){
			sprintf((char*)pLocalParam->szCurFreq, "%4.2f MHz",  pLocalParam->fmBeginFreq / 100.0);
		}
		else{
			if(pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency < pLocalParam->st_RadioInitParamInfors[pLocalParam->eRadioChannel].usFreqMin || pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency > pLocalParam->st_RadioInitParamInfors[pLocalParam->eRadioChannel].usFreqMax)
				return;
			//sprintf((char*)pLocalParam->szCurFreq, "%4.2f MHz",  pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency / 100.0);
			sprintf((char*)pLocalParam->szCurFreq, "%4.2f MHz",  wFrequency / 100.0);
		}
	}
	else
	{
		if(pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency == 0){
			sprintf((char*)pLocalParam->szCurFreq, "%d KHz",  pLocalParam->amBeginFreq);
		}
		else{
			if(pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency < pLocalParam->st_RadioInitParamInfors[pLocalParam->eRadioChannel].usFreqMin || pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency > pLocalParam->st_RadioInitParamInfors[pLocalParam->eRadioChannel].usFreqMax)
				return;
			//sprintf((char*)pLocalParam->szCurFreq, "%4.2f MHz",  pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel ].wCurFrequency / 100.0);
			sprintf((char*)pLocalParam->szCurFreq, "%d KHz",  wFrequency);
		}
	}
	
	RadioToApp_CurChannelFreqText(pLocalParam->szCurFreq, strlen((char*)pLocalParam->szCurFreq));
}

void moduleParameterInit(void){
	ModuleParam_RadioInitUI();
}

void moduleParameterDeInit(void){
	ModuleParamResponse_WriteData();
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
	    case CUR_CHANNEL:
	    	*(u8*)param = (u8)pLocalParam->eRadioChannel;
			*paramLen = sizeof(u8);
	    break;
	    case CUR_FREQ:
	    	*(u16*)param = (u16)pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].wCurFrequency;
			*paramLen = sizeof(u16);
	    break;
		default:break; 
	}
}

void ModuleParam_RadioInitUI(void)
{
	ModuleParamRadioIDChangePara(pLocalParam->u8RadioCountryCode);
	RadioToApp_BeginAndEndFreq(pLocalParam->eRadioChannel);
	ModuleParamDefaultFreqToUI();
	RadioToApp_LightCurChannel(pLocalParam->eRadioChannel);
	ModuleRadio_setButtonVisible();
}

void ModuleParamResponse_InitByConfig(void)
{
	radioTohal_InitCmd(0x01);
	InitParamMakeAndSendMessageToHal();
	//radioTohal_RadioSwitch_Power(pLocalParam->bIsRadioPowerOn);
	//radioTohal_ImitateKey(pLocalParam->eRadioChannel + 1);
	//radioTohal_SetSensitivity(pLocalParam->sensitivitystate);
	//radioTohal_RadioSwitch_TA(pLocalParam->radioTAstate);
	//radioTohal_RadioSwitch_AF(pLocalParam->radioAFstate);
}

void InitParamMakeAndSendMessageToHal()
{
	u8 buff[63];
	memset(buff,0,sizeof(buff));

	buff[0] = pLocalParam->bIsRadioPowerOn;
	u8 eCurRadioChannel = pLocalParam->eRadioChannel + 1;
	if(eCurRadioChannel == 2)
	{
		eCurRadioChannel = 1;
	}

	buff[1] = eCurRadioChannel;

	u16 uCurFmFrequency = pLocalParam->stszRadioChannelRecord[0].wCurFrequency;
	memcpy(&buff[2],&uCurFmFrequency,2);
	
	u16 uCurAmFrequency = pLocalParam->stszRadioChannelRecord[2].wCurFrequency;
	memcpy(&buff[4],&uCurAmFrequency,2);

	buff[6] = pLocalParam->radioTAstate;
	buff[7] = pLocalParam->radioAFstate;
	buff[8] = pLocalParam->sensitivitystate;
	buff[9] = pLocalParam->u8RadioCountryCode;

	LOGD("Power:%d CurRadioChannel:%d",buff[0],buff[1]);
	LOGD("FM:%d AM:%d",uCurFmFrequency,uCurAmFrequency);
	LOGD("TA:%d AF:%d sensi:%d CountryCode:%d",buff[6],buff[7],buff[8],buff[9]);
	
	radioTohal_InitParamCmd(buff,10);
}

void ModuleParamResponse_InitParam(void)
{
	LOGD("radio:ModuleParamResponse_InitParam");
	pLocalParam->scanCtrlType = UIACTION_MOUSEUP;
	pLocalParam->afState = 0x00;
	pLocalParam->taState = 0x00;
	pLocalParam->bIsRadioInitOK = false;
	pLocalParam->eScanState = Ctrl_STOP;
	pLocalParam->bIsRadioPowerOn = true;
	pLocalParam->nFlashState = 0x00;
	pLocalParam->searchBeginIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE; 
	pLocalParam->inputFrequency.len = 0;
	pLocalParam->searchSaveIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;
	//pLocalParam->inputNumber = 0;
	memset(pLocalParam->szCurFreq, 0, sizeof(pLocalParam->szCurFreq));
	pLocalParam->eRadioChannel = FM1;
	pLocalParam->bIsHasRadioStationAndInfo = false;
	//memset(pLocalParam->stszRadioChannelRecord);
	memset(&(pLocalParam->stszRadioChannelRecord), 0, sizeof(pLocalParam->stszRadioChannelRecord));
	
	int i;
	for (i = 0; i < CHANNEL_NUM; i++)
	{
		pLocalParam->stszRadioChannelRecord[i].cCurRecordIndex = CHANNEL_RECORD_NUM;
		pLocalParam->stszRadioChannelRecord[i].curPage = 1;
		pLocalParam->stszRadioChannelRecord[i].totalPages = 1;
		memset(pLocalParam->stszRadioChannelRecord[i].bRadioFreqRecordState, 0, sizeof(pLocalParam->stszRadioChannelRecord[i].bRadioFreqRecordState));
		memset(pLocalParam->stszRadioChannelRecord[i].wRadioFreqRecord, 0, sizeof(pLocalParam->stszRadioChannelRecord[i].wRadioFreqRecord));
	}
	memset(pLocalParam->dwszCurChannelCurFreqRecFuncID, 0, sizeof(pLocalParam->dwszCurChannelCurFreqRecFuncID));
	memset(pLocalParam->dwszCurChannelPreFreqRecFuncID, 0, sizeof(pLocalParam->dwszCurChannelPreFreqRecFuncID));

	pLocalParam->bIsNeedCmpWithRecFreq = true;
	pLocalParam->sensitivitystate=0;
	pLocalParam->radioAFstate=0xff;
	pLocalParam->radioTAstate=0;
	memset(pLocalParam->szStationName,0,sizeof(pLocalParam->szStationName));
	pLocalParam->cTAAFVisible=0;

	pLocalParam->bUiButtonDownNoShow = false;

	pLocalParam->u8RadioCountryCode = 7;
	pLocalParam->uPanelKeyTuneTime = 0;
}

void ModuleParamResponse_ReadData(void)
{
	readParameter();
}

void ModuleParamResponse_WriteData(void)
{
	saveParameter();
}


void moduleParameterReInit(void)
{
	LOGD("&&&&&&&&&&&&&&&&&&&& radio moduleParameterReInit");
	radioTohal_ImitateKey(pLocalParam->eRadioChannel + 1);
}
int module_extendInterface(char *buffer, int len)
{
	int extendCmd = buffer[0];
	int extendParam = buffer[1];
	LOGD("**********************radio module_extendInterface:%x,%x",extendCmd,extendParam);
	switch(extendCmd)
	{
		case 0x2C:
			if(extendParam == 0x00)//acc off
			{
				ModuleParamResponse_WriteData();
				
			}
			else if(extendParam == 0x01)// 
			{
				
				ModuleParamResponse_WriteData();
			}
			else if(extendParam == 0x02)//default set
			{
				ModuleParamResponse_InitParam();
				ModuleParamResponse_WriteData();
			}
			break;
		case 0x2D:
			if(extendParam == 0x00) //acc on
			{

				//ModuleParamResponse_InitParam();
				//ModuleParamResponse_ReadData();
		
				//radioTohal_RadioSwitch_Power(pLocalParam->bIsRadioPowerOn);
				//radioTohal_InitCmd(0x01);
				//radioTohal_ImitateKey(pLocalParam->eRadioChannel + 1);
				ModuleParam_RadioInitUI();
				initAuxscreenFreRecordList();
				//ModuleParamResponse_InitByConfig();
			}
			break;
		case 0xFD:
			{
				ModuleParamResponse_InitByConfig();
				initAuxscreenFreRecordList();
			}
			break;
		default :break;
	}		
	return 0;
}

void ModuleRadio_setButtonVisible()
{
     if(pLocalParam->cTAAFVisible==0)
     {
    	 setVisible(CONTROLID_RADIO_MAIN_TA,0x00);
		 setControllable(CONTROLID_RADIO_MAIN_TA,0x00);
		 
    	 setVisible(CONTROLID_RADIO_MAIN_AF,0x00);
		 setControllable(CONTROLID_RADIO_MAIN_AF,0x00);
		 
    	 setVisible(CONTROLID_RADIO_SET_AF_ON,0x00);
		 setControllable(CONTROLID_RADIO_SET_AF_ON,0x00);
		 
    	 setVisible(CONTROLID_RADIO_SET_AF_OFF,0x00);
		 setControllable(CONTROLID_RADIO_SET_AF_OFF,0x00);
		 
    	 setVisible(CONTROLID_RADIO_SET_TA_ON,0x00);
		 setControllable(CONTROLID_RADIO_SET_TA_ON,0x00);
		 
    	 setVisible(CONTROLID_RADIO_SET_TA_OFF,0x00);
		 setControllable(CONTROLID_RADIO_SET_TA_OFF,0x00);
		 
    	 setVisible(CONTROLID_RADIO_SET_AF_TEXT_BK,0x00);
		 setControllable(CONTROLID_RADIO_SET_AF_TEXT_BK,0x00);
		 
    	 setVisible(CONTROLID_RADIO_SET_TA_TEXT_BK,0x00);
		 setControllable(CONTROLID_RADIO_SET_TA_TEXT_BK,0x00);
     }
     LOGD("ModuleRadio_setButtonVisible TAAFVisible=%d",pLocalParam->cTAAFVisible);
}
















