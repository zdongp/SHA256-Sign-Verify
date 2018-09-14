#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestCommand.h"
#include "moduleParamResponse.h"
#include "appRequestCommand.h"
#include "moduleParamRequest.h"

//fengxingxing 2015/7/23
//#include "CNotifyAndResponseFlyJniSdk.h"
//CNotifyAndResponseFlyJniSdk  g_notifyAndResponseFlyJniSdk ;

void analyseHalMessage_RADIO(char resCmd, unsigned char *param, unsigned char len){
	
	if(resCmd != 0x10)
		LOGD("[%s] resCmd:%x,param:%x,%x len:%d",__FUNCTION__,resCmd,param[0],param[1],len);
		
	if(resCmd == 0x10 || resCmd == 0x14)//Send AutoMate
	{
	    halToAutoMate(resCmd,param,len);
	}

	switch(resCmd){
		case 0x01:
			halToRadio_InitParam(param[0]);
			break;
		case 0x02:
		    halToRadio_InitState(param[0]);
			break;
		case 0x09:
			{
			       halToRadio_FrequencyChannel(param[0] -1);
			       unsigned short curFreq = 0;
			       curFreq = (unsigned short)(((param[2] << 8) & 0xFF00) + (param[1] & 0xFF));
			       halToRadio_Frequency(curFreq);
			}
			break;
		case 0x10:{//���ص�ǰƵ��
				unsigned short curFreq = 0;
				curFreq = (unsigned short)(((param[1] << 8) & 0xFF00) + (param[0] & 0xFF));
				halToRadio_Frequency(curFreq);
			}
			break;
		case 0x13:
			halToRadio_ScanCtrlState(param[0]);
			break;
		case 0x14://������̨
		        halToRadio_SearchState();
			break;
		case 0x15://��������
		        halToRadio_PowerState(param[0]);
			break;
		case 0x16://AF����
			halToRadio_AFState(param[0]);
			break;
		case 0x17:
			halToRadio_TAState(param[0]);
			break;
		case 0x18:
		    halToRadio_FlickerCtrl(param[0]);
			break;
		case 0x20:
			halToRadio_FrequencyChannel(param[0]);
			break;
		case 0x21:
		    halToRadio_FrequencyName(param, len);
			break;
		case 0x22:
			halToRadio_CurTextInfo(param, len);
			break;
		case 0x23:
			halToRadio_CurProgaramType(param[0]);
			break;
		case 0x24:
			//halTRadio_Switch_AF(param[0]);
			break;
		case 0x25:
			//halTRadio_Switch_TP(param[0]);
			break;
		case 0x26:
			//halTRadio_Switch_TA(param[0]);
			break;
		case 0x40:
			halToRadio_AreaChoose(param, len);
			break;
		case 0x41:
			RadioToApp_Set_Switch_AF(param[0]);
			break;
		case 0x42:
			RadioToApp_Set_Switch_TA(param[0]);
			break;
		case 0x43:
			RadioToApp_Get_sensitivityState(param[0]);
			break;
		default:
			break;
	}
}

void halToRadio_InitParam(u8 nParam){
//	radioTohal_RadioSwitch_AF(pLocalParam->afState);//AF ����
//	radioTohal_RadioSwitch_TA(pLocalParam->taState);//TA ����
//	RadioToApp_Set_Switch_AF(pLocalParam->afState);//set page af state
//	RadioToApp_Set_Switch_TA(pLocalParam->taState);//set page ta state
		radioTohal_RadioSwitch_AF(pLocalParam->radioAFstate);//AF ����
		radioTohal_RadioSwitch_TA(pLocalParam->radioTAstate);//TA ����
		RadioToApp_Set_Switch_AF(pLocalParam->radioAFstate);//set page af state
		RadioToApp_Set_Switch_TA(pLocalParam->radioTAstate);//set page ta state

}//��ʼ������

void halToRadio_InitState(u8 nState)
{
	if(nState == 0x01)
	{
		pLocalParam->bIsRadioInitOK = true;
		RadioToApp_IsCanVisitRadio(true);
	}
	else
	{
		pLocalParam->bIsRadioInitOK = false;
		RadioToApp_IsCanVisitRadio(false);
	}
}//��ʼ��״̬

void halToAutoMate(char resCmd, unsigned char *param, unsigned char len)
{
    radioToModule_NotifyAutoMate_State(resCmd,param,len);
}

