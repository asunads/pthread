#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;
int thread_num = 8;
int count;
pthread_mutex_t mtx;
pthread_cond_t cond_var;

void Iph_barrier()
{
    pthread_mutex_lock(&mtx);
    count++;
    if(count == thread_num)
    {
        count = 0;
        pthread_cond_broadcast(&cond_var);
    }else{
        while(pthread_cond_wait(&cond_var,&mtx) != 0);
    }
    pthread_mutex_unlock(&mtx);
}

void * worker(void * in)
{
	cout<<"a";
	Iph_barrier();
	cout<<"b";
	Iph_barrier();
	Iph_barrier();
	cout<<"c";
	Iph_barrier();
	Iph_barrier();
	cout<<"d";
	Iph_barrier();
	Iph_barrier();
	cout<<"e";
	Iph_barrier();
	Iph_barrier();
	Iph_barrier();
	Iph_barrier();
	cout<<"f";
	Iph_barrier();
	cout<<endl;
	return (void *)0;
}
void Iph_init()
{
	count =0;
	pthread_mutex_init(&mtx,0);
    pthread_cond_init(&cond_var,0);
}

void Iph_destroy()
{
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond_var);
}

int main()
{
	cout<<"lets start"<<endl;
	pthread_t threads[thread_num];
	void *p = 0;

	Iph_init();

	for(int i = 0;i<thread_num;i++)
		pthread_create(&threads[i],0,worker,0);
	for(int i = 0;i<thread_num;++i)
		pthread_join(threads[i],(void **)&p);

    Iph_destroy();
	return 0;
}
