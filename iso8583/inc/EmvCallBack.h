#ifndef _EMVCALLBACK_H
#define _EMVCALLBACK_H


#define MENU_LINES					3



int CEmvWaitAppSel(int TryCnt, unsigned char *AppNameList, int AppNum);
int CEmvAppConfirmBeforeSelect(unsigned char *Aid, int aidLen);
int CEmvAppConfirmBeforeSelectForLoad(unsigned char *Aid, int aidLen);
int CEmvGetUnknowTLV(unsigned short Tag, unsigned char *dat, int len);
int  CEmvGetDateTime(unsigned char *DateTime);
void CEmvIoCtrl(unsigned char ioname,unsigned char *iovalue);
int CEmvInputAmt(unsigned char *AuthAmt, unsigned char *CashBackAmt);
void CEmvAdviceProc(void);
int CEmvVerifyCert(void);
void CEmvVerifyPINOK(void);
int CEmvGetHolderPwd(int iTryFlag, int iRemainCnt, unsigned char *pszPlainPin);
int CEmvReferProc(void);
void  CEmvGetAllAmt(unsigned char *PANData,int PANDataLen, unsigned char AuthAmt[6], unsigned char bcdTotalAmt[6]);
int CEmvDispCardNo(void);
int CEmvReadAndHandleQPbocExData(unsigned long *amt, unsigned char *qpbocExType);
int CEmvUpdateQPbocExData(void);
int CEmvAccountTypeSelect(const char **accTypeNameList, int num, unsigned char *selItemNo);
int CEmvReadSN(unsigned char *Sn);
unsigned char CEmvKeypadEncrypt(unsigned char KeyIndex, unsigned char Mode, unsigned char *DataIn, int DataInLen , unsigned char *DataOut  );
int CEmvHandleBeforeGPO(void);

#endif




