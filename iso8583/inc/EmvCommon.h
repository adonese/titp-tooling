#ifndef _EMV_COMMON_H_
#define _EMV_COMMON_H_
#include "EmvTag.h"


#define TRAD_SALE  3
#define TRAD_QUARY 5


#define MAX_APPNAME_LEN		33		
#define EMV_PROC_BEGIN      0x01
#define EMV_PROC_REVERSE_ER 0x02
#define EMV_PROC_OLOK       0x04


typedef struct
{
	u8 sTotalOfflineAmt[6];				
	u8 sOfflineAmt[6];					
	u8 uTCUpFlag;						
	u8 uOffUpFlag;						
	u32 nEmvOfflineCount;			
	u32 nEmvOnlineCount;			
}STRUCT_TRADE_ATT;


typedef  struct  
{
	u8	ucAidLen;						
	u8	sAID[17];						
	u8	bOnlinePin;						
	unsigned long EC_TermLimit;		
}TERMAIDLIST;

typedef struct _limit_total_strc 
{
	u8 sTotalOfflineAmt[6];	
	u32 nCardOneDayAmt;		
	u32 nTotalOfflineCount;	
	u8 sOfflineAmt[6];		
	u32 nEmvOfflineCount;
}LIMIT_TOTAL_STRC;

typedef struct _tagDE55EmvTag
{
	unsigned short	uiEmvTag;
	unsigned char	ucOption;
}DE55EmvTag;

typedef struct _EMV_APPLIST_{
    unsigned char AppName[MAX_APPNAME_LEN];	
    unsigned char AID[17];					
    unsigned char AidLen;					
    unsigned char SelFlag;					      
    unsigned char Priority;					
    unsigned char TargetPer;			
    unsigned char MaxTargetPer;			
    unsigned char FloorLimitCheck;			
    unsigned char RandTransSel;				
    unsigned char VelocityCheck;			
    unsigned long FloorLimit;			
    unsigned long Threshold;				
    unsigned char TACDenial[6];				
    unsigned char TACOnline[6];			
    unsigned char TACDefault[6];			
    unsigned char AcquierId[7];				
    unsigned char dDOL[256];				
    unsigned char tDOL[256];				
    unsigned char Version[3];				
    unsigned char RiskManData[10];			
	unsigned char EC_bTermLimitCheck;		
	unsigned long EC_TermLimit;				
	unsigned char CL_bStatusCheck;			
	unsigned long CL_FloorLimit;			
	unsigned long CL_TransLimit;			
	unsigned long CL_CVMLimit;				
	unsigned char TermQuali_byte2;			
	unsigned char bOnlinePin;               
}EMV_APPLIST;





typedef struct _EMV_CAPK_{
    unsigned char RID[5];				
    unsigned char KeyID;				
    unsigned char HashInd;				
    unsigned char ArithInd;				
    unsigned char ModulLen;				
    unsigned char Modul[248];			
    unsigned char ExponentLen;			
    unsigned char Exponent[3];			
    unsigned char ExpDate[3];			
    unsigned char CheckSum[20];			
}EMV_CAPK;


