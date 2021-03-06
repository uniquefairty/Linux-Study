#include "tcpsvr.hpp"

void* ThreadStart(void* arg)
{
    pthread_detach(pthread_self());
    TcpServer* ts=(TcpServer*)arg;
    while(1)
    {

      std::string buf;
      ts->Recv(buf);
      printf("cli say:%s\n",buf.c_str());
  
      printf("svr say:");
      fflush(stdout);
      std::cin>>buf;
  
      ts->Send(buf);

    }
    delete ts;
}

int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("./svr [ip] [port]\n");
        return 0;
    }

    std::string ip=argv[1];
    uint16_t port=atoi(argv[2]);

    TcpServer ts;
    if(!ts.CreateSock())
    {
        return 0;
    }

    if(!ts.Bind(ip,port))
    {
        return 0;
    }

    if(!ts.Listen(5))
    {
        return 0;
    }

    //想使用TcpServer当中的手法数据接口，并且使用成员变量保存新创建（接收和发送数据）出来的socket
    while(1)
    {
      TcpServer* peerts=new TcpServer();//堆上申请的空间在入口函数上释放的
      struct sockaddr_in peeraddr;
      if(!ts.Accept(peerts,&peeraddr))
      {
          return 0;
      }

      pthread_t tid;
      int ret=pthread_create(&tid,NULL,ThreadStart,(void *)peerts);
      if(ret<0)
      {
          perror("pthread_create");
          return 0;
      }

    }
    ts.Close();

    return 0;
}
