#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include "tools.hpp"

//试题id 试题名称 试题路径 试题难度
typedef struct Questions
{
    std::string id_;
    std::string name_;
    std::string path_;
    std::string star_;
}QUES;

class OjModel
{
    public:
        OjModel()
        {
            LoadQuestions("./config_oj.cfg");
        }
        bool GetAllQuestions(std::vector<Questions>* ques)
        {
            for(const auto& kv:model_map_)
            {
                ques->push_back(kv.second);
            }
            
            //针对内置类型进行操作
            //std::greater降序排序 std::less 升序排序
            std::sort(ques->begin(),ques->end(),[](const Questions& l,const Questions& r){
                    return std::atoi(l.id_.c_str()) <std::atoi(r.id_.c_str());
                    });
        return true;
        }

    private:
        bool LoadQuestions(const std::string& configfile_path)
        {
            //使用C++文件中的文件流来加载文件，并获取文件当中的内容 
            //iostream处理控制台IO fstream处理命名文件的 stringstream完成内存中对象的IO
            //ofstream:output文件流，文件当中写
            //ifstream:input文件流，从文件当中读
            //在定义istream对象的时候，就可以指定打开哪一个文件，和文件进行绑定
            //ifstream(const char* filename,ios_base::openmode mode=ios_base::in);//in 以读的方式打开 out:以写的方式打开
            //void open(const char*filename,ios_base::penmode mode=ios_base::in);
            
            std::ifstream file(configfile_path.c_str());
            if(!file.is_open())
            {
                return false;
            }

            std::string line;
            while(std::getline(file,line))
            {
                //1 单链表 ./xxx  难度
                //1.需要切割字符串
                std::vector<std::string> vec;
                
                StringTools::Split(line," ",&vec);
                if(vec.size()!=4)
                {
                    continue;
                }
                //2.切割后的内容保存到unordered_map
                Questions ques;
                ques.id_=vec[0];
                ques.name_=vec[1];
                ques.path_=vec[2];
                ques.star_=vec[3];
                model_map_[ques.id_]=ques;
            }
            file.close();
            return true;

        }
    private:
        //map<key(id),value(TestQues)> model_map;红黑树 有序的树形结构，查询的效率不高
        //unordered_map<key,value>   //哈希表-无序-查询效率高，基本上就是常数时间完成的
        std::unordered_map<std::string ,Questions> model_map_;

        

};
