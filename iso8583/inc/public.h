

#ifndef _PUBLIC_H
#define _PUBLIC_H




typedef struct
{
	char DispName[8];			// Fun dispname max size is 8
	int (*pCallFun)(void);
}_DEAL_FUN;

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : display tile in first line(Counter display center)
PARAM[IN] : Title : Content to display
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void DispTitle(char* Title);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : display menu, automatically process the need to turn the screen, 
            filter out the need of the key and other issues
PARAM[IN] : Title     : menu title
            Menu      : list of menu
            ucLines   : line numbers predict to be diaplay
            ucStartKey: line number the menu start to diaplay
            ucEndKey  : line number the menu end to diaplay
            IsShowX   : current value falg
            ucTimeOut : timeout(second)
PARAM[OUT]: N/A
RETURN    : key value that pressed, if timeout return -2
NOTES     : if((IsShowX >> t) & 0x01) remark current selected item
*************************************************************************************/
int ShowMenuItem(char *Title, char *Menu[], u8 ucLines, u8 ucStartKey, u8 ucEndKey, int IsShowX, u8 ucTimeOut);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Display the menu item, and select item to run function.
PARAM[IN] : Title    : disp title on line1
            menu     : disp menu and function
            menuCount: the count of menu
            ucTimeOut: timeout(sencond)
PARAM[OUT]: N/A
RETURN    : 0
*************************************************************************************/
int ShowMultMenuItem(char *Title, _DEAL_FUN menu[], int menuCount, unsigned int ucTimeOut);

#endif