#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringID.h"
#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"

#include "appResponseCommand.h"
#include "otherModuleRequestCommand.h"

#include "moduleParamResponse.h"
extern "C"{
#include "unicodestring.h"
};

void RadioToApp_IsCanVisitRadio(u8 bIsCanVisit)
{
	if (bIsCanVisit)
		{
			setAnalogData(CONTROLID_MENU_RADIO, BUTTON_UP);
			setControllable(CONTROLID_MENU_RADIO, CTRL_ENABLE);
		}
	else
		{
			setAnalogData(CONTROLID_MENU_RADIO, BUTTON_DISABLE);
			setControllable(CONTROLID_MENU_RADIO, CTRL_DISABLE);
		}
}

void RadioToApp_ScanCtrlState(u8 nState)
{
	setUpdateUI(0x00);

	if(nState == Ctrl_STOP)
	{
		ModuleParamResponse_WriteData();
		
		setDigitalData(CONTROLID_RADIO_MAIN_SCAN, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_ON_ONE_CHANNEL, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_NEXT_CHANNEL, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_INC_FINE_TUNE_OR_SEARCH, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_DEC_FINE_TUNE_OR_SEARCH, BUTTON_UP);
		
		if(pLocalParam->searchBeginIndex < FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM)
		{
			if(pLocalParam->searchSaveIndex == pLocalParam->searchBeginIndex)
			{
				pLocalParam->searchSaveIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM;
				pLocalParam->searchBeginIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM; 
				setUpdateUI(0x01);
				return;
			}
				
			short curPage = pLocalParam->searchBeginIndex/CHANNEL_RECORD_NUM;
			u8 nChannel = pLocalParam->eRadioChannel;
			pLocalParam->stszRadioChannelRecord[nChannel].curPage = curPage + 1;
			RadioToApp_ChannelRecord(nChannel);//��ʾ��¼��Ƶ��
			radioTohal_Frequency(pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[curPage * CHANNEL_RECORD_NUM]);
			RadioToApp_UpdatePage(nChannel);
		}
		pLocalParam->searchSaveIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM;
		pLocalParam->searchBeginIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM; 
		pLocalParam->scanCtrlType = UIACTION_MOUSEUP;
		u8 allNum = (pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].totalPages - 1)*CHANNEL_RECORD_NUM;
		radioToModule_AuxscreenFreRecordList(pLocalParam->eRadioChannel,0x00,allNum,pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].wRadioFreqRecord);
		
	}
	else if(nState == Ctrl_SCAN_REPEAT)
	{
			if(pLocalParam->bUiButtonDownNoShow)
			{
			}
		else
			{
		setDigitalData(CONTROLID_RADIO_MAIN_SCAN, BUTTON_DOWN);
		setDigitalData(CONTROLID_RADIO_MAIN_ON_ONE_CHANNEL, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_NEXT_CHANNEL, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_INC_FINE_TUNE_OR_SEARCH, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_DEC_FINE_TUNE_OR_SEARCH, BUTTON_UP);
		}
	}
	else if(nState == Ctrl_SCAN_INC)
	{
		if(pLocalParam->bUiButtonDownNoShow)
		{
		}
		else
		{
			setDigitalData(CONTROLID_RADIO_MAIN_SCAN, BUTTON_UP);
			setDigitalData(CONTROLID_RADIO_MAIN_NEXT_CHANNEL, BUTTON_DOWN);
			setDigitalData(CONTROLID_RADIO_MAIN_ON_ONE_CHANNEL, BUTTON_UP);
			setDigitalData(CONTROLID_RADIO_MAIN_INC_FINE_TUNE_OR_SEARCH, BUTTON_DOWN);
			setDigitalData(CONTROLID_RADIO_MAIN_DEC_FINE_TUNE_OR_SEARCH, BUTTON_UP);
		}
		
	}
	else if(nState == Ctrl_SCAN_DEC)
	{		
	if(pLocalParam->bUiButtonDownNoShow)
			{
			}
		else
			{
		setDigitalData(CONTROLID_RADIO_MAIN_SCAN, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_NEXT_CHANNEL, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_ON_ONE_CHANNEL, BUTTON_DOWN);
		setDigitalData(CONTROLID_RADIO_MAIN_INC_FINE_TUNE_OR_SEARCH, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_DEC_FINE_TUNE_OR_SEARCH, BUTTON_DOWN);

		}
	}
		
	
	setUpdateUI(0x01);
}

