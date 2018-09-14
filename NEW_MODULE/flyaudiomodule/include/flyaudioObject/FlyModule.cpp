/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#include "FlyModule.h"

extern CFlyModule *g_pFlyModule;
extern void sendMessageToModule(moduleMessage_t *pModuleMsg);
extern void sendGetOtherModuleParam(moduleParam_t *pModuleParam);

CFlyModule::CFlyModule(void)
{
}

CFlyModule::~CFlyModule(void)
{
}

void CFlyModule::deInit(void){}//类析化

void CFlyModule::moduleParameterInit(void)
{
	LOGD("[%s]", __FUNCTION__);

	m_pFlyParam->initFatherParam();
	m_pFlyParam->init();
	m_pFlyParam->readParameter();
}

void CFlyModule::moduleParameterReInit(void)
{
	LOGD("[%s]", __FUNCTION__);

	m_pFlyParam->init();
	m_pFlyParam->readParameter();
}
moduleid_t CFlyModule::locale_module_mid(void){return 0;}//得到本模块 ID
void CFlyModule::getMyModuleParam(char id, u8 *p, u8 *pLen)
{
	//LOGD("[%s] id = [0x%x]", __FUNCTION__, id);

	switch((u8)id)
	{
	default:
		break;
	}
}

int CFlyModule::analyseFlyNativeServerMessage(char *p, u8 len)
{
	u8 cmd = (u8)p[0];
	u8 p1 = (u8)p[1];
LOGD("zwp [%s],p[0]=0x%x",__FUNCTION__,p[0]);
	switch(cmd)
	{
	case 0x1D:
		{
			if(p1 == 0)
			{
				getStandbyOn();
			}
			else if(p1 == 1)
			{
				getStandbyOff();
			}
		}
		break;
	case 0x2C:
		switch(p1)
		{
		case 0x00:// acc off
			getAccOff();
			break;
		case 0x01:// reset
			getReset();
			break;
		case 0x02:// reset factory setting
			getResetFactorySetting();
			break;
		}
		break;
	case 0x2D:// acc on
		getAccOn();
		break;
	/*case 0x3D:
		getWakeUp();
		break;*/
	case 0xFD:// system code start init module
		getSystemCodeStartInitModule();
		break;
	case 0xFE:// system code start init module finish
		getSystemCodeStartInitModuleFinish();
		break;
	}

	return 0;
}

void CFlyModule::analyseTimerHandleMessage(u8 *p, u8 len)
{
	timer_t tId = (timer_t)0xFFFFFF;
	memcpy(&tId,p+3,sizeof(timer_t));

	nativeTimerHandler(tId);
}

void CFlyModule::analyseOtherModuleMessage(moduleid_t id, u8 *p, u8 len)//其它模块数据进来
{
	switch(id)
	{
	case MODULE_ID_AUDIOVIDEO:
		getAudioVideoMessage(p, len);
		break;
	case MODULE_ID_SYSTEM:
		getSystemMessage(p, len);
		break;
	case MODULE_ID_KEY:
		getKeyMessage(p, len);
		break;
	case MODULE_ID_RADIO:
		getRadioMessage(p, len);
		break;
	case MODULE_ID_DVD:
		getDvdMessage(p, len);
		break;
	case MODULE_ID_TPMS:
		getTpmsMessage(p, len);
		break;
	case MODULE_ID_BACK:
		getBackCarMessage(p, len);
		break;
	case MODULE_ID_TV:
		getTvMessage(p, len);
		break;
	case MODULE_ID_BT:
		getBtMessage(p, len);
		break;
	case MODULE_ID_AC:
		getAcMessage(p, len);
		break;
	case MODULE_ID_GPS:
		getGpsMessage(p, len);
		break;
	case MODULE_ID_EXTCAR:
		getExtcarMessage(p, len);
		break;
	case MODULE_ID_SYNC:
		getSyncMessage(p, len);
		break;
	case MODULE_ID_DVR:
		getDvrMessage(p, len);
		break;
	case MODULE_ID_IPOD:
		getIpodMessage(p, len);
		break;
	case MODULE_ID_MEDIA:
		getMediaMessage(p, len);
		break;
	case MODULE_ID_BLCD:
		getBlcdMessage(p, len);
		break;
	case MODULE_ID_AUX:
		getAuxMessage(p, len);
		break;
	case MODULE_ID_AUXSCREEN:
		getAuxScreenMessage(p, len);
		break;
	case MODULE_ID_OSD:
		getOsdMessage(p, len);
		break;
	case MODULE_ID_EXTERNALCTRL:
		getExternalctrlMessage(p, len);
		break;
	case MODULE_ID_TIMER:
		getTimerMessage(p, len);
		break;
	case MODULE_ID_CENTER:
		getCenterMessage(p, len);
		break;
	case MODULE_ID_SERVICE:
		getServiceMessage(p, len);
		break;
	case MODULE_ID_AUTOMATE:
	    getAutoMateMessage(p, len);
	    break;
	case MODULE_ID_FLYJNISDK:
	    getFlyJniSdkMessage(p, len);
	    break;
	default:
		break;
	}
}

