#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdio.h>
#include <poll.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/poll.h> 
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "types_def.h"

#include "moduleCommApi.h"
#include "commonFunc.h"
#include "code_data_offset_all.h"





UINT32 forU8ToU32LSB(BYTE *p)
{
	UINT32 iTemp = 0;
	iTemp = (p[3] << 24) + (p[2] << 16) + (p[1] << 8) + p[0];
	return iTemp;
}

void forU32TopU8LSB(UINT32 data,BYTE *p)
{
	p[0] = data;
	data = data >> 8;p[1] = data;
	data = data >> 8;p[2] = data;
	data = data >> 8;p[3] = data;
}

ULONG forU8ToPtrADDR(BYTE *p)
{
	UINT i = 0;
	ULONG iTemp = 0;
	for (i = 0; i < sizeof(void*); i++)
	{
		iTemp <<= 8;
		iTemp += p[sizeof(void*) - i - 1];
	}
	/*
	iTemp = p[7];
	iTemp = iTemp << 8; iTemp += p[6];
	iTemp = iTemp << 8; iTemp += p[5];
	iTemp = iTemp << 8; iTemp += p[4];
	iTemp = iTemp << 8; iTemp += p[3];
	iTemp = iTemp << 8; iTemp += p[2];
	iTemp = iTemp << 8; iTemp += p[1];
	iTemp = iTemp << 8; iTemp += p[0];
	*/
	return iTemp;
}

void forPtrADDRToU8(ULONG ADDR, BYTE *p)
{
	UINT i = 0;
	
	for (i = 0; i < sizeof(void *); i++)
	{
		p[i] = ADDR;
		ADDR >>= 8;
	}
	/*
	p[0] = ADDR;
	ADDR = ADDR >> 8;p[1] = ADDR;
	ADDR = ADDR >> 8;p[2] = ADDR;
	ADDR = ADDR >> 8;p[3] = ADDR;
	ADDR = ADDR >> 8;p[4] = ADDR;
	ADDR = ADDR >> 8;p[5] = ADDR;
	ADDR = ADDR >> 8;p[6] = ADDR;
	ADDR = ADDR >> 8;p[7] = ADDR;
	*/
}


/******************** below interface for debug msg ***************************/

static const char *tag = "MODULE";

#if defined(LINUX_QT)
#define DLOG(...) printf(__VA_ARGS__)

#else
#include <android/log.h>

#define DLOG(...) __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__)

#endif


#define DEBUG_MESSAGE_MAX_LEN 256
#define vsnprintfBuffLen	(1024*8)


int debug_fd = -1;
int debugLevel = 0;
char bufToStringBuff[DEBUG_MESSAGE_MAX_LEN];
char buffToStringPrint[DEBUG_MESSAGE_MAX_LEN*2];
char vsnprintfBuff[vsnprintfBuffLen];




char *bufToHex(BYTE *buf, UINT len)
{
	UINT i;
	UINT j;
	char str[4];

	for (i=0,j=0; i<len && j < DEBUG_MESSAGE_MAX_LEN - 4; i++,j=j+3)
	{
		snprintf(str, sizeof(str), " %02X", buf[i]);
		memcpy(&bufToStringBuff[j], str, 3);
	}
	bufToStringBuff[j] = '\n';
	bufToStringBuff[j+1] = '\0';

	return bufToStringBuff;
}

char *bufToDec(UINT32 iData)
{
	snprintf(bufToStringBuff, sizeof(bufToStringBuff), " %d", (int)iData);
	return bufToStringBuff;
}

static void writeStringToDebug(char *debugBuf)
{
	if (debug_fd < 0)
	{
		debug_fd = open("/dev/lidbg_msg",O_RDWR);
	}
	if (debug_fd > 0)
	{
		//write(debug_fd, debugBuf, strlen(debugBuf));
	}

    DLOG("%s",debugBuf);     
}

void debugPrintf(char *fmt,...)
{
	int len;
	va_list ap;
	va_start(ap, fmt);
	len = vsnprintf(vsnprintfBuff, vsnprintfBuffLen, fmt, ap);
	va_end(ap);
	vsnprintfBuff[len] = 0;
	writeStringToDebug(vsnprintfBuff);
}

