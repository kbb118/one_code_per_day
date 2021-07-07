TARGET = a.out
OBJ = main.c
LIBOBJ = example_lib.o 

all : $(TARGET)
	@gcc -o $< $(OBJ) $(LIBOBJ)

$(TARGET) : $(LIBOBJ)
	@gcc -o $< -c example_lib.c 

clean : 
	@rm $(TARGET) $(LIBOBJ)
