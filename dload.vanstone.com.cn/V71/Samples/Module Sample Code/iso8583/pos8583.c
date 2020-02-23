#include "stdafx.h"
#include "../inc/global.h"


static u8 *ucPacketPointer;		//8583 Packet operation Position
static int iPacketLength;		//8583 packet length

u8 sucBackTradeNOFlag;
 
//8583 Packet Bit Map S(8)、8583 Packet Bit Map S(8) 
#define  TRACE_NUM     51   
const POS8583PACKET_STRC TrTable[TRACE_NUM] = {	// 
	{ POS_ECHO,     "900010", NO_ACTION,
		"00", "00", "301", "0820", "0830","0400", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x10},
											{0x21,0x99,0x08,0x10,0x02,0xB0,0x00,0xF4}},
	{ POS_LOGON,     "900010", ACTTRACEADD,
		"00", "00", "001", "0800", "0810","0400", {0x00,0x20,0x00,0x00,0x00,0xC0,0x00,0x12},
											{0x21,0x99,0x08,0x10,0x02,0xB0,0x00,0xF4}},
	{ POS_SALE,    "000000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"00", "22", "000", "0200", "0210", "0400",{0x70,0x24,0x06,0xC0,0x30,0xC0,0x9A,0x11},
											{0x70,0x24,0x06,0x80,0x36,0xc0,0x82,0x11}},
	{ POS_SALE_VOID, "200000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"00", "23", "000", "0200", "0210", "0400",{0x70,0x20,0x06,0xC0,0x3C,0xc0,0x98,0x19},
											{0x70,0x24,0x06,0x80,0x36,0xC0,0x82,0x19}},
	{ POS_QUE,       "310000", ACTTRACEADD,
		"00", "01", "000", "0200", "0210","0400", {0x60,0x24,0x06,0xc0,0x30,0xC0,0x9A,0x11},
											{0x00,0x20,0x00,0x00,0x02,0x80,0x00,0x00}},
	{ POSPARAM_DOWN, "900000", ACTTRACEADD,
		"00", "00", "360", "0800", "0810","0400", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x10},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}}, 
	{ POSPARAM_DOWNEND, "900000", ACTTRACEADD,
		"00", "00", "361", "0800", "0810","0400", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x10},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ SYS_SIGNUPLOAD,     "000000", ACTTRACEADD,	//5022000008C00210
	"00", "07", "800", "0820", "0830", "0400",{0x50,0x20,0x02,0x00,0x08,0xC0,0x42,0x13},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	//emv类交易 
	{ EMVCAPK_DOWN, "900000", ACTTRACEADD,
		"02", "00", "370", "0800", "0810","0400", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x14},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}}, 
	{ EMVPARAM_DOWN, "900000",  ACTTRACEADD,
		"02", "00", "380", "0800", "0810","0400", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x14},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ EMVCAPK_QUERYIDX, "000000", ACTTRACEADD,
		"00", "00", "372", "0820", "0830","0440", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x14},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ EMVCAPK_END, "000000", ACTTRACEADD,
		"00", "00", "371", "0800", "0810","0440", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x10},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ EMVPARAM_QUERYIDX, "000000", ACTTRACEADD,
		"00", "00", "382", "0820", "0830","0440", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x14},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ EMVPARAM_END, "000000", ACTTRACEADD,
		"00", "00", "381", "0800", "0810","0440", {0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x10},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	/*其他标准应用*/
	{ POS_PREAUTH, "030000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"06", "10", "000", "0100", "0110","0400", {0x70,0x24,0x06,0xC0,0x30,0xC0,0x9A,0x11},
											{0x70,0x24,0x06,0x80,0x06,0xc0,0x82,0x11}},
	{ POS_PREAUTH_VOID, "200000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"06", "11", "000", "0100", "0110","0400", {0x70,0x24,0x06,0xC0,0x34,0xc0,0x98,0x19},
											{0x70,0x24,0x06,0x80,0x06,0xC0,0x82,0x19}},
	{ POS_PREAUTH_DONE, "000000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"06", "20", "000", "0200", "021","0400", {0x70,0x24,0x04,0xC0,0x34,0xC0,0x98,0x19},
											{0x70,0x24,0x04,0x80,0x06,0xC0,0x82,0x19}},
	{ POS_AUTH_VOID, "200000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"06", "21", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x3c,0xc0,0x98,0x19},
											{0x70,0x24,0x04,0x80,0x06,0xC0,0x82,0x19}},
	{ POS_PREAUTH_ADD, "030000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"06", "12", "000", "0100", "0110","0400", {0x70,0x24,0x06,0xC0,0x30,0xC0,0x9A,0x11},
											{0x70,0x24,0x06,0x80,0x06,0xc0,0x82,0x11}},
	{ POS_REFUND,    "200000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"00", "25", "000", "0220", "0230","0400", {0x70,0x24,0x06,0xC0,0x38,0xC0,0x98,0x1B},
											{0x70,0x24,0x06,0x80,0x06,0xC0,0x80,0x19}},
	{ POS_INST,    "000008", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"64", "40", "000", "0200", "0210","0400", {0x70,0x24,0x06,0xC0,0x30,0xC2,0x9A,0x17},
											{0x70,0x24,0x06,0x80,0x06,0xC0,0x80,0x19}},
	{ POS_INSTVOID,    "200008", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"64", "41", "000", "0200", "0210","0400", {0x70,0x24,0x06,0xC0,0x3C,0xC0,0x98,0x1B},
											{0x70,0x24,0x06,0x80,0x06,0xC0,0x80,0x19}},
	{ POS_INSTREFUND,    "210008", ACTPRINT + ACTLOG + ACTTRACEADD,
		"64", "41", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x3C,0xC0,0x98,0x1F},
											{0x70,0x24,0x06,0x80,0x06,0xC0,0x80,0x19}},
	{ POS_INSTQUERY,    "310008", ACTTRACEADD,
		"64", "42", "000", "0200", "0210","0400", {0x60,0x24,0x04,0xC0,0x30,0xE0,0x98,0x13},
											{0x70,0x24,0x06,0x80,0x06,0xC0,0x80,0x19}},
	{ POS_LOGOFF,    "000000", ACTTRACEADD,
		"00", "00", "002", "0820", "0830","0400", {0x00,0x20,0x00,0x00,0x00,0xc0,0x00,0x10},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}}, 
	{ POS_SETTLE,      "000000", ACTTRACEADD,
		"00", "00", "201", "0500", "0510", "0400",{0x00,0x20,0x00,0x00,0x00,0xc1,0x80,0x12},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ POS_BATCHUP,      "000000", ACTTRACEADD,
		"00", "00", "201", "0320", "0330", "0400",{0x50,0x20,0x06,0x00,0x00,0xc0,0x02,0x14},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ ICC_BATCHUP_TC,      "000000", ACTTRACEADD,
		"61", "00", "203", "0320", "0330", "0400",{0x50,0x20,0x06,0x00,0x00,0xc0,0x02,0x14},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ ICC_SCRSEND,      "000000", ACTTRACEADD,
		"00", "00", "951", "0620", "0630", "0400",{0x70,0x20,0x06,0x00,0x0C,0xC0,0x82,0x19},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ TMS_QUERY, "410000", NO_ACTION, 
		"00", "00", "000", "4100", "4110", "0420", {0x20,0x00,0x00,0x00,0x00,0xc0,0x00,0x03},
										      {0x20,0x00,0x00,0x00,0x02,0xc0,0x00,0x03}},

	// 
	{ POINTS_WASHCAR,    "930000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"65", "53", "000", "0200", "0210","0400", {0x60,0x24,0x06,0xC0,0x30,0xC0,0x18,0x11},
											{0x60,0x24,0x06,0xC0,0x30,0xC0,0x18,0x11}},
	{ POINTSCASH_SALEVOID,    "200009", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"65", "72", "000", "0200", "0210","0400", {0x70,0x24,0x06,0xC0,0x38,0xC0,0x98,0x1D},
											{0x70,0x24,0x06,0xC0,0x38,0xC0,0x98,0x1D}},
	{ POINTSCASH_PREQUE,    "100009", ACTTRACEADD,
		"65", "50", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x30,0xC0,0x98,0x11},
											{0x50,0x20,0x00,0x00,0x0a,0x80,0x00,0x00}},
	{ POINTSCASH_SALE,    "000009", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"65", "71", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x30,0xC0,0x98,0x15},
											{0x70,0x24,0x04,0x80,0x32,0xC0,0x80,0x15}},
	{ POINTS_QUERY,    "310009", ACTTRACEADD,
		"65", "52", "000", "0200", "0210","0400", {0x60,0x24,0x04,0xC0,0x30,0xC0,0x18,0x11},
											{0x50,0x20,0x00,0x00,0x0a,0x80,0x00,0x00}},
	{ POINTS_REFUND,    "200009", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"65", "52", "000", "0220", "0230","0400", {0x70,0x24,0x06,0xC0,0x3C,0xC1,0x98,0x11},
											{0x50,0x20,0x00,0x00,0x0a,0x80,0x00,0x00}},
	{ TRANSFER_CARDOUT,    "080000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"66", "56", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x30,0xC0,0x1A,0x15},
											{0x70,0x24,0x04,0x80,0x06,0xC0,0x00,0x15}},
	{ TRANSFER_REIMBURSED,    "180000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"66", "57", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x30,0xC0,0x18,0x15},
											{0x70,0x24,0x04,0x80,0x06,0xC0,0x00,0x15}},
	{ TRANSFER_REPAYMENT,    "280000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"66", "58", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x30,0xC0,0x18,0x15},
											{0x70,0x24,0x04,0x80,0x06,0xC0,0x00,0x15}},
	{ TRANSFER_CARDTOCARD,      "080000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"68", "56", "092", "0200", "0210", "0400",{0x70,0x2c,0x06,0xc0,0x30,0xc0,0x1a,0x15},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ RBPOINT_QUERY,    "310007", ACTTRACEADD,
		"65", "55", "000", "0200", "0210","0400", {0x60,0x24,0x04,0xC0,0x30,0xC0,0x18,0x11},
											{0x50,0x20,0x00,0x00,0x0a,0x80,0x00,0x00}},
	{ RBPOINT_CONSUME,    "000007", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"65", "53", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x30,0xC0,0x18,0x15},
											{0x70,0x24,0x04,0x80,0x36,0xC0,0x00,0x15}},
	{ RBPOINT_VOID,    "200007", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"65", "55", "000", "0200", "0210","0400", {0x70,0x24,0x04,0xC0,0x3C,0xC0,0x18,0x19},
											{0x70,0x24,0x04,0x80,0x06,0xC0,0x00,0x19}},
	{ QPBOC_SALE,    "000000", ACTPRINT + ACTLOG + ACTTRACEADD,
		"00", "36", "000", "0200", "0210", "0400",{0x70,0x3C,0x06,0xC0,0x38,0xC0,0x9A,0x13},
											{0x70,0x24,0x06,0x80,0x36,0xc0,0x82,0x11}},
	{ ECC_SALE,    "000000", ACTPRINT + ACTLOG + ACTTRACEADD,
		"00", "36", "000", "0200", "0210", "0400",{0x70,0x3C,0x06,0xC0,0x38,0xC0,0x9A,0x13},
											{0x70,0x24,0x06,0x80,0x36,0xc0,0x82,0x11}},
	{ ECC_ERRORUP,    "000000", ACTLOG + ACTTRACEADD,
		"00", "38", "000", "0200", "0210", "0400",{0x70,0x3C,0x06,0xC0,0x38,0xC0,0x9A,0x13},
											{0x70,0x24,0x06,0x80,0x36,0xc0,0x82,0x11}},
	{ ECC_REFUND,    "000000", ACTPRINT + ACTLOG + ACTTRACEADD,
		"00", "37", "000", "0220", "0230","0400", {0x70,0x3C,0x06,0xC0,0x34,0xC0,0x98,0x1B},
											{0x70,0x24,0x04,0x80,0x06,0xC0,0x00,0x19}},
	{ ECC_LOAD,    "700000", ACTPRINT + ACTREVERSAL + ACTLOG + ACTTRACEADD,
		"00", "80", "000", "0200", "0210","0400", {0x70,0x24,0x06,0x80,0x30,0xC0,0x9A,0x11},
											{0x70,0x24,0x04,0x80,0x06,0xC0,0x00,0x19}},
	{ PASSWORD_VERIFY,      "320000", ACTTRACEADD,
		"00", "01", "092", "0100", "0110", "0400",{0x60,0x24,0x06,0xc0,0x30,0xE0,0x9A,0x17},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ ACCOUNT_VERIFY,      "330000", ACTTRACEADD,
		"00", "01", "092", "0100", "0110", "0400",{0x70,0x24,0x06,0xc0,0x30,0xc2,0x80,0x13},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}},
	{ HOLDER_NAMEDISP,      "330000", ACTTRACEADD,
		"00", "02", "000", "0100", "0110", "0400",{0x60,0x24,0x06,0xc0,0x30,0xC0,0x80,0x13},
											{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00}}
};


