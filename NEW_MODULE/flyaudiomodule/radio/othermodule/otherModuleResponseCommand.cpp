#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "paramID.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleRequestCommand.h"
#include "moduleParamResponse.h"
#include "moduleParamRequest.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "controlID.h"

#include "param.h"
#include "commonFunc.h"
void otherModuleInit(void){

}

void otherModuleDeInit(void){

}

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){

	switch(sendModuleId){
		case MODULE_ID_SYSTEM:
			OtherModuleToRadio_AnalyseSystem(param, len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			OtherModuleToRadio_AnalyseAudioAndVideo(param, len);
			break;
		case MODULE_ID_KEY:
			OtherModuleToRadio_AnalyseKey(param, len);
			break;
		case MODULE_ID_BLCD:
			break;
		case MODULE_ID_EXTERNALCTRL:
			OtherModuleToRadio_AnalyseExternalCtrl(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToRadio_FromAutomate(param,len);
		    break;
		case MODULE_ID_FLYJNISDK:
			g_clsNotifyAndResponseFlyJniSdk.getFlyJniSdkMessage(param,  len);
			break;
		case MODULE_ID_CENTER:
			moduleToRadio_FromCenter_Message(param, len);
			break;
		case MODULE_ID_AUXSCREEN:
			moduleToRadio_FromAuxcreen_Message(param, len);
			break;
		default:
			break;
	}
}

void OtherModuleToRadio_AnalyseSystem(unsigned char *pBuf, int nLen)
{
	switch(pBuf[0])
	{
	case 0x03:
		radioTohal_ImitateKey(FM1 + 1);
		break;
	case 0x10:
		ModuleParamResponse_WriteData();
		break;
	case 0x14: //通知各模块恢复出厂设置
		ModuleParamResponse_InitParam();
		ModuleParamResponse_WriteData();
		break;
	case 0x30:
		
		break;

	case 0x31://ACC OFF
		
		break;


	//news
	case 0x2C:	// acc off		
		Get_SystemAccOff();
		break;
	case 0x2D:	// acc on
		Get_SystemAccOn();
		break;
	case 0xE3:
		if (Ctrl_STOP != pLocalParam->eScanState)
			radioTohal_ScanCtrl(Ctrl_STOP);
		break;
		
	default:
		break;
	}
}

void OtherModuleToRadio_AnalyseAudioAndVideo(unsigned char *pBuf, int nLen)
{
	switch(pBuf[0])
	{
	case 0x00: //设置声音视频模式
		{
			if (0x04 == pBuf[1])
			{
				RadioToApp_CurChannelFreqText(pLocalParam->szCurFreq, strlen((char*)pLocalParam->szCurFreq));
				
				u8 nChannel=pLocalParam->eRadioChannel;
				radioToModule_AUXScreen_RadioChannel(nChannel);

				u16 wFrequency=pLocalParam->stszRadioChannelRecord[pLocalParam->eRadioChannel].wCurFrequency;
				radioToModule_AUXScreen_RadioFrequency(wFrequency);
				
				LOGD("radioToModule_AUXScreen:nChannel=%d,Frequency=%d",nChannel,(wFrequency >> 8) + ((wFrequency & 0xFF) << 8));
				IsCurFreqInRecord(nChannel,wFrequency);
				
			}
		}
		break;
	case 0x02:
		{
			if(pBuf[1] == 0x01)//The first audio init,the second radio!!!
			{
				ModuleParamResponse_InitByConfig();
			}
		}
		break;
	case 0x06: //设置静音
		break;
	}
}

void OtherModuleToRadio_AnalyseKey(unsigned char *pBuf, int nLen)
{
	if (pBuf[0] != 0x00)
		return;
	
	switch(pBuf[1])
	{
	case 0x02://面板按键MENU
		OtherModuleResponse_ProcessPanelKey_MENU();
		break;
	case 0x03:  //面板按键AV
		OtherModuleResponse_ProcessPanelKey_AV();
		break;
	case 0x06:
		OtherModuleResponse_ProcessPanelKey_RADIO();
		break;
	case 0x0B:      //FM1 0x0B
		OtherModuleResponse_ProcessPanelKey_FM1();
		break; 
	case 0x0C:      //FM2 0x0C
		OtherModuleResponse_ProcessPanelKey_FM2();
		break;
	case 0x0D:      //AM 0x0D
		OtherModuleResponse_ProcessPanelKey_AM();
		break;
	case 0x0E:	    //FM 0x0E
		OtherModuleResponse_ProcessPanelKey_FM();
		break;
	case 0x38:      //SEEK + : 0x38
		OtherModuleResponse_ProcessPanelKey_SEEK_INC();
		break;
	case 0x39:		//SEEK - : 0x39
		OtherModuleResponse_ProcessPanelKey_SEEK_DEC();
		break;
	case 0x3B:		//TUNE+: 0x3B
		OtherModuleResponse_ProcessPanelKey_TUNE_INC();
		break;
	case 0x3C:		//TUNE-: 0x3C
		OtherModuleResponse_ProcessPanelKey_TUNE_DEC();
		break;
	case 0x3D:      /*长按SEEK+*/
		OtherModuleResponse_ProcessPanelKey_SEEK_INC_TIMER();
		break;
	case 0x3E:      /*长按SEEK-*/
		OtherModuleResponse_ProcessPanelKey_SEEK_DEC_TIMER();
		break;
		break;
	default:
		break;	    
	}
}

void OtherModuleResponse_ProcessPanelKey_MENU()
{
	if (Ctrl_STOP != pLocalParam->eScanState)
			radioTohal_ScanCtrl(Ctrl_STOP);
	
     radioToModule_NotifySystem_JumpPage(PAGE_MENU);
}

void OtherModuleResponse_ProcessPanelKey_AV()
{
	if (Ctrl_STOP != pLocalParam->eScanState)
			radioTohal_ScanCtrl(Ctrl_STOP);

	u16 curPage = 0;
	unsigned char curPageLen = 2;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);

	if (curPage != PAGE_RADIO_MAIN)
		{
			radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
			return;
		}

	switch(pLocalParam->eRadioChannel)
		{
		case FM1:
			//radioTohal_ImitateKey(FM1 + 2);
			radioTohal_ImitateKey(FM1 + 3);
			break;
		//case FM2:
		//	radioTohal_ImitateKey(FM2 + 2);
		//	break;
		case AM:
			radioToModule_JumpToOtherModule();
			break;
		}
} 

void OtherModuleResponse_ProcessPanelKey_RADIO()
{
	if (Ctrl_STOP != pLocalParam->eScanState)
		radioTohal_ScanCtrl(Ctrl_STOP);

	u16 curPage = 0;
	unsigned char curPageLen = 2;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);
	if (curPage != PAGE_RADIO_MAIN)
	{
		radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
		return;
	}

	switch(pLocalParam->eRadioChannel)
	{
		case FM1:
			appToRadio_RadioChannel_MouseUp(AM);
		break;
		case FM2:
			appToRadio_RadioChannel_MouseUp(AM);
		break;
		case AM:
			appToRadio_RadioChannel_MouseUp(FM1);
		break;
		default:break;
	}
	
}

