#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
  int fd=open("./log",O_RDWR|O_CREAT);
  if(fd<0)
  {
    perror("open");
    return 1;
  }
  close(1);
  //int dup2(int oldfd, int newfd);
  //newfd:会关闭newfd这个文件的描述符，并且将newfd拷贝oldfd；
  //oldfd：要重定向哪个文件描述符
  dup2(fd,1);
  for(;;)
  {
    char buf[1024]={0};
    ssize_t read_size=read(0,buf,sizeof(buf)-1);

    if(read_size<0)
    {
      perror("read");
      break;
    }
    printf("%s",buf);
    fflush(stdout);
  }
  return 0;
}

