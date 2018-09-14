#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"

void airconditionToModule_NotifySystem_jumpPage(u16 PageId){
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&PageId,2);
     makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_SYSTEM,buf,3);
}

void airconditionToModule_NotifySystem_JumpPrePage(void){
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_SYSTEM,buf,2);
}

void airconditionToModule_NotifySystem_SwitchModule(void)//����AV KEY
{
	unsigned char buff[] =  {0x81,MODULE_ID_AC};
	makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_SYSTEM,buff,2);
}

void airconditionToModule_NotifyOsd_DisplayACTitle()
{
	u8 buf[] = {0x01,0x11};
	makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_OSD,buf,2);
}
void airconditionToModule_NotifyOsd_DisplayOSDACInfor(u16 leftTempValue,u16 rightTempValue,u8 unit,u8 ucSpeed,u8 ucAcState){
	u8 buf[8] = {0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	buf[1] = leftTempValue & 0xFF;
	buf[2] = (leftTempValue & 0xFF00)>>8;
	buf[3] = rightTempValue & 0xFF;
	buf[4] = (rightTempValue & 0xFF00)>>8;
	buf[5] = unit;
	buf[6] = ucSpeed;
	buf[7] = ucAcState;
	makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_OSD,buf,8);
}

void ACToModule_NotifyOsd_DisplayOSDACInfor_Q(u16 leftTempValue,u16 rightTempValue,unsigned char ucSpeed,unsigned char ucAcState){
	u8 buf[] = {0x02, 0x42, 0x00,0x00,0x00,0x00,0x00,0x00};
	buf[2] = (leftTempValue >> 8) & 0xFF;
	buf[3] = leftTempValue & 0xFF;
	buf[4] = (rightTempValue>> 8) & 0xFF;
	buf[5] = rightTempValue & 0xFF;
	buf[6] = ucSpeed;
	buf[7] = ucAcState;
	makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_OSD,buf,8);
}

void sendAcMessageacToOtherModule(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0xf0;
	buf[1] = 0x02;
	memcpy(buf+2,param,len);
	makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_EXTCAR, buf, len+2);
}

void setAcSwitchToHal(u8 param)
{
	u8 buf[3] = {0x00,0x00,param};
	sendAcMessageacToOtherModule(buf,3);
}

void acToHalTempMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x01;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}
void acToHalwindMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x02;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}
void acToHalWindModeMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x03;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}
void acToHalLoopModeMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x04;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}
void acToHalACswitchMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x05;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}
void acToHalAutoSwitchMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x06;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}

void acToHalDualSwitchMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x07;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}

void acToHalMistRemovalMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x08;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}

void acToHalRearWindowHeatingMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x09;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}

void acToHalRearHeatSeatMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x0A;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}

void acToHalAirConditionLockMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x0B;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}

void setAcTemperature(int tempL,int tempR,int min,int max,u8 tag,u8 unit)
{
	u8 buf[256];
	int nTempL = tempL;
	int nTempR = tempR;
	int nMinTemp = min;
	int nMaxTemp = max;
	memset(buf,0,sizeof(buf));
	buf[0] = 0x00;
	memcpy(buf+1,&nMinTemp,2);
	memcpy(buf+3,&nMaxTemp,2);
	memcpy(buf+5,&nTempL,2);
	memcpy(buf+7,&nTempR,2);
	buf[9] = tag;
	buf[10] = unit;
	LOGD("setToHalTemp--L:%d    R:%d",tempL,tempR);
	acToHalTempMessage(buf,11);
}
void setPublicAcTemperature(u8 RorL,u8 param)
{
	u8 buf[3] = {0x01,RorL,param};
	acToHalTempMessage(buf,3);
}

void setAcwindSpeed(u8 param,u8 min,u8 max)
{
	u8 buf[4];
	buf[0] = 0x00;
	buf[1] =  min;
	buf[2] = max;
	buf[3] = param;
	acToHalwindMessage(buf,4);
}
void setpublicAcwindSpeed(u8 param)
{
	u8 buf[2];
	buf[0] = 0x01;
	buf[1] =  param;
	acToHalwindMessage(buf,2);
}

