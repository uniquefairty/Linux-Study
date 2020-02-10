#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>

int ticket=100;
pthread_mutex_t mutex;

void *rout(void *arg)
{
    char *id=(char*)arg;
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(ticket>0)
        {
            usleep(1000);
            printf("%s sells ticket:%d\n",id,ticket);
            ticket--;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    return 0;
}
int main()
{
    pthread_t t1,t2,t3,t4;

    pthread_mutex_init(&mutex,NULL);//创建线程之前对互斥量初始化
    
    pthread_create(&t1,NULL,rout,"thread 1");
    pthread_create(&t2,NULL,rout,"thread 2");
    pthread_create(&t3,NULL,rout,"thread 3");
    pthread_create(&t4,NULL,rout,"thread 4");

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
