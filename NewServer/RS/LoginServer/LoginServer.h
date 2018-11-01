#ifndef _LOGIN_SERVERE_H_
#define _LOGIN_SERVERE_H_

#include <iostream>
#include "servant/Application.h"

using namespace std;
using namespace tars;


class LoginServantHandle : public ServantHandle
{
protected:
     virtual void handleClose(const TC_EpollServer::tagRecvData &stRecvData);

};

class LoginServer: public Application
{
public:

	LoginServer();
	~LoginServer();

	virtual void initialize();

	virtual void destroyApp();

	virtual void setHandle(TC_EpollServer::BindAdapterPtr& adapter);
	
};

extern LoginServer g_app;


#endif