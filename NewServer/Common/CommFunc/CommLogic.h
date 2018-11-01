#ifndef _COMM_LOGIC_H_
#define _COMM_LOGIC_H_
/////////////////////////////////////////////////////////////////////
#include <math.h>
#include <set>
#include "servant/Application.h"
#include "servant/Communicator.h"
#include "count_time.hpp"
#include "ErrorHandle.h"

/////////////////////////////////////////////////////////////////////
using namespace std;
using namespace tars;

/////////////////////////////////////////////////////////////////////

namespace ServerEngine
{
/////////////////////////////////////////////////////////////////////

/**
 * ͨ��ģ�巽��: JCE����T���л�
 * @param t ����T�Ķ���
 * @return �ַ���
 */
template<typename T> std::string TarsToStr(const T& t)
{
	string s;
	try
	{
	    tars::TarsOutputStream<BufferWriter> osk;
	    t.writeTo(osk);
	    s.assign(osk.getBuffer(),osk.getLength());
	}
	catch(std::exception& e)
	{
		string strReason = e.what();
		assert(false);
	}

    return s;
}

/**
 * ͨ��ģ�巽��: JCE����T�ṹ��
 * @param s �ַ���
 * @return ����T�Ķ���
 */
template<typename T> T& TarsToObj(const std::string& s,T& t)
{
	try
	{
    	tars::TarsInputStream<BufferReader> isk;
		isk.setBuffer(s.c_str(),s.length());
		t.readFrom(isk);
	}
	catch(std::exception& e)
	{
		string strReason = e.what();
		assert(false);
	}

    return t;
}

/**
 * ͨ��ģ�巽��: JCE����T���л�
 * @param t ����T�Ķ���
 * @param buffer ���л�����ַ�����
 */
template<typename T> void TarsToBuffer(const T& t, vector<tars::Char>& buffer)
{
    tars::TarsOutputStream<BufferWriter> osk;
    t.writeTo(osk);
    buffer = osk.getByteBuffer();

    return;
}

/**
 * ͨ��ģ�巽��: JCE����T�ṹ��
 * @param vc �ַ�����
 * @param t ����T�Ķ���
 * @return ����T�Ķ���
 */
template<typename T, typename B> T& TarsToObj(const B& vc,T& t)
{
    tars::TarsInputStream<BufferReader> isk;
    isk.setBuffer((const tars::Char*)(&vc[0]), vc.size());
    t.readFrom(isk);

    return t;
}
/**
 * ͨ��ģ�巽��: JCE����T�ṹ����ӡ
 * @param t ����T�Ķ���
 * @return �ַ���
 */
template<typename T> std::string PrintTars(const T& t)
{
    ostringstream os;
    t.display(os);

    return os.str();
}

/**
 * ͨ��ģ�巽��: Tars���������ṹ����ӡ
 * @param itbegin  ������iterator begin
 * @param itend  ������iterator end
 * @return �ַ���
 */
template <typename I> std::string PrintTars(I itbegin,I itend)
{
    std::ostringstream s;
    I it = itbegin;
	while(it!=itend) 
    {
		it->display(s);
        it++;
	}
	return s.str();
}

/**
 * ͨ��ģ�巽��: JCE����T������־����ӡ
 * @param t ����T�Ķ���
 * @return �ַ���
 */
template<typename T> std::string LogTars(const T& t)
{
    ostringstream os;
    t.displaySimple(os);

    return os.str();
}

/**
 * ͨ��ģ�巽��: Tars����������־����ӡ
 * @param itbegin  ������iterator begin
 * @param itend  ������iterator end
 * @return �ַ���
 */
template <typename I> std::string LogTars(I itbegin,I itend)
{
    std::ostringstream s;
    I it = itbegin;
	while(it!=itend) 
    {
		it->displaySimple(s);
        s<<";";
        it++;
	}
	return s.str();
}


//����ת��
#define TC_I2S(I)       TC_Common::tostr<int>(I)
#define TC_S2I(S)       TC_Common::strto<int>(S)
#define TC_S2SIZET(S)   TC_Common::strto<size_t>(S)
#define TC_S2KEYT(S)    TC_Common::strto<key_t>(S)
#define TC_TIMET2S(I)   TC_Common::tostr<time_t>(I)
#define TC_S2TIMET(I)   TC_Common::strto<time_t>(I)
#define TC_S2F(S)       TC_Common::strto<float>(S)
#define TC_U2S(N)       TC_Common::tostr<unsigned>(N)
#define TC_S2U(S)       TC_Common::strto<unsigned>(S)
#define TC_TRIM(S)      TC_Common::trim(S)
#define TC_BIN2S(S)     TC_Common::bin2str(S)
#define TC_G2U8(S)      TC_Encoder::gbk2utf8(S)
#define TC_U82G(S)      TC_Encoder::utf82gbk(S)

//���̿���
#define PROC_BEGIN do{
#define PROC_END   }while(0);

#define PROC_TRY_BEGIN do{try{
#define PROC_TRY_END   }__COMMON_EXCEPTION_CATCH__}while(0);

inline unsigned int StrIp2Int(const string& sIp)
{
	struct in_addr inaddr;
	inet_aton(sIp.c_str(), &inaddr);
	return inaddr.s_addr;
}
inline bool IsQQ(unsigned i)
{
    return (i > 10000) && (i < 0x80000000);
}

inline bool IsQQ(const string& qq)
{
	string sQQ = TC_TRIM(qq);
	if (TC_Common::isdigit(sQQ))
	{
		unsigned i = TC_S2U(sQQ);
    	return IsQQ(i);
	}

	return false;
}
inline void StringToLower(const string& sOrg, string& sDest)
{
    sDest = sOrg;
	transform(sDest.begin(),sDest.end(),sDest.begin(), ::tolower);
}

/////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////
#endif //
/////////////////////////////////////////////////////////////////////




