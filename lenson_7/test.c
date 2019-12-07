#include<stdio.h>
#include<unistd.h>

int main()
{
  //pid_t和pid_t和int 都是等价的
  pid_t ret=fork();
  //getpid获取进程的id
  //getppid获取父进程的pid
  if(ret>0)
  {
    //父进程
    printf("father:%d\n",getpid());
    while(1)
    {
      sleep(1);
    }
  }else if(ret==0)
  {
    //子进程
    printf("child:%d\n",getpid());
    int count=3;
    while(count>0)
    {
      sleep(1);
      --count;
    }
  }
  else{
    //创建失败
    perror("fork");
  }
 // printf("pid:%d,ppid:%d,ret:%d\n",getpid(),getppid(),ret);
  return 0;
}
