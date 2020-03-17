#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *rout(void *arg)
{
    int i=0;
    for(;;)
    {
        printf("I am thread1\n");
        sleep(1);
    }
}

int main(void)
{
    pthread_t tid;
    int ret=pthread_create(&tid,NULL,rout,NULL);
    if(0!=ret)
    {
        fprintf(stderr,"pthread_create:%s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }

    int i;
    for(;;)
    {
        printf("I an main thread\n");
        sleep(1);
    }
}
