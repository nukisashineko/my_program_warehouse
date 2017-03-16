TARGET = _make_onpu_
OBJS = _make_onpu_.o
LIBOBJS = 
CC ?= gcc
CFLAGS += -O
CFLAGS += -Wall
.SUFFIXES: .c .o

all:		$(TARGET)

$(TARGET):	$(OBJS)
		$(CC) $<  -o $@ $(CFLAGS)
	
.c.o :		$<
		$(CC) -c $< $(CFLAGS)
clean : 
		rm -f $(OBJS) $(TARGET)