void halToRadio_Frequency(u16 nFrequency)
{
	u16 prePage = 0;
	u16 curPage = 0;
	int DVDSound;

	bool sendToOsdTag = false;
	unsigned char prePageLen, curPageLen, soundLen;
	getOtherModuleParam(MODULE_ID_SYSTEM,PREV_PAGE, (u8 *)&prePage,(u8 *)&prePageLen);
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,(u8 *)&curPageLen);

	radioToModule_AUXScreen_RadioFrequency(nFrequency);

	u8 cChannel = pLocalParam->eRadioChannel;
	if (pLocalParam->stszRadioChannelRecord[cChannel].wCurFrequency != nFrequency)
	{
		if (pLocalParam->bIsHasRadioStationAndInfo)
		{
			RadioToApp_ClearRadioStationNameAndInfo();
		}
	}
	if(pLocalParam->stszRadioChannelRecord[cChannel].wCurFrequency == nFrequency)
		sendToOsdTag = true;
	pLocalParam->stszRadioChannelRecord[cChannel].wCurFrequency = nFrequency;
	u16 wFrequency = nFrequency;
	wFrequency = (wFrequency >> 8) + ((wFrequency & 0xFF) << 8);
	LOGD("--->>>>halToRadio Frequency :%d",  wFrequency);
	
	g_clsNotifyAndResponseFlyJniSdk.sendToSdkFreNum( wFrequency);                   //fre num send to SDK
	
	u16 beginFreq = 0;
	if (FM1 == pLocalParam->eRadioChannel || FM2 == pLocalParam->eRadioChannel)
	{
		sprintf((char*)pLocalParam->szCurFreq, "%4.2f MHz",  wFrequency / 100.0);
		beginFreq = pLocalParam->fmBeginFreq ;
		g_clsNotifyAndResponseFlyJniSdk.sendToApp_RadioChanelAndFre(0x00,wFrequency);
	}
	else
	{
		sprintf((char*)pLocalParam->szCurFreq, "%d KHz",  wFrequency);
		beginFreq =  pLocalParam->amBeginFreq;
		g_clsNotifyAndResponseFlyJniSdk.sendToApp_RadioChanelAndFre(0x01,wFrequency);
	}

	u16 CurPageID = 0;
	u8  CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);
	u8  HomePageOSDDrop = 0;
	u8  HomePageOSDDroplen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_HOMEPAGE_OSD_VISIBLE,(u8*)&HomePageOSDDrop,&HomePageOSDDroplen);
	if(HomePageOSDDrop == 0 && CurPageID == PAGE_THIRD_PAGE)
	{
		LOGD("[%s]HomePageOSDDrop= %d",__FUNCTION__,HomePageOSDDrop);
	}
	else
	{
		if(CurPageID != PAGE_RADIO_MAIN && CurPageID != PAGE_MEDIA && !sendToOsdTag)
		{
			u16 sound = 0;
			u8 soundLen = 0;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&sound,&soundLen);
			if(sound == 0x04 /* !pLocalParam->acc_on */){

				LOGD("\nRadio Frequency %d,%d",nFrequency,wFrequency);
				if(FM1 == pLocalParam->eRadioChannel || FM2 == pLocalParam->eRadioChannel)
					radioToModule_NotifyOsd_ShowFrequecy(0x0, wFrequency,0x01);
				else if(AM == pLocalParam->eRadioChannel)
					radioToModule_NotifyOsd_ShowFrequecy(0x1, wFrequency,0x00);
				radioToModule_NotifyOsd_ShowTitle();//显示下拉
			}
			else{
					// set acc_on false
			}
		}
	}
	
	if(pLocalParam->bIsNeedCmpWithRecFreq) //�ж��ǲ���Ҫ�ͼ�¼��Ƚϵ�״̬:true Ҫ���ж�,false  �����ж�
	{
		IsCurFreqInRecord((u16)cChannel, (u16)nFrequency);
	}
	pLocalParam->bIsNeedCmpWithRecFreq = true;

//	setUpdateUI(0x00);
    if(pLocalParam->curStep != 0)
	    setAnalogData(CONTROLID_RADIO_MAIN_CHANNEL_GUANG, (wFrequency - beginFreq)/pLocalParam->curStep);
	
	RadioToApp_CurChannelFreqText(pLocalParam->szCurFreq, strlen((char*)pLocalParam->szCurFreq));
	
//	setUpdateUI(0x01);
}//Ƶ��

void halToRadio_ScanCtrlState(u8 nState)
{
	pLocalParam->eScanState = (E_CtrlScan)nState;
	//u8 nBtState = (Ctrl_STOP == pLocalParam->eScanState) ? BUTTON_UP: BUTTON_DOWN;
	g_clsNotifyAndResponseFlyJniSdk.sendToApp_RadioScanStatus(nState);
	RadioToApp_ScanCtrlState(nState);

	u16 sound = 0;
	u8 soundLen = 0;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&sound,&soundLen);
	if(sound == 0x04){
		//RadioToApp_SendRadioScanState(nState);
	}
}//Scan����״̬

