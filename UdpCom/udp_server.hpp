#pragma once
#include "UdpSocket.hpp"
#include "assert.h"

#include <functional>
//C式写法
//typedef void (*Handler)(const std::string& req,std::string* resp);:

typedef std::function<void (const std::string&,std::string* resp)> Handler;

class UdpServer
{
    public:
        UdpServer()
        {
            assert(_sock.CreatSocket());

        }

        ~UdpServer()
        {
            _sock.Close();
        }

        bool Start(const std::string& ip,uint16_t port,Handler, Handler handler)

        {
            //1.创建socket
            //2.绑定端口号
            bool ret=_sock.Bind(ip,port);
            if(!ret)
            {
                return false;
            }
            //3.进入事件循环
            for(;;)
            {
                std::string req;
                std::string remote_ip;
                uint16_t remote_port=0;
                bool ret=_sock.RecvFrom(&req,&remote_ip,&remote_port);

                if(!ret)
                {
                    continue;
                }
                std::string resp;
                //5.根据请求计算响应
                hander(req,&resp);
                //6.返回响应客户端
                _sock.Sendto(resp,remote_ip,remote_port);
                printf("[%s:%d] req:%s,resp:%s\n",remote_ip.c_str(),remote_port,
                    req.c_str(),resp.c_str());
            }
            _sock.Close();
            return true;
        }
    private:
        UdpSocet _sock;
}
