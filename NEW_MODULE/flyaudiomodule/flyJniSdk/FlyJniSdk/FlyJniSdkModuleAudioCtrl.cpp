#include "FlyJniSdkModuleAudioCtrl.h"


CFlyJniSdkModuleAudioCtrl::CFlyJniSdkModuleAudioCtrl(void)
{

}

CFlyJniSdkModuleAudioCtrl::~CFlyJniSdkModuleAudioCtrl(void)
{

}

void CFlyJniSdkModuleAudioCtrl::analyseAudioCtrlAppMessageType(u8 *p, u8 len)
{
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			break;
		case CONTROL_MESSAGE:
			analyseAudioCtrlOperationMassage(p+1, len - 1);
			break;
		default:break;
	}

}

void CFlyJniSdkModuleAudioCtrl::analyseAudioCtrlOperationMassage(u8 *p, u8 len)
{
	switch(p[0])
	{
		case 0x00://Play control
		case 0x01://Play Mode Set
			SdkToOtherModule_AudioCtrl_FromSourceSource(p[0],p[1]);
			break;
		default:break;
	}
}

void CFlyJniSdkModuleAudioCtrl::setToCurPlaySourcePlayCtrl(u8 p)
{
	switch(p)
	{
		case 0x00://Next
		case 0x01://Last
		case 0x02://pause
		case 0x03://play
		case 0x04://stop
		case 0x05://finish
		break;
		default:break;
	}
}

void CFlyJniSdkModuleAudioCtrl::setToCurPlaySourcePlayMode(u8 p)
{
	switch(p)
	{
		case 0x00://sequential cycle
		case 0x01://random Play
		case 0x02://single tune circulation
	    case 0x03://Loop PlayBack
		break;
		default:break;
	}
}



