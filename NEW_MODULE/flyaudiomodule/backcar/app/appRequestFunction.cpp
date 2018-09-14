#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "pageID.h"


void BackcarToApp_Displaying_VideoColorSet(u8 state)
{
	setDigitalData(CONTROLID_BACK_VIDEO_SET_BUTTON,state);
}

void BackcarToApp_Displaying_WarnintLineText(bool state)
{
	setVisible(CONTROLID_BACK_VIDEO_WARNINT_LINE_TEXT,state);
	backCarToModule_NotifyOSD_aboutT123_BackCarWarningsDisplay(state);
}

void BackcarToApp_Displaying_RedWarningLine(bool state)
{
	setVisible(CONTROLID_BACK_VIDEO_OSD_RED_LINE,state);
	setVisible(CONTROLID_BACK_VIDEO_TRACE_TYPE,state);
}

void BackcarToApp_Displaying_TraceLine_SetButton(bool state)
{
	setVisible(CONTROLID_BACK_VIDEO_TRACE_TYPE_SWITCH,state);
	setVisible(CONTROLID_BACK_VIDEO_TRACE_TYPE_CHANGE,state);
}

void BackcarToApp_Inside_ActShowAnswerBox(int isShow)
{
	setUpdateUI(0);

	setVisible(CONTROLID_BACK_VIDEO_CALL_BACKGROUND, isShow);
	setVisible(CONTROLID_BACK_VIDEO_PHONE_NUMBER, isShow);
	setVisible(CONTROLID_BACK_VIDEO_CALL_IN_OR_OUT, isShow);
	setVisible(CONTROLID_BACK_VIDEO_HAND_UP, isShow);
	setVisible(CONTROLID_BACK_VIDEO_CALL_IN, isShow);

	setUpdateUI(1);
}

void BackcarVideo_BackGroundColor_Set(bool state)
{
	if(state)
	{
	    pLocalParam->bBackVideo_SetColor=false;
	    backCarToModule_NotifyOSD_aboutT123_ChangePage_OSDDispalying(MODULE_ID_OSD,PAGE_BACK_VIDEO,PAGE_BACK_VIDEO_T123COLORSET_PAGE,1);
	}
	else
	{
	    pLocalParam->bBackVideo_SetColor=true;
	    backCarToModule_NotifyOSD_aboutT123_ChangePage_OSDDispalying(MODULE_ID_OSD,PAGE_BACK_VIDEO_T123COLORSET_PAGE,PAGE_BACK_VIDEO,1);
	}

    BackcarVideo_IsShowVideoColorButton(state);
}

void BackcarVideo_IsShowVideoColorButton(bool state)
{
    setUpdateUI(0);
	//BackcarToApp_Displaying_RedWarningLine(!state);
	//setVisible(CONTROLID_BACK_VIDEO_OSD_GROUND_SET_MASK, state);//�ɰ�
	setVisible(CONTROLID_BACK_VIDEO_SET_BUTTON, !state); 
	setVisible(CONTROLID_BACK_VIDEO_SET_CONTRAST_FILE, state); //�Աȶ�����
	setVisible(CONTROLID_BACK_VIDEO_SET_CONTRAST, state);
	setVisible(CONTROLID_BACK_VIDEO_SET_CONTRAST_JIAN, state);// �Աȶ� ��
	setVisible(CONTROLID_BACK_VIDEO_SET_CONTRAST_JIA, state);// �Աȶ� ��
	setVisible(CONTROLID_BACK_VIDEO_SET_TONE_FILE, state); //���Ͷ�����
	setVisible(CONTROLID_BACK_VIDEO_SET_TONE, state);
	setVisible(CONTROLID_BACK_VIDEO_SET_TONE_JIAN, state);//���Ͷ� ��
	setVisible(CONTROLID_BACK_VIDEO_SET_TONE_JIA, state);//  ���Ͷ� ��
	setVisible(CONTROLID_BACK_VIDEO_SET_SATURATION_FILE, state); //ɫ������
	setVisible(CONTROLID_BACK_VIDEO_SET_SATURATION, state);
	setVisible(CONTROLID_BACK_VIDEO_SET_SATURATION_JIAN, state);//  ɫ��	��
	setVisible(CONTROLID_BACK_VIDEO_SET_SATURATION_JIA, state);//  ɫ��  ��
	setVisible(CONTROLID_BACK_VIDEO_SET_BRIGHTNESS_JIAN, state);//  ɫ��	��
	setVisible(CONTROLID_BACK_VIDEO_SET_BRIGHTNESS_JIA, state);//  ɫ��  ��
	setUpdateUI(1);

}
void setToUI_BackCarLine_Type(int em)
{
	ToUI_BackCarVideo_TraceType((Em_Backcar_TraceType)em);
}