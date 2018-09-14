#include <stdio.h>
#include <stdlib.h>
#include <math.h>
extern "C"{
#include "unicodestring.h"
};
#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleResponseFunction.h"



/*֪ͨosd*/
void TellToOSD()
{
	u16 LeftTempOSD = 0;
	u16 RightTempOSD = 0;
	u8  uSpeed=0;
	u16 curpage = 0;
	u8 curpagelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curpage,&curpagelen);
	if(curpage != (u16)PAGE_AIRCONDITION )//&& m_pTheApp->m_pCenterParam->ACenable == 1)
	{
		uSpeed=convertSpeedTo123(pLocalParam->ucSpeed);
		if(uSpeed)pLocalParam->bACAccOn=false;
		if(pLocalParam->bACAccOn&&uSpeed==0)return;
		airconditionToModule_NotifyOsd_DisplayACTitle();
		if (pLocalParam->bOff)
		{
			if(pLocalParam->bACAccOn)return;
			airconditionToModule_NotifyOsd_DisplayOSDACInfor(0xFFFF,0xFFFF,0,0xFF,0x00);//Set_OSDOFF();
			return;
		}

		LeftTempOSD=convertTemperatureToT123(pLocalParam->leftTempValue);
		RightTempOSD=convertTemperatureToT123(pLocalParam->rightTempValue);
//		airconditionToModule_NotifyOsd_DisplayOSDACInfor(pLocalParam->leftTempValue ,pLocalParam->rightTempValue ,
//													0x00,pLocalParam->ucSpeed ,pLocalParam->ucAcState);
		airconditionToModule_NotifyOsd_DisplayOSDACInfor(LeftTempOSD,RightTempOSD,0x00,uSpeed,pLocalParam->ucAcState);
	}
}
u16 convertTemperatureToT123(u16 tempValue){
	double dTemp=tempValue/100.0+10;
	if(dTemp<=17)tempValue=0xFFFD;
	else if(dTemp>=27)tempValue=0xFFFE;
	else
		tempValue=(u16)(dTemp*100);
	return tempValue;
}
u8 convertSpeedTo123(u8 speed){
	if(speed==1)speed=0xFD;
	if(speed==7)speed=0xFE;
	return speed;
}

void fks_TellToOSD()
{
	u8  uSpeed=0;
	u16 LeftTempOSD = 0;
	u16 RightTempOSD = 0;
	u16 curpage = 0;
	u8 curpagelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curpage,&curpagelen);
	
	if( fabs(pLocalParam->fks_fLeftTemperature-15.0) < 0.000001 )
		//LeftTempOSD=0;
		LeftTempOSD=0xFFFD;
	else if( fabs(pLocalParam->fks_fLeftTemperature-30.0) < 0.000001 )
		//LeftTempOSD=34*100;
		LeftTempOSD=0xFFFE;
	else if( fabs(pLocalParam->fks_fLeftTemperature - 127.5) <0.000001)
		//LeftTempOSD = 35*100;
		LeftTempOSD=0xFFFF;
	else 
		LeftTempOSD = pLocalParam->fks_fLeftTemperature*100;

	
	if( fabs(pLocalParam->fks_fRightTemperature-15.0) < 0.000001 )
		//RightTempOSD=0;
		RightTempOSD=0xFFFD;
	else if( fabs(pLocalParam->fks_fRightTemperature-30.0) < 0.000001 )
		//RightTempOSD=34*100;
		RightTempOSD=0xFFFE;
	else if( fabs(pLocalParam->fks_fRightTemperature - 127.5) <0.000001)
		//RightTempOSD = 35*100;
		RightTempOSD=0xFFFF;
	else
		RightTempOSD = pLocalParam->fks_fRightTemperature*100;
	
	if(curpage != (u16)PAGE_AIRCONDITION)
	{
		uSpeed=convertSpeedTo123(pLocalParam->fks_uWindSpeed);
		if(uSpeed)pLocalParam->bACAccOn=false;
		if(pLocalParam->bACAccOn&&uSpeed==0)return;
		airconditionToModule_NotifyOsd_DisplayACTitle();
		if (pLocalParam->fks_uAcSwitch == 0)
		{
			//ACToModule_NotifyOsd_DisplayOSDACInfor_Q(0x2328,0x2328,0,0);//Set_OSDOFF();
			if(pLocalParam->bACAccOn)return;
			airconditionToModule_NotifyOsd_DisplayOSDACInfor(0xFFFF,0xFFFF,0,0xFF,0x00);//Set_OSDOFF();
			return;
		}
//		ACToModule_NotifyOsd_DisplayOSDACInfor_Q(LeftTempOSD,RightTempOSD,
//													pLocalParam->fks_uWindSpeed,pLocalParam->fks_uAcState);
        LOGD("fks osd:LeftT=%d,rightT=%d,speed=%x,acState=%x",LeftTempOSD,RightTempOSD,uSpeed,pLocalParam->fks_uAcState);
		airconditionToModule_NotifyOsd_DisplayOSDACInfor(LeftTempOSD,RightTempOSD,0x00,uSpeed,pLocalParam->fks_uAcState);

		}

}
void SiYu_TellToOSD()
{
	u8  uSpeed=0;
	u16 curpage = 0;
	u8 curpagelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curpage,&curpagelen);
	u16 LeftTempOSD = 35*100;
	u16 RightTempOSD = 35*100;
	if(curpage != (u16)PAGE_AIRCONDITION)
	{
		uSpeed = convertSpeedTo123(pLocalParam->SiYu_uWindSpeed);
		if(uSpeed)pLocalParam->bACAccOn=false;
		if(pLocalParam->bACAccOn&&uSpeed==0)return;
		if (pLocalParam->SiYu_uAcSwitch == 0)
		{
			if(pLocalParam->bACAccOn)return ;
			ACToModule_NotifyOsd_DisplayOSDACInfor_Q(0x2328,0x2328,0,0);//Set_OSDOFF();
			return;
		}
		ACToModule_NotifyOsd_DisplayOSDACInfor_Q(LeftTempOSD,RightTempOSD,
													pLocalParam->SiYu_uWindSpeed,0);
	}
}

void toyota_TellToOSD()
{
	u8  uSpeed=0;
	u16 LeftTempOSD = 0;
	u16 RightTempOSD = 0;
	u16 curpage = 0;
	u8 curpagelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curpage,&curpagelen);
	if(curpage != (u16)PAGE_AIRCONDITION)
	{
		uSpeed = convertSpeedTo123(pLocalParam->ucToyotaSpeed);
		if(uSpeed)pLocalParam->bACAccOn=false;
		if(pLocalParam->bACAccOn&&uSpeed==0)return;
		airconditionToModule_NotifyOsd_DisplayACTitle();
		if (pLocalParam->nToyotaAcOff == 0)
		{
			//pLocalParam->usToyotaLeftTempOSD=0x2328,pLocalParam->usToyotaRightTempOSD=0x2328,pLocalParam->ucToyotaSpeed=0,pLocalParam->ucToyotaAOrCState=0;
			if(pLocalParam->bACAccOn)return;
			airconditionToModule_NotifyOsd_DisplayOSDACInfor(0xFFFF,0xFFFF,0,0xFF,0x00);
			return;
		}
		else
		{
			if(pLocalParam->usToyotaLeftTempValue==0xff)
				pLocalParam->usToyotaLeftTempOSD=35*100;
			if(pLocalParam->usToyotaRightTempValue==0xff)
				pLocalParam->usToyotaRightTempOSD=35*100;
		}

		LeftTempOSD = convertToyotaTemperatureToT123(pLocalParam->usToyotaLeftTempOSD);
		RightTempOSD = convertToyotaTemperatureToT123(pLocalParam->usToyotaRightTempOSD);
		//ACToModule_NotifyOsd_DisplayOSDACInfor_Q(pLocalParam->usToyotaLeftTempOSD,pLocalParam->usToyotaRightTempOSD,pLocalParam->ucToyotaSpeed,pLocalParam->ucToyotaAOrCState);
		airconditionToModule_NotifyOsd_DisplayOSDACInfor(LeftTempOSD,RightTempOSD,0x00,uSpeed,pLocalParam->ucToyotaAOrCState);
	}

}

u16 convertToyotaTemperatureToT123(u16 tempValue){
	if(tempValue==0)tempValue=0xFFFD;
	if(tempValue==3400)tempValue=0xFFFE;
	if(tempValue==3500)tempValue=0xFFFF;
	return  tempValue;
}

