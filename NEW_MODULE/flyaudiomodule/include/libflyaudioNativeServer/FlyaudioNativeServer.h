#ifndef __FLYAUDIO_NATIVE_SERVER_H_
#define __FLYAUDIO_NATIVE_SERVER_H_



void flyaudioNativeServer_Init(void);
int flyaudioNativeServer_write(const void *writebuf, const int length);
int flyaudioNativeServer_read(void *readbuf, int length);
int flyaudioNativeServer_ioctl(int cmd, char *arg, int length);
int flyaudioNativeServer_open(void);
int flyaudioNativeServer_close(void);



#endif
