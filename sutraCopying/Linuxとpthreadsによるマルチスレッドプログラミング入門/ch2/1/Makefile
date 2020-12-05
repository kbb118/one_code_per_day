TARGET := firstThread

CFLAGS := $(CFLAGS) -pthread
LDFLAGS := $(LDFLAGS) -pthread

all: $(TARGET)

firstThread: firstThread.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o

