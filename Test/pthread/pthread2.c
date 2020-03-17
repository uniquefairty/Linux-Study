#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *thread1(void *arg)
{
    printf("thread 1 returning...\n");
    int *p=(int *)malloc(sizeof(int));
    *p=1;
    return (void*)p;
}

void *thread2(void *arg)
{
    printf("thread 2 exiting...\n");
    int *p=(int *)malloc(sizeof(int));
    *p=2;
    pthread_exit((void*)p);
}

void *thread3(void *arg)
{
    while(1)
    {
        printf("thread 3 is running...\n");
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid;
    void *ret;

    //thread 1 return 
    pthread_create(&tid,NULL,thread1,NULL);
    pthread_join(tid,&ret);//return 返回：ret存放的是thread线程函数的返回值
    printf("thread return ,thread id %X,return code:%d\n",tid,*(int*)ret);
    free(ret);

    //thread 2 exit
    pthread_create(&tid,NULL,thread2,NULL);
    pthread_join(tid,&ret);//pthread_exit终止的，ret存放的是pthread_exit的参数
    printf("thread return,tnread id %X,return code:%d\n",tid,*(int*)ret);
    free(ret);

    //thread 3 cancle by other
    pthread_create(&tid,NULL,thread3,NULL);
    sleep(3);
    pthread_cancel(tid);//取消一个任意执行中的线程
    pthread_join(tid,&ret);//pthread_cancle异常终止的，ret存放的是常数PTHREAD_CANCELED
    if(ret==PTHREAD_CANCELED)
    {
        printf("thread return,thread id %X,return code:PTHREAD_CANCELED\n",tid);
    }
    else
    {
        printf("thread return,thread id %X,return code:NULL\n",tid);
    }
}
