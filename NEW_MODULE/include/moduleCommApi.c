#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stdarg.h>
#include <sys/ioctl.h>


#include <unistd.h>
#include <sys/mman.h>

#include "types_def.h"
#include "moduleCommApi.h"
#include "commonFunc.h"



struct flyAllInOne{

	int module_comm_fd;
	BOOL bKillModuleCommReadThread;

    MODULE_INIT_INFO moduleInitInfo;
	
};


static struct flyAllInOne *pFlyAllInOneInfo = NULL;


#ifndef _IOCOM_NONE
# define _IOCOM_NONE      0U
#endif
 
#ifndef _IOCOM_WRITE
# define _IOCOM_WRITE     1U
#endif
 
#ifndef _IOCOM_READ
# define _IOCOM_READ      2U
#endif
 



#define _IOCOM_DIRBITS 2
#define _IOCOM_SIZEBITS 30  


#define _IOCOM_SIZESHIFT (0)
#define _IOCOM_DIRSHIFT (_IOCOM_SIZESHIFT + _IOCOM_SIZEBITS)
         
#define _IOCOM(dir,size) \
         (((dir) << _IOCOM_DIRSHIFT) | \
          ((size) << _IOCOM_SIZESHIFT))
 
/* used to create numbers */
#define _IOOM(size)     _IOCOM(_IOCOM_NONE,(size))
#define _IOROM(size)      _IOCOM(_IOCOM_READ,(size))
#define _IOWOM(size)      _IOCOM(_IOCOM_WRITE,(size))




/******************** below interface for comm between hal ***************************/


static void defaultCmdMsgProc(unsigned char *buf, unsigned int len)
{
    debugBuf("default modulecommMsgProc: ", buf, len);
}


int writeDataToModuleComm(unsigned char *buff, unsigned int len)
{
	BOOL status = FALSE;

	if (pFlyAllInOneInfo == NULL || pFlyAllInOneInfo->module_comm_fd < 0 || 0 == len)
	{
		return FALSE;
	}
	if (ioctl(pFlyAllInOneInfo->module_comm_fd, _IOWOM(len), buff) > 0)
	{
		status = TRUE;
	}
    else
    {
        debugBuf("write moduleComm err: ", buff, len);    
    }

	return status;
}




int makeModuleCommMsgToHAL(unsigned char *msg, unsigned int length, unsigned int objID)
{
	BYTE *buf;
	BOOL bMalloc = FALSE;
	BOOL status = FALSE;
	BYTE MsgBuf[255]={0};
	UINT streamLen = 0;
    UINT i = 0;
    BYTE checksum = 0;
    
	if (length+5 > 255)
	{
		buf = (BYTE *)malloc(sizeof(BYTE)*7+length);
		bMalloc = TRUE;
	}
	else
	{
		buf = MsgBuf;
	}

	buf[streamLen++] = 0xFF;
	buf[streamLen++] = HALMSG_MODULE;

    if (TRUE == bMalloc)
    {
        buf[streamLen++] = 0x01;
        buf[streamLen++] = (length + 2) >> 8;
        buf[streamLen++] = (length + 2) & 0xFF;
        checksum += buf[streamLen-1];
    }
    else
    {
    	buf[streamLen++] = length + 2;
        checksum += length + 2;
    }
	buf[streamLen++] = objID;
    for (i = 0; i < length; i++)
    {
        buf[streamLen+i] = msg[i];
        checksum += msg[i];
    }
    streamLen += length;
	buf[streamLen++] = checksum;


	status = writeDataToModuleComm(buf, streamLen);
	
	if (bMalloc)
	{
		free(buf);
		buf = NULL;
	}

	return status;
}


int makeModuleCommMsgToModule(unsigned char *msg, unsigned int len, unsigned int objID)
{
	BYTE *buf;
	BOOL bMalloc = FALSE;
	BOOL status = FALSE;
	BYTE MsgBuf[255]={0};
	UINT streamLen = 0;
    UINT i = 0;
    BYTE checksum = 0;
    
	if (len+5 > 255)
	{
		buf = (BYTE *)malloc(sizeof(BYTE)*7+len);
		bMalloc = TRUE;
	}
	else
	{
		buf = MsgBuf;
	}

	buf[streamLen++] = 0xFF;
	buf[streamLen++] = PRODUCT_MODULE;

    if (TRUE == bMalloc)
    {
        buf[streamLen++] = 0x01;
        buf[streamLen++] = (len + 2) >> 8;
        buf[streamLen++] = (len + 2) & 0xFF;
        checksum += buf[streamLen-1];
    }
    else
    {
    	buf[streamLen++] = len + 2;
        checksum += len + 2;
    }

	buf[streamLen++] = objID;
    for (i = 0; i < len; i++)
    {
        buf[streamLen+i] = msg[i];
        checksum += msg[i];
    }
    streamLen += len;
	buf[streamLen++] = checksum;

		
    status = writeDataToModuleComm(buf, streamLen);

	if (bMalloc)
	{
		free(buf);
		buf = NULL;
	}
     
	return status;
}