void CFlyModule::getAutoMateMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getAudioVideoMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getSystemMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getKeyMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getRadioMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getDvdMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getTpmsMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getBackCarMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getTvMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getBtMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getAcMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getGpsMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getExtcarMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getSyncMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getDvrMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getIpodMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getMediaMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getBlcdMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getAuxMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getAuxScreenMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getOsdMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getExternalctrlMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getTimerMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getCenterMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getServiceMessage(u8 *p, u8 len)
{ 
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::getFlyJniSdkMessage(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__, "p", p, len);
}

void CFlyModule::timerHandleProc(int timerId)//java ui 定时器处理函数
{
	LOGD("[%s] timerId = [%d]", __FUNCTION__, timerId);
}

void CFlyModule::pageIdUiHaveGone(int pageId)
{
	LOGD("[%s] pageId = [%d]", __FUNCTION__, pageId);
}

//启动复位重要接口
void CFlyModule::getSystemCodeStartInitModule()
{
	LOGD("[%s]", __FUNCTION__);

	//m_pFlyParam->init() 在 moduleParameterInit 和 moduleParameterReInit 调用. 最先到达的初始化消息
	m_pFlyModule->init();
	m_pFlyApp->init();
	m_pFlyHal->init();
}

void CFlyModule::getSystemCodeStartInitModuleFinish()//冷启动起来初始化所有 module 结束
{
	LOGD("[%s]", __FUNCTION__);
}

void CFlyModule::getAccOn()
{
	LOGD("[%s]", __FUNCTION__);
}

void CFlyModule::getAccOff()
{
	LOGD("[%s]", __FUNCTION__);
}//收到 acc off 消息

void CFlyModule::getStandbyOn()
{
	LOGD("[%s]", __FUNCTION__);
}

void CFlyModule::getStandbyOff()
{
	LOGD("[%s]", __FUNCTION__);
}

void CFlyModule::getWakeUp()
{
	LOGD("zwp[%s]", __FUNCTION__);
}

void CFlyModule::getReset()
{
	LOGD("[%s]", __FUNCTION__);

	m_pFlyParam->saveParameter();
}

void CFlyModule::getResetFactorySetting()
{
	LOGD("[%s]", __FUNCTION__);

	m_pFlyParam->init();
	m_pFlyParam->saveParameter();
}

void CFlyModule::setPage(u16 id)
{
	u8 szMsg[] = {0x82, 0x00, 0x00};
	memcpy(szMsg + 1, &id, 2);
	makeAndSendMessageToModule(locale_module_mid(),  MODULE_ID_SYSTEM,  szMsg, sizeof(szMsg));
}

void CFlyModule::setPrePage(void)
{
	u8 szMsg[] = {0x83, 0x00};
	makeAndSendMessageToModule(locale_module_mid(),  MODULE_ID_SYSTEM,  szMsg, sizeof(szMsg));
}

