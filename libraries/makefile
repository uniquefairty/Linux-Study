test1:test1.c libadd.a
	gcc $^ -o $@

libadd.a:add.c
	gcc -c add.c -o add.o
	ar -rc libadd.a add.o

.PHONY:clear
	rm test1
