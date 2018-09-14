#ifndef __PARAM_H__
#define __PARAM_H__

enum emSystemSwitchCmd{SwitchModuleCmd=0x81,SwitchCurPageCmd=0x82,SwitchPrePageCmd=0x83};


typedef struct {
	u8 bBrakeState;//ɲ���Ŀ���
	u8 bEnterAux;//����AUX���

	u8 bInAuxChannel;//�Ƿ���AUXͨ��
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
