#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
  char *env=getenv("myenv");
  if(env)
  {
    printf("%s\n",env);
  }
  return 0;
}

/*环境变量的获取
int main(int argc,char *argv[],char *env[])
{
  //3.系统调用获取
      printf("%s\n",getenv("PATH"));
  //2.通过第三方便量environ获取
 // extern char **environ;
 // int i=0;
 // for(;environ[i];i++)
 // {
 //   printf("environ[%d]=%s\n",i,environ[i]);
// }

  //1.命令行第三个参数
//  int i=0;
//  for(;env[i]!=NULL;i++)
//  {
//    printf("env[%d]=%s\n",i,env[i]);
//  }
  return 0;
}
*/