void debugBuf(char *fmt, BYTE *buf, UINT len)
{
	while (len
		&& (strlen(fmt)+1+len*3 > DEBUG_MESSAGE_MAX_LEN*2))
	{
		len--;
	}

	if (strlen(fmt)+1+len*3 > DEBUG_MESSAGE_MAX_LEN*2)
	{
		debugPrintf("debugBuf OverFlow!\n");
		return;
	}
	strcpy(buffToStringPrint,fmt);
	strcat(buffToStringPrint,bufToHex(buf,len));
	writeStringToDebug(buffToStringPrint);
}



void debugTagSet(const char *tagName)
{
	if (NULL != tagName)
	{
		tag = tagName;
	}
}


void setDebugLevel(BYTE level)
{
    debugLevel = level;
}


//---------------------------------------

#define INI_FILE_MAX	20
FILE_BUFFER fileConfig[INI_FILE_MAX];

UINT32 stringToDec(char *buf,int len);

void procINIData(BYTE *p,UINT length,_t_procINI _p_procINI);


static unsigned short get_unicode(unsigned short int gb)
{
	return gb_uni_table[gb];
}

int gb2312_to_unicode(unsigned short int *unicode, BYTE *gb2312, UINT32 len)
{
	UINT32 i,j;
	unsigned short iTmp;

	for(i=0,j=0;i<len;j++)
	{
		if ((unsigned char)gb2312[i]<=0x80)
		{
			unicode[j]=gb2312[i];
			i++;
		}
		else
		{
			unicode[j]=get_unicode(*(unsigned short int*)(gb2312+i));
			i+=2;
		}
	}
	return j*2;
}


//--------------------- below is sempose function interface -------------------------
#include <sys/ipc.h>
#include <sys/sem.h>


#ifdef LINUX_QT
union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                               (Linux-specific) */
};


int init_sem(int sem_id,int init_value) {
    union semun sem_union;
    sem_union.val=init_value;
    if (semctl(sem_id,0,SETVAL,sem_union)==-1) {
        perror("Sem init");
        exit(1);
    }
    return 0;
}

int del_sem(int sem_id) {
    union semun sem_union;
    if (semctl(sem_id,0,IPC_RMID,sem_union)==-1) {
        perror("Sem delete");
        exit(1);
    }
    return 0;
}
int sem_p(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_num=0;
    sem_buf.sem_op=-1;
    sem_buf.sem_flg=SEM_UNDO;
    if (semop(sem_id,&sem_buf,1)==-1) {
        perror("Sem P operation");
        exit(1);
    }
    return 0;
}
int sem_v(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_num=0;
    sem_buf.sem_op=1;
    sem_buf.sem_flg=SEM_UNDO;
    if (semop(sem_id,&sem_buf,1)==-1) {
        perror("Sem V operation");
        exit(1);
    }
    return 0;
}

int getSemidBykey(int key)
{
	return semget((key_t)key,1,IPC_CREAT|0666);
}
#endif

//--------------------- below is property function interface ------------------------

#ifdef LINUX_QT
#include "flyprop.h"

#else
#include <sys/system_properties.h>

int property_get(const char *key, char *value, const char *default_value)
{
	int len;

	len = __system_property_get(key, value);
	if(len > 0) {
		return len;
	}

	if(default_value) {
		len = strlen(default_value);
		memcpy(value, default_value, len + 1);
	}
	return len;
}

int property_set(const char* key, const char* value)
{
	return __system_property_set(key, value);
}

struct property_list_callback_data
{
    void (*propfn)(const char *key, const char *value, void *cookie);
    void *cookie;
};

static void property_list_callback(const prop_info *pi, void *cookie)
{
    char name[PROP_NAME_MAX];
    char value[PROP_VALUE_MAX];
    struct property_list_callback_data *data = cookie;

    __system_property_read(pi, name, value);
    data->propfn(name, value, data->cookie);
}

int property_list(
        void (*propfn)(const char *key, const char *value, void *cookie),
        void *cookie)
{
    struct property_list_callback_data data = { propfn, cookie };
    return __system_property_foreach(property_list_callback, &data);
}


#endif

