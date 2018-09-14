#ifndef COMMONFUNC_H_
#define COMMONFUNC_H_

#include "types_def.h"
#ifdef __cplusplus
extern "C" {
#endif

#define INFINITE 0xFFFFFFFF

#define GPIO_DIR_OUT 0
#define GPIO_DIR_IN 1

#define GPIO_VALUE_LOW 0
#define GPIO_VALUE_HIGH 1

#define GPIO_EDGE_NONE 0
#define GPIO_EDGE_RISING 1
#define GPIO_EDGE_FALLING 2
#define GPIO_EDGE_BOTH    3

struct flydata
{
	BYTE buff[256];
	BYTE step;
	UINT nowlen;
	UINT freamlen;
	BYTE checksum;
};


typedef struct _FILE_BUFFER
{
	char fileName[100];
	ULONG buffLength;
	BYTE *buff;
}FILE_BUFFER;

typedef void (*p_flydataProc) (BYTE *buf, UINT len);
typedef void (*_t_procINI)(BOOL bNode,char *id,char *value);




#ifdef LINUX_QT
#include "flyprop.h"
#else

#define PROPERTY_VALUE_MAX 512
int property_get(const char *key, char *value, const char *default_value);
int property_set(const char* key, const char* value);
int property_list(void (*propfn)(const char *key, const char *value, void *cookie), void *cookie);

#endif


void Sleep(UINT32 sTime);
ULONG GetTickCount(void);

UINT32 stringToDec(char *buf,int len);

void ResetUserTimer(ULONG *Timer);
ULONG ReadUserTimer(ULONG *Timer);
BOOL TimerHasExpired(ULONG *Timer);
void TimerSet(ULONG *Timer, ULONG time);

BOOL TimerOut(ULONG *Timer, ULONG timeOuts);

BOOL dealFlyData(BYTE *p,UINT length, p_flydataProc flydataProc);

void readINIFileConfig(char *file, _t_procINI _p_procINI);

void PostSignal(pthread_mutex_t *pMutex,pthread_cond_t *pCond,BOOL *bRunAgain);
int WaitSignedTimeOut(pthread_mutex_t *pMutex,pthread_cond_t *pCond,BOOL *bRunAgain,UINT32 iTimeOutMs);

int openIICDev(const char *dev, UINT addr);
int readIICDev(int fd, BYTE *subAddr, UINT subAddrLen, char *buf, UINT len);
int writeIICDev(int fd, char *buf, UINT len);

int get_gpio_fd(int pin);
int gpio_export(int pin);
int gpio_unexport(int pin);
int gpio_direction(int pin, int dir);
int gpio_write(int pin, int value);
int gpio_read(int pin);
int gpio_edge(int pin, int edge);

int init_sem(int sem_id,int init_value);
int del_sem(int sem_id);
int sem_p(int sem_id);
int sem_v(int sem_id);
int getSemidBykey(int key);

int gb2312_to_unicode(unsigned short int *unicode, BYTE *gb2312, UINT32 len);




void debugPrintf(char *fmt,...);
void debugBuf(char *fmt, BYTE *buf, UINT len);
void setDebugLevel(BYTE level);
UINT getDebugLevel(const char *propName, const char *defaultLevel);
void debugTagSet(const char *tagName);


UINT32 forU8ToU32LSB(BYTE *p);
void forU32TopU8LSB(UINT32 data,BYTE *p);


extern int debugLevel;
#define DBG0(CODE) if(1){CODE}
#define DBG1(CODE) if(debugLevel&0x01){CODE}
#define DBG2(CODE) if(debugLevel&0x02){CODE}
#define DBG3(CODE) if(debugLevel&0x04){CODE}


#ifdef __cplusplus
}
#endif

#endif
