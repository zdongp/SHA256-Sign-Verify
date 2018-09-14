#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"

#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "appRequestCommand.h"
#include "appResponseCommand.h"
#include "appRequestFunction.h"

#include "otherModuleRequestCommand.h"
#include "moduleParamResponse.h"


//Radio�����˵��İ�ť
void appToRadio_MenuRadio_MouseUp()
{
	//2012.5.9 by lijiewen
	//if (!pLocalParam->bIsRadioInitOK)
	//	return;
     radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
	 
}

//���ذ���
void appToRadio_Back_MouseUp()
{
	if (Ctrl_STOP != pLocalParam->eScanState)
			radioTohal_ScanCtrl(Ctrl_STOP);
	
     radioToModule_NotifySystem_JumpPage(PAGE_MENU);
}
void appToRadio_Eq_MouseUp(void){
     radioToModule_NotifySystem_JumpPage(PAGE_EQ);
}

void appToRadio_Eq_MouseDown(void){
	if (Ctrl_STOP != pLocalParam->eScanState)
		radioTohal_ScanCtrl(Ctrl_STOP);
}

void appToRadio_Audio_MouseUp(void){
     radioToModule_NotifySystem_JumpPage(PAGE_SOUND);
}

void appToRadio_Audio_MouseDown(void){
	if (Ctrl_STOP != pLocalParam->eScanState)
		radioTohal_ScanCtrl(Ctrl_STOP);
}

//---------2012-5-28------updata-----------//
void appToRadio_TurnOFF_MouseUp(void)
{
	if (Ctrl_STOP != pLocalParam->eScanState)
		radioTohal_ScanCtrl(Ctrl_STOP);
	
	if (pLocalParam->bIsRadioPowerOn)
		{
			radioTohal_RadioSwitch_Power(0x00);// turn off
		}
	else
		{
			radioTohal_RadioSwitch_Power(0x01);// turn off
		}
//	   u8 wzCurFreq[CUR_FREQ_SHU_ZU_SIZE  * 2];
//		memset(wzCurFreq, 0, sizeof(wzCurFreq));
//		setSerialData(CONTROLID_RADIO_MAIN_JIEMU_NAME,wzCurFreq,2);
//		setSerialData(CONTROLID_RADIO_MAIN_JIEMU_CONTENT,wzCurFreq,2);
}
//---------------------------------------//

