
#include "FlyJniSdkModule.h"

#include "FlyJniSdkModuleRadio.h"
#include "FlyJniSdkModuleBt.h"
#include "FlyJniSdkModuleAudioVideo.h"
#include "FlyJniSdkModuleDvd.h"
#include "FlyJniSdkModuleSystem.h"
#include "FlyJniSdkModuleExtcar.h"
#include "FlyJniSdkModuleAc.h"
#include "FlyJniSdkModuleMedia.h"
#include "FlyJniSdkModuleAudioCtrl.h"
#include "FlyJniSdkModuleExternalCtrl.h"

CFlyModule *g_pFlyModule = (CFlyModule*)CFlyJniSdkModule::GetInstance();

CFlyJniSdkModule::CFlyJniSdkModule(void)
{
    m_pFlyJniSdkApp    = CFlyJniSdkApp::GetInstance();
    m_pFlyJniSdkModule = this;
    m_pFlyJniSdkHal    = CFlyJniSdkHal::GetInstance();
    m_pFlyJniSdkParam  = CFlyJniSdkParam::GetInstance();

    m_pFlyApp    = m_pFlyJniSdkApp;
    m_pFlyModule = m_pFlyJniSdkModule;
    m_pFlyHal    = m_pFlyJniSdkHal;
    m_pFlyParam  = m_pFlyJniSdkParam;

    m_pFlyJniSdkApp->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
    m_pFlyJniSdkHal->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);
    m_pFlyJniSdkParam->initObject(m_pFlyApp, m_pFlyHal, m_pFlyModule, m_pFlyParam);


}

CFlyJniSdkModule::~CFlyJniSdkModule(void)
{
}

moduleid_t CFlyJniSdkModule::locale_module_mid(void)
{
    return MODULE_ID_FLYJNISDK;
}

void CFlyJniSdkModule::init(void)
{
    // 冷启动起来调用
    LOGD("[%s] [%s]", __FILE__, __FUNCTION__);

    m_pFlyJniSdkModule->initNativeTimer();

}

void CFlyJniSdkModule::getAccOff()
{
    LOGD("[%s]", __FUNCTION__);

    u8 szMsg[2] = {0x2C, 0x00};
    m_pFlyJniSdkParam->m_pFlyJniModuleExtcar->initCarInforParam();
    setToFlyJniSdkService(MODULE_ID_FLYJNISDK, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModule::getReset(void)
{
    LOGD("[%s]", __FUNCTION__);

    u8 szMsg[2] = {0x2C, 0x01};
    setToFlyJniSdkService(MODULE_ID_FLYJNISDK, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModule::getResetFactorySetting(void)
{
    LOGD("[%s]", __FUNCTION__);

    u8 szMsg[2] = {0x2C, 0x02};
    setToFlyJniSdkService(MODULE_ID_FLYJNISDK, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModule::getSystemCodeStartInitModule(void)
{
    LOGD("[%s] CFlyJniSdkModule", __FUNCTION__);
    m_pFlyJniSdkParam->m_pFlyJniModuleExtcar->initCarInforParam();
}

void CFlyJniSdkModule::getAccOn()
{
    LOGD("[%s]", __FUNCTION__);

    u8 szMsg[2] = {0x2D, 0x00};
    setToFlyJniSdkService(MODULE_ID_FLYJNISDK, szMsg, sizeof(szMsg));
}
void CFlyJniSdkModule::timerHandleProc(int timerId)
{

}

int CFlyJniSdkModule::nativeTimerHandlerProcess(timer_t timerId)
{
    long int ID = 0;
    ID = (long int)timerId;
    switch(ID)
    {
        case JNISDK_TIMER_ID_RADIO_JUMP_PAGE:
        {
            m_pFlyJniSdkParam->m_pFlyJniModuleRadio->sendToRadioSetONorOFF(0x01);
            m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestMuteOrUnMute(0x00);
        }
            break;
        case JNISDK_TIMER_ID_A2DP_JUMP_PAGE:
        {
            m_pFlyJniSdkParam->m_pFlyJniSdkModuleBt->setToBtSetBtJumpToBtMusicPage(0x01);
            m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestMuteOrUnMute(0x00);
        }
            break;
        case JNISDK_TIMER_ID_MIDEA_JUMP_PAGE:
        {
            m_pFlyJniSdkParam->m_pFlyJniSdkModuleMedia->setToMediaJumpMediaPage(0x01);
            m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->sendToAudioRequestMuteOrUnMute(0x00);
        }
            break;
        default:break;
    }

    return 0;
}

void CFlyJniSdkModule::getMyModuleParam(char id, u8 *p, u8 *pLen)
{
    switch((u8)id)
    {
        //case FLY_FlyJniSdk_PARAM_SIGNAL:
        //	{
        //		*p = isHaveAvinSignal() ? 1 : 0;
        //		*pLen = 1;

        //		LOGD("[%s] [%s] *p = [%d]", __FUNCTION__, "FLY_FlyJniSdk_PARAM_SIGNAL", *p);
        //	}
        //	break;
        default:
            break;
    }
}

void CFlyJniSdkModule::getSystemMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);
    m_pFlyJniSdkParam->m_pFlyJniModuleSystem->getSystemMessage(p,  len);
}

void CFlyJniSdkModule::getAudioVideoMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);
    m_pFlyJniSdkParam->m_pFlyJniModuleAudioVideo->getAudioVideoMessage(p, len);
}

void CFlyJniSdkModule::getKeyMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);

    switch(p[0])
    {
        case 0xE2://enter FlyJniSdk system
        {
        }
            break;
    }
}

