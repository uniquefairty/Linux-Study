#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    int pipefd[2];
    if(pipe(pipefd)==-1)
    {
        perror("pipe error");
    }

    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        perror("fork error");
    }
    if(pid==0)
    {
        //child
        close(pipefd[0]);//关闭读端
        write(pipefd[1],"hello",5);
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
    close(pipefd[1]);
    char buf[10]={0};
    read(pipefd[0],buf,10);
    printf("buf=%s\n",buf);
    return 0;

}
