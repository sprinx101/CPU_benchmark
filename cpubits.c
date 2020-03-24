#include "/opt/CPU_benchmark/include/cpubits.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint32_t cpubits_count(cpubits *b)
{
	static const uint32_t max = CPUBITS_SIZE * 8;
	uint32_t count = 0,i = 0;
	while( i < max )
	{
		count += CPUBITS_GET(b,i);
		++i;
	}
	return count;
}

int cpubits_min(cpubits *b)
{
	int i = 0;
	while(i<CPUBITS_SIZE * 8){
		if(CPUBITS_GET(b,i))
		  return i;
		++i;
	}
	return -1;
}

int cpubits_max(cpubits *b)
{
	int i = CPUBITS_SIZE * 8 - 1;
	while(i >= 0)
	{
		if(CPUBITS_GET(b,i))
		  return i;
		--i;
	}
	return i;
}

int cpubits_next(cpubits *b,int start,int end)
{
	start ++;
	if(start >= 0)
	{
		int i = start;
		if(end == -1)
		  end = CPUBITS_SIZE * 8;
		while(i < end)
		{
			if(CPUBITS_GET(b,i))
			  return i;
			++i;
		}
	}
	return -1;
}


cpubits *cpubits_from_str(char *str)
{
	char *v, *nv, *hy;
	int r0,r1;
	cpubits *newbits = malloc(CPUBITS_SIZE);
	if(newbits)
	{
		memset(newbits,0,CPUBITS_SIZE);
		if(NULL != str)
		{
			v=(char*)str;
			while( *v != 0)
			{
				nv = strchr(v,',');
				if(nv == NULL) nv=strchr(v,0);
				hy=strchr(v,'-');
				if(hy && hy < nv)
				{
					r0=strtol(v,NULL,0);
					r1=strtol(hy+1,NULL,0);
				}
				else{
					r0=r1=strtol(v,NULL,0);
				}
				for(;r0 <= r1;r0++)
				{
					CPUBITS_SET(newbits,r0);
				}
				v = (*nv == ',') ? nv+1 :nv;
			}
		}
	}
	return newbits;
}


char *cpubits_to_str(cpubits *bits,char *str,int max_len)
{
	static const uint32_t max = CPUBITS_SIZE * 8;
	uint32_t i = 1,seq_start = 0,seq_last = 0,seq = 0,l = 0;
	char buffer[65536] = "";
	if(CPUBITS_GET(bits,0))
	{
		seq = 1;
		strcpy(buffer, "0");
	}
	while(i < max)
	{
		if(CPUBITS_GET(bits,i))
		{
			seq_last = i;
			if(!seq)
			{
				seq = 1;
				seq_start = i;
				l = strlen(buffer);
				sprintf(buffer + l,"%s%d",l ? "," : "",i);
			}
		}else{
			if(seq && seq_last != seq_start)
			{
				l = strlen(buffer);
				sprintf(buffer + l,"-%d",seq_last);
			}
			seq = 0;
		}
		i++;
	}
	if(NULL == str)
	  return strdup(buffer);
	else{
		strncpy(str,buffer,max_len);
		return str;
	}
}

