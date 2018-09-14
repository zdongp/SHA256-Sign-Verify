#ifndef __PARAM_H__
#define __PARAM_H__

#include "global.h"

#define INFORS_MAX_LEN 100

typedef struct{
	u8 uc_Barcode[INFORS_MAX_LEN];
	u8 uc_IMEI_Infors[INFORS_MAX_LEN];
	u8 uc_MAC_Infors[INFORS_MAX_LEN];
	u8 uc_WIFI_Status;
	short uc_WIFI_NetworkSignal;
	short uc_4G_NetworkSignal;
	u8 uc_MemoryUsageSd1_Infors[INFORS_MAX_LEN];
	u8 uc_TotalSizeSd1_Infors[INFORS_MAX_LEN];
	u8 uc_MemoryUsageSd0_Infors[INFORS_MAX_LEN];
	u8 uc_TotalSizeSd0_Infors[INFORS_MAX_LEN];
	u8 uCurSd1Status;
	u8 uTheNetworkStatus_WiFi;
	u8 uTheNetworkStatus_4G;
}local_param_t;

typedef struct{
}global_param_t;

extern local_param_t localParam;
extern global_param_t globalParam;


extern local_param_t *pLocalParam;
extern global_param_t *pGlobalParam;




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
