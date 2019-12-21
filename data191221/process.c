#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

/*
int g_val=0;

int main()
{
  pid_t id=fork();
  if(id<0)
  {
    perror("fork");
    return 0;
  }else if(id==0)
  {
    //child
    g_val=100;
    printf("child[%d]:%d:%p\n",getpid(),g_val,&g_val);
  }else{
    //parent
    sleep(3);
    printf("parent[%d]:%d:%p\n",getpid(),g_val,&g_val);
  }
  sleep(1);
  return 0;
}
*/




int main(void)
{
  pid_t pid;
  printf("Before:pid is %d\n",getpid());

  if((pid=fork()==-1))
    perror("fork()"),exit(1);
  printf("After:pid is %d,fork return %d\n",getpid(),pid);
  sleep(1);
  return 0;
}
