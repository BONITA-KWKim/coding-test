CURRENT_DIR = $(shell pwd)

SOURCES=$(CURRENT_DIR)/greedy_3120 

all:
	for module  in $(SOURCES); \
	do \
		( echo [[[[[ $$module ]]]]]; cd $$module; $(MAKE) all; echo "---------------------------") \
	done

clean:
	for module  in $(SOURCES); \
	do \
		( echo [[[[[ $$module ]]]]]; cd $$module; $(MAKE) clean; echo "---------------------------") \
	done