void RadioToApp_IsRadioPowerOn(u8 nState)
{
	setUpdateUI(0x00);
	setAnalogData(CONTROLID_RADIO_SET_OPEN_RADIO, nState);
	setAnalogData(CONTROLID_RADIO_MAIN_TURNOFF, nState);
	setAnalogData(CONTROLID_RADIO_MAIN_OTHER_TURNOFF, nState);
	if(nState == 0){
		setStringText(CONTROLID_RADIO_MAIN_OTHER_TURNOFF,STRINGID_RADIO_OPEN);
	}
	else{
		setStringText(CONTROLID_RADIO_MAIN_OTHER_TURNOFF,STRINGID_RADIO_CLOSE);
	}
	setUpdateUI(0x01);
}


void RadioToApp_FlashState(u8 nState)
{
	u8 wzCurFreq[CUR_FREQ_SHU_ZU_SIZE  * 2];
	u8 wzCurFreq1[CUR_FREQ_SHU_ZU_SIZE  * 2];
	memset(wzCurFreq, 0, sizeof(wzCurFreq));
	memset(wzCurFreq1, 0, sizeof(wzCurFreq1));
	static u16 uLastFrequency=0;
	if(uLastFrequency!=pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].wCurFrequency)
	{
		//setSerialData(CONTROLID_RADIO_MAIN_JIEMU_NAME,wzCurFreq,2);
		setSerialData(CONTROLID_RADIO_MAIN_JIEMU_CONTENT,wzCurFreq,2);
		uLastFrequency=pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].wCurFrequency;
	}
	pLocalParam->szCurFreq[CUR_FREQ_SHU_ZU_SIZE - 1] = 0;
	int nLen = 0;
	int nLen1 = 0;
	if (1 == nState)
	{
		  ansi_str_to_unicode16(pLocalParam->szCurFreq, (unsigned short *)wzCurFreq);
		  nLen = 2 * strlen((char *)(pLocalParam->szCurFreq));

		u8 temBuf[CUR_FREQ_SHU_ZU_SIZE  * 2] = {0};
		int temLen = 0;
		int tLen = strlen((char *)pLocalParam->szCurFreq);
		if(tLen > 4)
		{
			memcpy(temBuf,pLocalParam->szCurFreq,tLen-4);
		}
		ansi_str_to_unicode16(temBuf, (unsigned short *)wzCurFreq1);
		nLen1 = 2 * strlen((char *)(temBuf));
		  
	}

	setSerialData(CONTROLID_RAFIO_MAIN_FREQUENCY, wzCurFreq, nLen);
	setSerialData(CONTROLID_RAFIO_MAIN_FREQUENCY_NEW, wzCurFreq1, nLen1);
	LOGD("RadioToApp_FlashState -------------");
}

/*void RadioToApp_BeginAndEndFreq(u16 beginFreq, u16 endFreq)
{
	
}*/
void RadioToApp_LightCurChannel(u8 cChannel)
{
	static int displaychannel = -1;
	int array[3] ={ CONTROLID_RADIO_MAIN_FM1, CONTROLID_RADIO_MAIN_FM2, CONTROLID_RADIO_MAIN_AM};

	if(displaychannel == cChannel){
		return;
	}

	if(displaychannel != -1){
		setDigitalData(array[displaychannel], BUTTON_UP);
	}

	displaychannel = cChannel;

	if(displaychannel != -1){
		setDigitalData(array[displaychannel], BUTTON_DOWN);
	}

	
}

