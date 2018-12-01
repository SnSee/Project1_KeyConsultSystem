#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <map>
#include "dataManager.h"
#include "serverDataManager.h"
using namespace std;
//创建服务器及收发数据
class TcpConnSrv{
public:
	TcpConnSrv(unsigned int maxevents);
	//创建监听文件描述符，成功返回0，出现问题返回-1
	int setListenFd(const short port_num);
	//创建epoll树用于监听
	int createEpoll();
	//开启监听并根据监听结果进行连接或通信处理
	int startListen();
	//释放空间
	~TcpConnSrv();
private:
	//保存客户端ip信息
	map<int, struct sockaddr_in> map_addr;
	struct sockaddr_in temp_cltaddr;
	int lfd, cfd, efd;
	unsigned int MAXEVENTS;
	ServerDataManager *dataManager;
	char *data;
};
