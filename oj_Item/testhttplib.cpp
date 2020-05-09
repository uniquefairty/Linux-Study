#include <stdio.h>
#include "httplib.h"
#include <iostream>

using namespace httplib;

void func(const Request& req,Response& resp)
{
    //req:http请求的内容
    //resp：需要给用户响应的内容
    resp.set_content("<html>hello bite</html>","123");
}
int main()
{
    Server svr;
    //svr.Get("/",func);
    svr.Get("/aaa",[](const Request& req,Response& resp)
            {
            std::cout<<"haha"<<std::endl;
            (void)req;
            resp.set_content("<html>linux-haha</html>","123");
            }
            );
    svr.listen("192.168.2.138",19090);
    return 0;
}
