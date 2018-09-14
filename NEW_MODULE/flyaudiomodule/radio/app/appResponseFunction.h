#ifndef __APP_RESPONSE_FUNCTION_RADIO_H__
#define __APP_RESPONSE_FUNCTION_RADIO_H__

void appToRadio_MenuRadio_MouseUp();//Radio�����˵��İ�ť
void appToRadio_Back_MouseUp();//���ذ�ť
void appToRadio_Eq_MouseUp(void); //EQ
void appToRadio_Eq_MouseDown(void);
void appToRadio_Audio_MouseUp(void);//Audio
void appToRadio_Audio_MouseDown(void);
void appToRadio_TurnOFF_MouseUp(void);//�ر�������
void appToRadio_RadioChannel_MouseUp(char type);//FM1 FM2 AM ѡ��
void appToRadio_RadioChannel_MouseDown(char type);
void appToRadio_Scan_MouseUp(void);//Scan
void appToRadio_FreqCtrl_MouseDown(char type);
void appToRadio_FreqCtrl_MouseUp(char type);//Ƶ��ѡ��
void appToRadio_Channel_MouseTimer(char channel);//����Ƶ��
void appToRadio_Channel_MouseUp(char channel);//Ƶ������
void appToRadio_Channel_MouseDown(char cRecordIndex);


void appToRadio_SaveRecord(u32 cIndex);
u8 appToRadio_IsCanShowOSD(u32 nPageID);



void appToRadio_Set_MouseUp(void);

void appToRadio_Next_MouseUp(void);
void appToRadio_Scan_Inc_MouseUp(void );
void appToRadio_Scan_Dec_MouseUp(void);
void appToRadio_Set_Back_MouseUp(void );
void appToRadio_Set_TA_MouseUp(u8 state);
void appToRadio_Main_Frequency_MouseUp(void);
void appToRadio_Set_AF_MouseUp(u8 state);
void appToRadio_Number_num(int num);
void appToRadio_Number_Point(void);
void appToRadio_Number_Del(void );
void appToRadio_Number_Cancel(void);
void appToRadio_Number_OK(void);
void appToRadio_Number(unsigned char key);
void appToRadio_Radio_Numb(u8 key);
void appToRadio_Number_Back(void);

void appToRadio_Main_Gauge_MouseUp(unsigned char *param,unsigned char len);
void appToRadio_MAIN_PrePage(void);
void appToRadio_MAIN_NextPage(void);

void appToRadio_ClearRecord(u32 index);
void appToRadio_Scan_MouseTimer(void);
void appToRadio_ClearAllFrequencyRecord(u8 nChannel);
void appToRadio_Scan_MoudeDown();
void appToRadio_Main_SetSensitivity(u32 ctrlID );    /*����������*/
void appToRadio_Main_SetAF(u32 ctrlID );
void appToRadio_Main_SetTA(u32 ctrlID );
void appToRadio_Main_Delete(void );    /*ɾ���̨*/

void appToRadio_Analyze_FrequencyMessage();
void appToRadio_Radio_FM_AM_Switch();
void appToRadio_FreqCtrl_SearchType(char type);
void RadioToUI_Main_SetFineTuneButton(int p,char param);
void appToRadio_FreqCtrl_SetFineTune_MouseUp(char type);
void sdkToModuleSetRepeatScan();


#endif
