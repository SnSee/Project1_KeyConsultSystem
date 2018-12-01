#ifndef __TLVMES__
#define __TLVMES__
#include <iostream>
#include <string.h>
#include "BaseASN1.h"
using namespace std;
//TLV(序列化)化与反序列化一个结构体
// 数据节点结构体(类)
/*typedef struct ITCAST_ANYBUF_
{
    ITCAST_UINT8 	  *pData;
    ITCAST_UINT32     dataLen;

    ITCAST_UINT32     unusedBits;	
    ITCAST_UINT32     memoryType;
    ITCAST_UINT32     dataType;
    struct ITCAST_ANYBUF_ *next;  
    struct ITCAST_ANYBUF_ *prev;
}ITCAST_ANYBUF;
*/
class TlvMes{
public:
	TlvMes();
	//将结构体第一个成员TLV化并作为头节点
	int encodeHeadNode(int data);
	int encodeHeadNode(char *data);
	//将结构体中其他成员TLV化
	int encodeNextNode(int data);
	int encodeNextNode(char *data);
	//解码头节点，字符串节点需要调用者提供空间
	int decodeHeadNode(int *data);
	int decodeHeadNode(char *data);
	//解码其他节点
	int decodeNextNode(int *data);
	int decodeNextNode(char *data);
	//将链表序列化，outData为传出参数，*outData表示序列化后的字符串
	//使用完要用free释放空间
	void serializeStruct(char **outData, int *outDataLen);
	//将链表反序列化
	void unserializeStruct(char *inData, int inDataLen);
	//释放结构体
	void freeAllNodes();
	~TlvMes();
private:
	BaseASN1 *baseASN1;
	ITCAST_ANYBUF *pHead;	
	ITCAST_ANYBUF *pNext;	
	ITCAST_ANYBUF *pTemp;	
};
#endif
