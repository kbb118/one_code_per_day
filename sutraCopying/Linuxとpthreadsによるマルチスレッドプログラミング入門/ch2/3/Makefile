TARGET ?= firstThread3

CFLAGS := $(CFLAGS) -pthread
LDFLAGS := $(LDFLAGS) -pthread

all: $(TARGET)


$(TARGET): $(TARGET).o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o