int makeModuleCommMsgToJNI(unsigned char *msg, unsigned int length)
{
	BYTE *buf;
	BOOL bMalloc = FALSE;
	BOOL status = FALSE;
	BYTE MsgBuf[255]={0};
	UINT streamLen = 0;
    UINT i = 0;
    BYTE checksum = 0;
    
	if (length+4 > 255)
	{
		buf = (BYTE *)malloc(sizeof(BYTE)*7+length);
		bMalloc = TRUE;
	}
	else
	{
		buf = MsgBuf;
	}

	buf[streamLen++] = 0xFF;
	buf[streamLen++] = JNIMSG_MODULE;

    if (TRUE == bMalloc)
    {
        buf[streamLen++] = 0x01;
        buf[streamLen++] = (length + 1) >> 8;
        buf[streamLen++] = (length + 1) & 0xFF;
        checksum += buf[streamLen-1];
    }
    else
    {
    	buf[streamLen++] = length + 1;
        checksum += length + 1;
    }
    for (i = 0; i < length; i++)
    {
        buf[streamLen+i] = msg[i];
        checksum += msg[i];
    }
    streamLen += length;
	buf[streamLen++] = checksum;

	status = writeDataToModuleComm(buf, streamLen);
	
	if (bMalloc)
	{
		free(buf);
		buf = NULL;
	}

	return status;
}


void *moduleCommReadThread(void *arg)
{
	INT ret;
    pthread_t curPthread;
        
	BYTE buff[4096];

	if(!arg) debugPrintf("moduleCommReadThread arg --> NULL\n");

	char threadName[16];
	snprintf(threadName, 16, "modComm-%X-%X",pFlyAllInOneInfo->moduleInitInfo.moduleType, pFlyAllInOneInfo->moduleInitInfo.moduleMsgId);
    curPthread = pthread_self();
	pthread_setname_np(curPthread, threadName);
	
	while (!pFlyAllInOneInfo->bKillModuleCommReadThread)
	{
		buff[0] = 0xFF;
        buff[1] = pFlyAllInOneInfo->moduleInitInfo.moduleType;
        buff[2] = 0;
        buff[3] = pFlyAllInOneInfo->moduleInitInfo.moduleMsgId;
        DBG2(debugPrintf("[moduleCommReadThread]ioctl type%X id %X\n", buff[1], buff[3]););
		ret = ioctl(pFlyAllInOneInfo->module_comm_fd, _IOROM(0), buff);
        DBG2(debugPrintf("[moduleCommReadThread]ioctl out %d\n", ret););
		if (ret > 0)
		{
			pFlyAllInOneInfo->moduleInitInfo.pCmdMsgProc(buff, ret);
		}

	}


	return NULL;
}



/****************************************************/


//BOOL moduleInterfaceDeinit(void)
//{
//	int i;
//
//	if (pFlyAllInOneInfo->module_comm_fd > 0)
//	{
//		close(pFlyAllInOneInfo->module_comm_fd);
//	}
//	free(pFlyAllInOneInfo);
//	pFlyAllInOneInfo = NULL;
//	return TRUE;
//}

int readDataFromModuleComm(unsigned char *buff, unsigned int len)
{
	int ret = 0;
	if (pFlyAllInOneInfo == NULL || pFlyAllInOneInfo->module_comm_fd < 0 || 0 == len)
	{
		debugPrintf("open module_comm_fd Fail!\n");
		return 0;
	}
	
	buff[0] = 0xFF;
	buff[1] = pFlyAllInOneInfo->moduleInitInfo.moduleType;
	buff[2] = 0;
	buff[3] = pFlyAllInOneInfo->moduleInitInfo.moduleMsgId;
	DBG2(debugPrintf("[moduleCommReadThread]ioctl type%X id %X\n", buff[1], buff[3]););
	ret = ioctl(pFlyAllInOneInfo->module_comm_fd, _IOROM(0), buff);
	DBG2(debugPrintf("[moduleCommReadThread]ret %d\n", ret););

	return ret;	
}


BOOL createReadCommThread()
{
	INT res;
	pthread_t		tid;
	pthread_attr_t	attr;


	if (pFlyAllInOneInfo->module_comm_fd < 0)
	{
		debugPrintf("open module_comm_fd Fail!\n");
		return FALSE;
	}
	else
	{
		pFlyAllInOneInfo->bKillModuleCommReadThread = FALSE;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		res = pthread_create(&tid,&attr,moduleCommReadThread,NULL);
		debugPrintf("module_comm Thread ID:%d\n",tid);
		if(res != 0)
		{
			debugPrintf(" pthread_create moduleCommThread Fail!\n");
			return FALSE;
		}
	}
    return TRUE;
}

int moduleInterfaceInit(P_MODULE_INIT_INFO pModuleInitInfo)
{
    int ret = FALSE;
	
    if(!pFlyAllInOneInfo)
	{
		pFlyAllInOneInfo = (struct flyAllInOne*)malloc(sizeof(struct flyAllInOne));
		if (NULL == pFlyAllInOneInfo)
		{
			return FALSE;
		}
		memset(pFlyAllInOneInfo,0,sizeof(struct flyAllInOne));
	}
	

    debugPrintf("pModuleInitInfo :type %02X id %02X\n", pModuleInitInfo->moduleType, pModuleInitInfo->moduleMsgId);
    memcpy(&(pFlyAllInOneInfo->moduleInitInfo), pModuleInitInfo, sizeof(MODULE_INIT_INFO));

	pFlyAllInOneInfo->module_comm_fd = open("/dev/lidbg_module_comm0",O_RDWR);

    if (NULL == pFlyAllInOneInfo->moduleInitInfo.pCmdMsgProc)
    {
        pFlyAllInOneInfo->moduleInitInfo.pCmdMsgProc = defaultCmdMsgProc;
    }
    
    
    return TRUE;
}