ISO8583_FieldDef FieldLength_Table[64] = {
	{8, 8, ISO_8583_UNPACKED},			// 1 -- Bit Map, 
	{L_LLVAR, 19, ISO_8583_PACKED},		 
	{6, 6, ISO_8583_PACKED},			 
	{12, 12, ISO_8583_PACKED},			 
	{12, 12, ISO_8583_PACKED},			 
	{12, 12, ISO_8583_PACKED},			// 6 --  
	{5, 5, ISO_8583_PACKED},			// 7 -- Transmission Date And Time 
	{1, 1, ISO_8583_UNPACKED},			// 8 -- Amount, Cardholder Billing Fee 
	{8, 8, ISO_8583_PACKED},			// 9 -- Conversion Rate, Settlement 
	{8, 8, ISO_8583_PACKED},			// 10 -- Conversion Rate, Cardholder Billing 
	{6, 6, ISO_8583_PACKED},			// 11 -- System Trace Audit Number 
	{3, 3, ISO_8583_UNPACKED},			// 12 -- Time, Local Transaction 
	{2, 2, ISO_8583_UNPACKED},			// 13 -- Date, Local Transaction 
	{2, 2, ISO_8583_UNPACKED},			// 14 -- Date, Expiration 
	{4, 4, ISO_8583_PACKED},			// 15 -- Date, Settlement 
	{1, 1, ISO_8583_UNPACKED},			// 16 -- Date, Conversion 
	{4, 4, ISO_8583_PACKED},			// 17 -- Date, Capture 
	{6, 6, ISO_8583_PACKED},			// 18 -- Merchant's Type 
	{3, 3, ISO_8583_PACKED},			// 19 -- Acquiring Institution Country Code 
	{3, 3, ISO_8583_PACKED},			// 20 -- Primary Account Number Extended, CountryCode 
	{7, 7, ISO_8583_UNPACKED},			// 21 -- Forwarding Institution Country Code 
	{2, 2, ISO_8583_UNPACKED},			// 22 -- Point of Service Entry Mode 
	{2, 2, ISO_8583_UNPACKED},			// 23 -- Card Sequence Number 
	{2, 2, ISO_8583_UNPACKED},			// 24 -- Netword International Identifier 
	{2, 2, ISO_8583_PACKED},			// 25 -- Point of Service Condition Code 
	{2, 2, ISO_8583_PACKED},			// 26 -- Point of Service PIN Capture Code 
	{1, 1, ISO_8583_UNPACKED},			// 27 -- Authorization Identification Response Length 
	{1, 1, ISO_8583_UNPACKED},			// 28 -- Amount, Transaction Fee x+n8 
	{3, 3, ISO_8583_UNPACKED},			// 29 -- Amount, Settlement Fee x+n8 
	{9, 9, ISO_8583_UNPACKED},			// 30 -- Amount, Transaction Processing Fee x+n8 
	{9, 9, ISO_8583_UNPACKED},			// 31 -- Amount, Settlement Processing Fee x+n8 
	{L_LLVAR, 11, ISO_8583_PACKED},		// 32 -- Acquiring Institution Identification Code 
	{L_LLVAR, 11, ISO_8583_PACKED},		// 33 -- Forwarding Institution Identification Code 
	{L_LLVAR, 28, ISO_8583_PACKED},		// 34 -- Primary Account Number, Extended 
	{L_LLVAR, 37, ISO_8583_PACKED},		// 35 -- Track 2 Data 
	{L_LLLVAR, 104, ISO_8583_PACKED},	// 36 -- Track 3 Data 
	{12, 12, ISO_8583_UNPACKED},		// 37 -- Retrieval Reference Number 
	{6, 6, ISO_8583_UNPACKED},			// 38 -- Authorization Identification Response 
	{2, 2, ISO_8583_UNPACKED},			// 39 -- Response Code 
	{3, 3, ISO_8583_UNPACKED},			// 40 -- Service Restriction Code 
	{8, 8, ISO_8583_UNPACKED},			// 41 -- Card Acceptor Terminal Identification 
	{15, 15, ISO_8583_UNPACKED},		// 42 -- Card Acceptor Identification Code 
	{40, 40, ISO_8583_UNPACKED},		// 43 -- Card Acceptor Name/Location 
	{ L_LLVAR, 25, ISO_8583_UNPACKED},	// 44 -- Additional Response Data 
	{L_LLVAR, 76, ISO_8583_UNPACKED},	// 45 -- Track 1 Data 
	{L_LLLVAR, 999, ISO_8583_UNPACKED},	// 46 -- Additional Date - ISO 
	{L_LLLVAR, 999, ISO_8583_UNPACKED},	// 47 -- Additional Date - National 
	{L_LLLVAR, 999, ISO_8583_PACKED},	// 48 -- Additional Date - Private 
	{3, 3, ISO_8583_UNPACKED},			// 49 -- 货币 Code, Transaction 
	{L_LLLVAR, 999, ISO_8583_UNPACKED},			// 50 -- Currency Code, Settlement 
	{3, 3, ISO_8583_UNPACKED},			// 51 -- Currency Code, Cardholder Billing 
	{8, 8, ISO_8583_UNPACKED},			// 52 -- Personal Identification Number (PIN) Data 
	{16,16, ISO_8583_PACKED},			// 53 -- 
	{L_LLLVAR, 40, ISO_8583_UNPACKED},	// 54 -- Additional Amounts 
	{L_LLLVAR, 999, ISO_8583_UNPACKED},	// 55 -- Reserved ISO 
	{L_LLLVAR, 999, ISO_8583_UNPACKED},	// 56 -- Reserved ISO 
	{L_LLLVAR, 999, ISO_8583_UNPACKED},	// 57 -- Reserved National 
	{L_LLLVAR, 999, ISO_8583_UNPACKED},	// 58 -- Reserved National 
	{L_LLLVAR, 340, ISO_8583_UNPACKED},	// 59 -- Reserved National 
	{L_LLLVAR, 13, ISO_8583_PACKED},	// 60 -- Reserved Private 
	{L_LLLVAR, 29, ISO_8583_PACKED},	// 61 -- Reserved Private 
	{L_LLLVAR, 512, ISO_8583_UNPACKED},	// 62 -- Reserved Private 
	{L_LLLVAR, 80, ISO_8583_UNPACKED},	// 63 -- Reserved Private 
	{8, 8, ISO_8583_UNPACKED}			// 64 -- Message Authentication Code Field 
};
 
