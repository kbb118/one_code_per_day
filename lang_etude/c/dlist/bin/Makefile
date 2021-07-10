TARGET  := dlist
OBJS    := dlist.o

include ../../makefiles/dir.mk
include $(MAKEFILE_DIR)/lib.mk

T_DEPLIB := logger
test: $(SRC_DIR)/dlist.c
	$(CC) $(DFLAGS)                        \
	    $(INCL_DIR:%=-I%) $(LIB_DIR:%=-L%) \
	    -DTEST $^ -o $@                    \
	    $(T_DEPLIB:%=-l%)
