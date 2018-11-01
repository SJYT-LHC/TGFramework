#include "LoginServer.h"
#include "LoginImp.h"

LoginServer g_app;

void LoginServantHandle::handleClose(const TC_EpollServer::tagRecvData &stRecvData)
{
	//todo close
}

LoginServer::LoginServer()
{
}

LoginServer::~LoginServer()
{
}

void LoginServer::setHandle(TC_EpollServer::BindAdapterPtr& adapter)
{
	adapter->setHandle<LoginServantHandle>();
}

void LoginServer::initialize()
{
	

	string strLoginObject = ServerConfig::Application + "." + "LoginServer" + ".LoginObj";
	addServant<LoginImp>(strLoginObject);
	addServantProtocol(strLoginObject, &AppProtocol::parseStream<0, unsigned short, true>);

	FDLOG("LoginServer")<<"addobject|"<<strLoginObject<<endl;

}

void LoginServer::destroyApp()
{
	
}	


int main(int argc, char** argv)
{
	try
	{
		g_app.main(argc, argv);
		g_app.waitForShutdown();
	}
	catch (std::exception& e)
	{
		cerr << "std::exception:" << e.what() << std::endl;
	}
	catch (...)
	{
		cerr << "unknown exception." << std::endl;
	}

	return 0;
}