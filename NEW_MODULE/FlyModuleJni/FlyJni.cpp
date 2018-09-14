#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


#include <android/log.h>

#include <jni.h>
#include "types_def.h"
#include "FlyJni.h"
#include "moduleCommApi.h"
#include "commonFunc.h"


#define LOG_TAG "JNI_MODULE"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG ,  LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  ,  LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  ,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)



static int share_fd = -1;

static BOOL initState = FALSE;


pthread_mutex_t dataBuffMutex;

sem_t dataBuffReadSem;


unsigned char dataBuff[4096];
int dataLen = -1;

static void moduleCommDataProc(unsigned char *buf, unsigned int len)
{
    debugBuf("moduleCommDataProc: ", buf, len);
	pthread_mutex_lock(&dataBuffMutex);
	memcpy(dataBuff, buf, len);
	dataBuff[1] = 0x55;
	dataLen = len;
	pthread_mutex_unlock(&dataBuffMutex);
	sem_post(&dataBuffReadSem);
}


static void flyNativeServerInit(void)
{
    MODULE_INIT_INFO initInfo;

	while(share_fd < 0)
	{
		share_fd = open("/dev/flysemdriver", O_RDWR);
		LOGI("[%s] Open /dev/flysemdriver device %s",__FUNCTION__, share_fd<0?"failed":"true");
	}

	if (FALSE == initState)
	{
		debugPrintf("====NativeServerInit===\n");
		debugTagSet(LOG_TAG);

		pthread_mutex_init(&dataBuffMutex, NULL);
		sem_init(&dataBuffReadSem, 0, 0);


		memset(&initInfo, 0, sizeof(MODULE_INIT_INFO));
	    initInfo.moduleMsgId = 0;
	    initInfo.moduleType = JNIMSG_MODULE;
	    //initInfo.pCmdMsgProc = moduleCommDataProc;
		
		if(FALSE == moduleInterfaceInit(&initInfo))
		{
			debugPrintf("module init fail\n");
			return ;
		}

		//system("/flysystem/bin/FlyModuleService&");
		
		//createReadCommThread();
		initState = TRUE;
	}
}


static int flyNativeServerRead(char *buf, int len)
{
	int ret = 0;
	if (TRUE == initState)
	{
		ret = readDataFromModuleComm((BYTE *)buf, (INT)len);
		DBG2(debugBuf("[JNI_RD]:", (BYTE*)buf, (INT)ret););

		buf[1] = 0x55;
		
	}
	return ret;
}


static int flyNativeServerWrite(char *buf, int len)
{
	if (TRUE == initState)
	{
		DBG2(debugBuf("[JNI_WR]:", (BYTE*)buf, (INT)len););
		makeModuleCommMsgToModule((BYTE*)&buf[3], (INT)len-4, JNIMSG_MODULE);
	}
	return len;
}

static jint jni_write(JNIEnv *env, jobject thiz, jbyteArray writeBuf, jint counts)
{
	if(counts <= 0)
		return -1;

	char *buffer = (char*)env->GetByteArrayElements(writeBuf, NULL);

	flyNativeServerWrite(buffer, counts);

	env->ReleaseByteArrayElements(writeBuf, (jbyte*)buffer, 0);

	return counts;
}

static jint jni_read(JNIEnv *env, jobject thiz, jbyteArray readBuf, jint counts) {
	int size = -1;
	

//	if (dataLen > 0)
//	{
//		sem_wait(&dataBuffReadSem);
//		pthread_mutex_lock(&dataBuffMutex);
//		size = dataLen;
//		env->SetByteArrayRegion(readBuf,0,size,(jbyte*)dataBuff);
//		dataLen = -1;
//		pthread_mutex_unlock(&dataBuffMutex);
//		debugBuf("[JNI_RD]:", (BYTE*)dataBuff, size);
//
//	}
	size = flyNativeServerRead((char*)dataBuff, 4096);
	
	env->SetByteArrayRegion(readBuf,0,size,(jbyte*)dataBuff);

	return size;
}

