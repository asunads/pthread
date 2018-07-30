#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;
int thread_num = 8;
int count;
int Iph_index ;
sem_t count_sem;
sem_t barrier_sem[2];

void Iph_barrier()
{
	sem_wait(&count_sem);
	if(count == thread_num-1)
	{
		count = 0;
		int temp = Iph_index;
		for(int i = 1;i<thread_num;++i)
		{
			sem_post(&barrier_sem[temp]);
		}
		sleep(1);
		Iph_index = Iph_index ^ 1;
		sem_post(&count_sem);
	}else{
		count++;
		sem_post(&count_sem);
//		sleep(1);
		sem_wait(&barrier_sem[Iph_index]);
	}
}	
void * worker(void * in)
{
	cout<<"a"<<endl;
	Iph_barrier();
	cout<<"b"<<endl;
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
	sem_init(&count_sem,0,1);
	sem_init(&barrier_sem[0],0,0);
	sem_init(&barrier_sem[1],0,0);
	Iph_index = 0;
}
int main()
{
	cout<<"lets start"<<endl;
	pthread_t threads[thread_num];
	void *p = 0;

	Iph_init();
	cout<<"lets start1"<<endl;
	
	for(int i = 0;i<thread_num;i++)
		pthread_create(&threads[i],0,worker,0);
	for(int i = 0;i<thread_num;++i)
		pthread_join(threads[i],(void **)&p);

	return 0;
}