#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "timer_interface.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"
void analyseHalMessage_TPMS(char resCmd, unsigned char *param, unsigned char len)
{


    switch(resCmd)
    {
    
    case HALTOTPMS_INIT_CMD://��Դ״̬
        {
	    	halToTPMS_InitParam(param[0]);   
        }
		break;
    case HALTOTPMS_INIT_STATUS://����״̬
        {
	   		halToTPMS_InitStatus(param[0]);    
        }
		break;
    case HALTOTPMS_PAIR_MODE://���
        {
	    	halToTPMS_PairMode(param[0]);	    
        }
		break;
    case HALTOTPMS_FL_UPDATA:
    case HALTOTPMS_FR_UPDATA:
    case HALTOTPMS_RL_UPDATA:
    case HALTOTPMS_RR_UPDATA:
        {
		halToTPMS_TireSwapDispose(resCmd,param,len);	    
        }
		break;
    default:
        break;	
		
    }
}

void halToTPMS_InitParam(u8 u8_Param)//��Դ״̬
{
}

void halToTPMS_InitStatus(u8 u8_Param)//����״̬
{
	if(u8_Param == 0x00)
		pLocalParam->u8_tpms_bInitState = false;
	else
		pLocalParam->u8_tpms_bInitState = true;

}

void halToTPMS_WhetherExist(u8 u8_Param)
{

}

void halToTPMS_PairMode(u8 u8_Param)//���
{
	LOGD("halToTPMS_PairMode^^^^^^^^^^^^^^^u8_Param:0x0%x", u8_Param);
	
	if(u8_Param == 0x00){//exit pair mode
	    localParam.ucTpmsPairStatus = 0;
		Pair_Mode(false);
	}else if(u8_Param == 0x01){
	    localParam.ucTpmsPairStatus = 1;
		Pair_Mode(true);
	}

}
void halToTPMS_TireSwapDispose(char resCmd, unsigned char *param, unsigned char len)
{
	u8 tireNub=resCmd-HALTOTPMS_FL_UPDATA;
	u8 swapTireNub=0;
	for(swapTireNub=0;swapTireNub<4;swapTireNub++)
		if(CONTROLID_TPMS_FL_SIGN+16*tireNub == pLocalParam->tireSignIDArr[swapTireNub])
			break;
	//LOGD("halToTPMS_TireSwapDispose:tireNub:%d,swapTireNub:%d",tireNub,swapTireNub);
	if(swapTireNub == 4)
		LOGD("ERROR:halToTPMS_TireSwapDispose");
	halToTPMS_UpdataTrieInfo(param,len,swapTireNub);
}