static void flyModuleConfigInit()
{
	BYTE buf[] = {0xff,0xff};
	makeModuleCommMsgToModule(buf, 2, INITMSG_MODULE);
	debugBuf("[JNI_WR]:", buf, 2);
}
static jint jni_ioctl(JNIEnv *env, jobject thiz,  jint cmd, jbyteArray arg){
	char *buffer = (char*)env->GetByteArrayElements(arg, NULL);
	int length = env->GetArrayLength(arg);
	LOGE("jni_open -------jni_ioctl---------");
	//flyNativeServerInit();
	flyModuleConfigInit();

	env->ReleaseByteArrayElements(arg, (jbyte*)buffer, 0);

	return 0;
}

static void jni_lock(JNIEnv *env, jobject thiz)
{
	if(share_fd>0)
	{
		ioctl(share_fd, SEM_LOCK);
	}
}

static void jni_unlock(JNIEnv *env, jobject thiz)
{
	if(share_fd>0)
	{
		ioctl(share_fd, SEM_UNLOCK);
	}
}

static jint jni_writePageId(JNIEnv* env, jobject thiz, jint pageid)
{
	int ret = 0;

	if(share_fd>0)
	{
		short _pageId = (short)pageid;
		ioctl(share_fd, WRITE_PAGEID_FORJAVA, _pageId);
		LOGI("[%s] Open /dev/flysemdriver device %s",__FUNCTION__, share_fd<0?"failed":"true");
	}
	return ret;
}



static jint jni_readPageId(JNIEnv* env, jobject thiz)
{
	short page = -1;

	if(share_fd>0)
	{
		ioctl(share_fd, READ_PAGEID_FORJAVA, &page);
		LOGI("[%s] Open /dev/flysemdriver device %s",__FUNCTION__, share_fd<0?"failed":"true");
	}
	return (jint)page;

}



static jint jni_open(JNIEnv *env, jobject thiz){return 0;}
static jboolean jni_close(JNIEnv *env, jobject thiz){return 0;}






static  JNINativeMethod gMethods[] = {
	{"_open",				"()I",     			(void *)jni_open    },
	{"_write",				"([BI)I",        	(void *)jni_write   },
	{"_read",				"([BI)I",			(void *)jni_read    },
	{"_ioctl",				"(I[B)I",			(void *)jni_ioctl  	},
	{"_close",				"()Z",				(void *)jni_close   },
	{"lock",					"()V",			(void*)jni_lock		},
	{"unlock",				"()V",				(void*)jni_unlock	},
	{"writePageId",	"(I)I",				(void*)jni_writePageId	},
	{"readPageId",		"()I",					(void*)jni_readPageId	},
};


 /*
  * Register several native methods for one class.
  */
static int registerNativeMethods(JNIEnv* env, const char* className,
		JNINativeMethod* gMethods, int numMethods) {

	jclass clazz;

	clazz = env->FindClass(CLASS_NAME);
	if (clazz == NULL) {
		LOGE("Native registration unable to find class '%s'", className);
		return JNI_FALSE;
	}

	if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
		LOGE("RegisterNatives failed for '%s'", className);
		return JNI_FALSE;
	}

	return JNI_TRUE;
}

 /*
  * Register native methods for all classes we know about.
  *
  * returns JNI_TRUE on success.
  */
static int registerNatives(JNIEnv* env) {
	if (!registerNativeMethods(env, CLASS_NAME,
			gMethods, sizeof(gMethods) / sizeof(gMethods[0]))) {
		return JNI_FALSE;
	}

	return JNI_TRUE;
 }


 // ----------------------------------------------------------------------------

 /*
  * This is called by the VM when the shared library is first loaded.
  */

typedef union {
	JNIEnv* env;
	void* venv;
} UnionJNIEnvToVoid;

jint JNI_OnLoad(JavaVM* vm, void* reserved){

	UnionJNIEnvToVoid uenv;
	jint result = -1;
	JNIEnv* env = NULL;

	uenv.venv = NULL;

	LOGI("JNI_OnLoad for flyjni");
	flyNativeServerInit();

	if (vm->GetEnv(&uenv.venv, JNI_VERSION_1_4) != JNI_OK) {
	 LOGE("ERROR: GetEnv failed");
	 goto bail;
	}
	env = uenv.env;

	if (registerNatives(env) != JNI_TRUE) {
	 LOGE("ERROR: registerNatives failed");
	 goto bail;
	}

	result = JNI_VERSION_1_4;

bail:
	return result;
 }