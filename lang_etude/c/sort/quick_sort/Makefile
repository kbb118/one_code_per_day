CC=gcc
CFLAGS=-Wall -Wextra
DFLAGS=-D DEBUG -g
INCLUDE=-I lib -I../../lib
LIBS=lib/dlist.o -L../../lib -llogger
DLIBS=lib/dlist.do
TARGET=quick_sort
DTARGET=$(TARGET)_d

all:$(TARGET)
d: $(DLIBS) $(DTARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBS)
$(DTARGET): main.do $(DLIBS)
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -o $@ $^
$(DLIBS): $(DLIBS:.do=.c)
	LANG=C $(MAKE) -C lib d

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@
%.do:%.c
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $^ -o $@

clean:
	rm -f main.o main.do