/*
**	0x01: FM1	0x02: FM2	0x03: AM
*/
void appToRadio_RadioChannel_MouseUp(char type)
{
	if (Ctrl_STOP != pLocalParam->eScanState)
			radioTohal_ScanCtrl(Ctrl_STOP);

	if (type == pLocalParam->eRadioChannel)
		return;
	
	radioTohal_ImitateKey(type + 1);
	
}
void appToRadio_Scan_MoudeDown()
{
	if (Ctrl_STOP != pLocalParam->eScanState)
	{
			pLocalParam->isSearch = NO_SEARCH;
			radioTohal_ScanCtrl(Ctrl_STOP);
	}
	else
		pLocalParam->isSearch = SEARCH;
}
void appToRadio_RadioChannel_MouseDown(char type){
	if (Ctrl_STOP != pLocalParam->eScanState)
		radioTohal_ScanCtrl(Ctrl_STOP);
}
/*Scan�������Ӧ�¼�	
*/
void appToRadio_Scan_MouseUp(void)
{
	//����ǰ��������״̬����ֻ��Ӧ����ʱ��ֹͣ�����¼�
	if(pLocalParam->isSearch == NO_SEARCH)
		return;
	//������scan����ֻ��Ӧ�����¼�
	if(pLocalParam->scanCtrlType == UIACTION_MOUSETIMER)
	{
		pLocalParam->scanCtrlType = UIACTION_MOUSEUP;
		return;
	}
	
/*
	//����ǰû��������Ҳ���ǳ����¼�����������׷�Ӵ�̨
	//--------------begin  ����������̨����ʼλ�ã�---------------------
	u8 nChannel = pLocalParam->eRadioChannel;
	short totalPages = pLocalParam->stszRadioChannelRecord[nChannel].totalPages;
	int baseIndex = (totalPages - 1) * CHANNEL_RECORD_NUM;
	int i = 0;
	if(totalPages < FREQUENCY_MAX_PAGE)
	{
		pLocalParam->searchSaveIndex = baseIndex;
	}
	else
	{
		
		
		for(; i < CHANNEL_RECORD_NUM; i++)
		{
			if(pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[baseIndex + i])
				break;
		}
		if(i >= CHANNEL_RECORD_NUM)
		{
			pLocalParam->searchSaveIndex = baseIndex;
		}
		else
		{
			pLocalParam->searchSaveIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM;
		}
		
	}
	
	pLocalParam->searchBeginIndex = pLocalParam->searchSaveIndex;
	//-------------------------end-------------------
*/
	appToRadio_ClearAllFrequencyRecord(pLocalParam->eRadioChannel);
	pLocalParam->searchSaveIndex = 0;//
	pLocalParam->searchBeginIndex = 0;

	rdaioToHal_Scan(Ctrl_SCAN_REPEAT);
}
//Scan�����¼�
void appToRadio_Scan_MouseTimer(void)
{
	if(pLocalParam->isSearch == NO_SEARCH)
	{
		return;
	}

	pLocalParam->scanCtrlType = UIACTION_MOUSETIMER;
	/*
	appToRadio_ClearAllFrequencyRecord(pLocalParam->eRadioChannel);
	pLocalParam->searchSaveIndex = 0;//
	pLocalParam->searchBeginIndex = 0;
	*/
	//--------------modify 2013-04-16 15:33:17---------------
	//�޸Ĵ�̨��ʽΪ�п�λ�ʹ�̨
	u8 nChannel = pLocalParam->eRadioChannel;
	short totalPages = pLocalParam->stszRadioChannelRecord[nChannel].totalPages;
	short totalSaveFreq = totalPages * CHANNEL_RECORD_NUM;
	short i = 0;
	for(; i < totalSaveFreq; i++)
	{
		if(pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[i])
		{
			continue;
		}
		else
		{
			pLocalParam->searchSaveIndex = i;
			pLocalParam->searchBeginIndex = pLocalParam->searchSaveIndex;
			break;
		}
	}
	/*
	//----------------------------------------------------------------------------
	u8 nChannel = pLocalParam->eRadioChannel;
	short totalPages = pLocalParam->stszRadioChannelRecord[nChannel].totalPages;
	int baseIndex = (totalPages - 1) * CHANNEL_RECORD_NUM;
	int i = 0;
	if(totalPages < FREQUENCY_MAX_PAGE)
	{
		pLocalParam->searchSaveIndex = baseIndex;
	}
	else
	{
		
		
		for(; i < CHANNEL_RECORD_NUM; i++)
		{
			if(pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[baseIndex + i])
				break;
		}
		if(i >= CHANNEL_RECORD_NUM)
		{
			pLocalParam->searchSaveIndex = baseIndex;
		}
		else
		{
			pLocalParam->searchSaveIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM;
		}
		
	}
	
	pLocalParam->searchBeginIndex = pLocalParam->searchSaveIndex;
	//-----------------------------------------------------------------------------
	*/
	rdaioToHal_Scan(Ctrl_SCAN_REPEAT);
}

/*
**	0x01: Freq_INC	0x02: Freq_DEC
*/

void appToRadio_FreqCtrl_MouseDown(char type)
{
	if (Ctrl_STOP != pLocalParam->eScanState)
	{
		pLocalParam->searchBeginIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM;
		pLocalParam->searchSaveIndex = FREQUENCY_MAX_PAGE * CHANNEL_RECORD_NUM;
		radioTohal_ScanCtrl(Ctrl_STOP);	
		return;
	}
		
	
	switch(type)
		{
		case 0x00://
			radioTohal_Frequency_Inc(0);
			break;
		case 0x01:
			radioTohal_Frequency_Dec(0);
			break;
		}
}

