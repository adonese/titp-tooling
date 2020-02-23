#ifndef AFX_POS8583_H
#define AFX_POS8583_H
 
 
typedef struct 
{
	u8 RidFlag[2];
	u8 RidLen;
	u8 RID[5];
	
	u8 CAPKIFlag[2];
	u8 CAPKILen;
	u8 CAPKI;
	
	u8 ExpDateFlag[2];
	u8 ExpDateLen;
	u8 ExpireDate[8];
}TSEmvCapkIdx;
#define CAPKIDXLEN	19	 
 
typedef struct		 
{
	u8 AidFlag[2];
	u8 AidLen;
	u8 Aid[16];
}TSEmvParamIdx;
 
#define NO_ACTION		0x00	 
#define ACTPRINT		0x01	 
#define ACTREVERSAL		0x02	 
#define ACTLOG			0x04	 
#define ACTTRACEADD		0x08	 
                                 
typedef struct _POS8583PACKET_STRC {
	int            iTransNo;              
	unsigned char  TransCode[7];          
	 
	//  ACTIONPRINT ACTIONREVERSE ACTIONELOG ACTIONTRACENO
	unsigned char  action;			
	char  SevCode[3];		 
	char  MessCode[3];		 
	char  NetInfoCode[4];	 
	char  SendMsgId[5];		 
	char  RecvMsgId[5];		 
	char  ReversedMsgId[5];	 
	u8    BitmapSend[8];	 
	u8    BitmapReverse[8];	 
} POS8583PACKET_STRC;        
#define TRANS8583_STRC_LEN sizeof(struct _POS8583PACKET_STRC)

//
enum	 
{
	RECORDNORMAL	=	0x00,	 
	RECORDVOID		=	0x01,	 
	RECORDHAVEUP	=	0x02	 
};

typedef struct {
	 
	u8 ucRecFalg;					 
	u8 EccTrans; 					 
	u8 IccOnline;					 
	u8 IccFallBack;					 
	u16 nIccDataLen;				 
	u8 Trans_id;					 
	u8 SecTransId;					 
	char MainAcc[22];				 
	u8 TradeAmount[6+1];			 
	u8 TradeDate[4];				 
	u8 TradeTime[3];				 
	u8 OperatorNo;					 
	u32 lTraceNo;				 	 
	u32 lNowBatchNum;				 
	char szRespCode[2+1];       	 
	u16  SignRecFlag;				 

 
	u8 bitmapsend[8];				 
	u8 ResProcCode[3+1];			 
	u8 TipAmount[6];				 
	u8 TradeDateAndTime[5];			 
	u8 ExpDate[4];					 
	u8 EntryMode[4];				 
	u8 field_26[2];					 
	u8 DesAndFrCardFlag_28;			 
	u8 CenterId[9];					 
	char SysReferNo[13];			 
	char AuthCode[7];				 
	char TerminalNo[9];				 
	char MerchantNo[16];			 
	char MerchTermNO[5];			 
	u8 szIssuerBankId[9];            
	u8 szRecvBankId[9];				 
	u8 SecondAmount[6];				 
	u8 SecondAccMode;				 
	char SecondAcc[21];				 
	char SecondHoldername[20+1];	 
	char HoldCardName[20+1];		 
	u8 cardType[16+1];				 
	//u8 IccSn[2];					 
	char AddInfo[122+1];			 
	u32 OldTraceNo;					 
	u32 OldBatchNum;				 
	char OldTransDate[9];			 
	char OldSysRefNo[13];			 
	char OldTermNo[9];				 
	// EMV                   
	u8	IccData[1+255];				 
	char szCardUnit[4];  			 
	u8	bPanSeqNoOk;				 
	u8	ucPanSeqNo;					 
	u8	sAppCrypto[8];				 
	u8	sAuthRspCode[2];             
	u8	sTVR[5];                     
	u8	sAIP[2];                     
	u8  szUnknowNum[4];              
	char szAID[32+1];                
	char szAppLable[16+1];           
	u8	sTSI[2];                     
	u8	sATC[2];                     
	u8	szAppPreferName[16+1];       
	u8	Ec_Balance[6];				 
	char nBlock632Len;               
	char szBlock632[120];			 
	char szTransCode[7];			 
	u8   OldTransCode[7];			 
} LOG_STRC;                          
#define LOG_SIZE  sizeof(LOG_STRC)   

