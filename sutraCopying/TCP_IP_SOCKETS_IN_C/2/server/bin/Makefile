include ../../common.mk

TARGET          = tcp_echo_server
TARGET_DEBUG    = $(TARGET)_d

FILE_PATHS      = $(wildcard ../src/*.c)
SRCS            = $(notdir $(FILE_PATHS))
OBJS            = $(SRCS:.c=.o)
OBJS_DEBUG      = $(SRCS:.c=.do)

UTIL_SRC_PATHS        = $(notdir $(wildcard ../../util/src/*.c))
UTIL_OJBS_PATHS       = $(addprefix ../../util/bin/, $(UTIL_SRC_PATHS:.c=.o))
UTIL_OJBS_DEBUG_PATHS = $(addprefix ../../util/bin/, $(UTIL_SRC_PATHS:.c=.do))

all: $(TARGET)
d  : $(TARGET_DEBUG)

UTIL_DIR = ../../util/bin
$(UTIL_OJBS_PATHS):
	cd $(UTIL_DIR) && make
$(UTIL_OJBS_DEBUG_PATHS):
	cd $(UTIL_DIR) && make d

$(TARGET)      : $(OBJS)       $(UTIL_OJBS_PATHS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^
$(TARGET_DEBUG): $(OBJS_DEBUG) $(UTIL_OJBS_DEBUG_PATHS)
	$(CC) $(D_CFLAGS) $(CPPFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(OBJS_DEBUG) $(TARGET) $(TARGET_DEBUG) \
	$(UTIL_OJBS_PATHS) $(UTIL_OJBS_PATHS)
