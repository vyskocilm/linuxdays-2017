# Docker image for Linuxdays workshop

This contain "blessed" version of zeromq dependencies. Feel free to use
whatever appropriate on your laptot

## Install

```
docker pull vyskocilm/zimg:latest
```

## Use

Define shell alias to save your keyboard

```
alias z="docker run -v ${PWD}:/home/zeromq -it --rm vyskocilm/zimg:latest"
```

Build and test example program
```
$ z make
gcc  -lczmq zh.c -o zh
./zh
I: 18-07-23 13:20:44 Hello from zsys(4.2.0)@e38b6d1331e3
$ ./zh
I: 18-07-23 15:20:51 Hello from zsys(4.2.0)@linux-33zu
```
