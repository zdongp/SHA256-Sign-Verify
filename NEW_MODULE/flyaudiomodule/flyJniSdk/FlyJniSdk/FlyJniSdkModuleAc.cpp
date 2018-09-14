#include "FlyJniSdkModuleAc.h"

CFlyJniSdkModuleAc::CFlyJniSdkModuleAc(void)
{
}

CFlyJniSdkModuleAc::~CFlyJniSdkModuleAc(void)
{
}
void CFlyJniSdkModuleAc::sendToAppAcStatusInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x00;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToFlyJniSdkService(MODULE_SDK_AC, szMsg,len+1);
}

void CFlyJniSdkModuleAc::getAcMessage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			//sendToAppAcStatusInfo(p+1, len-1);
		break;
		default:break;
	}
}

void CFlyJniSdkModuleAc::analyseAcAppMessageType(u8 *p, u8 len)
{
	outPutLog(__FUNCTION__,"p",p,(int)len);
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseAcReturnStatusMassage(p+1, len - 1);
			break;
		case CONTROL_MESSAGE:
			analyseControlACOperationMassage(p+1, len - 1);
			break;
		default:break;
	}

}
void CFlyJniSdkModuleAc::analyseAcReturnStatusMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			if(p[1] == 0x01)
			{
				setToAcGetCurAcInfo();
			}
			break;
		default:break;
	}
}

void CFlyJniSdkModuleAc::analyseControlACOperationMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x01:
			sendToAcJumpAcPage(p[1]);
			break;
		case 0x02:
			sendToAcSetAcSwitch(p[1]);
			break;
		case 0x03:
			sendToAcSetAcWindSpeed(p + 1,len - 1);	
			break;
		case 0x04:
			sendToAcSetAcSyncSwitch(p[1]);
			break;
		case 0x05:
			sendToAcSetAcCycleModel(p[1]);
			break;
		case 0x06:
			sendToAcSetAcTemp(p + 1,len - 1);
			break;
		case 0x07:
			sendToAcSetAcWindowHeat(p + 1,len - 1);
			break;
		case 0x08:
			sendToAcSetAcWindModel(p + 1,len - 1);
			break;
		case 0x09:
			sendToAcSetAcAorCModel(p + 1,len - 1);
			break;
		case 0x0a:
			sendToAcSetAcSeatHeatSwitch(p + 1,len - 1);
			break;
		case 0x0b:
			sendToAcSetAcAUTOSwitch(p + 1,len - 1);
			break;
		case 0x0c:
			sendToAcSetAcMaxAorCModel(p + 1,len - 1);
			break;
		case 0x0d:
			sendToAcSetAcMaxWindowHeat(p + 1,len - 1);
			break;
		case 0x0e:
			sendToAcSetAcSetAcTempAddOrRed(p + 1,len - 1);
			break;
		case 0x0f:
			sendToAcSetAcSetAcWindSpeedAddOrRed(p + 1,len - 1);
			break;
		default:break;
	}
}

/********************send To Ac****************************/
void CFlyJniSdkModuleAc::setToAcGetCurAcInfo()
{
	setToAcGetCurAcSwitch();
	setToAcGetCurTemp();
	setToAcGetCurWSpeed(); //W:wind
	setToAcGetCurWMode();//W:wind
	setToAcGetCurLoopMode();
	setToAcGetCurAorCSwitch();
	setToAcGetCurMaxAorCSwitch();
	setToAcGetCurAutoSwitch();
	setToAcGetCurSYNCSwitch();
	setToAcGetCurFGlassMistRemoval();
	setToAcGetCurRGlassMistRemoval();
	setToAcGetCurHeatSeatStatus();
	setToAcGetCurHeatSeatGrade();
}


/********************send To Ac get Status****************************/
void CFlyJniSdkModuleAc::setToAcGetCurAcSwitch()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x00};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurTemp()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x01};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurWSpeed() //W:wind
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x02};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurWMode()//W:wind
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x03};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurLoopMode()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x04};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurAorCSwitch()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x05};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurMaxAorCSwitch()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x06};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurAutoSwitch()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x07};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurSYNCSwitch()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x08};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurFGlassMistRemoval()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x09};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurRGlassMistRemoval()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x0A};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
void CFlyJniSdkModuleAc::setToAcGetCurHeatSeatStatus()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x0B};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}

void CFlyJniSdkModuleAc::setToAcGetCurHeatSeatGrade()
{
	u8 buf[2] = {RESPONE_CHANGE_STATE,0x0C};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,2);
}
/***************************setToAcControl************************************************/
void CFlyJniSdkModuleAc::sendToAcJumpAcPage(u8 param)
{
	u8 buf[3] = {CONTROL_MESSAGE,0x00,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,3);
}

void CFlyJniSdkModuleAc::sendToAcSetAcSwitch(u8 param)
{
	u8 buf[3] = {CONTROL_MESSAGE,0x02,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,3);
}

void CFlyJniSdkModuleAc::sendToAcSetAcWindSpeed(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x03;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}

void CFlyJniSdkModuleAc::sendToAcSetAcSyncSwitch(u8 param)
{
	u8 buf[3] = {CONTROL_MESSAGE,0x04,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,3);
}

void CFlyJniSdkModuleAc::sendToAcSetAcCycleModel(u8 param)
{
	u8 buf[3] = {CONTROL_MESSAGE,0x05,param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,3);
}

void CFlyJniSdkModuleAc::sendToAcSetAcTemp(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x06;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}

void CFlyJniSdkModuleAc::sendToAcSetAcWindowHeat(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x07;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}

void CFlyJniSdkModuleAc::sendToAcSetAcWindModel(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x08;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}

void CFlyJniSdkModuleAc::sendToAcSetAcAorCModel(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x09;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}

void CFlyJniSdkModuleAc::sendToAcSetAcSeatHeatSwitch(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x0a;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}

void CFlyJniSdkModuleAc::sendToAcSetAcAUTOSwitch(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x0b;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}
void CFlyJniSdkModuleAc::sendToAcSetAcMaxAorCModel(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x0c;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}
void CFlyJniSdkModuleAc::sendToAcSetAcMaxWindowHeat(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x0d;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}
void CFlyJniSdkModuleAc::sendToAcSetAcSetAcTempAddOrRed(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x0e;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}

void CFlyJniSdkModuleAc::sendToAcSetAcSetAcWindSpeedAddOrRed(u8 *p,u8 len)
{
	u8 buf[16] = {0};
	buf[0] = CONTROL_MESSAGE;
	buf[1] = 0x0f;
	memcpy(buf+2,p,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AC,buf,len+2);
}
/********************send To App****************************/
