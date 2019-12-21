#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

int main()
{
  int i=0;
  for(i=0;i<256;i++)
  {
    //char *strerror(int errnum);
    //通过错误编号获取错误描述信息
    printf("error:%s\n",strerror(i));
    //perror("error");
  }
 // int pid=fork();
 // if(pid<0)
  {
    //每次调用系统调用接口，不管对错都会重置errno全局变量
    //perror("fork error");
    //printf("fork error:%s\n",strerror(errno));
  }
  printf("hello~~");
  return 0;
}
