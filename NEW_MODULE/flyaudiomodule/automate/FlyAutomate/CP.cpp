///////////////////////////////////////////////////////////////////////////////
///
/// The CCP class for low-level control of the Apple Auth Co-processor over
/// I2C.
///
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <string.h>
#include "CP.h"

extern "C"
{
	#include "flyi2c.h"
}

#define  ACP_I2C_ADDRESS     (0x10)
#define INVALID_FD          (-1)

// Struct used to send/revceive data
typedef struct {
    char   i2c_address;
    int      reg;
    int      size;
    unsigned char   data[512];
} SMBUS_TRANSFER;

static int SMBus_Initialize(void)
{
	return i2c_open(1);
}

static void SMBus_DeInit(int smbus_fd)
{
	i2c_close(smbus_fd);
}

static bool SMBus_ReadData(int smbus_fd,SMBUS_TRANSFER *pTransfer)
{
    bool bRet = false;
    int bytes_read;

    bytes_read = i2c_read_data(smbus_fd,pTransfer->i2c_address,pTransfer->reg,(char*)&pTransfer->data[0],pTransfer->size,0);
    if(bytes_read == pTransfer->size)
    {
        bRet = true;
    }

    return bRet;// Returns TRUE on success, FALSE otherwise
}

static bool SMBus_WriteData(int smbus_fd,SMBUS_TRANSFER *pTransfer)
{
    bool bRet = false;
    int ret;

    if(i2c_write_data(smbus_fd,pTransfer->i2c_address,pTransfer->reg,(char*)&pTransfer->data[0],pTransfer->size) == 0)
    {
    	bRet = true;
    }

    return bRet;// Returns TRUE on success, FALSE otherwise
}

/////////////////////////////////////////
////////////////////////////////////////
CCP::CCP()
{
	h = SMBus_Initialize();
}

CCP::~CCP()
{
    SMBus_DeInit(h);
}

bool	CCP::Init()
{
	return true;
}

unsigned char CCP::GetDeviceVersion()  // Get Coprocessor Device Version.
{
	SMBUS_TRANSFER xfr;
	unsigned char  ret = -1;

    	if (h == INVALID_FD)
		return ret;

	//read REG00(Device Version)
	xfr.i2c_address = ACP_I2C_ADDRESS;
	xfr.size        = 0x01;
	xfr.reg         = ACP_REG_DEVICE_VERSION;
    	if (!SMBus_ReadData(h, &xfr))
		return ret;

	ret = xfr.data[0];
	return ret;
}

unsigned char CCP::GetFWVersion()  // Get Coprocessor FW Version.
{
	SMBUS_TRANSFER xfr;
	unsigned char ret = -1;

   	if (h == INVALID_FD)
		return ret;

	//read REG01(FW Version)
	xfr.i2c_address = ACP_I2C_ADDRESS;
	xfr.size        = 0x01;
    	xfr.reg         = ACP_REG_FW_VERSION;
    	if (!SMBus_ReadData(h, &xfr))
		return ret;

	ret = xfr.data[0];
	return ret;
}


// Get Coprocessor auth prot major.
unsigned char CCP::GetAuthProtocolMajor()
{
	SMBUS_TRANSFER xfr;
	unsigned char ret = -1;

    	if (h == INVALID_FD)
		return ret;

	//read REG02(Protocol Major)
    	xfr.i2c_address = ACP_I2C_ADDRESS;
    	xfr.size        = 0x01;
    	xfr.reg         = ACP_REG_AUTH_PROTO_MAJOR_VERSION;
    	if (!SMBus_ReadData(h, &xfr))
	 	return ret;

    	ret = xfr.data[0];
    	return ret;
}


// Get Coprocessor auth prot minor.
unsigned char CCP::GetAuthProtocolMinor()
{
	SMBUS_TRANSFER xfr;
	unsigned char ret = -1;

    	if (h == INVALID_FD)
		return ret;

	//read REG03(Protocol Minor)
   	xfr.i2c_address = ACP_I2C_ADDRESS;
    	xfr.size        = 0x01;
    	xfr.reg         = ACP_REG_AUTH_PROTO_MINOR_VERSION;
	if (!SMBus_ReadData(h, &xfr))
		return ret;

	ret = xfr.data[0];
	return ret;
}