int byd_ac_degree2osdDegree(int d)
{
	int t = 100;
	if (d == 0x11)
		d = 0;
	else if (d == 0x21)
		d = 34;
	
	d *= t;
	return d;
}


void byd_ac_msg_to_osd(E_AC_COLD_MODE acMode, int  leftDegree, int rightDegree, u8 windSpeed, E_AC_AC_MODE acDoor)
{
	u8 uSpeed=0;
	u16 pageID = 0;
	u8 len = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&pageID , &len);
	LOGD("byd ac msg to osd pageid = [%X]", pageID);
	if (pageID != (u16)PAGE_AIRCONDITION)
	{
		uSpeed = convertSpeedTo123(windSpeed);
		if(uSpeed)pLocalParam->bACAccOn=false;
		if(pLocalParam->bACAccOn&&uSpeed==0)return;
		airconditionToModule_NotifyOsd_DisplayACTitle();
		if (acDoor == AC_AC_MODE_OFF)
		{
			//leftDegree = 0x2328, rightDegree = 0x2328, windSpeed = 0, acMode = AC_COLD_MODE_OFF;
			if(pLocalParam->bACAccOn)return;
			leftDegree = 0xFFFF, rightDegree = 0xFFFF, windSpeed = 0xFF, acMode = AC_COLD_MODE_OFF;
		}
		else
		{
			leftDegree = byd_ac_degree2osdDegree(leftDegree);
			rightDegree = byd_ac_degree2osdDegree(rightDegree);
		}

		LOGD("byd ac msg to osd LD = [%d], RD = [%d], WS = [%d], AC = [%d]", leftDegree, rightDegree, windSpeed, acMode);
		//ACToModule_NotifyOsd_DisplayOSDACInfor_Q(leftDegree, rightDegree, windSpeed, acMode);
		uSpeed = convertSpeedTo123(windSpeed);
		leftDegree = convertToyotaTemperatureToT123(leftDegree);
		rightDegree = convertToyotaTemperatureToT123(rightDegree);
		airconditionToModule_NotifyOsd_DisplayOSDACInfor(leftDegree, rightDegree, 0x00,uSpeed, acMode);
	}
}

int golf_ac_degree2osdDegree(int d)
{
       return d;
       int t = 100;
       if (d == 0x00)
               d = 0;
       else if (d == 0xFE)
               d = 34;

       d *= t;
       return d;
}
int  golf_ac_degree2osdDegreeByUnit(int d,E_AC_DEGREE_UNIT degreeUnit){
	double dTemp=0.0;
	if (d== 0)
		d=0xFFFD;
	else if(d==0xFE)
		d=0xFFFE;
	else if(d==0xFF)
		d=0xFFFF;
	else{
		if(degreeUnit==0){
			d=(int)(((d-0x3c)+160)*0.1*100);
		}else if(degreeUnit==1){
			d=((d-0x28)/4+60)*100;
		}
	}
	return d;
}

void golf_ac_msg_to_osd(E_AC_COLD_MODE acMode, E_AC_DEGREE_UNIT degreeUnit, int  leftDegree, int rightDegree, u8 windSpeed, E_AC_AC_MODE acDoor)
{
	u16 pageID = 0;
	u8 len = 0;
	u8 uSpeed=0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&pageID , &len);
	LOGD("golf ac msg to osd pageid = [%X]", pageID);
	if (pageID != (u16)PAGE_AIRCONDITION)
	{
		LOGD("golf ac msg to osd LD = [%d], RD = [%d], WS = [%d], AC = [%d]", leftDegree, rightDegree, windSpeed, acMode);
		//ACToModule_NotifyOsd_setACInfoToOSD(0x00, degreeUnit, leftDegree, rightDegree, windSpeed, acMode, acDoor);
		uSpeed=convertSpeedTo123(windSpeed);
		if(uSpeed)pLocalParam->bACAccOn=false;
		if(pLocalParam->bACAccOn&&uSpeed==0)return;
		airconditionToModule_NotifyOsd_DisplayACTitle();
		if (acDoor == AC_AC_MODE_OFF)
		{
				//leftDegree = 0x2328, rightDegree = 0x2328, windSpeed = 0, acMode = AC_COLD_MODE_OFF;
			if(pLocalParam->bACAccOn)return;
			leftDegree = 0xFFFF, rightDegree = 0xFFFF, windSpeed = 0xFF, acMode = AC_COLD_MODE_OFF;
		}
		else
		{
				leftDegree = golf_ac_degree2osdDegreeByUnit(leftDegree,degreeUnit);
				rightDegree = golf_ac_degree2osdDegreeByUnit(rightDegree,degreeUnit);
		}

		LOGD("golf ac msg to osd LD = [%d], RD = [%d], WS = [%d], AC = [%d]", leftDegree, rightDegree, windSpeed, acMode);
		//ACToModule_NotifyOsd_DisplayOSDACInfor_Q(leftDegree, rightDegree, windSpeed, acMode);

		airconditionToModule_NotifyOsd_DisplayOSDACInfor(leftDegree, rightDegree, degreeUnit,uSpeed, acMode);
     }
}

int crv_ac_degree2osdDegree(int d)
{
		int t = 100;
		if (d == 2)
			d = 0;
		else if (d == 1)
			d = 34;
		
		d *= t;
		return d;
}

void crv_ac_msg_to_osd(u8 acMode, int  leftDegree, int rightDegree, u8 windSpeed, E_AC_AC_MODE acDoor)
{
	u8 uSpeed=0;
	u16 pageID = 0;
	u8 len = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&pageID , &len);
	LOGD("crv ac msg to osd pageid = [%X]", pageID);
	if (pageID != (u16)PAGE_AIRCONDITION)
	{
		uSpeed = convertSpeedTo123(windSpeed);
		if(uSpeed)pLocalParam->bACAccOn=false;
		if(pLocalParam->bACAccOn&&uSpeed==0)return;
		airconditionToModule_NotifyOsd_DisplayACTitle();
		if (acDoor == AC_AC_MODE_OFF)
		{
			if(pLocalParam->bACAccOn)return;
			leftDegree = 0xFFFF, rightDegree = 0xFFFF, windSpeed = 0xFF, acMode = 0;
		}
		else
		{
			leftDegree = crv_ac_degree2osdDegree(leftDegree);
			rightDegree = crv_ac_degree2osdDegree(rightDegree);
		}

		leftDegree = convertToyotaTemperatureToT123(leftDegree);
		rightDegree = convertToyotaTemperatureToT123(rightDegree);
		LOGD("crv ac msg to osd LD = [%d], RD = [%d], WS = [%d], AC = [%d]", leftDegree, rightDegree, windSpeed, acMode);
		//ACToModule_NotifyOsd_DisplayOSDACInfor_Q(leftDegree, rightDegree, windSpeed, acMode);
		airconditionToModule_NotifyOsd_DisplayOSDACInfor(leftDegree, rightDegree, 0x00,uSpeed, acMode);
	}
}


void AcOFFStatusChange(int bOffStatus){
	setUpdateUI(0x00);
	if(bOffStatus){		
		setSerialData(CONTROLID_AIRCONDITION_TEMP_L, (u8*)"",0);
		setSerialData(CONTROLID_AIRCONDITION_TEMP_R, (u8*)"",0);
		setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT, (u8*)"",0);
		setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, 0);
		setDigitalData(CONTROLID_AIRCONDITION_A_C, 0);
		setDigitalData(CONTROLID_AIRCONDITION_AUTO, 0);
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_UP, 0);
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_RIGHT, 0);
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_DOWN, 0);
		setDigitalData(CONTROLID_AIRCONDITION_MAX_UP, 0);
		setDigitalData(CONTROLID_AIRCONDITION_UP, 0);
		setDigitalData(CONTROLID_AIRCONDITION_CAR_REVOLUTION, 0);
		setDigitalData(CONTROLID_AIRCONDITION_DUAL, 0);
		if(pLocalParam->ucSpeed != 0 || pLocalParam->bSpeedMarkToOSD){
			// osd
			TellToOSD();
		}
		pLocalParam->nOsdStatusMark = 7;
	}
	else{
		unicode16_t leftBuffer[MAX_NUM*2],rightBuffer[MAX_NUM*2];
		int leftLen = ansi_str_to_unicode16((u8*)pLocalParam->leftTemperatureStr, leftBuffer);
		int rightlen = ansi_str_to_unicode16((u8*)pLocalParam->rightTemperatureStr,rightBuffer);

		setSerialData(CONTROLID_AIRCONDITION_TEMP_L, (u8*)leftBuffer,leftLen*2);
		setSerialData(CONTROLID_AIRCONDITION_TEMP_R, (u8*)rightBuffer,rightlen*2);

		setDigitalData(CONTROLID_AIRCONDITION_A_C, pLocalParam->bAc);
		setDigitalData(CONTROLID_AIRCONDITION_AUTO, pLocalParam->iAuTo);
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_UP, pLocalParam->bBackNext);
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_RIGHT, pLocalParam->bFront);
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_DOWN, pLocalParam->bDown);
		setDigitalData(CONTROLID_AIRCONDITION_MAX_UP, pLocalParam->bMax);
		setDigitalData(CONTROLID_AIRCONDITION_UP, pLocalParam->bBackUp);
		setDigitalData(CONTROLID_AIRCONDITION_CAR_REVOLUTION, pLocalParam->bLoop);
		setDigitalData(CONTROLID_AIRCONDITION_DUAL, pLocalParam->bDual);
	}
	setUpdateUI(0x01);
}


