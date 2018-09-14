#ifndef __PARAM_H__
#define __PARAM_H__

typedef struct {
	u8 uIsAgreePageHide;
}local_param_t;

typedef struct{

}global_param_t;


extern local_param_t *pLocalParam;
extern global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
