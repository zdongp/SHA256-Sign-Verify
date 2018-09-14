#include "SteeringWheelStudy.h"

#include "param.h"
#include "global.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "halResponseCommand.h"
#include "halRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include <flymoduleApi_internal.h>

CSteeringWheelStudy::CSteeringWheelStudy(void)
{
	m_bBeginStudyKey = false;

	memset(m_szKeyState, 0, sizeof(m_szKeyState));
	memset(m_szbCtrlIdHaveDown, 0, sizeof(m_szbCtrlIdHaveDown));
	memset(m_szbCtrlIdHavdDoneMouseTimer, 0, sizeof(m_szbCtrlIdHavdDoneMouseTimer));
}

CSteeringWheelStudy::~CSteeringWheelStudy(void)
{
}

bool CSteeringWheelStudy::processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len)
{
	LOGD("[%s] id = [0x%x], mouseStatus = [%s]", __FUNCTION__, id, getMouseMessageType(e));
	//outPutLog(__FUNCTION__, "p", p, len);

	bool bRet =true;
	
	switch(id)
	{
	case CONTROLID_SETUP_WHEEL_LEARNING:
		clickWheelKeyStudy(e);
		break;
	case CONTROLID_SYSTEM_WHEEL_LEARNING_APPLY:
		clickApply(e);
		break;
	case CONTROLID_SYSTEM_WHEEL_LEARNING_BACK:
		if (e == MOUSE_STATUS_UP)
			//systemToModule_NotifySystem_JumpPrePage();
		setPage(PAGE_SETUP_BEGIN + 4);
		break;
	case CONTROLID_SYSTEM_WHEEL_LEARNING_DELETE:
		clickDelete(e);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_ONE_PRE:
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_ONE_NEXT:
		if (e == MOUSE_STATUS_UP)
		setPage(PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_TWO);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_TWO_PRE:
		if (e == MOUSE_STATUS_UP)
		setPage(PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_ONE);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_TWO_NEXT:
		if (e == MOUSE_STATUS_UP)
		setPage(PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_THREE);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_THREE_PRE:
		if (e == MOUSE_STATUS_UP)
		setPage(PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_TWO);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_THREE_NEXT:
		if (e == MOUSE_STATUS_UP)
		setPage(PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_FOUR);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_FOUR_PRE:
		if (e == MOUSE_STATUS_UP)
		setPage(PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_THREE);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_FOUR_NEXT:
		if (e == MOUSE_STATUS_UP)
		setPage(PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_FIVE);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_FIVE_PRE:
		if (e == MOUSE_STATUS_UP)
		setPage(PAGE_SYSTEM_SET_STEER_WHEEL_STUDY_FOUR);
		break;
	case CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_FIVE_NEXT:
		break;
	default:
		bRet = false;
		break;
	}

	if (id >= CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_BEGIN && id <= CTRL_ID_SYSTEM_SET_STEER_WHEEL_STUDY_BEGIN + 255)
	{
		clickKey(e, id);
		bRet = true;
	}
		
	return bRet;
}

bool CSteeringWheelStudy::processHalMsg(u8 cmd, u8 *p, u8 len)
{
	bool bRet = true;
	
	switch(cmd)
	{
	case 0x1A://是否使用自定义方向盘数据
		getFromHalApplySelfDefineSteerWheelDesign(p[0]);
		break;
	case 0x1B://返回方向盘学习状态
		getFromHalStudyKeyState(p[0]);
		break;
	case 0x1C://返回方向盘按键状态
		getFromHalKeyState(p, len);
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

void CSteeringWheelStudy::clickWheelKeyStudy(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			updateWheelKeyStudyState();
			setPage(PAGE_SYSTEM_WHEEL_LEARNING);
		}
		break;
	default:
		break;
	}
}

void CSteeringWheelStudy::clickKey(E_MOUSE_STATUS e, u32 id)
{
	switch(e)
	{
	case MOUSE_STATUS_DOWN:
		{
			m_szbCtrlIdHaveDown[id - FUNC_CTRL_ID_KEY_BEGIN] = true;
	
			setAnalogData(id, 1);
		}
		break;
	case MOUSE_STATUS_UP:
		{
			/*if (m_szbCtrlIdHavdDoneMouseTimer[id - FUNC_CTRL_ID_KEY_BEGIN])
			{
				m_szbCtrlIdHavdDoneMouseTimer[id - FUNC_CTRL_ID_KEY_BEGIN] = false;
				return;
			}*/

			if (m_bBeginStudyKey)
				setToHalCancleStudyKey();
			else
				setToHalStudyKey(id - FUNC_CTRL_ID_KEY_BEGIN);
			
		}
		break;
	case MOUSE_STATUS_TIMER:
		{
			m_szbCtrlIdHavdDoneMouseTimer[id - FUNC_CTRL_ID_KEY_BEGIN] = true;

			setToHalDeleteStudyKey(id - FUNC_CTRL_ID_KEY_BEGIN);
		}
		break;
	default:
		break;
	}
}

void CSteeringWheelStudy::clickApply(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			if(0x01 == pLocalParam->u8_Sys_UserSteeringWheel)
			{
				setPage(PAGE_SETUP_BEGIN + 4);
			}
			else
			{
				setToHalApplyStudyKey(1);
				setPage(PAGE_SETUP_BEGIN + 4);
			}
		}
		break;
	default:
		break;
	}
}

