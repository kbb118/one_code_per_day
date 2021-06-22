include ../../common.mk

FILE_PATHS      = $(wildcard ../src/*.c)
SRCS            = $(notdir $(FILE_PATHS))
OBJS            = $(SRCS:.c=.o)
OBJS_DEBUG      = $(SRCS:.c=.do)

all  : $(OBJS)
d    : $(OBJS_DEBUG)
clean:
	rm -f $(OBJS) $(OBJS_DEBUG)

