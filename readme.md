<!-- TOC -->

- [1. 版本1](#1-版本1)
- [2. 版本2](#2-版本2)

<!-- /TOC -->


# 1. 版本1

直接用指令编译也可以

```bash
g++ foo1.cpp foo1.h foo2.cpp foo2.h main.cpp -o version1
```

```Makefile
version1: main.cpp foo1.cpp foo2.cpp foo1.h foo2.h
	g++ main.cpp foo1.cpp foo2.cpp foo1.h foo2.h -o version1
clean:
	rm version1
```

缺点:

* 任何文件只要做了修改项目都要完整的重新编译

# 2. 版本2

