#ifndef __FLY_MODULE_COMMON_H
#define __FLY_MODULE_COMMON_H

#include <flytypes.h>
#include <sys/cdefs.h>

#include "hardware.h"

#include "flyaudiomodule/messageQueue.h"
#include "flyaudiomodule/moduleParamStruct.h"

__BEGIN_DECLS

//#define MTK_ANDROID_CODE

typedef void (*writeHalMessage)(halMessage_t*);
typedef void (*writeAppMessage)(appMessage_t*);
typedef void (*writeModMessage)(moduleMessage_t*);
typedef void (*GetModParam)(moduleParam_t*);
typedef void (*SetTimerMessage)(moduleMessage_t *);

typedef struct
{
	writeHalMessage setHal;//sendTo Hal
	writeAppMessage setApp;//sendTo App
	writeModMessage setMod;//sendTo Module
	GetModParam getMod;//getModuleParam
	SetTimerMessage setTimer;
}mod_callback_t;

//struct flymodule_module_t
//{
//	struct fa_module_t module;
//};

struct flymodule_device_t
{
	//struct fa_device_t dev;
	int (*setCallBack)(const moduleid_t mid, mod_callback_t* mCallback);
	void (*writeMessage)(const flymessage_t *pFlyMsg);
	void (*getModuleParam)(moduleParam_t *p);
	void (*init)(void);
	void (*reInit)(void);
	int (*ioctl)(char *p, int len);
	int (*LogPermission)(int enable);
};






//---------------- COMMAND -------------------

#define MSG_TO_JNI		0xFF
#define MSG_TO_HAL		0xFE

#define MSG_FROM_JNI	0xFF
#define MSG_FROM_HAL	0xFE

//-------------------------------------------

#define command_register_set(Index,set_command)	(command_list[Index].set=set_command)
#define command_register_get(Index,get_command) (command_list[Index].get=get_command)

#define command_set(Index,buf,len)	command_list[Index].set(buf,len)
#define command_get(Index,buf,len)	command_list[Index].get(buf,len)



__END_DECLS

#endif	// end __FLY_MODULE_COMMON_H
