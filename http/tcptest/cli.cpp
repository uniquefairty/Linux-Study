#include "tcpsvr.hpp"


int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("./cli [ip] [port]\n");
        return 0;
    }

    std::string ip=argv[1];
    uint16_t port=atoi(argv[2]);

    TcpServer ts;
    if(!ts.CreateSock())
    {
        return 0;
    }

    if(!ts.Connect(ip,port))
    {
        return 0;
    }

    while(1)
    {
#if 0
        //存在粘包问题
        printf("cli say:");
        fflush(stdout);
#endif

        std::string buf;
        //std::cin>>buf;
        Data data;
        data.a=1;
        data.b=1;

        ts.Send(&data);
        ts.Send(&data);//验证粘包问题

        ts.Recv(buf);
        printf("svr say:%s\n",buf.c_str());
    }

    ts.Close();

    return 0;
}
