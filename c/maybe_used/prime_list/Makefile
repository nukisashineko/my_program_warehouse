TARGET = prime_list
OBJS = prime_list.o
LIBOBJS =
CC ?= gcc
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
