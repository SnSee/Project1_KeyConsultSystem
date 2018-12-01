#include "genRequestMsg.h"

GenRequestMsg::GenRequestMsg(){
	this->m_reqMsg = new RequestMsg;
}
char *GenRequestMsg::setRequestMes(RequestMsg &reqMsg){
	m_reqMsg->reqType = reqMsg.reqType;
	strcpy(m_reqMsg->clientId, reqMsg.clientId);
	strcpy(m_reqMsg->serverId, reqMsg.serverId);
	getRandStr(m_reqMsg->rstr, sizeof(m_reqMsg->rstr));
	//调用散列函数的类生成哈希值()
	HashStr hashStr;
	hashStr.hashlizeStr(m_reqMsg->authCode, m_reqMsg->rstr, sizeof(m_reqMsg->rstr));	
	char *msg = genRequestStr();
	return msg;
}
void GenRequestMsg::getRequestMes(RequestMsg &reqMsg, char *inData, int inDataLen){
	ungenRequestStr(inData, inDataLen);
	reqMsg.reqType = m_reqMsg->reqType;
	strcpy(reqMsg.clientId, m_reqMsg->clientId);
	strcpy(reqMsg.serverId, m_reqMsg->serverId);
	strcpy(reqMsg.rstr, m_reqMsg->rstr);
	strcpy(reqMsg.authCode, m_reqMsg->authCode);
}
char *GenRequestMsg::genRequestStr(){
	char *buf = NULL;
	int msgLen = 0;
	TlvMes *tlvMes = new TlvMes;
	tlvMes->encodeHeadNode(m_reqMsg->reqType);
	tlvMes->encodeNextNode(m_reqMsg->clientId);
	tlvMes->encodeNextNode(m_reqMsg->serverId);
	tlvMes->encodeNextNode(m_reqMsg->rstr);
	tlvMes->encodeNextNode(m_reqMsg->authCode);
	//TODO:使用完msg后用free释放空间
	tlvMes->serializeStruct(&buf, &msgLen);
	char *msg = new char[msgLen];
	strcpy(msg, buf);
	tlvMes->freeAllNodes();

	delete tlvMes;
	return msg;
}
void GenRequestMsg::ungenRequestStr(char *inData, int inDataLen){
	TlvMes *tlvMes = new TlvMes;
	tlvMes->unserializeStruct(inData, inDataLen);
	tlvMes->decodeHeadNode(&m_reqMsg->reqType);
	tlvMes->decodeNextNode(m_reqMsg->clientId);
	tlvMes->decodeNextNode(m_reqMsg->serverId);
	tlvMes->decodeNextNode(m_reqMsg->rstr);
	tlvMes->decodeNextNode(m_reqMsg->authCode);
	tlvMes->freeAllNodes();

	delete tlvMes;
}

char *GenRequestMsg::getRandStr(char *str, int strLen){
	srand(time(NULL));	
	int index, i = 0;
	for(i = 0; i < strLen; i++){
		index = rand() % 3;
		switch(index){
			case 0:
				str[i] = rand() % 10 + '0';			
				break;
			case 1:
				str[i] = rand() % 26 + 'a';
				break;
			case 2:
				str[i] = rand() % 26 + 'A';
				break;
		}
	}
	return str;
}
GenRequestMsg::~GenRequestMsg(){
	if(NULL != m_reqMsg){
		delete m_reqMsg;
		m_reqMsg = NULL;
	}
}
