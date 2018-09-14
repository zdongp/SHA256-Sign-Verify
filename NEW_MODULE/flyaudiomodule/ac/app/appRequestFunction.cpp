#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "halResponseFunction.h"

#include "math.h"
extern "C"{
#include "unicodestring.h"
};


void appRequest_refreshACDoor_PowerSupply(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_POWER_SUPPLY, state);
}

void appRequest_refreshAC_SYNC_Mode(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_SYNC, state);
}

void appRequest_refreshAOrCMode(u8 State){
	setDigitalData(CONTROLID_AIRCONDITION_A_C,State);
}

void appRequest_refreshuinnerLoopStatus(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_CAR_REVOLUTION, state);
}
void appRequest_refreshAcOffStatus(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_ON, state);
}

void appRequest_refreshColdMode(u8 mode)
{
	setDigitalData(CONTROLID_AIRCONDITION_COLD_MODE, mode);
}

void appRequest_refreshRearWindowsHeatMode(u8 mode)
{
	setDigitalData(CONTROLID_AIRCONDITION_UP, mode);
}

void appRequest_refreshWindToWindowMode(u8 mode)
{
	setDigitalData(CONTROLID_AIRCONDITION_SEAT_UP, mode);
}

void appRequest_refreshWindToFaceMode(u8 mode)
{
       setDigitalData(CONTROLID_AIRCONDITION_SEAT_RIGHT, mode);
}

void appRequest_refreshWindToFeetMode(u8 mode)
{
       setDigitalData(CONTROLID_AIRCONDITION_SEAT_DOWN, mode);
}

void appRequest_refreshLeftSeatHeat(u8 p)
{
	   setAnalogData(CONTROLID_AIRCONDITION_LEFT_HEATED_SEAT_GAUGE, p);
}

void appRequest_refreshRightSeatHeat(u8 p)
{
	   setAnalogData(CONTROLID_AIRCONDITION_RIGHT_HEATED_SEAT_GAUGE, p);
}

void appRequest_refreshOutRecycleMode(u8 mode)
{
	setAnalogData(CONTROLID_AIRCONDITION_OUT_RECYCLE, mode);
}

void appRequest_refreshACDoor(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_OFF, state);
}

void appRequest_refreshAutoMode(u8 mode)
{
	setDigitalData(CONTROLID_AIRCONDITION_AUTO, mode);
}

void appRequest_refreshWindFace(u8 face)
{
	setAnalogData (CONTROLID_AIRCONDITION_SEAT_RIGHT_OR_DOWN, face);
}

void appRequest_refreshWindSpeedLevel(u8 level)
{
	setAnalogData(CONTROLID_AIRCONDITION_FOCUS_PROGRESSBAR, level);

	char szMsg[20] = {0};
	if(level == 1)
	sprintf(szMsg, "%s", "Min");
	else if(level == 7)
	sprintf(szMsg, "%s", "Max");
	else if(level == 0)
	sprintf(szMsg, "%s", DEFAULT_N_A_GOLF);
	else
	sprintf(szMsg, "%d", level);
	setAnsiSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT, (u8*)szMsg, strlen(szMsg));

}

void appRequest_refreshDegreeCtrlMode(u8 mode)
{
	setAnalogData(CONTROLID_AIRCONDITION_DOUBLE_CTRL, mode);
}



void appRequest_fks_refreshLeftTemple(float t)
{
	LOGD("t:%f",t);
	char szBuf[20] = {0};
	char szUnicodeBuf[50] = {0};
	if( fabs(t-30.0)<0.000001 )
		sprintf(szBuf,"Hi");
	else if( fabs(t-15.0)<0.000001 )
		sprintf(szBuf,"Lo");
	else if(fabs(t - 127.5) <0.000001)
		sprintf(szBuf," ");
	else 
		sprintf(szBuf, "%3.1f ", t);
	int len =	ansi_str_to_unicode16((u8*)szBuf,(unicode16_t*)szUnicodeBuf);
		
	setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)szUnicodeBuf,2*len);
	fks_TellToOSD();
}