void RadioToApp_ChannelRecord(u8 cChannel)
{
	if (cChannel >= CHANNEL_NUM)
		return ;

	int i = 0;
	int curPage = pLocalParam->stszRadioChannelRecord[cChannel].curPage;
	int baseNum = (curPage - 1) * CHANNEL_RECORD_NUM;
	for(i = 0; i < CHANNEL_RECORD_NUM; i++)
	{
		u8 szFreqRecord[100];
		memset(szFreqRecord, 0, sizeof(szFreqRecord));
		if(pLocalParam->stszRadioChannelRecord[cChannel].bRadioFreqRecordState[i + baseNum])
		{
			u16 wFreq = pLocalParam->stszRadioChannelRecord[cChannel].wRadioFreqRecord[i + baseNum];
			wFreq = (wFreq >> 8) + ((wFreq & 0xFF) << 8);
			if(FM1 == cChannel || FM2 == cChannel)
			{
					sprintf((char*)szFreqRecord, " %4.1f",  wFreq / 100.0);
			}
			else if(AM == cChannel)
			{
					sprintf((char*)szFreqRecord, " %d", wFreq);
			}
				
		}
		RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + i,szFreqRecord,strlen((char*)szFreqRecord));
		//u8 wzFreqRecord[200];
		//memset(wzFreqRecord, 0, sizeof(wzFreqRecord));
		//ansi_str_to_unicode16(szFreqRecord, (unsigned short *)wzFreqRecord);
	   // int nLen = 2 * strlen((char *)(szFreqRecord));
		//setSerialData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + i, wzFreqRecord, nLen);
	}
}

void RadioToApp_LightCurChannelFreq(u8 cChannel, short curPage)
{
	static int displaychannel = -1;
	//TEST
	//char pos[3] = { -1, -1, -1};
	if(cChannel == displaychannel){
		return;
	}

	u8 cIndex = pLocalParam->stszRadioChannelRecord[cChannel].cCurRecordIndex;
	int i;
	int baseIndex = (curPage - 1) * CHANNEL_RECORD_NUM;
	u16 curFrequency = pLocalParam->stszRadioChannelRecord[cChannel].wCurFrequency;
	
	for(i = 0; i <  CHANNEL_RECORD_NUM; i++){

		if(pLocalParam->stszRadioChannelRecord[cChannel].bRadioFreqRecordState[baseIndex + i])
		{
			if(pLocalParam->stszRadioChannelRecord[cChannel].wRadioFreqRecord[baseIndex + i] == curFrequency)
			{
				pLocalParam->dwszCurChannelCurFreqRecFuncID[cChannel] = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+i;//���浱ǰ��¼��
				setDigitalData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+i, BUTTON_DOWN);
				pLocalParam->stszRadioChannelRecord[cChannel].cCurRecordIndex=baseIndex+i;
				break;
			}
			else
			{
				setDigitalData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+i, BUTTON_UP);
			}
		}
		else
		{
			if(cIndex == (baseIndex + i))
			{
				pLocalParam->dwszCurChannelCurFreqRecFuncID[cChannel] = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+i;//���浱ǰ��¼��
				setDigitalData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+i, BUTTON_DOWN);
				break;
			}
			else{
				setDigitalData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+i, BUTTON_UP);
			}
		}
	}
	i++;
	if(i < CHANNEL_RECORD_NUM)
	{
		for(; i < CHANNEL_RECORD_NUM; i++)
		{
			setDigitalData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN+i, BUTTON_UP);
		}
	}
	
#if 0
	u32 i;
	for (i = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN; i < CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + CHANNEL_RECORD_NUM; i++){
		//if(i ==  CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + cIndex  && pLocalParam->dwszCurChannelCurFreqRecFuncID[cChannel] !=0)
		//{
		//	setDigitalData(i, BUTTON_DOWN);
		//}
		//else
		//{
			setDigitalData(i, BUTTON_UP);
		//}
		//setAnalogData(i, BUTTON_UP);
	}
	//
	//u8 cIndex = pLocalParam->stszRadioChannelRecord[cChannel].cCurRecordIndex;
	//if (cIndex >= CHANNEL_RECORD_NUM)
		//return;

	//pLocalParam->dwszCurChannelCurFreqRecFuncID[cChannel] = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + cIndex;

	//setAnalogData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + cIndex, BUTTON_DOWN);