void CFlyModule::setNextModule(void)
{
	u8 szMsg[] = {0x81, locale_module_mid()};
	makeAndSendMessageToModule(locale_module_mid(),  MODULE_ID_SYSTEM,  szMsg, sizeof(szMsg));
}

//定时器
void CFlyModule::initNativeTimer(void)
{
	////setNativeTimerHandler(CFlyModule::nativeTimerHandler);
}

void CFlyModule::setNativeTimerHandler(timer_handler_function func)
{
	u8 szMsg[] = {0x10, 0x00, 0x00, 0x00, 0x00};

	//szMsg[1] = ((unsigned int)func >> 24) & 0xFF;
	//szMsg[2] = ((unsigned int)func >> 16) & 0xFF;
	//szMsg[3] = ((unsigned int)func >> 8) & 0xFF;
	//szMsg[4] = (unsigned int)func & 0xFF;

	szMsg[1] = ((u64)func >> 24) & 0xFF;
    szMsg[2] = ((u64)func >> 16) & 0xFF;
    szMsg[3] = ((u64)func >> 8) & 0xFF;
    szMsg[4] = (u64)func & 0xFF;

	m_pFlyModule->makeAndSendMessageToModule(locale_module_mid(), MODULE_ID_TIMER, szMsg, sizeof(szMsg));
}

int CFlyModule::setNativeTimer(int time, int mode, int timerId)
{
	u8 szMsg[10];

	szMsg[0] = 0x20;
	szMsg[1] = (timerId >> 24) & 0xFF;
	szMsg[2] = (timerId >> 16) & 0xFF;
	szMsg[3] = (timerId >> 8) & 0xFF;
	szMsg[4] = timerId & 0xFF;

	szMsg[5] = (time >> 24) & 0xFF;
	szMsg[6] = (time >> 16) & 0xFF;
	szMsg[7] = (time >> 8) & 0xFF;
	szMsg[8] = time & 0xFF;

	szMsg[9] = (u8)mode;

	m_pFlyModule->makeAndSendMessageToModule(locale_module_mid(), MODULE_ID_TIMER, szMsg, sizeof(szMsg));

	return 0;
}

int CFlyModule::deleteNativeTimer(int timerId)
{
	u8 szMsg[5];

	szMsg[0] = 0x30;
	szMsg[1] = (timerId >> 24) & 0xFF;
	szMsg[2] = (timerId >> 16) & 0xFF;
	szMsg[3] = (timerId >> 8) & 0xFF;
	szMsg[4] = timerId & 0xFF;

	m_pFlyModule->makeAndSendMessageToModule(locale_module_mid(), MODULE_ID_TIMER, szMsg, sizeof(szMsg));

	return 0;
}

int CFlyModule::nativeTimerHandler(timer_t timerId)
{
	
	LOGD("[%s] timerId = [%d]", __FUNCTION__, timerId);
	g_pFlyModule->nativeTimerHandlerProcess(timerId);

	return 0;
}

int CFlyModule::nativeTimerHandlerProcess(timer_t timerId)
{
	LOGD("[%s] timerId = [%d]", __FUNCTION__, timerId);
	return 0;
}

//外部调用
void CFlyModule::outCallBack_readParameter(void)
{
	m_pFlyParam->readParameter();
}

void CFlyModule::outCallBack_saveParameter(void)
{
	m_pFlyParam->saveParameter();
}

moduleid_t CFlyModule::outCallBack_locale_module_mid(void)
{
	return m_pFlyModule->locale_module_mid();
}

void CFlyModule::outCallBack_analyseHalMessage(halid_t hid, u8 cmd, u8 *p, u8 len)
{
	m_pFlyHal->analyseHalMessage(hid, cmd, p, len);
}

void CFlyModule::outCallBack_analyseAppMessage(u8 *p, u8 len)
{
	m_pFlyApp->analyseAppMessage(p, len);
}

void CFlyModule::outCallBack_analyseOtherModuleMessage(moduleid_t id, u8 *p, u8 len)
{
	m_pFlyModule->analyseOtherModuleMessage(id, p, len);
}

void CFlyModule::outCallBack_analyseTimerHandleMessage(u8 *p, u8 len)
{
	m_pFlyModule->analyseTimerHandleMessage(p, len);
}