void appRequest_fks_refreshRightTemple(float t)
{
	char szBuf[20] = {0};
	char szUnicodeBuf[50] = {0};
	if( fabs(t-30.0)<0.000001 )
		sprintf(szBuf,"Hi");
	else if( fabs(t-15.0)<0.000001 )
		sprintf(szBuf,"Lo");
	else if(fabs(t - 127.5) <0.000001)
		sprintf(szBuf," ");
	else 
		sprintf(szBuf, "%3.1f ", t);

	int len =	ansi_str_to_unicode16((u8*)szBuf,(unicode16_t*)szUnicodeBuf);
		
	setSerialData(CONTROLID_AIRCONDITION_TEMP_R ,(u8*)szUnicodeBuf,2*len);
	fks_TellToOSD();
}
void appRequest_fks_refreshDownStatus(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_SEAT_DOWN, state);
}
void appRequest_fks_refreshFrontStatus(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_SEAT_RIGHT, state);
}
void appRequest_fks_refreshAcMaxStatus(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_FOCUS_MAX_A_C, state);
}
void appRequest_fks_refreshMaxUpStatus(u8 state)
{
	setDigitalData(CONTROLID_AIRCONDITION_MAX_UP, state);
}

/**********************************************toyota***************************************************/
void appRequest_toyota_refreshAcSpeed(u8 speed)
{
	LOGD("toyota AcSpeed: windspeed=%d",speed);
	#define AC_SPEED_BUFFER_MAX	16
	char TempStr[AC_SPEED_BUFFER_MAX];
	unicode16_t uTempStr[AC_SPEED_BUFFER_MAX*2];

	if(speed == 0x0E){
		appRequest_refreshWindSpeedLevel(0);
		return;
	}
	else if(speed == 1){
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
		
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT,(u8*)uTempStr,len*2);
	appRequest_refreshWindSpeedLevel(speed);
	toyota_TellToOSD();

}

void appRequest_toyota_refreshLeftTemple(int t)
{
	LOGD("toyota LeftTemple:%x",t);
	char szBuf[20] = {0};
	char szUnicodeBuf[50] = {0};

	if(t==0x39)
	{
		setSerialData(CONTROLID_AIRCONDITION_TEMP_L, (u8*)"",0);
		pLocalParam->usToyotaLeftTempOSD = 35*100;
		return;
	}
	else if(t==0x37)
	{
		sprintf(szBuf,"Hi");
		pLocalParam->usToyotaLeftTempOSD = 34*100;
	}
	else if(t==0)
	{
		sprintf(szBuf,"Lo");
		pLocalParam->usToyotaLeftTempOSD = 0*100;
	}
	else if(t>=0x05 && t <= 0x21)
	{
		float curT = 0;
		curT = t;
		curT = 18+(curT-5)/2;
		LOGD("curT:%f",curT);
		sprintf(szBuf, "%3.1f ",curT);
		
		pLocalParam->usToyotaLeftTempOSD=curT*100;
	}
	
	int len = ansi_str_to_unicode16((u8*)szBuf,(unicode16_t*)szUnicodeBuf);
	setSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)szUnicodeBuf,2*len);

	toyota_TellToOSD();

}

void appRequest_toyota_refreshRightTemple(int t)
{
	LOGD("toyota RightTemple:%x",t);
	char szBuf[20] = {0};
	char szUnicodeBuf[50] = {0};

	if(t==0x39)
	{
		setSerialData(CONTROLID_AIRCONDITION_TEMP_R, (u8*)"",0);
		pLocalParam->usToyotaRightTempOSD=35*100;
		return;
	}
	else if(t==0x37)
	{
		sprintf(szBuf,"Hi");
		pLocalParam->usToyotaRightTempOSD=34*100;
	}
	else if(t==0)
	{
		sprintf(szBuf,"Lo");
		pLocalParam->usToyotaRightTempOSD=0*100;
	}
	else if(t>=0x05 && t <= 0x21)
	{
		float curT = 0;
		curT = t;
		curT = 18+(curT-5)/2;
		LOGD("curT:%f",curT);
		sprintf(szBuf, "%3.1f ",curT);
		pLocalParam->usToyotaRightTempOSD=curT*100;
	}
	
	int len = ansi_str_to_unicode16((u8*)szBuf,(unicode16_t*)szUnicodeBuf);
	setSerialData(CONTROLID_AIRCONDITION_TEMP_R ,(u8*)szUnicodeBuf,2*len);
	
	toyota_TellToOSD();
}


