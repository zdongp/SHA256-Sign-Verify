#ifndef __FLY_PROPERTIES_H__
#define __FLY_PROPERTIES_H__



#define FLY_PROPERTY_PATH		"/data/fly/.property"

#define MAX_STRING_LINE 		4096
#define MAX_STRING_LEN   		154
#define MAX_PROPERTY_KEY_LEN	60
#define MAX_PROPERTY_VALUE_LEN	92


int set_property(void);
int save_property(void);



#endif
