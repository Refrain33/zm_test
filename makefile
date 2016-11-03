test:./main.c ./src/*.c
	gcc main.c ./src/*.c -o test -I./include -I/usr/local/include/hiredis -L/usr/lib64 -lhiredis

*.o:*.c
	gcc main.c ./src/*.c -c *.o -I./include -I/usr/local/include/hiredis -L/usr/lib64 -lhiredis