UINT getDebugLevel(const char *propName, const char *defaultLevel)
{
	char propValue[PROPERTY_VALUE_MAX+1]={0};
	property_get(propName, propValue, defaultLevel);
    return stringToDec(propValue, 1);
    
}


//--------------------- below is timer function interface ------------------------

struct flydata flydata;
BOOL dealFlyData(BYTE *p,UINT length, p_flydataProc flydataProc)
{
	UINT i;

	for (i = 0;i < length;i++)
	{
		switch (flydata.step)
		{
		case 0:
			if (0xFF == p[i])
				flydata.step = 1;
			break;
		case 1:
			if (0xFF == p[i])
				flydata.step = 1;
			else if (0x55 == p[i])
				flydata.step = 2;
			else
				flydata.step = 0;
			break;
		case 2:
			flydata.step = 3;
			flydata.nowlen = 0;
			flydata.freamlen = p[i];
			flydata.checksum = p[i];
			break;
		case 3:
			if (flydata.nowlen < (flydata.freamlen-1))
			{
				flydata.buff[flydata.nowlen] = p[i];
				flydata.checksum += p[i];
				flydata.nowlen++;
			}
			else
			{
				flydata.step = 0;
				if (flydata.checksum == p[i])
				{
					flydataProc(flydata.buff, flydata.freamlen-1);
				}
			}
			break;
		default:
			flydata.step = 0;
			break;
		}
	}

	if (flydata.step > 1)
		return TRUE;
	else
		return FALSE;
}


void Sleep(UINT32 sTime)
{
	usleep(sTime*1000);
}

ULONG GetTickCount(void)
{

	struct timespec usr_timer;
	clock_gettime(CLOCK_MONOTONIC,&usr_timer);

	return usr_timer.tv_sec*1000 + usr_timer.tv_nsec / 1000000;

/*
    struct timeval nowTime; 
    gettimeofday(&nowTime, NULL); 
    return nowTime.tv_sec*1000 + nowTime.tv_usec/1000;
*/
}

void ResetUserTimer(ULONG *Timer)
{
    *Timer = GetTickCount();
}


ULONG ReadUserTimer(ULONG *Timer)
{
    return GetTickCount() - *Timer;
}

