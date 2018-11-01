#ifndef __IPROFILER_STRATEGY_H__
#define __IPROFILER_STRATEGY_H__

#define IID_IProfilerStrategy	 MAKE_RID('p','r','s','r')

BEGIN_MINIAPR_NAMESPACE

class IProfilerStrategy:public IComponent
{
public:

	virtual void onBeginProfiler(const std::string& strProfilerName, Uint64 ddTimer) = 0;


	virtual void onEndProfiler(const std::string& strProfilerName, Uint64 ddTimer) = 0;

	virtual void onObjCountInc(const std::string& strClassName, int iSingleSize) = 0;

	virtual void onObjCountDec(const std::string& strClassName) = 0;
};

END_MINIAPR_NAMESPACE

#endif