void OtherModuleResponse_ProcessPanelKey_FM1()
{
	appToRadio_RadioChannel_MouseUp(FM1);
	u16 curPage = 0;
	unsigned char curPageLen = 1;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);

	if (curPage != PAGE_RADIO_MAIN)
	{
		radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
	}
}  

void OtherModuleResponse_ProcessPanelKey_FM2()
{
	appToRadio_RadioChannel_MouseUp(FM2);
	u16 curPage = 0;
	unsigned char curPageLen = 1;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);

	if (curPage != PAGE_RADIO_MAIN)
	{
		radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
	}
}

void OtherModuleResponse_ProcessPanelKey_AM()
{
	appToRadio_RadioChannel_MouseUp(AM);
	u16 curPage = 0;
	unsigned char curPageLen = 1;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);

	if (curPage != PAGE_RADIO_MAIN)
	{
		radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
	}
} 

void OtherModuleResponse_ProcessPanelKey_FM()
{
	appToRadio_RadioChannel_MouseUp(FM1);
	u16 curPage = 0;
	unsigned char curPageLen = 1;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8 *)&curPage, (u8 *)&curPageLen);

	if (curPage != PAGE_RADIO_MAIN)
	{
		radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
	}
}   

void OtherModuleResponse_ProcessPanelKey_SEEK_INC()
{
	
	if (Ctrl_STOP != pLocalParam->eScanState)
	{
		pLocalParam->searchBeginIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;
		pLocalParam->searchSaveIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;
		radioTohal_ScanCtrl(Ctrl_STOP);
	}
	int mChannelRecordNum=0;
	u32 nChannel = pLocalParam->eRadioChannel;
	if(pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex == CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE)
	{
		pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = (pLocalParam->stszRadioChannelRecord[nChannel].curPage - 1) * CHANNEL_RECORD_NUM - 1;
	}
	int i;
	mChannelRecordNum = CHANNEL_RECORD_NUM*pLocalParam->stszRadioChannelRecord[nChannel].totalPages;
	for (i = 0; i < mChannelRecordNum; i++)
	{
		if (pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[i])
		{
			break;
		}
	}
	if (mChannelRecordNum == i)
		return;

	pLocalParam->bIsNeedCmpWithRecFreq = false;

	u8 cIndex = pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex;
	cIndex++;
	cIndex = cIndex % mChannelRecordNum;
	pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = cIndex ;

	while(!pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[cIndex ])
	{
		cIndex++;
		cIndex = cIndex % mChannelRecordNum;
		pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = cIndex ;
	}
	
	u32 dwFunID = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + (u32)(cIndex % CHANNEL_RECORD_NUM);
	int curPage = pLocalParam->stszRadioChannelRecord[nChannel].curPage;
	int cCurPage = (cIndex / CHANNEL_RECORD_NUM) + 1;
	setUpdateUI(0x00);
	if(curPage != cCurPage)
	{
		pLocalParam->stszRadioChannelRecord[nChannel].curPage = cCurPage;
		RadioToApp_UpdatePage(nChannel);
		RadioToApp_ChannelRecord(nChannel);
	}
	pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel] = pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel];
	RadioToApp_CurAndPreChange(pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel], dwFunID);
	//radioTohal_Frequency2(pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[cIndex + baseIndex]);
	radioTohal_Frequency(pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[cIndex ]);
	pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel] = dwFunID;

	radioToModule_AUXScreen_RadioRecord(cIndex );
	setUpdateUI(0x01);




} 

