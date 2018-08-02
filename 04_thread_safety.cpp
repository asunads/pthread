#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;


int thread_num = 2;
sem_t sems[9];



void * worker(void * in)
{
	char  my_line[400];
	int rank = *(int *)in;
	int next = (rank+1)%thread_num;
 	char *fg_rv;
	char *my_string;
	char * saveptr_p;
	sem_wait(&sems[rank]);
	 fg_rv = fgets(my_line,10, stdin);
	sem_post(&sems[next]);

	while(fg_rv){
		cout<<"rank = "<<rank<<" =  "<<my_line<<endl;
		int count = 0;

		my_string = strtok_r(my_line,"\t\n",&saveptr_p);
		while(my_string != 0)
		{
			count++;
			cout<<"rank = "<<rank<<" = "<<my_string<<endl;
			my_string = strtok_r(0,"\t\n",&saveptr_p);
		}

		sem_wait(&sems[rank]);
		 fg_rv = fgets(my_line,10, stdin);
		sem_post(&sems[next]);
	}

	return (void *)0;
}

int main()
{
	for(int i = 0;i<thread_num;i++)
	{
		if(i == 0)
			sem_init(&sems[i],0,1);
		else
			sem_init(&sems[i],0,0);
	}


	pthread_t threads[thread_num];
	void *p = 0;
	int para[thread_num];

	cout<<"lets start1"<<endl;
	
	for(int i = 0;i<thread_num;i++){
		para[i] = i;
		pthread_create(&threads[i],0,worker,&para[i]);
	}
	for(int i = 0;i<thread_num;++i)
		pthread_join(threads[i],(void **)&p);
	return 0;
}