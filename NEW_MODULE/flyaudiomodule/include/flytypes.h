#ifndef __FLY_TYPES_H
#define __FLY_TYPES_H


typedef int		int32;
typedef short	int16;
typedef char		int8;

typedef unsigned int		uint32;
typedef unsigned short	uint16;
typedef unsigned char		uint8;

typedef unsigned int 		u32;
typedef unsigned short	u16;
typedef unsigned char		u8;

typedef u32		U32;
typedef u16		U16;
typedef u8		U8;


typedef U32			OBJID_T;
typedef u32			objid_t;

typedef U16			PAGEID_T;
typedef u16			pageid_T;

typedef U8			HALID_T;
typedef u8			halid_t;

typedef U8			MODULEID_T;
typedef u8			moduleid_t;

typedef U32			PARAMID_T;
typedef u32			paramid_t;

#define BUFFER_TO_OBJID(x)					(x[0]<<24 | x[1] << 16 | x[2] << 8 | x[3])

#define MODULE_ID(_obj_id)		((_obj_id >> 16) & 0xFF)	

#define ELEMENT_NR(x)			(sizeof(x)/sizeof(x[0]))

#endif
