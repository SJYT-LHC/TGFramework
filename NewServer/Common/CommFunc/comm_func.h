#ifndef _COMM_FUNC_H
#define _COMM_FUNC_H

// ������������
#include <libgen.h>
#include <libgen.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "define.h"

#define _fval_to_ival(fval,ival) (ival) = *(int*)&(fval)
#define _ival_to_fval(ival,fval) (fval) = *(float*)&(ival)

#define MAX_CAT_LEN 131072
#define StrCat( str, iLen, format, ... ) do{\
    char szMsg[MAX_CAT_LEN];\
	snprintf( szMsg, MAX_CAT_LEN-1, format, ##__VA_ARGS__ ); \
    szMsg[MAX_CAT_LEN-1] = 0;\
    int iCatLen = iLen - strnlen(str, iLen);\
	if( iCatLen > 0 )\
	{\
		strncat( str, szMsg, iCatLen );\
	}\
}while(0)

//MASK���
//MASKֱ�Ӷ�Ӧ����Ӧ��MASKֵ
#define CLS_MASK(DATA,MASK) (DATA) = ((DATA) & (~(MASK)))
#define SET_MASK(DATA,MASK) (DATA) = ((DATA) | (MASK))
#define IS_MASK(DATA,MASK)  ((((DATA) & (MASK)) > 0)?true:false)
//MASKPOS��Ӧ��MASK��bitλ��,��0��ʼ��0��Ӧ���ұߵ�bitλ
#define CLS_MASK_BYPOS(DATA,MASKPOS) (DATA) = ((DATA) & (~(1<<(MASKPOS))))
#define SET_MASK_BYPOS(DATA,MASKPOS) (DATA) = ((DATA) | (1<<(MASKPOS)))
#define IS_MASK_BYPOS(DATA,MASKPOS)  ((((DATA) & (1<<(MASKPOS))) > 0)?true:false)

void 	StrCpy( char *szDst, const char *szSrc, int iBufLen);
void    UTF8_2_UNICODE(char *szDst, unsigned int &dwDstStrLen, const char *szSrc, int iSrcSize, bool bZeroEnd = true);
void 	CapStrCpy(char *szDst, unsigned char& cDstStrLen, const char *szSrc, int iBufLen, bool bUnicode = false );
void    CapLongStrCpy(char * szDst, unsigned short &wDstStrLen, const char *szSrc, int iBufLen,bool bUniCode = false );

void 	CapBinaryStrCpy(char *szDst, unsigned char& cDstStrLen, const char *szSrc, int iBufLen);
void    CapLongBinaryStrCpy(char * szDst, unsigned short &wDstStrLen, const char *szSrc, int iBufLen);
WORD 	GetIconMagicWord();


char 	*MakeIPStr( int iIPAddr);
int 	StartDaemonProcess(const char szWorkDir [ ]);
bool 	IsProcessSingle(char * szProcessName);
int 	StopProcess(char * szProcessName);
int 	AnalysizeZoneIndex(int iEntryID, int *piWorldIndex, int *piZoneIndex);
unsigned int Str2HashInt( const char * arkey, unsigned int nKeyLength);
void 	StrTrim(char * strInput);

int 	TimValMinus( timeval & tvA, TIME_VAL &tvB, TIME_VAL &tvResult);
float   FastInvSqrt(float x);
void 	GetStringTime( time_t timeNow, char *pszTime, int len);

//��һ�����ͻ��ZoneSvr��Dir���е�λ�ñ�ǣ�����:������ID,����ID,����ID,��ID
void         IntToSvrID(const unsigned int iComID, char& cWorldGrpID,char& cWorldID,char& cZoneGrpID,char& cZoneSvrID);
//��������ID,����ID,����ID,��ID�������ZoneSvr��Dir���е�int��ʽ��λ�ñ��
//unsigned int���ݸ�ʽ����(��IDռ1���ֽ�):
//cWorlGrpID|cWorldID|cZoneGrpID|cZoneSvrID
//      8bit|    8bit|      8bit|     8bit|      
unsigned int SvrIDToInt(const char cWorldGrpID,const char cWorldID,const char cZoneGrpID,const char cZoneSvrID);

bool IsStringNum(char *szNumString, int iLen);
int AdvanceAtoi(const std::string& strValue);

unsigned int MsPass(struct timeval* pstTv1, struct timeval* pstTv2);



//ģ���еı���������ʽΪ${parakey},����AΪʵ�ʵļ�ֵ��,��mParam��������parakey��Ӧ��ֵ
void MakeTextFromTemplatePara(const string &sTemplateCont, map<string, string> &mParam, string &sRetText);

//sDesc��ʽ����Ϊ(#�ָ�):��͵ȼ�1#100#��͵ȼ�2#300
//��:  1#100#50#120
//����false����û���ҵ���Ӧ����ֵ���߸�ʽ����,��ʱ����iHitVal��֤Ϊ0
bool getRightValByLevel(const std::string& sDesc, int iLevel, int &iHitVal);

inline unsigned int GetClientIpFromConnPos( INT64 iConnPos )
{ 
    return (unsigned int)( iConnPos >> 16 );
}
inline unsigned short GetClientPortFromConnPos( INT64 iConnPos )
{
	return (unsigned short)(iConnPos &0xFFFF);
}
inline string IntIpToStrIp( unsigned int iIPAddr)
{
	char* sIp = inet_ntoa(*(struct in_addr *)(&iIPAddr));
	return string(sIp,strlen(sIp));
}


#endif

