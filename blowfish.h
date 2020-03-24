#ifndef __BLOWFISH_H__
#define __BLOWFISH_H__

typedef struct{
	unsigned long P[16+2];
	unsigned long S[4][256];
}BLOWFISH_CTX;

void Blowfish_Init(BLOWFISH_CTX *ctx,unsigned char * key,int keylen);
void Blowfish_Encrypt(BLOWFISH_CTX *ctx,unsigned long *xl,unsigned long *xr);
void Blowfish_Decrypt(BLOWFISH_CTX *ctx,unsigned long *xl,unsigned long *xr);


#endif
