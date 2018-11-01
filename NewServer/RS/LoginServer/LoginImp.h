#ifndef _LOGIN_IMP_H_
#define _LOGIN_IMP_H_

#include <iostream>
#include "servant/Application.h"
#include "Login.h"

class  LoginImp : public ServerEngine::Login
{

public:

	LoginImp();
	virtual ~LoginImp();

	 /**
     * 对象初始化
     */
    virtual void initialize();

    /**
     * 处理客户端的主动请求
     * @param current
     * @param response
     * @return int
     */
    virtual int doRequest(tars::TarsCurrentPtr current, vector<char>& response);

    /**
     * @param resp
     * @return int
     */
    virtual int doResponse(ReqMessagePtr resp);

	/**
     * @param resp
     * @return int
     */
	int doResponseException(ReqMessagePtr resp);

	/**
     * @param resp
     * @return ints
     */
	int doResponseNoRequest(ReqMessagePtr resp);

    /**
     * 对象销毁
     */
	virtual void destroy();
 //Login 
public:
    virtual tars::Int32 lockUser(tars::Int32 userid,tars::Int32 NewLockState,tars::Int32 lockMin,tars::Int64 &lockTime,std::string &tip,tars::TarsCurrentPtr current);
    virtual tars::Int32 modifyAccid(tars::Int32 userid,tars::Int32 newAccid,std::string &tip,tars::TarsCurrentPtr current);
    virtual tars::Int32 modifyMobile(tars::Int32 userid,const std::string & newMobile,std::string &tip,tars::TarsCurrentPtr current);
    virtual tars::Int32 modifyPassWord(tars::Int32 userid,const std::string & newPassWd,std::string &tip,tars::TarsCurrentPtr current);
};

#endif