int CalMac(u8 *lpOut, u8 *lpIn, u16 len)
{
	u8 Buf[128], TmpBuf[128], MacData[1024];
	int i, l, k, MacDataLen, ret;
	char dispbuf[32];

	memset(Buf		, 0, sizeof(Buf));
	memset(TmpBuf	, 0, sizeof(TmpBuf));
	memset(MacData	, 0, sizeof(MacData));
	
	DisplayProcessing();

	memcpy(MacData, lpIn, len);
	MacDataLen = len + ( 8 - (len % 8 ) );

	l = MacDataLen / 8;
	for(i = 0; i < l; i++)
	{
		for (k = 0; k < 8; k++) 
		{
			Buf[k] = Buf[k] ^ MacData[i * 8 + k];
		}
	}
	
	BcdToAsc_Api((char*)TmpBuf, Buf, 16);
	memset(Buf, 0, sizeof(Buf));
	
	if(gCtrlParam.pinpad_type == PIN_PED)
	{
		ret = PEDMac_Api(gCtrlParam.MacKeyIndes, 0x01, TmpBuf, 8, Buf, 0x01);
		ret= 0;
		if(ret != 0)
		{
			GetPinpadError(ret, dispbuf);
			ErrorPrompt(dispbuf, 4);
			return 1;
		}
		
		for (k = 0; k < 8; k++)
			TmpBuf[k] = Buf[k] ^ TmpBuf[8 + k];
		
		memset(Buf, 0, sizeof(Buf));
		ret = PEDMac_Api(gCtrlParam.MacKeyIndes, 0x01, TmpBuf, 8, Buf, 0x01);
		ret = 0;
		if(ret != 0)
		{
			GetPinpadError(ret, dispbuf);
			ErrorPrompt(dispbuf, 4);
			return 2;
		}
	}
	else
	{
		ret = PPReadPinPadSn_Api(Buf);
		if(ret != 0)
			return -1;
		
		ret = PPMac_Api(gCtrlParam.MacKeyIndes, 0x01, TmpBuf, 8, Buf, 0x01);
		ret = 0;
		if(ret != 0)
		{
			GetPinpadError(ret, dispbuf);
			ErrorPrompt(dispbuf, 4);
			return 1;
		}
		
		for (k = 0; k < 8; k++) 
			TmpBuf[k] = Buf[k] ^ TmpBuf[8 + k];
		
		memset(Buf, 0, sizeof(Buf));
		ret = PPMac_Api(gCtrlParam.MacKeyIndes, 0x01, TmpBuf, 8, Buf, 0x01);
		ret = 0;
		if(ret != 0)
		{
			GetPinpadError(ret, dispbuf);
			ErrorPrompt(dispbuf, 4);
			return 2;
		}
	}

	BcdToAsc_Api((char*)TmpBuf, Buf, 16);
	memcpy(lpOut, TmpBuf, 8);
	return 0;
}
 
int Pack8583Packet(u8 *Packet, u8 Type)
{
	int iPackLen;
	char buf[32];

	memset(buf, 0, sizeof(buf));
	
	Init8583Packet(Packet);
	//TPDU
	memcpy(ucPacketPointer, G_CommPara.DialSet.Tpdu, 5); 
	ucPacketPointer += 5;
	iPacketLength += 5;
	// 
	sprintf(buf, "%s%s", BANK_MAINVER, BANK_BRANCHVER);
	AscToBcd_Api(ucPacketPointer, buf, 12);
	ucPacketPointer += 6;
	iPacketLength += 6;
	
	if(Type == 0)
	{
		memcpy(BitMap, PosCom.stTrnTbl.BitmapSend, 8);
		AscToBcd_Api((u8*)buf, PosCom.stTrnTbl.SendMsgId, 4);
	}
	else	// 
	{
		memcpy(BitMap, PosCom.stTrnTbl.BitmapSend, 8);//PosCom.stTrnTbl.BitmapReverse
		AscToBcd_Api((u8*)buf, PosCom.stTrnTbl.ReversedMsgId, 4);
	}
	memcpy(ucPacketPointer, buf, 2);
	ucPacketPointer += 2;
	iPacketLength +=  2;
	
	Pack8583PackDealBitmap(BitMap, Type);
	memcpy(PosCom.stTrans.bitmapsend, BitMap, 8);	// 
	memcpy(ucPacketPointer, BitMap, 8);
	ucPacketPointer += 8;
	iPacketLength += 8;
	
	iPackLen = Pack8583PacketData(Packet);
	return iPackLen;
}
 
int Pack8583PackDealBitmap(u8 *pBitmap, u8 ifreverse)
{
	// 
	if(PosCom.stTrans.Trans_id == SYS_SIGNUPLOAD)
	{
		if(strlen(PosCom.stTrans.SysReferNo) == 0)
			RemoveField(37, pBitmap);
		return 0;
	}
	// 
	if(ifreverse)
	{
		RemoveField(37, pBitmap);
		if(PosCom.stTrans.Trans_id != POINTS_WASHCAR)	// 
			AddField(39, pBitmap);
		// 
		RemoveField(35, pBitmap);
		RemoveField(47, pBitmap);
		RemoveField(62, pBitmap);
		RemoveField(63, pBitmap);
	}
	
	// 
	if(memcmp(PosCom.stTrans.AuthCode, "000000", 6) == 0)
	{
		RemoveField(38, pBitmap);
	}
	/*
	if(PosCom.stTrans.bPanSeqNoOk)
		AddField(23, pBitmap);
	else
		RemoveField(23, pBitmap);
		*/
	if(PosCom.stTrans.nIccDataLen == 0)					// 
	{
		RemoveField(55, pBitmap);
	}

	if (!PosCom.Track2Len)
	{
		RemoveField(35, pBitmap);
	}
	else
	{
		if(PosCom.stTrans.EntryMode[0] == PAN_MAGCARD)		// 
		{
			RemoveField(2, pBitmap);
		}
	}

	if( !PosCom.Track3Len )
	{
		RemoveField(36, pBitmap);
	}

	if (PosCom.stTrans.EntryMode[1] == PIN_NOT_INPUT)		// 
	{
		RemoveField(26, pBitmap);
		RemoveField(52, pBitmap);
		RemoveField(53, pBitmap);
	}
	
	// 
	if( (PosCom.stTrans.Trans_id == QPBOC_SALE)||
		(PosCom.stTrans.Trans_id == ECC_SALE)||
		(PosCom.stTrans.Trans_id == ECC_ERRORUP) )
		RemoveField(37, pBitmap);
	
	return 0;
}
 