int isRecordCurFrequency(u8 nChannel)
{
	int totalPages = pLocalParam->stszRadioChannelRecord[nChannel].totalPages;
	int totalRecordNum = totalPages * CHANNEL_RECORD_NUM;
	int i = 0;
	for(; i < totalRecordNum; i++)
	{
		if(pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[i])
		{
			if(pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[i] ==
				pLocalParam->stszRadioChannelRecord[nChannel].wCurFrequency)
			{
				return 1;
			}
		}
	}
	return 0;
}
void halToRadio_SearchState()
{

	short saveIndex = pLocalParam->searchSaveIndex;
	LOGD("  halToRadio_SearchState    saveIndex=%d", saveIndex);
	if(saveIndex >= CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE)
	{
		//pLocalParam->searchSaveIndex = 0x00;
		radioTohal_ScanCtrl(Ctrl_STOP);
		return;
	}
	
	u8 nChannel = pLocalParam->eRadioChannel;
	//����Ѿ������˸�̨���ղ��ٱ���
	if(isRecordCurFrequency(nChannel))
	{
		return;
	}
	//���ǰλ����̨���򱣴浽��һ��λ��
	if(pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[saveIndex])
	{
		pLocalParam->searchSaveIndex++;
		halToRadio_SearchState();	
	}
	short page = saveIndex / CHANNEL_RECORD_NUM;
	setUpdateUI(0x00);
	appToRadio_SaveRecord(saveIndex);
	if(saveIndex % CHANNEL_RECORD_NUM == 0)
	{
		short totalPages = pLocalParam->stszRadioChannelRecord[nChannel].totalPages;
		if((page + 1) > totalPages)
			pLocalParam->stszRadioChannelRecord[nChannel].curPage = totalPages;
		else
			pLocalParam->stszRadioChannelRecord[nChannel].curPage = page + 1;
		RadioToApp_UpdatePageAndRecord();
	}
	else
	{
		if(pLocalParam->stszRadioChannelRecord[nChannel].curPage == (page + 1))
			RadioToApp_DisplayOneRecord(saveIndex);
		else
		{
			pLocalParam->stszRadioChannelRecord[nChannel].curPage = page + 1;
			RadioToApp_UpdatePageAndRecord();
		}
	}
	g_clsNotifyAndResponseFlyJniSdk.sendToSdkRadioScanChanelAndfre(pLocalParam->stszRadioChannelRecord[nChannel].wCurFrequency);
	pLocalParam->searchSaveIndex++;
	setUpdateUI(0x01);
 

}


//--------2012-5-28-----updata----------------//
void halToRadio_PowerState(u8 nState)
{
	if(nState)
	{
		RadioToApp_IsRadioPowerOn(BUTTON_UP);
		pLocalParam->bIsRadioPowerOn = true;
		g_clsNotifyAndResponseFlyJniSdk.sendToSdkRadioPowerStatus(nState);        //radio power status send to SDK
	}
	else
	{
		RadioToApp_IsRadioPowerOn(BUTTON_DOWN);
		pLocalParam->bIsRadioPowerOn = false;
		g_clsNotifyAndResponseFlyJniSdk.sendToSdkRadioPowerStatus(nState);        //radio power status send to SDK
	}
	g_clsNotifyAndResponseFlyJniSdk.sendToApp_RadioSwitch(nState);  
}
//------------------------------------------//

void halToRadio_AFState(u8 nState){}//AF״̬
void halToRadio_TAState(u8 nState){}//TA״̬

void halToRadio_FlickerCtrl(u8 nCtrlFlag)
	{
		pLocalParam->nFlashState = nCtrlFlag;
		RadioToApp_FlashState(nCtrlFlag);
	}//��˸����

