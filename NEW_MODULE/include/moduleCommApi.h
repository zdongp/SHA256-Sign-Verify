#ifndef MODULECOMMAPI_H_
#define MODULECOMMAPI_H_

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*t_msgProc)(unsigned char *buf, unsigned int len);


typedef enum
{
    HALMSG_MODULE = 0x54,
    PRODUCT_MODULE = 0x55,
    JNIMSG_MODULE = 0x56,
    INITMSG_MODULE = 0x57
} MODULETYPE;


typedef struct
{
    MODULETYPE moduleType;
    unsigned int moduleMsgId;
    t_msgProc pCmdMsgProc;
} MODULE_INIT_INFO, *P_MODULE_INIT_INFO;

int moduleInterfaceInit(P_MODULE_INIT_INFO moduleInitInfo);
int createReadCommThread();
int readDataFromModuleComm(unsigned char *buff, unsigned int len);
int writeDataToModuleComm(unsigned char *buff, unsigned int len);

int makeModuleCommMsgToHAL(unsigned char *msg, unsigned int len, unsigned int objID);
int makeModuleCommMsgToModule(unsigned char *msg, unsigned int len, unsigned int objID);
int makeModuleCommMsgToJNI(unsigned char *buf, unsigned int len);


#ifdef __cplusplus
}
#endif

#endif
