.PHONY: all clean main run test
all:run
main:
	g++ ${shell ls *.cpp} -o main.out
run:main
	./main.out
test:main
	for file in $(basename $(shell find test/*.cfg)); \
	do \
		./main.out <$$file.cfg >$$file.res; \
	done
clean:
	rm -f *.out test/*.res