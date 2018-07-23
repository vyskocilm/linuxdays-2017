
CC=gcc

all: zh.c
	$(CC) $(CFLAGS) -lczmq zh.c -o zh
	./zh