void OtherModuleResponse_ProcessPanelKey_SEEK_DEC()
{

	LOGD("--------------------dec---------------");
	if (Ctrl_STOP != pLocalParam->eScanState)
	{
		pLocalParam->searchBeginIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;
		pLocalParam->searchSaveIndex = CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE;
		radioTohal_ScanCtrl(Ctrl_STOP);
	}
	pLocalParam->bIsNeedCmpWithRecFreq = false;
	u32 nChannel = pLocalParam->eRadioChannel;
	if(pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex == CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE)
	{
		pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = (pLocalParam->stszRadioChannelRecord[nChannel].curPage) * CHANNEL_RECORD_NUM;
	}
	int i;
	int mChannelRecordNum=0;
	mChannelRecordNum = CHANNEL_RECORD_NUM*pLocalParam->stszRadioChannelRecord[nChannel].totalPages;
	for (i = 0; i < mChannelRecordNum; i++)
	{
		if (pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[i])
		{
			break;
		}
	}
	if (mChannelRecordNum == i)
		return;

	pLocalParam->bIsNeedCmpWithRecFreq = false;
	
	u8 cIndex = pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex;
	cIndex = cIndex + mChannelRecordNum - 1;
	cIndex = cIndex % mChannelRecordNum;
	pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = cIndex;

	while(!pLocalParam->stszRadioChannelRecord[nChannel].bRadioFreqRecordState[cIndex])
	{
		cIndex = cIndex + mChannelRecordNum - 1;
		cIndex = cIndex % mChannelRecordNum;
		pLocalParam->stszRadioChannelRecord[nChannel].cCurRecordIndex = cIndex ;
	}
	
	u32 dwFunID = CONTROLID_RADIO_MAIN_CHANNEL_NAME_BEGIN + (u32)(cIndex % CHANNEL_RECORD_NUM);
	int curPage = pLocalParam->stszRadioChannelRecord[nChannel].curPage;
	int cCurPage = (cIndex / CHANNEL_RECORD_NUM) + 1;
	setUpdateUI(0x00);
	if(curPage != cCurPage)
	{
		pLocalParam->stszRadioChannelRecord[nChannel].curPage = cCurPage;
		RadioToApp_UpdatePage(nChannel);
		RadioToApp_ChannelRecord(nChannel);
	}
	pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel] = pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel];
	RadioToApp_CurAndPreChange(pLocalParam->dwszCurChannelPreFreqRecFuncID[nChannel], dwFunID);
	//radioTohal_Frequency2(pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[cIndex + baseIndex]);
	radioTohal_Frequency(pLocalParam->stszRadioChannelRecord[nChannel].wRadioFreqRecord[cIndex ]);
	pLocalParam->dwszCurChannelCurFreqRecFuncID[nChannel] = dwFunID;
	setUpdateUI(0x01);

	radioToModule_AUXScreen_RadioRecord(cIndex);


	
} 


