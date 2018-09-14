#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <commonFunc.h>
#include <ctype.h>
#include <string.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
#include "moduleParamResponse.h"

CCarInfoCarSettingToyota gclsCarInforCarSettings;
u8 sTrunkInfor = 0xFF;
u8 sDoors = 0xFF;
u8 sSelfBelts = 0xFF;
u8 sHandBreak = 0xFF;

#define FLY_CFG_MAIN_DRIVER_RIGHT  "fly.cfg.main.driver.right"
#define FLY_EXTCAR_SPEEDLOCK    			"fly.extcar.speedlock"
#define FLY_EXTCAR_SHIFTLOCK    			"fly.extcar.shiftlock"
#define FLY_EXTCAR_PMODEUNLOCK    			"fly.extcar.pmodeunlock"
#define FLY_EXTCAR_DPRESSUNLOCK    			"fly.extcar.dpressunlock"
#define FLY_EXTCAR_LIGHTSENSITIVITY    		"fly.extcar.lightsensitivity"
#define FLY_EXTCAR_CARLOCK		    		"fly.extcar.carlock"
#define FLY_EXTCAR_HISTORYCUR    			"fly.extcar.historycur"
#define FLY_EXTCAR_HISTORY1    				"fly.extcar.history1"
#define FLY_EXTCAR_HISTORY2    				"fly.extcar.history2"
#define FLY_EXTCAR_HISTORY3    				"fly.extcar.history3"
#define FLY_EXTCAR_HISTORY4    				"fly.extcar.history4"
#define FLY_EXTCAR_HISTORY5   				"fly.extcar.history5"
#define FLY_EXTCAR_ACOREFFECTVEN			"fly.extcar.acorreffectven"
#define FLY_EXTCAR_GOLF_DRIVE_DATA_TYPE		"fly.extcar.golf.drive.data.type"
#define FLY_EXTCAR_DA_ZHONG_SEND_CHINESE_TO_CAR_SCREEN		"fly.extcar.cnswitch"
#define FLY_EXTCAR_GOLF_7_RADAR_RING_DOOR		"fly.extcar.golf7.radar.ring.door"

#define FLY_CARNAME          "fly.carName"
#define FLY_FLYUI_CAINFO_BUTTON_VISIBLE          "fly.flyui.carinfo.visible"


#define FLY_CARSETING_SPEED_AUTOLOCK "fly.carset.speed.autolock"
#define FLY_CARSETING_HEADLIGHT_SENTIVITY "fly.carset."
#define FLY_CARSETING_INLIGHT_TIMER "fly.carset.inlight.timer"
#define FLY_CARSETING_SWITCHDOOR_UNLOCK "fly.carset.switchdoor.unlock"
#define FLY_CARSETING_ELECTRONIC_SYSKEY "fly.carset.electronic.syskey"
#define FLY_CARSETING_PILOTLAMP "fly.carset.pilotlamp"
#define FLY_CARSETING_OUTP_LOCK "fly.carset.outp.lock"
#define FLY_CARSETING_INP_LOCK "fly.carset.inp.lock"
#define FLY_CARSETING_DRIVERDOOR_UNLOCK "fly.carset.driverdoor.unlock"
#define FLY_CARSETING_BACKGUIDELINE "fly.carset.backguideline"
#define FLY_CARSETING_TELECONTROL_2STEP "fly.carset.telecontrol.2step"
#define FLY_CARSETING_AUTOACMODE "fly.carset.autoac.mode"
#define FLY_CARSETING_VENTILATMODE "fly.carset.ventilat.mode"

#define FLY_CARSETING_DRIVING_MOD "fly.carsetting.drivingmod"
#define FLY_CARSETING_DAMPING_SYSTEM "fly.carsetting.dampingsystem"
#define FLY_CARSETING_STEERING_WHEEL "fly.carsetting.steeringwheel"
#define FLY_CARSETING_DRIVING_GEAR "fly.carsetting.drivinggear"
#define FLY_CARSETING_DYNAMIC_HEADLIGHT "fly.carsetting.dynamicheadlight"
#define FLY_CARSETING_AC_MOD "fly.carsetting.acmod"
#define FLY_CARSETING_ENGINE_SOUNDS "fly.carsetting.enginesounds"

extcar_local_param_t localParam;
extcar_local_param_t *pLocalParam = (extcar_local_param_t*)&localParam;

