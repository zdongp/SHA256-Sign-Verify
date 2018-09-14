#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <messageQueue.h>
#include <moduleParamStruct.h>

#include "types_def.h"
#include "hardware.h"
#include "commonFunc.h"

#include <flytypes.h>
#include <flymoduleApi.h>
#include <allconfig.h>
#include <config.h>
#include <flymoduleApi_internal.h>
#include <flyaudiomodule/debug.h>

#include <string.h>

static device_command_t *command_list;


static mod_callback_t *g_spstModCallBack = NULL;
static flymessage_t g_stFlymessage;
static halMessage_t g_stHalMessage;
static agentMessage_t g_stAgentMessage;

//////////////////////////////////////////////////////////////////////////

ptrPrintLog printLog = debugPrintf; // printLog_detail
//ptrPrintLog		printLog = __android_log_print;
//////////////////////////////////////////////////////////////////////////
extern void moduleParameterInit(void);
extern void moduleParameterReInit(void);

extern void readParameter(void);
extern void saveParameter(void);

extern int module_extendInterface(char *p, int len);
extern void analyseAgentMessage(moduleid_t sendModuleId,u8 *p, u8 len);
extern void analyseAppMessage(u8 *p, u8 len);
extern void analyseHalMessage(halid_t hid, u8 cmd, u8 *p, u8 len);
extern void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *p, u8 len);
extern void analyseTimerHandleMessage(u8 *p, u8 len);

extern void getMyModuleParam(char paramId, u8 *p, u8 *paramLen);
extern moduleid_t locale_module_mid(void);

extern void timerHandleProc(int timerId);
extern void pageIdUiHaveGone(int pageId);
//////////////////////////////////////////////////////////////////////////
static void sendMessageToHal(halMessage_t *pHalMsg)
{
//	if (g_spstModCallBack && g_spstModCallBack->setHal)
//	{
//		g_spstModCallBack->setHal(pHalMsg);
//	}

	BYTE msg[256] = {MESSAGETYPE_HAL};

	memcpy(&msg[1], &pHalMsg->messagebuf[3], pHalMsg->messagebuf[2]-1);

	command_set(MODULE_ID_MAIN_SERVICE, msg, pHalMsg->messagebuf[2]);

}

void sendMessageToApp(appMessage_t *pAppMsg)
{
//	if (g_spstModCallBack && g_spstModCallBack->setApp)
//	{
//		g_spstModCallBack->setApp(pAppMsg);
//	}

	BYTE msg[256] = {MESSAGETYPE_APP};

	memcpy(&msg[1], &pAppMsg->messagebuf[3], pAppMsg->messagebuf[2]-1);

	command_set(MODULE_ID_MAIN_SERVICE, msg, pAppMsg->messagebuf[2]);


}

void sendMessageToTimer(moduleMessage_t *pModuleMessage)
{
//	if (g_spstModCallBack && g_spstModCallBack->setTimer)
//	{
//		g_spstModCallBack->setTimer(pModuleMessage);
//	}
	BYTE msg[320] = {MESSAGETYPE_TIMER};

	memcpy(&msg[1], pModuleMessage->messagebuf,pModuleMessage->messageLen);
	command_set(pModuleMessage->arrivedModuleID, msg, 1+pModuleMessage->messageLen);

}


void sendMessageToModule(moduleMessage_t *pModuleMsg)
{

	BYTE msg[320] = {MESSAGETYPE_MODULE, pModuleMsg->sendModuleID};

	memcpy(&msg[2], pModuleMsg->messagebuf,pModuleMsg->messageLen);
	command_set(pModuleMsg->arrivedModuleID, msg, 2+pModuleMsg->messageLen);


//	if (g_spstModCallBack && g_spstModCallBack->setMod)
//	{
//		g_spstModCallBack->setMod(pModuleMsg);
//	}
}

void sendMessageToBroadcast(unsigned char *buffer, int len)
{
	command_set(MODULE_ID_MAIN_SERVICE, buffer, len);
}

void sendGetOtherModuleParam(moduleParam_t *pModuleParam)
{
//	if (g_spstModCallBack && g_spstModCallBack->getMod)
//	{
//		g_spstModCallBack->getMod(pModuleParam);
//	}


	command_get(pModuleParam->moduleID, (unsigned char *)pModuleParam, sizeof(moduleParam_t));



}

