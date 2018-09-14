#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

void appToSYNC_MainButton_MouseUp(u32 FunID);
void appToSYNC_MainButton_MouseDown(u32 FunID);
void appToSYNC_MainButton_MouseTimer(u32 FunID);

void appToSYNC_InSpeech_MouseUp(void);
void appToSYNC_ApplicationButton_MouseUp();

void appToSYNC_MENUSync_MouseUp();
void appToSYNC_MainBACK_MouseUp();
void appToSYNC_MainAudio_MouseUp();

void test();
void test1();

void appToSyncModule_BackNextPage_File_Button(int ctrlId,char ctrlType);


#endif
