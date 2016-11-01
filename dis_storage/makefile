src=$(wildcard ./src/*.c)
obj=$(patsubst %.c,%.o,$(src))
main=$(wildcard ./*.c)

LIB=./include
target=myApp

$(target):$(obj)
	gcc $(main) $(obj) -o $(target) -I$(LIB)

%.o:%.c
	gcc -c $< -o $@ -I$(LIB)

.PHONY:clean
clean:
	-rm -f $(obj) $(target)
