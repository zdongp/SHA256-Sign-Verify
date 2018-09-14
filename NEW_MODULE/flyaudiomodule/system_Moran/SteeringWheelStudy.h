#pragma once

#include "FlyObject.h"

#define KEY_MAX_NUM		256

#define	FUNC_CTRL_ID_KEY_BEGIN		CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_BEGIN

class CFlyObject;
class CSteeringWheelStudy  : public CFlyObject
{
public:
	CSteeringWheelStudy(void);
	~CSteeringWheelStudy(void);

	bool processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	bool processHalMsg(u8 cmd, u8 *p, u8 len);

	void clickWheelKeyStudy(E_MOUSE_STATUS e);
	void clickKey(E_MOUSE_STATUS e, u32 id);
	void clickApply(E_MOUSE_STATUS e);
	void clickDelete(E_MOUSE_STATUS e);
	
	//update
	void updateWheelKeyStudyState(void);

	//assit
	const char* getMouseMessageType(u8 p);
	void setPage(int nPageId);

	//hal
	void setToHalApplyStudyKey(u8 p);
	void setToHalStudyKey(u8 key);
	void setToHalCancleStudyKey(void);
	void setToHalDeleteStudyKey(u8 p);

	void getFromHalApplySelfDefineSteerWheelDesign(u8 p);
	void getFromHalStudyKeyState(u8 p);
	void getFromHalKeyState(u8 *p, int len);

private:
	bool m_bBeginStudyKey;

	u8 m_szKeyState[32];
	bool m_szbCtrlIdHaveDown[KEY_MAX_NUM];
	bool m_szbCtrlIdHavdDoneMouseTimer[KEY_MAX_NUM];

};
