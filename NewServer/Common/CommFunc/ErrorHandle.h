#ifndef _ERRORHANDLE_H_
#define _ERRORHANDLE_H_
/////////////////////////////////////////////////////////////////////
#include "log/tars_logger.h"
#include "servant/PropertyReport.h"

using namespace tars;

/////////////////////////////////////////////////////////////////////
namespace Aegis
{
/////////////////////////////////////////////////////////////////////


/*
 *	�쳣������
 *	��׽���쳣�������ж�Ϊϵͳ���󣬷�ҵ��ʧ�ܵ�����������ǵ�������־��
 *	ϵͳ�������е�����´�����־Ӧ��Ϊ��
 *
 *	�쳣������__COMMON_EXCEPTION_CATCH__������
 *	������¼����ʹ��ERRLOG������
 */
/////////////////////////////////////////////////////////////////////

// ������־
#ifndef RLOG
#define RLOG (LOG->debug())
#endif
//#define	FDLOG(name) (FDLOG(name))
// ������־
#ifndef TRLOG
#define TRLOG   (LOG->debug() << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|")
#endif
#ifndef TFDLOG
#define TFDLOG(name)   (FDLOG(name)<<"|" )
#endif
//#define DAYLOG   (DLOG)
#ifndef TDLOG
#define TDLOG   (DLOG << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|")
#endif
#ifndef ERRLOG
#define ERRLOG   (FDLOG("error"))
#endif
#ifndef TERRLOG
#define TERRLOG  (FDLOG("error") << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|")
#endif

/////////////////////////////////////////////////////////////////////
//ͳһ�쳣����
#ifndef  __COMMON_EXCEPTION_CATCH__
#define  __COMMON_EXCEPTION_CATCH__   \
	catch(TafException &tarsEx)\
{\
    TERRLOG << "exception|tars|" << tarsEx.what() << endl;\
}\
	catch ( TC_Exception &e )\
{\
	TERRLOG << "exception|tc|" << e.what() << endl;\
}\
	catch ( exception &e ) \
{\
	TERRLOG << "exception|exception|" << e.what() << endl;\
}\
	catch ( ... )\
{\
	TERRLOG << "exception|unkown" << endl;\
} 
#endif
/////////////////////////////////////////////////////////////////////
// 
//֧������һ���ؼ���
#ifndef  __COMMON_EXCEPTION_CATCH_EXT__
#define  __COMMON_EXCEPTION_CATCH_EXT__(KEY)   \
	catch(TafException &tarsEx)\
{\
    TERRLOG << "exception|tars|" << tarsEx.what() << "|" << KEY << endl;\
}\
	catch ( TC_Exception &e )\
{\
	TERRLOG << "exception|tc|" << e.what() << "|" << KEY << endl;\
}\
	catch ( exception &e ) \
{\
	TERRLOG << "exception|exception|" << e.what() << "|" << KEY << endl;\
}\
	catch ( ... )\
{\
	TERRLOG << "exception|unkown" << "|" << KEY << endl;\
} 
#endif


/////////////////////////////////////////////////////////////////////

#ifndef  __COMMON_EXCEPTION_CATCH_THROW__
#define  __COMMON_EXCEPTION_CATCH_THROW__   \
	catch(TafException &tarsEx)\
{\
    TERRLOG << "exception|tars|" << tarsEx.what() << endl;\
   	throw;\
}\
	catch ( TC_Exception &e )\
{\
	TERRLOG << "exception|tc|" << e.what() << endl;\
   	throw;\
}\
	catch ( exception &e ) \
{\
	TERRLOG << "exception|exception|" << e.what() << endl;\
   	throw;\
}\
	catch ( ... )\
{\
	TERRLOG << "exception|unkown" << endl;\
   	throw;\
} 
#endif


/////////////////////////////////////////////////////////////////////

#ifndef  __COMMON_EXCEPTION_CATCH_THROW_EXT__
#define  __COMMON_EXCEPTION_CATCH_THROW_EXT__(KEY)   \
	catch(TafException &tarsEx)\
{\
    TERRLOG << "exception|tars|" << tarsEx.what() << "|" << KEY << endl;\
   	throw;\
}\
	catch ( TC_Exception &e )\
{\
	TERRLOG << "exception|tc|" << e.what() << "|" << KEY << endl;\
   	throw;\
}\
	catch ( exception &e ) \
{\
	TERRLOG << "exception|exception|" << e.what() << "|" << KEY << endl;\
   	throw;\
}\
	catch ( ... )\
{\
	TERRLOG << "exception|unkown" << "|" << KEY << endl;\
   	throw;\
} 
#endif

//���̿���
#ifndef  __BEGIN_DO_WHILE_FALSE_PROC__
#define __BEGIN_DO_WHILE_FALSE_PROC__  do{
#endif
#ifndef  __END_DO_WHILE_FALSE_PROC__
#define __END_DO_WHILE_FALSE_PROC__    }while(0);
#endif

/////////////////////////////////////////////////////////////////////
// Property ͳ��
// �����ϱ����󹤳���tars����Ｚ���˹������������ٷ�װһ��
class PropertyReportFactory : TC_HandleBase, public TC_ThreadLock, public TC_Singleton<PropertyReportFactory>
{
public:
    map<string, PropertyReportPtr>& getProperty(){return m_mPropertyReport;}
	TC_ThreadMutex &getSelfMutex(){return m_mutex;}
private:
    map<string, PropertyReportPtr> m_mPropertyReport;
	TC_ThreadMutex m_mutex;
};

// �������ֲ�����������ϱ���������Ҫ�ֲ���Ҫ�����Ӷ���
#define __TARS_PROPERTY_CREATE__(name) { \
	TC_LockT<TC_ThreadMutex> lock(PropertyReportFactory::getInstance()->getSelfMutex()); \
	if (PropertyReportFactory::getInstance()->getProperty().find(name) == PropertyReportFactory::getInstance()->getProperty().end()) \
	{ \
		PropertyReportFactory::getInstance()->getProperty()[name] = Application::getCommunicator()->getStatReport()->createPropertyReport(name, PropertyReport::sum(), PropertyReport::avg(), PropertyReport::count(), PropertyReport::max(), PropertyReport::min()); \
	} \
}

