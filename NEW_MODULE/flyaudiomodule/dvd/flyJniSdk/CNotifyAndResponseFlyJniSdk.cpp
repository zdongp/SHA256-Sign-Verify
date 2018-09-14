//moupeng 2015/7/21
#include "CNotifyAndResponseFlyJniSdk.h"
#include "appResponseFunction.h"

CNotifyAndResponseFlyJniSdk:: CNotifyAndResponseFlyJniSdk()
{

}

CNotifyAndResponseFlyJniSdk:: ~CNotifyAndResponseFlyJniSdk()
{

}
void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkPlayState(char cState)
{
       u8 buf[] = {0x00,0x00};
	memcpy(&buf[1],&cState,1);
	LOGD("[%s],cState:%d",__FUNCTION__,cState);
	
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_FLYJNISDK,buf,2);       
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkTitleAndTrack(unsigned short title,unsigned short track)
{
	u8 buf[5]={0x00};
	buf[0]=0x01;
	buf[1]=(u8)((title>>8)&0xff);
	buf[2]=(u8)(title&0xff);
	buf[3]=(u8)((track>>8)&0xff);
	buf[4]=(u8)(track&0xff);
	LOGD("[%s], title:%d,track:%d",__FUNCTION__,title, track);
	
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_FLYJNISDK,buf,5);    
}


void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkCurrentTime(unsigned char hour,unsigned char minute,unsigned char second)
{
	u8 buf[4]={0x00};
	buf[0]=0x02;
	buf[1]=hour;
	buf[2]=minute;
	buf[3]=second;
	LOGD("[%s] CurTimes:%d:%d:%d",__FUNCTION__,hour,minute,second);
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_FLYJNISDK,buf,4);    
}

void  CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkDvdDiscAndFileType(unsigned char discType,unsigned char fileType)
{
       u8 buf[3]={0x00};
	buf[0]=0x03;
	buf[1]=discType;
	buf[2]=fileType;
	LOGD("[%s], discType:%d ,fileType:%d",__FUNCTION__,discType, fileType);
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_FLYJNISDK,buf,3);    
}

 void  CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkDevState(unsigned char devState)
 {
    u8 buf[] = {0x00,0x00};
	buf[0]=0x04;
	buf[1]=devState;
	
	LOGD("[%s],cState:%d",__FUNCTION__,devState);
	
	makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_FLYJNISDK,buf,2);       
 }


 void  CNotifyAndResponseFlyJniSdk::analyseFlyJniSdkMessage(unsigned char *p,int len)
  {
  	LOGD("[%s] p[0]:%d",__FUNCTION__,p[0]);
  	switch(p[0])
  	{
  		case 0:
		case 1:
			appToDvd_MainPlayPause_MouseUp();
			break;
		case 2:
			appToDvd_MainPrev_MouseUp();
			break;
		case 3:
			appToDvd_MainNext_MouseUp();
			break;
  	}
  }

