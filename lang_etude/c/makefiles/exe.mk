DTARGET = $(TARGET)_d

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCL) $^ -o $@
$(DTARGET): $(DOBJS)
	$(CC) $(DFLAGS) $(INCL) $^ -o $@

d: $(DTARGET)

include $(MAKEFILE_DIR)/common.mk
