<!-- TOC -->

- [1. 版本1](#1-版本1)
- [2. 版本2](#2-版本2)
- [3. 版本3](#3-版本3)

<!-- /TOC -->


# 1. 版本1

直接用指令编译也可以

```bash
g++ foo1.cpp foo1.h foo2.cpp foo2.h main.cpp -o version1
```

```Makefile
all: version1

version1: main.cpp foo1.cpp foo2.cpp foo1.h foo2.h
	g++ main.cpp foo1.cpp foo2.cpp -o version1
clean:
	rm -rf version1
```

缺点:

* 任何文件只要做了修改项目都要完整的重新编译

# 2. 版本2

```Makefile
all: version2

version2: main.o foo1.o foo2.o
	g++ main.o foo1.o foo2.o -o version2
main.o: main.cpp foo1.h foo2.h
	g++ -c main.cpp -o main.o
foo1.o: foo1.cpp foo1.h
	g++ -c foo1.cpp -o foo1.o
foo2.o: foo2.cpp foo2.h
	g++ -c foo2.cpp -o foo2.o
clean:
	rm -rf version2 *.o
```

优点:
* 不需要整个项目重新编译, 比如修改了foo1.cpp, 只需要重新构建foo1.o即可

缺点:
* 内容重复
	* x.cpp => x.o 重复
	* x.cpp 依赖的头文件 => x.o 重复

# 3. 版本3

```Makefile
all: version3

obj = main.o foo1.o foo2.o

target = version3

CXX = g++

# $< xxx.c
# $@ xxx.o

$(target): $(obj)
	$(CXX $(obj) -o $(target) 

%.o: %.c
	$(CXX) -c $< -o $@

clean:
	rm -rf version3 *.o
```

优点:
* x.cpp => x.o 重复 的问题解决了

缺点:
* x.cpp 依赖的头文件变化