typedef struct _EMV_PARAM_{
	unsigned char MerchName[128];		
	unsigned long FloorLimit; 
	unsigned char bCheckFloorLimit; 
	unsigned char bSupCandFromAidList_CL; 
	unsigned char IfSupportOnline;		
	unsigned char IfSupportRFPBOC;		
	unsigned char IfSupportContactMode;	
	unsigned char IfRequireCVM;			
	unsigned char IfSupportOnlinePIN;	
	unsigned char IfSupportSign;		
	unsigned char maxNumFashCardRec;    
	unsigned char FlashCardTimeout;  	
	
	unsigned char IfSupFlashCardHandle;  
	unsigned char IfSkipCardHolderVerify;   
	unsigned char pureECCSupportState;	
	unsigned char reserv_1[111];
	unsigned char MerchCateCode[2];		
	unsigned char MerchId[15];				
	unsigned char TermId[8];				
	unsigned char TerminalType;				
	unsigned char Capability[3];			
	unsigned char ExCapability[5];			
	unsigned char TransCurrExp;				
	unsigned char ReferCurrExp;				
	unsigned char ReferCurrCode[2];			
	unsigned char CountryCode[2];			
	unsigned char TransCurrCode[2];			
	unsigned long ReferCurrCon;				
	unsigned char TransType;				
	unsigned char ForceOnline;				
	unsigned char GetDataPIN;				
	unsigned char SupportPSESel;			
	unsigned char TermTransQuali[4];		
	unsigned char TermIsSupEct;				
	unsigned char ECTSI;					
	unsigned char bSurportSM;				
	unsigned char EC_bTermLimitCheck;		
	unsigned long EC_TermLimit;				
	unsigned char CL_bStatusCheck;			
	unsigned long CL_FloorLimit;			
	unsigned long CL_TransLimit;		
	unsigned long CL_CVMLimit;			

	unsigned char TermVersion[2];		
	unsigned char TermTargetPer;		
	unsigned char TermMaxTargetPer;	
	unsigned long TermThreshold;		
	unsigned char AIDForECCOnly[16]; 
	unsigned char AidLenForECCOnly; 
	char AcquierId[11+1];        
	unsigned char bSupportQPBOCEx; 
	unsigned char bSupportAccTypeSel; 
	unsigned char qpbocExMacKeyIdx; 
	unsigned char Reserve[4];         
}EMV_PARAM;


typedef struct _EMV_CLAPPLIST_{
    unsigned char AppName[MAX_APPNAME_LEN];	
    unsigned char AID[17];					
    unsigned char AidLen;					
    unsigned char SelFlag;					
    
    unsigned char Priority;				
    unsigned char TargetPer;				
    unsigned char MaxTargetPer;				
    unsigned char FloorLimitCheck;			
    
    unsigned char RandTransSel;				
    unsigned char VelocityCheck;		
    
    unsigned long FloorLimit;			
    unsigned long Threshold;			
    unsigned char TACDenial[6];			
    unsigned char TACOnline[6];			
    
    unsigned char TACDefault[6];			
    unsigned char AcquierId[7];				
    unsigned char dDOL[256];				
    unsigned char tDOL[256];				
    unsigned char Version[3];			
    
    unsigned char RiskManData[10];		
	unsigned char EC_bTermLimitCheck;		
	
	unsigned long EC_TermLimit;				
	
	unsigned char CL_bStatusCheck;			
	
	unsigned long CL_FloorLimit;			
	unsigned long CL_TransLimit;			
	unsigned long CL_CVMLimit;			
	
	unsigned char TermQuali_byte2;			
	unsigned char bOnlinePin;               
	

	unsigned char CL_TermQuali_byte1;		
	unsigned char CL_CountryCode[2];		
	unsigned char CL_TransCurrCode[2];		
	unsigned char CL_LimitForNoTicket[6];	
}EMV_CLAPPLIST;




#define DE55_MUST_SET		1			//�������
#define DE55_OPT_SET		2			//��ѡ�����
#define DE55_COND_SET		3			//������������

#define TAG_NULL_1			0x00		// null tag
#define TAG_NULL_2			0xFF		// null tag

#define  E_NEED_FALLBACK	91			//51 ��ҪFALLBACK 
#define  ONLINE_REQUEST		55			//IC����Ҫ������ 

// useful macro
#define _MIN(a, b)		( (a)<(b) ? (a) : (b) )
#define _MAX(a, b)		( (a)>(b) ? (a) : (b) )

// macros for analyze EMV TLV string
#define TAGMASK_CLASS		0xC0		// tag mask of tag class
#define TAGMASK_CONSTRUCTED	0x20		// tag mask of constructed/primitive data
#define TAGMASK_FIRSTBYTE	0x1F		// tag mask of first byte
#define TAGMASK_NEXTBYTE	0x80		// tag mask of next byte

