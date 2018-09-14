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

#include <dlfcn.h>


#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  

#include <android/log.h>

#include <jni.h>
#include "types_def.h"
#include "FlyInertialNavJni.h"
#include "moduleCommApi.h"
#include "commonFunc.h"


#define LOG_TAG "JNI_INERTIALNAV"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG ,  LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  ,  LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  ,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)

#define SERVER_PORT 5555  
int clientSocket;

#define PIPE_PATH           "/cache/fly_to_inertialNav_jni_fifo"
int pipe_fd = -1;


#define HAL_LIBRARY_PATH "/flysystem/lib/hw"
#define HALSTUBFILENAME	"/flysystem/inifile/halstublist.xml"


#define HAL_MODULE_MAX_NUM	30
#define DEVICE_NAME_MAX_LEN 	30

struct global_control_device_t{
	struct hw_device_t common;
	int (*global_read )( unsigned char *read_buf,  int buf_len);
	int (*global_write)( unsigned char *write_buf, int buf_len);
	int (*global_ioctl)( int cmd, unsigned char *arg);
	int (*global_close)();
} ;


struct global_control_device_t *dev = NULL;


BOOL initState = FALSE;
unsigned char dataBuff[4096];
int dataLen = -1;








/**
 * There are a set of variant filename for modules. The form of the filename
 * is "<MODULE_ID>.variant.so" so for the led module the Dream variants
 * of base "ro.product.board", "ro.board.platform" and "ro.arch" would be:
 *
 * led.trout.so
 * led.msm7k.so
 * led.ARMV6.so
 * led.default.so
 */

static const char *variant_keys[] = {
    "ro.hardware",  /* This goes first so that it can pick up a different
                       file on the emulator. */
    "ro.product.board",
    "ro.board.platform",
    "ro.arch"
};

static const int HAL_VARIANT_KEYS_COUNT =
    (sizeof(variant_keys)/sizeof(variant_keys[0]));

/**
 * Load the file defined by the variant and if successful
 * return the dlopen handle and the hmi.
 * @return 0 = success, !0 = failure.
 */
static int load(const char *id,
        const char *path,
        const struct hw_module_t **pHmi)
{
    int status;
    void *handle;
    struct hw_module_t *hmi;

    /*
     * load the symbols resolving undefined symbols before
     * dlopen returns. Since RTLD_GLOBAL is not or'd in with
     * RTLD_NOW the external symbols will not be global
     */
    handle = dlopen(path, RTLD_NOW);
    if (handle == NULL) {
        char const *err_str = dlerror();
        printf("load: module=%s\n%s\n", path, err_str?err_str:"unknown");
        status = -EINVAL;
        goto done;
    }

    /* Get the address of the struct hal_module_info. */
    hmi = (struct hw_module_t *)dlsym(handle, HAL_MODULE_INFO_SYM_AS_STR);
    if (hmi == NULL) {
        printf("load: couldn't find symbol %s\n", HAL_MODULE_INFO_SYM_AS_STR);
        status = -EINVAL;
        goto done;
    }

    if (strcmp(id, hmi->id) != 0) {
        printf("load: id=%s != fai->id=%s\n", id, hmi->id);
    }

    hmi->dso = handle;

    /* success */
    status = 0;

    done:
    if (status != 0) {
        hmi = NULL;
        if (handle != NULL) {
            dlclose(handle);
            handle = NULL;
        }
    } else {
        printf("loaded HAL id=%s path=%s hmi=%p handle=%p\n",
                id, path, *pHmi, handle);
    }

    *pHmi = hmi;

    return status;
}

int hw_get_module(const char *id, const struct hw_module_t **module)
{
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s.default.so", HAL_LIBRARY_PATH, id);
    if (access(path, R_OK) == 0) goto found;


    return -ENOENT;

found:
    /* load the module, if this fails, we're doomed, and we should not try
     * to load a different variant. */
    return load(id, path, module);
}


void makeMsgToHal(BYTE *msg, UINT length)
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
	buf[streamLen++] = 0x82;
    for (i = 0; i < length; i++)
    {
        buf[streamLen+i] = msg[i];
        checksum += msg[i];
    }
    streamLen += length;
	buf[streamLen++] = checksum;


	dev->global_write(buf, (int)streamLen);
	
	if (bMalloc)
	{
		free(buf);
		buf = NULL;
	}

}

