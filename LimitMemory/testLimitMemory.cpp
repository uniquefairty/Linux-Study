#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <errno.h>
#include <iostream>
//用于内存不足的情况下程序退出
static char *reservedMemoryForExit;

void outOfMemoryHandler()
{
    static bool isInHandler=false;
    if(isInHandler)
        return;
    isInHandler=true;

    //释放保留内存，一面程序退出过程中再次出现内存不足
    delete[] reservedMemoryForExit;
    reservedMemoryForExit=NULL;
    printf("Memory Not Enough exit");
    abort();
}

void initNewOperHandler()
{
    const int RESERVED_MEM_SIZE=1024*1024*2;
    std::set_new_handler(outOfMemoryHandler);
    //用于内存不足的情况下程序退出
    reservedMemoryForExit=new char[RESERVED_MEM_SIZE];
}

int main(void)
{
    int nMemoryLimit=1024*1024*20;//5M

    struct rlimit64 memoryL;

    getrlimit64(RLIMIT_AS,&memoryL);
    printf("before set men:%lu,%lu\r\n",(unsigned long)memoryL.rlim_cur,(unsigned long)memoryL.rlim_max);

    memoryL.rlim_cur=nMemoryLimit;
    memoryL.rlim_max=nMemoryLimit;
    setrlimit64(RLIMIT_AS,&memoryL);

    getrlimit64(RLIMIT_AS,&memoryL);
    printf("after set mem:%lu,%lu\r\n", (unsigned long)memoryL.rlim_cur, (unsigned long)memoryL.rlim_max); 

    initNewOperHandler();
    
    int i=0;
    while(1)
    {
        i++;
        //当进程内存达到最大值，malloc calloc返回NULL记录error=ENOMEM
        errno=0;
        char *psString=(char *)calloc(1,1024);
        if(NULL==psString)
        {
            printf("errno=%d,ENOMEM=%d\r\n",errno,ENOMEM);
        }
        else
        {
            printf("success,%d\r\n",i);
        }

    }
    return 0;
}


