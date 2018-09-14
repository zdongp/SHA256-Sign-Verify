#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halResponseFunction.h"
#include "appRequestCommand.h"

extern "C"{
#include "unicodestring.h"
};
void service_to_app_for_preTreatmentACC(u8 type)
{
	u8 param[] = {0x2B, 0x00};
	param[1] = type;

	setCommand(0x00000000,param,2);
}


