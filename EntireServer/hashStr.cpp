#include "hashStr.h"

HashStr::HashStr(){

}

int HashStr::hashlizeStr(char *dest, char *src, int srcLen){
/*
 * unsigned char *HMAC(const EVP_MD *evp_md, const void *key, 
 * int key_len,
 * const unsigned char *d, size_t n, unsigned char *md,
 * unsigned int *md_len);
 */
	const char *key = "lovingX123";
	int key_len = strlen(key);
	unsigned char md[SHA256_DIGEST_LENGTH] = "";
	unsigned int md_len;
	HMAC(EVP_sha256(), (void *)key, key_len, 
			(unsigned char *)src, (size_t)srcLen, 
			md, &md_len);
	int i = 0;
	for(i = 0; i < SHA256_DIGEST_LENGTH; i++){
		sprintf(dest + i*2, "%02x", md[i]);
	}

	return 0;
}

HashStr::~HashStr(){

}