#endif
}

void RadioToApp_ClearRadioStationNameAndInfo(void)
{
	pLocalParam->bIsHasRadioStationAndInfo = false;

	setSerialData(CONTROLID_RADIO_MAIN_STATION_NAME, NULL, 0);
	setSerialData(CONTROLID_RADIO_MAIN_TIPS, NULL, 0);
}

void RadioToApp_TextInfo(u8 *pBuf, int nLen)//�ı���Ϣ
{
	//RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_MAIN_TIPS, pBuf, nLen);
	//RadioToApp_SetSerialData_Unicode(CONTROLID_RADIO_MAIN_TIPS, pBuf, nLen);
	//20140922
	LOGD("RadioToApp_TextInfo");
	RadioToApp_SetSerialData_Unicode(CONTROLID_RADIO_MAIN_JIEMU_CONTENT, pBuf, nLen);
	LOGD("unicode Radio station content= %s",pBuf);
}

void RadioToApp_RadioStationName(u8 *pBuf, int nLen)//Ƶ�����
{
	//RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_MAIN_STATION_NAME, pBuf, nLen);
	//RadioToApp_SetSerialData_Unicode(CONTROLID_RADIO_MAIN_STATION_NAME, pBuf, nLen);
	//20140922
	LOGD("ansi Radio station current frequency = %s",pLocalParam->szCurFreq);
	memcpy(pLocalParam->szStationName,pBuf,nLen);
	//RadioToApp_SetSerialData_Unicode(CONTROLID_RADIO_MAIN_JIEMU_NAME , pBuf, nLen);
	if( *pBuf !=NULL){
		pLocalParam->bIsHasRadioStationAndInfo=true;
	    	RadioToApp_SetSerialData_Unicode(CONTROLID_RAFIO_MAIN_FREQUENCY , pBuf, nLen);
		RadioToApp_SetSerialData_Unicode(CONTROLID_RAFIO_MAIN_FREQUENCY_NEW , pBuf, nLen);
	}
	else{
		pLocalParam->bIsHasRadioStationAndInfo=false;
		RadioToApp_CurChannelFreqText(pLocalParam->szCurFreq, strlen((char*)pLocalParam->szCurFreq));
	}
	LOGD("unicode Radio station name= %s,nLen=%d,pBuf[0]=%d",pBuf,nLen,pBuf[0]);
}

void RadioToApp_CurChannelFreqText(u8 *pBuf, int nLen)
{
	static u16 uLastFrequency=0;

	if(uLastFrequency!=pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].wCurFrequency)
	{
		u8 wzCurFreq[CUR_FREQ_SHU_ZU_SIZE  * 2];
		memset(wzCurFreq, 0, sizeof(wzCurFreq));
		//setSerialData(CONTROLID_RADIO_MAIN_JIEMU_NAME,wzCurFreq,2);
		setSerialData(CONTROLID_RADIO_MAIN_JIEMU_CONTENT,wzCurFreq,2);
		uLastFrequency=pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].wCurFrequency;

       pLocalParam->bIsHasRadioStationAndInfo=false;
	}
	if(pLocalParam->bIsHasRadioStationAndInfo);
	else{
		RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RAFIO_MAIN_FREQUENCY, pBuf, nLen);
		u8 temBuf[CUR_FREQ_SHU_ZU_SIZE  * 2] = {0};
		int temLen = 0;
		if(nLen > 4)
		{
			if(FM1 == pLocalParam->eRadioChannel || FM2 == pLocalParam->eRadioChannel)
				memcpy(temBuf,pBuf,nLen-5);
			else memcpy(temBuf,pBuf,nLen-4);
			temLen = strlen((char *)temBuf);
		}
		RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RAFIO_MAIN_FREQUENCY_NEW, temBuf, temLen);
	}
	LOGD("RadioToApp_CurChannelFreqText--bIsHasRadioStationAndInfo=%d--- = %s",pLocalParam->bIsHasRadioStationAndInfo,pBuf);
}

