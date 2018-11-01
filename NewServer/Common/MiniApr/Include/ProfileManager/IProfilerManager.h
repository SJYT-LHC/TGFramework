#ifndef __IPROFILERMANAGER_H__
#define __IPROFILERMANAGER_H__

#include <typeinfo>

#define IID_IProfilerManager	MAKE_RID('p','r', 'm', 'g')

BEGIN_MINIAPR_NAMESPACE

class IProfilerManager:public IComponent
{
public:


	virtual void beginProfiler(const std::string& strProfileName) = 0;


	virtual void endProfiler(const std::string& strProfilerName) = 0;


	virtual void incObjCount(const std::string& strClassName, int iSingleSize) = 0;

	virtual void decObjCount(const std::string& strClassName) = 0;
};

class  ProfileHelp
{
public:
	
	ProfileHelp(const char* profileName);
	~ProfileHelp();

private:
	std::string	m_strProfileName;
	static IProfilerManager* m_pProfileManager;
};


template<class T>
class ObjCounter
{
public:

	ObjCounter()
	{
		IProfilerManager* pProfileManager = getComponent<IProfilerManager>("ProfileManager", IID_IProfilerManager);
		if(pProfileManager)
		{
			pProfileManager->incObjCount(typeid(T).name(), (int)sizeof(T) );
		}
	}

	~ObjCounter()
	{
		IProfilerManager* pProfileManager = getComponent<IProfilerManager>("ProfileManager", IID_IProfilerManager);
		if(pProfileManager)
		{
			pProfileManager->decObjCount(typeid(T).name() );
		}
	}
};



#define PROFILE_MONITOR(name)		ProfileHelp stackObject(name);
#define PROFILE_MONITOR_INDEX(index, name)		ProfileHelp stackObject##index(name);
#define PROFILE_OBJ_COUNTER(name)     ObjCounter<name> m_hideObjCounter;


END_MINIAPR_NAMESPACE

#endif
