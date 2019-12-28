/*回顾一下标准IO接口
 * fopen 打开文件
 * r  只读打开，文件不存在报错
 * r+ 读写打开，文件不存在报错
 * w  只写方式，文件不存在，则创建；若存在，则清空原有内容
 * w+ 读写打开，文件不存在，则创建；若存在，则清空原有内容
 * a  追加写打开，文件不存在，则创建；写入的时候，总在文件的末尾
 * a+ 读和追加打开，文件不存在，则创建；写入的时候，总在文件末尾
 * fwrite 向文件写入数据
 * fread 从文件读出数据
 * fseek 跳转读写位置
 * fclose 关闭文件
 * */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#if 0
int main()
{
  //FILE *fopen(const char *path, const char *mode);
  char *file="./tmp.txt";
  FILE *fp=fopen(file,"r");
  if(fp==NULL)
  {
    perror("fopen error");
    return -1;
  }
  //size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
  //size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
  //ptr: 要写入的数据
  //size: 数据块的大小
  //nmemb：数据块的个数
  //stream:文件流指针
  //char buf[1024]={"haha"};
 // fwrite(buf,1,strlen(buf),fp);
  char buf2[1024];
  //int fseek(FILE *stream, long offset, int whence);
  fseek(fp,0,SEEK_END);
  //long ftell(FILE *stream);计算文件的大小
  long Fsize= ftell(fp);
  printf("FILE_Size:%ld\n",Fsize);
  fseek(fp,0,SEEK_SET);
  int ret= fread(buf2,Fsize,1,fp);
  perror("fread error");
  printf("buf2:[%d]-[%s]\n",ret,buf2);
  fclose(fp);
  return 0;
}
#endif

int main()
{
  printf("printf");
  const char* lp="linux";
  const char* lp1="-jiang";
  fprintf(stdout,"%s%s",lp,lp1);
  fwrite("fwrite",1,6,stdout);
  write(1,"write",5);
  return 0;
}
