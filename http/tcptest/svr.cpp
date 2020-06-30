#include "tcpsvr.hpp"
#include <boost/algorithm/string.hpp>
#include <vector>

int Sum(std::string Data)
{
    //1+1
    //boost::split(type,select_list,boost::is_any_of(""),boost::token_compress_on/off);
    //type:类型是vector<std::string>类型，保存切割完成之后的字符串
    //select:待切割的字符串，可以直接传入string对象
    //boost::is_any_of:告诉spilt函数按照什么样的字符串进行切割，单个字符支持，支持字符串（1++1  ”++“）
    //boost::token_compress_on/off:(1,,,2)
    //当是”on“：对于多个连续的分隔符当成1个处(1 2)
    //当是"off":有多少个分割字符就按照多少个分割字符来处理(1 _ _ 2)
    std::vector<std::string> output;
    std::string split_char ="+";
    boost::split(output,Data,boost::is_any_of(split_char),boost::token_compress_off);
    //int sum=atoi(output[0].c_str())+atoi(output[1].c_str());//将字符串转整型
    int sum_number=0;
    for(size_t i=0;i<output.size();i++)
    {
        sum_number+=atoi(output[i].c_str());

    }
    return sum_number;
    
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

    
    TcpServer peerts;
    if(!ts.Accept(peerts))
    {
       return 0;
    }
    //想使用TcpServer当中的手法数据接口，并且使用成员变量保存新创建（接收和发送数据）出来的socket
    while(1)
    {
       sleep(15);
  
       Data data;
       peerts.Recv(data);
      //1+1
      printf("cli say:%d+%d\n",data.a,data.b);

      std::string buf;
      buf=std::to_string(data.a+data.b);
  
      peerts.Send(buf);
  
    }
    ts.Close();

    return 0;
}
