#ifndef _KEY_H
#define _KEY_H

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  :  Processing fastkeys
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
REMARK:A timeout time (2sec)
*************************************************************************************/
void FastKeyTest(void);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  :  Display key value
PARAM[IN] : key :key value needed to display
PARAM[OUT]: N/A
RETURN    : N/A
*************************************************************************************/
void  GetKey_Ret(U8 Key, u8 DispLine);

/************************************************* ************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION : The entrance of key test program
PARAM[IN]: N/A
PARAM[OUT]: N/A
RETURN: TRUE:all keys were tested and exit  FALSE: Not all keys were tested and tested
REMARK: ESC key should be pressed at last while testing
************************************************** ***********************************/
BOOL  KeyValueTest();

BOOL  WaitKeyValueTest();

/************************************************* ************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION : test sound while key pressed
PARAM[IN]: N/A
PARAM[OUT]: N/A
RETURN: N/A
************************************************** ***********************************/
void KeySoundTest(void);

/************************************************* ************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION : The interface of key press test program
PARAM[IN]:   N/A
PARAM[OUT]: N/A
RETURN: 0
************************************************** ***********************************/
int KEYTestFun(void);



#endif