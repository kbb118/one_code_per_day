TARGET ?= threadAttr

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -pthread $^ -o $@
