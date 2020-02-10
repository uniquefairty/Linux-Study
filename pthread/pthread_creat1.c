#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *rout(void *arg)
{
    int i;
    for(;;)
    {
        printf("I am thread1\n");
        sleep(1);
    }
}

int main()
{
    pthread_t tid;
    int ret=0;
    if((ret==pthread_create(&tid,NULL,rout,NULL))!=0)
    {
        fprintf(stderr,"pthread_creat:%s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }
    int i=0;
    for(;;)
    {
        printf("I an main thread\n");
        sleep(1);
    }


    return 0;
}
