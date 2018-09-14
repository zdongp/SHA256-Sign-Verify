#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/types.h>

#include <android/log.h>

#include <flyutils/debug.h>
#include <string.h>

#include "commonFunc.h"


typedef void (*debugPrintFunc)(void* cookie, const char* txt);

void printHexDebugData(const void *buf, size_t length, debugPrintFunc func=0, void *cookie=0);



void log_output(const char* msg, const char* buffer, const int length);
void dyb_log_output(const char*name, const char* msg, const char* buffer, const int length, ptrPrintLog pFun, char * tag);


//�ر�
//#define TAG	"dyb"
#define LOGI(...)		debugPrintf(__VA_ARGS__)


static void defaultPrintFunc(void* cookie, const char* txt)
{
    printf("%s", txt);
}

static inline char makelowerhexdigit(uint32_t val)
{
    return "0123456789abcdef"[val&0xF];
}

static inline char makeupperhexdigit(uint32_t val)
{
    return "0123456789ABCDEF"[val&0xF];
}


void printHexDebugData(const void *buf, size_t length, debugPrintFunc func, void *cookie)
{
	if(!func) func = defaultPrintFunc;

	size_t offset, bytesPerLine;
	unsigned char *pos = (unsigned char*)buf;
	if(!pos || (length <=  0)) return;

	static char buffer[1024] = {0};
	memset(buffer, 0, sizeof(buffer));
	static const size_t maxBytesPerLine = ((128-12-1)/3)&~0xF;

	size_t word;
	char *c = 0;
	offset = 0;
	while(1)
	{
		c = buffer;
        sprintf(c, "0x%08x: ", (int)offset);
        c += 12;

        bytesPerLine = (length > maxBytesPerLine)? maxBytesPerLine:length;
        for (word = 0; word < bytesPerLine; word++) {
			 const unsigned char val = *(pos+word);
            *c++ = makeupperhexdigit(val>>4);
            *c++ = makeupperhexdigit(val);
            *c++ = ' ';
            if((word & 0x07) ==  0x07) *c++ = ' ';
        }
		*c = 0;

		func(cookie, buffer);
        if(length <= bytesPerLine) break;

        length -= bytesPerLine;
        pos += bytesPerLine;
        offset += maxBytesPerLine;
	}
}

void printLog_none(char *fmt, ...)
{
	return ;
}



void log_output(const char* msg, const char* buffer, const int length)
{
	//if (printLog != printLog_none)
	{
		int len = length * 3 + strlen(msg) + 1;
		char *out = (char*)malloc(len);
		if (!out) return ;

		memset(out, 0, sizeof(char) * len);
		snprintf(out, len, "%s:", msg);

		int i, j = strlen(msg);
		for (i = 0; i < length; i++)
			{
				snprintf(out + j, len - j, "%02X ", buffer[i]);
				j += 3;
			}
		LOGI("%s", out);
		//__android_log_print(out, "dyb", __VA_ARGS__);
		free(out);
	}
	
}

void dyb_log_output(const char*name, const char* msg, const char* buffer, const int length, ptrPrintLog pFun, char * tag)
{
	if (pFun != printLog_none)
	{
		int len = strlen(name)+strlen(msg)+1;
		char *_msg = (char*)malloc(len);
		if(!_msg) return;

		if(name && msg)
			snprintf(_msg, len, "%s%s", name, msg);
			
		log_output(_msg, buffer, length);

		free(_msg);
	}

}

