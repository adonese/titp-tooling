#ifndef EMVTAG__H__
#define EMVTAG__H__


#define TLV_TAG_IIN				0x43   
#define TLV_TAG_AID				0x4F	
#define TLV_TAG_ALABEL			0x50	
#define TLV_TAG_TRACK2EQ		0x57	
#define TLV_TAG_PAN				0x5A	
#define TLV_TAG_DDFNAME			0x5D	
#define TLV_TAG_CVNAME			0x5F20 
#define TLV_TAG_INVALID_DATE	0x5F24 
#define TLV_TAG_VALID_DATE		0x5F25 
#define TLV_TAG_ISCODE			0x5F28 
#define TLV_TAG_TCCODE			0x5F2A 
#define TLV_TAG_FSELLAG			0x5F2D 
#define TLV_TAG_SVRCODE			0x5F30 
#define TLV_TAG_PANSEQ			0x5F34 
#define TLV_TAG_IURL			0x5F50 
#define TLV_TAG_IBAN			0x5F53 
#define TLV_TAG_BIC				0x5F54 
#define TLV_TAG_ISCODE_ALPH2	0x5F55 
#define TLV_TAG_ISCODE_ALPH3	0x5F56 
#define TLV_TAG_APPTEMP			0x61	
#define TLV_TAG_FCITEMP			0x6F	
#define TLV_TAG_RPD				0x70	
#define TLV_TAG_RPTFMT2			0x77	
#define TLV_TAG_ISCRIPTFMT2		0x72	
#define TLV_TAG_DDT				0x73	
#define TLV_TAG_RPTFMT 			0x80	
#define TLV_TAG_AMT_B			0x81	
#define TLV_TAG_AIP				0x82	
#define TLV_TAG_DFN				0x84	
#define TLV_TAG_ISC				0x86
#define TLV_TAG_ALP				0x87	
#define TLV_TAG_SFI				0x88	
#define TLV_TAG_ARC				0x8A	
#define TLV_TAG_CDOL1			0x8C	
#define TLV_TAG_CDOL2			0x8D	
#define TLV_TAG_CVML			0x8E	
#define TLV_TAG_CAPKI			0x8F	
#define TLV_TAG_IPKC			0x90	
#define TLV_TAG_IAD				0x91	
#define TLV_TAG_ICPR			0x92	
#define TLV_TAG_SSAD			0x93	
#define TLV_TAG_AFL				0x94	
#define TLV_TAG_TVR			0x95
#define TLV_TAG_TDOL			0x97	
#define TLV_TAG_TDATE			0x9A	
#define TLV_TAG_TSI			0x9B  
#define TLV_TAG_TTYPE			0x9C	
#define TLV_TAG_DDATAFNAME		0x9D	
#define TLV_TAG_ACCOUNT_TYPE		0x5F57
#define TLV_TAG_AMT				0x9F02	
#define TLV_TAG_OMT				0x9F03	
#define TLV_TAG_OMT_B			0x9F04 
#define TLV_TAG_ADD				0x9F05	
#define TLV_TAG_AIDONT			0x9F06	
#define TLV_TAG_AUC				0x9F07	
#define TLV_TAG_CAV				0x9F08	
#define TLV_TAG_TAV				0x9F09	
#define TLV_TAG_CHNEX			0x9F0B	
#define TLV_TAG_IAC_DEF			0x9F0D	
#define TLV_TAG_IAC_REFUSE		0x9F0E	
#define TLV_TAG_IAC_ONLINE		0x9F0F 
#define TLV_TAG_IAPPD			0x9F10	
#define TLV_TAG_ICI				0x9F11	
#define TLV_TAG_AFN				0x9F12 
#define TLV_TAG_LOATCREG		0x9F13 
#define TLV_TAG_SOTFLOOR		0x9F14	
#define TLV_TAG_COTPIN			0x9F17	
#define TLV_TAG_TSC				0x9F1A 
#define TLV_TAG_TFLOOR			0x9F1B 
#define TLV_TAG_TRACK1			0x9F1F 
#define TLV_TAG_TRDTIME			0x9F21 
#define TLV_TAG_SOFFTTOP		0x9F23	
#define TLV_TAG_AC				0x9F26	
#define TLV_TAG_CID				0x9F27	
#define TLV_TAG_IPKEXP			0x9F32 
#define TLV_TAG_ATC				0x9F36 
#define TLV_TAG_UNPRENUM		0x9f37  
#define TLV_TAG_PDOL			0x9F38 
#define TLV_TAG_ACC_CVM			0x9F42 
#define TLV_TAG_ACEXP			0x9F44
#define TLV_TAG_DAC				0x9F45 
#define TLV_TAG_ICPKC			0x9F46 
#define TLV_TAG_ICPKEXP			0x9F47	
#define TLV_TAG_ICPKR			0x9F48 
#define TLV_TAG_DDOL			0x9F49
#define TLV_TAG_SDOL			0x9F4A 
#define TLV_TAG_SDAD			0x9F4B 
#define TLV_TAG_IDD				0x9F4C 
#define TLV_TAG_EOL				0x9F4D 
#define TLV_TAG_MERNAME			0x9F4E 
#define TLV_TAG_LOFFMT			0x9F4F 
#define TLV_TAG_ACC_MCHECK		0x9F51 
#define TLV_TAG_ADA				0x9F52	
#define TLV_TAG_SOFFTTOP_INT	0x9F53 

#define TLV_TAG_AOS_AMT			0x9F5D 
#define TLV_TAG_CARD_ARD		0x9F69 //Card Authentication Related Data 

#define TLV_TAG_IDDFCI			0xBF0C 
#define TLV_TAG_FCISTEMP		0xA5	
#define TLV_TAG_ECTTL			0x9F7B 
#define TLV_TAG_ECTSI			0x9F7A	
#define TLV_TAG_ECB				0x9F79 
#define TLV_TAG_ECSTL			0x9F78 
#define TLV_TAG_ECBL			0x9F77	
#define TLV_TAG_SECCC			0x9F76	
#define TLV_TAG_ACCOFFTAL_DC	0x9F75 
#define TLV_TAG_ECIAC			0x9F74 
#define TLV_TAG_ECRT 			0x9F6D 

#define TLV_TAG_TTQ				0x9F66 
#define TLV_TAG_CAPP_TI		0xDF60  
#define TLV_TAG_QPBOCEX_CSIGN		0xDF61  
#define TLV_TAG_CAPP_DMT_LMT			0xDF62 
#define TLV_TAG_CAPP_DMT					0xDF63 

#define TLV_TAG_SM_SIGN			0xDF69 
/////////////////////////////////////////////////////////////////////////////


#endif