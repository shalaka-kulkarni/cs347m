#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

pthread_mutex_t mutex[10];
pthread_cond_t cond[10];
pthread_t slave[5];

struct arg_struct 
{
    int thread_id;
    int fl_no;
    int op;
};

void *thread_func(void *arguments)
{
	struct arg_struct *args = (arg_struct*)arguments;
	int fl_no = args->fl_no;
	int thread_id = args->thread_id;
	int op = args->op;

	pthread_mutex_lock(&mutex[fl_no]);
	pthread_cond_wait(&cond[fl_no], &mutex[fl_no]);
	cout<<"In thread "<<thread_id<<endl;
	for(int i=0;i<100;i++)
	{
		cout<<"Delay "<<i<<" in thread "<<thread_id<<endl;
	}
	pthread_mutex_unlock(&mutex[fl_no]);
	pthread_cond_signal(&cond[fl_no]);
}

int main()
{
	cout<<"Entered main"<<endl;
	struct arg_struct args;
	for(int i=0;i<10;i++)
	{
		pthread_mutex_init(&mutex[i], NULL);
	}
	for(int i=0;i<5;i++)
	{
		args.thread_id = i+1;
		args.op = 1;
		args.fl_no = 0;
		cout<<"Creating thread "<<(i+1)<<endl;
		int rc = pthread_create(&slave[i], NULL, thread_func, (void*)&args);
		if (rc)
		{
	 		cout<<"ERROR; return code from pthread_create() is "<<rc<<endl;
		}

	}

	return 0;
}