#define LENMASK_NEXTBYTE	0x80		// length mask
#define LENMASK_LENBYTES	0x7F		// mask of bytes of lenght

#define TAG_NULL_1			0x00		// null tag
#define TAG_NULL_2			0xFF		// null tag


#define ICC_EMV				0			//emv����

#define  PARAM_OPEN			1
#define  PARAM_CLOSE		0

#define TERM_AIDLIST		"termaid.lst"   
#define ICC_SCRIPT_FILE		"iccscript"
#define FILE_TOTAL_LMT		"total.lmt"
#define CAPK_FILE			"capkfile"  




#define ENGLISH				0
#define CHINESE				1

#define TYPE_CASH			0x01		//��������(�ֽ�)
#define TYPE_GOODS			0x02		//��������(����)
#define TYPE_SERVICE		0x04		//��������(����)
#define TYPE_CASHBACK		0x08		//��������(����)
#define TYPE_INQUIRY		0x10		//��������(��ѯ)
#define TYPE_PAYMENT		0x20		//��������(֧��)
#define TYPE_ADMINISTRATIVE	0x40		//��������(����)
#define TYPE_TRANSFER		0x80		//��������(ת��)

#define MAX_APP_NUM			32			//Ӧ���б����ɴ洢��Ӧ����
#define MAX_CAPK_NUM		64			//��֤��Կ�����ɴ洢�Ĺ�Կ��
#define MAX_CAPKREVOKE_NUM	96			//��֤��Կ�����б��������32*3

#define PART_MATCH			0x00		//ASI(����ƥ��)
#define FULL_MATCH			0x01		//ASI(��ȫƥ��)

#define EMV_GET_POSENTRYMODE			0 
#define EMV_GET_BATCHCAPTUREINFO		1 
#define EMV_GET_ADVICESUPPORTINFO		2 

//���״����������붨��
#define EMV_OK              0			//�ɹ�  
#define ERR_EMVRSP         (-2)			//���������
#define ERR_APPBLOCK       (-3)			//Ӧ������
#define ERR_NOAPP          (-4)			//��Ƭ��û��EMVӦ��
#define ERR_USERCANCEL     (-5)			//�û�ȡ����ǰ��������
#define ERR_TIMEOUT        (-6)			//�û�������ʱ
#define ERR_EMVDATA        (-7)			//��Ƭ���ݴ���
#define ERR_NOTACCEPT      (-8)			//���ײ�����
#define ERR_EMVDENIAL      (-9)			//���ױ��ܾ�
#define ERR_KEYEXP         (-10)		//��Կ����
#define ERR_NOPINPAD       (-11)		//û��������̻���̲�����
#define ERR_NOPIN          (-12)		//û��������û���������������
#define ERR_CAPKCHECKSUM   (-13)		//��֤������ԿУ��ʹ���
#define ERR_NOTFOUND       (-14)		//û���ҵ�ָ�������ݻ�Ԫ��
#define ERR_NODATA         (-15)		//ָ��������Ԫ��û������
#define ERR_OVERFLOW       (-16)		//�ڴ����
#define ERR_NOTRANSLOG     (-17)		//�޽�����־
#define ERR_NORECORD       (-18)		//�޼�¼
#define ERR_NOLOGITEM      (-19)		//Ŀ־��Ŀ����
#define ERR_ICCRESET       (-20)		//IC����λʧ��
#define ERR_ICCCMD         (-21)		//IC����ʧ��
#define ERR_ICCBLOCK       (-22)		//IC������ 
#define ERR_ICCNORECORD    (-23)		//IC���޼�¼
#define ERR_GENAC1_6985    (-24)		//GEN AC�����6985
#define ERR_USECONTACT     (-25)		//�ǽ�ʧ�ܣ����ýӴ�����
#define ERR_APPEXP         (-26)		//qPBOC��Ӧ�ù���
#define ERR_BLACKLIST      (-27)		//qPBOC��������
#define ERR_GPORSP         (-28)		//err from GPO
#define ERR_TRANSEXCEEDED		(-30)	//�ǽӽ��׳���
#define ERR_QPBOCFDDAFAIL		(-31)
///////////////140910����
#define ERR_UNSUPPORTED			(-32)	//��֧��
#define ERR_NOFILE				(-33)	//û���ļ�
#define ERR_DENIALFORECC		(-34)	//�ܾ��������ֽ𿨵���������
#define ERR_RMAC				(-35)	//��ȫ����macУ���
#define ERR_RFNOTAG9F66			(-36)	//�ǽӵ�PDOL��û��9f66
#define ERR_MACCHECK			(-37)
#define ERR_MEMERR				(-38)	//6581 �ڴ�ʧ��
#define ERR_LENERR				(-39)	//6700 ���ȴ���
#define ERR_CONDNOTSATISFIED	(-40)	//6985 ����������
#define ERR_CMDNOEXIST			(-41)	//6d00 �������
#define ERR_CMDNOTSUPPORT		(-42)	// 6e00 �������Ͳ�֧��
#define ERR_TCUNAVAILABLE		(-43)	//9406 ����TC������
#define ERR_READ_LAST_REC		-44		//�����һ����¼ʧ��
#define ERR_ECBALANCE_SHORT		-45		//�������ֽ�����


