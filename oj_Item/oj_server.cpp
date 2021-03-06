#include <stdio.h>
#include <string>
#include <string.h>

#include "httplib.h"
#include "oj_model.hpp"
#include "oj_view.hpp"
#include "oj_log.hpp"

int main()
{
    //httlib的时候，需要使用httplib提供的命名空间
    using namespace httplib;
    Server svr;
    OjModel ojmodel;
    //lambda [] 表达式引出符，lamada函数的捕获列表
    //[var] 值传递方式将var变量传递到lamada函数当中去
    //[=]:值传递方式捕获所有父作用域当中的所有变量
    //[&var]:引用传递var
    //[&]:引用传递方式捕获所有父作用域上中的变量
    //[this]:z值传递this指针
    //给http传递lamada表达式是一个回调函数的方式
    //
    //1.要获取试题的信息
    //试题的信息来源于文件当中
    svr.Get("/all_questions",[&ojmodel](const Request& req,Response& resp){
            std::vector<Questions> ques;
            ojmodel.GetAllQuestions(&ques);
            //<html>id.name start</html>
            //char buf[10240]={'\0'};
            //snprintf(buf,sizeof(buf)-1,"<html>%s.%s %s</html>",ques[0].id_.c_str(),ques[0].name_.c_str(),ques[0].star_.c_str());

            //std::string html;
            //html.assign(buf,strlen(buf));
            
            //stringstream ss;
            //想使用模板技术去html页面
            
            std::string html;
            OjView::ExpandAllQuestionshtml(&html,ques);
            //LOG(INFO,html);
            resp.set_content(html,"text/html;charset=UTF-8");
            });
    //正则表达式
    //    \b:单词的分界  
    //    *:匹配任意字符串
    //    \d:匹配一个数字
    //源码转义：特殊字符就按照特殊字符字面源码来编译
    //     R"(str)"
    svr.Get(R"(/question/\d+)",[&ojmodel](const Request& req,Response& resp){
            std::string html="1";
            resp.set_content(html,"text/html;charset=UTF-8");
            });
    svr.listen("0.0.0.0",19999);
    LOG(INFO,"listen in 0.0.0.0:19999");
    LOG(INFO,"Server ready");
    return 0;
}