void OtherModuleResponse_ProcessPanelKey_TUNE_INC()
{
	if (Ctrl_STOP != pLocalParam->eScanState)
			radioTohal_ScanCtrl(Ctrl_STOP);
	if (TRUE == TimerOut(&pLocalParam->uPanelKeyTuneTime, 30))
	{
		radioTohal_ImitateKey(0x07);
	}
} 



void OtherModuleResponse_ProcessPanelKey_TUNE_DEC()
{
	if (Ctrl_STOP != pLocalParam->eScanState)
			radioTohal_ScanCtrl(Ctrl_STOP);
	if (TRUE == TimerOut(&pLocalParam->uPanelKeyTuneTime, 30))
	{
		radioTohal_ImitateKey(0x08);
	}
} 

void OtherModuleResponse_ProcessPanelKey_SEEK_INC_TIMER(void)
{
	LOGD("OtherModuleResponse_ProcessPanelKey_SEEK_INC_TIMER");
	pLocalParam->bUiButtonDownNoShow = true;
	rdaioToHal_Scan(Ctrl_SCAN_INC);
}
void OtherModuleResponse_ProcessPanelKey_SEEK_DEC_TIMER(void)
{
	LOGD("OtherModuleResponse_ProcessPanelKey_SEEK_INC_TIMER");
	pLocalParam->bUiButtonDownNoShow = true;
	rdaioToHal_Scan(Ctrl_SCAN_DEC);
}



void Get_SystemAccOn(void)
{	
	ModuleParamResponse_InitParam();
	//ModuleParamResponse_WriteData();
	ModuleParamResponse_InitByConfig();
}
void Get_SystemAccOff(void)
{
	ModuleParamResponse_WriteData();
}



