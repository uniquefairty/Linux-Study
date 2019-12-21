/*进程等待*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<wait.h>
#include<errno.h>

int main()
{
  int pid=fork();
  if(pid<0)
  {
    perror("fork error");
    exit(-1);
  }else if(pid==0)
  {
    sleep(5);
    exit(0);
  }
  //pid_t wait(int *status);
  //阻塞等待任意一个子进程退出；如果当前没有子进程退出，则一直等待
  //status：用于获取子进程的退出码；不关注则置空即可
  //返回值：退出的子进程的pid
  //wait(NULL);
  int ret=waitpid(pid,NULL,0);
  if(ret<0)
  {
    perror("waitpid error");
    return -1;
  }
  printf("pid:%d-%d\n",ret,pid);
  while(1)
  {
    printf("------------i am parent!!\n");
    sleep(1);
  }
  return 0;
}
