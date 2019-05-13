<!-- TOC -->

- [1. 版本1-直接编译](#1-版本1-直接编译)
- [2. 版本2-减少重复编译](#2-版本2-减少重复编译)
- [3. 版本3-自动推导](#3-版本3-自动推导)
- [4. 版本4-推导头文件依赖](#4-版本4-推导头文件依赖)
- [5. 版本5-automake](#5-版本5-automake)
- [6. 版本6-automake static library](#6-版本6-automake-static-library)

<!-- /TOC -->


# 1. 版本1-直接编译

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

# 2. 版本2-减少重复编译

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

# 3. 版本3-自动推导

```Makefile
all: version3

obj = main.o foo1.o foo2.o

target = version3

CXX = g++

# $< xxx.c
# $@ xxx.o

$(target): $(obj)
	$(CXX) $(obj) -o $(target) 

%.o: %.c
	$(CXX) -c $< -o $@

clean:
	rm -rf version3 *.o
```

优点:
* x.cpp => x.o 重复 的问题解决了

缺点:
* x.cpp 依赖的头文件变化

# 4. 版本4-推导头文件依赖

```Makefile
all: version4

SRCS = main.cpp foo1.cpp foo2.cpp
OBJS = ${SRCS:.cpp=.o}

target = version4

CXX = g++

$(target): $(OBJS)
	$(CXX) $(OBJS) -o $(target)

# $< xxx.cpp
# $@ xxx.d

#sed -i '1s/^/$@ /' $@
%.d: %.cpp
	$(CXX) -MM $< > $@
	
%.o: %.cpp
	$(CXX) -c $<  -o $@

clean:
	rm -rf version4 *.o *.d

-include ${SRCS:.cpp=.d}
```

优点:
* x.cpp 依赖的头文件变换,相应.o会重新编译

解释:

```Makefile
foo1.o: foo1.cpp foo1.h
foo2.o: foo2.cpp foo2.h
main.o: main.cpp foo1.h foo2.h
```

* .cpp => .d依赖 => 补充(xxx.o 依赖 于 xxx.cpp xxx.h) => xxx.o => xxx

# 5. 版本5-automake

* https://i.stack.imgur.com/kuFHy.gif (依赖图)
* https://www.gitignore.io/api/c++ (忽视文件)
* https://www.gitignore.io/api/autotools (忽视文件)

```bash
autoscan .
mv configure.scan configure.ac
# #AC_CONFIG_SRCDIR([config.h]) 注释这个
# AM_INIT_AUTOMAKE 增加这个
aclocal
autoconf
autoheader
automake --add-missing

./configure
make
sudo make install
```

等于:
```bash
autoreconf --install
./configure
make
sudo make install
```

Makefile.am
```Makefile
AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = version5
version5_SOURCES = foo1.cpp foo2.cpp main.cpp
```

优点:

* 上述的依赖推导自动完成,不需要自己实现.d
* 跨平台

# 6. 版本6-automake static library

