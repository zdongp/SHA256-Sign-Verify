#ifndef __DEBUG_H__
#define __DEBUG_H__


#include <stdarg.h>
#include <android/log.h>

#include <../flyutils/debug.h>
#include "config.h"


//typedef enum android_LogPriority {
//    ANDROID_LOG_UNKNOWN = 0,
//    ANDROID_LOG_DEFAULT,    /* only for SetMinPriority() */
//    ANDROID_LOG_VERBOSE,
//    ANDROID_LOG_DEBUG,
//    ANDROID_LOG_INFO,
//    ANDROID_LOG_WARN,
//    ANDROID_LOG_ERROR,
//    ANDROID_LOG_FATAL,
//    ANDROID_LOG_SILENT,     /* only for SetMinPriority(); must be last */
//} android_LogPriority;


//typedef void (*ptrPrintLog)(char *fmt, ...);
extern ptrPrintLog		printLog;  // extern form FlyDebut.cpp's printLog = printLog_none


//�ر�
#define LOGV(...)		printLog(__VA_ARGS__)
#define LOGD(...)		printLog(__VA_ARGS__)
#define LOGI(...)		printLog(__VA_ARGS__)
#define LOGW(...)		printLog(__VA_ARGS__)
#define LOGE(...)		printLog(__VA_ARGS__)
#define LOGF(...)		printLog(__VA_ARGS__)
#define LOGS(...)		printLog(__VA_ARGS__)


/*
//����
#ifdef  DEBUG_DISABLE
#define LOGV(...)	(void(0))
#define LOGD(...)	(void(0))
#define LOGI(...)	(void(0))
#define LOGW(...)	(void(0))
#define LOGE(...)	(void(0))
#else
#if 0
#define LOGV(fmt, ...)	__android_log_print(ANDROID_LOG_VERBOSE, TAG, "[%s:%d] "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGD(fmt, ...)	__android_log_print(ANDROID_LOG_DEBUG, TAG, "[%s:%d] "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGI(fmt, ...)	__android_log_print(ANDROID_LOG_INFO, TAG, "[%s:%d] "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGW(fmt, ...)	__android_log_print(ANDROID_LOG_WARN, TAG, "[%s:%d] "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGE(fmt, ...)	__android_log_print(ANDROID_LOG_ERROR, TAG, "[%s:%d] "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGV(...)	__android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...)	__android_log_print(ANDROID_LOG_DEBUG ,  TAG, __VA_ARGS__)
#define LOGI(...)	__android_log_print(ANDROID_LOG_INFO  ,  TAG, __VA_ARGS__)
#define LOGW(...)	__android_log_print(ANDROID_LOG_WARN  ,  TAG, __VA_ARGS__)
#define LOGE(...)	__android_log_print(ANDROID_LOG_ERROR  , TAG, __VA_ARGS__)
#endif
#endif
*/



#endif





