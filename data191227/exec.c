/*exec函数族基本使用*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<wait.h>

int main()
{
  int pid=fork();
  if(pid==0)
  {
    printf("i am child!\n");
    //execl("/bin/ls","ls","-l","-a",NULL);
    //execl("/bin/lalsdkf","ls","-l","-a",NULL);
    //execlp("ls","ls","-l",NULL);
    char *argv[]={"ls","-l","-a",NULL};
    char *env[]={"PATH=./TEST","HOME=~",NULL};
    execve("/bin/ps",argv,env);
    perror("execl error");
    exit(0);
  }
  wait(NULL);
  printf("hello ~~bit\n");
  return 0;
}
