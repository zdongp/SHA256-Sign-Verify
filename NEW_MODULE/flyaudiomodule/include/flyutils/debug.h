#ifndef __FLY_UTILS_DEBUG_H_
#define __FLY_UTILS_DEBUG_H_

#include <stdio.h>
#include <stdarg.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

typedef void (*ptrPrintLog)(char *fmt, ...);
void printLog_none(char *fmt, ...);

__END_DECLS

#endif
