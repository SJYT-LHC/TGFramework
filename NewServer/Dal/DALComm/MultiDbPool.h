//////////////////////////////////////////////////////////////////////////
//    ֧�ֶ�ip�ֿ���Ե�DbPool
//    author: forrestliu@tencent.com 
//////////////////////////////////////////////////////////////////////////
#ifndef _MULTI_DB_POOL_H_
#define _MULTI_DB_POOL_H_

#include "DbPool.h"

namespace ServerEngine
{
	/** 
     Ĭ�ϻ���key�ķ�Pool����
     */
    template<typename K>
    struct default_dispatch_policy
    {
    	static string getPoolIdx(K key)
    	{
            return "";
    	}
    };
    
    //���ذ汾��100����ƽ���������ip
    template<>
    struct default_dispatch_policy<string>
    {
    	static string getPoolIdx(string key)
    	{
            return TC_Common::tostr(TC_Common::strto<int>(key.substr(key.length() - 2))/20);
    	}
    };


    /** 
     multi database pool
     */
    template 
    < 
        typename T, 
        typename K,
    	typename DispatchPolicy = default_dispatch_policy<K>
    >
    class MultiDbPool : public TC_Singleton<MultiDbPool<T,K,DispatchPolicy> > 
    {
        //typedef DbPool<T> DalDbPool;

        public:
            //��ʼ��
            void init(const TC_Config& conf);
            
            //��ȡ�ض���DBPool
            DbPool<T>* getPool(K key)
            {
                string sIdx = DispatchPolicy::getPoolIdx(key);
                //����, ˫check����, ��֤��ȷ��Ч��
                if(_poolStore.find(sIdx) != _poolStore.end())
                {
                    return _poolStore[sIdx];
                }
                else
                {
                    return NULL;
                }
            }

        protected:
            static TC_ThreadLock            _tl;
            static std::map<string,DbPool<T> *>   _poolStore;
            static bool                     _inited;        ///<�Ƿ��Ѿ���ʼ��
            
    };

     template 
    < 
        typename T,
        typename K,
    	typename DispatchPolicy
    > 
    TC_ThreadLock MultiDbPool<T,K,DispatchPolicy>::_tl; 
    
    template 
    < 
        typename T, 
        typename K,
    	typename DispatchPolicy
    >
    map<string,DbPool<T>*> MultiDbPool<T,K,DispatchPolicy>::_poolStore;

    template 
    < 
        typename T, 
        typename K,
    	typename DispatchPolicy
    >
    bool MultiDbPool<T,K,DispatchPolicy>::_inited = false;

    template 
    < 
        typename T, 
        typename K,
    	typename DispatchPolicy
    >
    void MultiDbPool<T,K,DispatchPolicy>::init(const TC_Config& conf)
    {
        if(!_inited)
        {
            TC_ThreadLock::Lock lock(_tl);
            if(!_inited)
            {
                vector<string> pools;
                if(conf.getDomainVector("/MultiDbPool/Pools", pools))
                {
                    for(size_t i = 0; i < pools.size(); i++)
                    {
                        //LOG->debug()<<"begin to init multi db pool:"<<pools[i]<<endl;
                        const map<string,string> mapConf = conf.getDomainMap("/MultiDbPool/Pools/"+pools[i]);
                        DbPool<T>* pPool = new DbPool<T>();
                        pPool->init(mapConf);
                        _poolStore[pools[i]] = pPool; 
                    }
                }

                _inited = true;
            }   
        }
        
    }

}

#endif

