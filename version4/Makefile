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