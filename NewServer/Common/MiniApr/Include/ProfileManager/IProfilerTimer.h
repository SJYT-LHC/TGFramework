#ifndef __IPROFILER_TIMER_H__
#define __IPROFILER_TIMER_H__

#define IID_IProfilerTimer	MAKE_RID('p','r','t','m')

BEGIN_MINIAPR_NAMESPACE

class IProfilerTimer:public IComponent
{
public:
	
	virtual Uint64 getMicroseconds() = 0;
	
	virtual void resetTimer() = 0;
};

END_MINIAPR_NAMESPACE

#endif
