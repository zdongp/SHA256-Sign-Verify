#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

void moduleToAux_FromKey_AnalyseMsg(unsigned char* buf,int len);   //��������KeyModule����Ϣ
void moduleToAux_FromSystem_AnalyseMsg(unsigned char* buf,int len);//��������SystemModule����Ϣ
void moduleToAux_FromAudio_AnalyseMsg(unsigned char* buf,int len); //��������SoundModule����Ϣ
void moduleToAux_FromExternalCtrl_AnalyseMsg(unsigned char* buf,int len);
void moduleToAux_FromAutomate_AnalyseMsg(unsigned char* buf,int len);

//Get Panel Key Msg
void moduleToAux_FromKey_DispatchProcessKeyCmd(unsigned char ucCmd); //Dispatch Process Cmd From KeyModule

void moduleToAux_FromSystem_SaveDataToRestart();//��λ����
void moduleToAux_FromSystem_RestoreToFactoryDefaults(); //Restore To Factory Defaults

void moduleToAux_FromSystem_EnterVideo();
void moduleToAux_FromSystem_EnterCtrlFace();

void moduleToAux_FromKey_ProcessPanelKey_NAVI();            //NAVI
void moduleToAux_FromKey_ProcessPanelKey_MENU();            //Menu
void moduleToAux_FromKey_ProcessPanelKey_AV();            //AV
void moduleToAux_FromKey_ProcessPanelKey_AUX();          //aux


void moduleToAux_FromSystem_BrakeState(char cBrake);//�Ƿ�ɲ��״̬
	

#endif