#define CONVERT_TO_TEMPERATURE(value)	((value)/100.0 + 10)
void CalculateTemperature(u16 temperature_value, char *temp_str){
	double dTemp;

	dTemp = CONVERT_TO_TEMPERATURE(temperature_value);

	if(dTemp <= 17){
		sprintf(temp_str, "%s", "Lo");
	}
	else if(dTemp >= 27){
		sprintf(temp_str, "%s", "Hi");
	}
	else {
		sprintf(temp_str, "%.1f", dTemp);
	}
	LOGI("temp_str:%s", temp_str);
}

int compareData(char cmd, u16 value){
	int ret = 0;
	switch(cmd){
		case 0x10:	// left
			{
				char leftBuffer[MAX_NUM];
				CalculateTemperature(value, leftBuffer);
				if(strcmp(leftBuffer,pLocalParam->leftTempStr) == 0){
					ret = 1;
				}
				else{
					ret = 0;
				}
			}
			break;
		case 0x11:	// right
			{
				char rightBuffer[MAX_NUM];
				CalculateTemperature(value, rightBuffer);
				if(strcmp(rightBuffer,pLocalParam->rightTempStr) == 0){
					ret = 1;
				}
				else{
					ret = 0;
				}
			}
			break;
		case 0x12:	// speed
			if(value == pLocalParam->ucSpeed){
				ret = 1;
			}
			else{
				ret = 0;
			}
			break;
		case 0x13:
			if(value == pLocalParam->ucAcState){
				ret = 1;
			}
			else{
				ret = 0;
			}
			break;
		default:
			ret = 0;
			break;
	}

	return ret;
}

void halToAC_LeftTemperature(char resCmd, u16 temp_value){
	unicode16_t tempBuffer[2*MAX_NUM];

	if(pLocalParam->nOsdStatusMark <= 7){
		pLocalParam->nOsdStatusMark++;
	}

	CalculateTemperature(temp_value, pLocalParam->leftTemperatureStr);
	LOGD("pLocalParam->leftTemperatureStr=%s",pLocalParam->leftTemperatureStr);
	setUpdateUI(0x00);
	if(compareData(resCmd, temp_value)){
		if(pLocalParam->bOff){
			setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)"",0);
		}
		else{
			int len =	ansi_str_to_unicode16((u8*)pLocalParam->leftTemperatureStr,tempBuffer);
			setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)tempBuffer,2*len);
		}
	}
	else{
		pLocalParam->leftTempValue = temp_value;
		memcpy(pLocalParam->leftTempStr, pLocalParam->leftTemperatureStr, strlen(pLocalParam->leftTemperatureStr)+1);
		if(pLocalParam->bOff){
			setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)"",0);
		}
		else{
			int len =	ansi_str_to_unicode16((u8*)pLocalParam->leftTemperatureStr,tempBuffer);
			setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)tempBuffer,2*len);
			if(pLocalParam->nOsdStatusMark >= 5){
				TellToOSD();
			}
		}
	}
	setUpdateUI(0x01);
}

void halToAC_RightTemperature(char resCmd, u16 temp_value){
	unicode16_t tempBuffer[2*MAX_NUM];

	if(pLocalParam->nOsdStatusMark <= 7){
		pLocalParam->nOsdStatusMark++;
	}

	CalculateTemperature(temp_value, pLocalParam->rightTemperatureStr);
	LOGD("pLocalParam->rightTemperatureStr=%s",pLocalParam->rightTemperatureStr);
	setUpdateUI(0x00);
	if(compareData(resCmd, temp_value)){
		if(pLocalParam->bOff){
			setSerialData(CONTROLID_AIRCONDITION_TEMP_R,(u8*)"",0);
		}
		else{
			int len =	ansi_str_to_unicode16((u8*)pLocalParam->rightTemperatureStr,tempBuffer);
			setSerialData(CONTROLID_AIRCONDITION_TEMP_R,(u8*)tempBuffer,2*len);
		}
	}
	else{
		pLocalParam->rightTempValue = temp_value;
		memcpy(pLocalParam->rightTempStr, pLocalParam->rightTemperatureStr, strlen(pLocalParam->rightTemperatureStr)+1);
		if(pLocalParam->bOff){
			setSerialData(CONTROLID_AIRCONDITION_TEMP_R,(u8*)"",0);
		}
		else{
			int len =	ansi_str_to_unicode16((u8*)pLocalParam->rightTemperatureStr,tempBuffer);
			setSerialData(CONTROLID_AIRCONDITION_TEMP_R,(u8*)tempBuffer,2*len);
			if(pLocalParam->nOsdStatusMark >= 5){
				TellToOSD();
			}
		}
	}
	setUpdateUI(0x01);
}

void halToAC_Speed(char cmd, unsigned char speed){
	LOGD("halToAC_Speed: speed=%d",speed);
#define AC_SPEED_BUFFER_MAX	16
	char TempStr[AC_SPEED_BUFFER_MAX];
	unicode16_t uTempStr[AC_SPEED_BUFFER_MAX*2];
	if(pLocalParam->nOsdStatusMark <= 7){
		pLocalParam->nOsdStatusMark++;
	}

	if(speed == 1){
		sprintf(TempStr, "%s", "Min");
	}
	else if(speed == 7){
		sprintf(TempStr, "%s", "Max");
	}
	else if(speed == 0){
		memset(TempStr, 0x00, AC_SPEED_BUFFER_MAX);
	}
	else{
		sprintf(TempStr, "%d", speed);
	}

	if(speed != 0){
		pLocalParam->bSpeedMarkToOSD = 1;
	}
	setUpdateUI(0x00);
	if(compareData(cmd, speed)){
		if(pLocalParam->bOff){
			setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT,(u8*)"",0);
			setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, 0);
		}
		else{
			int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
			setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT,(u8*)uTempStr,len*2);
			setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, speed);

		}
	}
	else{
		pLocalParam->ucSpeed = speed;
		if(pLocalParam->bOff){
			setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT,(u8*)"",0);
			setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, 0);
		}
		else{
			int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
			setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT,(u8*)uTempStr,len*2);
			setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, speed);
			if(pLocalParam->nOsdStatusMark >= 5){
				TellToOSD();
			}
		}
	}
	setUpdateUI(0x01);
}

void halToAC_AcStatus(char cmd, unsigned char status){

	if(pLocalParam->nOsdStatusMark <= 7){
			pLocalParam->nOsdStatusMark++;
	}

	pLocalParam->bAc = status;

	if(compareData(cmd, status)){
		if(pLocalParam->bOff){
			setDigitalData(CONTROLID_AIRCONDITION_A_C, 0);

			LOGD("AAAAAAAAAAAAAA");
		}
		else{
			setDigitalData(CONTROLID_AIRCONDITION_A_C, pLocalParam->bAc);
			LOGD("BBBBBBBBBBBBBBB, %X", pLocalParam->bAc);
		}
	}
	else{
		pLocalParam->ucAcState = status;
		if(pLocalParam->bOff){
			setDigitalData(CONTROLID_AIRCONDITION_A_C, 0);
			LOGD("CCCCCCCCCCCCCCCCCCCC");
		}
		else{
			setDigitalData(CONTROLID_AIRCONDITION_A_C, pLocalParam->bAc);
			LOGD("DDDDDDDDDDDDDDDDDDDD %X", pLocalParam->bAc);
			if(pLocalParam->nOsdStatusMark < 6)
				return;

			pLocalParam->bInitAc = 1;

			TellToOSD();
		}
	}
}

