TARGET ?= fly3

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -pthread $^ -lm -o $@

clean:
	rm -f $(TARGET) *.o
