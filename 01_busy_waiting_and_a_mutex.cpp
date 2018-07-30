#include <iostream>
#include <pthread.h>
using namespace std;
int thread_num = 8;
int count;
int thread_count,temp = 0;
pthread_mutex_t mtx;

void Iph_set_barrier(int n)
{
	thread_count = n;
}
void test()
{
	temp++;
}
void Iph_barrier()
{
	pthread_mutex_lock(&mtx);
	count++;
	pthread_mutex_unlock(&mtx);

	while(count < thread_count) {
		int temp = 23;
		temp = temp*2;
	}
}
void * worker(void * in)
{
	cout<<"a";
	Iph_barrier();
	cout<<"b";
	return (void *)0;
}
int main()
{
	cout<<"lets start"<<endl;
	pthread_t threads[thread_num];
	count =0;
	int p = 0;
	Iph_set_barrier(8);
	pthread_mutex_init(&mtx,0);
	
	for(int i = 0;i<thread_num;i++)
		pthread_create(&threads[i],0,worker,0);
	for(int i = 0;i<thread_count;++i)
		pthread_join(threads[i],(void **)&p);
	cout<<endl;




	pthread_mutex_destroy(&mtx);
	return 0;
}