int Pack8583PacketData(u8* Packet)
{
	u8 k, tag, BitNo;
	int iFieldLen, iPacketLen;
	char sFieldBuf[512];

	memset(sFieldBuf, 0, sizeof(sFieldBuf));

	iPacketLen = 0;
    for(k = 0; k < 64; k++) {
		BitNo = k + 1;
		tag = 0x01;
		tag  <<= (7 - (k % 8));
		
		if(!(BitMap[k / 8] & tag))
			continue;
		iFieldLen = 0;
		memset(sFieldBuf, 0, sizeof(sFieldBuf));

		switch(BitNo)
		{
		case 2:
			strcpy((char*)sFieldBuf, (char*)PosCom.stTrans.MainAcc);
			iFieldLen = strlen((char *)PosCom.stTrans.MainAcc);
			break;
		case 3:
			if(PosCom.stTrans.Trans_id == ICC_SCRSEND)// 
			{
				memcpy(sFieldBuf, PosCom.stTrans.OldTransCode, 6);
			}
			else 
			{
				memcpy(sFieldBuf, PosCom.stTrnTbl.TransCode, 6);
			}
			
			iFieldLen = 6;
			break;
		case 4:
			BcdToAsc_Api((char*)sFieldBuf, PosCom.stTrans.TradeAmount, 12);
			iFieldLen = 12;
			break;
		case 6:
			iFieldLen = 12;
			break;
		case 7:
			memcpy(sFieldBuf, &PosCom.stTrans.TradeDate[2], 2);				// 
			memcpy(&sFieldBuf[2], PosCom.stTrans.TradeTime, 3);				// 	
			iFieldLen = 5;
			break;
		case 8:
			strcpy((char *)sFieldBuf,"1");
			iFieldLen = 1;
			break;
		case 9:																//  
			sprintf((char *)sFieldBuf, "%08d", PosCom.stTrans.lNowBatchNum);
			iFieldLen = 8;
			break;
		case 11:
			sprintf((char *)sFieldBuf, "%06d", PosCom.stTrans.lTraceNo);
			iFieldLen = 6;
			break;
		case 12:
			memcpy(sFieldBuf, PosCom.stTrans.TradeTime, 3);
			iFieldLen = 3;
			break;
		case 13:
			memcpy(sFieldBuf, &PosCom.stTrans.TradeDate[2], 2);			//  YYYYMMDD(bcd)
			iFieldLen = 2;
			break;
		case 14:
			memcpy(sFieldBuf,PosCom.stTrans.ExpDate, 2);	
			iFieldLen = 2;
			break;
		case 15:															// 
			memcpy(sFieldBuf, PosCom.stTrans.OldTransDate, 8);
			iFieldLen = 8;
			break;
		case 16:
			sFieldBuf[0]= 0x31;
			iFieldLen = 1;	
			break;
		case 18:
			iFieldLen = 6;
			break;
		case 21:
			memcpy(sFieldBuf, gCtrlParam.Version, 7);
			iFieldLen = 7;
			break;
		case 22:															// 
			memcpy(sFieldBuf, PosCom.stTrans.EntryMode, 2);
			//sFieldBuf[3] = '0';
			iFieldLen = 2;
			break;
		case 23:
			sFieldBuf[0] = 0;
			sFieldBuf[1] = PosCom.stTrans.ucPanSeqNo;
			iFieldLen = 2;
			break;
		case 24:
			memcpy((char*)sFieldBuf, "0109", 4);
			iFieldLen = 4;
			break;
		case 25:
			memcpy((char*)sFieldBuf, PosCom.stTrnTbl.SevCode, 2);			// 
			iFieldLen = 2;
			break;
		case 26:
			strcpy((char *)sFieldBuf,"12");									// 
			iFieldLen = 2;
			break;
		case 28:
			sFieldBuf[0]= 0x00;												// 
			iFieldLen = 1;
			break;
		case 32:
			memcpy(sFieldBuf, "01000000", 8);
			iFieldLen = 8;
			break;
		case 35:															// 
			iFieldLen = strlen((char *) PosCom.Track2);
			if(iFieldLen > 37)
				iFieldLen = 37;
			memcpy(sFieldBuf, PosCom.Track2, iFieldLen);
			break;
		case 36:																	// 
			iFieldLen = strlen((char *) PosCom.Track3);
			memcpy(sFieldBuf, PosCom.Track3, iFieldLen);
			break;
		case 37:
			memcpy(sFieldBuf,PosCom.stTrans.SysReferNo, 12);
			iFieldLen = 12;
			break;
		case 38:
			memcpy(sFieldBuf, PosCom.stTrans.AuthCode, 6);
			iFieldLen = 6;
			break;
		case 39:
			memcpy(sFieldBuf, PosCom.stTrans.szRespCode, 2);
			iFieldLen = 2;
			break;
		case 40:																	// 
			strcpy((char*)sFieldBuf, (char*)PosCom.sField40_oldTerNum);
			iFieldLen = 3;
			break;
		case 41:
			memcpy(sFieldBuf, PosCom.stTrans.TerminalNo, 8);
			iFieldLen = 8;
			break;
		case 42:
			memcpy(sFieldBuf, PosCom.stTrans.MerchantNo,15);
			iFieldLen = 15;
			break;
		case 43:
			memcpy(sFieldBuf, gCtrlParam.MerchantName, 40);	//  
			iFieldLen = 40;
			break;
		case 47:
			iFieldLen = strlen(PosCom.sField47);
			memcpy(sFieldBuf, PosCom.sField47, iFieldLen);//PosCom.stTrans.MerchantNo
			break;
		case 48:
			strcpy((char*)sFieldBuf, (char*)PosCom.sField48);
			iFieldLen = strlen((char*)PosCom.sField48);
			break;
		case 49:
			strcpy((char*)sFieldBuf, "156");
			iFieldLen = 3;
			break;
		case 50:
			//if(PosCom.stTrans.Trans_id == SYS_SIGNUPLOAD)
			//{
				memcpy(sFieldBuf, PosCom.sSign50, PosCom.iSign50Len);
				iFieldLen = PosCom.iSign50Len;
			//}
			break;
		case 52:
			memcpy(sFieldBuf, PosCom.sPIN, 8);
			iFieldLen = 8;
			break;
		case 53:
			if(gCtrlParam.DesType == 1)
				strcpy(sFieldBuf,"2000000000000000");
			else
				strcpy(sFieldBuf,"2600000000000000");
			iFieldLen = 16;
			break;
		case 54:
			strcpy(sFieldBuf, PosCom.sField54);
			iFieldLen = strlen(PosCom.sField54);
			break;
		case 55:
			if(PosCom.stTrans.nIccDataLen)
			{
				memcpy(sFieldBuf, PosCom.stTrans.IccData, PosCom.stTrans.nIccDataLen);
				iFieldLen = PosCom.stTrans.nIccDataLen;
			}
			else
			{
				iFieldLen = 0;
			}
			break;
		case 56:
			break;
		case 57:
			break;
		case 58:
			strcpy((char *)sFieldBuf, "F-POSC 3.G.2.4");
			iFieldLen = strlen((char *)sFieldBuf);
			break;
		case 59:
			break;
		case 60:
			iFieldLen = 11;
			//60. 
			memcpy(sFieldBuf, PosCom.stTrnTbl.MessCode, 2);
			//60. 
			sprintf((char *)sFieldBuf + 2, "%06d", PosCom.stTrans.lNowBatchNum);
			//60. 
			if(PosCom.stTrans.Trans_id == POS_LOGON)
			{
				if (gCtrlParam.DesType == 0)
					memcpy(sFieldBuf+8,"003",3);
				else
					memcpy(sFieldBuf+8,"001",3);
			}
			else
			{
				/*
				if( (PosCom.stTrans.Trans_id == ICC_SCRSEND)
				||(PosCom.stTrans.Trans_id == POS_LOGOFF)
				||(PosCom.stTrans.Trans_id == POS_SETTLE)
				||(PosCom.stTrans.Trans_id == POS_BATCHUP)
				||(PosCom.stTrans.Trans_id == ICC_BATCHUP_TC)
				||(PosCom.stTrans.Trans_id == POSPARAM_DOWN)
				||(PosCom.stTrans.Trans_id == EMVPARAM_QUERYIDX)
				||(PosCom.stTrans.Trans_id == EMVPARAM_DOWN)
				||(PosCom.stTrans.Trans_id == EMVPARAM_END)
				||(PosCom.stTrans.Trans_id == EMVCAPK_QUERYIDX)
				||(PosCom.stTrans.Trans_id == EMVCAPK_DOWN)
				||(PosCom.stTrans.Trans_id == EMVCAPK_END) )
				*/
				if( memcmp(PosCom.stTrnTbl.SendMsgId, "03", 2) == 0
					||memcmp(PosCom.stTrnTbl.SendMsgId, "05", 2) == 0
					||memcmp(PosCom.stTrnTbl.SendMsgId, "06", 2) == 0
					||memcmp(PosCom.stTrnTbl.SendMsgId, "08", 2) == 0 )
				{
					memcpy(sFieldBuf+8, PosCom.stTrnTbl.NetInfoCode, 3);	// 
				}
				else
				{
					//memcpy(sFieldBuf+8, "031", 3);	 
					memcpy(sFieldBuf+8, "000", 3);	 
				}
			 
				switch(PosCom.stTrans.EntryMode[0])
				{
					case PAN_MAGCARD:
						sFieldBuf[11] = 0x32;
						break;
					case PAN_ICCARD:
						sFieldBuf[11] = 0x35;
						break;
					case PAN_PICCQUICK:
					case PAN_PICCFULL:
					case PAN_PICCMSD:
						sFieldBuf[11] = 0x36;
						break;
					default:
						sFieldBuf[11] = 0x30;
						break;
				}
			 
				if(PosCom.stTrans.IccFallBack == 0)
					sFieldBuf[12] = 0x30;
				else
				{
					sFieldBuf[11] = 0x35;	 
					sFieldBuf[12] = 0x32;	 
				}
				iFieldLen = 13;
			}
			break;
		case 61:
			sprintf(sFieldBuf, "%06d%06d", PosCom.stTrans.OldBatchNum, PosCom.stTrans.OldTraceNo);
			if(strlen(PosCom.stTrans.OldTermNo))
				strcat(sFieldBuf, PosCom.stTrans.OldTermNo);
			else
				strcat(sFieldBuf, PosCom.stTrans.OldTransDate+4);
			
			iFieldLen = strlen((char*)sFieldBuf);
			break;
		case 62:
			iFieldLen = PackCupBlock62((u8*)sFieldBuf);
			break;
		case 63:
			if( PosCom.stTrans.Trans_id == POS_LOGON || PosCom.stTrans.Trans_id == POS_SETTLE ||
				PosCom.stTrans.Trans_id == TMS_QUERY )
			{
				sprintf(sFieldBuf, "%03d", gtOperator.nCurOptNO);
				memcpy(sFieldBuf+3, TMSCCB_FACTORY_ID, 2);
				memcpy(sFieldBuf+5, TMSCCB_MACHINE_ID, 2);
				iFieldLen = 7;
				memset(&sFieldBuf[iFieldLen], 0, 32);
				memcpy(&sFieldBuf[iFieldLen], "0000", 4);
				memcpy(&sFieldBuf[iFieldLen+4], TMSCCB_FACTORY_ID, 2);
				memcpy(&sFieldBuf[iFieldLen+6], TMSCCB_MACHINE_ID, 2);
				memcpy(&sFieldBuf[iFieldLen+8], APPVERSION+7, 6);
				iFieldLen = 32+7;
				sFieldBuf[iFieldLen] = gCtrlParam.TerminalType+0x30;
				// 
				PEDReadPinPadSn_Api((u8*)&sFieldBuf[40]);
				tag = (u8)AscToLong_Api((u8*)&sFieldBuf[40], 2);
				memcpy(&sFieldBuf[40], &sFieldBuf[42], tag);
				memset(sFieldBuf+40+tag, ' ', 30-tag);
				iFieldLen = 70;
			}
			else
			{
				strcpy(sFieldBuf, "000");
				iFieldLen = 3;
			}
			break;
		case 64:
			if(CalMac((u8*)sFieldBuf, &Packet[11], (u16)(iPacketLen - 11) ) != 0 )
				return -2;													 
			iFieldLen = 8;
			break;
		default:
			return (-1);
			break;
		}          /* end switch */
		// 
		iPacketLen = Setting8583PrimaryField(BitNo, (u8*)sFieldBuf, iFieldLen);
		if(iPacketLen == -1)
		{
			return -1;
		}
    }
    return(iPacketLen);
}
 
