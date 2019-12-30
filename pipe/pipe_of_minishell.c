#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_CMD 1024
char command[MAX_CMD];
char* pipe_command[1024];
int do_face()
{
    memset(command,0x00,MAX_CMD);
    printf("minishell$");
    fflush(stdout);
    if(scanf("%[^\n]%*c",command)==0)
    {
        getchar();
        return -1;
    }
    return 0;
}
char **do_parse(char *buff)//解析字符串
{
    int argc=0;
    static char*argv[32];
    char *ptr=buff;

    while(*ptr!='\0')
    {
        if(!isspace(*ptr))
        {
            argv[argc++]=ptr;
            while(!isspace(*ptr)&&(*ptr)!='\0')
            {
                ptr++;
            }
            continue;
        }
        *ptr='\0';
        ptr++;
    }
    argv[argc]=NULL;//置最后一个字符为空
    return argv;

}

int do_redirect(char *buff)
{
    char *ptr=buff;
    char *file=NULL;
    int type=0,fd,redirect_type=-1;
    while(*ptr!='\0')
    {
        if(*ptr=='>')
        {
            *ptr++='\0';
            redirect_type++;
            if(*ptr=='>')
            {
                *ptr++='\0';
                redirect_type++;
            }
            while(isspace(*ptr))//指向空格++
            {
                ptr++;
            }
            file=ptr;
            while(!isspace(*ptr)&&*ptr!='\0')
            {
                ptr++;
            }
            *ptr='\0';
            if(redirect_type==0)//命令行只有一个> 表示清空重定向
            {
                fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0664);
            }
            else //命令行里有 >> 表示追加重定向
            {
                fd=open(file,O_CREAT|O_APPEND|O_WRONLY,0664);
            }
            dup2(fd,1);
        }
        ptr++;
    }
    return 0;
}

int do_command(char *buff)
{
    int pipe_num=0,i;
    char *ptr=buff;
    int pipefd[32][2]={{-1}};
    int pid=-1;

    pipe_command[pipe_num]=ptr;
    while(*ptr!='\0')
    {
        if(*ptr!='|')
        {
            pipe_num++;
            *ptr++='\0';
            pipe_command[pipe_num]=ptr;
            continue;
        }
        ptr++;
    }
    pipe_command[pipe_num+1]=NULL;
    return pipe_num;//下标表示有几个管道 |
}

int do_pipe(int pipe_num)
{
    int pid=0,i;
    int pipefd[10][2]={{0}};
    char **argv={NULL};
    for(i=0;i<=pipe_num;i++)
    {
        pipe(pipefd[i]);
    }
    for(i=0;i<=pipe_num;i++)
    {
        pid=fork();
        if(pid==0)
        {
            do_redirect(pipe_command[i]);
            argv=do_parse(pipe_command[i]);
            if(i!=0)
            {
                close(pipefd[i][1]);
                dup2(pipefd[i][0],0);
            }
            if(i!=pipe_num)
            {
                close(pipefd[i+1][0]);
                dup2(pipefd[i+1][1],1);
            }
            execvp(argv[0],argv);
        }
        else
        {
            close(pipefd[i][0]);
            close(pipefd[i][1]);
            waitpid(pid,NULL,0);
        }
    }
    return 0;
}

int main()
{
    int num=0;
    while(1)
    {
        if(do_face()<0)
            continue;
        num=do_command(command);
        do_pipe(num);
    }
    return 0;
    
}