BOOL TimerHasExpired(ULONG *Timer)
{
    if (GetTickCount() - *Timer >= 1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void TimerSet(ULONG *Timer, ULONG time)
{
    *Timer = GetTickCount() + time;
}

BOOL TimerOut(ULONG *timer, ULONG timeout)
{
	if (GetTickCount() - *timer >= timeout)
	{
		*timer = GetTickCount();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void PostSignal(pthread_mutex_t *pMutex,pthread_cond_t *pCond,BOOL *pbRunAgain)
{
	pthread_mutex_lock(pMutex);
	*pbRunAgain = TRUE;
	pthread_cond_signal(pCond);
	pthread_mutex_unlock(pMutex);
}

int WaitSignedTimeOut(pthread_mutex_t *pMutex,pthread_cond_t *pCond,BOOL *pbRunAgain,UINT32 iTimeOutMs)
{
	int ret = 0;
	struct timespec timenow;
	struct timespec timeout;
	UINT32 iSecnod,iMSecnod;

	pthread_mutex_lock(pMutex);

	if (*pbRunAgain)
	{
	}
	else if (INFINITE == iTimeOutMs || 0 == iTimeOutMs)
	{
		pthread_cond_wait(pCond,pMutex);
	}
	else
	{
		clock_gettime(CLOCK_MONOTONIC,&timenow);

		iSecnod = iTimeOutMs / 1000;
		iMSecnod = iTimeOutMs % 1000;

		timeout.tv_sec = timenow.tv_sec + iSecnod;
		timeout.tv_nsec = timenow.tv_nsec + (iMSecnod*1000)*1000;

		while (timeout.tv_nsec >= 1000000000)
		{
			timeout.tv_nsec -= 1000000000;
			timeout.tv_sec++;
		}

		ret = pthread_cond_timedwait(pCond,pMutex,&timeout); 
	}

	*pbRunAgain = FALSE;

	pthread_mutex_unlock(pMutex);

	return ret;
}



//--------------------- below is flyaudio config file function interface -----------------

UINT32 stringToDec(char *buf,int len)
{
	UINT32 iData = 0;
	BOOL b16x = FALSE;

	//DBG3(debugPrintf(" stringToDec %s %d\n",buf,len););

	if ('0' == buf[0])
	{
		if ('x' == buf[1] || 'X' == buf[1])
		{
			b16x = TRUE;
			buf += 2;
			len -= 2;
		}
	}

	while (*buf && len)
	{
		if (b16x)
		{
			if (buf[0] >= 'a' && buf[0] <= 'f')
			{
				iData *= 16;
				iData += buf[0]+10-'a';
			}
			else if (buf[0] >= 'A' && buf[0] <= 'F')
			{
				iData *= 16;
				iData += buf[0]+10-'A';
			}
			else if (buf[0] >= '0' && buf[0] <= '9')
			{
				iData *= 16;
				iData += buf[0]-'0';
			}
		}
		else
		{
			if (buf[0] >= '0' && buf[0] <= '9')
			{
				iData *= 10;
				iData += buf[0]-'0';
			}
		}
		buf++;
		len--;
	}

	return iData;
}

void procINIData(BYTE *p,UINT length,_t_procINI _p_procINI)
{
	UINT i;

	char *id;
	char *value;

	int idLength = 0;
	int valueLength = 0;
	BOOL isNode = FALSE;

	BOOL bID = TRUE;
	BOOL bNeedProc = FALSE;
	BOOL bEnd = FALSE;

	id = (char *)malloc(256);
	value = (char *)malloc(256);

	for (i = 0;i <= length;i++)
	{
		if (i == length)
		{
			bNeedProc = TRUE;
			bEnd = TRUE;
		}
		else if ('[' == p[i])
		{
			isNode = TRUE;
		}
		else if (']' == p[i])
		{
			bNeedProc = TRUE;
			bEnd = TRUE;
		}
		else if ('#' == p[i])
		{
			bID = TRUE;
			bNeedProc = TRUE;
			bEnd = TRUE;
		}
		else if ('\r' == p[i] || '\n' == p[i])
		{
			bID = TRUE;
			bNeedProc = TRUE;
			bEnd = FALSE;
		}
		else if ('=' == p[i])
		{
			bID = FALSE;
		}
		else if (p[i] > ' ')// if (p[i] > 0x20 && p[i] <= 0x7E)
		{
			if (bID)
			{
				id[idLength++] = p[i];
				id[idLength] = '\0';
			}
			else
			{
				value[valueLength++] = p[i];
				value[valueLength] = '\0';
			}
		}

		if (bNeedProc)
		{
			bNeedProc = FALSE;

			if (isNode)
			{
				if (idLength)
				{
					(*_p_procINI)(TRUE,id,value);
				}
			}
			else
			{
				if (idLength && valueLength)
				{
					(*_p_procINI)(FALSE,id,value);
				}
			}

			isNode = FALSE;
			idLength = 0;
			valueLength = 0;
		}
	}

	free(id);
	free(value);
}


void readINIFile(const char *fileName,_t_procINI _p_procINI)
{
	FILE *fd;
	ULONG fsize;
	char *p;

	fd = fopen(fileName,"rb");
	if(fd)
	{
		fseek(fd,0,SEEK_END);
		fsize = ftell(fd);
		p = (char *)malloc(fsize);

		fseek(fd,0,SEEK_SET);
		fread(p,1,fsize,fd);

		procINIData((BYTE *)p,fsize,_p_procINI);

		free(p);
		fclose(fd);
	}
	else
	{
		debugPrintf(" flyreadINIFile open -> %s fail!\n",fileName);
	}
}

BYTE* getINIFileBuff(const char *fileName, ULONG *length)
{
	FILE *fd;
	ULONG fsize;
	BYTE *p;

	fd = fopen(fileName,"rb");
	if(fd)
	{
		fseek(fd,0,SEEK_END);
		fsize = ftell(fd);
		p = (BYTE *)malloc(fsize);

		if (p != NULL)
		{
			fseek(fd,0,SEEK_SET);
			fread(p,1,fsize,fd);
			*length = fsize;
			return p;
		}
	}

	debugPrintf(" getINIFileBuff %s fail! -> %s\n", fileName, strerror(errno));
	*length = 0;
	return NULL;

}

void readINIFileConfig(char *file, _t_procINI _p_procINI)
{
	int i = 0;
	for (i = 0; i < INI_FILE_MAX; i++)
	{
		if (fileConfig[i].buffLength > 0)
		{
			if (strcmp(fileConfig[i].fileName, file) == 0)
			{
				procINIData(fileConfig[i].buff, fileConfig[i].buffLength, _p_procINI);
				return ;
			}
		}
		else
		{
			fileConfig[i].buff = getINIFileBuff(file, &(fileConfig[i].buffLength));
			if (fileConfig[i].buff != NULL)
			{
				snprintf(fileConfig[i].fileName, 100, "%s", file);
				procINIData(fileConfig[i].buff, fileConfig[i].buffLength, _p_procINI);
			}
			return ;
		}
	}

	if (fileConfig[INI_FILE_MAX-1].buffLength > 0)
	{
		free(fileConfig[INI_FILE_MAX-1].buff);
		memset(&fileConfig[INI_FILE_MAX-1], 0, sizeof(FILE_BUFFER));
		fileConfig[INI_FILE_MAX-1].buff = getINIFileBuff(file, &(fileConfig[INI_FILE_MAX-1].buffLength));
		if (fileConfig[INI_FILE_MAX-1].buff != NULL)
		{
			snprintf(fileConfig[INI_FILE_MAX-1].fileName, 100, "%s", file);
			procINIData(fileConfig[INI_FILE_MAX-1].buff, fileConfig[INI_FILE_MAX-1].buffLength, _p_procINI);
		}
	}
}


BYTE ascArry[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
BYTE *SDcardDataBuf = NULL;

static void binartToAsc(BYTE *buf ,BYTE *P , UINT32 len)
{
	BYTE Hbit;
	BYTE Lbit;
	UINT32 i;
	UINT32 nowState = 0;
	UINT32 bufState = 0;

	if(!P) return;

	for(i=0;i<len;i++)
	{
		Hbit = buf[bufState] >> 4 & 0x0f;
		Lbit = buf[bufState] & 0x0f;
		bufState++;

		P[nowState++] = ascArry[Hbit%16];
		P[nowState++] = ascArry[Lbit%16];
		P[nowState++] = ' ';
	}
}

//--------------------- below is IIC ops function interface -----------------
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

int openIICDev(const char *dev, UINT addr)
{
    int fd = 0;
    fd = open(dev, O_RDWR);
    if (fd <= 0)
    {
        return fd;
    }
    else
    {
        if (ioctl(fd, I2C_SLAVE, addr) < 0)
        {
            close(fd);
            return -1;
        }
        else
        {
            return fd;
        }
    }
}

int readIICDev(int fd, BYTE *subAddr, UINT subAddrLen, char *buf, UINT len)
{
    int ret = 0;
    ret = write(fd, subAddr, subAddrLen);
    if (ret > 0)
    {
        return read(fd, buf, len);
    }
    else
    {
        return ret;
    }
}

int writeIICDev(int fd, char *buf, UINT len)
{
    
    return write(fd, buf, len);
}


//--------------------- below is GPIO contrl function interface -----------------
#define BUFFER_MAX 512
#define DIRECTION_MAX 512


int get_gpio_fd(int pin)
{
   
    char path[DIRECTION_MAX];  
    int fd;  
  
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/value", pin);  
    fd = open(path, O_RDONLY);  
    if (fd < 0) {  
        fprintf(stderr, "failed to open gpio value for reading!\n");  
        return -1;  
    }  
     
    return fd;  
}

int gpio_export(int pin)  
{  
    char buffer[BUFFER_MAX];  
    int len;  
    int fd;  
  
    fd = open("/sys/class/gpio/export", O_WRONLY);  
    if (fd < 0) {  
        fprintf(stderr, "Failed to open export for writing! == > %s\n", strerror(errno));  
        return(-1);  
    }  
  
    len = snprintf(buffer, BUFFER_MAX, "%d", pin);  
    if (write(fd, buffer, len) < 0) {  
        fprintf(stderr, "Fail to export gpio! == > %s\n", strerror(errno));  
        close(fd);
        return -1;  
    }  
     
    close(fd);  
    return 0;  
}  

int gpio_unexport(int pin)  
{  
    char buffer[BUFFER_MAX];  
    int len;  
    int fd;  
  
    fd = open("/sys/class/gpio/unexport", O_WRONLY);  
    if (fd < 0) {  
        fprintf(stderr, "Failed to open unexport for writing! == > %s\n", strerror(errno));  
        return -1;  
    }  
  
    len = snprintf(buffer, BUFFER_MAX, "%d", pin);  
    if (write(fd, buffer, len) < 0) {  
        fprintf(stderr, "Fail to unexport gpio! == > %s\n", strerror(errno));  
        close(fd);
        return -1;  
    }  
     
    close(fd);  
    return 0;  
}  

int gpio_direction(int pin, int dir)  
{  
    const char dir_in[] = "in";
    const char dir_out[] = "out";
    const char *dir_str = dir_in;
    
    char path[DIRECTION_MAX];  
    int fd;  
  
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);  
    fd = open(path, O_WRONLY);  
    if (fd < 0) {  
        fprintf(stderr, "failed to open gpio direction for writing! == > %s\n", strerror(errno));  
        return -1;  
    }  

    if (GPIO_DIR_IN == dir)
    {
        dir_str = dir_in;
    }
    else if (GPIO_DIR_OUT == dir)
    {
        dir_str = dir_out;
    }
  
    if (write(fd, dir_str, strlen(dir_str)) < 0) {  
        fprintf(stderr, "failed to set direction! == > %s\n", strerror(errno)); 
        close(fd);
        return -1;  
    }  
  
    close(fd);  
    return 0;  
}  

int gpio_write(int pin, int value)  
{  
    static const char values_str[] = "01";  
    char path[DIRECTION_MAX];  
    int fd;  
  
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/value", pin);  
    fd = open(path, O_WRONLY);  
    if (fd < 0) {  
        fprintf(stderr, "failed to open gpio value for writing! == > %s\n", strerror(errno));  
        return -1;  
    }  
  
    if (write(fd, &values_str[value == GPIO_VALUE_LOW ? 0 : 1], 1) < 0) {  
        fprintf(stderr, "failed to write value! == > %s\n", strerror(errno)); 
        close(fd);
        return -1;  
    }  
  
    close(fd);  
    return 0;  
}  

int gpio_read(int pin)  
{  
    char path[DIRECTION_MAX];  
    char value_str[3];  
    int fd;  
  
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/value", pin);  
    fd = open(path, O_RDONLY);  
    if (fd < 0) {  
        fprintf(stderr, "failed to open gpio value for reading! == > %s\n", strerror(errno)); 
        return -1;  
    }  
  
    if (read(fd, value_str, 3) < 0) {  
        fprintf(stderr, "failed to read value! == > %s\n", strerror(errno)); 
        close(fd);
        return -1;  
    }  
  
    close(fd);  
    return (atoi(value_str));  
} 

int gpio_edge(int pin, int edge)  
{  
    const char edge_none[] = "none";
    const char edge_rising[] = "rising";
    const char edge_falling[] = "falling";
    const char edge_both[] = "both";
    const char *edge_str = edge_none;
    
    char path[DIRECTION_MAX];  
    int fd;  
  
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/edge", pin);  
    fd = open(path, O_WRONLY);  
    if (fd < 0) {  
        fprintf(stderr, "failed to open gpio edge for writing! == > %s\n", strerror(errno));  
        return -1;  
    }  

    if (GPIO_EDGE_NONE == edge)
    {
        edge_str = edge_none;
    }
    else if (GPIO_EDGE_RISING== edge)
    {
        edge_str = edge_rising;
    }
    else if (GPIO_EDGE_FALLING== edge)
    {
        edge_str = edge_falling;
    }
    else if (GPIO_EDGE_BOTH== edge)
    {
        edge_str = edge_both;
    }
  
    if (write(fd, edge_str, strlen(edge_str)) < 0) {  
        fprintf(stderr, "failed to write value! == > %s\n", strerror(errno)); 
        close(fd);
        return -1;  
    }  
  
    close(fd);  
    return 0;  
}  


