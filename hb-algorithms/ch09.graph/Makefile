ROOT=$(shell pwd)

all: ${ROOT}/test-graph

${ROOT}/test-graph: ${ROOT}/test-graph.c ${ROOT}/graph.o
	gcc -o $@ $^

${ROOT}/graph.o: ${ROOT}/graph.c
	gcc -c -o $@ $^

clean:
	-rm -f *.o