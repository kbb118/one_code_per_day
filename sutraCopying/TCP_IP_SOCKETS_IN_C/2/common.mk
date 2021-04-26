CC              = gcc
CFLAGS_COMMON   = -Wall -Wextra
CFLAGS          = $(CFLAGS_COMMON) -O3
CFLAGS_DEBUG    = $(CFLAGS_COMMON) -g -O0
CPPFLAGS        =

%.o: ../src/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
%.do: ../src/%.c
	$(CC) -c $(D_CFLAGS) $(CPPFLAGS) -o $@ $<
