.PHONY: all clean main run test
all:run
main:
	g++ ${shell ls *.cpp} -o main.out
run:main
	./main.out
test:main
	./main.out <test/1.cfg >test/1.res
clean:
	rm -f *.out test/*.res