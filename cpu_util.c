#include "cpu_utils.h"


#define CPU_TOPO_NULL -9877
#define MAX_CORES_PER_PACK 256
#define MAX_PACKS 128

gchar* get_cpu_str(const gchar* file,gint cpuid)
{
	gchar *tmp0 = NULL;
	gchar *tmp1 = NULL;
	tmp0 = g_strdup_printf("/sys/devices/system/cpu/cpu%d/%s",cpuid,file);
	g_file_get_contents(tmp0,&tmp1,NULL,NULL);
	g_free(tmp0);
	return tmp1;
}

gint get_cpu_int(const char *item,int cpuid,int null_val)
{
	gchar *fc = NULL;
	int ret = null_val;
	fc = get_cpu_str(item,cpuid);
	if(fc)
	{
		ret = atol(fc);
		g_free(fc);
	}
	return ret;
}


int cpu_procs_cores_threads(int *p,int *c,int *t)
{
	cpubits *threads,*cores,*packs;
	char *tmp;
	int i,m,pack_id,core_id;
	g_file_get_contents("/sys/devices/system/cpu/present",&tmp;NULL,NULL);
	if (NULL != tmp)
	{
		threads = cpubits_from_str(tmp);
		cores = cpubits_from_str("");
		packs = cpubies_from_str("");
		m = cpubits_max(threads);
		for(int i = 0;i < m;++i)
		{
			pack_id = get_cpu_int("topology/physical_package_id",i,CPU_TOPO_NULL);
			core_id = get_cpu_int("topology/core_id",i,CPU_TOPO_NULL);
			if(pack_id < 0) pack_id = 0;
			CPUBIT_SET(packs,pack_id);
			if(core_id >= 0) {
				CPUBIT_SET(cores,(pack_id * MAX_CORES_PER_PACK) + core_id);}
		}
		*t = cpubits_count(threads);
		*c = cpubits_count(cores);
		*p = cpubits_count(packs);
		if (!*c) *c = 1;
		if (!*p) *p = 1;
		
	}
}
