#include "tcpConnSrv.h"
TcpConnSrv::TcpConnSrv(unsigned int maxevents){
	MAXEVENTS = maxevents;
}
int TcpConnSrv::setListenFd(const short port_num){
	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd < 0){
		perror("socket error");
		return -1;
	}
	//端口复用
	int opt = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));
	struct sockaddr_in srvaddr;
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(port_num);
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret_bind = bind(lfd, (struct sockaddr*)&srvaddr, sizeof(srvaddr));
	if(ret_bind < 0){
		perror("bind error");
		return -1;
	}
	listen(lfd, 1);
	return 0;
}
int TcpConnSrv::createEpoll(){
	efd = epoll_create(1024);
	if(efd < 0){
		printf("in file:%s line:%d", __FILE__, __LINE__);
		perror("epoll_create error");
		return -1;
	}
	epoll_event ev;
	ev.events = EPOLLIN|EPOLLET;
	ev.data.fd = lfd; 
	//lfd上树
	epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &ev);
	return 0;
}
int TcpConnSrv::startListen(){
	epoll_event ev;
	epoll_event evs[MAXEVENTS];
	int i = 0;
	socklen_t cltlen = 0;
	int nready = epoll_wait(efd, evs, 1024, -1);
	if(nready < 0){
		printf("in file:%s line:%d:\n", __FILE__, __LINE__);
		perror("epoll_wait error");
		return -1;
	}
	for(i = 0; i < nready; i++){
		int sfd = evs[i].data.fd;
		//处理连接请求
		if(sfd == lfd){
			cfd = accept(lfd, (struct sockaddr*)&temp_cltaddr, &cltlen);
			if(cfd < 0){
				perror("accept error");
				continue;
			}
			//通信文件描述符上树
			//设置epoll为ET边缘触发模式
			ev.events = EPOLLIN|EPOLLET;
			ev.data.fd = cfd;
			epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &ev);	
			//客户端ip信息存储到map中
			map_addr.insert(make_pair(cfd, temp_cltaddr));
		}
		//处理通信
		else{
			dataManager = new ServerDataManager;
			dataManager->setConnFd(cfd, temp_cltaddr);
			data = dataManager->recvData();	
			dataManager->disposeData();
			
			//TODO
		}
	}
	return 0;
}

TcpConnSrv::~TcpConnSrv(){
	if(NULL != dataManager){
		delete dataManager;
		dataManager = NULL;
	}
}
