#ifndef __HASHSTR__
#define __HASHSTR__
#include <iostream>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <string.h>
using namespace std;
//将字符串进行哈希运算生成哈希值作为验证码
class HashStr{
public:
	HashStr();
	int hashlizeStr(char *dest, char *src, int srcLen);
	~HashStr();
private:
};
#endif