void DispRenewKeyResult(int ret)
{
	char DisBuf[30];

	memset(DisBuf, 0, sizeof(DisBuf));

	switch(ret) 
	{
		case 0:
			return;
			break;
		case -1:
			strcpy(DisBuf,"write PinKey failed");
			break;
		case -2:
			strcpy(DisBuf,"CAL Pinkey failed");
			break;
		case -3:
			strcpy(DisBuf,"Pinkey error");
			break;
		case -4:
			strcpy(DisBuf,"write MacKey failed");
			break;
		case -5:
			strcpy(DisBuf,"CAL MacKey value failed");
			break;
		case -6:
			strcpy(DisBuf,"MacKey check failed");
			break;
		case -7:
			strcpy(DisBuf,"write EncKey failed");
			break;
		case -8:
			strcpy(DisBuf,"CAL EncKey value failed");
			break;
		case -9:
			strcpy(DisBuf,"EncKey check failed");
			break;
		case -20:
			strcpy(DisBuf,"receive key failed");
			break;
		case -21:
			strcpy(DisBuf,"write Pinkey failed");
			break;
		case -22:
			strcpy(DisBuf,"write Mackey failed");
			break;
		case -23:
			strcpy(DisBuf,"write EncKey failed");
			break;
		default:
			break;
	}
	ScrDisp_Api(LINE5, 0,DisBuf, CDISP);
	WaitEnterAndEscKey_Api(2);
}
 
int PPWriteCUPKey(unsigned char *Inbuf, u16 len)
{
	u8 PinKey[21], MacKey[21], EncKey[21], MacZero[9], MacOut[9], TestKeyId;

	memset(PinKey, 0, sizeof(PinKey));
	memset(MacKey, 0, sizeof(MacKey));
	memset(MacZero, 0, sizeof(MacZero));
	memset(MacOut, 0, sizeof(MacOut));

	TestKeyId = 5;
	if (gCtrlParam.DesType == 0)
	{
		memcpy(PinKey, Inbuf+0, 20);
		memcpy(MacKey, Inbuf+20, 20);

		if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId,0x83, PinKey) != 0x00 )
			return -1;
		if(PPMac_Api(TestKeyId, 0x03, MacZero, 8, MacOut, 0x01 ) != 0x00 )
			return -2;
		if(memcmp(MacOut, PinKey + 16, 4) != 0x00 )
			return -3;
		if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.PinKeyIndes, 0x83, PinKey) != 0x00)
			return -21;

		if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId, 0x13, MacKey) != 0x00 )
			return -4;
		if(PPMac_Api(TestKeyId, 0x01, MacZero, 8, MacOut, 0x01 ) != 0x00 )
			return -5;
		if(memcmp(MacOut, MacKey + 16, 4) != 0x00 )
			return -6;
		if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.MacKeyIndes, 0x13, MacKey) != 0x00)
			return -22;

		if(gCtrlParam.IfEncTotalBag)
		{
			memcpy(EncKey, Inbuf+40, 20);
			if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId, 0x83, EncKey) != 0x00)
				return -7;
			if(PPMac_Api(TestKeyId, 0x03, MacZero, 8, MacOut, 0x01) != 0x00)
				return -8;
			if(memcmp(MacOut, EncKey + 16, 4) != 0x00)
				return -9;
			if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.EncKeyIndes, 0x83, EncKey) != 0x00)
				return -23;
		}
	}
	else
	{
		memcpy(PinKey, Inbuf+0, 12);
		memcpy(MacKey, Inbuf+12, 12);
		
		if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId,0x81, PinKey) != 0x00 )
			return -1;
		if(PPMac_Api(TestKeyId, 0x01, MacZero, 8, MacOut, 0x01 ) != 0x00 )
			return -2;
		if(memcmp(MacOut, PinKey + 8, 4) != 0x00 )
			return -3;
		if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.PinKeyIndes, 0x81, PinKey) != 0x00)
			return -21;
		
		if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId,0x13, MacKey) != 0x00 )
			return -4;
		if(PPMac_Api(TestKeyId, 0x01, MacZero, 8, MacOut, 0x01 ) != 0x00 )
			return -5;
		if(memcmp(MacOut, MacKey + 8, 4) != 0x00 )
			return -6;
		if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.MacKeyIndes, 0x81, MacKey) != 0x00)
			return -22;
		
		if(gCtrlParam.IfEncTotalBag)
		{
			memcpy(EncKey, Inbuf+24, 12);
			if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId, 0x81, EncKey) != 0x00)
				return -7;
			if(PPMac_Api(TestKeyId, 0x01, MacZero, 8, MacOut, 0x01) != 0x00)
				return -8;
			if(memcmp(MacOut, EncKey + 8, 4) != 0x00)
				return -9;
			if(PPWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.EncKeyIndes, 0x81, EncKey) != 0x00)
				return -23;
		}
	}
	return 0;
}
 
int PEDWriteCUPKey(unsigned char *Inbuf, u16 len)
{
	u8 TestKeyId, PinKey[21], MacKey[21], EncKey[21], MacZero[9], MacOut[9];

	memset(PinKey, 0, sizeof(PinKey));
	memset(MacKey, 0, sizeof(MacKey));
	memset(MacZero, 0, sizeof(MacZero));
	memset(MacOut, 0, sizeof(MacOut));

	TestKeyId = 5;
	if(gCtrlParam.DesType == 0)
	{
		memcpy(PinKey, Inbuf+0, 20);
		memcpy(MacKey, Inbuf+20, 20);
		
		if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId, 0x83, PinKey) != 0x00)
			return -1;
		if(PEDMac_Api(TestKeyId, 0x03, MacZero, 8, MacOut, 0x01 ) != 0x00)
			return -2;
		if(memcmp(MacOut, PinKey + 16, 4) != 0x00 )
			return -3;
		if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.PinKeyIndes, 0x83, PinKey) != 0x00)
			return -21;

		if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId, 0x13, MacKey) != 0x00)
			return -4;
		if(PEDMac_Api(TestKeyId, 0x01, MacZero, 8, MacOut, 0x01 ) != 0x00)
			return -5;
		if(memcmp(MacOut, MacKey + 16, 4) != 0x00 )
			return -6;
		if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.MacKeyIndes, 0x13, MacKey) != 0x00)
			return -22;
		if(gCtrlParam.IfEncTotalBag)
		{
			memcpy(EncKey, Inbuf+40, 20);
			if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId, 0x83, EncKey) != 0x00)
				return -7;
			if(PEDMac_Api(TestKeyId, 0x03, MacZero, 8, MacOut, 0x01) != 0x00)
				return -8;
			if(memcmp(MacOut, EncKey + 16, 4) != 0x00)
				return -9;
			if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.EncKeyIndes, 0x83, EncKey) != 0x00)
				return -23;
		}
		
	}
	else
	{
		memcpy(PinKey, Inbuf+0, 12);
		memcpy(MacKey, Inbuf+12, 12);
		
		if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId,0x81, PinKey) != 0x00)
			return -1;
		if(PEDMac_Api(TestKeyId, 0x01, MacZero, 8, MacOut, 0x01) != 0x00)
			return -2;
		if(memcmp(MacOut, PinKey + 8, 4) != 0x00)
			return -3;
		if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.PinKeyIndes, 0x81, PinKey) != 0x00)
			return -21;
		
		if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId, 0x81, MacKey) != 0x00)
			return -4;
		if(PEDMac_Api(TestKeyId, 0x01, MacZero, 8, MacOut, 0x01) != 0x00)
			return -5;
		if(memcmp(MacOut, MacKey + 8, 4) != 0x00)
			return -6;
		if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.MacKeyIndes, 0x81, MacKey) != 0x00)
			return -22;
		
		if(gCtrlParam.IfEncTotalBag)
		{
			memcpy(EncKey, Inbuf+24, 12);
			if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, TestKeyId, 0x81, EncKey) != 0x00)
				return -7;
			if(PEDMac_Api(TestKeyId, 0x01, MacZero, 8, MacOut, 0x01) != 0x00)
				return -8;
			if(memcmp(MacOut, EncKey + 8, 4) != 0x00)
				return -9;
			if(PEDWriteWKey_Api(gCtrlParam.MainKeyIdx, gCtrlParam.EncKeyIndes, 0x81, EncKey) != 0x00)
				return -23;
		}
		
	}
	return 0;
}
 
