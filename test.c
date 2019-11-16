//命令行版本的进度条程序
#include<stdio.h>
//只在Linux下有这个文件
#include<unistd.h>
int main()
{
  const char* label="/-\\|";
  char buf[1024]={0};
  int i=0;
  for(;i<100;i++)
  {
    buf[i]='#';
    printf("[%d%%][%c][%s]\r",i,label[i%4],buf);
    fflush(stdout);
    //\n表示换行 
    //\r表示回车
    usleep(100*1000);
    //单位是秒
  }
  return 0;
}