void CFlyModule::outCallBack_getMyModuleParam(char id, u8 *p, u8 *pLen)
{
	m_pFlyModule->getMyModuleParam(id, p, pLen);
}

void CFlyModule::outCallBack_moduleParameterInit(void)
{
	m_pFlyModule->moduleParameterInit();
}

void CFlyModule::outCallBack_moduleParameterReInit(void)
{
	m_pFlyModule->moduleParameterReInit();
}

int CFlyModule::outCallBack_analyseFlyNativeServerMessage(char *p, int len)
{
	return m_pFlyModule->analyseFlyNativeServerMessage(p, len);
}

void CFlyModule::outCallBack_analyseAgentMessage(moduleid_t id, u8 *p, u8 len)
{
	m_pFlyApp->analyseAgentMessage(id, p, len);
}

void CFlyModule::outCallBack_timerHandleProc(int timerId)
{
	m_pFlyModule->timerHandleProc(timerId);
}

void CFlyModule::outCallBack_pageIdUiHaveGone(int pageId)
{
	m_pFlyModule->pageIdUiHaveGone(pageId);
}

void CFlyModule::makeAndSendMessageToModule(u8 id, u8 arrivedModuleId, u8 *p, u8 len)
{
	u8 *pMsg = NULL;
	moduleMessage_t *pModuleMessage = NULL;

	pModuleMessage = &m_stModuleMessage;
	memset(pModuleMessage, 0, sizeof(moduleMessage_t));

	pMsg = pModuleMessage->messagebuf;
	pModuleMessage->sendModuleID = id;
	pModuleMessage->arrivedModuleID = arrivedModuleId;

	memcpy(pMsg, p, len);
	pModuleMessage->messageLen = len;

	sendMessageToModule(pModuleMessage);
}

void CFlyModule::getOtherModuleParam(U8 moduleId, U8 id, u8 *p, u8 *pLen)
{
	moduleParam_t *pModuleParam = NULL;

	pModuleParam = &m_stModuleParam;
	memset(pModuleParam, 0, sizeof(moduleParam_t));

	pModuleParam->moduleID = moduleId;
	pModuleParam->paramID = id;

	sendGetOtherModuleParam(pModuleParam);

	*pLen = pModuleParam->paramLen;
	memcpy(p, pModuleParam->parambuf, *pLen);
}

u16 CFlyModule::getCurPageId(void)
{
	u16 wPageId = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&wPageId, &len);

	LOGD("[%s] id = [0x%x]", __FUNCTION__, wPageId);

	return wPageId;
}
u16 CFlyModule::getPrePageId(void)
{
	u16 pPageId = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, PREV_PAGE, (u8*)&pPageId, &len);

	LOGD("[%s] id = [0x%x]", __FUNCTION__, pPageId);

	return pPageId;
}

u8 CFlyModule::getCurExternalDeviceId(void)
{
	u8 id = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_IS_DVRORTV, (u8*)&id, &len);

	LOGD("[%s] id = [0x%x]", __FUNCTION__, id);

	return id;
}

u16 CFlyModule::getCurAudioVideoChannel(void)
{
	u16 wAudioVideoChannel = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, SOUND_CHANNEL, (u8*)&wAudioVideoChannel, &len);

	LOGD("[%s] wAudioVideoChannel = [0x%x]", __FUNCTION__, wAudioVideoChannel);

	return wAudioVideoChannel;
}

u16 CFlyModule::getLastAudioVideoMediaChannel(void)
{
	u16 wAudioVideoMediaChannel = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, LAST_MEDIA_CHANNEL, (u8*)&wAudioVideoMediaChannel, &len);

	LOGD("[%s] wAudioVideoMediaChannel = [0x%x]", __FUNCTION__, wAudioVideoMediaChannel);

	return wAudioVideoMediaChannel;
}

