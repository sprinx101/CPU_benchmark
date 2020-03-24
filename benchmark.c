#include "/opt/CPU_benchmark/include/benchmark.h"

typedef struct _parallelBenchTask ParallelBenchTask;

struct _ParallelBenchTask{
	gint	thread_number;
	guint	start,end;
	gpointer	data,callback;
	int *stop;
};


static gpointer benchmark_crunch_for_dispatcher(gpointer data)
{
	ParallelBenchTask	*pbt = (ParallelBenchTask *)data;
	gpointer (*callback)(void *data,gint thread_number);
	gpointer return_value = g_malloc(sizeof(double));
	int count = 0;

	if((callback = pbt->callback))
	{
		while(!*pbt->stop)
		{
			callback(pbt->data);
			if(!*pbt->stop)
			  count++;
		}
	}else{
		/////
		DEBUG("this is thread %p;callback is NULL and it should't be!",g_thread_self());
	}
	g_free(pbt);

	*(double*)return_value = (double)count;
	return return_value;
}



bench_value benchmark_crunch_for(float seconds,gint n_threads,gpointer callback,gpointer callback_data)
{
	int cpu_procs,cpu_cores,cpu_threads,thread_number,stop = 0;
	GSList *threads = NULL,*t;
	GTimer *timer;
	bench_value ret = EMPTY_BENCH_VALUE;

	timer = g_timer_new();

	cpu_procs_cores_threads(&cpu_procs,&cpu_cores,&cpu_threads);
	if(n_threads > 0)
	  ret.threads_used = n_threads;
	else if(n_threads < 0)
	  ret.threads_used = cpu_cores;
	else
	  ret.threads_used = cpu_threads;

	g_timer_start(timer);
	for(thread_number = 0;thread_number < ret.thread_used;thread_number++)
	{
		ParallelBenchTask *pbt = g_new0(ParallelBenchTask,1);
		GThread *thread;

		/////
		DEBUG("launching thread %d",thread_number);

		pbt->thread_number = thread_number;
		pbt->data = callback_number;
		pbt->callback = callback;
		pbt->stop = &stop;

		thread = g_thread_new("dispatcher",(GThreadFunc)benchmark_crunch_for_dispatcher,pbt);
		threads = g_slist_prepend(threads,thread);

		/////
		DEBUG("thread %d launched as context %p",thread_number,thread);
	}

	g_usleep(seconds * 1000000);

	stop=1;
	g_timer_stop(timer);

	ret.result = 0;
	DEBUG("waiting for all threads to finish");
	/////
	for (t = threads; t ;t = t->next)
	{
		DEBUG("waiting for thread with context %p",t->data);
		gpointer *rv = g_thread_join((GThread *)t->data);
		ret.result += *(double*)rv;
		g_free(rv);
	}
	ret.elapsed_time = g_timer_elapsed(timer,NULL);

	g_slist_free(threads);
	g_timer_destory(timer);

	return ret;
}



static gpointer benchmark_parallel_for_dispatcher(gpointer data)
{
	ParallelBenchTask	*pbt = (ParallelBenchTask *)data;
	gpointer	(*callback)(unsigned int start,unsigned int end,void *data,gint thread_number);
	gpointer		return_value = NULL;

	if((callback = pbt->callback))
	{
		/////
		DEBUG("this is thread %p,items %d -> %d,data %p",g_thread_self(),pbt->start,pbt->end,pbt->data);
		return_value=callback(pbt->start,pbt->end,pbt->data,pbt->thread_number);
		/////
		DEBUG("This is thread %p ;return_value is %p",g_thread_self(),return_value);
	}
	else{
		/////
		DEBUG("This is thread %p;callback is NULL and it should't be!",g_thread_self());
	}
	g_free(pbt);

	return return_value;
}



bench_value benchmark_parallel_for(gint n_threads,guint start,guint end,gpointer callback,gpointer callback_data)
{
	gchar	*temp;
	int 	cpu_procs,cpu_cores,cpu_threads;
	guint	iter_per_thread,iter,thread_number=0;
	GSList 	*threads=NULL,*t;
	GTimer	*timer;

	bench_value ret = EMPTY_BENCH_VALUE;
	timer = g_timer_new();
	cpu_proc_cores_threads(&cpu_procs,&cpu_cores,&cpu_threads);
	
	if(n_threads > 0)
	  ret.threads_used = n_threads;
	else if(n_threads < 0)
	  ret.threads_used = cpu_cores;
	else
	  ret.threads_used = cpu_threads;

	while(ret.threads_used > 0)
	{
		iter_per_thread = (end - start)/ret.threads_used;
		if(iter_per_thread == 0)
		{
			/////
			DEBUG("not enough items per thread;disabling one thread");
			ret.threads_used--;
		}else{
			break;
		}
	}

	/////
	DEBUG("Using %d threads across %d logical processors;processing %d elements (%d per thread)",ret.threads_used,cpu_threads,(end - start),iter_per_thread);

	g_timer_start(timer);
	for(iter = start,iter < end;)
	{
		ParallelBenchTask *pbt=g_new0(ParallelBenchTask,1);
		GThread *thread;
		guint ts = iter,te = iter + iter_per_thread;
		
		if(end-te < iter_per_thread)
		  te=end;
		iter=te;

		/////
		DEBUG("launching thread %d",1 + thread_number);

		pbt->thread_number = thread_number++;
		pbt->start		   = ts;
		pbt->end		   = te - 1;
		pbt->data		   = callback_data;
		pbt->callback	   = callback;

		thread = g_thread_new("dispatcher",(GThreadFunc)benchmark_parallel_for_dispatcher,pbt);
		threads = g_slist_prepend(threads,thread);

		/////
		DEBUG("thread %d launched as context %p",thread_number,thread);
	}

	/////
	DEBUG("waiting for all threads to finish");
	for(t = threads; t ;t = t->next)
	{
		/////
		DEBUG("waiting for thread with context %p",t->data);
		gpointer *rv = g_thread_join((GThread *)t->data);
		if(rv)
		{
			if(ret.result == -1.0)
			  ret.result=0;
			ret.result += *(double*)rv;
		}
		g_free(rv);
	}


	g_timer_stop(timer);
	ret.elapsed_time = g_timer_elapsed(timer,NULL);

	g_slist_free(threads);
	g_timer_destory(timer);

	/////
	DEBUG("Finishing; all threads took %f seconds to finish",ret.elapsed_time);
	return ret;
}





























