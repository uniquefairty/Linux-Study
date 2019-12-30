#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int g_val=100;

int main()
{
    int fd[2];
    int ret=pipe(fd);
    if(ret<0)
    {
        return ret;
    }

    //如果读端不读，写端一只写，则最后会将管道写满，并且进入阻塞状态
  //  while(1)
  //  {
  //      write(fd[1],"1",1);
  //  }
  
    //如果写端不写，则读端会陷入阻塞
    char buf[1024]={0};
    int ret_size=read(fd[0],buf,sizeof(buf)-1);
    printf("ret_size:%d",ret_size);


    //如果当前把写端关闭，读端去读，则若存在数据，read返回，不会阻塞，进程继续
    //int count=10;
    //while(count--)
    //{
    //    write(fd[1],"a",1);
    //}
    //close(fd[1]);

    //char buf[1024]={0};
    //int read_size=read(fd[0],buf,sizeof(buf)-1);
    //printf("[%d]-[%s]\n",read_size,buf);
    //return 0;
    

    //如果把读端关闭fd[0]关闭，在往写端去写,write
    //write操作会产生信号SIGPIPE，进而可能导致write进程退出
   // close(fd[0]);
   // write(fd[1],"jiangliang",10);
   // while(1)
   // {
   //     printf("hehehe\n");
   // }

    return 0;
}
