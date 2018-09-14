#ifndef __MODULE_PARAM_STRUCT_H__
#define __MODULE_PARAM_STRUCT_H__

typedef struct
{
	unsigned char moduleID;
	unsigned char paramID;
	unsigned char Reserved;
	unsigned char paramLen;
	unsigned char parambuf[300];	// app message buffer
} MODULEPARAM;


typedef MODULEPARAM		moduleParam_t;

#endif