extcar_global_param_t globalParam;
extcar_global_param_t *pGlobalParam = (extcar_global_param_t*)&globalParam;

CNotifyAndResponseFlyJniSdk g_clsExtcar;

void readParameter(void){

	LOGD("[dyb] ************* readParameter*****************");

	int value = 0;
	int t = 0;
	setDefaultParam();
	char property[PROPERTY_VALUE_MAX];

	static int nT = 0;
	property_get(FLY_CFG_MAIN_DRIVER_RIGHT,property,NULL);
	sscanf(property,"%d", &nT);
	pLocalParam->em_MainDriverPos = (EM_MAIN_DRIVER)nT;

	property_get(FLY_EXTCAR_SPEEDLOCK,property,NULL);
	sscanf(property,"%d", &pLocalParam->speedLock);

	property_get(FLY_EXTCAR_SHIFTLOCK,property,NULL);
	sscanf(property,"%d", &pLocalParam->shiftLock);

	property_get(FLY_EXTCAR_PMODEUNLOCK,property,NULL);
	sscanf(property,"%d", &pLocalParam->pModeUnlock);

	property_get(FLY_EXTCAR_DPRESSUNLOCK,property,NULL);
	sscanf(property,"%d", &pLocalParam->dPressUnlock);

	property_get(FLY_EXTCAR_LIGHTSENSITIVITY,property,NULL);
	sscanf(property,"%d", &pLocalParam->lightSensitivity);

	property_get(FLY_EXTCAR_CARLOCK,property,NULL);
	sscanf(property,"%d", &pLocalParam->carLock);

	property_get(FLY_EXTCAR_HISTORYCUR,property,NULL);
	sscanf(property,"%f", &pLocalParam->carHistory.fHistoryCur);

	property_get(FLY_EXTCAR_HISTORY1,property,NULL);
	sscanf(property,"%f", &pLocalParam->carHistory.fHistory1);

	property_get(FLY_EXTCAR_HISTORY2,property,NULL);
	sscanf(property,"%f", &pLocalParam->carHistory.fHistory2);

	property_get(FLY_EXTCAR_HISTORY3,property,NULL);
	sscanf(property,"%f", &pLocalParam->carHistory.fHistory3);

	property_get(FLY_EXTCAR_HISTORY4,property,NULL);
	sscanf(property,"%f", &pLocalParam->carHistory.fHistory4);

	property_get(FLY_EXTCAR_HISTORY5,property,NULL);
	sscanf(property,"%f", &pLocalParam->carHistory.fHistory5);

	t = 0xc0;
	property_get(FLY_EXTCAR_ACOREFFECTVEN,property,"192");
	sscanf(property,"%d", &t);
	pLocalParam->AutomaticalAcOrEffectVentilat = (u8)t;

	property_get(FLY_CARNAME,property,"0");
	sscanf(property,"%s",pLocalParam->c_carName);

	t = 0;
	property_get(FLY_EXTCAR_GOLF_DRIVE_DATA_TYPE,property, 0);
	sscanf(property,"%d",&t);
	pLocalParam->eDriveDataType = (E_DRIVE_DATA_TYPE)t;

	property_get(FLY_EXTCAR_DA_ZHONG_SEND_CHINESE_TO_CAR_SCREEN,property, "1");
	sscanf(property,"%d", &pLocalParam->nCanSendChineseToDZCarScreen);
	LOGD("[DYB12] readParameter nCanSendChineseToDZCarScreen = [%d]", pLocalParam->nCanSendChineseToDZCarScreen);

	t=0;
	property_get(FLY_FLYUI_CAINFO_BUTTON_VISIBLE,property,"1");
	sscanf(property,"%d", &t);
        pLocalParam->cCarinfoButtonVisible = t ;
	//pLocalParam->cCarinfoButtonVisible=0;
	LOGD("%d,%d,%d,%d,%d,%d,%f,%f, golf drive data type = [%d]"
			,pLocalParam->speedLock
			,pLocalParam->shiftLock
			,pLocalParam->pModeUnlock
			,pLocalParam->dPressUnlock
			,pLocalParam->lightSensitivity
			,pLocalParam->carLock
			,pLocalParam->carHistory.fHistoryCur
			,pLocalParam->carHistory.fHistory1
			,pLocalParam->eDriveDataType);


	static int nTempV = 0;
	property_get(FLY_CARSETING_SPEED_AUTOLOCK,property,"0");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_SpeedAutoLockState = (E_CARSET_SPEED_AUTOLOCK_STATE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_HEADLIGHT_SENTIVITY,property,"3");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_HeadLightSentivity = (E_CARSET_HEADLIGHT_SENTIVITY)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_INLIGHT_TIMER,property,"1");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_IntertiorLightTimer = (E_CARSET_INTERTIORLIGHT_TIMER)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_SWITCHDOOR_UNLOCK,property,"0");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_SwitchDoorUnlockSwitch = (E_CARSET_DOOR_UNLOCK_SWITCH)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_ELECTRONIC_SYSKEY,property,"1");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_ElectronicToSysKeyState = (E_CARSET_ELECTRONICTOSYSKEY_STATE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_PILOTLAMP,property,"1");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_PilotlampState = (E_CARSET_LOCKSTATE_PILOTLAMP_STATE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_OUTP_LOCK,property,"0");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_OutPAutoLockState = (E_CARSET_OUT_P_AUTOLOCK_STATE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_INP_LOCK,property,"0");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_InPAutoLockState = (E_CARSET_IN_P_AUTOLOCK_STATE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_DRIVERDOOR_UNLOCK,property,"0");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_DriverDoorAutoUnlockState = (E_CARSET_DRIVERDOOR_AUTOUNLOCK_STATE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_BACKGUIDELINE,property,"2");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_BackCarGuideLineSet = (E_CARSET_BACKCAR_GUIDELINESET)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_TELECONTROL_2STEP,property,"0");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_Telecontrol2StepState = (E_CARSET_TELECONTROL_2SEP_AUTOUNLOCK_STATE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_AUTOACMODE,property,"1");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_AutoAcModeState = (E_CARSET_AUTO_ACMODE_STATE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_VENTILATMODE,property,"1");
	sscanf(property,"%d", &nTempV);
	gclsCarInforCarSettings.m_enCarSet_VentilatModeState = (E_CARSET_EFFECTIVE_VENTILATMODE_STATE)nTempV;


	nTempV = 0;
	property_get(FLY_CARSETING_DRIVING_MOD,property,"2");
	sscanf(property,"%d", &nTempV);
	pLocalParam->eCar_DrivingMode = (E_CAR_DRIVING_MODE)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_DAMPING_SYSTEM,property,"2");
	sscanf(property,"%d", &nTempV);
	pLocalParam->eCar_DampingSystemMode = (E_CAR_DAMPING_SYSTEM_MOD)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_STEERING_WHEEL,property,"2");
	sscanf(property,"%d", &nTempV);
	pLocalParam->eCar_SteeringWheelMode = (E_CAR_STEERING_WHEEL_MOD)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_DRIVING_GEAR,property,"2");
	sscanf(property,"%d", &nTempV);
	pLocalParam->eCar_DrivingGearMode = (E_CAR_DRIVING_GEAR_MOD)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_DYNAMIC_HEADLIGHT,property,"2");
	sscanf(property,"%d", &nTempV);
	pLocalParam->eCar_Dynamic_Headlight_FollowerMode = (E_CAR_DYNAMIC_HEADLIGHT_FOLLOWER_MOD)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_AC_MOD,property,"2");
	sscanf(property,"%d", &nTempV);
	pLocalParam->eCar_AcMode = (E_CAR_AC_MOD)nTempV;

	nTempV = 0;
	property_get(FLY_CARSETING_ENGINE_SOUNDS,property,"2");
	sscanf(property,"%d", &nTempV);
	pLocalParam->eCar_InternalEngineSoundsMode = (E_CAR_INTERNAL_ENGINE_SOUNDS_MOD)nTempV;

	if(!pLocalParam->m_pCarInfo)
		extarToApp_CarInfoInitUI();
}

