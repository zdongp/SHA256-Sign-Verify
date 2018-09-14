#ifndef __APP_REQUEST_COMMAND_H__
#define __APP_REQUEST_COMMAND_H__

#define UI_VISIBLE		1
#define UI_INVISIBLE	0

#define UI_ENABLE		1
#define	UI_DISABLE		0

#define UI_FRONT		0
#define UI_BACK			1
#define UI_GRAY			2

#define UI_CTRL_ENABLE	1
#define UI_CTRL_DISABLE	0

#define UI_CONTROL_TYPE_DIGITAL		0x00
#define UI_CONTROL_TYPE_ANALOG		0x01
#define UI_CONTROL_TYPE_SERIAL		0x02
#define UI_CONTROL_TYPE_PARAMSET	0xFF


void setDigitalData(int controlId, int enable);
void setAnalogData(int controlId, int analog);
void setSerialData(int controlId, u8 *buffer, int len);
void setVisible(int controlId, int visible);
void setControllable(int controlId, int controllable);
void setValues(int controlId, int values);

void setGroupNumber(u32 ctrlId, u8 groupIndex);
void setProgressRange(u32 ctrlId, int range);
void setUpdateUI(unsigned char update);
void setCommand(int controlId, u8 *param, int paramLen);


#endif
