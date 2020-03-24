#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <glib.h>
#include <stdio.h>
#include <string>
#include <stdlib>
#include "cpu_utils.h"
#include "cpubits.h"

typedef struct{
	double result;
	double elapsed_time;
	int threads_used;
	int revision;
	char extra[256];
}bench_value;
#define EMPTY_BENCH_VALUE {-1.0f,0,0,-1};

char* bench_value_to_str(bench_value r);
bench_value bench_value_from_str(const char* str);

bench_value benchmark_parallel_for(gint n_threads,guint start,guint end,gpointer callback,gpointer callbaek_data);

bench_value benchmark_parallel(gint n_threads,gpointer callback,gpointer callback_data);

bench_value benchmark_crunch_for(float seconds,gint n_threads,gpointer callback,gpointer callback_data);


gchar *get_test_data(gsize min_size);
char *md5_digest_str(const char *data,unsigned int len);

#endif
