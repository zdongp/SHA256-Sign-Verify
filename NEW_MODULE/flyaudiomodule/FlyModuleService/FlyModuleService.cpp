#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include <pthread.h>
#include <errno.h>
#include <limits.h>

#include "types_def.h"
#include "moduleCommApi.h"
#include "commonFunc.h"
#include "flymoduleApi.h"
#include "hardware.h"
#include "tinyxml.h"
#include "tinystr.h"

#include "moduleID.h"
#include "hal.h"
#include "FlyProperties.h"

#define MODULE_LIBRARY_PATH "/flysystem/lib/fa"
#define MODULELISTFILENAME	"/flysystem/inifile/modulelist.xml"



#define LOG_TAG "MAIN_MODULE"

#define LOCAL_MODULE_NAME		"moduleService"
#define LOCAL_MODULE_ID			MODULE_ID_MAIN_SERVICE

device_command_t command_list[HAL_MODULE_MAX_NUM];

struct t_moduleList{
	int count;
	int index[HAL_MODULE_MAX_NUM];
} ;

struct t_moduleList moduleList;



static int default_get(unsigned char *buf,  int len)
{
	debugPrintf("default get\n");
	return 0;
}

static int default_set(unsigned char *buf,  int len)
{
	debugPrintf("default set\n");
	return 0;
}


static void commandSetToAll(unsigned char *buf,  int len)
{
	int i = 0;
	for (i = 0; i < moduleList.count; i++)
	{
		command_set(moduleList.index[i], buf, len);
	}
}


static int GotoModuleID_getHalID(u8 halId)

{
	int uModuleId = -1;
	switch(halId)
	{
		case HAL_ID_GLOBAL: 			//0x00
		case HAL_ID_SYSTEM: 			//0x01
			uModuleId = MODULE_ID_SYSTEM;
			break;
		case HAL_ID_AUDIO: 			//0x02
		case HAL_ID_VIDEO: 			//0x03
		   	uModuleId = MODULE_ID_AUDIOVIDEO;
			break;
		case HAL_ID_KEY: 			//0x04
			uModuleId = MODULE_ID_KEY;
			break;
		case HAL_ID_EXDISPLAY: 			//0x05
		   	uModuleId = MODULE_ID_AUXSCREEN;
			break;
		case HAL_ID_OSD_BUTTEN: 			//0x06
		case HAL_ID_OSD_SETVIDEO: 			//0x07
			uModuleId = MODULE_ID_OSD;
			break;
		case HAL_ID_RADIO: 			//0x10
		   	uModuleId = MODULE_ID_RADIO;
			break;
		case HAL_ID_BACK: 			//0x11
			uModuleId = MODULE_ID_BACK;
			break;
		case HAL_ID_DVD: 			//0x20
		   uModuleId = MODULE_ID_DVD;
			break;
		case HAL_ID_BT: 			//0x30
			uModuleId = MODULE_ID_BT;
			break;
		case HAL_ID_XMRADIO: 			//0x40
			break;
		case HAL_ID_TPMS: 			//0x50
			uModuleId = MODULE_ID_TPMS;
			break;
		case HAL_ID_TV: 			//0x60
			uModuleId = MODULE_ID_TV;
			break;
		case HAL_ID_AC: 			//0x70
			uModuleId = MODULE_ID_AC;
			break;
		case HAL_ID_EXTCAR: 			//0x80
		   	uModuleId = MODULE_ID_EXTCAR;
			break;
		case HAL_ID_EXTCAR_HONDA_RSU://0x81
			uModuleId = MODULE_ID_EXTCAR_HONDA_TSU;
			break;
		case HAL_ID_IPOD: 			//0x90
			uModuleId = MODULE_ID_IPOD;
			break;
		case HAL_ID_BLCD: 			//	0x91
			uModuleId = MODULE_ID_BLCD;
			break;
		case HAL_ID_SERVICE: 			//0xFF
			uModuleId = MODULE_ID_SERVICE;
			break;
		case HAL_ID_DVR: 			//0x92
		   	uModuleId = MODULE_ID_DVR;
			break;
		case HAL_ID_NV: 			//0x93
			uModuleId = MODULE_ID_DNV;
			break;
		case HAL_ID_MODULE_ROUTE: 			//0x51
			break;
		case HAL_ID_AUTOMATE:
			uModuleId = MODULE_ID_AUTOMATE;
			break;
		}
	return uModuleId;
}


