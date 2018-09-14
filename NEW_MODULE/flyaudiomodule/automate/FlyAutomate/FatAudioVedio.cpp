#include "FatAudioVedio.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"

CFatAudioVedio::CFatAudioVedio(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["2101"] = &CFatAudioVedio::SelectVolume;
	mapCmdFunc["2110"] = &CFatAudioVedio::SelectMuteOn;
	mapCmdFunc["2111"] = &CFatAudioVedio::SelectMuteOff;
	mapCmdFunc["21AS"] = &CFatAudioVedio::ResponseValueVolume;
	mapCmdFunc["2201"] = &CFatAudioVedio::SelectLengthwaysBalance;
	mapCmdFunc["2202"] = &CFatAudioVedio::SelectCrosswiseBalance;
	mapCmdFunc["22AS"] = &CFatAudioVedio::ResponseValueBalance;
	mapCmdFunc["2401"] = &CFatAudioVedio::SelectEqualizer;
	mapCmdFunc["24AS"] = &CFatAudioVedio::ResponseValueEqualizer;
}

CFatAudioVedio::~CFatAudioVedio(void)
{
}

void CFatAudioVedio::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatAudioVedio::SelectVolume( u8* pCmd, u8 ucLen )
{
	u8 ucMaxVolume = 0;
	u8 ucMaxVolumeLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, MAX_VOLUME, &ucMaxVolume, &ucMaxVolumeLen);
	u8 uTempParam = TransformAcsiiToInteger(pCmd+4, 2);

	if(uTempParam > ucMaxVolume){
		return;
	}
	
	m_pFatHal->Set_Volume(uTempParam);
	m_pFatHal->Send_DriverACK();
}

void CFatAudioVedio::SelectMuteOn( u8* pCmd, u8 ucLen )
{
	m_pFatHal->Set_Mute(true);
	m_pFatHal->Send_DriverACK();
}

void CFatAudioVedio::SelectMuteOff( u8* pCmd, u8 ucLen )
{
	m_pFatHal->Set_Mute(false);
	m_pFatHal->Send_DriverACK();
}

void CFatAudioVedio::ResponseValueVolume( u8* pCmd, u8 ucLen )
{
	u8 ucVolume = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_VOLUME, &ucVolume, &ucParamLen);
	u8 szVolume[] = {'I', 0x00, 0x00};
	//sprintf((char*)(szVolume+1), "%02d", ucVolume);
	TransformIntegerToAcsii(szVolume+1, ucVolume, 10, 2);
	m_pFatHal->SendResponseMsg(szVolume, sizeof(szVolume));
}

void CFatAudioVedio::SelectLengthwaysBalance( u8* pCmd, u8 ucLen )
{
	m_pFatHal->Set_FrontRearBalance(TransformAcsiiToInteger(pCmd+4, 2));
	m_pFatHal->Send_DriverACK();
}

void CFatAudioVedio::SelectCrosswiseBalance( u8* pCmd, u8 ucLen )
{
	m_pFatHal->Set_LeftRightBalance(TransformAcsiiToInteger(pCmd+4, 2));
	m_pFatHal->Send_DriverACK();
}

void CFatAudioVedio::ResponseValueBalance( u8* pCmd, u8 ucLen )
{
	u8 ucFRBalance = 0;
	u8 ucLRBalance = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_FRONT_REAR_BALANCE, &ucFRBalance, &ucParamLen);
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_LEFT_RIGHT_BALANCE, &ucLRBalance, &ucParamLen);
	
	u8 szBalance[] = {'I', 0x00, 0x00, 0x00, 0x00};
// 	sprintf((char*)(szBalance+1), "%02d", ucFRBalance);
// 	sprintf((char*)(szBalance+3), "%02d", ucLRBalance);
	TransformIntegerToAcsii(szBalance+1, ucFRBalance, 10, 2);
	TransformIntegerToAcsii(szBalance+3, ucLRBalance, 10, 2);
	m_pFatHal->SendResponseMsg(szBalance, sizeof(szBalance));
}

void CFatAudioVedio::SelectEqualizer( u8* pCmd, u8 ucLen )
{
	int nIndex = TransformAcsiiToInteger(pCmd+4, 2);
	switch(nIndex)
	{
	case 1:
		{
			m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_AUDIOVIDEO, CONTROLID_EQ_CALSSICAL);
			m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_AUDIOVIDEO, CONTROLID_EQ_CALSSICAL);
			m_pFatHal->Send_DriverACK();
		}
		break;
	case 2:
		{
			m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_AUDIOVIDEO, CONTROLID_EQ_POP);
			m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_AUDIOVIDEO, CONTROLID_EQ_POP);
			m_pFatHal->Send_DriverACK();
		}
		break;
	case 3:
		{
			m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_AUDIOVIDEO, CONTROLID_EQ_JAZZ);
			m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_AUDIOVIDEO, CONTROLID_EQ_JAZZ);
			m_pFatHal->Send_DriverACK();
		}
		break;
	}
}

void CFatAudioVedio::ResponseValueEqualizer( u8* pCmd, u8 ucLen )
{
	u8 ucEqualizer = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_EQUALIZER, &ucEqualizer, &ucParamLen);
	u8 szEqualizer[] = {'I', 0x00, 0x00};
	//sprintf((char*)(szEqualizer+1), "%02d", ucEqualizer);
	TransformIntegerToAcsii(szEqualizer+1, ucEqualizer, 10, 2);
	m_pFatHal->SendResponseMsg(szEqualizer, sizeof(szEqualizer));
}
