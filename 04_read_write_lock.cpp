#include <iostream>
#include <vector>
#include <pthread.h>
#include <random>
#include <algorithm>


using namespace std;
vector<int> vec;
pthread_rwlock_t rwlock;
int thread_num = 8;
void *worker(void * in)
{
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,10000000);
    int temp;
    for(int i = 0;i<1000;i++)
    {
        pthread_rwlock_rdlock(&rwlock);
        //for(int i = 0;i<vec.size()-1;i++)
        {
            //if(vec[i]<vec[i+1]);

        }
        cout<<vec.size()<<endl;
        pthread_rwlock_unlock(&rwlock);
        pthread_rwlock_wrlock(&rwlock);
        vec.push_back(distribution(generator));
       // sort(vec.begin(),vec.end());
        pthread_rwlock_unlock(&rwlock);

    }
    return (void *)0;
}

int main()
{
    pthread_rwlock_init(&rwlock,0);
	pthread_t threads[thread_num];
    void *p = 0;

	for(int i = 0;i<thread_num;i++)
		pthread_create(&threads[i],0,worker,0);
	for(int i = 0;i<thread_num;++i)
		pthread_join(threads[i],(void **)&p);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
