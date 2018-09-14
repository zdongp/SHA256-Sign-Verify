#include "global.h"
#include "controlID.h"
#include "param.h"
#include "appRequestFunction.h"
#include "appResponseCommand.h"

void appInit(void){

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

	switch(ctrlType)
	{
		case UIACTION_MOUSEUP:
		   break;
		case UIACTION_MOUSEDOWN:
		default:
		break;
	}
}

