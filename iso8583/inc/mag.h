#ifndef _MAG_H
#define _MAG_H


#define MODE_AUTO	0
#define MODE_MANUAL	1

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : check if the trackdata is exist
PARAM[IN] : TrackData :trackdata
            TrackFlag :control if count 2-3 track or count 1-2-3 track  success rates
            TrackFlag = 0x06  count 2-3 track      success rates
            TrackFlag = 0x07  count 1-2-3 track    success rates
PARAM[OUT]: N/A
RETURN    : the result of check  : FALSE -fail TRUE -success
NOTES     : Only according to the length of data to adjust if success ,
            and do not carry out specific data comparison	
*************************************************************************************/
BOOL CheckMagTrack(u8 *TrackData, int TrackFlag);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Check if the trackdata is valid
PARAM[IN] : TrackData :trackdata
PARAM[OUT]: N/A
RETURN    : the result of check  : FALSE-failure 	TRUE-success
NOTES     : The length of trackdata is the compressive BCD code number
*************************************************************************************/
BOOL CheckReadMagData(u8 *TrackData);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Separate three track data
PARAM[IN] : Inbuf :	trackdata that read out
PARAM[OUT]: Outbuf:	trackdata that separated
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void MagDataAnalyticTo3Track(unsigned char *Inbuf, char *Outbuf);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Branch paging display
PARAM[IN] : *DispBuf:  string to display
            StarLine:  start line of diaplay
            EndLine :  endline of display
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void SrcDispForBuf(char *Title, char *DispBuf, int StarLine, int EndLine);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Entrance of Magnetic card trackdata  test procedure
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
void MagTrackCheck(void);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Entrance of Magnetic card swipe success rate test procedure
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : TRUE:test success 
            FALSE:test failed or canceled
NOTES     : N/A
*************************************************************************************/
BOOL MagSuccCheck(void);

/*************************************************************************************
AUTHOR    : www.vanstone.com.cn
FUNCTION  : Entrance of Magnetic card test program
PARAM[IN] : N/A
PARAM[OUT]: N/A
RETURN    : N/A
NOTES     : N/A
*************************************************************************************/
int MAGTestFun(void);

#endif