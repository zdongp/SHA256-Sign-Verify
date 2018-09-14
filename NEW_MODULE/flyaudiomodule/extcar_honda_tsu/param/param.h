#ifndef __PARAM_H__
#define __PARAM_H__

#include "CNotifyAndResponseFlyJniSdk.h"

typedef struct {

}extcar_local_param_t;

typedef struct{
	
}extcar_global_param_t;


extern extcar_local_param_t *pLocalParam;
extern extcar_global_param_t *pGlobalParam;

extern CNotifyAndResponseFlyJniSdk g_clsExtcarHondaTsu;

void readParameter(void);
void saveParameter(void);



typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
uni16_size_t uni16_strlen(const unicode16_t *uni16);
unicode16_t ansi_to_unicode16(const unsigned char ansi);
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);

#endif