int Parse8583PacketData(u8 Bitno, u8 *buf, int len, u8 *packet, u16 PackLen)
{
	u8 MacBuf[9];
	char TemBuf[32];
	int ret;

	memset(MacBuf, 0, sizeof(MacBuf));
	memset(TemBuf, 0, sizeof(TemBuf));

	switch(Bitno)
	{
	case 2:																								//   
		if(len > 19)
			return (-1);
		memcpy(PosCom.stTrans.MainAcc, buf, len);
		PosCom.stTrans.MainAcc[len] = 0;
		break;
	case 3:
		AscToBcd_Api(PosCom.stTrans.ResProcCode, (char*)buf, len);
		break;
	case 4:
		AscToBcd_Api(PosCom.stTrans.TradeAmount, (char*)buf, 12);// 
		break;
	case 8:
		break;
	case 9:																							 
		if((PosCom.stTrans.Trans_id == POS_LOGON) || (PosCom.stTrans.Trans_id == POS_SETTLE))		 
		{
			gCtrlParam.lNowBatchNum = AscToLong_Api(buf + 2, (u8)strlen((char*)&buf[2]) );
			SaveCtrlParam();
		}                                                                             
		break;                                                                        
	case 11:																		 
		if( PosCom.stTrans.lTraceNo != AscToLong_Api(buf, (u8)strlen((char*)buf) ) ) 
			sucBackTradeNOFlag = 1;                                                   
		break;                                                                        
	case 12:																		 
		memcpy(PosCom.stTrans.TradeTime, buf, 3);                                     
		break;                                                                        
	case 13:																		 
		memcpy(&PosCom.stTrans.TradeDate[2], buf, 2);		                          
		break;                                                                        
	case 14:
		memcpy(PosCom.stTrans.ExpDate, buf, 2);
		break;
	case 15:
		break;
	case 18:
		break;
	case 21:
		break;
	case 28:
		PosCom.stTrans.DesAndFrCardFlag_28 = buf[0];
		break;
	case 32:
		buf[8] = 0;
		strcpy((char *)PosCom.stTrans.CenterId, (char *)buf);
		break;
	case 35:
		//memcpy(sFile35TempBuf,buf, 12);															
		break;
	case 36:
		break;                                                                             
	case 37:																				 
		memcpy(PosCom.stTrans.SysReferNo, buf, 12);                                        
		PosCom.stTrans.SysReferNo[12] = 0;                                                 
		break;                                                                             
	case 38:																				 
		memcpy(PosCom.stTrans.AuthCode, buf, 6);                                           
		PosCom.stTrans.AuthCode[6] = 0;                                                    
		break;                                                                             
	case 39:																				 
		memcpy(PosCom.stTrans.szRespCode, buf, 2);                                         
		PosCom.stTrans.szRespCode[2] = 0;
		if(memcmp(PosCom.stTrans.szRespCode, "00", 2) == 0)	 
		{                                                    
			if(sucBackTradeNOFlag != 0) 
			{
				if((PosCom.stTrans.Trans_id != POS_LOGON) &&
					(PosCom.stTrans.Trans_id != EMVPARAM_DOWN))
				{	 
					ErrorPrompt("trace NO. not match",2);
					return (-1);
				}
			}
		}
		break;
	case 41:																							 
		if ( (memcmp(buf, PosCom.stTrans.TerminalNo, 8) != 0 ) && (strlen(PosCom.stTrans.TerminalNo) != 0) )
		{
 			ErrorPrompt("terminal NO. not match",2);
 			return (-1);
		}
		break;
	case 42:																							 
		if ( memcmp(buf, PosCom.stTrans.MerchantNo, 15) != 0 )
		{
			ErrorPrompt("merchant NO. not math",2);
			return (-1);
		}
		break;
	case 43:
		break;
	case 44:
		memcpy(PosCom.stTrans.szIssuerBankId, buf, 8);
		PosCom.stTrans.szIssuerBankId[8] = 0;
		if(len > 11)
		{
			memcpy(PosCom.stTrans.MerchTermNO, buf+11, 4);
			PosCom.stTrans.MerchTermNO[4] = 0;
		}
		break;
	case 48:
		if (PosCom.stTrans.Trans_id == POS_SETTLE) 
		{
			PosCom.ucRmbSettRsp = buf[30];
			PosCom.ucFrnSettRsp = buf[61];
		}
		memset(PosCom.sField48, 0, sizeof(PosCom.sField48));
		memcpy(PosCom.sField48, buf, len);
		break;
	case 49:
		break;
	case 50:
		break;
	case 52:
		break;
	case 53:
		break;
	case 54:
		memcpy(PosCom.stTrans.AddInfo, buf, len);	 
		break;
	case 55:
		//memcpy(PosCom.stTrans.IccData, buf, len);
		//PosCom.stTrans.nIccDataLen = len;
		memcpy(PosCom.RespIccData, buf, len);		 
		PosCom.nRespIccLen = len;
		break;
	case 56:
		break;
	case 57:
		break;
	case 58:																							   
		memset(PosCom.sField58, 0, sizeof(PosCom.sField58));
		memcpy(PosCom.sField58, buf, len);
		PosCom.iField58Len = len;
		memcpy(PosCom.stTrans.cardType, buf, 16);														 
		break;
	case 59:
		break;
	case 60:
		memset(TemBuf, 0, sizeof(TemBuf));
		memcpy(TemBuf, buf+2, 6);
		TemBuf[6] = 0;
		PosCom.stTrans.lNowBatchNum = AscToLong_Api((u8*)TemBuf, (u8)strlen(TemBuf) );
		
		// 
		if (PosCom.stTrans.Trans_id == POS_LOGON && (memcmp(PosCom.stTrans.szRespCode,"00",2) == 0))
		{
			gCtrlParam.lNowBatchNum = AscToLong_Api((u8*)TemBuf, (u8)strlen(TemBuf) );
			SaveCtrlParam();
		}
		break;
	case 61:
		break;
	case 62:
		ret = ParseCupBlock62(buf, (u16)len);
		if(ret < 0) return -3;
		break;
	case 63:
		if (PosCom.stTrans.Trans_id == POS_SETTLE || PosCom.stTrans.Trans_id == POS_LOGON || PosCom.stTrans.Trans_id == TMS_QUERY)
		{
			memcpy(gCtrlParam.TerminalTmsVer, buf+3, 36);	
			gCtrlParam.TerminalTmsVer[36] = 0;
			ret = 36;
			// 
			ret += 3;
			gCtrlParam.DownFlag = buf[ret+1]-0x30;
			ret += 2;
			//
			if(ret < len)
			{
				memcpy(gCtrlParam.DownTime, buf+ret, 28);		// 
				gCtrlParam.DownTime[28] = 0;
				ret += 28;
				memcpy(gCtrlParam.VirtualTermNo, buf+ret, 11);	// 
				gCtrlParam.VirtualTermNo[11] = 0;
				ret += 11;
				/* 
				if(ret < len)
				{
					gCtrlParam.TerminalType = buf[ret]-0x30;		// 
					ret += 1;
					
					memcpy(gCtrlParam.DownTermSerial, buf+ret, 30);	// 
				}
				*/
			}
			SaveCtrlParam();
		}
		else
		{
			memcpy(PosCom.stTrans.szCardUnit, buf, 3);// 
			PosCom.stTrans.szCardUnit[3] = 0;
			// 
			PosCom.stTrans.nBlock632Len = len-3;
			memcpy(PosCom.stTrans.szBlock632, buf+3, PosCom.stTrans.nBlock632Len);
			/*
			if(len > 3)
			{
				if(len >= 23)
				{
					memcpy(PosCom.stTrans.szIssuerResp, buf + 3, 20); 
					PosCom.stTrans.szIssuerResp[20] = 0;
				}
				if(len >= 43)
				{
					memcpy(PosCom.stTrans.szCenterResp, buf + 23, 20);
					PosCom.stTrans.szCenterResp[20] = 0;
				}
				if(len >= 63)
				{
					memcpy(PosCom.stTrans.szRecvBankResp, buf + 43, 20);
					PosCom.stTrans.szRecvBankResp[20] = 0;
				}
			}
			*/
		}
		break;
	case 64:
// 		for(i = 11; i < PackLen; i++)
// 		{
// 			if(memcmp(&packet[i], buf, 8) == 0) break;
// 		}
// 		if(CalMac(MacBuf, &packet[11], (u16)(i-11) )!= 0)									 
// 		{                                                                                    
// 			//ErrorPrompt("计算校验错误",2);                                                 
// 			return -1;                                                                       
// 		}                                                                                    
// 	                                                                                         
// 		if(memcmp(MacBuf, buf, 8) != 0 )                                                     
// 		{                                                                                    
// 		    ErrorPrompt("MAC校验不符",2);                                                    
// 			return (-2);																	 
// 		}                                                                                    
		break;                                                                               
	default:
		break;
     }
     return(0);
}
 
int ResolveHostPacket(u8 *Packet, u16 PacketLen)
{
	u8 BitNo;
	int nRet, len;
	u8 buf[1024];

	memset(buf, 0, sizeof(buf));
	
	Init8583Packet(Packet);
	if(Get8583MsgID() != 0)
		return(-1);

	sucBackTradeNOFlag = 0;	// 
	BitNo = 0;
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		len = Get8583Field(&BitNo, buf);
		
		if(len == -1) return(-1);
		if(len == -2) return 0;
		if(len == 0) continue;
		nRet = Parse8583PacketData(BitNo, buf, len, Packet, PacketLen);
		if(nRet != 0)
			return nRet;
	}
}
 
int Init8583Packet(u8 *Packet)
{
    ucPacketPointer = Packet;
    iPacketLength = 0;
	giRespCmd = 0;		// 
	return(0);
}
 
