#include <iostream>
#include <stdlib.h>
#include <queue>
#include <pthread.h>

#define NUM 8

class BlockQueue
{
    private:
        std::queue<int> q;
        int _cap;
        pthread_mutex_t lock;
        pthread_cond_t Consume;
        pthread_cond_t Product;
    public:
        BlockQueue(int cap=NUM)
            :_cap(cap)
        {
            pthread_mutex_init(&lock,NULL);
            pthread_cond_init(&Consume,NULL);
            pthread_cond_init(&Product,NULL);

        }

        void PushData(const int& data)
        {
            pthread_mutex_lock(&lock);
            while(_cap==q.size())
            {
                //队列满，通知消费者去消费
                pthread_cond_signal(&Consume);
                std::cout<<"queue full,notify consume data,product stop."<<std::endl;
                pthread_cond_wait(&Product,&lock);//生产者等待
            }
            q.push(data);
            pthread_mutex_unlock(&lock);
       }

        void PopData(int data)
        {
            pthread_mutex_lock(&lock);
            while(0==q.size())
            {
                //队列空，通知生产者
                pthread_cond_signal(&Product);
                std::cout<<"queue empty,notify product data,consume stop."<<std::endl;
                pthread_cond_wait(&Consume,&lock);//消费者等待
            }
            data=q.front();
            q.pop();
            pthread_mutex_unlock(&lock);
        }

        ~BlockQueue()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&Consume);
            pthread_cond_destroy(&Product);
        }
};

void* consumer(void *arg)
{
    BlockQueue *bqp=(BlockQueue*)arg;
    int data;
    for(;;)
    {
        bqp->PopData(data);
        std::cout<<"Consume data done: "<<data<<std::endl;
    }
}

void* producter(void *arg)
{
    BlockQueue *bqp=(BlockQueue *)arg;
    srand((unsigned long)time(NULL));
    for(;;)
    {
        int data=rand()%1024;
        bqp->PushData(data);
        std::cout<<"Product data done: "<<data<<std::endl;
    }
}

int main()
{
    BlockQueue bq;
    pthread_t c,p;
    pthread_create(&c,NULL,consumer,(void*)&bq);
    pthread_create(&p,NULL,producter,(void*)&bq);

    pthread_join(c,NULL);
    pthread_join(p,NULL);
    return 0;
}