void saveParameter(void){

	LOGD("[dyb] *************saveParameter*****************");

	char property[PROPERTY_VALUE_MAX];
	LOGD("saveParameter:%d,%d,%d,%d,%d,%d,%f,%f"
		,pLocalParam->speedLock
		,pLocalParam->shiftLock
		,pLocalParam->pModeUnlock
		,pLocalParam->dPressUnlock
		,pLocalParam->lightSensitivity
		,pLocalParam->carLock
		,pLocalParam->carHistory.fHistoryCur
		,pLocalParam->carHistory.fHistory1);
	sprintf(property,"%d", pLocalParam->speedLock);
	property_set(FLY_EXTCAR_SPEEDLOCK,property);

	sprintf(property,"%d", pLocalParam->shiftLock);
	property_set(FLY_EXTCAR_SHIFTLOCK,property);

	sprintf(property,"%d", pLocalParam->pModeUnlock);
	property_set(FLY_EXTCAR_PMODEUNLOCK,property);

	sprintf(property,"%d", pLocalParam->dPressUnlock);
	property_set(FLY_EXTCAR_DPRESSUNLOCK,property);

	sprintf(property,"%d", pLocalParam->lightSensitivity);
	property_set(FLY_EXTCAR_LIGHTSENSITIVITY,property);

	sprintf(property,"%d", pLocalParam->carLock);
	property_set(FLY_EXTCAR_CARLOCK,property);

	sprintf(property,"%f", pLocalParam->carHistory.fHistoryCur);
	property_set(FLY_EXTCAR_HISTORYCUR,property);

	sprintf(property,"%f", pLocalParam->carHistory.fHistory1);
	property_set(FLY_EXTCAR_HISTORY1,property);

	sprintf(property,"%f", pLocalParam->carHistory.fHistory2);
	property_set(FLY_EXTCAR_HISTORY2,property);

	sprintf(property,"%f", pLocalParam->carHistory.fHistory3);
	property_set(FLY_EXTCAR_HISTORY3,property);

	sprintf(property,"%f", pLocalParam->carHistory.fHistory4);
	property_set(FLY_EXTCAR_HISTORY4,property);

	sprintf(property,"%f", pLocalParam->carHistory.fHistory5);
	property_set(FLY_EXTCAR_HISTORY5,property);

	sprintf(property,"%d", pLocalParam->AutomaticalAcOrEffectVentilat);
	property_set(FLY_EXTCAR_ACOREFFECTVEN,property);

	sprintf(property,"%d", (int)pLocalParam->eDriveDataType);
	property_set(FLY_EXTCAR_GOLF_DRIVE_DATA_TYPE,property);

	sprintf(property,"%d", pLocalParam->nCanSendChineseToDZCarScreen);
	property_set(FLY_EXTCAR_DA_ZHONG_SEND_CHINESE_TO_CAR_SCREEN,property);
	LOGD("[DYB12] saveParameter nCanSendChineseToDZCarScreen = [%d]", pLocalParam->nCanSendChineseToDZCarScreen);

	sprintf(property,"%d", pLocalParam->cCarinfoButtonVisible);
	property_set(FLY_FLYUI_CAINFO_BUTTON_VISIBLE,property);



	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_SpeedAutoLockState);
	property_set(FLY_CARSETING_SPEED_AUTOLOCK,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_HeadLightSentivity);
	property_set(FLY_CARSETING_HEADLIGHT_SENTIVITY,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_IntertiorLightTimer);
	property_set(FLY_CARSETING_INLIGHT_TIMER,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_SwitchDoorUnlockSwitch);
	property_set(FLY_CARSETING_SWITCHDOOR_UNLOCK,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_ElectronicToSysKeyState);
	property_set(FLY_CARSETING_ELECTRONIC_SYSKEY,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_PilotlampState);
	property_set(FLY_CARSETING_PILOTLAMP,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_OutPAutoLockState);
	property_set(FLY_CARSETING_OUTP_LOCK,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_InPAutoLockState);
	property_set(FLY_CARSETING_INP_LOCK,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_DriverDoorAutoUnlockState);
	property_set(FLY_CARSETING_DRIVERDOOR_UNLOCK,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_BackCarGuideLineSet);
	property_set(FLY_CARSETING_BACKGUIDELINE,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_Telecontrol2StepState);
	property_set(FLY_CARSETING_TELECONTROL_2STEP,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_AutoAcModeState);
	property_set(FLY_CARSETING_AUTOACMODE,property);

	sprintf(property,"%d", gclsCarInforCarSettings.m_enCarSet_VentilatModeState);
	property_set(FLY_CARSETING_VENTILATMODE,property);

	sprintf(property,"%d", pLocalParam->eCar_DrivingMode);
	property_set(FLY_CARSETING_DRIVING_MOD,property);

	sprintf(property,"%d", pLocalParam->eCar_DampingSystemMode);
	property_set(FLY_CARSETING_DAMPING_SYSTEM,property);

	sprintf(property,"%d", pLocalParam->eCar_SteeringWheelMode);
	property_set(FLY_CARSETING_STEERING_WHEEL,property);

	sprintf(property,"%d", pLocalParam->eCar_DrivingGearMode);
	property_set(FLY_CARSETING_DRIVING_GEAR,property);

	sprintf(property,"%d", pLocalParam->eCar_Dynamic_Headlight_FollowerMode);
	property_set(FLY_CARSETING_DYNAMIC_HEADLIGHT,property);

	sprintf(property,"%d", pLocalParam->eCar_AcMode);
	property_set(FLY_CARSETING_AC_MOD,property);

	sprintf(property,"%d", pLocalParam->eCar_InternalEngineSoundsMode);
	property_set(FLY_CARSETING_ENGINE_SOUNDS,property);
	
}