void halToAc_AcAutoStatus(unsigned char status){
	pLocalParam->iAuTo = status;
	setAnalogData(CONTROLID_AIRCONDITION_AUTO,pLocalParam->bOff? 0: pLocalParam->iAuTo);
}

void halToAc_AcModeUpStatus(unsigned char status){
	pLocalParam->bBackNext = status;
	setDigitalData(CONTROLID_AIRCONDITION_SEAT_UP, pLocalParam->bOff? 0: pLocalParam->bBackNext);
}

void halToAc_AcModeFrontStatus(unsigned char status){
	pLocalParam->bFront = status;
	setDigitalData(CONTROLID_AIRCONDITION_SEAT_RIGHT, pLocalParam->bOff? 0: pLocalParam->bFront);
}

void halToAc_AcModeDownStatus(unsigned char status){
	pLocalParam->bDown= status;
	setDigitalData(CONTROLID_AIRCONDITION_SEAT_DOWN, pLocalParam->bOff? 0: pLocalParam->bDown);
}

void halToAc_AcMaxStatus(unsigned char status){
	pLocalParam->bMax= status;
	setDigitalData(CONTROLID_AIRCONDITION_MAX_UP, pLocalParam->bOff? 0: pLocalParam->bMax);
}

void halToAc_AcRearStatus(unsigned char status){
	pLocalParam->bBackUp= status;
	setDigitalData(CONTROLID_AIRCONDITION_UP, pLocalParam->bBackUp);
}

void halToAc_AcVaneStatus(unsigned char status){
	pLocalParam->bLoop= status;
	setDigitalData(CONTROLID_AIRCONDITION_CAR_REVOLUTION, pLocalParam->bOff? 0: pLocalParam->bLoop);
}

void halToAc_AcDualStatus(unsigned char status){
	pLocalParam->bDual= status;
	setDigitalData(CONTROLID_AIRCONDITION_DUAL, pLocalParam->bOff? 0: pLocalParam->bDual);
}

void halToAc_AcOFFStatus(unsigned char status){
	pLocalParam->bOff= status;
	setDigitalData(CONTROLID_AIRCONDITION_OFF, pLocalParam->bOff);
	AcOFFStatusChange(pLocalParam->bOff);
}

void halToAc_AcSeatHeatersLeft(unsigned char status)
{
	pLocalParam->seatHeatersLeft = status;
	setAnalogData(CONTROLID_AIRCONDITION_LEFT_HEATED_SEAT_GAUGE, status);
}
void halToAc_AcSeatHeatersRight(unsigned char status)
{
	pLocalParam->seatHeatersRight = status;
	setAnalogData(CONTROLID_AIRCONDITION_RIGHT_HEATED_SEAT_GAUGE, status);
}
void halToAc_AcAc_maxStatus(unsigned char status)
{
	pLocalParam->bAc_max = status;
	setDigitalData(CONTROLID_AIRCONDITION_AC_MAX, status);
}
void halToAc_AcRear_LockStatus(unsigned char status)
{
	pLocalParam->bRear_Lock = status;
	setDigitalData(CONTROLID_AIRCONDITION_REAR, status);
}

int analyseHalMessage_AIRCONDITION(char resCmd, unsigned char *param, unsigned char len){
	#if 1
	int i, index;
	static unsigned char degbuf[2048];
	index = 0;
	for(i = 0; i < len; i++){
		sprintf((char*)&degbuf[index],"%02x ",param[i]);
		index = strlen((char*)degbuf);
	}
	LOGI("----------Module AC------------->>>>>>   halMessage:%02x %s  %d", resCmd, degbuf, param[0]);
	#endif
	switch (resCmd)
	{
		case 0x01://��Դ״̬
		case 0x02://����״̬
			break;
		case 0x10://���¶�
			{
				u16 leftTemp = (param[0] << 8) + param[1];
				halToAC_LeftTemperature(resCmd, leftTemp);
			}
			break;
		case 0x11://���¶�
			{
				u16 rightTemp = (param[0] << 8) + param[1];
				halToAC_RightTemperature(resCmd, rightTemp);
			}
			break;
		case 0x12://speed
			LOGI("============halToAC_Speed before");
			halToAC_Speed(resCmd, param[0]);
			LOGI("============halToAC_Speed after");
			break;
		case 0x13://AC��ť
			halToAC_AcStatus(resCmd, param[0]);
			break;
		case 0x14://�Զ�auto
			halToAc_AcAutoStatus(param[0]);
			break;
		case 0x15://mode up  - back up
			halToAc_AcModeUpStatus(param[0]);
			break;
		case 0x16://mode front
			halToAc_AcModeFrontStatus(param[0]);
			break;
		case 0x17://mode down
			halToAc_AcModeDownStatus(param[0]);
			break;
		case 0x18://max
			halToAc_AcMaxStatus(param[0]);
			break;
		case 0x19://rear - back next //�����
			halToAc_AcRearStatus(param[0]);
			break;
		case 0x1A://vane
			halToAc_AcVaneStatus(param[0]);
			break;
		case 0x1B://off
			halToAc_AcOFFStatus(param[0]);
			break;
		case 0x1C://dual
			halToAc_AcDualStatus(param[0]);
			break;
		case 0x1d://�����μ���
			halToAc_AcSeatHeatersLeft(param[0]);
			break;
		case 0x1e://�����μ���
			halToAc_AcSeatHeatersRight(param[0]);
			break;
		case 0x1f://AC-MAX������07B-17
			halToAc_AcAc_maxStatus(param[0]);
			break;
		case 0x20://REAR_LOCK������07B-17      menu�˵��е�rear
			halToAc_AcRear_LockStatus(param[0]);
			break;
		//case 0x21://MODE----����B50
		//	break;
		default:
			break;
	}
	return true;
}


/********misra funtion*****/
void halToAC_Mistra_Speed(u8 speed)
{ 
	LOGD("halToAC_Speed: speed=%d",speed); 

	if(speed == pLocalParam->ucSpeed)
		return;
	
	#define AC_SPEED_BUFFER_MAX	16 
	char TempStr[AC_SPEED_BUFFER_MAX];
	unicode16_t uTempStr[AC_SPEED_BUFFER_MAX*2];

	if(speed == 0xFD)
	{ 
		sprintf(TempStr, "%s", "Min");
		speed = 1;
	}
	else if(speed == 0xFE)
	{ 
		sprintf(TempStr, "%s", "Max");
		speed = 8;
	}
	else if(speed == 0)
	{ 
		memset(TempStr, 0x00, AC_SPEED_BUFFER_MAX);
			
	}
	else
	{ 
		sprintf(TempStr, "%d", speed);
	}
	setUpdateUI(0x00);
	pLocalParam->ucSpeed = speed;
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT,(u8*)uTempStr,len*2);
	setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, speed);
	mistraToOSD();
	setUpdateUI(0x01);
}

void halToAC_Mistra_LeftTemperature(char resCmd, u16 temp_value){
	if(temp_value == pLocalParam->leftTempValue)
		return;
		
	unicode16_t tempBuffer[2*MAX_NUM];

	if(pLocalParam->nOsdStatusMark <= 7){
		pLocalParam->nOsdStatusMark++;
	}
	mistra_CalculateTemperature(temp_value, pLocalParam->leftTemperatureStr);
	setUpdateUI(0x00);
	pLocalParam->leftTempValue = temp_value;
	memcpy(pLocalParam->leftTempStr, pLocalParam->leftTemperatureStr, strlen(pLocalParam->leftTemperatureStr)+1);
	if(pLocalParam->bOff){
		setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)"",0);
	}
	else{
		int len =	ansi_str_to_unicode16((u8*)pLocalParam->leftTemperatureStr,tempBuffer);
		setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)tempBuffer,2*len);
		mistraToOSD();	
	}
	
	setUpdateUI(0x01);
}

