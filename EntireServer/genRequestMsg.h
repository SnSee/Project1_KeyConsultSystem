#ifndef __GEN_REQUESTMSG__
#define __GEN_REQUESTMSG__
#include <iostream>
#include <string.h>
#include <ctime>
#include "tlvMes.h"
#include "hashStr.h"
#include "mytypes.h"
using namespace std;
//生成最终要发送的消息（调用编码及序列化类的方法）
//请求类型
//enum REQTYPE{
//	KEY_CONSULT,	//密钥协商
//	KEY_CHECK,		//密钥校验k
//};
////请求消息结构体
//struct RequestMsg{
//	int reqType;		//请求类型
//	char clientId[12];
//	char serverId[12];	
//	char rstr[64];		//随机字符串
//	char authCode[65];	//认证码
//};
class GenRequestMsg{
public:
	GenRequestMsg();
	~GenRequestMsg();
	//初始化请求消息结构体，传入的结构体不必包含随机字符串和验证码
	//返回要发送的字符串，使用完要free这个指针
	char *setRequestMes(RequestMsg &reqMsg);
	//返回解析后的请求消息结构体
	void getRequestMes(RequestMsg &reqMsg, char *inData, int inDataLen);
private:
	//将请求消息结构体转化成可传输的字符串，使用完成后要free掉返回的指针对应空间
	char *genRequestStr();
	//将收到的字符串解析成结构体
	void ungenRequestStr(char *inData, int inDataLen);
	//生成随机字符串
	char *getRandStr(char *str, int strLen);
private:
	RequestMsg *m_reqMsg;
};
#endif
