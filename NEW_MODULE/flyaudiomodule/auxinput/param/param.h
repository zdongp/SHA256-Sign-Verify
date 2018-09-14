#ifndef __PARAM_H__
#define __PARAM_H__

enum emSystemSwitchCmd{SwitchModuleCmd=0x81,SwitchCurPageCmd=0x82,SwitchPrePageCmd=0x83};


typedef struct {
	u8 bBrakeState;//刹车的控制
	u8 bEnterAux;//进入AUX与否

	u8 bInAuxChannel;//是否在AUX通道
	u8 bInSleep;
	u8 uSleepOnDealLogic;

	u8 uAUX_VideoSwitch;

}aux_local_param_t;

typedef struct{
	
}aux_global_param_t;


extern aux_local_param_t *pLocalParam;
extern aux_global_param_t *pGlobalParam;



void readParameter(void);
void saveParameter(void);




#endif
