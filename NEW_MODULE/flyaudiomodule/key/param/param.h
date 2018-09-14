#ifndef __PARAM_H__
#define __PARAM_H__
#include "keyJniSdk.h"


typedef struct{
		u8 m_iSoundChannel;//channel

		int n_DispatchBySoundMode;
		bool u_bSync_BTCall;

		bool bKeyAction_DropDownOSD;
		CKeyJniSdk *g_pClsKeyJniSdk;
}key_local_param_t;

typedef struct{
	
}key_global_param_t;

extern key_local_param_t *pLocalParam;
extern key_global_param_t *pGlobalParam;


void recoverDefaultParam(void);

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



#endif
