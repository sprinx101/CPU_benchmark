#ifndef __CPUBITS_H__
#define __CPUBITS_H__

#include<stdint.h>

#define CPUBITS_SIZE 4096
#define CPUBITS_SET(BITS,BIT) ((BITS)[(BIT)/32] |= (1 << (BIT)%32))
#define CPUBITS_GET(BITS,BIT) (((BITS)[(BIT)/32] & (1 << (BIT)%32)) >> (BIT)%32)
#define CPUBITS_CLEAR(BITS) memset((BITS),0,CPUBITS_SIZE)

typedef uint32_t cpubits;
uint32_t cpubits_count(cpubits *b);
int cpubits_min(cpubits *b);
int cpubits_max(cpubits *b);
int cpubits_next(cpubits *b,int start,int end);


#endif