u16 CFlyModule::getDefaultAudioVideoChannel(void)
{
	u16 wAudioVideoChannel = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_AUDIOVIDEO, DEFAULT_CHANNEL, (u8*)&wAudioVideoChannel, &len);

	LOGD("[%s] wAudioVideoChannel = [0x%x]", __FUNCTION__, wAudioVideoChannel);

	return wAudioVideoChannel;
}

bool CFlyModule::getBackCarStatus(void)
{
	bool bRet = false;
	u8 r = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_BACK, FLY_BACK_CAR_PARAM_BACK_CAR_STATUS, &r, &len);

	bRet = (1 == r) ? true : false;

	LOGD("[%s] bRet = [%s]", __FUNCTION__, bRet ? "Yes" : "No");

	return bRet;
}

bool CFlyModule::getBackCarRadarStatus(void)
{
	bool bRet = false;
	u8 r = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_BACK, FLY_BACK_CAR_PARAM_BACK_CAR_RADAR_STATUS, &r, &len);

	bRet = (1 == r) ? true : false;

	LOGD("[%s] bRet = [%s]", __FUNCTION__, bRet ? "Yes" : "No");

	return bRet;
}

bool CFlyModule::getSystemStandbyStatus(void)
{
	bool bRet = false;
	u8 r = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, SLEEP_STATE, &r, &len);

	bRet = (1 == r) ? true : false;

	LOGD("[%s] bRet = [%s]", __FUNCTION__, bRet ? "Yes" : "No");

	return bRet;
}

u8 CFlyModule::getSystemScreenStatus(void)
{
	u8 r = 0;
	u8 len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, LCD_STATE, &r, &len);

	LOGD("[%s] r = [%d]", __FUNCTION__, r);

	return r;
}


bool CFlyModule::isTpmsSelected(void)
{
	bool bRet = false;
	u8 ret = 0, len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_IS_DVRORTV, &ret, &len);
	bRet = (ret == 1) ? true : false;

	LOGD("[%s] [%s]", __FUNCTION__, bRet ? "tpms is selected!" : "tpms is not selected!");

	return bRet;
}