void halToAC_Mistra_RightTemperature(char resCmd, u16 temp_value){

	if(temp_value == pLocalParam->rightTempValue)
		return;
	
	unicode16_t tempBuffer[2*MAX_NUM];

	if(pLocalParam->nOsdStatusMark <= 7){
		pLocalParam->nOsdStatusMark++;
	}

	mistra_CalculateTemperature(temp_value, pLocalParam->rightTemperatureStr);
	setUpdateUI(0x00);
	
	pLocalParam->rightTempValue = temp_value;
	
		
	memcpy(pLocalParam->rightTempStr, pLocalParam->rightTemperatureStr, strlen(pLocalParam->rightTemperatureStr)+1);
	if(pLocalParam->bOff){
		setSerialData(CONTROLID_AIRCONDITION_TEMP_R,(u8*)"",0);
	}
	else{
		int len =	ansi_str_to_unicode16((u8*)pLocalParam->rightTemperatureStr,tempBuffer);
		setSerialData(CONTROLID_AIRCONDITION_TEMP_R,(u8*)tempBuffer,2*len);	
		mistraToOSD();	
	}
	setUpdateUI(0x01);
}

u8 MistraConvertSpeedTo123(u8 speed){
	if(speed==1)
		speed=0xFD;
	if(speed==8)
		speed=0xFE;
	
	return speed;
}

u16 MistraConvertTemperatureToT123(u16 tempValue){
	if(tempValue == 0xFFFD)
		tempValue=0xFFFD;
	else if(tempValue == 0xFFFF)
		tempValue=0xFFFF;
	
	return tempValue;
}
void mistraToOSD()
{
	u16 LeftTempOSD = 0;
	u16 RightTempOSD = 0;
	u8  uSpeed=0;
	u16 curpage = 0;
	u8 curpagelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curpage,&curpagelen);
	if(curpage != (u16)PAGE_AIRCONDITION )//&& m_pTheApp->m_pCenterParam->ACenable == 1)
	{
		uSpeed=MistraConvertSpeedTo123(pLocalParam->ucSpeed);
		if(uSpeed)pLocalParam->bACAccOn=false;
		if(pLocalParam->bACAccOn&&uSpeed==0)return;
		airconditionToModule_NotifyOsd_DisplayACTitle();
		if (pLocalParam->bOff)
		{
			if(pLocalParam->bACAccOn)return;
			airconditionToModule_NotifyOsd_DisplayOSDACInfor(0xFFFF,0xFFFF,0,0xFF,0x00);//Set_OSDOFF();
			return;
		}

		LeftTempOSD=MistraConvertTemperatureToT123(pLocalParam->leftTempValue);
		RightTempOSD=MistraConvertTemperatureToT123(pLocalParam->rightTempValue);
		airconditionToModule_NotifyOsd_DisplayOSDACInfor(LeftTempOSD,RightTempOSD,0x00,uSpeed,pLocalParam->ucMistraAOrCState);
	}
}
int HexToDec(uint16_t hex)
{
	uint8_t hex4,hex3,hex2,hex1;

	hex4 = hex >> 6;
	hex3 = (hex &0x3f) >>5;
	hex2 = (hex &0x1f) >>4;
	hex1 = hex &0x0f;
    return ((hex4<<6) + (hex3<<5)+(hex2<<4)+hex1);
}

void mistra_CalculateTemperature(u16 temperature_value, char *temp_str){
	u16 dTemp;
	if(temperature_value == 0xFFFD)
	{
		sprintf(temp_str,"%s","LOW");
	}
	else if(temperature_value == 0xFFFE)
		{
			sprintf(temp_str,"%s","HIGH");
		}
	else
	{
		dTemp = HexToDec(temperature_value);
		temp_str[0] = dTemp/1000 +'0';
		temp_str[1] = dTemp%1000/100 + '0';
		temp_str[2] = '.';
		temp_str[3] = (dTemp%100)/10 + '0';
	}
	
}


/***********Public_ac***************/
void halToPublic_Ac_Switch_status(u8 param)
{
	LOGD("%s ----- 1%x",__FUNCTION__,pLocalParam->acSwitchStatus);
	LOGD("%s ----- 2%x",__FUNCTION__,param);
	if(pLocalParam->acSwitchStatus == param)
		return;
	pLocalParam->acSwitchStatus = param;
	//sendToModuleJniSdk_AcSwitch(param);
	g_pClsAcJniSdk.sendToApp_AcSwitch(param);
	if(param == 0x00 || param == 0xFF)
	{
		initAcPageAfterAcOff();
	}
	else if(param == 0x01)
	{
		initAcPageAfterAcOn();
	}
	publicAcInfoToOSD(pLocalParam->acTempL, pLocalParam->acTempR,pLocalParam->acWindSpeed,pLocalParam->acSwitchStatus);
}

void publicAcInfoToOSD(u16 LeftTemp,u16 RightTemp,u8 uSpeed,u8 uACstate)
{
	u16 LeftTempOSD = 0;
	u16 RightTempOSD = 0;
	
	u16 curpage = 0;
	u8 curpagelen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curpage,&curpagelen);
	if(curpage != (u16)PAGE_AIRCONDITION )
	{
		if (!pLocalParam->acSwitchStatus)
		{
			airconditionToModule_NotifyOsd_DisplayOSDACInfor(0xFFFF,0xFFFF,0,0xFF,0x00);
			return;
		}
		
		if(LeftTemp == pLocalParam->acMaxTemp || LeftTemp == 0xFFF8)
			LeftTempOSD = 0xFFFE;
		else if(LeftTemp == pLocalParam->acMinTemp || LeftTemp == 0xFFF7)
			LeftTempOSD = 0xFFFD;
		else if(LeftTemp == 0xFFF9)
			LeftTempOSD = 0xFFFF;
		else
			LeftTempOSD = LeftTemp;
		
		if(RightTemp == pLocalParam->acMaxTemp || RightTemp == 0xFFF8)
			RightTempOSD = 0xFFFE;
		else if(RightTemp == pLocalParam->acMinTemp || RightTemp == 0xFFF7)
			RightTempOSD = 0xFFFD;
		else if(RightTemp == 0xFFF9)
			RightTempOSD = 0xFFFF;
		else
			RightTempOSD = RightTemp;
		
		if(uSpeed == 0xF9)
			uSpeed = 0xFF;
		else if(uSpeed == 0xF8)
			uSpeed = 0xFE;
		else if(uSpeed == 0xF7)
			uSpeed = 0xFD;
		airconditionToModule_NotifyOsd_DisplayOSDACInfor(LeftTempOSD,RightTempOSD,pLocalParam->acTempDataUnit ,uSpeed,uACstate);
		airconditionToModule_NotifyOsd_DisplayACTitle();
	}
}

void TEMP_L(float f,int sf,u8 Tag,u8 unit)
{
	char szBuf[20] = {0};
	char szUnicodeBuf[50] = {0};
	if(sf == 0xFFF9 || sf == 0xFFFF)
		sprintf(szBuf," ");
	else if(sf == 0xFFF8)
		sprintf(szBuf,"Hi");
	else if(sf == 0xFFF7 )
		sprintf(szBuf,"Lo");
	else if(sf  == 0xFFFA)
	{
		if(Tag)
			sprintf(szBuf, "%3.1f ", f);
		else
			sprintf(szBuf, "%2.0f", f);
	}	
	else 
	{
		if(Tag)
			sprintf(szBuf, "%3.1f ", f);
		else
			sprintf(szBuf, "%2.0f", f);
	}

	if(unit == 0x00)
		setAnalogData(CONTROLID_AIRCONDITION_TEMP_L_ICON,0);
	else if(unit == 0x01)
		setAnalogData(CONTROLID_AIRCONDITION_TEMP_L_ICON,1);
	if(sf == 0xFFF9 || sf == 0xFFFF ||sf == 0xFFF8 || sf == 0xFFF7)
		setVisible(CONTROLID_AIRCONDITION_TEMP_L_ICON,false);
	else
		setVisible(CONTROLID_AIRCONDITION_TEMP_L_ICON,true);
	
	int len = ansi_str_to_unicode16((u8*)szBuf,(unicode16_t*)szUnicodeBuf); 
	 if(sf  == 0xFFFA)
	 {}
	 else
	 {
		setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)szUnicodeBuf,2*len);
	 }
}

