#pragma once
#include "global.h"

class  CAcJniSdk
{
	public:
		CAcJniSdk();
		~CAcJniSdk();
	public:		//param tag
		bool acSwitchSendTag = false;
		bool acTempSendTag = false;
		bool acSeedSendTag = false;
		bool acWModeSendTag = false;
		bool acLModeSendTag = false;
		bool acACSatusSendTag = false;
		bool acACMaxSendTag = false;
		bool acAutoSendTag = false;
		bool acSyncSendTag = false;
		bool acFrontSendTag = false;
		bool acRearSendTag = false;
		bool acHeatSeatSendTag = false;
		bool acHeatGradeSendTag = false;
		

	public:		//Function
		void getSdkToModuleAcMessage(u8 *p,int len);
		void analysSdkToAcStatusMessage(u8 *buf,u8 len);
		void analysSdkToAcContrlMessage(u8 *buf,u8 len);
		
		void sendToFlyJniSdkService(u8 moduleId, u8 *p, int len);
		void sendToAppAcStatusInfo(u8 *buf,int len);
		void sendToApp_AcSwitch(u8 param);
		void sendToApp_AcTemp(int min,int max,int Ltemp,int Rtemp,u8 Decimal,u8 unit);
		void sendToApp_AcWindSpeed(u8 min,u8 max,u8 speed);
		void sendToApp_AcWindMode(u8 param);
		void sendToApp_AcLoopMode(u8 param);
		void sendToApp_AcAorCStatus(u8 param);
		void sendToApp_AcMaxAorCStatus(u8 param);
		void sendToApp_AcAutoSwitch(u8 param);
		void sendToApp_AcDual(u8 param);
		void sendToApp_FrontClassMistRemoval(u8 param);
		void sendToApp_RearWindowHeat(u8 param);    //Glass mist removal
		void sendToApp_HeatSeatStatus(u8 tag,u8 param);
		void sendToApp_HeatSeatGrade(u8 tag,u8 param);
		void analysAcTempAndSendToApp(int min, int max, int tempL, int tempR,u8 Digits,u8 unit);
		void analysAcWindSpeedAndSendToApp(u8 min, u8 max, u8 curvalue);

		void sdkToAcSetWindSpeed(u8 *buf,u8 len);
		void sdkToAcSetTempValue(u8 *buf,u8 len);
		void sdkToAcSetMistRemoval(u8 *buf,u8 len);
		void sdkToAcSetMaxMistRemoval(u8 *buf,u8 len);
		void analyseSdkSetTempAddOrRed(u8 *buf,int len);
		void analyseSdkSetTempAddOrRed_All(u8 *buf,int len);
		void analyseSdkSetTempAddOrRed_Left(u8 *buf,int len);
		void analyseSdkSetTempAddOrRed_Right(u8 *buf,int len);
		void analyseSdkSetWindSpeedAddOrRed(u8 *buf,int len);
};