bool CFlyModule::isAuxSelected(void)
{
	bool bRet = false;
	u8 ret = 0, len = 0;

	getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_IS_AUX, &ret, &len);
	bRet = (ret == 1) ? true : false;

	LOGD("[%s] [%s]", __FUNCTION__, bRet ? "aux is selected!" : "aux is not selected!");

	return bRet;
}

 void CFlyModule::setGoBackVideoPageTimer(void)
 {
  //   return ;
	 if (m_pFlyParam->m_nTimerIdGoBackVideoPage != 0)
	 {
		 m_pFlyApp->killTimer(m_pFlyParam->m_nTimerIdGoBackVideoPage);
		 m_pFlyParam->m_nTimerIdGoBackVideoPage = 0;
	 } 

	 m_pFlyParam->m_nTimerIdGoBackVideoPage = m_pFlyApp->setTimer(locale_module_mid(), TIME_INTERVAL_GO_BACK_VIDEO_PAGE_FROM_OSD_VIDEO, TIMER_TYPE_ONE_TIME);

	 LOGD("[%s] m_nTimerIdGoBackVideoPage1028 = [%d]", __FUNCTION__, m_pFlyParam->m_nTimerIdGoBackVideoPage);
 }

 void CFlyModule::killGoBackVideoPageTimer(void)
 {
	 LOGD("[%s] m_nTimerIdGoBackVideoPage = [%d]", __FUNCTION__, m_pFlyParam->m_nTimerIdGoBackVideoPage);

	 if (m_pFlyParam->m_nTimerIdGoBackVideoPage != 0)
	 {
		 m_pFlyApp->killTimer(m_pFlyParam->m_nTimerIdGoBackVideoPage);
		 m_pFlyParam->m_nTimerIdGoBackVideoPage = 0;
	 } 
 }


 //assist
 const char* CFlyModule::getModuleNameString(u8 p)
 {
	 const static char* szMap[0xFF + 1] = {"can not find it!"};

     szMap[MODULE_ID_AUDIOVIDEO] = "MODULE_ID_AUDIOVIDEO";
     szMap[MODULE_ID_SYSTEM] = "MODULE_ID_SYSTEM";
     szMap[MODULE_ID_KEY] = "MODULE_ID_KEY";
     szMap[MODULE_ID_RADIO] = "MODULE_ID_RADIO";
     szMap[MODULE_ID_DVD] = "MODULE_ID_DVD";
     szMap[MODULE_ID_TPMS] = "MODULE_ID_TPMS";
     szMap[MODULE_ID_BACK] = "MODULE_ID_BACK";
     szMap[MODULE_ID_TV] = "MODULE_ID_TV";
     szMap[MODULE_ID_BT] = "MODULE_ID_BT";
     szMap[MODULE_ID_AC] = "MODULE_ID_AC";
     szMap[MODULE_ID_GPS] = "MODULE_ID_GPS";
     szMap[MODULE_ID_EXTCAR] = "MODULE_ID_EXTCAR";
     szMap[MODULE_ID_SYNC] = "MODULE_ID_SYNC";
     szMap[MODULE_ID_DVR] = "MODULE_ID_DVR";
     szMap[MODULE_ID_IPOD] = "MODULE_ID_IPOD";
     szMap[MODULE_ID_MEDIA] = "MODULE_ID_MEDIA";
     szMap[MODULE_ID_BLCD] = "MODULE_ID_BLCD";
     szMap[MODULE_ID_AUX] = "MODULE_ID_AUX";
     szMap[MODULE_ID_AUXSCREEN] = "MODULE_ID_AUXSCREEN";
     szMap[MODULE_ID_OSD] = "MODULE_ID_OSD";
   /*  szMap[MODULE_ID_NS_HAL] = "MODULE_ID_NS_HAL";*/
     szMap[MODULE_ID_EXTERNALCTRL] = "MODULE_ID_EXTERNALCTRL";
     szMap[MODULE_ID_TIMER] = "MODULE_ID_TIMER";
     szMap[MODULE_ID_CENTER] = "MODULE_ID_CENTER";
     szMap[MODULE_ID_SERVICE] = "MODULE_ID_SERVICE";

	 return szMap[p];
 }


 const char* CFlyModule::getAudioChannelString(u8 p)
 {
	 const char* szMap[0xFF + 1] = {"can not find audiovideo channel."};

	 szMap[1] = "DVD";
	 szMap[2] = "CDC";
	 szMap[3] = "RADIO";
	 szMap[4] = "AvIn";
	 szMap[5] = "iPod";
	 szMap[6] = "TV";
	 szMap[7] = "MP3";
	 szMap[9] = "BT";
	 szMap[0x0C] = "Android";

	 return szMap[p];
 }

 const char* CFlyModule::getAudioVideoChannelString(u8 p)
 {
	 const char* szMap[0xFF + 1] = {"can not find audio channel."};

	 szMap[CHANNEL_DVD_CTRL]   = "DVD_CTRL";
	 szMap[CHANNEL_DVD_VIDEO]  = "DVD_VIDEO";
	 szMap[CHANNEL_CDC_CTRL]   = "CDC_CTRL";
	 szMap[CHANNEL_CDC_VIDEO]  = "CDC_VIDEO";
	 szMap[CHANNEL_RADIO]      = "RADIO_CTRL";
	 szMap[CHANNEL_AUX_CTRL]   = "AUX_CTRL";
	 szMap[CHANNEL_AUX_VIDEO]  = "AUX_VIDEO";
	 szMap[CHANNEL_IPOD_CTRL]  = "IPOD_CTRL";
	 szMap[CHANNEL_IPOD_VIDEO] = "IPOD_VIDEO";
	 szMap[CHANNEL_TV_CTRL]	  = "TV_CTRL";
	 szMap[CHANNEL_TV_VIDEO]   = "TV_VIDEO";
	 szMap[CHANNEL_MP3]		  = "MP3_CTRL";
	 szMap[CHANNEL_SRADIO]     = "SRADIO_CTRL";
	/* szMap[CHANNEL_BT_A2DP]		  = "BT_A2DP";
	 szMap[CHANNEL_BT_RING]		  = "BT_RING";
	 szMap[CHANNEL_BT_CALL]		  = "BT_CALL";*/
	 szMap[CHANNEL_DVR_CTRL]   = "DVR_CTRL";
	 szMap[CHANNEL_DVR_VIDEO]  = "DVR_VIDEO";
	 szMap[CHANNEL_BACK_VIDEO] = "BACK_VIDEO";
	 szMap[CHANNEL_THREECHANNEL] = "THIRD_CTRL";

	 return szMap[p]; 
 }

 int CFlyModule::channel2ModuleId(u8 p)
{
	int nRet = -1;
	int sznMap[0xFF + 1] = {-1};

	sznMap[CHANNEL_DVD_CTRL] = MODULE_ID_DVD;
	sznMap[CHANNEL_DVD_VIDEO] = MODULE_ID_DVD;
	sznMap[CHANNEL_RADIO] = MODULE_ID_RADIO;
	//aux
	bool bIsAuxSelected = isAuxSelected();
	sznMap[CHANNEL_AUX_CTRL] = bIsAuxSelected ? MODULE_ID_AUX : MODULE_ID_SYNC;
	sznMap[CHANNEL_AUX_VIDEO] = bIsAuxSelected ? MODULE_ID_AUX : MODULE_ID_SYNC;
	//
	sznMap[CHANNEL_IPOD_CTRL] = MODULE_ID_IPOD;
	sznMap[CHANNEL_IPOD_VIDEO] = MODULE_ID_IPOD;
	sznMap[CHANNEL_TV_CTRL] = MODULE_ID_TV;
	sznMap[CHANNEL_TV_VIDEO] = MODULE_ID_TV;
	sznMap[CHANNEL_MP3] = MODULE_ID_MEDIA;
	/*sznMap[CHANNEL_BT_A2DP] = MODULE_ID_BT;*/
	sznMap[CHANNEL_DVR_CTRL] = MODULE_ID_DVR;
	sznMap[CHANNEL_DVR_VIDEO] = MODULE_ID_DVR;

	nRet = sznMap[p];

	//LOGD("[%s] p = [0x%x], ret = [0x%x], name = [%s]", __FUNCTION__, p, nRet, getAudioVideoChannelString(nRet));

	return nRet;
}
 
 //MTK 视频色彩设置//////////////////////////////////////////////////////////
 void CFlyModule::setBrightnessLevel(int level)//屏幕亮度
 {
	  LOGD("[%s] level = [%d]", __FUNCTION__, level);

	 u8 szMsg[5] = {0};
	 szMsg[0] = 0x01;
	 memcpy(szMsg + 1, &level, 4);

	 makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
 }

 void CFlyModule::setContrastLevel(int level)//对比度
 {
	  LOGD("[%s] level = [%d]", __FUNCTION__, level);

	 u8 szMsg[5] = {0};
	 szMsg[0] = 0x02;
	 memcpy(szMsg + 1, &level, 4);

	 makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
 }

 void CFlyModule::setBackLightLevel(int level)//背光亮度
 {
	  LOGD("[%s] level = [%d]", __FUNCTION__, level);

	 u8 szMsg[5] = {0};
	 szMsg[0] = 0x03;
	 memcpy(szMsg + 1, &level, 4);

	 makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
 }

 void CFlyModule::setHueLevel(int level)//色彩
 {
	 LOGD("[%s] level = [%d]", __FUNCTION__, level);

	 u8 szMsg[5] = {0};
	 szMsg[0] = 0x04;
	 memcpy(szMsg + 1, &level, 4);

	 makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
 }

 void CFlyModule::setSaturation(int level)//饱和度
 {
	  LOGD("[%s] level = [%d]", __FUNCTION__, level);

	 u8 szMsg[5] = {0};
	 szMsg[0] = 0x05;
	 memcpy(szMsg + 1, &level, 4);

	 makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
 }

void CFlyModule::setToAudioVideoVideoDisplaySetting(u8 p)
{
	u8 szMsg[] = {0x11, p};

	makeAndSendMessageToModule(locale_module_mid(), MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
}
