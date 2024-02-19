# Makefile for 'crawler' program
#
# Dylan Lawler, CS50, Spring 2022

PROG = crawler
OBJS = crawler.o 
LLIBS = ../common/common.a ../libcs50/libcs50.a
TEST = testing.sh


CFLAGS = -Wall -pedantic -std=c11 -ggdb  -I../common -I../libcs50
CC = gcc
MAKE = make

# make crawler
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) -o $@ $^

# make libraries
$(LLIBS):
	make -C ../common
	make -C ../libcs50

.PHONY: test clean

## test crawler into outfile
test: $(TEST)
	bash $(TEST) &> testing.out 

#delete object files, test directories, and executable
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
	rm -rf dir*
	make -C ../common clean
