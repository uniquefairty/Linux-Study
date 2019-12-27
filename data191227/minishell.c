#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<wait.h>
#include<ctype.h>
#include<errno.h>
#include<string.h>

int main()
{
  while(1)
  {
    char buf[1024]={0};
    printf("[user@localhost]$ ");
    fflush(stdout);
    //ls -l \n
    if(scanf("%[^\n]%*c",buf)!=1)
    {
      getchar();
      continue;
    }
//    printf("buf:[%s]\n",buf);
    //[  ls  -l  ]-->[ls]+[-l]
    int argc=0;
    char *argv[32];
    char *ptr=buf;
    while(*ptr!='\0')
    {
      //将指针走到非空白字符处
      if(!isspace(*ptr))
      {
        argv[argc]=ptr;
        argc++;
        //将ls走完，认为ls是一个完整的字符串
        //不能将l作为第0个参数
        while(!isspace(*ptr)&&*ptr!='\0')
        {
          ptr++;
        }
        //再ls之后添加一个字符串结尾标志
//        printf("argv[%d]=[%s]\n",argc,argv[argc]);
        *ptr='\0';
      }
      ptr++;
    }
    //argv[]={"ls","-l",NULL};
    argv[argc]=NULL;
    //       int chdir(const char *path);
    if(strcmp(argv[0],"cd")==0)
    {
      //int chdir(const char *path);
      //改变当前工作路径
      chdir(argv[1]);
      continue;
    }

    int pid=fork();
    if(pid<0)
    {
      perror("fork error");
      return -1;
    }
    else if(pid==0)
    {
      execvp(argv[0],argv);
      exit(-1);
    }
    wait(NULL);

  }
  return 0;
}
