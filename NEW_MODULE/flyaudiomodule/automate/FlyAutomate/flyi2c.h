#ifndef __FLY_I2C_H__
#define __FLY_I2C_H__

/* This is the structure as used in the I2C_RDWR ioctl call */
struct i2c_rdwr_ioctl_data {
	struct i2c_msg *msgs;	/* pointers to i2c_msgs */
	unsigned int nmsgs;			/* number of i2c_msgs */
};

/* 
/dev/i2c-X ioctl commands.  The ioctl's parameter is always an
 * unsigned long, except for:
 *  - I2C_FUNCS, takes pointer to an unsigned long
 *  - I2C_RDWR, takes pointer to struct i2c_rdwr_ioctl_data
 *  - I2C_SMBUS, takes pointer to struct i2c_smbus_ioctl_data
*/
#define I2C_RETRIES 0x0701  /* number of times a device address should
                   be polled when not acknowledging */
#define I2C_TIMEOUT 0x0702  /* set timeout in units of 10 ms */

/* NOTE: Slave address is 7 or 10 bits, but 10-bit addresses
 * are NOT supported! (due to code brokenness)
 */
#define I2C_SLAVE   0x0703  /* Use this slave address */
#define I2C_SLAVE_FORCE 0x0706  /* Use this slave address, even if it
                   is already in use by a driver! */
#define I2C_TENBIT  0x0704  /* 0 for 7 bit addrs, != 0 for 10 bit */

#define I2C_FUNCS   0x0705  /* Get the adapter functionality mask */

#define I2C_RDWR    0x0707  /* Combined R/W transfer (one STOP only) */

#define I2C_PEC     0x0708  /* != 0 to use PEC with SMBus */
#define I2C_SMBUS   0x0720  /* SMBus transfer */

#include <android/log.h>
extern char g_cOutput[];

#define LOG_LV_ERROR			0
#define LOG_LV_DEBUG			1

#define OUTPUT_MAX_LEN		256

#define MODULE_FLAG	"FlyAutomate"

#define fly_printf(...)\
{\
	__android_log_print(ANDROID_LOG_DEBUG, MODULE_FLAG, __VA_ARGS__);\
}

#define FLY_LOG(lvl,formatStr,...)\
{\
	memset(g_cOutput, 0, OUTPUT_MAX_LEN);\
	sprintf(g_cOutput, "%s------>%s", __PRETTY_FUNCTION__, formatStr);\
	fly_printf(g_cOutput, __VA_ARGS__);\
}

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG ,  MODULE_FLAG, __VA_ARGS__)

#if __cplusplus
extern "C" {
#endif
int i2c_open(int port);

void i2c_close(int fd);

int i2c_read_data(int fd, char slaveaddr, char regaddr, char *read_data, int size, int rcv_wait);

int i2c_write_data(int fd, char slaveaddr, char regaddr,char *send_data, int size);

#if __cplusplus
};  // extern "C"
#endif

#endif 
