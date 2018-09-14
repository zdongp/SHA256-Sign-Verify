#ifndef __FLYAUDIO_MODULE_API_INTERNAL_H_
#define __FLYAUDIO_MODULE_API_INTERNAL_H_

#include <flytypes.h>


void makeAndSendMessageToHal(moduleid_t halId, u8 *buf, int len);
void makeAndSendTimerHandleMessage(unsigned char sendModuleId, unsigned char arrivedModuleId, unsigned int index);



#endif