void appToRadio_FreqCtrl_MouseUp(char type)
{
	switch(type)
		{
		case 0x00:
			radioTohal_Frequency_Inc(1);
			break;
		case 0x01:
			radioTohal_Frequency_Dec(1);
			break;
		}
}
/*
	����һ��Ƶ����¼���¼�
	����ǰ��¼Ϊ�գ��ձ��浱ǰƵ��
	����ǰ��¼��Ϊ�գ��е�ǰ��¼�͵�ǰƵ����ͬ�������ǰ��¼
*/
void appToRadio_Channel_MouseTimer(char cIndex)
{
	u8 nChannel = pLocalParam->eRadioChannel;
	short curPage = pLocalParam->stszRadioChannelRecord[nChannel].curPage;
	u32 index = (u32)cIndex;
	index = (curPage - 1) * CHANNEL_RECORD_NUM + index;
	
	setUpdateUI(0x00);
	RadioToApp_DisplayOneRecord(index);
	appToRadio_SaveRecord(index);
	u8 allNum = (pLocalParam->stszRadioChannelRecord[nChannel].totalPages - 1)*CHANNEL_RECORD_NUM;
	radioToModule_AuxscreenFreRecordList(nChannel,0x00,allNum,pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord);
	setUpdateUI(0x01);	
}


//
void appToRadio_Channel_MouseUp(char cRecordIndex)
{
	pLocalParam->bIsNeedCmpWithRecFreq = false;
	
	u32 nChannel = pLocalParam->eRadioChannel;
	u8 curPage = pLocalParam->stszRadioChannelRecord[nChannel].curPage;
	u32 index = (u32)cRecordIndex;
	index = (curPage - 1) * CHANNEL_RECORD_NUM + index;
	pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel] = pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel];
	if (!pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[index])
	{
		setAnalogData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN +  cRecordIndex, BUTTON_UP);
		return;
	}

	pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel] = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + cRecordIndex;
	RadioToApp_CurAndPreChange(pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel], pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel]);

	pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = index;
	u16 wCurFreq = pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[index];
	
	radioTohal_Frequency(wCurFreq);
	radioToModule_AUXScreen_RadioRecord(index);
}

	

void appToRadio_Channel_MouseDown(char cRecordIndex){
	if(Ctrl_STOP != pLocalParam->eScanState)
	{
		pLocalParam->searchBeginIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;
		pLocalParam->searchSaveIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;
		radioTohal_ScanCtrl(Ctrl_STOP);
	}
	//if(pLocalParam->dwszCurChannelCurFreqRecFuncID[pLocalParam->eRadioChannel] != 0)
	//{
	//	setAnalogData(pLocalParam->dwszCurChannelCurFreqRecFuncID[pLocalParam->eRadioChannel],BUTTON_UP);
	//}
}

void appToRadio_SaveRecord(u32 index)
{

	u16 nChannel = (u16)pLocalParam->eRadioChannel;
	pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[index] = pLocalParam->stszRadioChannelRecord[nChannel].wCurFrequency;//���浱ǰƵ��ΪcIndex
	pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = index;//���浱ǰѡ�еļ�¼��
	pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[index] = (u8)true;
	updateTotalFreqPage();
	//ModuleParamResponse_WriteData();
	
}

u8 appToRadio_IsCanShowOSD(u32 nPageID)
{
	switch(nPageID)
	{
	case PAGE_RADIO_MAIN: 
	case PAGE_MENU:
		return false;
	default:
		return true;
	}
}


void appToRadio_Set_MouseUp()
{
	if (Ctrl_STOP != pLocalParam->eScanState)
		radioTohal_ScanCtrl(Ctrl_STOP);
	radioToModule_NotifySystem_JumpPage(PAGE_RADIO_SET);	
}


void appToRadio_Next_MouseUp()
{
}

void appToRadio_Scan_Inc_MouseUp()
{	
	rdaioToHal_Scan(Ctrl_SCAN_INC);
}

