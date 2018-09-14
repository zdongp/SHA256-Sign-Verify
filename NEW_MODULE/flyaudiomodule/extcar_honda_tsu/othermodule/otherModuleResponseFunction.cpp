#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "otherModuleResponseFunction.h"
#include "halRequestFunction.h"

void analyseFormSdkMessageExtcarHondaTsu(u8 *param,u8 len)
{
	extcarToHal_HondaTsu_Data(param,len);
}
