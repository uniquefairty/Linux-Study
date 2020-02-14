#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>

#define SIZE 4
#define THREADCOUNT 4

class RingQueue
{
    public:
        RingQueue()
            :_Vec(SIZE)
        {
            _Capacity=SIZE;
            _PosWrite=0;
            _PosRead=0;

            //初始化同步的信号量
            //生产者--我们提供的空间大小
            sem_init(&_ProSem,0,SIZE);
            //消费者--当前有多少资源可以消费
            sem_init(&_ConSem,0,0);

            //初始化互斥
            sem_init(&_LockSem,0,1);
        }

        ~RingQueue()
        {
            sem_destroy(&_ProSem);
            sem_destroy(&_ConSem);
            sem_destroy(&_LockSem);
        }

        void Push(int& Data)
        {
            //若在sem_wait(&_ProSem);前进行加锁sem_wait(&_LockSem);
            //sem_wait(&_ProSem);内部并没有sem_post(&_LockSem);功能
            //如果现在需要往_Vec循环队列中插入数据
            //循环队列空间已经全部被插入，没有空间
            //这时就会卡在sem_wait(&_ProSem);阻塞等待 消费者来通知进行生产
            //但是这时生产者把锁资源拿着，
            //消费者想要消费数据的时候，拿不到互斥锁资源_LockSem;
            sem_wait(&_ProSem);

            sem_wait(&_LockSem);
            _Vec[_PosWrite]=Data;
            _PosWrite=(_PosWrite+1)%_Capacity;
            sem_post(&_LockSem);

            //对资源进行+1操作，并且唤醒消费者
            sem_post(&_ConSem);
        }

        void Pop(int *Data)
        {
            sem_wait(&_ConSem);
            
            sem_wait(&_LockSem);
            *Data=_Vec[_PosRead];
            _PosRead=(_PosRead+1)%_Capacity;
            sem_post(&_LockSem);

            sem_post(&_ProSem);
        }
    private:
        std::vector<int> _Vec;
        size_t _Capacity;
        int _PosWrite;
        int _PosRead;
        //同步功能的信号量
        sem_t _ProSem;//生产者的信号量
        sem_t _ConSem;//消费者的信号量
        //实现互斥
        sem_t _LockSem;
};

void* ProStart(void* arg)
{
    RingQueue* rq=(RingQueue*)arg;
    int i=0;
    while(1)
    {
        rq->Push(i);
        printf("ProStart make data[%p][%d]\n",pthread_self(),i);
        i++;
    }
    return NULL;
}

void* ConStart(void* arg)
{
    RingQueue* rq=(RingQueue*)arg;
    int Data;
    while(1)
    {
        rq->Pop(&Data);
        printf("ConStart consume data [%p][%d]\n",pthread_self(),Data);
    }
    return NULL;
}
int main()
{
    pthread_t Pro_tid[THREADCOUNT],Con_tid[THREADCOUNT];
    int i=0;
    int ret=-1;
    RingQueue* rq=new RingQueue();
    for(;i<THREADCOUNT;i++)
    {
        ret=pthread_create(&Pro_tid[i],NULL,ProStart,(void*)rq);
        if(ret!=0)
        {
            printf("creat thread failed\n");
            return 0;
        }

        ret=pthread_create(&Con_tid[i],NULL,ConStart,(void*)rq);
        if(ret!=0)
        {
            printf("creat thread failed\n");
            return 0;
        }
    }

    for(i=0;i<THREADCOUNT;i++)
    {
        pthread_join(Pro_tid[i],NULL);
        pthread_join(Con_tid[i],NULL);
    }
    delete rq;
    return 0;
}

