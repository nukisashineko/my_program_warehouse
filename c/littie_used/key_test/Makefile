TARGET = key_test
OBJS = key_test.o
LIBOBJS =
CC ?= gcc
CFLAGS += -O
CFLAGS += -Wall
.SUFFIXES: .c .o

all:		$(TARGET)
	
$(TARGET):		$(OBJS)
		$(CC) $< -o $@ $(CFLAGS)
	
.c.o :		$<
		$(CC) -c $< $(CFLAGS)
clean :
		rm -f $(OBJS) $(TARGET)