int enc_get_utf8_size(const unsigned char pInput)
{
	unsigned char c = pInput;
	if(c < 0x80) return 1;
	if(c >= 0x80 && c < 0xC0) return -1;
	if(c >= 0xC0 && c < 0xE0) return 2;
	if(c >= 0xE0 && c < 0xF0) return 3;
	if(c >= 0xF0 && c < 0xF8) return 4;
	if(c >= 0xF8 && c < 0xFC) return 5;
	if(c >= 0xFC) return 6;

	return -1;
}

int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
    char b1, b2, b3, b4, b5, b6;

    *Unic = 0x0; // 
    int utfbytes = enc_get_utf8_size(*pInput);
    unsigned char *pOutput = (unsigned char *)Unic;

    switch(utfbytes)
    {
    case 1:
        *pOutput = *pInput;
        break;
    case 2:
        b1 = *pInput;
        b2 = *(pInput + 1);
        if ( (b2 & 0xC0) != 0x80 )
            return 0;
        *pOutput     = (b1 << 6) + (b2 & 0x3F);
        *(pOutput+1) = (b1 >> 2) & 0x07;
        break;
    case 3:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b2 << 6) + (b3 & 0x3F);
        *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
        break;
    case 4:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b3 << 6) + (b4 & 0x3F);
        *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
        *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
        break;
    case 5:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b4 << 6) + (b5 & 0x3F);
        *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
        *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);
        *(pOutput+3) = (b1 << 6);
        break;
    case 6:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        b6 = *(pInput + 5);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
                || ((b6 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b5 << 6) + (b6 & 0x3F);
        *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
        *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);
        *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
        break;
    default:
        return 0;
        break;
    }//switch(utfbytes)

    return utfbytes;
}


