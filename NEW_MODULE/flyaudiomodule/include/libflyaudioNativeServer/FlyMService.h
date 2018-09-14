#ifndef __FLY_M_SERVICE_H
#define __FLY_M_SERVICE_H

#include "IFlyMService.h"

#define FLYAUDIO_MODULE_SERVER		"android.flyaudio.module.center"

namespace android
{


class FlyMService: public BnFlyMService, public Thread
{
public:
	static void instantiate();
	
public:
	virtual ~FlyMService();
	
private:
	FlyMService();
	sp<IFlyMClient> mClient;

public:
	/* client request function */
	int registerClient(const sp<IFlyMClient>& client);
	int writeMessage(const char* msg, const int32_t length);
	int open(void);
	int ioctl(int cmd, void *data, int length);
	int close(void);
	//int testread(void *readbuf, int length);
private:
	/* call back the client function */
	int writeClientBroadcast(const char* action, const char* value);
	int writeClientMessage(const char* msg, const int32_t length);
	int writeClientStatus(int32_t msgType, int32_t ext1, int32_t ext2);

private:
	bool threadLoop();

private:
	char *buffer;
//public:
//	status_t run(const char* name = 0, int32_t priority = PRIORITY_DEFAULT, size_t stack=0);
//	status_t readyToRun()
//	{
//		init()
//		return NO_ERROR;
//	}
//	void requestExit();
};



};
#endif
