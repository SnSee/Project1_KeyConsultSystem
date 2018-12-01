#include "serverDataManager.h"
ServerDataManager::ServerDataManager(){
	reqMsg = new RequestMsg;
}
RequestMsg *ServerDataManager::parseData(){
	GenRequestMsg genReqMsg;
	//暂时使用strlen(buf)作为长度，因为长度没有发送过来
	genReqMsg.getRequestMes(*reqMsg, buf, strlen(buf));
	return reqMsg;
}
int ServerDataManager::disposeData(){
	
	if(!isOriginalReq()){
		cout << "数据被篡改" << endl;
		return -1;
	}
	//判断请求类型	
	switch(reqMsg->reqType){
		case REQTYPE::KEY_CONSULT:
			//TODO
			break;
		case REQTYPE::KEY_CHECK:
			break;
	}
	return 0;
}
bool ServerDataManager::isOriginalReq(){
	//计算字符串rstr的哈希值并与传进来的哈希值比较
	char dest[SHA256_DIGEST_LENGTH * 2 + 1] = "";
	HashStr hashStr;
	hashStr.hashlizeStr(dest, reqMsg->rstr, 64);	
	if(strcmp(dest, reqMsg->authCode) != 0){
		return false;
	}
	return true;
}
ServerDataManager::~ServerDataManager(){
	if(NULL != reqMsg){
		delete reqMsg;
		reqMsg = NULL;
	}
}
