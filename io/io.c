/*
 *int open(const char *pathname, int flags);
 *int open(const char *pathname, int flags, mode_t mode)
 *int creat(const char *pathname, mode_t mode);
 *
 *ssize_t read(int fd, void *buf, size_t count);
 * */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>


#if 0
//写文件操作
int main()
{
  int fd=open("myfile",O_WRONLY|O_CREAT,0664);
  if(fd<0)
  {
    perror("open");
    return 1;
  }

  int count=5;
  const char* msg="hello bit!\n";
  int len=strlen(msg);

  while(count--)
  {
    //ssize_t write(int fd, const void *buf, size_t count);
    //fd:打开文件返回的操作句柄-->文件描述符
    //buf：要写入的数据
    //count:要写入的数据长度
    //返回值：实际的写入长度（字节）  失败 -1
    write(fd,msg,len);
  }
  close(fd);

  return 0;
}
#endif


#if 0 
//读文件
int main()
{
  int fd=open("myfile",O_RDONLY);
  if(fd<0)
  {
    perror("open error");
    return 1;
  }

  const char*msg="hello bit~\n";
  char buf[1024];
  while(1)
  {
    ssize_t s=read(fd,buf,strlen(msg));
    if(s>0)
    {
      printf("%d\n",s);
      printf("%s",buf);
    }
    else{
      break;
    }
  }
  close(fd);
  return 0;
}
#endif

#if 0
int main()
{
  char buf[1024];
  ssize_t s=read(0,buf,sizeof(buf));
  if(s>0)
  {
    buf[s]=0;
    write(1,buf,strlen(buf));
    write(2,buf,strlen(buf));
  }
  return 0;
}
#endif

int main()
{
  int fd=open("tmp.txt",O_RDWR|O_CREAT,0664);
  if(fd<0)
  {
    perror("open");
    return 0;
  }
  printf("fd=[%d]\n",fd);
  const char * lp="linux";
  int ret=write(fd,lp,strlen(lp));
  printf("ret=[%d]\n",ret);

  lseek(fd,0,SEEK_SET);

  char arr[1024]={0};
  ret=read(fd,arr,sizeof(arr)-1);
  printf("read ret=[%d][%s]\n",ret,arr);
  close(fd);
  return 0;
}
