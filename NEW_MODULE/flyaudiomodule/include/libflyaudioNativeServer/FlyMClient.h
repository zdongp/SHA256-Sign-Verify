#ifndef __FLY_M_CLIENT_H
#define __FLY_M_CLIENT_H

#include <utils/threads.h>


#include "IFlyMService.h"


#define FLYAUDIO_MODULE_SERVER		"android.flyaudio.module.center"

namespace android
{

class clientListener: virtual public RefBase
{
public:
	virtual int writeAppBroadcast(const char* action, const char* value) = 0;
	virtual int writeAppMessage(const char* msg, const int32_t length) = 0;
	virtual int writeAppStatus(int32_t msgType, int32_t ext1, int32_t ext2) = 0;
};

class FlyMClient: public BnFlyMClient
{
public:
	virtual ~FlyMClient();
	FlyMClient();

public:
	void setListener(sp<clientListener>& listener);

private:
	sp<IFlyMService> getFlyService(void);

public:
	/* Server Set to UI */
	int writeBroadcast(const char* action, const char* value);
	int writeMessage(const char* msg, const int32_t length);
	int writeStatus(int32_t msgType, int32_t ext1, int32_t ext2);

public:
	int registerClient(const sp<IFlyMClient>& client);
	int writeMessageToService(const char* msg, const int32_t length);
	int openService(void);
	int ioctlService(int cmd, void *data, int length);
	int closeService(void);

private:
	sp<clientListener> mListener;
	sp<IFlyMService> mIFlyMService;
	Mutex mLock;
};

};

#endif
