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