/***************************************************************************************************/


//////BYD//////////////////////////////////////////////////////////////////////////////////////////

void appRequest_byd_refreshLeftTemprature(int degree)
{
	char ansiBuf[10] = {0};
	appRequest_byd_degree_num2string(degree, ansiBuf);
	setAnsiSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)ansiBuf, strlen((char*)ansiBuf));
}

void appRequest_byd_refreshRightTemprature(int degree)
{
	char ansiBuf[10] = {0};
	appRequest_byd_degree_num2string(degree, ansiBuf);
	setAnsiSerialData(CONTROLID_AIRCONDITION_TEMP_R ,(u8*)ansiBuf, strlen((char*)ansiBuf));
}

void appRequest_byd_refreshCarGroundDegree(int degree)
{
	char ansiBuf[10] = {0};
	appRequest_byd_degree_num2string(degree, ansiBuf);
	setAnsiSerialData(CONTROLID_AIRCONDITION_DEGREE_OF_OUTDOOR ,(u8*)ansiBuf, strlen((char*)ansiBuf));
}

void appRequest_byd_degree_num2string(int in, char *pOut)
{
	if (in == 0xFF)
	{
		sprintf((char*)pOut, "%s", "N/A");
		return ;
	}
	
	if (in <= 0x11)
		sprintf((char*)pOut, "%s", "Lo");
	else if (in >= 0x21)
		sprintf((char*)pOut, "%s", "Hi");
	else
		sprintf((char*)pOut,"%d", in);
}

//////////////////////////////////////////////////////////////////////////
void appRequest_golf_refreshLeftTemprature(int degree)
{
       char ansiBuf[20] = {0};
       appRequest_golf_degree_num2string(degree, ansiBuf);
       if(degree==0xFF||degree==0||degree==0xFE)
           setAnsiSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)ansiBuf, strlen((char*)ansiBuf));
       else
       {
          	   u8 ansiBuf[64] = {0};
          	   u8 unicBuf[32] = {0};
          	   wchar_t wcharBuf_C[10] = L"℃";
                 wchar_t wcharBuf_F[10] = L"℉";
          	   if (pLocalParam->e_golf_ac_degree_unit == AC_DEGREE_UNIT_C)
          	     	sprintf((char*) ansiBuf,"%.1lf", ((degree - 0x3C) + 160) * 0.1);
          	    else
          	        sprintf((char*) ansiBuf,"%d", (degree - 0x28) / 4 + 60);
          	   u32 dwUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicBuf);
          	   if (pLocalParam->e_golf_ac_degree_unit == AC_DEGREE_UNIT_C)
          	       memcpy((char*)unicBuf + dwUnicodeBufLen * 2, (char*)wcharBuf_C, 2);
          	   else
          		   memcpy((char*)unicBuf + dwUnicodeBufLen * 2, (char*)wcharBuf_F, 2);
          	   setSerialData(CONTROLID_AIRCONDITION_TEMP_L, (u8*)unicBuf, dwUnicodeBufLen * 2 + 2);
        }
}
void appRequest_golf_refreshRightTemprature(int degree)
{
       char ansiBuf[20] = {0};
       appRequest_golf_degree_num2string(degree, ansiBuf);
       if(degree==0xFF||degree==0||degree==0xFE)
       setAnsiSerialData(CONTROLID_AIRCONDITION_TEMP_R ,(u8*)ansiBuf, strlen((char*)ansiBuf));
       else
       {
    	   u8 ansiBuf[64] = {0};
    	   u8 unicBuf[32] = {0};
    	   wchar_t wcharBuf_C[10] = L"℃";
           wchar_t wcharBuf_F[10] = L"℉";
    	   if (pLocalParam->e_golf_ac_degree_unit == AC_DEGREE_UNIT_C)
    	     	sprintf((char*) ansiBuf,"%.1lf", ((degree - 0x3C) + 160) * 0.1);
    	    else
    	        sprintf((char*) ansiBuf,"%d", (degree - 0x28) / 4 + 60);
    	   u32 dwUnicodeBufLen = ansi_str_to_unicode16(ansiBuf, (unicode16_t*)unicBuf);
    	   if (pLocalParam->e_golf_ac_degree_unit == AC_DEGREE_UNIT_C)
    	       memcpy((char*)unicBuf + dwUnicodeBufLen * 2, (char*)wcharBuf_C, 2);
    	   else
    		   memcpy((char*)unicBuf + dwUnicodeBufLen * 2, (char*)wcharBuf_F, 2);
    	   setSerialData(CONTROLID_AIRCONDITION_TEMP_R, (u8*)unicBuf, dwUnicodeBufLen * 2 + 2);
       }
}
void appRequest_golf_degree_num2string(int in, char *pOut)
{
       if (in == 0xFF)
       {
               sprintf((char*)pOut, "%s", DEFAULT_N_A_GOLF);
               return ;
      }

      if (in == 0)
               sprintf((char*)pOut, "%s", "Lo");
      else if (in == 0xFE)
              sprintf((char*)pOut, "%s", "Hi");
      else
       {
  		if (pLocalParam->e_golf_ac_degree_unit == AC_DEGREE_UNIT_C)
  			sprintf((char*)pOut,"%.1lf \B0C", ((in - 0x3C) + 160) * 0.1);
  		else
  			sprintf((char*)pOut,"%d \B0F", (in - 0x28) / 4 + 60);
       }
}
//////////////////////////////////////////////////////////////////////////