void TEMP_R(float f,int sf,u8 Tag,u8 unit)
{
	char szBuf[20] = {0};
	char szUnicodeBuf[50] = {0};
	if(sf == 0xFFF9 || sf == 0xFFFF)
		sprintf(szBuf," ");
	else if(sf == 0xFFF8)
		sprintf(szBuf,"Hi");
	else if(sf == 0xFFF7 )
		sprintf(szBuf,"Lo");
	else if(sf  == 0xFFFA)
	{
		if(Tag)
			sprintf(szBuf, "%3.1f ", f);
		else
			sprintf(szBuf, "%2.0f", f);
	}	
	else 
	{
		if(Tag)
			sprintf(szBuf, "%3.1f ", f);
		else
			sprintf(szBuf, "%2.0f", f);
	}
	
	if(unit == 0x00)
		setAnalogData(CONTROLID_AIRCONDITION_TEMP_R_ICON,0);
	else if(unit == 0x01)
		setAnalogData(CONTROLID_AIRCONDITION_TEMP_R_ICON,1);
	if(sf == 0xFFF9 || sf == 0xFFFF ||sf == 0xFFF8 || sf == 0xFFF7)
		setVisible(CONTROLID_AIRCONDITION_TEMP_R_ICON,false);
	else
		setVisible(CONTROLID_AIRCONDITION_TEMP_R_ICON,true);
	int len = ansi_str_to_unicode16((u8*)szBuf,(unicode16_t*)szUnicodeBuf); 
	if(sf  == 0xFFFA)
	{}
	else
		setSerialData(CONTROLID_AIRCONDITION_TEMP_R,(u8*)szUnicodeBuf,2*len);
}

void halToAc_ShowAcWindDirection(u8 param)
{
	switch(param)
	{
		case 0x00:
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 1);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
			break;
		case 0x01:
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 1);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
			break;
		case 0x02:
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 1);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
			break;
		case 0x03:
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 1);
			break;
		case 0x04:
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 1);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
			break;
		case 0x05:
			break;
		case 0x07:
		case 0xF9:
		case 0xFF:
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_THE_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_BLOW_FACE_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW_AND_FEET, 0);
			setDigitalData(CONTROLID_AIRMODLE_FRONT_WINDOW, 0);
			break;
		default:break;
	}
}

void DisplayingUI_WindSpeed(u8 s)
{
	#define AC_SPEED_BUFFER_MAX 16 
	char TempStr[AC_SPEED_BUFFER_MAX];
	unicode16_t uTempStr[AC_SPEED_BUFFER_MAX*2];

	if(s  == 0xFF || s == 0 || s == 0xF9)
	{
		sprintf(TempStr, "%s", " ");
		s = 0;
	}
	else if(s  == 0xF7)
	{ 
		sprintf(TempStr, "%s", "Min");
	}
	else if(s  == 0xF8)
	{ 
		sprintf(TempStr, "%s", "Max");
	}
	else if(s == 0xFA)
	{ 
		memcpy(TempStr, "%d", pLocalParam->acWindSpeed);
		s = 	pLocalParam->acWindSpeed;
	}
	else
	{ 
		sprintf(TempStr, "%d", s);
	}

	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	if(s == 0xFA)
	{}
	else
	{
		setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT,(u8*)uTempStr,len*2);
		setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, s);
	}

}

void DisplayingUI_RearAcWindSpeed(u8 s)
{
	#define AC_SPEED_BUFFER_MAX 16 
	char TempStr[AC_SPEED_BUFFER_MAX];
	unicode16_t uTempStr[AC_SPEED_BUFFER_MAX*2];

	if(s  == 0xFF || s == 0 || s == 0xF9)
	{
		sprintf(TempStr, "%s", " ");
		s = 0;
	}
	else if(s  == 0xF7)
	{ 
		sprintf(TempStr, "%s", "Min");
		s = pLocalParam->RearAcMinWindSpeed;
	}
	else if(s  == 0xF8)
	{ 
		sprintf(TempStr, "%s", "Max");
		s = pLocalParam->RearAcMaxWindSpeed;
	}
	else if(s == 0xFA)
	{ 
		memcpy(TempStr, "%d", pLocalParam->RearAcWindSpeed);
		s = pLocalParam->RearAcWindSpeed;
	}
	else
	{ 
		sprintf(TempStr, "%d", s);
	}

	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	if(s == 0xFA)
	{
	}
	else
	{
		setAnalogData(CONTROLID_REAR_AIRCONDITION_WIND_SPEED_SCROLL_BAR, s);
	}

}

void halToAC_Public_Ac_LeftTemperature(int temp_value)
{
	if((temp_value > pLocalParam->acMaxTemp  || temp_value <  pLocalParam->acMinTemp) &&
		temp_value != 0xFFF7 && temp_value != 0xFFF8 &&temp_value != 0xFFF9&&
		temp_value != 0xFFFA &&temp_value != 0xFFFF)
		return;
	
	if(temp_value == pLocalParam->acTempL)
		return;

	float TempValue = temp_value/100.0;
	TEMP_L(TempValue,temp_value,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
	
	pLocalParam->acTempL = temp_value;
	if(temp_value == 0xFFF7)
		temp_value = pLocalParam->acMinTemp;
	else if(temp_value == 0xFFF8)
		temp_value = pLocalParam->acMaxTemp;
	else if(temp_value == 0xFFF9)
		temp_value = 0xFFFF;
	publicAcInfoToOSD(temp_value, pLocalParam->acTempR,pLocalParam->acWindSpeed,pLocalParam->acSwitchStatus);
}
void halToAC_Public_Ac_RightTemperature(int temp_value)
{
	if((temp_value > pLocalParam->acMaxTemp ||temp_value <  pLocalParam->acMinTemp)&&
		temp_value != 0xFFF7 && temp_value != 0xFFF8 &&temp_value != 0xFFF9&&
		temp_value != 0xFFFA  &&temp_value != 0xFFFF)
		return;

	if(temp_value == pLocalParam->acTempR)
		return;

	float TempValue = temp_value/100.0;
	TEMP_R(TempValue,temp_value,pLocalParam->acTempDataDigits,pLocalParam->acTempDataUnit);
	pLocalParam->acTempR = temp_value;
	if(temp_value == 0xFFF7)
		temp_value = pLocalParam->acMinTemp;
	else if(temp_value == 0xFFF8)
		temp_value = pLocalParam->acMaxTemp;
	else if(temp_value == 0xFFF9)
		temp_value = 0xFFFF;
	publicAcInfoToOSD(pLocalParam->acTempL, pLocalParam->acTempR,pLocalParam->acWindSpeed,pLocalParam->acSwitchStatus);
}

void halToAC_Public_Ac_WindSpeed(u8 speed)
{ 
	if((speed > pLocalParam->acMaxWindSpeed || speed < pLocalParam->acMinWindSpeed) &&
		speed != 0xF7 && speed != 0xF8 && speed != 0xF9 && speed != 0xFA && speed != 0xFE && speed != 0xFF)
		return;
	if(speed == pLocalParam->acWindSpeed)
		return;
	
	 DisplayingUI_WindSpeed(speed);
	pLocalParam->acWindSpeed = speed;	
	//analysAcWindSpeedAndSendToSdk(pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed,pLocalParam->acWindSpeed);
	g_pClsAcJniSdk.analysAcWindSpeedAndSendToApp(pLocalParam->acMinWindSpeed,pLocalParam->acMaxWindSpeed,pLocalParam->acWindSpeed);
	publicAcInfoToOSD(pLocalParam->acTempL, pLocalParam->acTempR,pLocalParam->acWindSpeed,pLocalParam->acSwitchStatus);
}
void halToAc_LoopModeStatus(u8 p)
{
	if(pLocalParam->acLoopMode == p)
		return;
	pLocalParam->acLoopMode = p;
	//sendToModuleJniSdk_AcLoopMode(p);
	g_pClsAcJniSdk.sendToApp_AcLoopMode(p);
	if(p == 0x00)
		setDigitalData(CONTROLID_AIRCONDITION_CAR_REVOLUTION,0);
	else if(p == 0x01)
		setDigitalData(CONTROLID_AIRCONDITION_CAR_REVOLUTION,1);
	halToAc_ShowAcLoopMode(p);
}
void halToAc_ShowAcLoopMode(u8 param)
{
	switch(param)
	{
		case 0x00:
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_OUTER, 1);
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_INNER, 0);
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_AUTO, 0);
			break;
		case 0x01:
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_OUTER, 0);
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_INNER, 1);
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_AUTO, 0);
			break;
		case 0x02:
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_OUTER, 0);
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_INNER, 0);
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_AUTO, 1);
			break;
		case 0xFF:
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_OUTER, 0);
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_INNER, 0);
			setDigitalData(CONTROLID_AIRCONDITION_LOOP_MODE_AUTO, 0);
			break;
		default:break;
	}
}
void halToAc_ACRefrigeration(u8 param)
{
	if(pLocalParam->AorCSwitchStatus == param)
		return;

	if(param == 0x00)
		setDigitalData(CONTROLID_AIRCONDITION_A_C,0);
	else if(param == 0x01)
		setDigitalData(CONTROLID_AIRCONDITION_A_C,1);
	pLocalParam->AorCSwitchStatus = param;
	//sendToModuleJniSdk_AcAorCStatus(param);
	g_pClsAcJniSdk.sendToApp_AcAorCStatus(param);
	//OSD
}
void halToAc_ACmaxRefrigeration(u8 param)
{
	if(pLocalParam->acMaxSwitchStatus == param)
		return;

	if(param == 0x00)
		setDigitalData(CONTROLID_AIRCONDITION_FOCUS_MAX_A_C,0);
	else if(param == 0x01)
		setDigitalData(CONTROLID_AIRCONDITION_FOCUS_MAX_A_C,1);
	pLocalParam->acMaxSwitchStatus = param;
	//sendToModuleJniSdk_AcMaxAorCStatus(param);
	g_pClsAcJniSdk.sendToApp_AcMaxAorCStatus(param);
}
void halToAc_FMistRemovalStatus(u8 p)
{
	if(pLocalParam->acFMistRemovalStatus == p)
		return;

	if(p == 0x00)
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_UP,0);
	else if(p == 0x01)
		setDigitalData(CONTROLID_AIRCONDITION_SEAT_UP,1);
	
	pLocalParam->acFMistRemovalStatus = p;
	//sendToModuleJniSdk_FrontClassMistRemoval(p);
	g_pClsAcJniSdk.sendToApp_FrontClassMistRemoval(p);
}

