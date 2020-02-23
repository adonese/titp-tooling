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




#define DE55_MUST_SET		1			//必须存在
#define DE55_OPT_SET		2			//可选择存在
#define DE55_COND_SET		3			//根据条件存在

#define TAG_NULL_1			0x00		// null tag
#define TAG_NULL_2			0xFF		// null tag

#define  E_NEED_FALLBACK	91			//51 需要FALLBACK 
#define  ONLINE_REQUEST		55			//IC交易要求联机 

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


#define ICC_EMV				0			//emv卡座

#define  PARAM_OPEN			1
#define  PARAM_CLOSE		0

#define TERM_AIDLIST		"termaid.lst"   
#define ICC_SCRIPT_FILE		"iccscript"
#define FILE_TOTAL_LMT		"total.lmt"
#define CAPK_FILE			"capkfile"  




#define ENGLISH				0
#define CHINESE				1

#define TYPE_CASH			0x01		//交易类型(现金)
#define TYPE_GOODS			0x02		//交易类型(购物)
#define TYPE_SERVICE		0x04		//交易类型(服务)
#define TYPE_CASHBACK		0x08		//交易类型(反现)
#define TYPE_INQUIRY		0x10		//交易类型(查询)
#define TYPE_PAYMENT		0x20		//交易类型(支付)
#define TYPE_ADMINISTRATIVE	0x40		//交易类型(管理)
#define TYPE_TRANSFER		0x80		//交易类型(转账)

#define MAX_APP_NUM			32			//应用列表最多可存储的应用数
#define MAX_CAPK_NUM		64			//认证公钥表最多可存储的公钥数
#define MAX_CAPKREVOKE_NUM	96			//认证公钥撤回列表的最大个数32*3

#define PART_MATCH			0x00		//ASI(部分匹配)
#define FULL_MATCH			0x01		//ASI(完全匹配)

#define EMV_GET_POSENTRYMODE			0 
#define EMV_GET_BATCHCAPTUREINFO		1 
#define EMV_GET_ADVICESUPPORTINFO		2 

//交易处理函数返回码定义
#define EMV_OK              0			//成功  
#define ERR_EMVRSP         (-2)			//返回码错误
#define ERR_APPBLOCK       (-3)			//应用已锁
#define ERR_NOAPP          (-4)			//卡片里没有EMV应用
#define ERR_USERCANCEL     (-5)			//用户取消当前操作或交易
#define ERR_TIMEOUT        (-6)			//用户操作超时
#define ERR_EMVDATA        (-7)			//卡片数据错误
#define ERR_NOTACCEPT      (-8)			//交易不接受
#define ERR_EMVDENIAL      (-9)			//交易被拒绝
#define ERR_KEYEXP         (-10)		//密钥过期
#define ERR_NOPINPAD       (-11)		//没有密码键盘或键盘不可用
#define ERR_NOPIN          (-12)		//没有密码或用户忽略了密码输入
#define ERR_CAPKCHECKSUM   (-13)		//认证中心密钥校验和错误
#define ERR_NOTFOUND       (-14)		//没有找到指定的数据或元素
#define ERR_NODATA         (-15)		//指定的数据元素没有数据
#define ERR_OVERFLOW       (-16)		//内存溢出
#define ERR_NOTRANSLOG     (-17)		//无交易日志
#define ERR_NORECORD       (-18)		//无记录
#define ERR_NOLOGITEM      (-19)		//目志项目错误
#define ERR_ICCRESET       (-20)		//IC卡复位失败
#define ERR_ICCCMD         (-21)		//IC命令失败
#define ERR_ICCBLOCK       (-22)		//IC卡锁卡 
#define ERR_ICCNORECORD    (-23)		//IC卡无记录
#define ERR_GENAC1_6985    (-24)		//GEN AC命令返回6985
#define ERR_USECONTACT     (-25)		//非接失败，改用接触界面
#define ERR_APPEXP         (-26)		//qPBOC卡应用过期
#define ERR_BLACKLIST      (-27)		//qPBOC黑名单卡
#define ERR_GPORSP         (-28)		//err from GPO
#define ERR_TRANSEXCEEDED		(-30)	//非接交易超限
#define ERR_QPBOCFDDAFAIL		(-31)
///////////////140910增加
#define ERR_UNSUPPORTED			(-32)	//不支持
#define ERR_NOFILE				(-33)	//没有文件
#define ERR_DENIALFORECC		(-34)	//拒绝纯电子现金卡的联机交易
#define ERR_RMAC				(-35)	//安全报文mac校验错
#define ERR_RFNOTAG9F66			(-36)	//非接的PDOL中没有9f66
#define ERR_MACCHECK			(-37)
#define ERR_MEMERR				(-38)	//6581 内存失败
#define ERR_LENERR				(-39)	//6700 长度错误
#define ERR_CONDNOTSATISFIED	(-40)	//6985 条件不满足
#define ERR_CMDNOEXIST			(-41)	//6d00 命令不存在
#define ERR_CMDNOTSUPPORT		(-42)	// 6e00 命令类型不支持
#define ERR_TCUNAVAILABLE		(-43)	//9406 所需TC不可用
#define ERR_READ_LAST_REC		-44		//读最后一条记录失败
#define ERR_ECBALANCE_SHORT		-45		//纯电子现金卡余额不足


#define ERR_RESERVER_FOR_EMV	(-1024)     //emv模块保留的错误码(-1到-1024)

#define REFER_APPROVE		0x01		//参考返回码(选择批准)
#define REFER_DENIAL		0x02		//参考返回码(选择拒绝)
#define ONLINE_APPROVE		0x00		//联机返回码(联机批准)     
#define ONLINE_FAILED		0x01		//联机返回码(联机失败) 
#define ONLINE_REFER		0x02		//联机返回码(联机参考)
#define ONLINE_DENIAL		0x03		//联机返回码(联机拒绝)
#define ONLINE_ABORT		0x04		//兼容PBOC(交易终止)
#define ONLINE_REFERANDFAIL 0x05		//联机拒绝和联机参考


#define PATH_PBOC			0x00		//应用路径:标准PBOC
#define PATH_QPBOC			0x01		//应用路径:qPBOC
#define PATH_MSD			0x02		//应用路径:MSD
#define PATH_ECash			0x03		//应用路径:电子现金




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