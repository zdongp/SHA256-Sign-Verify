#include <stdio.h>
#include <stdlib.h>
//#include <cutils/properties.h>


#include "global.h"
#include "otherModuleResponseFunction.h"
#include "appRequestCommand.h"


void moduleToCenter_StartRing(unsigned char ringId){
	setRingerCtrl(0x01);
}

void moduleToCenter_StopRing(){
	setRingerCtrl(0x00);
}

void moduleToCenter_StartAlarmRing(unsigned char ringId){
	setAlarmRingerCtrl(0x02);
}

void moduleToCenter_StopAlarmRing(){
	setAlarmRingerCtrl(0x03);
}


void moduleToCenter_FromBT_Message(unsigned char *param, unsigned char len){

	unsigned char cmd = param[0];
	
	switch(cmd){
		case 0x02:
			moduleToCenter_StartRing(0x01);
			break;
		case 0x03:
			LOGD("Stop Ring...");
			moduleToCenter_StopRing();
			break;
		default:
			break;
	}
}


void moduleToCenter_FromTPMS_Message(unsigned char *param, unsigned char len){

	unsigned char cmd = param[0];

	LOGD("moduleToCenter_FromTPMS_Message<><><><><cmd:%x", cmd);
	
	switch(cmd){
		case 0x04:
			LOGD("Start Alarm Ring...");			
			moduleToCenter_StartAlarmRing(0x01);
			break;	
		case 0x05:
			LOGD("Stop Alarm Ring...");
			moduleToCenter_StopAlarmRing();
			break;	
		default:
			break;
	}
}

void moduleToCenter_FromExtCar_Message(unsigned char *param, unsigned char len)
{
	switch(param[0])
	{
		case 0x12:
		{
			SetAlarmTip(param + 1, 2);
			LOGD("moduleToCenter_FromExtCar_Message: SetAlarmTip : param[1] = 0x%X , param[2] = 0x%X", param[1], param[2]);
		}
		break;
	}
}

void moduleToCenter_FromDNV_Message(u8 *p, u8 len)
{
	switch(p[0])
	{
	case 0x12:
		{
			SetAlarmTip(p + 1, 2);

			LOGD("[%s]", __FUNCTION__);
		}
		break;
	}
}

void moduleToCenter_FromSystem_Message(unsigned char *param, unsigned char len){
	
	unsigned char cmd = param[0];
	
	switch(cmd){
		case 0x2C:	// acc off
			break;
		case 0x2D:	// acc on
			break;
	}
}

void moduleToCenter_FromSYNC_Message(unsigned char *param, unsigned char len)
{
	switch(param[0])
	{
		case 0x00:
		{
			LOGD("moduleToCenter_FromSYNC_Message: SetAlarmTip:param[1] = 0x%X ", param[1]);
			setSyncContectStateToUI(param[1]);
		}
		break;
		default:break;
	}

}

void moduleToCenter_FromAutomate(u8 *param, int len)
{
    #include "appResponseCommand.h"
    
    if(param[0] != 0xff)
    return;
    analyseAppMessage(param+1,len-1);   
}


