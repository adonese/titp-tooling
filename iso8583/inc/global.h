#ifndef HX_GLOBAL_H
#define HX_GLOBAL_H

#ifdef HX_APP_VARIABLES
    #define EXTERN 
#else
    #define EXTERN extern 
#endif
/*
not support memory card on VM20, so
if you test other models, please open this micro.
*/
//#define TEST_NOTVM20  //if not vm20

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <ctype.h>
#include <stdarg.h>
#include "struct.h"
#include "coredef.h"
#include "EmvCommon.h"
#include "poslib.h"

#include "public.h"
#include "testConfig.h"

#ifdef TEST_IC
#include "ic.h"
#endif
#ifdef TEST_LCD
#include "lcd.h"
#endif
#ifdef TEST_PICC
#include "picc.h"
#endif
#ifdef TEST_MAG
#include "mag.h"
#endif
#ifdef TEST_KEY
#include "key.h"
#endif
#ifdef TEST_PED
#include "ped.h"
#endif
#ifdef TEST_EMV
#include "EmvCallBack.h"
#endif

#ifdef TEST_SSL
#include "Ssl.h"
#endif


#ifdef _SIMULATOR
#if 0
/*************************************************************************************
WRITER:         Lu Jianxing
COPYRIGHT:      Vanstone Electronic Technology (Beijing)Co.Ltd.
FUNCTION:       Generate QRcode bmp
PARAMETERS[IN]: str:the string used to generate QRcode,
				version: 0-4
				level:0-3
				FilePath:the path the bmp file will be saved 
PARAMETERS[OUT]:N/A	 
RETURN VALUE:   0: Success Others:failuer
NOTE:           N/A	
*************************************************************************************/
int QREncodeString(const char *str, int version, int level, const char *FilePath)
{
	return 0;
}
#endif
#endif


//#define QRCODE 
//#define TWOSIMSLOTS
EXTERN int FlushTime ;

//#define LST_SIMULATOR

#endif

