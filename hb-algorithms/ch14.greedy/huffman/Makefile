CURRENT_DIR=($shell pwd)

all: test-huffman

test-huffman: test-huffman.o huffman.o priority-queue.o
	gcc -o $@ $^