void appToRadio_Scan_Dec_MouseUp()
{
	rdaioToHal_Scan(Ctrl_SCAN_DEC);
}

void appToRadio_Set_Back_MouseUp(void)
{
	radioToModule_NotifySystem_JumpPrePage();
}

void appToRadio_Set_TA_MouseUp(u8 state)
{

	if(state == 0)
	{
		pLocalParam->taState = 0x00;
		radioTohal_RadioSwitch_TA(0x00);
	}
		
	else
	{
		pLocalParam->taState = 0x01;
		radioTohal_RadioSwitch_TA(0x01);
	}
}

void appToRadio_Set_AF_MouseUp(u8 state)
{
	if(state == 0)
	{
		pLocalParam->afState = 0x00;
		radioTohal_RadioSwitch_AF(0x00);
	}
	else
	{
		pLocalParam->afState = 0x00;
		radioTohal_RadioSwitch_AF(0x01);
	}
}

void appToRadio_Main_Frequency_MouseUp(void)
{
	RadioToApp_ShowInputFreq();
	radioToModule_NotifySystem_JumpPage(PAGE_RADIO_NUMBER);
	if (Ctrl_STOP != pLocalParam->eScanState)
		radioTohal_ScanCtrl(Ctrl_STOP);	
}
void appToRadio_Number_Back(void)
{
	radioToModule_NotifySystem_JumpPrePage();
}

void appToRadio_Radio_Numb(u8 key)
{
	if(pLocalParam->eRadioChannel == FM1 || pLocalParam->eRadioChannel == FM2)
	{
		if(pLocalParam->inputFrequency.len >= 6)
		{
			return;
		}
	}
	else if(pLocalParam->eRadioChannel == AM)
	{
		if(pLocalParam->inputFrequency.len >= 4)
		{
			return;
		}
		
	}
	if(pLocalParam->inputFrequency.len < INPUT_FREQUENCY_MAX_LEN)
	{
	
		pLocalParam->inputFrequency.frequencyNumber[pLocalParam->inputFrequency.len] = key;
		pLocalParam->inputFrequency.len++;
	}

}

void appToRadio_Number(unsigned char key)
{
	appToRadio_Radio_Numb(key);
	RadioToApp_ShowInputFreq();
}

void appToRadio_Number_num(int key)
{
	unsigned char chKey = 0;
	if(key == 0 && pLocalParam->inputFrequency.len == 0)//first   not  0
	{
		return ;
	}
	if(key>=0&&key<10)
	{
		chKey = (char)(key+0x30);
		appToRadio_Number(chKey);
	}	
}

void appToRadio_Number_Point(void)
{
	if(pLocalParam->eRadioChannel == AM)//AM      522~1620
		return;
	if(pLocalParam->inputFrequency.len == 0)
		return;
	unsigned char chKey = '.';
	appToRadio_Number(chKey);
	
}
void appToRadio_Number_Del(void)
{
	
	if(pLocalParam->inputFrequency.len <= 0)
	{
		pLocalParam->inputFrequency.len = 0;
	}
	else
	{
		pLocalParam->inputFrequency.len--;
		pLocalParam->inputFrequency.frequencyNumber[pLocalParam->inputFrequency.len] = 0x00;
	}
	
	RadioToApp_ShowInputFreq();
}
void appToRadio_Number_Cancel(void)
{
	clearInputFreq();
	radioToModule_NotifySystem_JumpPrePage();
}

