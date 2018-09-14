#ifndef FLYPROP_H
#define FLYPROP_H

#ifdef __cplusplus
extern "C"{
#endif

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define PROPERTY_VALUE_MAX          512

extern int property_get(const char* property, char* value, const char* defaultValue);
extern int property_set(const char* property, const char* value);

#ifdef __cplusplus
}
#endif

#endif // FLYPROP_H
