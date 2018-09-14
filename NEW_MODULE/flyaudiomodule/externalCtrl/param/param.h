#ifndef __PARAM_H__
#define __PARAM_H__
#include "externalJniSdk.h"

typedef struct {

	bool bIsAutoJumpPrePage;
	u8 uCurSpeechState;
	CExternalJniSdk g_pClsExternalJniSdk;
}local_param_t;

typedef struct{

}global_param_t;


extern local_param_t *pLocalParam;
extern global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
