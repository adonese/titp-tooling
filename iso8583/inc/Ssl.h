#ifndef _SSL_H
#define _SSL_H

#define		TIMEOUT			-2	
/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : test SSL
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : 0
NOTES     : N/A
*************************************************************************************/
int SSLTestFun(void);

void Connect();

int InitSSLVar(void);

int InitSSLCert(void);

//M1
int M1TestFun(void);

//Language font
void LanguageTest(void);


int OtherFun(void);


void SaveCommParam(void);
void ReadCommParam(void);

int SetLanParam();
void PrinterTest();
int Mifare1_test(void);
int SetGprsPara();

int SetConnectMode();
#endif