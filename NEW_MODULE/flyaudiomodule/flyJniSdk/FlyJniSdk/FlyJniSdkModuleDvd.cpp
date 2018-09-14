#include "FlyJniSdkModuleDvd.h"


CFlyJniSdkModuleDvd::CFlyJniSdkModuleDvd(void)
{

}
CFlyJniSdkModuleDvd::~CFlyJniSdkModuleDvd(void)
{

}

void CFlyJniSdkModuleDvd::setToDvdPlay(u8 p)
{
	LOGD("%s] p:%d",__FUNCTION__,p);
	u8 buf[2] = {0};
	buf[0] = 0x00;
	buf[1] = p;
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_DVD,buf,2);
}

void CFlyJniSdkModuleDvd::setToDvdPause(u8 p)
{
	LOGD("%s] p:%d",__FUNCTION__,p);
	u8 buf[2] = {0};
	buf[0] = 0x01;
	buf[1] = p;
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_DVD,buf,2);
}

void CFlyJniSdkModuleDvd::setToDvdNext(u8 p)
{
	LOGD("%s] p:%d",__FUNCTION__,p);
	u8 buf[2] = {0};
	buf[0] = 0x02;
	buf[1] = p;
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_DVD,buf,2);
}

void CFlyJniSdkModuleDvd::setToDvdLast(u8 p)
{
	LOGD("%s] p:%d",__FUNCTION__,p);
	u8 buf[2] = {0};
	buf[0] = 0x03;
	buf[1] = p;
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_DVD,buf,2);
}

void CFlyJniSdkModuleDvd::getAppCtrlMessage(u8 *p, u8 len)
{
	LOGD("[%s] Module_dvd p[0]:%x", __FUNCTION__,p[0]);
	switch(p[0])
	{
		case 0x01://setPlayStatus
			CtrlDvdPalyStatus(p[1]);
			break;
		default:
			break;
	}
}

void CFlyJniSdkModuleDvd::CtrlDvdPalyStatus(u8 p)
{
	switch(p)
	{
		case 0x02:
			setToDvdPlay(p);
			break;
		case 0x03:
			setToDvdPause(p);
			break;
		case 0x05:
			setToDvdNext(p);
			break;
		case 0x06:
			setToDvdLast(p);
			break;
		default:
			break;
	}
}

void CFlyJniSdkModuleDvd::getDvdMessage(u8 *p, u8 len)
{

   LOGD("Enter founction getDvdMessage");

	switch( p[0])
	{
        case 0x00:
			onDvdPlayStatus(p[1]);
			break;	
		case 0x01:
			onDvdTitleAndTrack(&p[1],len-1);
			break;	
		case 0x02:
			onDvdCurrentTime(&p[1],len-1);
			break;	  
	    case 0x03:
			onDvdDvdDiscAndFileType(&p[1],len-1);
			break;	  
	    case 0x04:
		  	onDvdDevState(p[1]);
			break;  
	}
}
void CFlyJniSdkModuleDvd::onDvdPlayStatus(u8 p)
{
    LOGD("[onDvdPlayStatus] get a message %d from Dvd!",p);
	u8 szMsg[2] = {0x01, p};
	setToFlyJniSdkService(MODULE_ID_DVD, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleDvd::onDvdTitleAndTrack(u8 *p,u8 len)
{
    u8 szMsg[5] = {0x00};
	szMsg[0] = 0x04;
	memcpy(szMsg + 1, p, len); 
    LOGD("[onDvdTitleAndTrack], Title %d  Track %d",p[0],p[2]);
	setToFlyJniSdkService(MODULE_ID_DVD, szMsg, len + 1);
}


void CFlyJniSdkModuleDvd::onDvdCurrentTime(u8 *p,u8 len)
{
    u8 szMsg[4] = {0x00};
	szMsg[0] = 0x06;
	memcpy(szMsg + 1, p, len); 
    LOGD("[onDvdCurrentTime], hour %d ,min %d,sec %d",p[0],p[1],p[2]);
	setToFlyJniSdkService(MODULE_ID_DVD, szMsg, len + 1);
}
void CFlyJniSdkModuleDvd::onDvdDvdDiscAndFileType(u8 *p,u8 len)
{
    u8 szMsg[3] = {0x00};
	szMsg[0] = 0x02;
	memcpy(szMsg + 1, p, len); 
    LOGD("[onDvdDvdDiscAndFileType], discType %d ,fileType %d",p[0],p[1]);
	setToFlyJniSdkService(MODULE_ID_DVD, szMsg, len + 1);
}

void CFlyJniSdkModuleDvd::onDvdDevState(u8 p)
{
    LOGD("[onDvdDevState] get a message %d from Dvd!",p);
	u8 szMsg[2] = {0x09, p};
	setToFlyJniSdkService(MODULE_ID_DVD, szMsg, sizeof(szMsg));
}
		