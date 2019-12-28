#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>

#if 0
//文件描述符的分配原则
int main()
{
  close(0);
  //close(1);
  int fd=open("myfile",O_RDONLY);
  if(fd<0)
  {
    perror("open");
    return 1;
  }
  printf("fd:%d\n",fd);
  close(fd);
  return 0;
}
#endif

int main()
{
  close(1);
  int fd=open("myfile",O_WRONLY|O_CREAT,0644);
  if(fd<0)
  {
    perror("open");
    return 1;
  }
  printf("fd:%d\n",fd);
  fflush(stdout);
  close(fd);
  exit(0);
}
 



