#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseFunction.h"
#include "appRequestFunction.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"

extern "C"{
#include "unicodestring.h"
};

void Get_Bluetooth_PhoneState(unsigned char *param, unsigned char len){

	switch(param[1]){
		case 1:	// dialin
			pLocalParam->udialin = true;
			break;
		case 0:	// nophone
		case 2:	// dialout
		case 3:	// calling
			pLocalParam->udialin = false;
			break;
	}
	BackcarToApp_Inside_ActShowAnswerBox(pLocalParam->udialin);
}

void Get_Bluetooth_CallInfro(unsigned char *param, int len)
{
	int nBufLen = len -1;
	u8 *pBufName = (u8*)malloc(nBufLen);

	if(pBufName == NULL)
		return;

	memcpy(pBufName,&param[1],nBufLen);
	setSerialData(CONTROLID_BACK_VIDEO_PHONE_NUMBER ,(u8 *)pBufName,nBufLen);
	free(pBufName);
	pBufName = NULL;
}