int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize)
{
	int nSrcLen = 0;
	int nDstLen = 0;
	u8 *pUtf8 = pInput;
	u8 *pUnic = pOutput;
	int nOneUtf8Len = 0;

	nOneUtf8Len = enc_get_utf8_size(*pUtf8);

	while(-1 != nOneUtf8Len)
	{
		unsigned long oneUnic = 0;
		enc_utf8_to_unicode_one(pUtf8, &oneUnic);

		nDstLen += 2;
		if (nOutputSize < nDstLen)//装不下，回退
		{
			nDstLen -= 2;
			break;
		}
		else
			memcpy(pUnic, &oneUnic, 2);

		nSrcLen += nOneUtf8Len;
		if (nSrcLen >= nInputLen)//解析完了，退出
		{
			break;
		}

		pUtf8 += nOneUtf8Len;
		pUnic += 2;

		nOneUtf8Len = enc_get_utf8_size(*pUtf8);
	}

	return nDstLen;
}

uni16_size_t uni16_strlen(const unicode16_t *uni16)
{
	return 0;
}
unicode16_t ansi_to_unicode16(const unsigned char ansi)
{
	return 0;
}
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16)
{
	int nSrcLen = strlen((char*)ansi);
	int nUni16Len = nSrcLen*2+2;
	int nRetLen = utf8_2_ucs2(ansi, nSrcLen, (u8*)uni16, nUni16Len);
	
	return (nRetLen/2);
}
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16)
{
	return 0;
}