void setAcwindMode(u8 param)
{
	u8 buf[2];
	buf[0] = 0x00;
	buf[1] = param;
	acToHalWindModeMessage(buf,2);
}
void setPublicAcwindMode()
{
	u8 buf[2] = {0x01,0x01};
	acToHalWindModeMessage(buf,2);
}

void setPublicAcwindModeForBody(u8 param)
{
	u8 buf[3] = {0x02,0x00,0x01};
	buf[1] = param; 
	acToHalWindModeMessage(buf,3);
}

void setAcLoopMode(u8 param)
{
	u8 buf[2];
	buf[0] = 0x00;
	buf[1] = param;
	acToHalLoopModeMessage(buf,2);
}

void setAcAorCSwitch(u8 param)
{
	u8 buf[2];
	buf[0] = 0x00;
	buf[1] = param;
	acToHalACswitchMessage(buf,2);
}

void setAcAorCMaxSwitch(u8 param)
{
	u8 buf[2];
	buf[0] = 0x05;
	buf[1] = param;
	acToHalACswitchMessage(buf,2);
}

void setAcAutoSwitch(u8 param)
{
	u8 buf[2];
	buf[0] = 0x00;
	buf[1] = param;
	acToHalAutoSwitchMessage(buf,2);
}

void setAcDualSwitch(u8 param)
{
	u8 buf[2];
	buf[0] = 0x00;
	buf[1] = param;
	acToHalDualSwitchMessage(buf,2);
}

void setAcFWindowHeating(u8 param)
{
	u8 buf[2];
	buf[0] = 0x00;
	buf[1] = param;
	acToHalMistRemovalMessage(buf,2);
}

void setAcRearWindowHeating(u8 param)
{
	u8 buf[2];
	buf[0] = 0x00;
	buf[1] = param;
	acToHalRearWindowHeatingMessage(buf,2);
}
void setAcInfoToSdk(u8 *param,int len)
{
	u8 buf[256] = {0};
	if(len > 255)
		len = 255;
	buf[0] = 0x01;
	memcpy(buf+1, param, len);
	makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_FLYJNISDK,buf,len +1);
}

void setAcHeatSeatSwitch(u8 LorR,u8 param)
{
	u8 buf[3];
	buf[0] = 0x00;
	buf[1] = LorR;
	buf[2] = param;
	acToHalHeatSeatMessage(buf,3);
}
void acToHalHeatSeatMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x0A;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}
void setAcHeatSeatGrade(u8 RorL,u8 param)
{
	u8 buf[3] = {0x01,RorL,param};
	acToHalHeatSeatMessage(buf,sizeof(buf));
}

void setAcFrontWindowBlowMax(u8 param)
{
	u8 buf[2];
	buf[0] = 0x05;
	buf[1] = param;
	acToHalMistRemovalMessage(buf,2);
}

void setRearAcSwitchToHal(u8 param)
{
	u8 buf[3] = {0x80,0x00,param};
	sendAcMessageacToOtherModule(buf,3);
}

void setRearAcTempeartrueControl(u8 param)
{
	u8 buf[] = {0x01,0x00,0x00};
	buf[2] =  param;
	acToHalRearAcTempeartrueCtrlMessage(buf,sizeof(buf));
}

void acToHalRearAcTempeartrueCtrlMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x81;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}


void setRearAcWindSpeed(u8 param)
{
	u8 buf[] = {0x01,0x00};
	buf[1] =  param;
	acToHalRearAcWindSpeedMessage(buf,sizeof(buf));
}

void acToHalRearAcWindSpeedMessage(u8 *param,u8 len)
{
	u8 buf[256];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x82;
	memcpy(buf+1,param,len);
	sendAcMessageacToOtherModule(buf,len+1);
}

void setRearAcControlLockToHal(u8 param)
{
	u8 buf[3] = {0x8B,0x00,param};
	sendAcMessageacToOtherModule(buf,3);
}

void setAcAutoSwitchBackRow(u8 param)
{
	u8 buf[3] = {0x86,0x00,param};
	sendAcMessageacToOtherModule(buf,3);

}