void makeAndSendMessageToHal(moduleid_t halId, u8 *p, int len)
{
	u32 sendLen = len + 4 + 1;
	halMessage_t *pHalMessage;

	pHalMessage =  &g_stHalMessage;
	memset(pHalMessage, 0, sizeof(halMessage_t));

	pHalMessage->messagebuf[0] = 0xFF;
	pHalMessage->messagebuf[1] = 0x55;
	pHalMessage->messagebuf[2] = (u8) (len + 1 + 1);
	pHalMessage->messagebuf[3] = (u8)halId;
	memcpy(&pHalMessage->messagebuf[4], p, len);

	pHalMessage->halID = halId;
	pHalMessage->messageLen = (u8) sendLen;

	sendMessageToHal(pHalMessage);
}


void makeAndSendTimerHandleMessage(unsigned char sendModuleId, unsigned char arrivedModuleId, unsigned int index){
	moduleMessage_t ModuleMessage, *pModuleMessage;

	pModuleMessage = (moduleMessage_t*)&ModuleMessage;
	
	memset(pModuleMessage, 0x00, sizeof(moduleMessage_t));

	pModuleMessage->sendModuleID = sendModuleId;
	pModuleMessage->arrivedModuleID = arrivedModuleId;

	pModuleMessage->messagebuf[0] = 0xFF;
	pModuleMessage->messagebuf[1] = 0x55;
	pModuleMessage->messagebuf[2] = (u8) (sizeof(int) + 1);	// Length
	memcpy(&pModuleMessage->messagebuf[3], &index, sizeof(int));

	pModuleMessage->messageLen = pModuleMessage->messagebuf[2]+2;

	sendMessageToTimer(pModuleMessage);
}


static int flymodule_device_setCallBack(const moduleid_t mid, mod_callback_t* mCallBack)
{
	if (mid != locale_module_mid())
		return -1;

	if (g_spstModCallBack)
	{
		g_spstModCallBack->setHal = mCallBack->setHal;
		g_spstModCallBack->setApp = mCallBack->setApp;
		g_spstModCallBack->setMod = mCallBack->setMod;
		g_spstModCallBack->getMod = mCallBack->getMod;
		g_spstModCallBack->setTimer = mCallBack->setTimer;

		readParameter();
	}

	return -1;
}

static void flymodule_device_writeMessage(const flymessage_t *pFlyMsg)
{

	if (!pFlyMsg)
		return;

	flymessage_t *mPFlyMsg = &g_stFlymessage;

	memcpy((void*)mPFlyMsg, (void*)pFlyMsg, sizeof(flymessage_t));

	switch (mPFlyMsg->messageType)
	{
	case MESSAGETYPE_HAL:
		{
			if (mPFlyMsg->messageParam1 != locale_module_mid())
				return;

			if ((mPFlyMsg->messagebuf[0] != 0xFF) || (mPFlyMsg->messagebuf[1] != 0x55))
				return;

			halid_t hid = mPFlyMsg->messageParam2;
			u8 cmd = mPFlyMsg->messagebuf[3];
			u8 *p = &mPFlyMsg->messagebuf[4];
			u8 paramLen = mPFlyMsg->messagebuf[2] - 2;

			analyseHalMessage(hid, cmd, p, paramLen);
		}
		break;
	case MESSAGETYPE_APP:
		{

			if (mPFlyMsg->messageParam1 != locale_module_mid())
				return;

			if ((mPFlyMsg->messagebuf[0] != 0xFF) || (mPFlyMsg->messagebuf[1] != 0x55))
				return;

			analyseAppMessage(&mPFlyMsg->messagebuf[3], mPFlyMsg->messagebuf[2]);
		}
		break;
	case MESSAGETYPE_MODULE:
		{
			if (mPFlyMsg->messageParam2 != locale_module_mid())
				return;

			analyseOtherModuleMessage(mPFlyMsg->messageParam1, mPFlyMsg->messagebuf, mPFlyMsg->messageLen);
		}
		break;
	case MESSAGETYPE_TIMER:
		if (mPFlyMsg->messageParam1 != locale_module_mid())
			return;

		analyseTimerHandleMessage(mPFlyMsg->messagebuf, mPFlyMsg->messageLen);
		break;
	default:
		break;
	}
}

static void flymodule_device_getModuleParam(moduleParam_t *p)
{
	if (p->moduleID != locale_module_mid())
		return;

	getMyModuleParam(p->paramID, p->parambuf, &p->paramLen);
}

static void flymodule_device_init(void)
{
	moduleParameterInit();
}

static void flymodule_device_reInit(void)
{
	moduleParameterReInit();
}

static int flymodule_device_ioctl(char *p, int len)
{
	return module_extendInterface(p, len);
}

