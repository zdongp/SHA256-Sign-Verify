#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/select.h>
#include <assert.h>
#include <sys/types.h>

#include "types_def.h"
#include "hardware.h"
#include "commonFunc.h"
#include "flymoduleApi.h"


#include "moduleCommApi.h"

#define LOG_TAG "TEST_MODULE"


#define		LOCAL_MODULE_ID			0x01
#define		LOCAL_MODULE_NAME		"FlyTest"
#define		LOCAL_HMODULE_AUTOHR	"flyaudio"



device_command_t *command_list;


int sendMsgToJNI(unsigned char *buf, int len)
{
	BYTE msg[256] = {MSG_TO_JNI};
	if (len > 255-1)
	{
		DBG0(debugPrintf("sendMsgToJNI len too long\n"););
		return 0;
	}
	memcpy(&msg[1], buf, len);
	return command_set(MODULE_ID_MAIN_SERVICE, msg, len+1);
}

int sendMsgToHAL(unsigned char *buf, int len, unsigned HALID)
{
	BYTE msg[256] = {MSG_TO_HAL, HALID};
	if (len > 255-2)
	{
		DBG0(debugPrintf("sendMsgToHAL len too long\n"););
		return 0;
	}
	memcpy(&msg[2], buf, len);

	return command_set(MODULE_ID_MAIN_SERVICE, msg, len+2);
}


static int halMsgProc(unsigned char *buf, int len)
{
	sendMsgToJNI(buf, len);

	return 0;
}

static int jniMsgProc(unsigned char *buf, int len)
{
	debugBuf("jniMsgProc:", buf, len);
	sendMsgToHAL(buf, len, HALMSG_MODULE);
//	sendMsgToJNI(buf, len);

	return 0;
}

static int fly_device_get(unsigned char *buf, int len)
{

	debugPrintf("so=%s id=%d get\n", LOCAL_MODULE_NAME, LOCAL_MODULE_ID);

    return 0;
}

static int fly_device_set(unsigned char *buf, int len)
{
	debugBuf("fly_device_set:", buf, len);

	switch (buf[0])
	{
		case MSG_FROM_JNI:
			jniMsgProc(&buf[1], len-1);
			break;
		case MSG_FROM_HAL:
			halMsgProc(&buf[1], len-1);
			break;
		default:
			break;		
	}

    return 0;
}

static int fly_device_close(struct hw_device_t* device)
{
    return 0;
}


static int fly_device_open(const struct hw_module_t* module, const char* id, struct hw_device_t* device)
{

	device->tag =  HARDWARE_DEVICE_TAG;
    device->version = 0;
    device->module = (struct hw_module_t*)module;

	device->close = fly_device_close;

	command_list = device->command_list;
	command_register_set(LOCAL_MODULE_ID, fly_device_set);
	command_register_get(LOCAL_MODULE_ID, fly_device_get);

	debugTagSet(LOG_TAG);

    debugPrintf("fly_device_open id --> %s\n", id);

	return TRUE;
}


static struct hw_module_methods_t device_module_methods = {
    .open=fly_device_open
};


struct hw_module_t HAL_MODULE_INFO_SYM = {
	.tag = HARDWARE_MODULE_TAG,
	.version_major = 1,
	.version_minor = 0,
	.id = LOCAL_MODULE_ID,
	.name = LOCAL_MODULE_NAME,
	.author = LOCAL_HMODULE_AUTOHR,
	.methods = &device_module_methods,

};
