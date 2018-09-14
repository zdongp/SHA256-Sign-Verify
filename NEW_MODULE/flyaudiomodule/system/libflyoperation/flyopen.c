#include "flyopen.h"

int  open_device(const char *devname, int flags){
	return open(devname, flags);
};
int  c_read_dev(int fd,short * pageid)
{
   return ioctl(fd,READ_PAGEID_FORC,pageid);
}
int  c_write_dev(int fd,short pageid)
{
   return ioctl(fd,WRITE_PAGEID_FORC,pageid);
}
int  c_lock(int fd)
{
  return ioctl(fd,SEM_LOCK);
}
int  c_unlock(int fd)
{
  return ioctl(fd,SEM_UNLOCK);
}