// ��������������ϱ�����
#define __TARS_PROPERTY_CREATE_SPEC__(name,policy)  { \
	TC_LockT<TC_ThreadMutex> lock(PropertyReportFactory::getInstance()->getSelfMutex()); \
	if (PropertyReportFactory::getInstance()->getProperty().find(name) == PropertyReportFactory::getInstance()->getProperty().end()) \
	{ \
		PropertyReportFactory::getInstance()->getProperty()[name] = Application::getCommunicator()->getStatReport()->createPropertyReport(name, PropertyReport::sum(), policy); \
	} \
} 

// �����ϱ�
#define __TARS_PROPERTY_REPORT__(name,value)  { \
	map<string, PropertyReportPtr>::iterator it = PropertyReportFactory::getInstance()->getProperty().find(name); \
	if (it != PropertyReportFactory::getInstance()->getProperty().end()) \
	{ \
		PropertyReportFactory::getInstance()->getProperty()[name]->report(value); \
	} \
}

/////////////////////////////////////////////////////////////////////
// tarsstat�ӿڼ�أ����ڷ�tars�ӿڵļ��
// ���:
//      obj       ����ģ��. һ�����app.servername ����:Comm.BindServer
//      func      �����ӿ���
//      host      ����IP
//      port      ����port
//      result    ���ֵ(StatReport::StatResult����):�ɹ�STAT_SUCC����ʱ STAT_TIMEOUT���쳣STAT_EXC
//      costtime  ��ʱ(��λms)
#define __TARS_REPORT_TO_STAT__(obj,func,host,port,result,costtime) { \
    StatReport* stat = Application::getCommunicator()->getStatReport(); \
    if (stat) \
    { \
        stat->report(obj, func, host, port,(StatReport::StatResult)result, costtime, 0, true); \
    } \
}

// �쳣�ϱ�
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////
#endif //_SNSCLI_ERRORHANDLE_H_
/////////////////////////////////////////////////////////////////////