/****************************CRV***********************************/
void appRequest_crv_refreshWindSpeedLevel(u8 level)
{
	LOGD("CRV_AcSpeed: level=%d",level);
	#define AC_SPEED_BUFFER_MAX	16
	char TempStr[AC_SPEED_BUFFER_MAX];
	unicode16_t uTempStr[AC_SPEED_BUFFER_MAX*2];

	if(level == 1){
		sprintf(TempStr, "%s", "Min");
	}
	else if(level == 7){
		sprintf(TempStr, "%s", "Max");
	}
	else if(level == 0){
		sprintf(TempStr, "%s", "N/A");
	}
	else{
		sprintf(TempStr, "%d", level);
	}
		
	int len = ansi_str_to_unicode16((u8*)TempStr, uTempStr);
	setSerialData(CONTROLID_AIRCONDITION_GAUGE_TEXT,(u8*)uTempStr,len*2);
	appRequest_refreshWindSpeedLevel(level);
}

void appRequest_crv_refreshLeftTemprature(int degree)
{
	char ansiBuf[10] = {0};
	appRequest_crv_degree_num2string(degree, ansiBuf);
	setAnsiSerialData(CONTROLID_AIRCONDITION_TEMP_L ,(u8*)ansiBuf, strlen((char*)ansiBuf));
}

void appRequest_crv_refreshRightTemprature(int degree)
{
	char ansiBuf[10] = {0};
	appRequest_crv_degree_num2string(degree, ansiBuf);
	setAnsiSerialData(CONTROLID_AIRCONDITION_TEMP_R ,(u8*)ansiBuf, strlen((char*)ansiBuf));
}
void appRequest_crv_degree_num2string(int in, char *pOut)
{
	if (in == 0xFF)
	{
		sprintf((char*)pOut, "%s", "N/A");
		return ;
	}
	
	if (in == 2)
		sprintf((char*)pOut, "%s", "Lo");
	else if (in == 1)
		sprintf((char*)pOut, "%s", "Hi");
	else
		sprintf((char*)pOut,"%d", in);
}

/////////////////////////////////////////////////////////////////////////////////////
