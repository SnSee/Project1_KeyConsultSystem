#include "serverManager.h"
ServerManager::ServerManager(short port){
	portNum = port;
	tcpConnSrv = new TcpConnSrv(1024);
}
int ServerManager::startServer(){
	tcpConnSrv->setListenFd(portNum);
	tcpConnSrv->createEpoll();
	tcpConnSrv->startListen();	
	return 0;
}
ServerManager::~ServerManager(){
	delete tcpConnSrv;
}