void RadioToApp_CurAndPreChange(u32 dwPreFuncID, u32 dwCurFuncID)
{
	if (dwPreFuncID == dwCurFuncID)
	{
		if (0 != dwCurFuncID){
			setDigitalData(dwCurFuncID, BUTTON_DOWN);
			//setAnalogData(dwCurFuncID, BUTTON_DOWN);
		}
		return;
	}
	if (0 != dwCurFuncID){
		setDigitalData(dwCurFuncID, BUTTON_DOWN);
		//setAnalogData(dwCurFuncID, BUTTON_DOWN);
	}

	if (0 != dwPreFuncID){

		setDigitalData(dwPreFuncID, BUTTON_UP);
		//setAnalogData(dwPreFuncID, BUTTON_UP);
	}

}

void RadioToApp_SetSerialData_Ansi2Unicode(int controlId, u8 *pBuf, int nLen)
{
	int nSendLen = nLen * 2;
	u8 *pwBuf = (u8*)malloc(nSendLen + 2);
	memset(pwBuf, 0, nSendLen);
	ansi_str_to_unicode16(pBuf, (unsigned short *)pwBuf);
	setSerialData(controlId, pwBuf, nSendLen);
	free(pwBuf);
}

//----------------------------------2012-7-5--------------------------------------//
void RadioToApp_SetSerialData_Unicode(int controlId, u8 *pBuf, int nLen){
	setSerialData(controlId, pBuf, nLen);
}

void RadioToApp_ShowCurArea(u8 areaCode)
{
	
}

void RadioToApp_Switch_TA(u8 nState)
{
	if(pLocalParam->radioTAstate){
		setDigitalData(CONTROLID_RADIO_MAIN_TA, nState);
	}
}

void RadioToApp_Switch_AF(u8 nState)
{
	if(pLocalParam->radioAFstate == 0x01){
		setDigitalData(CONTROLID_RADIO_MAIN_AF_ICO, nState);
		setDigitalData(CONTROLID_RADIO_SET_AF_ICO,nState);
	}
}
void RadioToApp_Switch_TP(u8 nState)
{
	setDigitalData(CONTROLID_RADIO_MAIN_TP_ICO, nState);
	setDigitalData(CONTROLID_RADIO_SET_TP_ICO,nState);
}
void RadioToApp_Set_Switch_TA(u8 nState)
{
	setDigitalData(CONTROLID_RADIO_SET_TF_SET, nState);
	LOGD("Radio set TA ------background index=%d",nState);
	pLocalParam->radioTAstate=nState;
	if(nState)
	{
			setDigitalData(CONTROLID_RADIO_SET_TA_ON, BUTTON_DOWN);
			setDigitalData(CONTROLID_RADIO_SET_TA_OFF, BUTTON_UP);
			//if(){
				setDigitalData(CONTROLID_RADIO_MAIN_TA, BUTTON_DOWN);
			//}
	}
	else
	{
			setDigitalData(CONTROLID_RADIO_SET_TA_ON, BUTTON_UP);
			setDigitalData(CONTROLID_RADIO_SET_TA_OFF, BUTTON_DOWN);
			setDigitalData(CONTROLID_RADIO_MAIN_TA, BUTTON_UP);
	}
}
void RadioToApp_Set_Switch_AF(u8 nState)
{
	setDigitalData(CONTROLID_RADIO_SET_AF_SET, nState);
	LOGD("Radio set AF -------background index=%d",nState);
	pLocalParam->radioAFstate=nState;
	if(nState)
	{
		setDigitalData(CONTROLID_RADIO_SET_AF_ON, BUTTON_DOWN);
		setDigitalData(CONTROLID_RADIO_SET_AF_OFF, BUTTON_UP);
		//if(){
			setDigitalData(CONTROLID_RADIO_MAIN_AF, BUTTON_DOWN);
		//}
	}
	else
	{
		setDigitalData(CONTROLID_RADIO_SET_AF_ON, BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_SET_AF_OFF,BUTTON_DOWN);
		setDigitalData(CONTROLID_RADIO_MAIN_AF, BUTTON_UP);
	}
}

