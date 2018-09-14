// PKCS7Sign.cpp : Defines the entry point for the console application.  
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/objects.h"
#include "openssl/x509.h"
#include "openssl/err.h"
#include "openssl/pem.h"
#include "openssl/pkcs12.h" 


/*
PKCS7Sign.cpp
功能：调用OpenSSL实现数字签名功能
环境：Ubuntu,OpenSSL1.0.1c
*/
 
/*
功能：初始化OpenSSL
*/
void InitOpenSSL()
{
	CRYPTO_malloc_init();
	/* Just load the crypto library error strings,
	* SSL_load_error_strings() loads the crypto AND the SSL ones */
	/* SSL_load_error_strings();*/
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms(); 
	OpenSSL_add_all_ciphers();
	OpenSSL_add_all_digests();
}
 
/*
功能：对length长度的input指向的内存块进行BASE64编码
入口：
const void *input           指向内存块的指针
int length                  内存块的有效长度
返回：
char *                      返回字符串指针，使用完毕后，必须用free函数释放。
*/
char *base64(const void *input, int length)
{
  BIO *bmem, *b64;
  BUF_MEM *bptr;
 
  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, input, length);
  BIO_flush(b64);
  BIO_get_mem_ptr(b64, &bptr);
 
  char *buff = (char *)malloc(bptr->length);
  memcpy(buff, bptr->data, bptr->length-1);
  buff[bptr->length-1] = 0;
 
  BIO_free_all(b64);
 
  return buff;
}
 
/*
功能：base64解码
入口：
char *inputBase64  BASE64编码的签名
void *retBuf       缓存大小
返回：
void *retBuf       解码后数据存放在这块内存中
int *retBufLen     解码后数据的长度
*/
void *decodeBase64(char *inputBase64, void *retBuf,int *retBufLen)
{
	BIO *b64, *bmem;
	
	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new_mem_buf(inputBase64, strlen((const char *)inputBase64));
	bmem = BIO_push(b64, bmem); 
	int err=0;
	int i=0;
	do
	{
		err = BIO_read(bmem, (void *)( (char *)retBuf+i++), 1);
	}while( err==1 && i<*retBufLen );
	BIO_free_all(bmem);
 
	*retBufLen = --i;
	
	return retBuf;
}
 
 
 
/*
功能：对明文进行签名
入口：
char*certFile    证书（例如：xxx.pfx）
char* pwd        证书的密码
char* plainText  待签名的字符串
int flag         签名方式
出口：
char *           签名后的数据以BASE64形式返回
                 使用完毕后，必须用free函数释放。
*/
 
char * PKCS7_GetSign(char*certFile,char* pwd, char* plainText,int flag,unsigned long plainLen, unsigned long *cipherLen)
{
	//取PKCS12對象
	FILE* fp;
	if (!(fp = fopen(certFile, "rb"))) 
	{ 
		fprintf(stderr, "Error opening file %s\n", certFile);        
		return NULL;     
	}    
	PKCS12 *p12= d2i_PKCS12_fp(fp, NULL);  
	fclose (fp);    
	if (!p12) {      
		fprintf(stderr, "Error reading PKCS#12 file\n");   
		ERR_print_errors_fp(stderr);  
		return NULL;   
	} 
	 
	//取pkey对象、X509证书、证书链
	EVP_PKEY *pkey=NULL;     
	X509 *x509=NULL;
	STACK_OF(X509) *ca = NULL;
	if (!PKCS12_parse(p12, pwd, &pkey, &x509, &ca)) {         
		fprintf(stderr, "Error parsing PKCS#12 file\n");       
		ERR_print_errors_fp(stderr);
		return NULL;
	} 
	PKCS12_free(p12);
 
	//明文轉為BIO對象
	//《vc++网络安全编程范例（14）-openssl bio编程 》   http://www.2cto.com/kf/201112/115018.html
	BIO *bio = BIO_new(BIO_s_mem());  
	// BIO_puts(bio,plainText);
	BIO_write(bio, plainText, plainLen);
 
	//數字簽名
	//PKCS7_NOCHAIN:签名中不包含证书链，第三个参数为NULL值的话，可不加这个FLAG标记
	//PKCS7_NOSMIMECAP:签名不需要支持SMIME
	PKCS7* pkcs7 = PKCS7_sign(x509, pkey, ca, bio, flag);
	if(pkcs7==NULL)
	{
		ERR_print_errors_fp(stderr);
		return NULL;
	}
 
	//共有两种编码，一种是ASN1，另一种是DER编码。
	//取數據簽名(DER格式)
	//openssl之pkcs7-data的编码解码
	//http://ipedo.i.sohu.com/blog/view/114822358.htm
	//入口：pkcs7对象
	//出口:der对象
	unsigned char *der;
	unsigned char *derTmp;
	unsigned long derlen;
	derlen = i2d_PKCS7(pkcs7,NULL);
	der = (unsigned char *) malloc(derlen);
	memset(der,0,derlen);
	derTmp = der;
    i2d_PKCS7(pkcs7,&derTmp);
 
	//DER转BASE64
	*cipherLen = derlen;
	return base64(der,derlen);
}
 
