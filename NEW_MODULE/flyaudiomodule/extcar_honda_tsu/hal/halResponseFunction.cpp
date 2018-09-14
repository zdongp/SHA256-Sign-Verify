#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "halResponseFunction.h"


void analyseHalMessage_EXTCAR_HONDA_TSU(u8 resCmd, u8 *param, u8 len)
{
	LOGD("[%s] cmd:%x %x %x %x","(HONDA TSU)",resCmd,param[0],param[1],param[2]);
	switch(resCmd)
	{
		case 0x01:
		case 0x02:
			break;
		case 0x10:
			GetGenarlData(param,len);
			break;
	}

}

void GetGenarlData(u8 *param,u8 len)
{
	switch(param[0])
	{
		case 0x00:
			getNoRealTimeDate(param+1,len -1);
			break;
		case 0x01:
			getRealTimeDate(param+1,len -1);
			break;
		case 0x02:
			break;
		default:break;
	}
}
void getNoRealTimeDate(u8 *param ,int len)
{
	switch(param[0])
	{
		case 0x00:
			param[0] = 0x00;
			break;
		case 0x01:
			param[0] = 0x01;
			break;
		case 0x02:
			param[0] = 0x02;
			break;
		case 0x03:
			param[0] = 0x03;
			break;
		case 0x04:
			param[0] = 0x04;
			break;
		case 0x05:
			param[0] = 0x05;
			break;
		case 0x06:
			param[0] = 0x06;
			break;
		case 0x07:
			param[0] = 0x07;
			break;
		case 0x08:
			param[0] = 0x08;
			break;
		case 0x09:
			param[0] = 0x09;
			break;
		case 0x10:
			param[0] = 0x0a;
			break;
		case 0x11:
			param[0] = 0x0b;
			break;
		case 0x12:
			param[0] = 0x0c;
			break;
		default:break;
	}
	g_clsExtcarHondaTsu.sendToAppNoRealTimeDate(param,len);
}

void getRealTimeDate(u8 *param ,int len)
{
	g_clsExtcarHondaTsu.sendToAppExtcarHondaTSUData(param,len);
}