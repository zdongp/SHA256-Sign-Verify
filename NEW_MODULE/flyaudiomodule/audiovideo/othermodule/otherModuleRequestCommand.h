#ifndef __OTHER_MODULE_REQUEST_COMMAND_H__
#define __OTHER_MODULE_REQUEST_COMMAND_H__

void makeAndSendMessageToModule(unsigned char sendModuleId, unsigned char arrivedModuleId, unsigned char *buffer, int len);

#endif