void halToRadio_FrequencyChannel(u8 cChannel)
{		
		
		g_clsNotifyAndResponseFlyJniSdk.sendToSdkFreSection(cChannel);     // cChannel = 0x00......FM       cChannel = 0x02......AM    send to SDK
		radioToModule_AUXScreen_RadioChannel(cChannel);
		pLocalParam->eRadioChannel = (E_RadioChannel)cChannel;

		LOGD("*************halToRadio_FrequencyChannel*******pLocalParam->eRadioChannel**********%d",pLocalParam->eRadioChannel);

		if (pLocalParam->bIsHasRadioStationAndInfo)
		{
			RadioToApp_ClearRadioStationNameAndInfo();
		}

		RadioToApp_SetGuangMaxValue(cChannel);//set guang Max Value
		setUpdateUI(0x00);
		if(pLocalParam->eRadioChannel == FM1 || pLocalParam->eRadioChannel == FM2)
		{
			RadioToApp_NumberPagePointIsEnable(0x01);
			RadioToUI_Main_FM_AM_One_button(0x01);
			 RadioToUI_Main_FM_AM_Show_Unit(0x01);
		}
		else if(pLocalParam->eRadioChannel == AM)
		{
			RadioToApp_NumberPagePointIsEnable(0x00);
			RadioToUI_Main_FM_AM_One_button(0x00);
			RadioToUI_Main_FM_AM_Show_Unit(0x00);
		}
		clearInputFreq();
		RadioToApp_BeginAndEndFreq(cChannel);//set   begin frequency and end frequency
		RadioToApp_UpdatePageAndRecord();
		RadioToApp_LightCurChannel(cChannel);//��ʾ��ǰѡ�е�Ƶ��
		//RadioToApp_LightCurChannelFreq(cChannel);//���ǰƵ���Ǽ�¼�е�һ������ѡ����
		//RadioToApp_ChannelRecord(cChannel);//��ʾ��ǰƵ���ļ�¼
		setUpdateUI(0x01);
}//Ƶ��

void halToRadio_FrequencyName(u8* buf,u32 len){
	radioToModule_AUXScreen_RadioStationName(buf, len);

	//pLocalParam->bIsHasRadioStationAndInfo = true;
	RadioToApp_RadioStationName(buf, len);
}//Ƶ�����

void halToRadio_CurTextInfo(u8* buf,u32 len){
	RadioToApp_TextInfo(buf, len);
}//��ǰ�ı���Ϣ

void halToRadio_CurProgaramType(u8 nType){

}//��ǰ�Ľ�Ŀ����

void IsCurFreqInRecord(u16 nChannel, u16 nFrequency){
	u32 nFuncID = 0;
	int i;
	int baseIndex = (pLocalParam->stszRadioChannelRecord[nChannel].curPage - 1) * CHANNEL_RECORD_NUM;
	for (i = 0; i < CHANNEL_RECORD_NUM; i++)
		{
			if (pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[baseIndex + i] && nFrequency == pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[i + baseIndex])
				{
					pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = baseIndex + i;
					nFuncID = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + i;
					pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel] = pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel];
					RadioToApp_CurAndPreChange(pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel], nFuncID);
					pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel] = nFuncID;

					radioToModule_AUXScreen_RadioRecord(baseIndex + i);

					return;
				}
		}
	pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel] = pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel];
	pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel] = 0;
	RadioToApp_CurAndPreChange(pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel], pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel]);
	pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM;

	radioToModule_AUXScreen_RadioRecord(0);

}

void halToRadio_AreaChoose(u8* param, u32 len)
{
	
	u8 areaCode = param[0];
	RadioToApp_ShowCurArea(areaCode);
	radioToModule_system_RadioArea(areaCode);
/*
	pLocalParam->fmBeginFreq = (unsigned short)(((param[1] << 8) & 0xFF00) + (param[2] & 0xFF));
	pLocalParam->fmEndFreq = (unsigned short)(((param[3] << 8) & 0xFF00) + (param[4] & 0xFF));
	unsigned short fmStepFreq = param[5];
	pLocalParam->amBeginFreq = (unsigned short)(((param[6] << 8) & 0xFF00) + (param[7] & 0xFF));
	pLocalParam->amEndFreq= (unsigned short)(((param[8] << 8) & 0xFF00) + (param[9] & 0xFF));
*/
	pLocalParam->fmBeginFreq = (unsigned short)(((param[1] << 8) & 0xFF00) + (param[2] & 0xFF));
	pLocalParam->fmEndFreq = (unsigned short)(((param[3] << 8) & 0xFF00) + (param[4] & 0xFF));
	pLocalParam->fmStep = param[5];

	pLocalParam->amBeginFreq = (unsigned short)(((param[6] << 8) & 0xFF00) + (param[7] & 0xFF));
	pLocalParam->amEndFreq= (unsigned short)(((param[8] << 8) & 0xFF00) + (param[9] & 0xFF));
	pLocalParam->amStep = param[10];

	LOGD("FM<%d  %d>(%d)",pLocalParam->fmBeginFreq,pLocalParam->fmEndFreq,pLocalParam->fmStep);
	LOGD("AM<%d  %d>(%d)",pLocalParam->amBeginFreq,pLocalParam->amEndFreq,pLocalParam->amStep);
	RadioToApp_BeginAndEndFreq(pLocalParam->eRadioChannel);
}

void halTRadio_Switch_TP(u8 nState)
{
	RadioToApp_Switch_TP(nState);
}
void halTRadio_Switch_AF(u8 nState)
{
	RadioToApp_Switch_AF(nState);
}

void halTRadio_Switch_TA(u8 nState)
{
	RadioToApp_Switch_TA(nState);
}

