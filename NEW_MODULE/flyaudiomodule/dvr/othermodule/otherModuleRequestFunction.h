#ifndef __OTHERMODULE_REQUEST_FUNCTION_H__
#define __OTHERMODULE_REQUEST_FUNCTION_H__

void dvrToModule_NotifySystem_JumpPage(u16 pageID);
void dvrToModule_NotifySystem_JumpPrePage(void);
void dvrToModule_NotifySystem_BackCarProtocolState(u8 state);

void dvrToModule_NotifyAuxscreen_State(char state);
void dvrToModule_NotifyAutoMate_State(char resCmd,u8 *param,u8 len);


void dvrToModule_NotifyOSD_aboutT123_VideoOSD_dvrMenu_Button(u8 swtich_button,u8 button_status);
void dvrToModule_NotifyOSD_aboutT123_VideoOSD_videoset_Button(u8 swtich_button,u8 button_status);
void dvrToModule_NotifyOSD_aboutT123_VideoOSD_recordPlay_Button(u8 swtich_button,u8 button_status);
void dvrToModule_NotifyOSD_aboutT123_VideoOSD_timeset_Button(u8 swtich_button,u8 button_status);
void dvrToModule_NotifyOSD_SetYMDaboutT123_VideoOSD(int nYMD);

void setTimerSyncTimeToDVR(void);
void killTimerSyncTimeToDVR(void);

void syncTimeToDVR(void);

void dvrtodnv(void);


#endif