void halToAc_FrontWindowBlowMaxStatus(u8 p)
{
	if(pLocalParam->acFrontWindowBlowMaxStatus == p)
		return;

	if(p == 0x00)
		setDigitalData(CONTROLID_AIRCONDITION_FRONT_WINDOW_BLOW_MAX_BUTTON,0);
	else if(p == 0x01)
		setDigitalData(CONTROLID_AIRCONDITION_FRONT_WINDOW_BLOW_MAX_BUTTON,1);
	
	pLocalParam->acFrontWindowBlowMaxStatus = p;
}

void halToAc_RMistRemovalStatus(u8 p)
{
	if(pLocalParam->acRMistRemovalStatus == p)
		return;

	if(p == 0x00)
		setDigitalData(CONTROLID_AIRCONDITION_UP,0);
	else if(p == 0x01)
		setDigitalData(CONTROLID_AIRCONDITION_UP,1);
	
	pLocalParam->acRMistRemovalStatus = p;
	sendToModuleJniSdk_RearWindowHeat(p);
	g_pClsAcJniSdk.sendToApp_RearWindowHeat(p);
}

void halToAc_PublicAcWindDirection(u8 p)
{
	#define NO_MODEL 0x07
	if(pLocalParam->acWindMode == p)
		return;
	
	halToAc_ShowAcWindDirection(p);
	if(p == 0xFA)
	{
		setAnalogData(CONTROLID_AIRCONDITION_WIND_MODE_SELECT, pLocalParam->acWindMode*2 );
		setAnalogData(CONTROLID_AIRCONDITION_SHOW_WIND_MODE, pLocalParam->acWindMode*2 );
	}
	else if(p == 0xFF)
	{
		setAnalogData(CONTROLID_AIRCONDITION_WIND_MODE_SELECT, NO_MODEL*2 );
		setAnalogData(CONTROLID_AIRCONDITION_SHOW_WIND_MODE, NO_MODEL*2 );
	}
	else
	{
		setAnalogData(CONTROLID_AIRCONDITION_WIND_MODE_SELECT, p*2 + 1);
		setAnalogData(CONTROLID_AIRCONDITION_SHOW_WIND_MODE, p*2 + 1);
	}
	
	pLocalParam->acWindMode = p;
	sendToModuleJniSdk_AcWindMode(p);
	g_pClsAcJniSdk.sendToApp_AcWindMode(p);
}
void halToAc_PublicAcAutoSwitch(u8 p)
{
	if(pLocalParam->acAUTOSwitchStatus == p)
		return;

	if(p == 0x00)
		setDigitalData(CONTROLID_AIRCONDITION_AUTO,0);
	else if(p == 0x01)
		setDigitalData(CONTROLID_AIRCONDITION_AUTO,1);
	pLocalParam->acAUTOSwitchStatus = p;
	//sendToModuleJniSdk_AcAutoSwitch(p);
	g_pClsAcJniSdk.sendToApp_AcAutoSwitch(p);
}

void halToAc_PublicAcSyncSwitch(u8 param)
{
	if(pLocalParam->acSYNCStatus == param)
		return;
	if(param == 0x00 || param == 0x01)
	{
		setDigitalData(CONTROLID_AIRCONDITION_DUAL ,param);
		pLocalParam->acSYNCStatus = param;
		//sendToModuleJniSdk_AcDual(param);
		g_pClsAcJniSdk.sendToApp_AcDual(param);
	}
}

void halToAc_PublicAcShowBodyButton(u8 p,u8 param)
{
	if(param != 0 && param != 1)
			return;
	switch(p)
	{
		case 0x01:
			setDigitalData(CONTROLID_AIRCONDITION_HEAD_BUTTON,param);
			break;
		case 0x02:
			setDigitalData(CONTROLID_AIRCONDITION_CHEST_BUTTON,param);
			break;
		case 0x03:
			setDigitalData(CONTROLID_AIRCONDITION_FOOT_BUTTON,param);
			break;
		default:break;
	}
}

void initAcPageAfterAcOff()
{
	setDigitalData(CONTROLID_AIRCONDITION_OFF, 1);
}
void initAcPageAfterAcOn()
{
	setDigitalData(CONTROLID_AIRCONDITION_OFF, 0);
}

void halToAc_PublicAcShowHeatSeatStatus(u8 LorR,u8 param)
{
	LOGD("LorR: %x ---- param:%x",LorR,param);
	if(LorR == 0x00 )	
	{
		if(pLocalParam->acHeatSeatStatusL == param)
			return;
		pLocalParam->acHeatSeatStatusL = param;
		//sendToModuleJniSdk_HeatSeatStatus(0x00,param);
		g_pClsAcJniSdk.sendToApp_HeatSeatStatus(0x00,param);
		if(param == 0x01)
			setDigitalData(CONTROLID_AIRCONDITION_HEAT_SEAT_L,1);
		else if(param == 0xFF || param == 0x00)
			setDigitalData(CONTROLID_AIRCONDITION_HEAT_SEAT_L,0);
	}//is Left
	else if(LorR == 0x01)
		{
			if(pLocalParam->acHeatSeatStatusR == param)
				return;
			pLocalParam->acHeatSeatStatusR = param;
			//sendToModuleJniSdk_HeatSeatStatus(0x01,param);
			g_pClsAcJniSdk.sendToApp_HeatSeatStatus(0x01,param);
			if(param == 0x01)
				setDigitalData(CONTROLID_AIRCONDITION_HEAT_SEAT_R,1);
			else if(param == 0xFF || param == 0x00)
				setDigitalData(CONTROLID_AIRCONDITION_HEAT_SEAT_R,0);
		}
}