/*****************************************ExternalResponseToRadio********************************************************/
void OtherModuleToRadio_AnalyseExternalCtrl(unsigned char *pBuf, int nLen)
{
	LOGD("ExternalResponseToRadio %x %x %x",pBuf[0],pBuf[1],pBuf[2]);
	if (Ctrl_STOP != pLocalParam->eScanState)
		radioTohal_ScanCtrl(Ctrl_STOP);
	
	if(pBuf[0] == 0x00)
	{	
		switch(pBuf[1])
		{
			case 0x00:
			{
				if(pBuf[2] == 0x01){
					ExternalResponseToRadio_Open();
				}
				else if(pBuf[2] == 0x00){
					ExternalResponseToRadio_Close();
				}
			}
			break;
			case 0x01:
			{
				if(pBuf[2] == 0x00)
					ExternalResponseToRadio_Listen_TheSpecificRadioName(&pBuf[3],nLen-3);
			}
			break;
			case 0x02:
			{
				if(pBuf[2] == 0x00)
					ExternalResponseToRadio_SearchChannel(&pBuf[3],nLen-3);
			}
			break; 
			case 0x03:
			{
				if(pBuf[2] == 0x01){
					ExternalResponseToRadio_SetFrequency_AM(&pBuf[3],nLen-3);
				}
				else if(pBuf[2] == 0x00){
					ExternalResponseToRadio_SetFrequency_FM(&pBuf[3],nLen-3);
				}
			}
			break;
			case 0x04:
			{
				switch(pBuf[2])
				{
					case 0x00:
					{
						u16 CurPageID = 0;
						u8  CurPageIDLen = 0;
						getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);

						u8 ucBackMode = 0;
						u8 ucBackModeLen = 0;
						getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,&ucBackModeLen);
						LOGD("externalctrl_FlyaudioApp ucBackMode:%x CurPageID:%x",ucBackMode,CurPageID);
						if(ucBackMode == 1 || CurPageID == PAGE_BLACK || CurPageID == PAGE_BACK_NOVIDEO || CurPageID == PAGE_BACK_VIDEO || CurPageID == PAGE_BACK_RADAR || CurPageID == PAGE_BACK_FULL_VIDEO || CurPageID == PAGE_BACK_FULL_VIDEO_CONTROL)
						{
							return;
						}
						
						radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
			
						appToRadio_ClearAllFrequencyRecord(pLocalParam->eRadioChannel);
						pLocalParam->searchSaveIndex = 0;
						pLocalParam->searchBeginIndex = 0;

						rdaioToHal_Scan(Ctrl_SCAN_REPEAT);
					}
					break;
					case 0x01:
					break;
					case 0x02:
					break;
					case 0x03:
					{
						if(Ctrl_STOP != pLocalParam->eScanState)
							radioTohal_ScanCtrl(Ctrl_STOP);
					}
					break;
					case 0x04:
					break;
					case 0x05:
					break;
					case 0x06:
					break;
					default:break;
				}
			}
			break;
			default:break;	    
		}
	}
	else if(pBuf[0] == 0x01)
	{
		if(pBuf[1] == 0x01)
		{
		 	radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);
		}
		else
		{
		}
	}

}

void moduleToRadio_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}

void ExternalResponseToRadio_Open()
{
	u16 CurPageID = 0;
	u8  CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);

	u8 ucBackMode = 0;
	u8 ucBackModeLen = 0;
	getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,&ucBackModeLen);
	LOGD("externalctrl_FlyaudioApp ucBackMode:%x CurPageID:%x",ucBackMode,CurPageID);
	if(ucBackMode == 1 || CurPageID == PAGE_BLACK || CurPageID == PAGE_BACK_NOVIDEO || CurPageID == PAGE_BACK_VIDEO || CurPageID == PAGE_BACK_RADAR || CurPageID == PAGE_BACK_FULL_VIDEO || CurPageID == PAGE_BACK_FULL_VIDEO_CONTROL)
	{
		return;
	}
	
	radioToModule_NotifySystem_JumpPage(PAGE_RADIO_MAIN);

	LOGD("ExternalResponseToRadio_Open pLocalParam->bIsRadioPowerOn:%x",pLocalParam->bIsRadioPowerOn);
	if (pLocalParam->bIsRadioPowerOn == false)
	{
		radioTohal_RadioSwitch_Power(0x01);// turn on
	}
}

void ExternalResponseToRadio_Close()
{
	LOGD("ExternalResponseToRadio_Close pLocalParam->bIsRadioPowerOn:%x",pLocalParam->bIsRadioPowerOn);
	if (pLocalParam->bIsRadioPowerOn == true)
	{
		radioTohal_RadioSwitch_Power(0x00);// turn off
	}
}

void ExternalResponseToRadio_Open_No_Jump()
{
	LOGD("ExternalResponseToRadio_Close pLocalParam->bIsRadioPowerOn:%x",pLocalParam->bIsRadioPowerOn);
	if (pLocalParam->bIsRadioPowerOn == false)
	{
		radioTohal_RadioSwitch_Power(0x01);// turn on
	}
}

void ExternalResponseToRadio_Listen_TheSpecificRadioName(unsigned char *pBuf, int nLen)
{
}

void ExternalResponseToRadio_SearchChannel(unsigned char *pBuf, int nLen)
{
	if(pLocalParam->isSearch == NO_SEARCH)
		return;
	appToRadio_ClearAllFrequencyRecord(pLocalParam->eRadioChannel);
	pLocalParam->searchSaveIndex = 0;
	pLocalParam->searchBeginIndex = 0;
	rdaioToHal_Scan(Ctrl_SCAN_REPEAT);
}

