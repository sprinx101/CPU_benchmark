#ifndef __CPU_UTILS_H__
#define __CPU_UTILS_H__

#include <glib.h>
#include <stdio.h>
#include <stdlib>

gchar *get_cpu_str(const gchar* file,gint cpuid);
gint get_cpu_int(const char * item,int cpuid,int null_val);

#endif
