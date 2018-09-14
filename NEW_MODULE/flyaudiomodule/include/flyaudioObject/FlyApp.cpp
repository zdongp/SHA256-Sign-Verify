/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "FlyApp.h"

extern "C"
{
	#include "unicodestring.h"
};

extern void sendMessageToApp(appMessage_t *pAppMsg);
extern void sendMessageToAgent(agentMessage_t *pAgentMsg);
extern int sendSetTimerMessage(int moduleID, int timeOut, int timerMode);
extern int sendKillTimerMessage(int timerID);
extern int sendSetPageMessage(int pageId);
extern int sendSetVolumeMessage(int type,int value,int flags1);


CFlyApp::CFlyApp(void)
{
}

CFlyApp::~CFlyApp(void)
{
}

void CFlyApp::deInit(void)
{

}

void CFlyApp::analyseAppMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
	u32 id = 0;
	E_MOUSE_STATUS e = MOUSE_STATUS_UNKNOW;
	u8 paramLen = 0;
	u8 *pParam = NULL;

	id += (u32)((p[0] << 24) & 0xFF000000);
	id += (u32)((p[1] << 16) & 0xFF0000);
	id += (u32)((p[2] << 8)  & 0xFF00);
	id += (u32)(p[3]         & 0xFF);

	e = (E_MOUSE_STATUS)p[4];
	paramLen = len - 5;
	pParam = p + 5;
 
    processMouseMsg(id, e, pParam, paramLen); 
}

void CFlyApp::analyseAgentMessage(moduleid_t id, u8 *p, u8 len)
{
	//outPutLog(__FUNCTION__, "p", p, len);

	m_pFlyHal->analyseAgentMessage(id, p, len);
} 

void CFlyApp::processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
}

void CFlyApp::appCmdCtrl(u8 *p, u8 len)
{

}

void CFlyApp::setDigitalData(u32 id, bool b)
{
	u8 p = (b) ? 1 : 0;

	makeAndSendMessageToUI(id, UI_CONTROL_TYPE_DIGITAL, &p, 1);
}

void CFlyApp::setAnalogData(u32 id,  u32 a)
{
	u8 szMsg[4] = {0};

	szMsg[0] = (u8)((a >> 24) & 0xFF);
	szMsg[1] = (u8)((a >> 16) & 0xFF);
	szMsg[2] = (u8)((a >> 8) & 0xFF);
	szMsg[3] = (u8)(a & 0xFF);

	makeAndSendMessageToUI(id, UI_CONTROL_TYPE_ANALOG, szMsg, 4);
}

void CFlyApp::setGroupNumber(u32 id, u8 i)
{
	u8 szMsg[2] = {0};

	szMsg[0] = 0x20;
	szMsg[1] = i;

	setCommand(id, szMsg, sizeof(szMsg));
}

void CFlyApp::setProgressRange(u32 id, int r)
{
	u8 szMsg[5] = {0};

	szMsg[0] = 0x60;
	szMsg[1] = (u8)(r >> 24) & 0xFF;
	szMsg[2] = (u8)(r >> 16) & 0xFF;
	szMsg[3] = (u8)(r >> 8)  & 0xFF;
	szMsg[4] = (u8)(r >> 0)  & 0xFF;

	setCommand(id, szMsg, sizeof(szMsg));
}

void CFlyApp::setSerialData(u32 id, u8 *p, u32 len)
{
	makeAndSendMessageToUI(id, UI_CONTROL_TYPE_SERIAL, p, len);
}

void CFlyApp::setAnsiSerialData(u32 id, u8 *p, u32 len)//????
{
	u32 dwAnsiBufLen = strlen((char*)p);
	u8 *pUnicodeBuf = (u8*)malloc(dwAnsiBufLen * 2 + 2);
	memset(pUnicodeBuf, 0, dwAnsiBufLen * 2 + 2);
	u32 dwUnicodeBufLen = ansi_str_to_unicode16(p, (u16*)pUnicodeBuf);
	setSerialData(id, pUnicodeBuf, dwUnicodeBufLen * 2);
	free(pUnicodeBuf);
}