void ExternalResponseToRadio_SetFrequency_FM(unsigned char *pBuf, int nLen)
{
	LOGD("ExternalResponseToRadio_SetFrequency_FM pLocalParam->eRadioChannel:%x",pLocalParam->eRadioChannel);	
	if (pLocalParam->eRadioChannel != 0x00){
		radioTohal_ImitateKey(0x01);
	}
	
	LOGD("*************start***************");
	for(int i =0;i<nLen;i++)
	{
	LOGD("***FM:%d",pBuf[i]);
	}
	LOGD("**************end****************");

	u32 n_curFrequency = pBuf[0]+pBuf[1]*256+pBuf[2]*256*256+pBuf[3]*256*256*256;
	LOGD("n_curFrequency:%d",n_curFrequency);
	int n_H = n_curFrequency/100;
	int n_L = n_curFrequency%100;
	LOGD("%d %d",n_H,n_L);

	u8 buffer1[3];
	memset(buffer1,0,sizeof(buffer1));
	
	for(int i=2;i>=0;i--)
	{
		buffer1[i] =(char)(n_H%10);
		n_H = n_H/10;
	}
	for(int j=0;j<3;j++)
	{
		externalResponseToRadio_Number_num(buffer1[j]);
	}

	unsigned char chKey = '.';
	appToRadio_Radio_Numb(chKey);

	u8 buffer2[2];
	memset(buffer2,0,sizeof(buffer2));

	for(int i=1;i>=0;i--)
	{
		buffer2[i] =(char)(n_L%10);
		n_L = n_L/10;
	}
	
	for(int j=0;j<2;j++)
	{
		externalResponseToRadio_Number_num(buffer2[j]);
	}

	ExternalResponseToRadio_SetFrequency();
}

void ExternalResponseToRadio_SetFrequency_AM(unsigned char *pBuf, int nLen)
{
	LOGD("ExternalResponseToRadio_SetFrequency_AM pLocalParam->eRadioChannel:%x",pLocalParam->eRadioChannel);
	if (pLocalParam->eRadioChannel != 0x02){
		radioTohal_ImitateKey(0x03);
	}
	
	LOGD("*************start***************");
	for(int i =0;i<nLen;i++)
	{
	LOGD("***AM:%d",pBuf[i]);
	}
	LOGD("**************end****************");

	u32 n_curFrequency = pBuf[0]+pBuf[1]*256+pBuf[2]*256*256+pBuf[3]*256*256*256;
	LOGD("n_curFrequency:%d",n_curFrequency);
	u8 buffer[nLen];
	memset(buffer,0,sizeof(buffer));
	
	for(int i=nLen-1;i>=0;i--)
	{
		buffer[i] =(char)(n_curFrequency%10);
		n_curFrequency = n_curFrequency/10;
	}

	for(int j=0;j<nLen;j++)
	{
		externalResponseToRadio_Number_num(buffer[j]);
	}

	ExternalResponseToRadio_SetFrequency();

}

void externalResponseToRadio_Number_num(u8 buff)
{
	LOGD("Number_num %d",buff);
	u8 uKey = 0;
	if(buff>=0 && buff<10)
	{
		uKey = (char)(buff+0x30);
	}

	appToRadio_Radio_Numb(uKey);

}

void  ExternalResponseToRadio_SetFrequency()
{
	appToRadio_Analyze_FrequencyMessage();
	clearInputFreq();
}

void moduleToRadio_FromCenter_Message(u8 *param, int len)
{
	switch(param[0])
	{
		case 0x00:
			//ModuleParamResponse_InitByConfig();
		break;
	}
}

void moduleToRadio_FromAuxcreen_Message(u8 *buf, int len)
{
	switch(buf[0])
	{
		case 0x30:
			analyseAuxcreenSetRadioBandValue(buf[1]);	
		break;
		default:break;
	}
}


/*************************************************************************************************/

void analyseTimerHandleMessage(u8 *p, u8 len)
{
}

void analyseAuxcreenSetRadioBandValue(u8 param)
{
	if(param == 0x00 ||param == 0x01 ||param == 0x02)
		appToRadio_RadioChannel_MouseUp(param);
}












