test:test.c
	gcc test.c -o test -g

.PHONY:clean
clean:
	rm test
