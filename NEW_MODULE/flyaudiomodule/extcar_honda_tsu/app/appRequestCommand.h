#ifndef __APP_REQUEST_COMMAND_H__
#define __APP_REQUEST_COMMAND_H__

#include "global.h"

#define UI_CONTROL_TYPE_DIGITAL 	0x00
#define UI_CONTROL_TYPE_ANALOG		0x01
#define UI_CONTROL_TYPE_SERIAL		0x02
#define UI_CONTROL_TYPE_PARAMSET	0xFF


void setDigitalData(u32 ctrlId, int enable);
void setAnalogData(u32 ctrlId, int analog);
void setSerialData(u32 ctrlId, u8 *buffer, int len);
void setAnsiSerialData(u32 ctrlId, u8 *buffer, int len);
void setVisible(u32 ctrlId, int visible);
void setControllable(u32 ctrlId, int controllable);
void setGroupNumber(u32 ctrlId, u8 groupIndex);
void setProgressRange(u32 ctrlId, int range);
void setExProgressRange(u32 ctrlId, int xRange, int yRange);
void setExProgressPos(u32 ctrlId, int xPos, int yPos);
void setExProgressSinglePos(u32 ctrlId, u8 direct, int pos);
void setStringText(u32 ctrlId, u32 stringId);
void setUpdateUI(u8 update);
void sendToExtcarHondaTsuFlyJniSdkService(u8 moduleId, u8 *p, u8 len);



#endif
