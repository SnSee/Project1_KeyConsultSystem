#ifndef __SERVERMANAGER__
#define __SERVERMANAGER__
#include <iostream>
#include "tcpConnSrv.h"
using namespace std;
//服务器管理
class ServerManager{
public:
	ServerManager(const short port);
	//开启服务器
	int startServer();
	~ServerManager();
private:
	TcpConnSrv *tcpConnSrv;	
	short portNum;
};

#endif