#define ERR_RESERVER_FOR_EMV	(-1024)     //emvģ�鱣���Ĵ�����(-1��-1024)

#define REFER_APPROVE		0x01		//�ο�������(ѡ����׼)
#define REFER_DENIAL		0x02		//�ο�������(ѡ��ܾ�)
#define ONLINE_APPROVE		0x00		//����������(������׼)     
#define ONLINE_FAILED		0x01		//����������(����ʧ��) 
#define ONLINE_REFER		0x02		//����������(�����ο�)
#define ONLINE_DENIAL		0x03		//����������(�����ܾ�)
#define ONLINE_ABORT		0x04		//����PBOC(������ֹ)
#define ONLINE_REFERANDFAIL 0x05		//�����ܾ��������ο�


#define PATH_PBOC			0x00		//Ӧ��·��:��׼PBOC
#define PATH_QPBOC			0x01		//Ӧ��·��:qPBOC
#define PATH_MSD			0x02		//Ӧ��·��:MSD
#define PATH_ECash			0x03		//Ӧ��·��:�����ֽ�




int EmvInitDefParam(void);
u32 ByteToLong(u8 *pSrc, u8 SrcLen);
int ReadTermAidList(void);
int WriteTermAidList(TERMAIDLIST *pTermAidList);
int DelTermAidList(unsigned char *AID, int AidLen);
void RemoveTailChars(char* pString, char cRemove);
void InitCapkFile(void);
void InitTestApps(void);
void FormatAmt_Str(char *pDest, char *pSrc);
void DisplayProcessing(void);
int DispCardNumber(char *CardNo,int len);
void FormatAmtToDisp(char *pOut, u8 *pIn, u8 flag);
int EmvProcess(int CommType, int TradType); // ic or picc
int DetectICPICC(u8 Mode);
int MyEmvCardProc(int tradeType, u8 *pTrackBuf);
int MyEmvTranProc(u8 *pConsumeAmt, u8 *pCashBackAmt, u8 *beOnline);
int MatchTrack2AndPan(u8 *pTrack2, u8 *pPan);
int MyGetEmvTrackData(u8 * pTrackBuf);
int MyGetCardFromTrackEx(char *cardNo, unsigned char *trackData);
int MyEMVICCOnlineTransComplete( int IsOnLineSucc);



#endif