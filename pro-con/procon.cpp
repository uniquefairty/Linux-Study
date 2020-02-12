#include <stdio.h>
#include <pthread.h>
using namespace std;
#include <iostream>
#include <queue>

#define THREADCOUNT 4

class BlockQueue
{
public:
    BlockQueue(int Capacity)
    {
        _Capacity=Capacity;
        pthread_mutex_init(&_QueueMutex,NULL);
        pthread_cond_init(&_ConsumeCond,NULL);
        pthread_cond_init(&_ProduceCond,NULL);
    }

    ~BlockQueue()
    {
        pthread_mutex_destroy(&_QueueMutex);
        pthread_cond_destroy(&_ConsumeCond);
        pthread_cond_destroy(&_ProduceCond);
    }

    bool IsFull()
    {
        if(_Queue.size()==_Capacity)
        {
            return true;
        }
        return false;
    }

    int Pop(int *Data)
    {
        pthread_mutex_lock(&_QueueMutex);
        while(_Queue.empty())
        {
            pthread_cond_wait(&_ConsumeCond,&_QueueMutex);
        }
        *Data=_Queue.front();
        _Queue.pop();
        pthread_mutex_unlock(&_QueueMutex);
        pthread_cond_signal(&_ProduceCond);
        return 0;
    }

    int Push(int& Data)
    {
        pthread_mutex_lock(&_QueueMutex);
        while(IsFull())
        {
            pthread_cond_wait(&_ProduceCond,&_QueueMutex);
        }
        _Queue.push(Data);
        pthread_mutex_unlock(&_QueueMutex);
        pthread_cond_signal(&_ConsumeCond);

        return 0;
    }

private:
    std::queue<int> _Queue;
    //定义_Queue的容量
    size_t _Capacity;
    //互斥
    pthread_mutex_t _QueueMutex;
    //同步
    pthread_cond_t _ConsumeCond;
    pthread_cond_t _ProduceCond; 
};

void *ConsumeStart(void *arg)
{
    BlockQueue *bq=(BlockQueue*)arg;
    while(1)
    {
        int Data;
        bq->Pop(&Data);
        printf("ConsumeStart[%X][%d]\n",pthread_self(),Data);
    }
    return NULL;
}

void *ProduceStart(void* arg)
{
    BlockQueue* bq=(BlockQueue*)arg;
    int i=0;
    while(1)
    {
        bq->Push(i);
        //该执行流可能被打断
        printf("ProduceStart [%p][%d]\n",pthread_self(),i);
        i++;
    }
    return NULL;

}

int main()
{
    pthread_t Con_tid[THREADCOUNT],Pro_tid[THREADCOUNT];

    int i=0;
    int ret=-1;
    BlockQueue* bq=new BlockQueue(5);
    for(;i<THREADCOUNT;i++)
    {
        ret=pthread_create(&Con_tid[i],NULL,ConsumeStart,(void*)bq);
        if(ret!=0)
        {
            printf("creat thread failed\n");
            return 0;
        }

        ret=pthread_create(&Pro_tid[i],NULL,ProduceStart,(void*)bq);
        if(ret!=0)
        {
            printf("creat thread failed\n");
            return 0;
        }
    }

    for(i=0;i<THREADCOUNT;i++)
    {
        pthread_join(Con_tid[i],NULL);
        pthread_join(Pro_tid[i],NULL);
    }

    delete bq;
    return 0;
}