void CSteeringWheelStudy::clickDelete(E_MOUSE_STATUS e)
{
	switch(e)
	{
	case MOUSE_STATUS_UP:
		{
			setToHalDeleteStudyKey(0);
		}
		break;
	default:
		break;
	}
}

void CSteeringWheelStudy::updateWheelKeyStudyState(void)
{
	int i = 0;
	
	for (i = 0; i < KEY_MAX_NUM; i++)
	{
		int j = FUNC_CTRL_ID_KEY_BEGIN + i;
		int z = i / 8;
		int zi = i % 8;
		int d = m_szKeyState[z];
		int s = ((1 << zi) & d) >> zi;

		if (s == 1)
		{
			m_szbCtrlIdHaveDown[i] = true;
			setAnalogData(j,  2);
		}
		
		bool bRetHave = m_szbCtrlIdHaveDown[i];

		if (bRetHave && (s == 0))
			setAnalogData(j,  0);
	}
}

const char* CSteeringWheelStudy::getMouseMessageType(u8 p)
{
	const char *pRet = "INIT_VALUE";

	switch(p)
	{
	case MOUSE_STATUS_DOWN:
		pRet = "DOWN";
		break;
	case MOUSE_STATUS_UP:
		pRet = "UP";
		break;
	case MOUSE_STATUS_TIMER:
		pRet = "TIMER";
		break;
	case MOUSE_STATUS_UNKNOW:
		pRet = "UNKNOW";
		break;
	}

	return pRet;
}

void CSteeringWheelStudy::setPage(int nPageId)
{
	systemToModule_NotifySystem_JumpPage(nPageId);
}

//hal
void CSteeringWheelStudy::setToHalApplyStudyKey(u8 p)
{
	u8 szMsg[] = {0x1A, p};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, szMsg, sizeof(szMsg));
}

void CSteeringWheelStudy::setToHalStudyKey(u8 key)
{
	u8 szMsg[] = {0x1B, key};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, szMsg, sizeof(szMsg));
}

void CSteeringWheelStudy::setToHalCancleStudyKey(void)
{
	u8 szMsg[] = {0x1C, 0};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, szMsg, sizeof(szMsg));
}

void CSteeringWheelStudy::setToHalDeleteStudyKey(u8 p)
{
	u8 szMsg[] = {0x1D, p};

	makeAndSendMessageToHal(HAL_ID_SYSTEM, szMsg, sizeof(szMsg));
}

void CSteeringWheelStudy::getFromHalApplySelfDefineSteerWheelDesign(u8 p)
{
	pLocalParam->u8_Sys_UserSteeringWheel = p;
	LOGD("[%s] p = [0x%x]", __FUNCTION__, p);

	if(0x01 == pLocalParam->u8_Sys_UserSteeringWheel)
	{
		setControllable(CONTROLID_SETUP_WHEEL_CHOOSE_DOWM,0);
		setControllable(CONTROLID_SETUP_WHEEL_CHOOSE_UP,0);
		setAnalogData(CONTROLID_SETUP_WHEEL_CHOOSE_DOWM, (short)2);
		setAnalogData(CONTROLID_SETUP_WHEEL_CHOOSE_UP, (short)2);
		setDigitalData(CONTROLID_SETUP_WHEEL_LEARNING_ON_OFF, true);

	}
	else if(0x00 == pLocalParam->u8_Sys_UserSteeringWheel)
	{
		setControllable(CONTROLID_SETUP_WHEEL_CHOOSE_DOWM,1);
		setControllable(CONTROLID_SETUP_WHEEL_CHOOSE_UP,1);
		setAnalogData(CONTROLID_SETUP_WHEEL_CHOOSE_DOWM, (short)0);
		setAnalogData(CONTROLID_SETUP_WHEEL_CHOOSE_UP, (short)0);
		setDigitalData(CONTROLID_SETUP_WHEEL_LEARNING_ON_OFF, false);
	}
}

void CSteeringWheelStudy::getFromHalStudyKeyState(u8 p)
{
	LOGD("[%s] p = [%d]", __FUNCTION__, p);

	switch(p)
	{
	case 0x00:
	case 0x02:
		m_bBeginStudyKey = false;
		updateWheelKeyStudyState();
		break;
	case 0x01:
		m_bBeginStudyKey = true;
		break;
	default:
		break;
	}
}

void outPutLogg(const char *pFunName, const char *pArgName, u8 *pArg, int len)
{
	const int nMsgSize = 512 * 3;

	if (3 * len >= nMsgSize)
	{
		LOGD("[%s] %s Error: arg len is bigger than szMsg.", pFunName, pArgName);
		return;
	}

	char szMsg[nMsgSize] = {0};
	int i = 0;
	int j = 0;
	for (i = 0; i < len; i++)
	{
		u8 *p = pArg + i;
		if (p)
		{
			snprintf(szMsg + j, nMsgSize - j, "%02X ", *p);
			j += 3;
		}
		else
			break;
	}

	LOGD("[%s] %s %s", pFunName, pArgName, szMsg);
}


void CSteeringWheelStudy::getFromHalKeyState(u8 *p, int len)
{
	LOGD("[%s] p = [%d]", __FUNCTION__, p[0]);
	outPutLogg(__FUNCTION__, "p", p, len);

	memcpy(m_szKeyState, p, len);
}

