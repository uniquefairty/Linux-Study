#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int fd[2];
    int ret=pipe(fd);
    if(ret<0)
    {
        return ret;
    }

    //fork子进程
    pid_t pid=fork();
    if(pid<0)
    {
        return 0;
    }
    else if(pid==0)
    {
        //子进程1
        //child1 ps aux
        dup2(fd[1],1);
        printf("child1:[%d]\n",getpid());
        execl("/user/bin/ps","ps","aux",NULL);
        exit(0);
    }

    pid_t pid2=fork();
    if(pid2<0)
    {
        return 0;
    }
    else if(pid2==0)
    {
        //child2 grep
        dup2(fd[0],0);
        execl("user/bin/grep","grep","sshd",NULL);
        exit(0);
    }
    //父进程
    close(fd[0]);//是否关掉父进程的读写两端是没有影响，建议关掉，防止父进程误操作将数据读走。
    close(fd[1]);
    waitpid(pid,NULL,0);
    waitpid(pid2,NULL,0);

    return 0;
}