void *readHalMsgThread(void *arg)
{
    pthread_t curPthread;
    curPthread = pthread_self();
	pthread_setname_np(curPthread, "HAL-navjniRead");

    BYTE buff[4096] = {0};
    int ret = 0;
    
    while (dev != NULL)
    {
        ret = ret = dev->global_read(buff, 4096);
        if (ret > 0)
        {
            debugBuf("navjni read data:", buff, ret);
        }
    }
    return NULL;

}


static void flyNativeServerInit(void)
{
	char *halstubName = "inertialNav";
	const struct hw_module_t *phw = NULL;
    struct hw_device_t *phwDev = NULL;

    pthread_t thread_id;
    INT res;


    debugTagSet(LOG_TAG);
    if (FALSE == initState)
    {
        if (hw_get_module(halstubName, &phw) < 0)
        {
            debugPrintf("hw_get_module %s fail ==> %s\n", halstubName, strerror(errno));
			return ;
        }
        if (NULL != phw)
        {
            phw->methods->open(phw, halstubName, &phwDev);
            {
                dev = (struct global_control_device_t *)phwDev;
                debugPrintf("open %s success\n", halstubName);
                initState = TRUE;
            
//                res = pthread_create(&thread_id, NULL ,readHalMsgThread, NULL);
                
            }
        }

    }
}


static int flyNativeServerRead(char *buf, int len)
{
    float f_gyroYaw, f_gyroPitch, f_gyroRoll, f_acceYaw, f_accePitch, f_acceRoll;
    float f_mountYaw, f_mountPitch, f_mountRoll;
    int res = 0;
	int ret = 0;
	if (TRUE == initState)
	{
		if (NULL != dev)
        {
            ret = dev->global_read((BYTE *)buf, len);
		    DBG0(debugBuf("[JNI_RD]:", (BYTE*)buf, (INT)ret););
            res += 2;
            memcpy((char *)&f_gyroYaw, (char*)&buf[res], 4);
            res += 4;
            memcpy((char *)&f_gyroPitch, (char*)&buf[res], 4);
            res += 4;
            memcpy((char *)&f_gyroRoll, (char*)&buf[res], 4);
            res += 5;

            memcpy((char *)&f_acceYaw, (char*)&buf[res], 4);
            res += 4;
            memcpy((char *)&f_accePitch, (char*)&buf[res], 4);
            res += 4;
            memcpy((char *)&f_acceRoll, (char*)&buf[res], 4);
            res += 5;

            memcpy((char *)&f_mountYaw, (char*)&buf[res], 4);
            res += 4;
            memcpy((char *)&f_mountPitch, (char*)&buf[res], 4);
            res += 4;
            memcpy((char *)&f_mountRoll, (char*)&buf[res], 4);
            res += 4;

        debugPrintf("f_gyroYaw %f, f_gyroPitch %f, f_gyroRoll %f \n \
                    , f_acceYaw %f, f_accePitch %f, f_acceRoll %f \n \
                    , f_mountYaw %f, f_mountPitch %f, f_mountRoll %f \n" \
            , f_gyroYaw, f_gyroPitch, f_gyroRoll \
            , f_acceYaw, f_accePitch, f_acceRoll \
            , f_mountYaw, f_mountPitch, f_mountRoll);

            
        }
	}
	return ret;
}


static int flyNativeServerWrite(char *buf, int len)
{
    BYTE data[256] = {0x10};
	if (TRUE == initState)
	{
		DBG0(debugBuf("[JNI_WR]:", (BYTE*)buf, (INT)len););
	    memcpy((char*)&data[1], buf, len);
    	makeMsgToHal((BYTE *)data, (UINT)(len+1));
		//makeModuleCommMsgToModule((BYTE*)&buf[3], (INT)len-4, JNIMSG_MODULE);
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

	size = flyNativeServerRead((char*)dataBuff, 4096);
	
	env->SetByteArrayRegion(readBuf,0,size,(jbyte*)dataBuff);

	return size;
}


static jint jni_open(JNIEnv *env, jobject thiz){return 0;}
static jboolean jni_close(JNIEnv *env, jobject thiz){return 0;}






static  JNINativeMethod gMethods[] = {
	{"_open",				"()I",     			(void *)jni_open    },
	{"_write",				"([BI)I",        	(void *)jni_write   },
	{"_read",				"([BI)I",			(void *)jni_read    },
	{"_close",				"()Z",				(void *)jni_close   },
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

	LOGI("JNI_OnLoad for FlyInertialNavjni");
	flyNativeServerInit();
    debugPrintf("JNI_OnLoad Init success\n");

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
