/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "FatHal.h"

CFatHal::CFatHal(void)
{
	m_emCurFatState = FAT_NULL;
}

CFatHal::~CFatHal(void)
{
	if (NULL != m_pFatSystem)
	{
		delete m_pFatSystem;
		m_pFatSystem = NULL;
	}
	if (NULL != m_pFatAudioVedio)
	{
		delete m_pFatAudioVedio;
		m_pFatAudioVedio = NULL;
	}
	if (NULL != m_pFatRadio)
	{
		delete m_pFatRadio;
		m_pFatRadio = NULL;
	}
	if (NULL != m_pFatDVD)
	{
		delete m_pFatDVD;
		m_pFatDVD = NULL;
	}
	if (NULL != m_pFatMedia)
	{
		delete m_pFatMedia;
		m_pFatMedia = NULL;
	}
	if (NULL != m_pFatAUX)
	{
		delete m_pFatAUX;
		m_pFatAUX = NULL;
	}
	if (NULL != m_pFatBlueTooth)
	{
		delete m_pFatBlueTooth;
		m_pFatBlueTooth = NULL;
	}
	if (NULL != m_pFatDVR)
	{
		delete m_pFatDVR;
		m_pFatDVR = NULL;
	}
	if (NULL != m_pFatTPMS)
	{
		delete m_pFatTPMS;
		m_pFatTPMS = NULL;
	}
	if (NULL != m_pFatiPod)
	{
		delete m_pFatiPod;
		m_pFatiPod = NULL;
	}
}

void CFatHal::init(void)
{
}