typedef struct{  
	u8 sPIN[9];						    
	u8 sField40_oldTerNum[4];		 
	char sField47[128];				 
	u16 iField48Len;                 
	u8 sField48[512];				 
	char sField54[64];               
	u16 iField58Len;
	u8 sField58[512];
	char sField61[64];
	u8 sField62[512];
	u8 ucPrtflag;					 
	u8 ucWriteLog;					 
	u8 ucPointType;					 
	u8 ucRmbSettRsp;				 
	u8 ucFrnSettRsp;				 
	u8 ucAmtSign;					 
	u8 sOrignTransInfo[31]; 		 
	u8 BalanceAmount[1+40];			 
	u8 Track1[88]; 					 
	u8 Track2[2+37]; 				 
	u8 Track3[2+107];				 
	u8 Track1Len;					 
	u8 Track2Len;					 
	u8 Track3Len;					 
	int IsSaveLogAndRev;			 
	POS8583PACKET_STRC stTrnTbl;	 
	LOG_STRC stTrans;				 
	//                               
	u8 HaveInputAmt;				 
	u8 HaveInputPin;				 
	u16 nRespIccLen;				 
	u8 RespIccData[512];
	//EMV                          
	u8 szCertData[2+20+1];			 
	int iReversalDE55Len;          
	u8 sReversalDE55[128];			 
	int iScriptDE55Len;            
	u8 sScriptDE55[128];			 
	u8 sSign50[1024];				 
	u16 iSign50Len;
}POS_COM;
/******************************858 *************************************/
typedef struct _ISO8583_FieldDef_ {
    int length;
    int maxlength;
	int packed;
} ISO8583_FieldDef;

#define	L_LLVAR	        			1002
#define	L_LLLVAR	    			1003

#define	ISO_8583_PACKED				1
#define	ISO_8583_UNPACKED			0

typedef struct{
	char baglen[3];	 
	char destype;	 
	char merchant[15];
	char terminal[8];
	char tradeflag[10];	 
	char respcode[2];	 
	char reverse[2];
} ENCBAGHEAD;
#define ENCBAGHEAD_SIZE  sizeof(ENCBAGHEAD)
 
int CalMac(u8 *lpOut, u8 *lpIn, u16 len);
 
int Pack8583Packet(unsigned char *Packet, u8 Type);
 
int Pack8583PackDealBitmap(u8 *pBitmap, u8 ifreverse);
 
int Pack8583PacketData(u8* Packet); 
void DispRenewKeyResult( int Ret);
 
int PPWriteCUPKey(unsigned char *Inbuf, u16 len);
 
int PEDWriteCUPKey(unsigned char *Inbuf, u16 len);
 
int Parse8583PacketData(u8 Bitno, u8 *buf, int len, u8 *packet, u16 PackLen);
 
int ResolveHostPacket(unsigned char  *Packet, u16 PacketLen);
 
int Init8583Packet(u8 *Packet);
 
int Setting8583PrimaryField(int BitNo, u8 * Field, int FieldLength);
 
int Get8583MsgID(void);
 
int Get8583Field(u8 *BitNo, u8 *Field); 
int GetTradeTable(POS8583PACKET_STRC *ptPackTable, int Txn);
 
int PackCupBlock62(u8* psFieldBuf); 
u8 *FindMemFromMem(u8 *pSrc, u16 nSrcLen, u8 *pFind, u16 nFindLen);
 
int ParseCupBlock62(u8 *psBuf, u16 nPackLen);

#endif