//������̥���
void halToTPMS_UpdataTrieInfo(u8 *pBuf, u8 len , u8 TireNub)
{

	u8 Conmand_Type;
	u8 Conmand_Data;
	
	Conmand_Type= pBuf[0];
 	Conmand_Data= pBuf[1];

	if(0x00 == Conmand_Type)//�͵籨�� battery state
	{
		LOGD("[%s]  local_TPMS_Data[%d].battery = [%d]",__FUNCTION__, TireNub, Conmand_Type);

		if(Conmand_Data == 0x01)
		{
			local_TPMS_Data[TireNub].u32_battery_low_power_times += 1;
			if (local_TPMS_Data[TireNub].u32_battery_low_power_times >= TPMS_UP_TO_WARMING_TIMES)
			{
		    		local_TPMS_Data[TireNub].b_battery_low = true;
				local_TPMS_Data[TireNub].u32_battery_low_power_times = TPMS_UP_TO_WARMING_TIMES;
				LOGD("the battery is low power!!!!~~~~~~~~~~~");
			}
			else 
			{
				local_TPMS_Data[TireNub].b_battery_low = local_TPMS_Data[TireNub].b_pre_battery_low;
			}
		}
		else if(Conmand_Data == 0x00)
		{
			local_TPMS_Data[TireNub].b_battery_low = false;
			local_TPMS_Data[TireNub].b_pre_battery_low = local_TPMS_Data[TireNub].b_battery_low;
			local_TPMS_Data[TireNub].u32_battery_low_power_times = 0;
			LOGD("~~~~~~~~~~~~~~~~~~the battery is normal!");
		}

		UpdateBattery(CONTROLID_TPMS_FL_SIGN+16*TireNub+1,local_TPMS_Data[TireNub].b_battery_low);//show low battery image
		
		if(local_TPMS_Data[TireNub].b_battery_low==true)
		{
			Alarm(FL_Power_Low+TireNub);
			LOGD("===============Alarm is ring=============");
		}
		else
		{
			clearAlarmText(FL_Power_Low+TireNub);
			LOGD("*******************clear Alarm Text****************");
		}
	}
	else if(0x01 == Conmand_Type) //��ݸ��� pair state 
	{
		LOGD("Conmand_Data=%d   UPDATE",Conmand_Data);
		if(Conmand_Data == 0x01)
		{
		   	local_TPMS_Data[TireNub].b_update = true;
		}
		else if(Conmand_Data == 0x00)
		{
			local_TPMS_Data[TireNub].b_update = false;
		}

		UpdateData(CONTROLID_TPMS_FL_SIGN+16*TireNub,local_TPMS_Data[TireNub].b_update);

		if(!local_TPMS_Data[TireNub].b_update)
		{
			 Clean_TireData(emTire_FL+TireNub);
		}
	}
	else if(0x02 == Conmand_Type) //̥ѹ
	{		
		if(0xFF != Conmand_Data)
		{
				local_TPMS_Data[TireNub].u32_tire_pressure = halToTPMS_PresureData(Conmand_Data);
				LOGD("[%s]  local_TPMS_Data[%d].u32_tire_pressure = [%d]",__FUNCTION__, TireNub, local_TPMS_Data[TireNub].u32_tire_pressure);

				if(local_TPMS_Data[TireNub].u32_tire_pressure >= localParam.u32_tpms_max_alarm_tire_pressure)
				{
					local_TPMS_Data[TireNub].max_pressure_abnormal_times+=1;
					local_TPMS_Data[TireNub].min_pressure_abnormal_times = 0;

					if (local_TPMS_Data[TireNub].max_pressure_abnormal_times >= TPMS_UP_TO_WARMING_TIMES)
					{
						clearAlarmText(FL_Pressure_Low+TireNub);
						Alarm(FL_Pressure_High+TireNub);
						
						local_TPMS_Data[TireNub].max_pressure_abnormal_times = TPMS_UP_TO_WARMING_TIMES;
						LOGD("u32_tire_pressure   MAX_ALARM~~~~~~~~~~~~~~");
					}
					else 
					{
						local_TPMS_Data[TireNub].u32_tire_pressure = local_TPMS_Data[TireNub].u32_pre_tire_pressure;
					}
				}
				
				else if(local_TPMS_Data[TireNub].u32_tire_pressure <= localParam.u32_tpms_min_alarm_tire_pressure)
				{	
					local_TPMS_Data[TireNub].min_pressure_abnormal_times+=1;
					local_TPMS_Data[TireNub].max_pressure_abnormal_times = 0;

					if (local_TPMS_Data[TireNub].min_pressure_abnormal_times >= TPMS_UP_TO_WARMING_TIMES)
					{
						clearAlarmText(FL_Pressure_High+TireNub);
						Alarm(FL_Pressure_Low+TireNub);	
						
						local_TPMS_Data[TireNub].min_pressure_abnormal_times = TPMS_UP_TO_WARMING_TIMES;
						LOGD("~~~~~~~~~~~~~~~MIN_ALARM  u32_tire_pressure");
					}
					else 
					{
						local_TPMS_Data[TireNub].u32_tire_pressure = local_TPMS_Data[TireNub].u32_pre_tire_pressure;
					}
				}
				else if ((local_TPMS_Data[TireNub].u32_tire_pressure > localParam.u32_tpms_min_alarm_tire_pressure) &&
						local_TPMS_Data[TireNub].u32_tire_pressure < localParam.u32_tpms_max_alarm_tire_pressure)
				{
					local_TPMS_Data[TireNub].max_pressure_abnormal_times = 0;
					local_TPMS_Data[TireNub].min_pressure_abnormal_times = 0;
					local_TPMS_Data[TireNub].u32_pre_tire_pressure = local_TPMS_Data[TireNub].u32_tire_pressure;
					
					clearAlarmText(FL_Pressure_Low+TireNub);
					clearAlarmText(FL_Pressure_High+TireNub);
					LOGD("***********************u32_tire_pressure  CLEAR************************");
				}

				tpms_TirePressure_Update(CONTROLID_TPMS_FL_SIGN+16*TireNub+2,local_TPMS_Data[TireNub].u32_tire_pressure);//display fl pressure value
		}
	}
	else if(0x03 == Conmand_Type) //�¶�
	{	
		if(0xFF != Conmand_Data)
		{
			local_TPMS_Data[TireNub].u32_temperature = halToTPMS_TemperatureData(Conmand_Data);//u8
			
			LOGD("local_TPMS_Data[%d].u32_temperature = [%d]", TireNub, local_TPMS_Data[TireNub].u32_temperature);
			if(local_TPMS_Data[TireNub].u32_temperature >= localParam.u32_tpms_max_alarm_temperature)
			{
				local_TPMS_Data[TireNub].u32_temperature_times += 1;
				if (local_TPMS_Data[TireNub].u32_temperature_times >= TPMS_UP_TO_WARMING_TIMES)
				{
					Alarm(FL_Temperature_High+TireNub);	
					local_TPMS_Data[TireNub].u32_temperature_times = TPMS_UP_TO_WARMING_TIMES;
					LOGD("*****************u32_temperature Alarm****************");
				}
				else
				{
					local_TPMS_Data[TireNub].u32_temperature = local_TPMS_Data[TireNub].u32_pre_temperature;
				}
			}
			else
			{
				local_TPMS_Data[TireNub].u32_pre_temperature = local_TPMS_Data[TireNub].u32_temperature;
				local_TPMS_Data[TireNub].u32_temperature_times = 0;

				clearAlarmText(FL_Temperature_High+TireNub);
				LOGD("=================u32_temperature clean Alarm Text================");
			}
			tpms_Temperature_Update(CONTROLID_TPMS_FL_SIGN+16*TireNub+3,local_TPMS_Data[TireNub].u32_temperature);
		}
	}
	/*<<<<<<<<<------------------[BEN] ADD----------------------*/
	//SetTimer(TIME_500MS, 1, TPMS_TIMER_SEND_THE_DATA_OF_TMPS);
	/*-------------------------------END------->>>>>>>>>>>>>>>>*/
}