/*
功能：验证签名
入口：
char*certFile    证书（含匙）
char* plainText  明文
char* cipherText 签名
出口：
bool true  签名验证成功
bool false 验证失败
*/
bool PKCS7_VerifySign(char* certFile,char* plainText,char* cipherText,int plainLen)
{
	/* Get X509 */
	FILE* fp = fopen(certFile, "rb");
	if (fp == NULL) 
		return false;

	X509* x509 = PEM_read_X509(fp, NULL, NULL, NULL);

	fclose(fp);
	if (x509 == NULL) 
	{
		ERR_print_errors_fp (stderr);
		return false;
	}

	//BASE64解码
	unsigned char *retBuf[1024*8];
	int retBufLen = sizeof(retBuf);
	memset(retBuf,0,sizeof(retBuf));
	decodeBase64(cipherText,(void *)retBuf,&retBufLen);
 
	//从签名中取PKCS7对象
	BIO* vin = BIO_new_mem_buf(retBuf,retBufLen);
	PKCS7 *p7 = d2i_PKCS7_bio(vin,NULL);
 
 
	//取STACK_OF(X509)对象
	STACK_OF(X509) *stack=sk_X509_new_null();//X509_STORE_new()
	sk_X509_push(stack,x509);
 
 
	//明码数据转为BIO
	BIO *bio = BIO_new(BIO_s_mem());  
	// BIO_puts(bio,plainText);
	BIO_write(bio, plainText, plainLen);

	//验证签名
	int err = PKCS7_verify(p7, stack, NULL,bio, NULL, PKCS7_NOVERIFY);
 
	if (err != 1) {
		ERR_print_errors_fp (stderr);
		return false;
	}
 
	return true;
}

//判断字符串是否全为数字：1是，0否
int isDigitStr(char const *str)
{
	return (strspn(str, "0123456789")==strlen(str));
}

//文件自适应,签名
void fileAdaptatSign(int argc, char const *argv[], char *plainFile, char *pfxFile, char *pwd)
{
	int i = 1;
	char PFX[] = "pfx";

	for(; i<argc; i++)
	{
		if(strstr((const char *)argv[i], PFX))
			strcpy(pfxFile, argv[i]);
		else if(isDigitStr(argv[i]))
			strcpy(pwd, argv[i]);
		else
			strcpy(plainFile, argv[i]);
	}
	return;
}

//文件自适应,验证签名
void fileAdaptVerify(int argc, char const *argv[], char *plainFile, char *certFile, char *cipherFile)
{
	int i = 1;
	char CER[] = "cer";
	char JKS[] = "jks";

	for(; i<argc; i++)
	{
		if(strstr((const char *)argv[i], CER))
			strcpy(certFile, argv[i]);
		else if(strstr((const char *)argv[i], JKS))
			strcpy(cipherFile, argv[i]);
		else
			strcpy(plainFile, argv[i]);
	}
	return;
}

//读文件
char *readFile(char *file, unsigned long *sizeFile)
{
	FILE *fp = fopen(file, "rb");
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);
	char *buf = (char *)malloc(size);

	fread(buf, size, 1, fp);
	if(sizeFile != NULL)
		*sizeFile = size;
	fclose(fp);

	return buf;
}

//生成签名文件.jks
void createCipherText(int argc, char const *argv[])
{
	char plainFile[256], pfxFile[256], pwd[256];
	char *cipher = (char *)"cipher.jks";
	
	InitOpenSSL();

	fileAdaptatSign(argc, argv, plainFile, pfxFile, pwd);

	unsigned long plainLen = 0;
	unsigned long cipherLen = 0;

	char *plainText = readFile(plainFile, &plainLen);
	char *cipherText = PKCS7_GetSign(pfxFile,pwd,plainText,PKCS7_DETACHED|PKCS7_NOSMIMECAP, plainLen, &cipherLen);

	unsigned long  cipherLen1 = strlen(cipherText);

	FILE *fp = fopen(cipher, "wb+");
	if(fp==NULL)
	{
		printf("cipher.jks fopen Failed\n");
		return;
	}
	size_t ret = fwrite(cipherText, 1, cipherLen1, fp);
	if (ret!=cipherLen1)
	{
		ret = remove(cipher);
		if(ret)
			perror("remove");
		printf("sign Failed!\n");
	}
	else
		printf("sign OK!\n");

	fclose(fp);
	free(plainText);
	
	return;
}

//验证签名文件
void PKCS7_VerifySignFile(int argc, char const *argv[])
{
	char certFile[256], plainFile[256], cipherFile[256];

    InitOpenSSL();

    fileAdaptVerify(argc, argv, plainFile, certFile, cipherFile);

    unsigned long plainLen = 0;
	char *plainText = readFile(plainFile, &plainLen);
	char *cipherText = readFile(cipherFile, NULL);


	//验证数字签名
	if(PKCS7_VerifySign(certFile,plainText,cipherText, plainLen))
		printf("Verify OK!\n");
	else
		printf("Verify Failed!\n");

	free(plainText);
	free(cipherText);
	return;
}



int main(int argc, char const *argv[])
{
	#ifdef SIGN
	createCipherText(argc, argv);
	#else
	PKCS7_VerifySignFile(argc, argv);
	#endif

	return 0;
}