void appToRadio_Analyze_FrequencyMessage()
{
	double number = 0;
	int freq  = 0;
	if(pLocalParam->inputFrequency.len <= 0)
	{
		return;
	}
	else
	{
		number = strtod((const char*)pLocalParam->inputFrequency.frequencyNumber, NULL);
		
	}
	if(pLocalParam->eRadioChannel == FM1 || pLocalParam->eRadioChannel == FM2)
	{
		freq = (int)(number * 100);
		if(freq < pLocalParam->fmBeginFreq)
		{
			freq = pLocalParam->fmBeginFreq;
		}
		else if(freq > pLocalParam->fmEndFreq)
		{
			freq = pLocalParam->fmEndFreq;
		}
		freq = freq - pLocalParam->fmBeginFreq;
	}
	else if(pLocalParam->eRadioChannel == AM)
	{
		freq = (int)number;
		if(freq < pLocalParam->amBeginFreq)
		{
			freq = pLocalParam->amBeginFreq;
		}
		else if(freq > pLocalParam->amEndFreq)
		{
			freq = pLocalParam->amEndFreq;
		}
		freq =  freq - pLocalParam->amBeginFreq;
	}
	
	int count = freq / pLocalParam->curStep;
	int remainder = freq % pLocalParam->curStep;
	if(remainder <= pLocalParam->curStep / 2)
	{
		freq = count * pLocalParam->curStep;
	}
	else
	{
		freq = (count + 1) * pLocalParam->curStep;
	}

	if(pLocalParam->eRadioChannel == FM1 || pLocalParam->eRadioChannel == FM2)
	{	
		freq = freq + pLocalParam->fmBeginFreq;
	}
	else if(pLocalParam->eRadioChannel == AM)
	{
		freq =  freq + pLocalParam->amBeginFreq;
	}
	
	radioTohal_Frequency2(freq);

}

void appToRadio_Number_OK(void)
{
	appToRadio_Analyze_FrequencyMessage();
	clearInputFreq();
	radioToModule_NotifySystem_JumpPrePage();
}
	

void appToRadio_Main_Gauge_MouseUp(unsigned char *param, unsigned char len)
{
	int pos = 0;

	pos += (int)((param[0] << 24) & 0xFF000000);
	pos += (int)((param[1] << 16) & 0xFF0000);
	pos += (int)((param[2] << 8) & 0xFF00);
	pos += (int)(param[3] & 0xFF);
	
	u16 frequency = 0;
	if(pLocalParam->eRadioChannel == FM1 || pLocalParam->eRadioChannel == FM2)
	{
		frequency = pLocalParam->fmBeginFreq;
	}
	else if(pLocalParam->eRadioChannel == AM)
	{
		frequency = pLocalParam->amBeginFreq;
	}
	pos = pos * pLocalParam->curStep;
	frequency = frequency + pos;
	radioTohal_Frequency2(frequency);
}

void appToRadio_MAIN_PrePage(void)
{
	if (Ctrl_STOP != pLocalParam->eScanState)
	{
		radioTohal_ScanCtrl(Ctrl_STOP);
		return;
	}
		
	changeMinFreqPage();
	setUpdateUI(0x00);
	RadioToApp_UpdatePageAndRecord();
	setUpdateUI(0x01);
}

void appToRadio_MAIN_NextPage(void)
{
	if (Ctrl_STOP != pLocalParam->eScanState)
	{
		radioTohal_ScanCtrl(Ctrl_STOP);
		return;
	}
	changeMaxFreqPage();
	setUpdateUI(0x00);
	RadioToApp_UpdatePageAndRecord();
	setUpdateUI(0x01);	
}

void appToRadio_ClearAllFrequencyRecord(u8 nChannel)
{
	short totalPages = pLocalParam->stszRadioChannelRecord[nChannel].totalPages;
	int num = totalPages * CHANNEL_RECORD_NUM;
	for(int j = 0; j < num; j++)
	{
		pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[j] = (u8)false;
		pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[j] = 0x00;
	}
	pLocalParam->stszRadioChannelRecord[nChannel].curPage = 1;
	pLocalParam->stszRadioChannelRecord[nChannel].totalPages = 1;
	pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel] = 0;
	pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;

	if(nChannel == pLocalParam->eRadioChannel)
	{
		setUpdateUI(0x00);
		RadioToApp_UpdatePage(nChannel);
		RadioToApp_ChannelRecord(nChannel);//��ʾ��¼��Ƶ��
		for(int k = 0; k < CHANNEL_RECORD_NUM; k++)
		{
			setDigitalData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + k, BUTTON_UP);
			//setAnalogData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + k, BUTTON_UP);
		}
		setUpdateUI(0x01);
	}
}

