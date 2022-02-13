
all: test1 test2 test_tree

%.o: %.cc tree.hh
	g++ -g -c -o $@ -Wall -O2 -std=c++11 -I. $<

test1: test1.o 
	g++ -o test1 test1.o

test2: test2.o 
	g++ -o test2 test2.o

test_tree: test_tree.o
	g++ -o test_tree test_tree.o

sample_path: sample_path.o
	g++ -o sample_path sample_path.o

run_tests: test1 test1.req
	./test1 > test1.res
	@diff test1.res test1.req
	@echo "*** All tests OK ***"

clean:
	rm -f *.o *~ *.res
