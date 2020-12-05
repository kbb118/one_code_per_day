TARGET ?= primeNumber5

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -pthread $^ -o $@

clean:
	rm -f $(TARGET) *.o
