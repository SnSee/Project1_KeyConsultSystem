#ifndef __SERVER_DATAMANAGER__
#define __SERVER_DATAMANAGER__
#include "dataManager.h"
#include "genRequestMsg.h"
#include "mytypes.h"
#include "hashStr.h"
class ServerDataManager :public DataManager{
public:
	ServerDataManager();
	//需要先调用父类的方法为buf赋值
	//设置通信文件描述符及客户端ip信息
	//void setConnFd(const int cfd, struct sockaddr_in &cltaddr);
    //读取数据并返回
	//char *recvData();
	//把请求信息解析到reqMsg结构体中
	RequestMsg *parseData();
	//处理请求数据
	int disposeData();
	~ServerDataManager();
private:
	//检查受到的数据是否被篡改
	bool isOriginalReq();

	RequestMsg *reqMsg;	
};
#endif
