#include "dataManager.h"
DataManager::DataManager(){
	buf = new char[BUFSIZ];	
	memset(buf, 0, BUFSIZ);
}
DataManager::DataManager(int cfd){
	m_cfd = cfd;
	buf = new char[BUFSIZ];
	memset(buf, 0, BUFSIZ);
}
void DataManager::setConnFd(const int cfd, struct sockaddr_in &cltaddr){
	this->m_cfd = cfd;
	memcpy(&temp_cltaddr, &cltaddr, sizeof(struct sockaddr));
}
char *DataManager::recvData(){
	memset(buf, 0, BUFSIZ);
	int len_r = read(m_cfd, buf, BUFSIZ);
	if(len_r < 0){
		perror("read error");
		return NULL;
	}
	else if(0 == len_r){
		printf("客户端关闭了连接\n");
		return NULL;
	}
	return buf;
}
int DataManager::sendData(const char *data){
	int len_w = write(m_cfd, data, strlen(data));
	if(len_w < 0){
		perror("write error");
		return -1;
	}
	else if(0 == len_w){
		printf("客户端已关闭");
		return -1;
	}
	return 0;
}
DataManager::~DataManager(){
	delete []buf;
}
