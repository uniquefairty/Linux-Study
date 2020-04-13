#include "tcpsvr.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string>


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
      TcpServer peerts;
      if(!ts.Accept(peerts))
      {
          return 0;
      }
  
      std::string buf;
      peerts.Recv(buf);
      printf("chrome send Data:%s\n",buf.c_str());
  
      //http协议去组织数据格式
      //响应首行
      //响应头部
      //空行
      //正文
      std::string body="<html><body><h1>hello world</h1></body></html>";
      char arraybuf[10240]={0};

      sprintf(arraybuf,"%s %s %s\r\nContent-Length: %lu\r\nContent-Type: %s\r\n\r\n","HTTP/1.1","200","OK",body.size(),"text/html");
      std::string header;
      header.assign(arraybuf,strlen(arraybuf));
      //snprintf(buf,size,"%s%s%s",str,str,str);安全，但是不知道size大小
      peerts.Send(header);
      peerts.Send(body);

      peerts.Close();
  
    }
    ts.Close();

    return 0;
}
