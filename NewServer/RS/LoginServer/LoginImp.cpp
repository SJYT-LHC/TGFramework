#include "LoginImp.h"

LoginImp::LoginImp()
{

}

LoginImp::~LoginImp()
{

}

void LoginImp::initialize()
{
    //添加各种配置
}

int LoginImp::doRequest(tars::TarsCurrentPtr current, vector<char>& response)
{
    current->setResponse(false);
	const vector<char>& requestBuffer = current->getRequestBuffer();
	if(requestBuffer.size() < 2)
	{
		current->close();
		return 0;
	}

    //协议解析什么的

    return 0;
}

int LoginImp::doResponse(ReqMessagePtr resp)
{
    return -1;
}

int LoginImp::doResponseException(ReqMessagePtr resp)
{
    return -1;
}

int LoginImp::doResponseNoRequest(ReqMessagePtr resp)
{
    return -1;
}


void LoginImp::destroy()
{
    
}


tars::Int32 LoginImp::lockUser(tars::Int32 userid,tars::Int32 NewLockState,tars::Int32 lockMin,tars::Int64 &lockTime,std::string &tip,tars::TarsCurrentPtr current)
{
    return ServerEngine::enRet::enRet_OK;
}

tars::Int32 LoginImp::modifyAccid(tars::Int32 userid,tars::Int32 newAccid,std::string &tip,tars::TarsCurrentPtr current)
{
    return ServerEngine::enRet::enRet_OK;
}

tars::Int32 LoginImp::modifyMobile(tars::Int32 userid,const std::string & newMobile,std::string &tip,tars::TarsCurrentPtr current)
{
    return ServerEngine::enRet_OK;
}

tars::Int32 LoginImp::modifyPassWord(tars::Int32 userid,const std::string & newPassWd,std::string &tip,tars::TarsCurrentPtr current)
{
    return ServerEngine::enRet::enRet_OK;
}