CC = gcc
CFLAGS = -Wall -Wextra
INCL = -I../../lib -I../include

liblogger.a: logger.o
	ar r $@ $^

%.o:../src/%.c
	$(CC) $(CFLAGS) $(INCL) -c $^

test: ../src/logger.c
	$(CC) $(CFLAGS) $(INCL) -DTEST $^ -o $@
