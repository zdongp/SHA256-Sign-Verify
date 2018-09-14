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
//#include <fcntl.h>
//#include <stdio.h>
//#include <string.h>
//#include <pthread.h>
//#include <linux/kernel.h>
//#include <errno.h>
//#include <sys/ioctl.h>
//#define SEM_MAGIC 's' //定义幻数
//#define SEM_MAX_NR 2 //定义命令的最大序�?


//#define SEM_LOCK _IO(SEM_MAGIC, 1) 		
//#define SEM_UNLOCK _IO(SEM_MAGIC, 2)	
//#define READ_PAGEID_FORC _IOR(SEM_MAGIC, 5 ,short) //C读取页面接口
//#define WRITE_PAGEID_FORC _IOW(SEM_MAGIC, 6 ,short)	//C写页面接�?


void setDigitalData(u32 ctrlId, int enable);
void setAnalogData(u32 ctrlId, int analog);
void setSerialData(u32 ctrlId, u8 *buffer, int len);
void jumpPage(u16 pageId);
void setVisible(u32 ctrlId, int visible);
void setControllable(u32 ctrlId, int controllable);
void setCommand(u32 ctrlId, u8 *param, int paramLen);

/**
 * setAnsiSerialData
 * ���� Ansi �ַ���
*/
void setAnsiSerialData(u32 id, u8 *p, u32 len);

// setGroupNumber��
// ������ʾ�ڼ���ͼƬ
// ���磺DVD�е�Folder_ITEM�����������ƣ�0Ϊ�գ�1Ϊ�ļ��У�2Ϊ�ļ���3Ϊ���ڲ���
void setGroupNumber(u32 ctrlId, u8 groupIndex);

// setProgressRange��
// ���ù����������ֵ�����Ӧ���ù�����λ��ֵ����setAnalogData()
void setProgressRange(u32 ctrlId, int range);	// ԭ����setValues()

// setExProgressRange:
// ������չ�����������ֵ����Sound��Balance���֣������Ӧ������Posλ��ֵ��
// ��setExProgressPos()����setExProgressPos()����
void setExProgressRange(u32 ctrlId, int xRange, int yRange);
void setExProgressPos(u32 ctrlId, int xPos, int yPos);
void setExProgressSinglePos(u32 ctrlId, u8 direct, int pos);
void setStringText(u32 ctrlId, u32 stringId);


void setOsdHidden(void);
void setOsdVolume(unsigned char vol);
void setOsdInfoControl(u8 *param, u8 len);


void setAndroidSTDKey(u8 keyval);
void setPanelKeyToAndroid(u8 panel_key);
void setScreenBrightnessCtrl(unsigned char brightness);

void setShowDebugInfo(u8 *buffer, u8 len);

void setUpdateUI(unsigned char update);


void System_ReturnAppStandyState(bool bstandby);
void Handle_NOBarCode(void);
void setOneBarcode(u8 *buffer, int len);

//2012-06-26
void System_NotifyAppEnterTimePage();

void System_NotifyAppExitTimePage();

void System_NotifyApp12_24();
void System_NotifyApp_HourInc();
void System_NotifyApp_HourDec();
void System_NotifyApp_MutInc();
void System_NotifyApp_MutDec();
void System_notifyApp_battery_state(u8 u8_Param);

void System_notifyApp_AUTO_SOUND_ON(u8 u8_Param);

void System_notifyApp_PingLoop(u8 u8_Param);
void System_notifyApp_BrakeState(u8 u8_Param);
void System_notifyApp_DisplayBrakecarPromtBox(u8 u8_Param);
void System_notifyApp_OtaJumpPage(u8 u8_Param);
void System_notifyApp_cvbsOrUsbSwitch(u8 u8_Param);
void System_notifyApp_EyeProtectionModeSwitch(u8 p);
void System_notifyApp_DesktopNavigationMapInformationsSyncSwitchState(u8 u8_Param);
void System_notifyApp_ChoiceNavigationMapInformations(u8 *PackgN,u8 PackgN_Len,u8 *classN,u8 classN_Len);


#endif
