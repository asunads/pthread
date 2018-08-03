#include <iostream>
#include <pthread.h>
using namespace std;
int thread_num = 4;
pthread_mutex_t mtx;
pthread_cond_t read_cond,write_cond;
int write_num,read_num;

void read_lock()
{
	pthread_mutex_lock(&mtx);
	while(write_num > 0) pthread_cond_wait(&write_cond,&mtx);
	read_num++;
	pthread_mutex_unlock(&mtx);
	cout<<"r";
	pthread_mutex_lock(&mtx);
	read_num--;
	if(read_num == 0)
		pthread_cond_broadcast(&read_cond);
	pthread_mutex_unlock(&mtx);
}
void write_lock()
{
	pthread_mutex_lock(&mtx);
	write_num++;
	while(read_num > 0) pthread_cond_wait(&read_cond,&mtx);
	cout<<"w";
	write_num--;
	if(write_num == 0)
		pthread_cond_broadcast(&write_cond);
	pthread_mutex_unlock(&mtx);
}
void * worker(void *in)
{
	for(int i = 0;i<10000;i++)
	{
		if(i % 30 == 0){
			write_lock();
		}else{
			read_lock();
		}
	}
	write_lock();
	return (void *)0;
}

void Iph_init()
{
	write_num = read_num = 0;
	pthread_mutex_init(&mtx,0);
	pthread_cond_init(&read_cond,0);
	pthread_cond_init(&write_cond,0);
}

void Iph_finalize()
{
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&read_cond);
	pthread_cond_destroy(&write_cond);
}
int main()
{
	Iph_init();
	pthread_t threads[thread_num];
	int Iph_arg[thread_num];
	int p = 0;

	for(int i = 0;i<thread_num;i++){
		Iph_arg[i] = i;
		pthread_create(&threads[i],0,worker,&Iph_arg[i]);
	}
	for(int i =0;i<thread_num;i++)
	{
		pthread_join(threads[i],(void **)&p);
	}

	Iph_finalize();
	return 0;
}