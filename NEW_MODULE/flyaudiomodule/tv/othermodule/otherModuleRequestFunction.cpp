#include <string.h>
#include "global.h"
#include "moduleID.h"
#include "otherModuleRequestCommand.h"


//��ָ��ҳ
void tvToModule_NotifySystem_JumpPage(u16 nPageId){
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&nPageId,2);
     makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_SYSTEM,buf,3);
}

//��ǰһҳ
void tvToModule_NotifySystem_JumpPrePage(){
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_SYSTEM,buf,2);
}

//�л�����һ��ģ��
void tvToModule_NotifySystem_SwitchToModule(u8 nModuleID){
    u8 buf[] = {0x81,nModuleID};
    makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_SYSTEM,buf,2);
}

void tvToModule_NotifyOSD_aboutT123_VideoOSD_Button(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X40,0x00,0x03};
	buf[1]=swtich_button;
	buf[2]=button_status;
	makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_OSD,buf,3);

}
void tvToModule_NotifyOSD_aboutT123_colorSet_Value(u8 setOptions,u8 value)
{
	u8 buf[] = {0X03,0x00,0x00};
	buf[1]=setOptions;
	buf[2]=value;
	makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_OSD,buf,3);
}

void tvToModule_NotifyOSD_aboutT123_VideoOSDcolorSet(u8 swtich_button,u8 button_status)
{
	u8 buf[] = {0X41,0x00,0x00};
	buf[1]=swtich_button;
	buf[2]=button_status;
	makeAndSendMessageToModule(MODULE_ID_TV,MODULE_ID_OSD,buf,3);
}


