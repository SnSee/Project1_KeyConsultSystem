#include "tlvMes.h"
#include "BaseASN1.h"
#include "ItcastLog.h"
TlvMes::TlvMes(){
	baseASN1 = new BaseASN1;
	pHead = NULL;
	pNext = NULL;
	pTemp = NULL;
}

int TlvMes::encodeHeadNode(int data){
	baseASN1->DER_ItAsn1_WriteInteger((ITCAST_UINT32)data, &pHead);
	pNext = pHead;
	pHead->next = NULL;	
	return 0;
}

int TlvMes::encodeHeadNode(char *data){
	baseASN1->DER_ITCAST_String_To_AnyBuf(&pTemp, (unsigned char *)data, strlen(data));
	baseASN1->DER_ItAsn1_ReadPrintableString(pTemp, &pHead);
	pNext = pHead;
	pHead->next = NULL;
	baseASN1->DER_ITCAST_FreeQueue(pTemp);
	pTemp = NULL;
	return 0;
}

int TlvMes::encodeNextNode(int data){
	baseASN1->DER_ItAsn1_WriteInteger(data, &pNext);
	pNext = pNext->next;
	return 0;
}

int TlvMes::encodeNextNode(char *data){
	baseASN1->DER_ITCAST_String_To_AnyBuf(&pTemp, (unsigned char *)data, strlen(data));
	baseASN1->DER_ItAsn1_WritePrintableString(pTemp, &(pNext->next));
	baseASN1->DER_ITCAST_FreeQueue(pTemp);
	pNext = pNext->next;
	return 0;
}

int TlvMes::decodeHeadNode(int *data){
	baseASN1->DER_ItAsn1_ReadInteger(pHead, (ITCAST_UINT32*)data);
	pNext = pHead->next;
	return 0;
}

int TlvMes::decodeHeadNode(char *data){
	baseASN1->DER_ItAsn1_ReadPrintableString(pHead, &pTemp);
	memcpy(data, pTemp->pData, pTemp->dataLen);
	baseASN1->DER_ITCAST_FreeQueue(pTemp);
	pTemp = NULL;
	pNext = pHead->next;
	return 0;
}

int TlvMes::decodeNextNode(int *data){
	baseASN1->DER_ItAsn1_ReadInteger(pNext, (ITCAST_UINT32*)data);
	pNext = pNext->next;
	return 0;
}

int TlvMes::decodeNextNode(char *data){
	baseASN1->DER_ItAsn1_ReadPrintableString(pNext, &pTemp);
	memcpy(data, pTemp->pData, pTemp->dataLen);
	baseASN1->DER_ITCAST_FreeQueue(pTemp);
	pTemp = NULL;
	pNext = pNext->next;
	return 0;
}
//将链表序列化
void TlvMes::serializeStruct(char **outData, int *outDataLen){
	baseASN1->DER_ItAsn1_WriteSequence(pHead, &pTemp);
	*outData = (char *)pTemp->pData;
	*outDataLen = pTemp->dataLen;
	baseASN1->DER_ITCAST_FreeQueue(pHead);
}
//将链表反序列化
void TlvMes::unserializeStruct(char *inData, int inDataLen){
	baseASN1->DER_ITCAST_String_To_AnyBuf(&pTemp, (unsigned char *)inData, inDataLen);
	baseASN1->DER_ItAsn1_ReadSequence(pTemp, &pHead);
	baseASN1->DER_ITCAST_FreeQueue(pTemp);
}
void TlvMes::freeAllNodes(){
	if(pHead != NULL){
		baseASN1->DER_ITCAST_FreeQueue(pHead);
		pHead = NULL;
	}
	if(pTemp != NULL){
		baseASN1->DER_ITCAST_FreeQueue(pTemp);
		pTemp = NULL;
	}
}
TlvMes::~TlvMes(){
	if(baseASN1 != NULL){
		delete baseASN1;
		baseASN1 = NULL;
	}
}
