#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__

void moduleToAux_FromKey_AnalyseMsg(unsigned char* buf,int len);   //分析来自KeyModule的消息
void moduleToAux_FromSystem_AnalyseMsg(unsigned char* buf,int len);//分析来自SystemModule的消息
void moduleToAux_FromAudio_AnalyseMsg(unsigned char* buf,int len); //分析来自SoundModule的消息
void moduleToAux_FromExternalCtrl_AnalyseMsg(unsigned char* buf,int len);
void moduleToAux_FromAutomate_AnalyseMsg(unsigned char* buf,int len);

//Get Panel Key Msg
void moduleToAux_FromKey_DispatchProcessKeyCmd(unsigned char ucCmd); //Dispatch Process Cmd From KeyModule

void moduleToAux_FromSystem_SaveDataToRestart();//复位保存
void moduleToAux_FromSystem_RestoreToFactoryDefaults(); //Restore To Factory Defaults

void moduleToAux_FromSystem_EnterVideo();
void moduleToAux_FromSystem_EnterCtrlFace();

void moduleToAux_FromKey_ProcessPanelKey_NAVI();            //NAVI
void moduleToAux_FromKey_ProcessPanelKey_MENU();            //Menu
void moduleToAux_FromKey_ProcessPanelKey_AV();            //AV
void moduleToAux_FromKey_ProcessPanelKey_AUX();          //aux


void moduleToAux_FromSystem_BrakeState(char cBrake);//是否刹车状态
	

#endif