///////////////////////////////////////////////add cbh//////////////////////////////////////////////////////////

#define PATH_FLYSYSTEM_FLYCONFIG_CARFLIE  "/flysystem/flyconfig"
#define PATH_FLYSYSTEM_OTA_UPDATA_MCU_TIME  "/flysystem/flytheme/mcu/mcu-version.txt"

static void readMcufile_content_and_set_property(const char *id_mcu)
{
	debugPrintf("readAnd_WriteToTheFile_load id_mcu:%s",id_mcu);

	if(access(id_mcu, F_OK) == -1)
	{
        debugPrintf("MCU file not exists");
		return;
	}

	if(access(id_mcu, R_OK) == -1)
	{
        debugPrintf("You can't read the MCU file!");
		return;
	}

	FILE *stream_mcu;
	stream_mcu = fopen(id_mcu,"r");
	if(stream_mcu==NULL){
        debugPrintf("stream_mcu error");
		return;
	}

	char buff[80]={0};
	int n1,offset1,onset1;

	offset1 = fseek(stream_mcu,0,SEEK_END);
    debugPrintf("offset1:%d",offset1);
	n1 = ftell(stream_mcu);
    debugPrintf("n1 %d********",n1);

	onset1=fseek(stream_mcu,0,SEEK_SET);
    debugPrintf("onset1:%d",onset1);

	int numread = fread(buff,sizeof(char),n1,stream_mcu);
    debugPrintf("fread ferror(stream_mcu):%d   numread:%d   ",ferror(stream_mcu),numread);

	char buff_mcu[PROPERTY_VALUE_MAX]={0};
	snprintf(buff_mcu, PROPERTY_VALUE_MAX, "%s",buff);
	if(NULL!=buff_mcu[0])
	property_set("fly.version.mcu", buff_mcu);
    debugPrintf("buff_mcu:%s\n",buff_mcu);

	fclose(stream_mcu);
	stream_mcu=NULL;

}

static void readMcufile_version_and_set_property(const char *id_mcu)
{
    debugPrintf("readAnd_WriteToTheFile_load id_mcu:%s",id_mcu);

	if(access(id_mcu, F_OK) == -1)
	{
        debugPrintf("MCU file not exists");
		return;
	}

	if(access(id_mcu, R_OK) == -1)
	{
        debugPrintf("You can't read the MCU file!");
		return;
	}

	FILE *stream_mcu;
	stream_mcu = fopen(id_mcu,"r");
	if(stream_mcu==NULL){
        debugPrintf("stream_mcu error");
		return;
	}

	char buff[80]={0};
	int n1,offset1,onset1;

	offset1 = fseek(stream_mcu,0,SEEK_END);
    debugPrintf("offset1:%d",offset1);
	n1 = ftell(stream_mcu);
    debugPrintf("n1 %d********",n1);

	onset1=fseek(stream_mcu,0,SEEK_SET);
    debugPrintf("onset1:%d",onset1);

	int numread = fread(buff,sizeof(char),n1,stream_mcu);
    debugPrintf("fread ferror(stream_mcu):%d   numread:%d   ",ferror(stream_mcu),numread);

	char buff_mcu[PROPERTY_VALUE_MAX]={0};
	snprintf(buff_mcu, PROPERTY_VALUE_MAX, "%s",buff);
	if(NULL!=buff_mcu[0])
	property_set("fly.version.times", buff_mcu);
    debugPrintf("buff_mcu:%s\n",buff_mcu);

	fclose(stream_mcu);
	stream_mcu=NULL;

}


#include <tinyxml.h>
#define CONFIGSTRING "flymodelconfig"
#define CONFIGITEM "item"
typedef void (*parse_callback)(TiXmlAttribute* pAttrib);

//////////////////////////////////////////////////////////////////////
#define PROPERTY_DEFAULT_VALUE	"UNKNOW"
enum E_EXTERNAL_DEVICE
{
	EXTERNAL_DEVICE_DVR,
	EXTERNAL_DEVICE_TV_TPMS,
	EXTERNAL_DEVICE_DNV,
	EXTERNAL_DEVICE_AMBIENT_LED,
	EXTERNAL_DEVICE_UNKNOW = 0xff
};

