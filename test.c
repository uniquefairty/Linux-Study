//命令行版本的进度调程序
#include<stdio.h>
//只有Linux下才有的文件
#include<unistd.h>

int main()
{
  //#表示进度条
  const char * label="/-\\|";
  char buf[1024]={0};
  int i=0;
  for(;i<100;++i)
  {
    buf[i]='#';
    printf("[%d%%][%c][%s]\r",i,label[i%4],buf);
    //\n换行
    //\r回车
    fflush(stdout);
    //单位是秒
    usleep(100*1000);
  }
}
