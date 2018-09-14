#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#define	FLYMESSAGE_MAX_LEN			(300)
#define	MESSAGEQUEUE_MAX_LEN		(1000)
#define	HALMESSAGE_MAX_LEN			(300)
#define	HALMESSAGEQUEUE_MAX_LEN		(1000)
#define	APPMESSAGE_MAX_LEN			(300)
#define	APPMESSAGEQUEUE_MAX_LEN		(1000)
#define	AGENTMESSAGE_MAX_LEN        (1000)


#define MESSAGETYPE_HAL				0
#define MESSAGETYPE_APP				1
#define MESSAGETYPE_MODULE			2
#define MESSAGETYPE_TIMER			3

#define MESSAGETYPE_INIT			4
#define MESSAGETYPE_IOCTL			5

#define MESSAGETYPE_BROADCAST		6

typedef struct
{
	unsigned char messageType;	//Message Type
	unsigned char messageParam1;// moduleID or others	sendModuleID
	unsigned char messageParam2;// halID or others		arrivedModuleID
	unsigned char messageLen;	//Message Length
	unsigned char messagebuf[FLYMESSAGE_MAX_LEN];// Message Buffer
} FLYMESSAGE;

typedef struct
{
	int startpos;	// message start position
	int endpos;		// message end position
	FLYMESSAGE message[MESSAGEQUEUE_MAX_LEN];	// message queue p
} MESSAGEQUEUE;

typedef struct
{
	unsigned char halID;
	unsigned char messageReserved1;
	unsigned char messageReserved2;
	unsigned char messageLen;			//Message Length
	unsigned char messagebuf[HALMESSAGE_MAX_LEN];	// hal Message Buffer
} HALMESSAGE;

typedef struct
{
	int startpos;		// message start position
	int endpos; 		// message end position
	HALMESSAGE message[HALMESSAGEQUEUE_MAX_LEN];	// hal message queue p
} HALMESSAGEQUEUE;


typedef struct
{
	unsigned char messageReserved1;//
	unsigned char messageReserved2;//
	unsigned char messageReserved3;//
	unsigned char messageLen;			//Message Length
	unsigned char messagebuf[APPMESSAGE_MAX_LEN];	// app message p
} APPMESSAGE;

typedef struct
{
	int startpos;	// message start position
	int endpos; 	// message end position
	APPMESSAGE message[APPMESSAGEQUEUE_MAX_LEN];	// app message queue p
} APPMESSAGEQUEUE;


typedef struct
{
	unsigned char sendModuleID;//
	unsigned char arrivedModuleID;//
	unsigned char messageReserved1;//
	unsigned char messageLen;			//Message Length
	unsigned char messagebuf[APPMESSAGE_MAX_LEN];	// app message p
} MODULEMESSAGE;


typedef struct
{
	unsigned short messageLen;			//Message Length
	unsigned char messagebuf[AGENTMESSAGE_MAX_LEN];	// agent Message Buffer
}AGENTMESSAGE;


typedef	FLYMESSAGE			flymessage_t;
typedef	MESSAGEQUEUE		messagequeue_t;
typedef HALMESSAGEQUEUE		halMessageQueue_t;
typedef HALMESSAGE			halMessage_t;
typedef APPMESSAGEQUEUE		appMessageQueue_t;
typedef APPMESSAGE			appMessage_t;
typedef MODULEMESSAGE		moduleMessage_t;
typedef AGENTMESSAGE        agentMessage_t;

#endif