bool isNeedToSetProperty(char * name)
{
	bool bRet = true;
	char property[PROPERTY_VALUE_MAX] = {0};

	if (strcmp(name,  "fly.set.b_Sys_DVROrTV") == 0)
	{
		property_get("fly.set.b_Sys_DVROrTV", property, "9");

        debugPrintf("[%s] dd %s", __FUNCTION__,  property);


			int t = 0;
			sscanf(property,"%d", &t);
			if (t == EXTERNAL_DEVICE_UNKNOW || t == 9)
				bRet = true;
			else
				bRet = false;

	}

	return bRet;
}
////////////////////////////////////////////////////////////////////////////

static void parse_module(TiXmlAttribute* pAttrib)
{
		char property_name[256];
		char property[256];

		while(pAttrib)
		{
			sprintf(property_name,"%s", pAttrib->Name());
			sprintf(property,"%s", pAttrib->Value());

            debugPrintf("[%s] %s:%s \n", __FUNCTION__, property_name,property);

			if (isNeedToSetProperty(property_name))
				property_set(property_name,property);

			pAttrib=pAttrib->Next();
		}

}

static int ParseFile_theModelconfigXML(const char *filename,parse_callback parse_func)
{
    debugPrintf("ParseFile_theModelconfigXML filename:%s",filename);

    TiXmlDocument doc(filename);
    bool loadOkay = doc.LoadFile();

    if(loadOkay)
    {
    	TiXmlHandle docHandle(&doc);
    	TiXmlNode* item = docHandle.FirstChild(CONFIGSTRING).FirstChild().Node();

		for (; item != 0; item = item->NextSibling())
		{
			//LOGI("Element [%s] ,type:%d ?= %d",item->Value(),item->Type(),TiXmlNode::ELEMENT);
		    if(item->Type() == TiXmlNode::ELEMENT && !strcmp(item->Value(),CONFIGITEM))
		    {
		    	(*parse_func)(item->ToElement()->FirstAttribute());
		    }
		}

    }
    else
    {
        debugPrintf("Failed to load file");
    	return -1;
    }
	return 0;
}


