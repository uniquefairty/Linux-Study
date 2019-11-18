#//out:out.c
#//	gcc out.c -o out 
#//
#//clean:
#//	rm out



bin=out
src=$(wildcard *.c)
#//从当前目录底下寻找.c后缀的文件 以空格分开
#//$查看里面的值
#src=test.c a.c
obj=$(patsubst %.c,%.o,$(src))
#obj=test.c a.o
cflags=-g
Include=-I ..
#假设头文件在上级目录
$(bin):$(obj)
	gcc $^ -o $@ 
%.o :%.c
	gcc $(cflags) -c $< -o $@
	#gcc $(cflags) $(Include) -c $< -o $@
clean:
	rm $(obj) $(bin)
