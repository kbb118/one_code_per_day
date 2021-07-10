TARGET  := libslist.a
OBJS    := slist.o

include ../../makefiles/dir.mk
include $(MAKEFILE_DIR)/lib.mk

T_DEPLIB :=
test: $(SRC_DIR)/slist.c
	$(CC) $(DFLAGS)                        \
	    $(INCL_DIR:%=-I%) $(LIB_DIR:%=-L%) \
	    -DTEST $^ -o $@                    \
	    $(T_DEPLIB:%=-l%)
