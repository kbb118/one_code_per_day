TARGET ?= fastPrimeNumber

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -pthread $^ -o $@

clean:
	rm -f $(TARGET) *.o