void CFlyApp::setUtf8String(u32 id, u8 *p, u32 len)
{
	char *pData = (char*)p;

	u8 szUnicode[256] = {0};
	memset(szUnicode,0,sizeof(szUnicode));

	int nRetLen = utf8_2_ucs2(p, len, szUnicode, sizeof(szUnicode));

	setSerialData(id, szUnicode, nRetLen + 2);
}

void CFlyApp::setUtf8SerialData(u32 id, u8 *p, u32 len)
{
	setUtf8String(id, p, len);

	/*u32 dwAnsiBufLen = strlen((char*)p);
	u8 *pUnicodeBuf = (u8*)malloc(dwAnsiBufLen * 2 + 2);
	memset(pUnicodeBuf, 0, dwAnsiBufLen * 2 + 2);
	u32 dwUnicodeBufLen = utf8_to_unicode16(p, (unicode16_t*)pUnicodeBuf);
	setSerialData(id, pUnicodeBuf, dwUnicodeBufLen * 2);
	free(pUnicodeBuf);*/
}


void CFlyApp::setCommand(u32 id, u8 *p, u32 len)
{
	makeAndSendMessageToUI (id, UI_CONTROL_TYPE_PARAMSET, p, len);
}

void CFlyApp::setVisible(u32 id, bool b)
{
	u8 szMsg[2] = {0};
	szMsg[1] = (b) ? 0x01 : 0x00;

	setCommand(id, szMsg, sizeof(szMsg));
}

void CFlyApp::setPlayEnable(bool b) 
{
	u8 szMsg[] = {0x62, 0x00};

	szMsg[1] = (b) ? 0x01 : 0x00;

	setCommand(0x00000000, szMsg, sizeof(szMsg));
}

void CFlyApp::setStringById(u32 id, u32 stringId)
{
	u8 szMsg[5] = {0xC0, 0x00, 0x00, 0x00, 0x00};

	szMsg[1] = (u8)(stringId >> 24) & 0xFF;
	szMsg[2] = (u8)(stringId >> 16) & 0xFF;
	szMsg[3] = (u8)(stringId >>  8) & 0xFF;
	szMsg[4] = (u8)(stringId >>  0) & 0xFF;

	setCommand(id, szMsg, sizeof(szMsg));
}

//lhy add 10.31 
void CFlyApp::setMixedExternalAppVoiceState(u8 status)
{
	u8 param[] = {0x70, 0x00};
	param[1] = status;
	setCommand(0x00000000, param, 2);
}



void CFlyApp::setExProgressSinglePos(u32 ctrlId, u8 direct, int pos)//EQ balance
{
	u8 param[6] = {0x72, direct, 0x00,  0x00, 0x00, 0x00};

	param[2] = (u8)(pos >> 24) & 0xff;
	param[3] = (u8)(pos >> 16) & 0xff;
	param[4] = (u8)(pos >>  8) & 0xff;
	param[5] = (u8)(pos >>  0) & 0xff;

	setCommand(ctrlId, param, 6);
}


void CFlyApp::setUpdateUI(bool b)
{
	u8 szMsg[] = {0xFE, 0x00};

	szMsg[1] = (b) ? 0x01 : 0x00;

	setCommand(0x00000000, szMsg, sizeof(szMsg));
}

void CFlyApp::setCtrlEnable(u32 id, bool b)
{
	u8 szMsg[2] = {0x10, 0x00};

	szMsg[1] = (b) ? 0x01 : 0x00;

	setCommand(id, szMsg, sizeof(szMsg));
}

void CFlyApp::makeAndSendMessageToUI(u32 id, u8 ctrlType, u8 *p, u32 len)
{	//LOGD("SEND TO UI");
	//outPutLog(__FUNCTION__, "p", p, len);
#if 1
	appMessage_t *pAppMessage = NULL;
	u8 *szMsg = NULL;

	pAppMessage = &m_stAppMessage;
	szMsg = pAppMessage->messagebuf;

	memset(pAppMessage, 0, sizeof(appMessage_t));

	szMsg[0] = 0xFF;
	szMsg[1] = 0x55;
	szMsg[2] = (u8)(len + 6);
	szMsg[3] = (u8)((id >> 24) & 0xFF);
	szMsg[4] = (u8)((id >> 16) & 0xFF);
	szMsg[5] = (u8)((id >> 8) & 0xFF);
	szMsg[6] = (u8)(id & 0xFF);
	szMsg[7] = ctrlType;
	memcpy(&szMsg[8], p, len);

	pAppMessage->messageLen = (u8)(len + 9);

	sendMessageToApp(pAppMessage);
#endif
}

