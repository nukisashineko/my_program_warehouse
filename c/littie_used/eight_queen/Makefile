TARGET = eight_queen
OBJS = eight_queen.o
LIBOBJS =
CC ?= g++
CFLAGS += -lm
CFLAGS += -O
CFLAGS += -Wall
.SUFFIXES: .c .o

all:		$(TARGET)

$(TARGET):	$(OBJS)
		$(CC) $(OBJS)  -o $@ $(CFLAGS)
	
.c.o :		$<
		$(CC) $(LIBOBJS) -c $< $(CFLAGS) 
clean : 
		rm -f $(OBJS) $(TARGET)
