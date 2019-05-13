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
