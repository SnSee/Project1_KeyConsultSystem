#ifndef __MY_TYPES__
#define __MY_TYPES__
//请求类型
enum REQTYPE{
    KEY_CONSULT,    //密钥协商                                             
    KEY_CHECK,      //密钥校验k
};
//请求消息结构体
struct RequestMsg{
    int reqType;        //请求类型
    char clientId[12];
    char serverId[12];    
    char rstr[64];      //随机字符串
    char authCode[65];  //认证码
};
//应答消息结构体
//TODO
#endif
