TARGET = pipe_func_NULL
OBJS = pipe_func_NULL.o
LIBOBJS =
CC = g++
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
