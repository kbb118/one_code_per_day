TARGET ?= pthread_cancel

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -g -pthread $^ -o $@
