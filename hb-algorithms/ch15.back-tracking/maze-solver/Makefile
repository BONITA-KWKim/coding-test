CUR_DIR = $(shell pwd)

all: $(CUR_DIR)/test-maze-solver

$(CUR_DIR)/test-maze-solver: $(CUR_DIR)/test-maze-solver.c $(CUR_DIR)/maze-solver.o
	gcc -o $@ $^

$(CUR_DIR)/maze-solver.o: $(CUR_DIR)/maze-solver.c
	gcc -c -o $@ $^

clean:
	-rm -f $(CUR_DIR)/maze-solver.o $(CUR_DIR)/test-maze-solver