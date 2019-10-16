#. copyright
#

CC=g++ 

#CURRENT_DIR = $(notdir $(shell pwd))
CURRENT_DIR = $(shell pwd)

SRC=$(CURRENT_DIR)/src
INC=$(CURRENT_DIR)/include
BUILD=$(CURRENT_DIR)/build
TEST=$(CURRENT_DIR)/test
BIN=$(CURRENT_DIR)/bin

GTEST=$(CURRENT_DIR)/../gtest
LIB=$(CURRENT_DIR)/../lib

all: dp_2601_test

##################################################
	
$(BUILD)/%.o:$(SRC)/%.cc
	@echo ">>>>>>>>>>>>>>>>>>>> $< : $@ <<<<<<<<<<<<<<<<<<<<"
	$(RM) -rf $@
	$(CC) -std=c++11 -c -o $@ -I$(INC) -L$(LIB) $(SRC)/$*.cc

##################################################	

dp_2601_test: $(BUILD)/fibonacci.o
	rm -f $(BIN)/test_main 
	$(CC) -std=c++11 -o $(BIN)/test_main -I$(INC) -I$(GTEST) -L$(LIB) -lgtest $(TEST)/test_main.cc $^
	./bin/test_main

##################################################	
clean:
	rm -rf $(BIN)/* $(BUILD)/*.o $(BUILD)/*.lis