void CFlyApp::makeAndSendToAgent(u8 id, u8 *inBuf, u32 inLen, u8 *outBuf, u32 outLen)
{
#if 0
	u16 sendLen = inLen + outLen + 2;
	agentMessage_t *pAgentMessage;

	pAgentMessage = &m_stAgentMessage;
	memset(pAgentMessage, 0, sizeof(agentMessage_t));

	pAgentMessage->messagebuf[0] = 0xFF;
	pAgentMessage->messagebuf[1] = 0x55;
	pAgentMessage->messagebuf[2] = (u8) (sendLen & 0x00FF);
	pAgentMessage->messagebuf[3] = (u8)((sendLen & 0xFF00) >> 8);
	pAgentMessage->messagebuf[4] = id;
	memcpy(&pAgentMessage->messagebuf[5], inBuf, inLen);

	pAgentMessage->messageLen = sendLen + 4;//ff 55 lenL lenH id

	sendMessageToAgent(pAgentMessage);
	memcpy(outBuf, &pAgentMessage->messagebuf[5 + inLen], outLen);
#endif
}

int CFlyApp::setTimer(int moduleID, int timeOut, int timerMode)
{
	//return sendSetTimerMessage(moduleID, timeOut, timerMode);
	return 0;
}

int CFlyApp::killTimer(int timerID)
{
	//return sendKillTimerMessage(timerID);
	return 0;
}

int CFlyApp::setPage(int pageId)
{
	//return sendSetPageMessage(pageId);
	return 0;
}

int CFlyApp::setVolume(int type,int value,int flags1)
{
	//return sendSetVolumeMessage(type, value, flags1);
    return 0;
}

const char* CFlyApp::getMouseMessageType(u8 p)
{
	const char *pRet = "INIT_VALUE";

	switch(p)
	{
	case MOUSE_STATUS_DOWN:
		pRet = "DOWN";
		break;
	case MOUSE_STATUS_UP:
		pRet = "UP";
		break;
	case MOUSE_STATUS_TIMER:
		pRet = "TIMER";
		break;
	case MOUSE_STATUS_UNKNOW:
		pRet = "UNKNOW";
		break;
	}

	return pRet;
}

void CFlyApp::clickColorSettingPageCtrlBackGround(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		m_pFlyModule->setGoBackVideoPageTimer();
		break;
	default:
		break;
	}
}

//颜色
void CFlyApp::clickColorSettingPageHueUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
		/*	int t = m_pFlyParam->m_nGlobalHueLevel;
			t = (t + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL) % (FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL);
			m_pFlyParam->m_nGlobalHueLevel = t;

			m_pFlyModule->setHueLevel(t);

            setAnalogData(CONTROLID_DVD_VIDEO_SET_COLOUR_GAUGE, t);*/
			m_pFlyModule->setToAudioVideoVideoDisplaySetting(0x03);
		}
		break;
	default:
		break;
	}

	m_pFlyModule->setGoBackVideoPageTimer();
}

void CFlyApp::clickColorSettingPageHueDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
            /*  
			int t = m_pFlyParam->m_nGlobalHueLevel;
			t = (t + FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL - FLY_VIDEO_SETTING_ONE_STEP_INTERVAL) % 
				(FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL);
			m_pFlyParam->m_nGlobalHueLevel = t;

			m_pFlyModule->setHueLevel(t);
 

            setAnalogData(CONTROLID_DVD_VIDEO_SET_COLOUR_GAUGE, t);
            */
			m_pFlyModule->setToAudioVideoVideoDisplaySetting(0x04);

		}
		break;
	default:
		break;
	}

	m_pFlyModule->setGoBackVideoPageTimer();
}

