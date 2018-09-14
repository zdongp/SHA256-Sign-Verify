#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "otherModuleResponseFunction.h"
#include "halResponseFunction.h"


int moduleToKey_AnalyseModuleCommand_System(unsigned char * buf,int len){
	//fromtype frommode totype tomode cmd param 
	int cmd = buf[0];
	int param = buf[1];
	switch(cmd)
	{
	case 0x10:
		if(0 == param)//系统复位
			saveParameter();
		break;
	case 0x14:
		if(0 == param)//恢复出厂设置
			recoverDefaultParam();
		break;
	case 0x2d:
		ModuleToKey_AccOn();
		break;
	case 0x2c:
		ModuleToKey_AccOff();
		break;
	default:
		break;
	}
	return true;

}

int moduleToKey_AnalyseModuleCommand_Sound(unsigned char * buf,int len){
	unsigned char cSoundModeCmd = buf[0];
	unsigned char cSoundMode = buf[1];
	switch(cSoundModeCmd)
	{
	case 0x00: //Get Sound Mode
		moduleToKey_GetChannel(cSoundMode);
		break;
	default:
		break;
	}
	return true;

}

int moduleToKey_AnalyseModuleCommand_Sync(unsigned char * buf,int len){
	switch(buf[0]){
		case 0x00:
			 pLocalParam->u_bSync_BTCall = (buf[1] ? true : false);
			break;
		default:break;
	}

	return true;
}

int moduleToKey_AnalyseModuleCommand_Key(unsigned char * buf,int len)
{
	switch(buf[0])
	{
		case 0x80://DA ZHONG
		    {
                    	   u8 key = 0x00;
                        switch(buf[1])
                            {
                                case 0x02:
					key = 0x38;			
                                    break;
				    case 0x03:
				   	key = 0x39;
					break;
				   case 0x06:
					key = 0x35;
					break;
				   case 0x07:
					key = 0x36;
					break;
				    case 0x1a:
					key = 0x31;
					break;
				
				    case 0x2b:
					key = 0x37;
					break;
					
                            }
				LOGD("key: moduleToKey_AnalyseModuleCommand_Key : key = 0x%02X, ", key);
				halToKey_analyseKeyValue(key);
		    }
                  break;
	}

	return 0;
}

void moduleToKey_AnalyseModuleCommand_ExternalCtrl(unsigned char * buf,int len)
{
	LOGD("+++key+++ExternalCtrl++++buf[0]:%x buf[1]:%x",buf[0],buf[1]);
	if(buf[0] != 0x00)
		return;

	u8 key = 0x00;
	switch(buf[1])
	{
		case 0x00:
		{
			static bool bKeyVal_Status=true;
			LOGD("bKeyVal_Status:%d",bKeyVal_Status);
			switch(buf[2])
			{
				case 0x00:
					if(bKeyVal_Status)
					{
						bKeyVal_Status=false;
						key = HALTOKEY_KEYVAL_MUTE;
					}
					break;
				case 0x01:
					if(!bKeyVal_Status)
					{
						bKeyVal_Status=true;
						key = HALTOKEY_KEYVAL_MUTE;
					}
					break;
				case 0x02:
				{
					bKeyVal_Status=true;
					key = HALTOKEY_KEYVAL_VOL_INC;
				}
				break;
				case 0x03:
				{
					bKeyVal_Status=true;
					key = HALTOKEY_KEYVAL_VOL_DEC;
				}
				break;				
				default:break;
			}
		}
        break;
        case 0x01:
        {
        	if(buf[2] == 0x00)
        	{
        		key = HALTOKEY_KEYVAL_SEEK_INC;
        	}
        	else if(buf[2] == 0x01)
        	{
        		key = HALTOKEY_KEYVAL_SEEK_DEC;
        	}
        }
        break;
        case 0x02:
        {
            if(buf[2] == 0x00)
        	{
        		key = HALTOKEY_KEYVAL_NAVI;
        	}
        	else if(buf[2] == 0x01)
        	{
        		key = HALTOKEY_KEYVAL_DEST;
        	}
        }
        break;
        case 0x03:
        {
            if(buf[2] == 0x00)
        	{
        		key = HALTOKEY_KEYVAL_TUNE_INC;
        	}
        	else if(buf[2] == 0x01)
        	{
        		key = HALTOKEY_KEYVAL_TUNE_DEC;
        	}
        	else if(buf[2] == 0x02)
        	{
        		key = HALTOKEY_KEYVAL_TUNE_DOWN;
        	}
        }
        break;
        case 0x04:
        break;
        case 0x05:
        {
            if(buf[2] == 0x00 || buf[2] == 0x01)
        		key = HALTOKEY_KEYVAL_OPEN;
        }
        break;
        default:break;
	}

	LOGD("key: moduleToKey_AnalyseModuleCommand_ExternalCtrl : key = %x", key);
	halToKey_analyseKeyValue(key);
}

void moduleToKey_GetChannel(unsigned char cSoundMode){
    pLocalParam->m_iSoundChannel = cSoundMode;
	//LOGD("-------------notify sound:%x",cSoundMode);
}

void ModuleToKey_AccOff(){
	LOGV("ModuleToKey_AccOff()");
}

void ModuleToKey_AccOn(){
	LOGV("ModuleToKey_AccOn()");
}
void analyseSdkToKeyDedicate_information(u8 *param,int len)
{
	LOGD("***key***%x %x******",param[0],param[1]);
	switch(param[0])
	{
		case 0x01:
		{
			if(param[1]==0x00)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_MUTE);
			else if(param[1]==0x01)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_VOL_INC);
			else if(param[1]==0x02)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_VOL_DEC);
		}
		break;
		case 0x02:
		{
			if(param[1]==0x00)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_SEEK_INC);
			else if(param[1]==0x01)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_SEEK_DEC);
		}
		break;
		case 0x03:
		{
			if(param[1]==0x00)
			halToKey_analyseKeyValue(HALTOKEY_KEYVAL_NAVI);
		}
		break;
		case 0x04:
		{
			if(param[1]==0x00)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_TUNE_INC);
			else if(param[1]==0x01)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_TUNE_DEC);
			else if(param[1]==0x02)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_TUNE_DOWN);	
		}
		break;
		case 0x05:
			break;
		case 0x06:
		{
			if(param[1]==0x01)
			halToKey_analyseKeyValue(HALTOKEY_KEYVAL_AV);
		}
		break;
		default:break;
	}
}

