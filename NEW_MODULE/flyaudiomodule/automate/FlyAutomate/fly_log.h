#pragma once

#include "global.h"
#include <map>
#include <string>
#include <stdlib.h> 
using namespace std;
extern char g_cOutput[];

#define LOG_LV_ERROR			0
#define LOG_LV_DEBUG			1

#define OUTPUT_MAX_LEN		256

#define MODULE_FLAG	"FlyAutomate"

#define fly_printf(...)\
{\
	__android_log_print(ANDROID_LOG_DEBUG, MODULE_FLAG, __VA_ARGS__);\
}

#define FLY_LOG(lvl,formatStr,...)\
{\
	memset(g_cOutput, 0, OUTPUT_MAX_LEN);\
	sprintf(g_cOutput, "%s------>%s", __PRETTY_FUNCTION__, formatStr);\
	fly_printf(g_cOutput, __VA_ARGS__);\
}

#define FLY_LOG_FORC(lvl,formatStr,...)\
{\
	memset(g_cOutput, 0, OUTPUT_MAX_LEN);\
	sprintf(g_cOutput, "%s------>%s", __FUNCTION__, formatStr);\
	fly_printf(g_cOutput, __VA_ARGS__);\
}

void TransformIntegerToAcsii(u8* pDest, u32 iSrc, u8 ucStep, u8 ucLen);
int TransformAcsiiToInteger(u8* pSrc, u8 ucLen);