static int flymodule_device_LogPermission(int nEnable)
{
	static int nPreEnable = '0';

	if (nPreEnable == nEnable)
		return 0;

	nPreEnable = nEnable;
//	if (nEnable == '1')
//		printLog = debugPrintf;
//	else if (nEnable == '0')
//		printLog = printLog_none;

	return 1;
}

static void flymodule_device_timerHandleProc(int timerId)
{
	timerHandleProc(timerId);
}

static void flymodule_device_pageIdUiHaveGone(int pageId)
{
	pageIdUiHaveGone(pageId);
}

static int flymodule_device_close(struct fa_device_t* device)
{
	struct flymodule_device_t *dev = (struct flymodule_device_t*) device;

	saveParameter();

	if (g_spstModCallBack)
		free(g_spstModCallBack);

	if (dev)
		free(dev);

	return 0;
}

#include "commonFunc.h"


#define		LOCAL_MODULE_ID			CURRENT_MODULE_ID
#define		LOCAL_MODULE_NAME		CURRENT_MODULE_NAME
#define		LOCAL_HMODULE_AUTOHR	"flyaudio"





static int fly_device_get(unsigned char *buf, int len)
{

	DBG2(debugPrintf("so=%s id=%d get\n", LOCAL_MODULE_NAME, LOCAL_MODULE_ID););
	moduleParam_t *p = (moduleParam_t *)buf;

	getMyModuleParam(p->paramID, p->parambuf, &p->paramLen);

    return 0;
}

static int fly_device_set(unsigned char *buf, int len)
{
	DBG2(debugBuf("command_set:", buf, len););

	switch (buf[0])
	{
		case MESSAGETYPE_HAL:
			analyseHalMessage(buf[1], buf[2], &buf[3], len-3);			
			break;
		case MESSAGETYPE_APP:
			analyseAppMessage(&buf[1], len-1);
			break;
		case MESSAGETYPE_MODULE:
			analyseOtherModuleMessage(buf[1], &buf[2], len-2);
			break;
		case MESSAGETYPE_TIMER:
			analyseTimerHandleMessage(&buf[1], len-1);
			break;
		case MESSAGETYPE_INIT:
			readParameter();
			moduleParameterInit();
			break;
		case MESSAGETYPE_IOCTL:
			module_extendInterface((char *)&buf[1], len-1);
			break;
		default:
			break;		
	}

    return 0;
}

static int fly_device_close(struct hw_device_t* device)
{
    return 0;
}

static int flymodule_device_open(const struct hw_module_t* module, const char* id, struct hw_device_t* device)
{
	struct flymodule_device_t *dev;

	int ret = -EFAULT;

//	dev = (struct flymodule_device_t*) malloc(sizeof(struct flymodule_device_t));
//	if (!dev)
//	{
//		LOGE("FlyAudio Module Stub Fail to alloc space!");
//		return ret;
//	}
//
//	memset(dev, 0, sizeof(struct flymodule_device_t));
//	dev->dev.tag = FLYAUDIO_DEVICE_TAG;
//	dev->dev.version = CURRENT_VERSION;
//	dev->dev.module = (struct fa_module_t*) module;
//	dev->dev.close = flymodule_device_close;
//
//	dev->setCallBack = flymodule_device_setCallBack;
//	dev->writeMessage = flymodule_device_writeMessage;
//	dev->getModuleParam = flymodule_device_getModuleParam;
//	dev->init = flymodule_device_init;
//	dev->reInit = flymodule_device_reInit;
//	dev->ioctl = flymodule_device_ioctl;
//	dev->LogPermission = flymodule_device_LogPermission;
//
//	*device = &(dev->dev);
//
//	g_spstModCallBack = (mod_callback_t*) malloc(sizeof(mod_callback_t));
//	memset(g_spstModCallBack, 0, sizeof(mod_callback_t));

	device->tag =  HARDWARE_DEVICE_TAG;
    device->version = 0;
    device->module = (struct hw_module_t*)module;

	device->close = fly_device_close;

	command_list = device->command_list;
	command_register_set(LOCAL_MODULE_ID, fly_device_set);
	command_register_get(LOCAL_MODULE_ID, fly_device_get);

	debugTagSet(TAG);

    debugPrintf("fly_device_open id --> %d name--> %s \n", LOCAL_MODULE_ID, id);


	ret = locale_module_mid();

	return ret;
}

static struct hw_module_methods_t flymodule_methods =
{
	.open = flymodule_device_open
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
	.tag = HARDWARE_MODULE_TAG,
	.version_major = 1,
	.version_minor = 0,
	.id = LOCAL_MODULE_ID,
	.name = LOCAL_MODULE_NAME,
	.author = LOCAL_HMODULE_AUTOHR,
	.methods = &flymodule_methods,

};

