#include <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <unistd.h>  
#include  <fcntl.h> 
#include  <errno.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include  <linux/i2c.h>
#include  <linux/time.h>
#include  <asm/ioctl.h>

#include "flyi2c.h"
char g_cOutput[256];
// #define LOG_TAG  "LIB_I2C"
// #define  FLY_LOG(LOG_LV_DEBUG, ...)   LOGI(__VA_ARGS__)
// #define  FLY_LOG(LOG_LV_DEBUG, ...)   LOGE(__VA_ARGS__)

int i2c_open(int port)
{
	FLY_LOG(LOG_LV_DEBUG, "i2c_open+++++%d", (unsigned char)1);
	char device_name[64];
	int slen = 0x00;
	int i2c_fd = 0x00;

	memset(device_name, 0x00, sizeof(device_name));	
	slen = sizeof(device_name);
	snprintf(device_name, slen-1, "%s%d", "/dev/i2c-", port);
	i2c_fd = open(device_name, O_RDWR, 777);
	if (i2c_fd < 0x00)
	{
		FLY_LOG(LOG_LV_DEBUG, "open %s error ! error is %s", device_name, strerror(errno));
		return -1;
	} 
	return i2c_fd;
}

void i2c_close(int fd)
{
	close(fd);	
}

int i2c_read_data(int fd, char slaveaddr, char regaddr, char *read_data, int size, int rcv_wait)
{
	FLY_LOG(LOG_LV_DEBUG, "i2c_read_data , fd is %d, slaveaddr is %d, subaddr is %d, size is %d", fd, slaveaddr, regaddr, size);
	struct i2c_rdwr_ioctl_data rdwr_data;
	int ret; 
	int i;

	if (rcv_wait > 0)
	{
		usleep(rcv_wait*1000);
	}

	rdwr_data.nmsgs=2; 
	rdwr_data.msgs=(struct i2c_msg*)malloc(rdwr_data.nmsgs*sizeof(struct i2c_msg));
	if(!rdwr_data.msgs)
	{
		FLY_LOG(LOG_LV_DEBUG, "i2c_read_data  malloc error%d", (unsigned char)1);
		return -1;
	}

	ioctl(fd,I2C_TIMEOUT,1);
	ioctl(fd,I2C_RETRIES,2);

	/******read data from i2c*******/
	(rdwr_data.msgs[0]).len=1; 
	(rdwr_data.msgs[0]).addr=slaveaddr; 
	(rdwr_data.msgs[0]).flags=0;//write
	(rdwr_data.msgs[0]).buf=(unsigned char*)malloc(sizeof(char));
	memset((rdwr_data.msgs[0]).buf, 0x00, sizeof(char));
	(rdwr_data.msgs[0]).buf[0]=regaddr;
	(rdwr_data.msgs[1]).len=size;
	(rdwr_data.msgs[1]).addr=slaveaddr;
	(rdwr_data.msgs[1]).flags=I2C_M_RD;//read
	(rdwr_data.msgs[1]).buf=(unsigned char*)malloc(size*sizeof(char));
	memset((rdwr_data.msgs[1]).buf, 0x00, size*sizeof(char));
	
	ret=ioctl(fd,I2C_RDWR,(unsigned long)&rdwr_data);
	if(ret<0)
	{
		FLY_LOG(LOG_LV_DEBUG, "i2c_read_data  I2C_RDWR read error%d", (unsigned char)1);
		free((rdwr_data.msgs[0]).buf);
		free((rdwr_data.msgs[1]).buf);
		free(rdwr_data.msgs);
		return -1;
	}
	for(i = 0; i < size; i++){
		FLY_LOG(LOG_LV_DEBUG, "i2c_read_data buff[%d]=%x", i , (rdwr_data.msgs[1]).buf[i]);
	}

	memcpy(read_data, rdwr_data.msgs[1].buf, size);	

	free((rdwr_data.msgs[0]).buf);
	free((rdwr_data.msgs[1]).buf);
	free(rdwr_data.msgs);
	return size;
}

int i2c_write_data(int fd, char slaveaddr, char regaddr,char *send_data, int size)
{
	FLY_LOG(LOG_LV_DEBUG, "i2c_write_data , fd is %d, slaveaddr is %d, subaddr is %d, size is %d", fd, slaveaddr, regaddr, size);
	int ret = 0x00; 
	int i = 0;
	struct i2c_rdwr_ioctl_data rdwr_data;

	if (send_data != NULL)
	{
		rdwr_data.nmsgs=1;
		rdwr_data.msgs=(struct i2c_msg*)malloc(rdwr_data.nmsgs*sizeof(struct i2c_msg));
		if(!rdwr_data.msgs)
		{
			FLY_LOG(LOG_LV_DEBUG, "i2c_write_data malloc error%d", (unsigned char)1);
			return -1;
		}
		ioctl(fd,I2C_TIMEOUT,1);
		ioctl(fd,I2C_RETRIES,2);

		/***write data to i2c**/
		rdwr_data.nmsgs=1;
		(rdwr_data.msgs[0]).len=size+1;
		(rdwr_data.msgs[0]).addr=slaveaddr;
		(rdwr_data.msgs[0]).flags=0; //write
		(rdwr_data.msgs[0]).buf=(unsigned char*)malloc((size+1) * sizeof(char));
		(rdwr_data.msgs[0]).buf[0]=regaddr;
		for ( i = 0; i < size; i++) 
		{
			(rdwr_data.msgs[0]).buf[i+1] = send_data[i];
		}
	
		ret=ioctl(fd,I2C_RDWR,(unsigned long)&rdwr_data);
		if(ret<0)
		{
			FLY_LOG(LOG_LV_DEBUG, "i2c_write_data  I2C_RDWR write error%d", (unsigned char)1);
			free(rdwr_data.msgs[0].buf);
			free(rdwr_data.msgs);
			return -1;
		}
		free(rdwr_data.msgs[0].buf);
		free(rdwr_data.msgs);
		FLY_LOG(LOG_LV_DEBUG, "i2c_write_data success!%d", (unsigned char)1);
		return 0;
	}
	return -1;
}


