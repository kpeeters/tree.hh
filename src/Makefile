
all: test1 test2

%.o: %.cc 
	g++ -g -c -Wall -O2 -std=c++11 -I. $^

test1: test1.o
	g++ -o test1 test1.o

test2: test2.o 
	g++ -o test2 test2.o

run_tests: test1 test1.req
	./test1 > test1.res
	@diff test1.res test1.req
	@echo "*** All tests OK ***"

clean:
	rm -f *.o *~ *.res