static void switch_moduleconfig_from_Thetype_file()
{
	char carName_select[50];
	char property[PROPERTY_VALUE_MAX];
	char path_select[PATH_MAX];
	char path_select1[PATH_MAX];
	char path_mcufile[PATH_MAX];

	property_get("persist.fly.car.select",property,"0");
	sscanf(property,"%s", carName_select);
    debugPrintf("carName_select:%s",carName_select);

	snprintf(path_select, sizeof(path_select), "%s/%s", PATH_FLYSYSTEM_FLYCONFIG_CARFLIE, carName_select);

	if(access(path_select, F_OK) == 0){
        debugPrintf("The file exists");
		snprintf(path_select1, sizeof(path_select1), "%s/%s/modelconfig/flymodelconfig.xml", PATH_FLYSYSTEM_FLYCONFIG_CARFLIE,carName_select);
		snprintf(path_mcufile, sizeof(path_mcufile), "%s/%s/mcu.txt", PATH_FLYSYSTEM_FLYCONFIG_CARFLIE,carName_select);
		goto LABEL_LOAD_MODULECONFIG;
	}
	else{
        debugPrintf("This file does not exist");
		snprintf(path_select1, sizeof(path_select1), "%s/%s/modelconfig/flymodelconfig.xml", PATH_FLYSYSTEM_FLYCONFIG_CARFLIE,"default");
		snprintf(path_mcufile, sizeof(path_mcufile), "%s/%s/mcu.txt", PATH_FLYSYSTEM_FLYCONFIG_CARFLIE,"default");
		goto LABEL_LOAD_MODULECONFIG;
	}

	LABEL_LOAD_MODULECONFIG:
		readMcufile_content_and_set_property(path_mcufile);
		readMcufile_version_and_set_property(PATH_FLYSYSTEM_OTA_UPDATA_MCU_TIME);
		ParseFile_theModelconfigXML(path_select1,&parse_module);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static int load(const char *name, int id,
        const char *path,
        struct hw_module_t **pHmi)
{
    int status;
    void *handle;
    struct hw_module_t *hmi;

    /*
     * load the symbols resolving undefined symbols before
     * dlopen returns. Since RTLD_GLOBAL is not or'd in with
     * RTLD_NOW the external symbols will not be global
     */

    handle = dlopen(path, RTLD_NOW);
    if (handle == NULL) {
        char const *err_str = dlerror();
        printf("load: module=%s\n%s\n", path, err_str?err_str:"unknown");
        status = -EINVAL;
        goto done;
    }

    /* Get the address of the struct hal_module_info. */
    hmi = (struct hw_module_t *)dlsym(handle, HAL_MODULE_INFO_SYM_AS_STR);
    if (hmi == NULL) {
        printf("load: couldn't find symbol %s\n", HAL_MODULE_INFO_SYM_AS_STR);
        status = -EINVAL;
        goto done;
    }

	debugPrintf("load: id=%d != fai->id=%d || name=%s != fai->name=%s\n"
			, id, hmi->id, name, hmi->name);

    if (strcmp(name, hmi->name) != 0 || id != hmi->id) {
		status = -EINVAL;
		goto done;
    }


    hmi->dso = handle;

    /* success */
    status = 0;

    done:
    if (status != 0) {
        hmi = NULL;
        if (handle != NULL) {
            dlclose(handle);
            handle = NULL;
        }
    } else {
        printf("loaded HAL id=%d path=%s hmi=%p handle=%p\n",
                id, path, *pHmi, handle);
    }

    *pHmi = hmi;

    return status;
}

int hw_get_module(const char *name, int id, struct hw_module_t **module)
{
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s.flyaudio.so", MODULE_LIBRARY_PATH, name);
	debugPrintf("get path %s\n", path);
    if (access(path, R_OK) == 0) goto found;

    return -ENOENT;

found:
    /* load the module, if this fails, we're doomed, and we should not try
     * to load a different variant. */
    return load(name, id, path, module);
}


BOOL analyseModulelistXml(const char *xmlPath,struct hw_module_t *phw[], struct hw_device_t *phwDev)
{
	char Name[256] = {0};
	UINT ID = 0;
	
	TiXmlElement* rootElement1;
	TiXmlElement* rootElement2;
	TiXmlDocument doc;
	if(!doc.LoadFile(xmlPath))
	{
		printf("load %s fail ==> %s\n", xmlPath, strerror(errno));
		return FALSE;
	}
	rootElement1 = doc.RootElement();
	rootElement2=rootElement1->FirstChildElement("Module");

	while(rootElement2 != NULL)
	{
		ID=atoi(rootElement2->Attribute("ID"));

        if(ID<HAL_MODULE_MAX_NUM)
        {

            strcpy(Name, rootElement2->Attribute("NAME"));

            if (hw_get_module(Name, ID, &phw[ID]) < 0)
            {
                debugPrintf("hw_get_module %s %d fail ==> %s\n", Name, ID, strerror(errno));
                return FALSE;
            }
			else
			{
				debugPrintf("hw_get_module %s %d success\n", Name, ID);
			}

            if (NULL != phw[ID])
            {
            	phwDev[ID].command_list = (device_command_t *)command_list;
                phw[ID]->methods->open(phw[ID], Name, &phwDev[ID]);

            }
			moduleList.index[moduleList.count++] = ID;
            rootElement2=rootElement2->NextSiblingElement();
        }
     }
	return TRUE;
}




static void getStandbyInfomation(char status)
{
	BYTE param[2] = {0x1D, 0x00};
	switch(status)
	{
		case 0:
			param[1] = 0x00;
            commandSetToAll(param, 2);
			break;
		case 1:
			param[1] = 0x01;
            commandSetToAll(param, 2);
			break;
		default:
			break;
	}
}

static void getSuspendInfomation(char status)
{
    BYTE param[3] = {MESSAGETYPE_IOCTL, 0x2C, 0x00};
	switch(status)
	{
		case 0:
			param[2] = 0x00;
            commandSetToAll(param, 3);
			break;
		case 1:
			param[2] = 0x01;
            commandSetToAll(param, 3);
			break;
		case 2:
			param[2] = 0x02;
            commandSetToAll(param, 3);
			break;
		default:
			break;
	}
}

static void getStartupInformation(void)
{
    BYTE param[3] = {MESSAGETYPE_IOCTL,0x2D, 0x00};
    commandSetToAll(param, 3);
}

void analyse_ServiceModule_Message(BYTE *buffer,  int length)
{
    BYTE cmd = buffer[0];
	switch(cmd)
	{
		case 0x01:	// parameter save(1) or read(0)
			if(buffer[1]) save_property();
			else set_property();

			break;
		case 0x2C:
			getSuspendInfomation(buffer[1]);
			break;
		case 0x2D:
			getStartupInformation();
			break;
		case 0x1D:
			getStandbyInfomation(buffer[1]);
			break;
	}
}



static int fly_device_get(unsigned char *buf,  int len)
{
	DBG2(debugPrintf("so=%s id=%d get\n", LOCAL_MODULE_NAME, LOCAL_MODULE_ID););

    return 0;
}

static int fly_device_set(unsigned char *buf, int len)
{
	DBG2(debugBuf("fly_device_set: ", buf, len););

	switch (buf[0])
	{
		case MESSAGETYPE_HAL:
			makeModuleCommMsgToHAL(&buf[2], len-2, buf[1]);
			break;
		case MESSAGETYPE_APP:
			makeModuleCommMsgToJNI(&buf[1], len-1);
			break;
		case MESSAGETYPE_BROADCAST:
			analyse_ServiceModule_Message(&buf[1], len-1);
			break;
		default:
			break;
	}

    return 0;
}





static void moduleInit()
{
	BYTE buf[10] = {MESSAGETYPE_INIT};
	commandSetToAll(buf, 1);

	buf[0] = MESSAGETYPE_IOCTL;
	buf[1] = 0xFD;
	buf[2] = 0x00;
	commandSetToAll(buf, 3);

	buf[1] = 0xFE;
	commandSetToAll(buf, 3);

}

static int moduleServiceInit()
{
    struct hw_module_t *phw[HAL_MODULE_MAX_NUM]={NULL};
    struct hw_device_t hwDev[HAL_MODULE_MAX_NUM];
	MODULE_INIT_INFO initInfo;
	int i = 0;
	
	memset(&initInfo, 0, sizeof(MODULE_INIT_INFO));
	memset(&hwDev, 0, HAL_MODULE_MAX_NUM*sizeof(struct hw_device_t));
	
    initInfo.moduleMsgId = 0;
    initInfo.moduleType = PRODUCT_MODULE;

	debugTagSet(LOG_TAG);

	if(FALSE == moduleInterfaceInit(&initInfo))
	{
		debugPrintf("module init fail\n");
		return FALSE;
	}

	for (i = 0; i < HAL_MODULE_MAX_NUM; i++)
	{
		command_register_set(i, default_set);
		command_register_get(i, default_get);
	}

	
	command_register_set(LOCAL_MODULE_ID, fly_device_set);
	command_register_get(LOCAL_MODULE_ID, fly_device_get);

	switch_moduleconfig_from_Thetype_file();
	
    if (FALSE == analyseModulelistXml(MODULELISTFILENAME,phw,(struct hw_device_t*)hwDev))
    {
    	debugPrintf("analyseModulelistXml fail\n");
		return FALSE;
    }

	//moduleInit();
	
	return TRUE;
}


int main(int argc, char **argv)
{
	BYTE buf[4096];
	int len = 0;
	BYTE moduleId = 0;
	
	if(FALSE == moduleServiceInit())
	{
		debugPrintf("moduleServiceInit fail\n");
		Sleep(5*1000);
	}

	
	while(1)
	{
	    
		len = readDataFromModuleComm(buf, 4096);

		if (len > 0)
		{
			DBG2(debugBuf("readModComm:", buf, len););
			switch (buf[3])
			{
				case HALMSG_MODULE:
					buf[3] = MESSAGETYPE_HAL;
					command_set(GotoModuleID_getHalID(buf[4]),&buf[3],buf[2]-1);
					break;
				case JNIMSG_MODULE:
					buf[3] = MESSAGETYPE_APP;
					moduleId = buf[5];
					if (moduleId == 0x00)
					{
						moduleId = 0xFE;
					}
					command_set(moduleId,&buf[3],buf[2]-1);
					break;
				case INITMSG_MODULE:
					 moduleInit();
					break;
				default:
					break;
			}
		}
	}

    return 0;
}


