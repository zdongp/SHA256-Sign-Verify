#ifndef __APP_REQUEST_COMMAND_H__
#define __APP_REQUEST_COMMAND_H__

#include "global.h"


#define UI_VISIBLE		1
#define UI_INVISIBLE	0

#define UI_ENABLE		1
#define UI_DISABLE		0

#define UI_FRONT		0
#define UI_BACK			1
#define UI_GRAY			2

#define UI_CTRL_ENABLE	1
#define UI_CTRL_DISABLE	0


#define UI_CONTROL_TYPE_DIGITAL 	0x00
#define UI_CONTROL_TYPE_ANALOG		0x01
#define UI_CONTROL_TYPE_SERIAL		0x02
#define UI_CONTROL_TYPE_PARAMSET	0xFF


void setDigitalData(u32 ctrlId, int enable);
void setAnalogData(u32 ctrlId, int analog);
void setSerialData(u32 ctrlId, u8 *buffer, int len);
void setVisible(u32 ctrlId, int visible);
void setControllable(u32 ctrlId, int controllable);

// setGroupNumber��
// ������ʾ�ڼ���ͼƬ
// ���磺DVD�е�Folder_ITEM����������ƣ�0Ϊ�գ�1Ϊ�ļ��У�2Ϊ�ļ���3Ϊ���ڲ���
void setGroupNumber(u32 ctrlId, u8 groupIndex);

// setProgressRange��
// ���ù����������ֵ�����Ӧ���ù�����λ��ֵ����setAnalogData()
void setProgressRange(u32 ctrlId, int range);	// ԭ����setValues()

// setExProgressRange:
// ������չ�����������ֵ����Sound��Balance���֣������Ӧ������Posλ��ֵ��
// ��setExProgressPos()����setExProgressPos()����
void setExProgressRange(u32 ctrlId, int xRange, int yRange);
void setExProgressPos(u32 ctrlId, int xPos, int yPos);
void setExProgressSinglePos(u32, u8 direct, int pos);


void setCamaraReadyForOpen(u8 bReady);
void setUpdateUI(unsigned char update);
void setRingerCtrl(unsigned char ring);
void setMixedExternalAppVoiceState(unsigned char status);

void setSoundChannelState_ToApp(u8 uChannel);
void setVolumeValue_ToApp(u8 uVolume);
void setIsMute_CurSysMediaChannelToApp(u8 uMute);
void setModulesInitCompleted(void);
void setExProgressSingleOnePos(u32 ctrlId,short x,short y);
void sendToAudioFlyJniSdkService(u8 moduleId, u8 *p, int len);


#endif
