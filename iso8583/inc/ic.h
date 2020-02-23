
#ifndef _IC_H
#define _IC_H

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
void IcCardTest();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Test Psam Card Function
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : 1.Init Psam Card
            2.Send APDU Command
*************************************************************************************/
void PsamCardTest();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Test SLE4442 Card Function
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void SLE4442CardTest();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Init SLE4442 Card
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void CheckAndInit_4442Card();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Read SLE4442 Card Data
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void ReadData_4442Card();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Write SLE4442 Card Data
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void WriteData_4442Card();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Verify SLE4442 Card PWD
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void VerifyPwd_4442Card();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Update SLE4442 Card Pwd
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void UpdatePwd_4442Card();

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Get SLE4442 Card Error PWD Input Count
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void GetPwdCount_4442Card();



/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Entrance of IC card test program
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
int ICTestFun(void);




#endif