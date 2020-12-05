TARGET ?= firstThread4

LDFLAGS := $(LDFLAGS) -pthread


all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o
