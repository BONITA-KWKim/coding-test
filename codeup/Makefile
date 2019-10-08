CURRENT_DIR = $(shell pwd)

SOURCES=$(CURRENT_DIR)/greedy_3120 \
$(CURRENT_DIR)/greedy_3301 \
$(CURRENT_DIR)/greedy_3321


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
