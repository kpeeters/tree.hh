
%.o: %.cc
	g++ -c -I. $^

test1: test1.o
	g++ -o test1 test1.o

run_tests: test1 test1.req
	./test1 > test1.res
	@diff test1.res test1.req
	@echo "*** All tests OK ***"

clean:
	rm -f *.o *~ *.res
