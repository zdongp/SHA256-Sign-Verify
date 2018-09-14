#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <flyutils/debug.h>
#include <cstring>
#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "controlID.h"
#define MESSAGETYPE_STATUS			0x00
#define MESSAGETYPE_CONTROL		0x01


class  CNotifyAndResponseFlyJniSdk
{
public:
    CNotifyAndResponseFlyJniSdk();
     ~CNotifyAndResponseFlyJniSdk();

	void sendToFlyJniSdk_HandLocker(u8 state);
	void sendToFlyJniSdk_SafetyBelt(u8 state);
	void sendToFlyJniSdk_OilRemind(int param);
	void sendToFlyJniSdk_DrivingDistance(int param);
	void sendToFlyJniSdk_EngineSpeed(int param);
	void sendToFlyJniSdk_InstantSpeed(int param);
	void sendToFlyJniSdk_DegreeOfWater(int param);
	void sendToFlyJniSdk_BatteryVoltageInfo(int param);
	void sendToFlyJniSdk_DoorInfo(char param);
	void sendToFlyJniSdk_EngineDoorInfo(char param);
	void sendToFlyJniSdk_FootLockState(char param);
	void sendToFlyJniSdk_GearState(char param);
	void sendToFlyJniSdk_CleanWaterStatus(char param);
	void sendToFlyJniSdk_MileageCanRun(int param);
	void sendToFlyJniSdk_AvgOilWearInfo(char cUnit,int param);
	void sendToFlyJniSdk_DegreeOfCarGround(int param);
	void sendToFlyJniSdk_CarLocker(char param);
	void sendToFlyJniSdk_TheCopilot_SafetyBelt(char state);
	void sendToFlyJniSdk_CarDoorWindow(u8 * param,int len);
	void sendToFlyJniSdk_CarDormer(char param);
	void sendToFlyJniSdk_CarHeadlight(char param);
	void sendToFlyJniSdk_BatteryAnomalyMonitoring(u8 param);
	
	void analyseFlyJniSdkMessage(unsigned char *p,int len);

	void sendToFlyJniSdk_AccOffBatteryVoltageInfo(int param);
	/********************/
	void analyseFlyJniSdkStatusMessage(unsigned char *p,int len);
	void analyseFlyJniSdkCtrlMessage(unsigned char *p,int len);
	/************************sendToAppBasicFunction*******************************/
	void sendToAppExtcarStatusInfo(u8 *buf,int len);
	/*****************************sendToAppFunction*****************************/
	void	 extcarSendSeatBeltsStatusToSdk(u8 param);
	void	 extcarSendRemainOilToSdk(int param);
	void	 extcarSendDriveMileageToSdk(int param);
	void	 extcarSendOutSideTemperatureToSdk(int nTemp,u8 nDecimal,u8 nUnit ,u8 PosOrNeg);
	void	 extcarSendHandBrakeStatusToSdk(u8 param);
	void	 extcarSendEngineSpeedToSdk(int param);
	void	 extcarSendPublicAverageSpeedToSdk(int param);
	void	 extcarSendInstantSpeedToSdk(int param);
	void	 extcarSendBatteryVoltageToSdk(int param);
	void	 extcarSendContinuedDriveMileageToSdk(int param);
	void	 extcarSendAverageFuelConsumptionToSdk(int param);
	void	 extcarSendDoorStatusToSdk(u8 *param,int len);
	void	 extcarSendDoorLockStatusToSdk(u8 *param,int len);
	void	 extcarSendTrunkStatusToSdk(u8 param);
	void	 extcarSendFrontCoverStatusToSdk(u8 param);
	void	 extcarSendSkyLightStatusToSdk(u8 param);
	void	 extcarSendLightStatusToSdk(u8 LightType,u8 param);
	void	 extcarSendGearsInfoToSdk(u8 param);
	void	 extcarSendVINCodeToSdk(u8 *param,int len);
	void analyseFindCarFeedBackInfo(u8 *param,int len);
	void analyseDrivingAutoLockInfo(u8 *param,int len);
	void analyseFollowMeHomeInfo(u8 *param,int len);
	void analyseSdkToModuleSkylightControl(u8 *param,int len);
};
