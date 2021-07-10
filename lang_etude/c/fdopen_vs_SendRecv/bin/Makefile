TARGET  := fdopen_vs_SendRecv
OBJS    := fdopen_vs_SendRecv.o

include ../../makefiles/dir.mk
include $(MAKEFILE_DIR)/exe.mk

all: ver_fdopen ver_SendRecv peer

#CFLAGS += -g

T_DEPLIB := logger
ver_fdopen: $(SRC_DIR)/fdopen_vs_SendRecv.c
	$(CC) $(CFLAGS)                        \
	    $(INCL_DIR:%=-I%) $(LIB_DIR:%=-L%) \
	    -DFDOPEN $^ -o $@                  \
	    $(T_DEPLIB:%=-l%)

ver_SendRecv: $(SRC_DIR)/fdopen_vs_SendRecv.c
	$(CC) $(CFLAGS)                        \
	    $(INCL_DIR:%=-I%) $(LIB_DIR:%=-L%) \
	    -DSENDRECV $^ -o $@                \
	    $(T_DEPLIB:%=-l%)

peer: $(SRC_DIR)/fdopen_vs_SendRecv.c
	$(CC) $(CFLAGS)                        \
	    $(INCL_DIR:%=-I%) $(LIB_DIR:%=-L%) \
	    -DPEER $^ -o $@                \
	    $(T_DEPLIB:%=-l%)
