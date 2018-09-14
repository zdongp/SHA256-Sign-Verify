#ifndef _FLY_OPEN_H
#define _FLY_OPEN_H

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <linux/kernel.h>
#include <errno.h>
#include <sys/ioctl.h>

__BEGIN_DECLS

#define SEM_MAGIC 's' //å®ä¹å¹»æ°
#define SEM_MAX_NR 2 //å®ä¹åœä»€çæå€§åºæ?


#define SEM_LOCK _IO(SEM_MAGIC, 1) 		
#define SEM_UNLOCK _IO(SEM_MAGIC, 2)	
#define READ_PAGEID_FORC _IOR(SEM_MAGIC, 5 ,int) //Cè¯»åé¡µé¢æ¥å£
#define WRITE_PAGEID_FORC _IOW(SEM_MAGIC, 6 ,short)	//Cåé¡µé¢æ¥å?

int  open_device(const char *devname, int flags);
int  c_read_dev(int fd,short * pageid);
int  c_write_dev(int fd,short pageid);
int  c_lock(int fd);
int  c_unlock(int fd);

__END_DECLS

#endif
