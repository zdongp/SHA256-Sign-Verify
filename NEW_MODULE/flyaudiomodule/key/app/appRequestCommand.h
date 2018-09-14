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
void setCommand(u32 ctrlId, u8 *param, int paramLen);

// setGroupNumber：
// 设置显示第几组图片
// 例如：DVD中的Folder_ITEM就是这样控制，0为空，1为文件夹，2为文件，3为正在播放
void setGroupNumber(u32 ctrlId, u8 groupIndex);

// setProgressRange：
// 设置滚动条的最大值，其对应设置滚动条位置值是用setAnalogData()
void setProgressRange(u32 ctrlId, int range);	// 原来是setValues()

// setExProgressRange:
// 设置扩展滚动条的最大值（如Sound中Balance部分），其对应的设置Pos位置值是
// 用setExProgressPos()或者setExProgressPos()函数
void setExProgressRange(u32 ctrlId, int xRange, int yRange);
void setExProgressPos(u32 ctrlId, int xPos, int yPos);
void setExProgressSinglePos(u32 ctrlId, u8 direct, int pos);
void setStringText(u32 ctrlId, u32 stringId);


void setOsdHidden(void);
void setOsdVolume(unsigned char vol);


void setAndroidSTDKey(u8 keyval);
void setPanelKeyToAndroid(u8 panel_key);

#endif
