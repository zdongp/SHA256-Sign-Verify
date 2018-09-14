#include "FatRadio.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"
CFatRadio::CFatRadio(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	m_nCheckFreq = 0;
	m_bCheckSearch = false;

	mapCmdFunc["4101"] = &CFatRadio::EnterRadio;
	mapCmdFunc["4102"] = &CFatRadio::SelectRadioFrequency;
	mapCmdFunc["4103"] = &CFatRadio::EnterAndSelectRadioFrequency;
	mapCmdFunc["41AS"] = &CFatRadio::ExecuteSpecifyFreqSearch;
	mapCmdFunc["4111"] = &CFatRadio::ExecuteScan;
	mapCmdFunc["4201"] = &CFatRadio::EnterRadio;
	mapCmdFunc["4202"] = &CFatRadio::SelectRadioFrequency;
	mapCmdFunc["4203"] = &CFatRadio::EnterAndSelectRadioFrequency;
	mapCmdFunc["42AS"] = &CFatRadio::ExecuteSpecifyFreqSearch;
	mapCmdFunc["4211"] = &CFatRadio::ExecuteScan;
}

CFatRadio::~CFatRadio(void)
{
}

void CFatRadio::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatRadio::AnalyseHalMsgFromRadio( u8 * pMsg, u8 ucLen, u8 ucCmd )
{
	if (!m_bCheckSearch)
		return;

	static u16 nCurFreq = 0;
	switch(ucCmd)
	{
	case 0x10:
		{
			nCurFreq = (u16)(pMsg[1] + (pMsg[0]<<8 & 0xFF00));
			FLY_LOG(LOG_LV_DEBUG, "nCurFreq = %d", nCurFreq);
			if (nCurFreq	> m_nCheckFreq)
			{
				m_pFatHal->Set_RadioScanCtrl(emCtrl_STOP);
				m_bCheckSearch = false;
				nCurFreq = 0;
				u8 szMsg[] = {'4', 'S', '0'};
				m_pFatHal->SendResponseMsg(szMsg, sizeof(szMsg));
			}
		}
		break;
	case 0x14:
		{
			FLY_LOG(LOG_LV_DEBUG, "nCurFreq = %d", nCurFreq);
			if (nCurFreq == m_nCheckFreq)
			{
				m_pFatHal->Set_RadioScanCtrl(emCtrl_STOP);
				m_bCheckSearch = false;
				nCurFreq = 0;
				u8 szMsg[] = {'4', 'S', '1'};
				m_pFatHal->SendResponseMsg(szMsg, sizeof(szMsg));
			}
		}
		break;
	}
}

void CFatRadio::ResponseInfoCurFatState()
{
	u8 szQuery[] = {'4', '0', '1', '0', '0', '0', '0'};
	u16 nFreq = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_RADIO, CUR_FREQ, (u8*)&nFreq, &ucParamLen);
	nFreq = (nFreq>>8) + ((nFreq & 0xff)<<8);	//高8位和低8位调换
	u8 ucVolume = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_VOLUME, &ucVolume, &ucParamLen);
	switch(m_pFatHal->GetCurFatState())
	{
	case FAT_FM:
		{
			szQuery[1] = '1';
			nFreq = (nFreq-8750)/10;
		}
		break;
	case FAT_AM:
		{
			szQuery[1] = '2';
			nFreq = (nFreq-522)/9;
		}
		break;
	default:
		return;
		break;
	}
	TransformIntegerToAcsii(szQuery+3, nFreq, 16, 2);
	TransformIntegerToAcsii(szQuery+5, ucVolume, 10, 2);
 	m_pFatHal->SendResponseMsg(szQuery, sizeof(szQuery));
}

void CFatRadio::JumpMediaByCommand( u8 ucFlag )
{
	m_pFatModule->NotifySystemJumpPage(PAGE_RADIO_MAIN);
	u8 ucCurChannel = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_RADIO, CUR_CHANNEL, (u8*)&ucCurChannel, &ucParamLen);
	FLY_LOG(LOG_LV_DEBUG, "ucFlag = %c ucCurChannel = 0x%x", ucFlag, ucCurChannel);
	if ('1' == ucFlag && emImitateKey_FM1 != ucCurChannel)
	{
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_RADIO, CONTROLID_RADIO_MAIN_FM1);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_RADIO, CONTROLID_RADIO_MAIN_FM1);
		m_pFatHal->SetCurFatState(FAT_FM);
	}
	else if ('2' == ucFlag && emImitateKey_AM != ucCurChannel)
	{
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_RADIO, CONTROLID_RADIO_MAIN_AM);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_RADIO, CONTROLID_RADIO_MAIN_AM);
		m_pFatHal->SetCurFatState(FAT_AM);
	}
}

u16 CFatRadio::CalculateRadioFreq( short nStep )
{
	u16 nFreq = 0;
	if (FAT_FM == m_pFatHal->GetCurFatState())
		nFreq = 10*nStep+8750;
	else
		nFreq = 9*nStep + 522;

	return nFreq;
}

void CFatRadio::EnterRadio( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[1]);
	m_pFatHal->Send_DriverACK();
}

void CFatRadio::SelectRadioFrequency( u8* pCmd, u8 ucLen )
{
	u16 nStep = TransformAcsiiToInteger(pCmd+4, 3);
	FLY_LOG(LOG_LV_DEBUG, "nSelectFreq = %d", CalculateRadioFreq(nStep));
	m_pFatHal->Set_RadioFrequency(CalculateRadioFreq(nStep));
	m_pFatHal->Send_DriverACK();
}

void CFatRadio::EnterAndSelectRadioFrequency( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[1]);
	SelectRadioFrequency(pCmd, ucLen);
}

void CFatRadio::ExecuteSpecifyFreqSearch( u8* pCmd, u8 ucLen )
{
	u16 nStep = TransformAcsiiToInteger(pCmd+4, 3);
	m_nCheckFreq = CalculateRadioFreq(nStep);
	m_bCheckSearch = true;
	m_pFatHal->Set_RadioFrequency(CalculateRadioFreq(nStep-1));
	m_pFatHal->Set_RadioScanCtrl(emCtrl_SCAN_INC);
	FLY_LOG(LOG_LV_DEBUG, "m_nCheckFreq = %d", m_nCheckFreq);
}

void CFatRadio::ExecuteScan( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_RADIO, CONTROLID_RADIO_MAIN_SCAN);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_RADIO, CONTROLID_RADIO_MAIN_SCAN);
	m_pFatHal->Send_DriverACK();
}