void appToRadio_Main_Delete(void )
{
	u8 nChannel = pLocalParam->eRadioChannel;
	int index = pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex;
	appToRadio_ClearRecord(index);
}
void appToRadio_Main_SetSensitivity(u32 ctrlID )
{
	u8 state=0;
	switch(ctrlID)
	{
	case CONTROLID_RADIO_MAIN_SET_GAO:
		state=0x01;
		break;
	case CONTROLID_RADIO_MAIN_SET_ZHONG:
		state=0x00;
		break;
	case CONTROLID_RADIO_MAIN_SET_DI:
		state=0x02;
		break;
	default: 
		break;
	}
	radioTohal_SetSensitivity(state);
}

void appToRadio_Main_SetAF(u32 ctrlID )
{
	u8 state=0;
	switch(ctrlID)
	{
	case CONTROLID_RADIO_SET_AF_ON:
		state=0x01;
		break;
	case CONTROLID_RADIO_SET_AF_OFF:
		state=0x00;
		break;
	default:
		break;
	}
	radioTohal_RadioSwitch_AF(state);
}

void appToRadio_Main_SetTA(u32 ctrlID )
{
	u8 state=0;
	switch(ctrlID)
	{
	case CONTROLID_RADIO_SET_TA_ON:
		state=0x01;
		break;
	case CONTROLID_RADIO_SET_TA_OFF:
		state=0x00;
		break;
	default:
		break;
	}
	radioTohal_RadioSwitch_TA(state);
}


//���ܺ��� ���һ��Ƶ�ʼ�¼
void appToRadio_ClearRecord( u32 index)
{
	LOGD("index=%d",index);
	if(index == CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE)
		return ;
	u8 nChannel = pLocalParam->eRadioChannel;
	pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[index] = (u8)false;
	pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[index] = 0x00;
	pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;
	updateTotalFreqPage();
	ModuleParamResponse_WriteData();
	char *szFreqRecord = " ";
	index = index % CHANNEL_RECORD_NUM;
	RadioToApp_SetSerialData_Ansi2Unicode(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + index, (u8 *)szFreqRecord, strlen((char*)szFreqRecord));		
	setAnalogData(CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + index,BUTTON_UP);
}

void appToRadio_Radio_FM_AM_Switch()
{
       if (Ctrl_STOP != pLocalParam->eScanState)
                       radioTohal_ScanCtrl(Ctrl_STOP);
       E_RadioChannel em = pLocalParam->eRadioChannel;
       if(em == FM2 || em == FM1)
               em = AM;
       else
               em = FM1;
       radioTohal_ImitateKey(((u8)em) + 1);
}
void appToRadio_FreqCtrl_SearchType(char type)
{
	switch(type)
	{
		case 0x00:
			appToRadio_Scan_Inc_MouseUp();
			break;
		case 0x01:
			appToRadio_Scan_Dec_MouseUp();
			break;
	}
}

void RadioToUI_Main_SetFineTuneButton(int p,char param)
{
	if(param == 0x10)
		setDigitalData(p, BUTTON_UP);
	else if(param == 0x00)
		setDigitalData(p, BUTTON_DOWN);
}

void appToRadio_FreqCtrl_SetFineTune_MouseUp(char type)
{
	if (Ctrl_STOP != pLocalParam->eScanState)
	{
		radioTohal_ScanCtrl(Ctrl_STOP);
		return;
	}
	switch(type)
	{
		case 0x00:
			{
				radioTohal_ImitateKey(0x07);
			}
			break;
		case 0x01:
			{
				radioTohal_ImitateKey(0x08);
			}
			break;
		default:break;
	}
}
void sdkToModuleSetRepeatScan()
{
	appToRadio_ClearAllFrequencyRecord(pLocalParam->eRadioChannel);
	pLocalParam->searchSaveIndex = 0;//
	pLocalParam->searchBeginIndex = 0;
	rdaioToHal_Scan(Ctrl_SCAN_REPEAT);
}