#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <cutils/properties.h>

#include "global.h"
#include "pageID.h"
#include "param.h"
#include "controlID.h"
#include "halResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "halRequestFunction.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"


extern "C"{
#include "unicodestring.h"
};
static void sercice_preTreatmentACC(char type)
{
	service_to_app_for_preTreatmentACC(type);
}

void service_suspends(char type)
{
	switch(type)
	{
		case 0x00:
			service_all_suspend_info(0x00);
			usleep(300);
			service_property_parameter(0x01);
			//usleep(1500000);
			//service_to_hal_for_suspends(0x00);
			break;
		case 0x01:
			service_all_suspend_info(0x01);
			service_property_parameter(0x01);
			service_to_hal_for_suspends(0x01);
			break;
		case 0x02:
			service_all_suspend_info(0x02);
			service_property_parameter(0x01);
			service_to_hal_for_suspends(0x02);
			break;
		case 0x03:
			service_all_suspend_info(0x03);
			service_property_parameter(0x01);
			service_to_hal_for_suspends(0x03);
			break;
		default:break;
	}
}

static void service_startup(void)
{
	service_all_startup();
}

static void service_powerManagerProcedureThree(char mode)
{
	LOGD("service_powerManagerProcedureThree mode:%x",mode);
	setPowerManagerProcedureThree(mode);
}

void service_GetBarCode(u8* Barcode, u8 len)
{
	u8 pAnsicBuf[128]={0};
	memcpy(pAnsicBuf, Barcode, len);
	memset(pLocalParam->uc_Barcode,0,sizeof(pLocalParam->uc_Barcode));
	memcpy(pLocalParam->uc_Barcode, Barcode, len);
	u8 pUnicodeBuf[256] = {0};
	int nUnicodeBufLen = ansi_str_to_unicode16(pAnsicBuf, (unicode16_t*)pUnicodeBuf);
    setSerialData(CONTROLID_COPYRIGHT_BARCODE,pUnicodeBuf,nUnicodeBufLen*2);
    LOGD("------service_GetBarCode,pLocalParam->c_barcode:%s",pAnsicBuf);

}

void analyseHalMessage_service(char resCmd, unsigned char *param, unsigned char len){
	LOGD("analyseHalMessage_service  resCmd:%x param[0]:%x",resCmd,param[0]);
	switch(resCmd){
		case 0x2B:
			//sercice_preTreatmentACC(param[0]);
			break;
		case 0x2C:
			if(param[0] != 0)
			service_suspends(param[0]);
			break;
		case 0x2D:
			//service_startup();
			break;
		case 0x2E:
			if(param[0] != 0)
			service_powerManagerProcedureThree(param[0]);
			break;
		case 0x30:
			service_GetBarCode(param,len);
		default:
			break;
	}
}
