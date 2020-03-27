#include <iostream>
#include <queue>
#include <stdlib.h>
#include <pthread.h>

#define NUM 8

class BlockQueue
{
    private:
        std::queue<int> q;
        int _cap;
        pthread_mutex_t lock;
        pthread_cond_t full;
        pthread_cond_t empty;

    private:
        bool IsEmpty()
        {
            return (q.size()==0?true:false);
        }

    public:
        BlockQueue(int cap=NUM)
            :_cap(cap)
        {
            pthread_mutex_init(&lock,NULL);
            pthread_cond_init(&full,NULL);
            pthread_cond_init(&empty,NULL);
        }

        void PushData(const int& data)
        {
            pthread_mutex_lock(&lock);
            while()

        }


}