void CFlyJniSdkModule:: getDvdMessage(u8 *p,u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);

    m_pFlyJniSdkParam->m_pFlyJniModuleDvd->getDvdMessage(p, len);

}



void CFlyJniSdkModule::getRadioMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);

    m_pFlyJniSdkParam->m_pFlyJniModuleRadio->getRadioMessage(p, len);

}

void CFlyJniSdkModule::getBtMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);

    m_pFlyJniSdkParam->m_pFlyJniSdkModuleBt->getBtMessage(p, len);

}

void CFlyJniSdkModule::getExtcarMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);

    m_pFlyJniSdkParam->m_pFlyJniModuleExtcar->getExtcarMessage(p, len);

}
void CFlyJniSdkModule::setToFlyJniSdkService(u8 moduleId, u8 *p, u8 len)
{
    static u8 szMsg[256] = {0};
    szMsg[0] = moduleId;

    if(len > 256)
        len = 256;

    memcpy(szMsg + 1, p, len);
    m_pFlyJniSdkApp->setCommand(0x51FFFF, szMsg, len + 1);


}
void CFlyJniSdkModule::sendToFlyJniSdkService(u8 moduleId, u8 *p, u8 len)
{
    static u8 szMsg[256] = {0};
    szMsg[0] = moduleId;

    if(len > 256)
        len = 256;

    memcpy(szMsg + 1, p, len);
    m_pFlyJniSdkApp->setCommand(0x51FFFE, szMsg, len + 1);


}
void CFlyJniSdkModule::getAcMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);

    m_pFlyJniSdkParam->m_pFlyJniSdkModuleAc->getAcMessage(p, len);

}
void CFlyJniSdkModule::getMediaMessage(u8 *p, u8 len)
{
    outPutLog(__FUNCTION__, "p", p, len);

    m_pFlyJniSdkParam->m_pFlyJniSdkModuleMedia->getMediaMessage(p, len);

}

void CFlyJniSdkModule::SdkToOtherModule_AudioCtrl_FromSourceSource(u8 cmd,u8 param)
{
    u16 cLastSoundChannel = m_pFlyJniSdkModule->getLastAudioVideoMediaChannel();
    u8 ToModeID = 0;
    switch(cLastSoundChannel)
    {
        case CHANNEL_DVD_CTRL://DVD ctrl
        case CHANNEL_DVD_VIDEO://DVD video
            ToModeID = MODULE_ID_DVD;
            break;
        case CHANNEL_RADIO: //RADIO
            ToModeID = MODULE_ID_RADIO;
            break;
        case CHANNEL_AUX_CTRL://AUX ctrl
        case CHANNEL_AUX_VIDEO://aux video
            ToModeID = MODULE_ID_AUX;
            break;
        case CHANNEL_IPOD_CTRL: //IPOD ctrl
        case CHANNEL_IPOD_VIDEO://ipod video
            ToModeID = MODULE_ID_IPOD;
            break;
        case CHANNEL_TV_CTRL://TV ctrl
        case CHANNEL_TV_VIDEO://tv video
            ToModeID = MODULE_ID_TV;
            break;
        case CHANNEL_MP3: //MEDIA
            ToModeID = MODULE_ID_MEDIA;
            break;
        case CHANNEL_BT:
            ToModeID = MODULE_ID_BT;
            break;
        case CHANNEL_DVR_CTRL:
        case CHANNEL_DVR_VIDEO:
            ToModeID = MODULE_ID_DVR;
            break;
        default:break;
    }

    if(ToModeID != 0)
    {
        SdkToOtherModule_aboutAudioCtrlCmd(ToModeID,cmd,param);
    }
}

void CFlyJniSdkModule::SdkToOtherModule_aboutAudioCtrlCmd(u8 ToMode,u8 cmd,u8 param)
{
    u8 buf[3] = {0xFF,cmd,param};
    makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,ToMode,buf,3);
}
