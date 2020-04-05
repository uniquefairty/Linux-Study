#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class TcpServer
{
    public:
        TcpServer()
        {
            Sock_=-1;
        }
        ~TcpServer()
        {

        }
        bool CreateSock()
        {
            Sock_=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(Sock_<0)
            {
                perror("socket");
                return false;
            }
            return true;
        }

        bool Bind(std::string& ip,uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(port);
            addr.sin_addr.s_addr=inet_addr(ip.c_str());

            int ret=bind(Sock_,(struct sockaddr*)&addr,sizeof(addr));
            if(ret<0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        bool Listen(int BackLog)
        {
            int ret=listen(Sock_,BackLog);
            if(ret<0)
            {
                perror("listen");
                return false;
            }
            return true;
        }

        //ts保存新创建的套接字
        bool Accept(TcpServer& ts,struct sockaddr_in* addr=NULL)
        {
            //int  accept(int sockfd, struct sockaddr *addr, socklen_t* addrlen);
            //sockfd:指的是当前监听的套接字
            //addr:对端地址信息,出参
            //addrlen:地址信息长度，输入输出型参数
            //返回值：返回大于0的数，则表示新创建的socket
            
            struct sockaddr_in peeraddr;
            socklen_t len=sizeof(struct sockaddr_in);

            int newfd=accept(Sock_,(struct sockaddr*)&peeraddr,&len);
            if(newfd<0)
            {
                perror("accept");
                return false;
            }
            //粗暴的做法：将新创建出来的套接字直接赋值给成员变量Sock_
            //Sock_=newfd;
            
            ts.Sock_=newfd;//让新创建的对象接受新的套接字，为客户端服务

            if(addr!=NULL)
            {
                memcpy(addr,&peeraddr,len);
            }
            return true;
        }

        //客户端连接服务端的接口
        bool Connect(std::string& ip,uint16_t port)
        {
            struct sockaddr_in destaddr;
            destaddr.sin_family=AF_INET;
            destaddr.sin_port=htons(port);
            destaddr.sin_addr.s_addr=inet_addr(ip.c_str());
            int ret=connect(Sock_,(struct sockaddr*)&destaddr,sizeof(destaddr));
            if(ret<0)
            {
                perror("connect");
                return false;
            }
            return true;

        }

        bool Send(std::string& buf)
        {
            int sendsize=send(Sock_,buf.c_str(),buf.size(),0);
            if(sendsize<0)
            {
                perror("send");
                return false;
            }
            return true;
        }

        bool Recv(std::string& buffer)
        {
            char buf[1024]={0};
            //falgs  0阻塞接受  MSG_PEEK 探测接受
            //由于TCP套接字是一个流式套接字，所以又可能数据接受的时候出现数据不完整的情况，对于上次协议所定义的数据不完整
            int recvsize=recv(Sock_,buf,sizeof(buf)-1,0);
            if(recvsize<0)
            {
                perror("recv");
                return false;
            }
            else if(recvsize==0)
            {
                //如果recvsize等于0，则表示对端连接关闭了
                printf("connect error\n");
                return false;
            }

            buffer.assign(buf,recvsize);
            return true;

        }

        void Close()
        {
            close(Sock_);
            Sock_=-1;
        }
    private:
        int Sock_;
};
