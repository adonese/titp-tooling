#ifndef _PICC_H
#define _PICC_H

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Test Ic Card Function
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : 1.Check Ic Card
            2.Init Ic Card
            3.Send APDU Command
*************************************************************************************/
void PiccCardTest();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Terminal Picc Test with MobilePhone NFC
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void NfcHceTest(void);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Entrance of PIIC card test program
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
int PICCTestFun(void);




#endif