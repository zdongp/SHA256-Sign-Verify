#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "appRequestFunction.h"
#include "appResponseCommand.h"
#include "appResponseFunction.h"

#include "param.h"

#include "SteeringWheelStudy.h"

void appInit(void){
	//systemToApp_Init();
}

void appDeInit(void){

}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;
	u8 u8_MouseStatus = 0;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);

	ctrlType = buffer[4];
	u8_MouseStatus = buffer[5];
	paramLen = len - 5;
	param = &buffer[5];

   

	//JumpPage
	short PageID = 0;
	short PageBeginID = CONTROLID_SETUP_JUMPPAGE_ONE >> 8;
	short PageEndID = (short)((CONTROLID_SETUP_JUMPPAGE_END >>8) & 0xFFFF);
	PageID = ctrlId >> 8;
	if(PageID >= PageBeginID && PageID <= PageEndID && buffer[3] == 0x01)
	{
		//appToSys_Setup_JumpPage_MouseUp(PageID);
	}

	bool bRet = pLocalParam->m_clsSteeringWheelStudy.processMouseMsg(ctrlId, (E_MOUSE_STATUS)ctrlType, param, paramLen);
	if (bRet)
	{
		LOGD("[%s] m_clsSteeringWheelStudy", __FUNCTION__);
		return;
	}

	LOGD("[DYB] Module_system analyseAppMessage ctrlId:%x  ctrlType:%x",ctrlId,ctrlType);
	switch(ctrlType)
    {
		case UIACTION_MOUSEDOWN:
			apptoSys_hadleDown(ctrlId,u8_MouseStatus,param,paramLen);
			break;
		 case UIACTION_MOUSEUP:
			appToSys_handleUp(ctrlId,u8_MouseStatus,param,paramLen);
			break;
		case UIACTION_MOUSETIMER:
			appToSys_handleTimer(ctrlId,u8_MouseStatus,param,paramLen);
			break;
		case UIACTION_MOUSECANCEL:
			appToSys_handleCancel(ctrlId,u8_MouseStatus,param,paramLen);
			break;
		default:break;
    }
	
}



