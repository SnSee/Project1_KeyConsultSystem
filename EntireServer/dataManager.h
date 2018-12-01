#ifndef __DATAMANAGER_
#define __DATAMANAGER_
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "genRequestMsg.h"
using namespace std;
//用于收发及处理数据
class DataManager{
public:
	DataManager();
	DataManager(int cfd);
	virtual ~DataManager() = 0;
	//设置通信文件描述符及客户端ip信息
	void setConnFd(const int cfd, struct sockaddr_in &cltaddr); 
	//读取数据并返回
	char *recvData();
	//发送数据
	int sendData(const char *data);
private:
protected:
	struct sockaddr_in temp_cltaddr;
	int m_cfd;
	char *buf;
};
#endif
