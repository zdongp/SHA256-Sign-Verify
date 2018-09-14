#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "halRequestFunction.h"
#include "param.h"
#include "pageID.h"
#include "flytypes.h"


#include "halRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "halResponseFunction.h"

void OtherModuleToService_AnalyseCenter(u8 *param)
{
	u8 u8_cmd = param[0];
	switch(u8_cmd)
	{
		case 0x00:
		{
			if(param[1] == 0x01)
			{
				service_to_hal_TheNewStructure(0x01);//���
				
			}
			else if(param[1]==0x00)
			{
				service_to_hal_TheNewStructure(0x00);//��
			}
		}
		break;
		case 0x3c:
		{
			if(param[1] == 0x01)
			{
				service_suspends(0x00);
				service_to_hal_ACCOff_30s_TheNewStructure(0x00);//acc_off
			}
			else if(param[1]==0x00)
			{
				service_to_hal_ACCOff_30s_TheNewStructure(0x01);//acc_on
				service_all_startup();
			}
		}
		break;
		case 0x3d:
			service_to_hal_FastToSwitchMachine_60s_TheNewStructure(param[1]);
		break;
		case 0xe0:
			service_to_hal_15Days_reset(&param[1]);
			break;
		default:break;
	}
}

void OtherModuleToService_AnalyseSystem(u8 *param,u8 uLen)
{
	u8 u8_cmd = param[0];
	switch(u8_cmd)
	{
		case 0x00:  /*����ѡ�����������*/
			service_all_suspend_info(0x02);
			service_property_parameter(0x01);
			break;
		case 0x01:
			service_all_standby_info(param[1]);
			break;
		case 0x02:
			service_GetBarCode(param + 1,uLen - 1);
			break;
		default:
			break;
	}
}

void OtherModuleToService_analyseBT(u8 *p)
{
	u8 szCmd = p[0];
	switch(szCmd)
		{
			case 0x2E:
				{
					serviceToModule_setAllModuleLogOpen(p[1]);
					LOGD("[OtherModuleToService_analyseBT] p[1] = [0x%x]", p[1]);
				}
			break;
		}
}

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	LOGD("Module_service analyseOtherModuleMessage sendModuleId:%x param[0]:%x param[1]:%x",sendModuleId,param[0],param[1]);
	switch(sendModuleId){
		case MODULE_ID_KEY:
			break;
		case MODULE_ID_CENTER:
			OtherModuleToService_AnalyseCenter(param);
			break;
		case MODULE_ID_SYSTEM:
			OtherModuleToService_AnalyseSystem(param,len);
			break;
		case MODULE_ID_BT:
			OtherModuleToService_analyseBT(param);
			break;
		default:
			break;
	}
}

void analyseTimerHandleMessage(u8 *p, u8 len)
{
}