void RadioToApp_BeginAndEndFreq(u8 cChannel)
{
	
	u16 beginFrequency = 0;
	u16 endFrequency = 0;
	u8 szBeginFreq[CUR_FREQ_SHU_ZU_SIZE];
	u8 szEndFreq[CUR_FREQ_SHU_ZU_SIZE];
	if (FM1 == cChannel || FM2 == cChannel)
	{
		beginFrequency = pLocalParam->fmBeginFreq;
		endFrequency = pLocalParam->fmEndFreq;
		sprintf((char*)szBeginFreq, "%4.1f",  beginFrequency / 100.0);
		sprintf((char*)szEndFreq, "%4.1f",  endFrequency / 100.0);
		setControllable(CONTROLID_RADIO_NUMBER_POINT, CTRL_ENABLE);
	}
	else if(AM == cChannel)
	{
		beginFrequency = pLocalParam->amBeginFreq;
		endFrequency = pLocalParam->amEndFreq;
		sprintf((char*)szBeginFreq, "%d",  beginFrequency );
		sprintf((char*)szEndFreq, "%d",  endFrequency );
		setControllable(CONTROLID_RADIO_NUMBER_POINT, CTRL_DISABLE);
		
	}
	RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_MAIN_LEFT_TXT,(u8 *)szBeginFreq,strlen((char*)szBeginFreq));
	RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_MAIN_RIGHT_TXT,(u8 *)szEndFreq,strlen((char*)szEndFreq));
	
}

void RadioToApp_ShowInputFreq()
{

	if(pLocalParam->inputFrequency.len == 0)
	{	
		setStringText(CONTROLID_RADIO_NUMBER_TXT, STRINGID_RADIO_INPUT_NUMBER);
	}
	else
	{
		
		char unit = 0;
		if(pLocalParam->eRadioChannel == FM1 || pLocalParam->eRadioChannel == FM2)
		{
			unit = 'M';
		}
		else
		{
			unit = 'k';	
		}
		const char * d = "MHz";
		char *freqNumber = (char*)malloc(pLocalParam->inputFrequency.len+4);
		if(freqNumber == NULL)
				return;
		memcpy(freqNumber, pLocalParam->inputFrequency.frequencyNumber, pLocalParam->inputFrequency.len);
		freqNumber[pLocalParam->inputFrequency.len] = ' ';
		freqNumber[pLocalParam->inputFrequency.len + 1] = unit;
		freqNumber[pLocalParam->inputFrequency.len + 2] = 'H';
		freqNumber[pLocalParam->inputFrequency.len + 3] = 'z';
		freqNumber[pLocalParam->inputFrequency.len + 4] = '\0';
		//freqNumber[pLocalParam->inputFrequency.len] = '\0';
		RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_NUMBER_TXT, (u8 *)freqNumber, strlen((char*)freqNumber));
	
		free(freqNumber);
	}

}
void RadioToApp_UpdatePageAndRecord(void)
{
	u8 cChannel = pLocalParam->eRadioChannel;
	u8 curPage = pLocalParam->stszRadioChannelRecord[cChannel].curPage;
	RadioToApp_UpdatePage(cChannel);
	RadioToApp_ChannelRecord(cChannel);//��ʾ��¼��Ƶ��
	RadioToApp_LightCurChannelFreq(cChannel, curPage);//����ѡ�е�Ƶ��
	
	
}
void RadioToApp_UpdatePage(u8 cChannel)
{
	u8 szPage[50];
	u8 totalPage = pLocalParam->stszRadioChannelRecord[cChannel].totalPages;
	u8 curPage = pLocalParam->stszRadioChannelRecord[cChannel].curPage;
	sprintf((char*)szPage, "%d/%d",  curPage, totalPage);
	RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_MAIN_PAGES,(u8 *)szPage,strlen((char*)szPage));
}
void RadioToApp_SetGuangMaxValue(u8 cChannel)
{
	u16 guangMax = 0;
	u16 beginFreq = 0;
	u16 endFreq = 0;
	if(FM1 == cChannel || FM2 == cChannel)
	{
		pLocalParam->curStep = pLocalParam->fmStep;
		beginFreq = pLocalParam->fmBeginFreq;
		endFreq = pLocalParam->fmEndFreq;
	}
	else if(AM == cChannel)
	{
		pLocalParam->curStep = pLocalParam->amStep;
		beginFreq = pLocalParam->amBeginFreq;
		endFreq = pLocalParam->amEndFreq ;
	}
	//beginFreq = (beginFreq >> 8) + ((beginFreq & 0xFF) << 8);
	//endFreq = (endFreq >> 8) + ((endFreq & 0xFF) << 8);
	guangMax =	 endFreq - beginFreq;
	LOGD("pLocalParam->curStep:%d",pLocalParam->curStep);
	if(pLocalParam->curStep != 0)
	setProgressRange(CONTROLID_RADIO_MAIN_CHANNEL_GUANG, guangMax / pLocalParam->curStep);
}