int Setting8583PrimaryField(int BitNo, u8 * Field, int FieldLength)
{
	ISO8583_FieldDef Iso8583Fdef;

	memset(&Iso8583Fdef, 0, sizeof(Iso8583Fdef));
	
	memcpy(&Iso8583Fdef,&FieldLength_Table[BitNo - 1],sizeof(ISO8583_FieldDef));
	
	if ( Iso8583Fdef.length == L_LLVAR) {
		if ( Iso8583Fdef.maxlength < FieldLength) {
            		return(-1);
		}
		LongToBcd_Api(ucPacketPointer, FieldLength, 1);
		ucPacketPointer += 1;
		iPacketLength += 1;
	}
    else if (Iso8583Fdef.length == L_LLLVAR) {
		if ( Iso8583Fdef.maxlength < FieldLength) {
			return(-1);
		}
		
		LongToBcd_Api(ucPacketPointer, FieldLength, 2);
		
		ucPacketPointer += 2;
		iPacketLength += 2;
	}
	else {
		if(Iso8583Fdef.length != FieldLength) {
			return(-1);
		}
	}
	
	if(Iso8583Fdef.packed) {
		AscToBcd_Api(ucPacketPointer, ( char *)Field, FieldLength); 
		ucPacketPointer += (FieldLength + 1 ) / 2;
		iPacketLength += (FieldLength + 1 ) / 2;
	}
	else {
		memcpy(ucPacketPointer, Field, FieldLength);
		ucPacketPointer += FieldLength;
		iPacketLength += FieldLength;
    }
	
	return(iPacketLength);
}
 
int Get8583MsgID(void)
{
	int len;
	u8 buf[10],buf1[5];
	
	memset(buf, 0, sizeof(buf));
	memset(buf1, 0, sizeof(buf1));
                                                 
	ucPacketPointer += 5;						 
	giRespCmd = ucPacketPointer[2]&0x0f;		 
	ucPacketPointer += 6;						 
	                                             
	BcdToAsc_Api((char *)buf1,ucPacketPointer,4);
	buf1[4] = 0;
	memcpy(buf,PosCom.stTrnTbl.SendMsgId,4);
	buf[4] = 0;
	ucPacketPointer += 2;
	
	memset(BitMap, '\0', 8); 
	len = 8;
	memcpy(BitMap, ucPacketPointer, len);							//	The Primary Bit Map 
	ucPacketPointer += len;

	return 0;
}
 
int Get8583Field(u8 *BitNo, u8 *Field)
{
	u8 Buf[4], Tmp[8], i, tag;
	int length;
	ISO8583_FieldDef Iso8583Fdef;
	
	memset(Buf, 0, sizeof(Buf));
	memset(Tmp, 0, sizeof(Tmp));
	memset(&Iso8583Fdef, 0, sizeof(Iso8583Fdef));

	for(i = *BitNo; i < 64; i++)
	{
		if(i == 0)
			continue;
		
		tag = 0x01;
		tag <<= (7 - (i % 8));
		if(BitMap[i/8] & tag)
		{
			memcpy(&Iso8583Fdef, &FieldLength_Table[i], sizeof(ISO8583_FieldDef));
			
			if(Iso8583Fdef.length == L_LLVAR)
			{
				memcpy(Buf, ucPacketPointer, 1);
				Buf[1] = '\0';
				ucPacketPointer += 1;
				BcdToAsc_Api((char *)Tmp, Buf, 2);
				Tmp[2] = 0;
				length = AscToLong_Api(Tmp, (u8)strlen((char*)Tmp) );
				if(Iso8583Fdef.maxlength < length)
				{
					return (-1);
				}
			}
			else if (Iso8583Fdef.length == L_LLLVAR)
			{
				memcpy(Buf, ucPacketPointer, 2);
				Buf[2] = '\0';
				ucPacketPointer += 2;
				//length = BCD2Long(buf, 2);
				BcdToAsc_Api((char *)Tmp, Buf, 4);
				Tmp[4] = 0;
				length = AscToLong_Api(Tmp, (u8)strlen((char*)Tmp) );
				if(Iso8583Fdef.maxlength < length)
				{
					return (-1);
				}
			}
			else
			{
				length = Iso8583Fdef.length;
			}
			
			if (Iso8583Fdef.packed)
			{
				BcdToAsc_Api((char *)Field, ucPacketPointer, length);
				Field[length] = '\0';
				ucPacketPointer += (length + 1) / 2;
			}
			else
			{
				memcpy(Field, ucPacketPointer, length);
				Field[length] = '\0';
				ucPacketPointer += length;
			}
			break;
		}
	}
	
	*BitNo = i + 1;
	if (i < 64)
		return (length);
	else
		return (-2);
}
 
int GetTradeTable(POS8583PACKET_STRC *ptPackTable, int Txn)
{
	u8 i;

	for(i = 0; i < TRACE_NUM; i++)
	{
		if(Txn == TrTable[i].iTransNo)
		{
			memcpy((u8*)ptPackTable, &TrTable[i], TRANS8583_STRC_LEN);
			return i;
		}
	}
	ErrorPrompt("get trade table failed!",1);
	return 0xff;
}
 
int PackCupBlock62(u8* psFieldBuf)
{
	u8 ucType;
	u16 nLen;
	char sTemp[32];

	memset(sTemp, 0, sizeof(sTemp));

	switch(PosCom.stTrans.Trans_id)
	{
		case POS_QUE: 
			/*
			psFieldBuf[0] = 0;							 
	        psFieldBuf[1] = 0x22;						 
	        psFieldBuf[2] = 0x30;
	        psFieldBuf[3] = 0x31 + CardInfo.CardHoldIdType;  
	        memset(&psFieldBuf[4], 0x20, 20);				 
	        i = CardInfo.CardHoldIdLen;
	        if(i > 20 ) i = 20;
	        memcpy(&psFieldBuf[4], CardInfo.CardHoldIdNo, i);  
	        */
	        break;
		case POS_SALE:
			/*
			if(gInstalmentTrade) 
			{
	    		psFieldBuf[0] = 0;							 
	            psFieldBuf[1] = 0x62;
	            memcpy(&psFieldBuf[2], PayTimes, 2);   
	            memset(&psFieldBuf[4], 0x20, 30);
	            i = strlen(MerchandiseCode);
	            if(i > 30)i = 30;
	            memcpy(&psFieldBuf[4], MerchandiseCode, i);// 
	    		memset(&psFieldBuf[34], 0x20, 30); // 
	    	}
	    	else  //    
	    	{                                                    
	    		psFieldBuf[0] = 0;							 
	            psFieldBuf[1] = 0x22;						 
	            psFieldBuf[2] = 0x30;                        
	            psFieldBuf[3] = 0x31 + CardInfo.CardHoldIdType;  
	            memset(&psFieldBuf[4], 0x20, 20);				 
	            i = CardInfo.CardHoldIdLen;
	            if(i > 20 ) i = 20;
	            memcpy(&psFieldBuf[4], CardInfo.CardHoldIdNo, i); // 
	    	}
	        */
	        break;
		case EMVCAPK_QUERYIDX:
	        psFieldBuf[0] = '1';
	        sprintf((char*)&psFieldBuf[1], "%02d", gCtrlParam.EmvDownFlag[1]);
			nLen = 3;
	        break;
		case EMVCAPK_DOWN:
			memcpy(&psFieldBuf[0], gsEmvCapkIdx[gCtrlParam.EmvDownFlag[1]-1].RidFlag, 12);
			nLen = 12;
	        break;
			//
		case EMVPARAM_QUERYIDX:
	        psFieldBuf[0] = '1';
	        sprintf((char*)&psFieldBuf[1], "%02d", gCtrlParam.EmvDownFlag[2]);
			nLen = 3;
	        break;
		case EMVPARAM_DOWN:
			nLen = gsEmvParamIdx[gCtrlParam.EmvDownFlag[2]-1].AidLen+3;	// 
        	memcpy(psFieldBuf, gsEmvParamIdx[gCtrlParam.EmvDownFlag[2]-1].AidFlag, nLen);		//Tag
	        break;
		case TRANSFER_CARDTOCARD:		 
		case TRANSFER_CARDOUT:			 
		case TRANSFER_REIMBURSED:		 
		case TRANSFER_REPAYMENT:		 
			nLen = strlen(PosCom.stTrans.SecondAcc);
			sprintf((char*)psFieldBuf, "%02d%s", nLen, PosCom.stTrans.SecondAcc);
			nLen = nLen+2;
			break;
		case RBPOINT_CONSUME:		// 
			BcdToAsc_Api(sTemp, PosCom.stTrans.TradeAmount, 12);
			memset(psFieldBuf, 0x20, 32);
			memcpy(psFieldBuf, &sTemp[10], 2);		// 
			nLen = 32;
			break;
		case POINTSCASH_SALE:	// 
		case POINTSCASH_SALEVOID:
			strcpy((char*)psFieldBuf, PosCom.stTrans.AddInfo);
			nLen = 12;
			break;
		case ICC_BATCHUP_TC:	// 
			strcpy((char*)psFieldBuf, "61");
			
			ucType = PosCom.stTrans.ResProcCode[2];
			if((ucType==90)||(ucType==91)||(ucType==92)||(ucType==93)||(ucType==94))//外卡
				strcat((char*)psFieldBuf, "01");
			else
				strcat((char*)psFieldBuf, "00");
			strcat((char*)psFieldBuf, PosCom.stTrans.szRespCode);
			memset(sTemp, 0, sizeof(sTemp));
			BcdToAsc_Api(sTemp, PosCom.stTrans.TradeAmount, 12);
			strcat((char*)psFieldBuf, sTemp);
			strcat((char*)psFieldBuf, "156");
			nLen = strlen((char*)psFieldBuf);
			break;
		case POS_INST:			 
		case POS_INSTREFUND:	 
			strcpy((char*)psFieldBuf, (char*)PosCom.sField62);
			nLen = strlen((char*)psFieldBuf);
			break;
		//case ACCOUNT_VERIFY:			// 
		//	strcpy((char*)psFieldBuf, "61");
		//	break;
		case SYS_SIGNUPLOAD:	// 
			strcpy((char*)psFieldBuf, "0101000");
			nLen = strlen((char*)psFieldBuf);
			break;
		default:
			break;
	}
	return nLen;
}
 
