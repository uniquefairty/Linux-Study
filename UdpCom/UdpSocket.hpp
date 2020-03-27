#pragma once
#include <cstdio>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpSocket
{
    public:
        UdpSocket()
            :_fd(-1)
        {}
        ~UdpSocket()
        {}
        //1.创建套接字
        bool CreatSocket()
        {
           _fd= socket(AF_INET,SOCK_DGRAM,0);
           if(_fd<0)
           {
               perror("socket");
               return false;
           }
           return true;
        }
        
        //2.绑定地址信息
        bool Bind(const std::string& ip,uint16_t port)
        {
            //ip+port
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            //主机字节序变成网络字节序
            addr.sin_port=htonl(port);//两个字节，牵扯到大小端问题
            //in_addr_t inet_addr(const char *cp);
            addr.sin_addr.s_addr=inet_addr(ip.c_str());  

            int ret=bind(_fd,(struct socketaddr*)&addr,sizeof(addr));
            if(ret<0)
            {
                perror("bind");
                return false;
            }
            return true;
        }
        //3.发送数据
        bool SendTo(const std::string& buf,const std::string& ip,uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htonl(port);
            addr.sin_addr.s_addr=inet_addr(ip.c_str());
            ssize_t writeSize=sendto(_fd,buf,buf.size(),0,(struct sockaddr *)&addr,sizeof(addr));
            if(writeSize<0)
            {
                perror("sendto");
                return false;
            }
            return true;

        }
        //4.接收数据
        bool RecvFrom(std::string* buf,std::string* ip=NULL,uint16_t* port=NULL)
        {
           char tmp[1024]={0};
           struct sockaddr_in peer;
           socklen_t len=sizeof(peer);

           ssize_t readSize=recvfrom(_fd,tmp,sizeof(tmp)-1,0,(struct sockaddr*)&peer,&len);
           if(readSize<0)
           {
               perror("recvfrom");
               return false;
           }   
           //将读到的缓冲区内容放到输出参数中
           buf->assign(tmp,readSize);
           if(ip!=NULL)
           {
               *ip=inet_ntoa(peer.sin_addr);
           }
           if(port!=NULL)
           {
               *port=ntohs(peer.sin_port);
           }
           return true;
        }
        //5.关闭套接字
        bool Close()
        {
            close(_fd);
            _fd=-1;
            return true;
        }
    private:
        int _fd;
};