void RadioToApp_DisplayOneRecord(u32 index)
{
	u8 nChannel = pLocalParam->eRadioChannel;
	u8 szFreqRecord[100];
	memset((char*)szFreqRecord, 0, sizeof(szFreqRecord));
	u16 wFreq = pLocalParam->stszRadioChannelRecord[nChannel].wCurFrequency;
	wFreq = (wFreq >> 8) + ((wFreq & 0xFF) << 8);
	if (FM1 == nChannel || FM2 == nChannel)
		sprintf((char*)szFreqRecord, " %4.1f", wFreq / 100.0);
	else if (AM == nChannel)
		sprintf((char*)szFreqRecord, " %d", wFreq);

	index = index % CHANNEL_RECORD_NUM;
	RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + index, szFreqRecord, strlen((char*)szFreqRecord));
	pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel] = pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel];
	pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel] = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + index;
	RadioToApp_CurAndPreChange(pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel], pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel]);
}



void RadioToApp_NumberPagePointIsEnable(u8 isEnable)
{
	if(isEnable)
	{
		setAnalogData(CONTROLID_RADIO_NUMBER_POINT, 0);
		setControllable(CONTROLID_RADIO_NUMBER_POINT, 1);
	}
	else
	{
		setAnalogData(CONTROLID_RADIO_NUMBER_POINT, 2);
		setControllable(CONTROLID_RADIO_NUMBER_POINT, 0);
	}
}

void RadioToApp_Get_sensitivityState(u8 state)
{
	LOGD(" RadioToApp_Get_sensitivityState:state=%d",state);
	pLocalParam->sensitivitystate=state;
	//setUpdateUI(0x00);
	switch(state)
	{
	case 0x00:
		setDigitalData(CONTROLID_RADIO_MAIN_SET_GAO,BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_SET_ZHONG,BUTTON_DOWN);
		setDigitalData(CONTROLID_RADIO_MAIN_SET_DI,BUTTON_UP);
		break;
	case 0x01:
		setDigitalData(CONTROLID_RADIO_MAIN_SET_GAO,BUTTON_DOWN);
		setDigitalData(CONTROLID_RADIO_MAIN_SET_ZHONG,BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_SET_DI,BUTTON_UP);
		break;
	case 0x02:
		setDigitalData(CONTROLID_RADIO_MAIN_SET_GAO,BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_SET_ZHONG,BUTTON_UP);
		setDigitalData(CONTROLID_RADIO_MAIN_SET_DI,BUTTON_DOWN);
		break;
	default:break;
	}
	
	//setUpdateUI(0x01);
}


void RadioToApp_SendRadioScanState(u8 state)
{
	u8 buf[3]={0x3f,0x00,0x00};
	buf[1]=0x00;
	buf[2]=state;
	sendCommandToApp(buf,3);
}

void RadioToUI_Main_FM_AM_One_button(u8 p)
{
       setAnalogData(CONTROLID_RADIO_MAIN_FM_AM_ICON, (int)p);
       setDigitalData(CONTROLID_RADIO_MAIN_SWITCH_CHANNEL_BUTTON, (int)p);
}


void RadioToUI_Main_FM_AM_Show_Unit(u8 p)
{
	setAnalogData(CONTROLID_RADIO_MAIN_FM_AM_UNIT, (int)p);
}
