#ifndef __I_FLY_M_SERVICE_H
#define __I_FLY_M_SERVICE_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IMemory.h>



namespace android
{

// IFlyMService enum
enum
{
	REGISTER_CLIENT = IBinder:: FIRST_CALL_TRANSACTION,
	REQUEST_SERVICE_OPEN,
	REQUEST_SERVICE_CLOSE,
	REQUEST_SERVICE_IOCTL,
	REQUEST_SERVICE_WRITE_MESSAGE,
//	REQUEST_WRITE_CLIENT_BROADCAST,
//	REQUEST_WRITE_CLIENT_MESSAGE,
//	REQUEST_WRITE_CLIENT_STATUS,
};

// IFlyMClient enum
enum
{
	REQUEST_CLIENT_WRITE_BROADCAST = IBinder::FIRST_CALL_TRANSACTION,
	REQUEST_CLIENT_WRITE_MESSAGE,
	REQUEST_CLIENT_WRITE_STATUS,
};


class IFlyMClient: public IInterface
{
public:
	DECLARE_META_INTERFACE(FlyMClient);
	
public:
	virtual int writeBroadcast(const char* action, const char* value) = 0;
	virtual int writeMessage(const char* msg, const int32_t length) = 0;
	virtual int writeStatus(int32_t msgType, int32_t ext1, int32_t ext2) = 0;
};


class IFlyMService: public IInterface
{
public:
	DECLARE_META_INTERFACE(FlyMService);

public:
	virtual int registerClient(const sp<IFlyMClient>& client) = 0;
	virtual int writeMessage(const char* msg, const int32_t length) = 0;
	virtual int open(void) = 0;
	virtual int ioctl(int cmd, void *data, int length) = 0;
	virtual int close(void) = 0;

//public:
//	virtual int writeClientMessage(const char* msg, const int32_t length) = 0;
//	virtual int writeClientBroadcast(const char* action, const char* value) = 0;
//	virtual int writeClientStatus(int32_t msgType, int32_t ext1, int32_t ext2) = 0;
};


class BnFlyMService: public BnInterface<IFlyMService>
{
public: 
	virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
};

class BnFlyMClient: public BnInterface<IFlyMClient>
{
public: 
	virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
};


};



#endif