void halToAc_PublicAcShowHeatSeatGrade(u8 *buf,u8 len)
{
	u8 LorR =buf[0];
	u8 minGrade = buf[1];
	u8 maxGrade = buf[2];
	u8 curGrade = buf[3];
	if((curGrade > maxGrade || curGrade < minGrade) && curGrade != 0xF9 && curGrade != 0xFA && 
		curGrade != 0xFE && curGrade != 0xFF )
		return;
	if(LorR == 0x00 )	
	{
		if(pLocalParam->acHeatSeatGradeL == curGrade)
			return;
		pLocalParam->acHeatSeatGradeL = curGrade;
		if(curGrade == 0xF9 || curGrade == 0xFE){
			setAnalogData(CONTROLID_AIRCONDITION_HEAT_GRADE_SEAT_L,0);
			//sendToModuleJniSdk_HeatSeatGrade(0x00,0);			
			//sendToModuleJniSdk_HeatSeatStatus(0x00,0x00);
			g_pClsAcJniSdk.sendToApp_HeatSeatStatus(0x00,0);
			g_pClsAcJniSdk.sendToApp_HeatSeatGrade(0x00,0);
		}
		else if(curGrade == 0xFF)
		{
			setAnalogData(CONTROLID_AIRCONDITION_HEAT_GRADE_SEAT_L,0);
			//sendToModuleJniSdk_HeatSeatStatus(0x00,0xFF);
			//sendToModuleJniSdk_HeatSeatGrade(0x00,0xFF);
			g_pClsAcJniSdk.sendToApp_HeatSeatStatus(0x00,0xFF);
			g_pClsAcJniSdk.sendToApp_HeatSeatGrade(0x00,0xFF);
		}
		else{
			setAnalogData(CONTROLID_AIRCONDITION_HEAT_GRADE_SEAT_L,curGrade);
			//sendToModuleJniSdk_HeatSeatStatus(0x00,0x01);
			//sendToModuleJniSdk_HeatSeatGrade(0x00,curGrade);
			g_pClsAcJniSdk.sendToApp_HeatSeatStatus(0x00,0x01);
			g_pClsAcJniSdk.sendToApp_HeatSeatGrade(0x00,curGrade);
		}
	}//is Left
	else if(LorR == 0x01)
		{
			if(pLocalParam->acHeatSeatGradeR == curGrade)
			return;
		pLocalParam->acHeatSeatGradeR = curGrade;
		if(curGrade == 0xF9 || curGrade == 0xFE){
			setAnalogData(CONTROLID_AIRCONDITION_HEAT_GRADE_SEAT_R,0);
			//sendToModuleJniSdk_HeatSeatGrade(0x01,0);
			//sendToModuleJniSdk_HeatSeatStatus(0x01,0x00);
			g_pClsAcJniSdk.sendToApp_HeatSeatStatus(0x01,0x00);
			g_pClsAcJniSdk.sendToApp_HeatSeatGrade(0x01,0x00);
			
		}
		else if(curGrade == 0xFF)
		{
			setAnalogData(CONTROLID_AIRCONDITION_HEAT_GRADE_SEAT_R,0);
			//sendToModuleJniSdk_HeatSeatGrade(0x01,0xFF);
			//sendToModuleJniSdk_HeatSeatStatus(0x01,0xFF);
			g_pClsAcJniSdk.sendToApp_HeatSeatStatus(0x01,0xFF);
			g_pClsAcJniSdk.sendToApp_HeatSeatGrade(0x01,0xFF);
		}
		else
		{
			setAnalogData(CONTROLID_AIRCONDITION_HEAT_GRADE_SEAT_R,curGrade);
			//sendToModuleJniSdk_HeatSeatGrade(0x01,curGrade);
			//sendToModuleJniSdk_HeatSeatStatus(0x01,0x01);
			g_pClsAcJniSdk.sendToApp_HeatSeatStatus(0x01,0x01);
			g_pClsAcJniSdk.sendToApp_HeatSeatGrade(0x01,curGrade);
		}
	}
}

void halToPublic_RearAc_Switch_status(u8 param)
{
	LOGD("%s ----- (%x,%x)",__FUNCTION__,pLocalParam->RearAcSwitchStatus,param);
	if(pLocalParam->RearAcSwitchStatus == param)
		return;
	
	pLocalParam->RearAcSwitchStatus = param;
	
	if(param == 0x00 || param == 0xFF)
	{
		DisplayRearAcSwitchStatus(1);
	}
	else if(param == 0x01)
	{
		DisplayRearAcSwitchStatus(0);
	}
}


void halToAC_Public_RearAc_TempValue(u8 p)
{
	LOGD("[%s] p:%x",__FUNCTION__,p);
	if((p > pLocalParam->RearAcMaxTempLevel || p < pLocalParam->RearAcMinTempLevel) &&
		p != 0xF7 && p != 0xF8 && p != 0xF9 && p != 0xFA && p != 0xFE && p != 0xFF)
		return;
	
	if(p == pLocalParam->RearAcTempValue)
		return;

	DisplayUI_RearAcTempRank(p);
	pLocalParam->RearAcTempValue = p;
}

void halToAC_Public_RearAc_WindSpeed(u8 p)
{
	if((p > pLocalParam->RearAcMaxWindSpeed || p < pLocalParam->RearAcMinWindSpeed) &&
		p != 0xF7 && p != 0xF8 && p != 0xF9 && p != 0xFA && p != 0xFE && p != 0xFF)
		return;
	
	if(p == pLocalParam->RearAcWindSpeed)
		return;
	
	DisplayingUI_RearAcWindSpeed(p);
	pLocalParam->RearAcWindSpeed = p;	
}

void halToPublic_RearAc_ControlLock_status(u8 p)
{
	if(pLocalParam->RearAcControlLockStatus == p)
		return;
	
	pLocalParam->RearAcControlLockStatus = p;
	
	if(p == 0x00 || p == 0xFF)
	{
		DisplayRearAcControlLockStatus(1);
	}
	else if(p == 0x01)
	{
		DisplayRearAcControlLockStatus(0);
	}

}

void halToPublic_RearAc_Auto_status(u8 p)
{
	if(pLocalParam->RearAcAutoStatus == p)
		return;
	
	pLocalParam->RearAcAutoStatus = p;

	if(p == 0x00 || p == 0xFF)
	{
		DisplayRearAcAutoStatus(0);
	}
	else if(p == 0x01)
	{
		DisplayRearAcAutoStatus(1);
	}
}

void halToAC_Public_RearAc_Temperature(int temp_value)
{
	if((temp_value > pLocalParam->RearAcMaxTempV  || temp_value <  pLocalParam->RearAcMinTempV) &&
		temp_value != 0xFFF7 && temp_value != 0xFFF8 &&temp_value != 0xFFF9&&
		temp_value != 0xFFFA &&temp_value != 0xFFFF)
		return;
	
	if(temp_value == pLocalParam->RearAcTempV)
		return;

	float TempValue = temp_value/100.0;
	TEMP_Rear(TempValue,temp_value,pLocalParam->RearAcTempDataDigits,pLocalParam->RearAcTempDataUnit);
	
	pLocalParam->RearAcTempV = temp_value;
	if(temp_value == 0xFFF7)
		temp_value = pLocalParam->RearAcMinTempV;
	else if(temp_value == 0xFFF8)
		temp_value = pLocalParam->RearAcMaxTempV;
	else if(temp_value == 0xFFF9)
		temp_value = 0xFFFF;
}

void TEMP_Rear(float f,int sf,u8 Tag,u8 unit)
{
	char szBuf[20] = {0};
	char szUnicodeBuf[50] = {0};
	if(sf == 0xFFF9 || sf == 0xFFFF)
		sprintf(szBuf," ");
	else if(sf == 0xFFF8)
		sprintf(szBuf,"Hi");
	else if(sf == 0xFFF7 )
		sprintf(szBuf,"Lo");
	else if(sf  == 0xFFFA)
	{
		if(Tag)
			sprintf(szBuf, "%3.1f ", f);
		else
			sprintf(szBuf, "%2.0f", f);
	}	
	else 
	{
		if(Tag)
			sprintf(szBuf, "%3.1f ", f);
		else
			sprintf(szBuf, "%2.0f", f);
	}

	if(unit == 0x00)
		setAnalogData(CONTROLID_AIRCONDITION_TEMPERATRUE_UNIT_ICON_BACK_ROW,0);
	else
		setAnalogData(CONTROLID_AIRCONDITION_TEMPERATRUE_UNIT_ICON_BACK_ROW,1);
	if(sf == 0xFFF9 || sf == 0xFFFF ||sf == 0xFFF8 || sf == 0xFFF7)
		setVisible(CONTROLID_AIRCONDITION_TEMPERATRUE_UNIT_ICON_BACK_ROW,false);
	else
		setVisible(CONTROLID_AIRCONDITION_TEMPERATRUE_UNIT_ICON_BACK_ROW,true);
	
	int len = ansi_str_to_unicode16((u8*)szBuf,(unicode16_t*)szUnicodeBuf); 
	 if(sf  == 0xFFFA)
	 {}
	 else
	 {
		setSerialData(CONTROLID_AIRCONDITION_TEMPERATRUE_TXT_BACK_ROW ,(u8*)szUnicodeBuf,2*len);
	 }
}