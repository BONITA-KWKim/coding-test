ROOT = ${shell pwd}

all: ${ROOT}/test-circular-queue ${ROOT}/circular-queue.o

${ROOT}/test-circular-queue/: ${ROOT}/test-circular-queue.c ${ROOT}/circular-queue.o
	gcc -o $@ $^

${ROOT}/circular-queue.o: ${ROOT}/circular-queue.c
	gcc -c -o $@ $^

clean:
	-rm -f *.o