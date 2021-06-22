CC=gcc
CFLAGS=-Wall -Wextra
DFLAGS=-D DEBUG -g

srcs=$(wildcard *.c)
OBJS=$(srcs:.c=.o)
DOBJS=$(srcs:.c=.do)

all: $(OBJS)
d: $(DOBJS)

proto: $(srcs:.c=_proto.h)

%_proto.h:%.c
	touch $@
	cproto -e $^ > $@

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
%.do:%.c
	$(CC) $(CFLAGS) $(DFLAGS) -c $^ -o $@
clean:
	rm -f $(OBJS) $(DOBJS)