//饱和度
void CFlyApp::clickColorSettingPageSaturationUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
            /*  
			int t = m_pFlyParam->m_nGlobalSaturationLevel;
			t = (t + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL) % (FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL);
			m_pFlyParam->m_nGlobalSaturationLevel = t;

			m_pFlyModule->setSaturation(t);

            setAnalogData(CONTROLID_DVD_VIDEO_SET_CHROMINANCE_GAUGE, t);
            */
			m_pFlyModule->setToAudioVideoVideoDisplaySetting(0x01);

		}
		break;
	default:
		break;
	}

	m_pFlyModule->setGoBackVideoPageTimer();
}

void CFlyApp::clickColorSettingPageSaturationDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
            /*  
			int t = m_pFlyParam->m_nGlobalSaturationLevel;
			t = (t + FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL - FLY_VIDEO_SETTING_ONE_STEP_INTERVAL) % 
				(FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL);
			m_pFlyParam->m_nGlobalSaturationLevel = t;

			m_pFlyModule->setSaturation(t);

            setAnalogData(CONTROLID_DVD_VIDEO_SET_CHROMINANCE_GAUGE, t);
*/
			m_pFlyModule->setToAudioVideoVideoDisplaySetting(0x02);
		}
		break;
	default:
		break;
	}

	m_pFlyModule->setGoBackVideoPageTimer();
}

//对比度
void CFlyApp::clickColorSettingPageContrastUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
            /*  
			int t = m_pFlyParam->m_nGlobalContrastLevel;
			t = (t + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL) % (FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL);
			m_pFlyParam->m_nGlobalContrastLevel = t;

			m_pFlyModule->setContrastLevel(t);

            setAnalogData(CONTROLID_DVD_VIDEO_SET_CONTRAST_GAUGE, t);

*/
			m_pFlyModule->setToAudioVideoVideoDisplaySetting(0x05);
		}
		break;
	default:
		break;
	}

	m_pFlyModule->setGoBackVideoPageTimer();
}

void CFlyApp::clickColorSettingPageContrastDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
            /*  
			int t = m_pFlyParam->m_nGlobalContrastLevel;
			t = (t + FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL - FLY_VIDEO_SETTING_ONE_STEP_INTERVAL) % 
				(FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL);
			m_pFlyParam->m_nGlobalContrastLevel = t;

			m_pFlyModule->setContrastLevel(t);

            setAnalogData(CONTROLID_DVD_VIDEO_SET_CONTRAST_GAUGE, t);
*/
			m_pFlyModule->setToAudioVideoVideoDisplaySetting(0x06);
		}
		break;
	default:
		break;
	}

	m_pFlyModule->setGoBackVideoPageTimer();
}

//亮度
void CFlyApp::clickColorSettingPageBrightnessUp(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
            /*  
			int t = m_pFlyParam->m_nGlobalBrightnessLevel;
			t = (t + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL) % (FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL);
			m_pFlyParam->m_nGlobalBrightnessLevel = t;

		//	m_pFlyModule->setBrightnessLevel(t);
            setAnalogData(CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_GAUGE, t);
*/
			m_pFlyModule->setToAudioVideoVideoDisplaySetting(0x07);
		}
		break;
	default:
		break;
	}

	m_pFlyModule->setGoBackVideoPageTimer();
}

void CFlyApp::clickColorSettingPageBrightnessDown(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
	case MOUSE_STATUS_TIMER:
		{
            /*  
			int t = m_pFlyParam->m_nGlobalBrightnessLevel;
			t = (t + FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL - FLY_VIDEO_SETTING_ONE_STEP_INTERVAL) % 
				(FLY_VIDEO_SETTING_MAX_VALUE + FLY_VIDEO_SETTING_ONE_STEP_INTERVAL);
			m_pFlyParam->m_nGlobalBrightnessLevel = t;

			m_pFlyModule->setBrightnessLevel(t);

            setAnalogData(CONTROLID_DVD_VIDEO_SET_BRIGHTNESS_GAUGE, t);
*/
			m_pFlyModule->setToAudioVideoVideoDisplaySetting(0x08);
		}
		break;
	default:
		break;
	}

	m_pFlyModule->setGoBackVideoPageTimer();
}