u8 *FindMemFromMem(u8 *pSrc, u16 nSrcLen, u8 *pFind, u16 nFindLen)
{
	u16 i;
	
	if(nSrcLen < nFindLen)
	{
		return NULL;
	}
	for(i = 0; i < nSrcLen-nFindLen; i++)
	{
		if(memcmp(&pSrc[i], pFind, nFindLen) == 0)
		{
			return &pSrc[i];
		}
	}
	return NULL;
}
 
int ParseCupBlock62(u8 *psBuf, u16 nPackLen)
{
	u8 i, *psHead = NULL;
	int iRet, iLen;
	
	switch(PosCom.stTrans.Trans_id)
	{
		case POS_LOGON:
			if( !memcmp(PosCom.stTrans.szRespCode,"00",2) || !memcmp(PosCom.stTrans.szRespCode,"89",2) )
			{
				ScrClrLine_Api(LINE2, LINE5);
				ScrDisp_Api(LINE3, 0, "update key", CDISP);
				iRet = PEDWriteCUPKey(psBuf, nPackLen);	// 
				if(gCtrlParam.pinpad_type == PIN_PP)
					iRet = PPWriteCUPKey(psBuf, nPackLen);
				
				DispRenewKeyResult(iRet);
				if(iRet != 0)
					return -3;
			}
			break;
		case EMVCAPK_QUERYIDX:									// 
			if((psBuf[0] >= '0')&&(psBuf[0] <= '3'))
			{
				if( (psBuf[0] == '1')||(psBuf[0] == '3') )		// 
					giRespCmd = EMVCAPKDATA;
				else
				{
					if(nPackLen >= CAPKIDXLEN)
						giRespCmd = EMVCAPKIDX;					// 
					else
						giRespCmd = EMVCAPKDATA;
				}
				//
				psBuf++;
				nPackLen -= 1;
				for(i = 0; i < nPackLen/CAPKIDXLEN; i++)
				{
					psHead = FindMemFromMem(psBuf, CAPKIDXLEN, (u8*)"\x9F\x06", 2);
					if(psHead == NULL) break;					// 
					memcpy(gsEmvCapkIdx[gCtrlParam.EmvDownFlag[1]].RidFlag, psHead, 8);
					psHead = FindMemFromMem(psBuf, CAPKIDXLEN, (u8*)"\x9F\x22", 2);
					if(psHead == NULL) break;					// 
					memcpy(gsEmvCapkIdx[gCtrlParam.EmvDownFlag[1]].CAPKIFlag, psHead, 4);
					psHead = FindMemFromMem(psBuf, CAPKIDXLEN, (u8*)"\xDF\x05", 2);
					if(psHead == NULL) break;					// 
					memcpy(gsEmvCapkIdx[gCtrlParam.EmvDownFlag[1]].ExpDateFlag, psHead, 7);

					if(gCtrlParam.EmvDownFlag[1] < 100)			// 
						gCtrlParam.EmvDownFlag[1]++;
					psBuf += CAPKIDXLEN;
				}
				if(giRespCmd == EMVCAPKDATA)					// 
				{
					DelFile_Api(EVMTEMPFILE);					// 
					WriteFile_Api(EVMTEMPFILE, (u8*)&gsEmvCapkIdx, 0, sizeof(gsEmvCapkIdx));
					gCtrlParam.EmvDownFlag[0] = EMVCAPKDATA;
					SaveCtrlParam();
				}
			}
			break;
		case EMVCAPK_DOWN:										 
			if(psBuf[0] == '1')									 
			{                                                    
				psBuf++;
				nPackLen -= 1;
				iRet = UpdateCapk(psBuf, nPackLen);
				//if(ucRet != 0) error
			}
			
			if(gCtrlParam.EmvDownFlag[1])
				gCtrlParam.EmvDownFlag[1]--;
			if(gCtrlParam.EmvDownFlag[1] == 0)
			{
				giRespCmd = EMVCAPKSTOP;			 
				
				memset(gCtrlParam.EmvDownFlag, 0, sizeof(gCtrlParam.EmvDownFlag));// 
			}
			else
			{
				giRespCmd = EMVCAPKDATA;
			}
			SaveCtrlParam();
			break;
		case EMVPARAM_QUERYIDX:
			if((psBuf[0] >= '0')&&(psBuf[0] <= '3'))
			{
				if( (psBuf[0] == '1')||(psBuf[0] == '3') )
					giRespCmd = EMVPARAMDATA;		 
				else
				{
					if(nPackLen > 4)	 
						giRespCmd = EMVPARAMIDX;					 
					else
						giRespCmd = EMVPARAMDATA;
				}
				//
				psBuf++;
				nPackLen -= 1;
				while(nPackLen)
				{
					iLen = psBuf[2];
					if((memcmp(psBuf,"\x9F\x06",2) == 0)&&((iLen>=0x05)&&(iLen<=0x10)))
					{
						memcpy(gsEmvParamIdx[gCtrlParam.EmvDownFlag[2]].AidFlag, psBuf, iLen+3);
						if(gCtrlParam.EmvDownFlag[2] < 100)	 
							gCtrlParam.EmvDownFlag[2]++;
					}
					//
					iLen += 3;
					psBuf += iLen;
					if(iLen >= nPackLen)
					{
						nPackLen = 0;
					}
					else
					{
						nPackLen -= iLen;
					}
				}
				if(giRespCmd == EMVPARAMDATA)		// 
				{
					DelFile_Api(EVMTEMPFILE);	// 
					WriteFile_Api(EVMTEMPFILE, (u8*)&gsEmvParamIdx, 0, sizeof(gsEmvParamIdx));
					gCtrlParam.EmvDownFlag[0] = EMVPARAMDATA;
					SaveCtrlParam();
				}
			}
			break;
		case EMVPARAM_DOWN:	// 
			if(psBuf[0] == '1')	// 
			{
				psBuf++;
				nPackLen -= 1;
				
				iRet = UpdateEmvParam(psBuf, nPackLen);
				//if(ucRet != 0) error
			}
			if(gCtrlParam.EmvDownFlag[2])
				gCtrlParam.EmvDownFlag[2]--;
			if(gCtrlParam.EmvDownFlag[2] == 0)
			{
				giRespCmd = EMVPARAMSTOP;		// 
				// 
				memset(gCtrlParam.EmvDownFlag, 0, sizeof(gCtrlParam.EmvDownFlag));
			}
			else
			{
				giRespCmd = EMVPARAMDATA;
			}
			SaveCtrlParam();
			break;
		case RBPOINT_CONSUME:	 
		case POS_INST:			 
			memcpy(PosCom.stTrans.AddInfo, psBuf, nPackLen);
			break;
		case POSPARAM_DOWN:
			// 
			psHead = psBuf;
			while(psHead <(psBuf+nPackLen))
			{
				iLen = ((psHead[0]&0x0f)*10)+(psHead[1]&0x0f);
				psHead += 2;
				switch(iLen)
				{
					case 11:
						gCtrlParam.oprTimeoutValue = ((psHead[0]&0x0f)*10)+(psHead[1]&0x0f);
						psHead += 2;
						break;
					case 12:
						G_CommPara.DialSet.ReDialTimes = psHead[0]-'0';
						psHead += 1;
						break;
					case 13:
						gCtrlParam.tip_flag = psHead[0]-'0';
						psHead += 1;
						break;
					case 14:
						gCtrlParam.tip_rate = ((psHead[0]&0x0f)*10)+(psHead[1]&0x0f);
						psHead += 2;
						break;
					case 15:
						gCtrlParam.ucAutoLogoff = psHead[0]-'0';
						psHead += 1;
						break;
					case 16:	 
						//memcpy(gCtrlParam.MerchantName, psHead, 40);
						//gCtrlParam.MerchantName[41] = 0;
						psHead += 40;
						break;
					case 17:
						psHead += 1;	 
						break;
					case 18:
						//gCtrlParam.MainKeyIdx = psHead[0]-'0';		 
						psHead += 1;
						break;
					case 19:
						gCtrlParam.SupportDCC = psHead[0]-'0';
						psHead += 1;
						break;
					case 20:
						AscToBcd_Api(gCtrlParam.MaxReimgursedAmt, (char*)psHead, 12);
						psHead += 12;
						break;
					case 21:
						AscToBcd_Api(gCtrlParam.installment_Min, (char*)psHead, 12);
						psHead += 12;
						break;
					case 22:
						gCtrlParam.ShieldPAN = psHead[0]-'0';
						psHead += 1;
						break;
					case 23:
						gCtrlParam.PrintErrReport = psHead[0]-'0';
						psHead += 1;
						break;
					case 24:
						gCtrlParam.VoidTransPwd = psHead[0]-'0';
						psHead += 1;
						break;
					case 25:
						gCtrlParam.DefaultTrade = psHead[0]-'0';
						psHead += 1;
						break;
					case 26:
						gCtrlParam.installment_BigAmt = psHead[0]-'0';
						psHead += 1;
						break;
					case 27:
						memcpy(gCtrlParam.transflag, psHead, 8);
						psHead += 8;
						break;
					default:
						return 0;	// 
				}
			}
			//giRespCmd = 0x10;	// 
			
			// 
			gCtrlParam.ucAutoLogoff = 1;	 
			gCtrlParam.DefaultTrade = 1;	 
			//gCtrlParam.VoidTransPwd = 0;	 
			SaveCtrlParam();
			break;
		case ACCOUNT_VERIFY:			// 
		case HOLDER_NAMEDISP:
			memcpy(PosCom.stTrans.HoldCardName, psBuf, 20);
			break;
	}
	return 0;
}


