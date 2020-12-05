TARGET ?= fly

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -pthread $^ -lm -o $@

clean:
	rm -f $(TARGET) *.o
