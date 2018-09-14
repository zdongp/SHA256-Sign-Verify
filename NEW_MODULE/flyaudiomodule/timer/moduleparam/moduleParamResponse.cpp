#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
//#include "timer_interface.h"


#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/poll.h>

#include <linux/input.h>



void moduleParameterInit(void){
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void){
	 LOGD("&&&&&&&&&&&&&&&&&&&& timer moduleParameterReInit");
}

int module_extendInterface(char *buffer, int len){
	LOGD("***********timer module_extendInterface:%x,%x",buffer[0],buffer[1]);
	return 0;
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		default:break;
	}
}