void CFatHal::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{
	m_pFatApp	 = (CFatApp *)pFlyApp; 
	m_pFatModule = (CFatModule *)pFlyModule; 
	m_pFatHal	 = (CFatHal *)pFlyHal; 
	m_pFatParam  = (CFatParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;

	m_pFatSystem = new CFatSystem(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatAudioVedio = new CFatAudioVedio(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatRadio = new CFatRadio(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatDVD = new CFatDVD(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatMedia = new CFatMedia(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatAUX = new CFatAUX(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatBlueTooth = new CFatBlueTooth(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatDVR = new CFatDVR(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatTPMS = new CFatTPMS(m_pFatHal, m_pFatApp, m_pFatModule);
	m_pFatiPod = new CFatiPod(m_pFatHal, m_pFatApp, m_pFatModule);
}

void CFatHal::analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len)
{
	switch(halId)
	{
	case HAL_ID_DVR:
		{
			if (0x1E != cmd)
				return;
			AnalyseHalMsgFromDVR(p+2, len-2);
		}
		break;
	case HAL_ID_RADIO:
		m_pFatRadio->AnalyseHalMsgFromRadio(p, len, cmd);
		break;
	default:
		break;
	}
}

void CFatHal::AnalyseHalMsgFromDVR( u8 * pCmd, u8 ucLen )
{
	u8 ucCmd = pCmd[0];
	FLY_LOG(LOG_LV_DEBUG, "ucCmd = %c", ucCmd);
	if (!JudgeAutomateState(pCmd, ucLen))
		return;
	
	switch(ucCmd)
	{
	case '0':
	case '1':
	case '3':
	case 'J':
	case 'K':
		m_pFatSystem->AnalyseFATCommand(pCmd, ucLen);
		break;
	case '2':
		m_pFatAudioVedio->AnalyseFATCommand(pCmd, ucLen);
		break;
	case '4':
		m_pFatRadio->AnalyseFATCommand(pCmd, ucLen);
		break;
	case '5':
		m_pFatDVD->AnalyseFATCommand(pCmd, ucLen);
		break;
	case '6':
	case '7':
	case 'I':
		m_pFatMedia->AnalyseFATCommand(pCmd, ucLen);
		break;
	case '8':
		m_pFatiPod->AnalyseFATCommand(pCmd, ucLen);
		break;
	case '9':
		m_pFatAUX->AnalyseFATCommand(pCmd, ucLen);
		break;
	case 'B':
		m_pFatBlueTooth->AnalyseFATCommand(pCmd, ucLen);
		break;
	case 'E':
		m_pFatDVR->AnalyseFATCommand(pCmd, ucLen);
		break;
	case 'H':
		m_pFatTPMS->AnalyseFATCommand(pCmd, ucLen);
		break;
	case 'R':
		Send_CurFatStatus();
		break;
	default:
		break;
	}
}

void CFatHal::SetCurFatState( emFatStatus emCurState )
{
	m_emCurFatState = emCurState;
}

emFatStatus CFatHal::GetCurFatState()
{
	return m_emCurFatState;
}

bool CFatHal::JudgeAutomateState( u8* pCmd, u8 ucLen )
{
	static bool bEnable = false;
	if ('0' == pCmd[0] &&
		'1' == pCmd[1] &&
		'0' == pCmd[2])
	{
		if ('1' == pCmd[3])
		{
			bEnable = true;

			m_pFatApp->ToUIcurIsAutomateMode(1);
			m_pFatApp->GetIMEI();
			m_pFatApp->GetCarMAC();
			m_pFatApp->GetWifiConnectStatus();
			m_pFatApp->GetWifiNetworksignalStrength();
			m_pFatApp->Get4GNetworksignalStrength();
			m_pFatApp->GetSd1Status();
			m_pFatApp->GetSd1MemoryUsage();
			m_pFatApp->GetSd1TheTotalSize();
			m_pFatApp->GetSd0MemoryUsage();
			m_pFatApp->GetSd0TheTotalSize();
			m_pFatModule->NotifyMP3_GoToAutoMate();
			m_pFatApp->GetWifiWhetherInternetStatus();
			m_pFatApp->Get4GWhetherInternetStatus();
			m_pFatModule->NotifyMP3_UsbStateInit();
			Send_DriverACK();
		}
		else if ('2' == pCmd[3])
		{
			bEnable = false;
			m_pFatApp->ToUIcurIsAutomateMode(0);
			Send_DriverACK();
		}
	}
	return bEnable;
}

void CFatHal::Send_DriverACK_Data(u8 p)
{
	u8 szMsg[] = {'A', 'C', 'K','0'};
	if(p == 1)
	{
		szMsg[3] = '1';
	}
	FLY_LOG(LOG_LV_DEBUG, "szMsg = %s", szMsg);
	m_pFatHal->SendResponseMsg(szMsg,4);
}

void CFatHal::SendResponseMsg( u8* pBuf, u8 ucLen )
{
	if(ucLen > (CMD_TO_AUTOMATE_MAX_LEN - 4))
		ucLen = CMD_TO_AUTOMATE_MAX_LEN - 4;
		
	int nLen = ucLen+4;
	
	char pMsg[CMD_TO_AUTOMATE_MAX_LEN];
	memset(pMsg,0,sizeof(pMsg));
	
	pMsg[0] = 0x1E;
	pMsg[1] = '0';
	pMsg[2] = '2';
	if(ucLen > 0){
		memcpy(&pMsg[3],pBuf, ucLen);
	}
	pMsg[ucLen+3] = 0x0D;
	
	//for(int i = 0;i < nLen;i++)
	//{
	//	FLY_LOG(LOG_LV_DEBUG, "pMsg = %x", pMsg[i]);
	//}
	
	makeAndSendMessageToHal(HAL_ID_DVR,(u8*)pMsg, nLen);
}

void CFatHal::Send_DriverACK()
{
	u8 szMsg[] = {'A', 'C', 'K'};
	SendResponseMsg(szMsg, sizeof(szMsg));
}

void CFatHal::Send_CurFatStatus()
{
	switch(m_emCurFatState)
	{
	case FAT_FM:
	case FAT_AM:
		m_pFatRadio->ResponseInfoCurFatState();
		break;
	case FAT_DVD:
		m_pFatDVD->ResponseInfoCurFatState();
		break;
	case FAT_MUSIC:
	case FAT_VAP:
		m_pFatMedia->ResponseInfoCurFatState();
		break;
	case FAT_AUX:
		m_pFatAUX->ResponseInfoCurFatState();
		break;
	case FAT_BT:
		m_pFatBlueTooth->ResponseInfoCurFatState();
		break;
	case FAT_DVR:
		m_pFatDVR->ResponseInfoCurFatState();
		break;
	default:
		break;
	}
}

void CFatHal::Set_LCDBrightness( u8 ucBright )
{
	FLY_LOG(LOG_LV_DEBUG, "ucBright = %d", ucBright);
	u8 szMsg[] = {0x14, ucBright};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, szMsg, sizeof(szMsg));
}

void CFatHal::Set_StandbyState( u8 ucStandby )
{
	FLY_LOG(LOG_LV_DEBUG, "ucStandby = %d", ucStandby);
	u8 szMsg[] = {0x32, ucStandby};
	makeAndSendMessageToHal(HAL_ID_SYSTEM, szMsg, sizeof(szMsg));
}

void CFatHal::Set_Volume( u8 ucVolume )
{
	FLY_LOG(LOG_LV_DEBUG, "ucVolume = %d", ucVolume);
	u8 szMsg[] = {0x12, ucVolume};
	makeAndSendMessageToHal(HAL_ID_AUDIO, szMsg, sizeof(szMsg));
}

void CFatHal::Set_Mute( bool bMute )
{
	FLY_LOG(LOG_LV_DEBUG, "bMute = %d", bMute);
	u8 szMsg[] = {0x11, 0x00};
	szMsg[1] = bMute ? 0x01 : 0x00;
	makeAndSendMessageToHal(HAL_ID_AUDIO, szMsg, sizeof(szMsg));
}

void CFatHal::Set_LeftRightBalance( u8 ucBalance )
{
	FLY_LOG(LOG_LV_DEBUG, "ucBalance = %d", ucBalance);
	u8 szMsg[] = {0x13, ucBalance};
	makeAndSendMessageToHal(HAL_ID_AUDIO, szMsg, sizeof(szMsg));
}

void CFatHal::Set_FrontRearBalance( u8 ucBalance )
{
	FLY_LOG(LOG_LV_DEBUG, "ucBalance = %d", ucBalance);
	u8 szMsg[] = {0x14, ucBalance};
	makeAndSendMessageToHal(HAL_ID_AUDIO, szMsg, sizeof(szMsg));
}

void CFatHal::Set_Equalizer( u8 ucEqualizer )
{
	u8 szMsg[] = {0x21, ucEqualizer};
// 	if (0x01 == ucEqualizer)
// 		szMsg[1] = EQ_CLASS;
// 	else if(0x02 == ucEqualizer)
// 		szMsg[1] = EQ_POP;
// 	else if(0x03 == ucEqualizer)
// 		szMsg[1] = EQ_JAZZ;

	FLY_LOG(LOG_LV_DEBUG, "ucEqualizer = %d", ucEqualizer);
	makeAndSendMessageToHal(HAL_ID_AUDIO, szMsg, sizeof(szMsg));
}

void CFatHal::Set_RadioSoftWareImitateKey(u8 ucKey)
{
	u8 szMsg[2] = {0x03, ucKey};
	makeAndSendMessageToHal(HAL_ID_RADIO, szMsg, sizeof(szMsg));
}

void CFatHal::Set_RadioScanCtrl(u8 ucCtrl)
{
	u8 szMsg[2] = {0x13, ucCtrl};
	makeAndSendMessageToHal(HAL_ID_RADIO, szMsg, sizeof(szMsg));
}

void CFatHal::Set_RadioFrequency(u16 nFreq)//设置收音机频率
{
	short nParam = (nFreq>>8) + ((nFreq & 0xff)<<8);
	u8 szMsg[]={0x10,0x00,0x00};
	memcpy(szMsg+1,&nParam,2);
	makeAndSendMessageToHal(HAL_ID_RADIO, szMsg, sizeof(szMsg));
}
