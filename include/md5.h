#ifndef __MD5_H
#define __MD5_H

struct MD5Context{
	unsigned long buf[4];
	unsigned long bits[2];
	unsigned char in[64];
};

void MD5Init(struct MD5Context *context);
void MD5Update(struct MD5Context *context,unsigned char const *buf,unsigned len);
void MD5Final(unsigned char digest[16],struct MD5Context *context);
void MD5Transform(unsigned long buf[4],const unsigned char in[64]);

#endif
