///////////////////////////////////////////////////////////////////////////////
///
/// Declaration file for Apple Authentication Co-processor CCP class.
///
///////////////////////////////////////////////////////////////////////////////
#ifndef _CP_H_
#define _CP_H_

#define		ERROR_VALUE			(-1)

// Authchip registers
#define ACP_REG_DEVICE_VERSION                                     (0x00)
#define ACP_REG_FW_VERSION                                            (0x01)
#define ACP_REG_AUTH_PROTO_MAJOR_VERSION            (0x02)
#define ACP_REG_AUTH_PROTO_MINOR_VERSION            (0x03)
#define ACP_REG_DEVICE_ID                                                (0x04)
#define ACP_REG_ERROR_CODE                                           (0x05)
#define ACP_REG_AUTH_CTRL_STATUS                               (0x10)
#define ACP_REG_SIG_DATA_LEN                                        (0x11)
#define ACP_REG_SIG_DATA                                                (0x12)
#define ACP_REG_CHALLENGE_DATA_LEN                          (0x20)
#define ACP_REG_CHALLENGE_DATA                                  	(0x21)
#define ACP_REG_ACC_CERT_DATA_LEN                   		(0x30)
#define ACP_REG_ACC_CERT_DATA_P1                    		(0x31)
#define ACP_REG_ACC_CERT_DATA_P2                   		(0x32)
#define ACP_REG_ACC_CERT_DATA_P3                    		(0x33)
#define ACP_REG_ACC_CERT_DATA_P4                    		(0x34)
#define ACP_REG_ACC_CERT_DATA_P5                    		(0x35)
#define ACP_REG_ACC_CERT_DATA_P6                    		(0x36)
#define ACP_REG_ACC_CERT_DATA_P7                    		(0x37)
#define ACP_REG_ACC_CERT_DATA_P8                    		(0x38)
#define ACP_REG_ACC_CERT_DATA_P9                    		(0x39)
#define ACP_REG_ACC_CERT_DATA_P10                   		(0x3A)
#define ACP_REG_ACC_CERT_DATA_P11                   		(0x3B)
#define ACP_REG_ACC_CERT_DATA_P12                   		(0x3C)
#define ACP_REG_ACC_CERT_DATA_P13                   		(0x3D)
#define ACP_REG_ACC_CERT_DATA_P14                   		(0x3E)
#define ACP_REG_ACC_CERT_DATA_P15                   		(0x3F)
#define ACP_REG_SELF_TEST_CTRL_STATUS               	(0x40)
#define ACP_REG_IPOD_CERT_DATA_LEN                  		(0x50)
#define ACP_REG_IPOD_CERT_DATA_P1                   		(0x51)
#define ACP_REG_IPOD_CERT_DATA_P2                   		(0x52)
#define ACP_REG_IPOD_CERT_DATA_P3                   		(0x53)
#define ACP_REG_IPOD_CERT_DATA_P4                   		(0x54)
#define ACP_REG_IPOD_CERT_DATA_P5                   		(0x55)
#define ACP_REG_IPOD_CERT_DATA_P6                   		(0x56)
#define ACP_REG_IPOD_CERT_DATA_P7                   		(0x57)
#define ACP_REG_IPOD_CERT_DATA_P8                   		(0x58)


class CCP  
{
public:
	int h;
	bool Init();
    	unsigned char GetDeviceVersion();
    	unsigned char GetAuthProtocolMajor();
   	unsigned char GetAuthProtocolMinor();
    	unsigned char GetFWVersion();

	CCP();
	virtual ~CCP();
};

#endif // _CP_H_
