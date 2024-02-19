# Makefile for 'indexer' program
#
# Dylan Lawler, CS50, Spring 2022
 
# executables
PROG = indexer
TEST = indextest 
ALL = $(PROG) $(TEST)

# executables depend on their object files
OBJS = indexer.o
TESTOBJS = indextest.o

# libraries
LLIBS = ../common/common.a ../libcs50/libcs50.a

# compilation
CFLAGS = -Wall -pedantic -std=c11 -ggdb  -I../common -I../libcs50
CC = gcc

# make both indexer and indextest
all: $(ALL)

# make indextest
$(TEST): $(TESTOBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ 

# make indexer
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ 


# make libraries
$(LLIBS):
	@make -sC ../common
	@make -sC ../libcs50

PHONY: test clean

# test a few indexer cases and indextest into testing.out
test: 
	bash testing.sh &> testing.out

# clean all makefile made files and clean libraries
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -rf *~ *.o letters* wikipedia* fake* *.out *fl
	rm -f $(PROG) $(TEST)
	@make -sC ../common clean