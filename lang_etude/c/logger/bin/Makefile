TARGET  := liblogger.a
OBJS    := logger.o

include ../../makefiles/dir.mk
include $(MAKEFILE_DIR)/lib.mk

T_DEPLIB :=
test: logger.do
	$(CC) $(DFLAGS) \
	    $(INCL_DIR:%=-I%) $(LIB_DIR:%=-L%) \
	    $(T_DEPLIB:%=-l%)
	    -DTEST $^ -o $@
