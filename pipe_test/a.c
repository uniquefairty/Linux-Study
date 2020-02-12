#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>

int main(int argc,char *argv[])
{
    mkfifo("tp",0644);
    int infd;
    infd=open("abc",O_RDONLY);
    if(infd==-1)
        ERR_EXIT("open");
    char buf[1024];
    int n;
    while((n==read(infd,buf,1024))>0)
    {
        write(outfd,buf,n);
    }
    close(infd);
    close(outfd);
    return 0;



}