int  halToTPMS_PresureData(u8 getData)
{

	double tmp=(double)getData*0.491;	
	int returnData=(int)tmp;
	if (tmp-returnData>=0.5){
		returnData=returnData*10+10;
	}else{
		returnData=returnData*10+5;
	}	
	return returnData;
}

int  halToTPMS_TemperatureData(u8 getData)
{
	return tpms_Temperature_F_To_C((double)getData);
}

void Alarm(u8 command)
{

	localParam.u8_CurAlarmValue = command;
	
	switch(pLocalParam->u8_tpms_alarm_type)
	{
		case Alarm_Voice:
			{		
				u16 curpage = 0;
				u8 curpagelen = 0;
			
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8 *)&curpage,(u8 *)&curpagelen);
				
				if(curpage == (u16)PAGE_TPMS){
					
					tpmsToUI_setAlarm_TextShow(command);
				}
				else{
					LOGD("localParam.bCanRing=%d,command=%d",localParam.bCanRing,command);
					if(command<16)return;
					if (localParam.bCanRing)
					{
							localParam.bCanRing = false;
							//tpmsToModule_NotifyOSDT123_ShowTitle();
						    //Set_TPMS_OSD_Control(command);
							StartRing(110);
							SetTimer(TIME_TPMS_RING_FRE_15S, 1, TPMS_TIMER_CTRL_ALARM_FRE);
					}
					tpmsToT123_setAlarm(command);

			//		SetTimer(TIME_5S,1,TPMS_TIMER_HIDDEN);//5000ms
					
					//StopRing();
					
				}
			}
			break;
		case Alarm_Text:
			{
				u16 curpage = 0;
				u8 curpagelen = 0;
			
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8 *)&curpage,(u8 *)&curpagelen);
				
				if(curpage == (u16)PAGE_TPMS){
					
					tpmsToUI_setAlarm_TextShow(command);
				}
				else
				{
					if(command<16)return;
					tpmsToModule_NotifyOSDT123_ShowTitle();
					Set_TPMS_OSD_Control(command);
				}
				
			}
			break;
		case Alarm_Close:
			break;
		default:
			break;
	}
}



