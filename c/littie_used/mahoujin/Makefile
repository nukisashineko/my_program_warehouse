TARGET = mahoujin
OBJS = mahoujin.o
OBJS += make_mahoujin.o
OBJS += view_mahoujin.o
LIBOBJS =
CC ?= g++
CFLAGS += -lm
CFLAGS += -O
CFLAGS += -Wall
.SUFFIXES:  .c .o

all:		$(TARGET)

$(TARGET):	$(OBJS)
		$(CC) $(OBJS)  -o $@ $(CFLAGS)
	
.c.o :		$<
		$(CC) $(LIBOBJS) -c $< $(CFLAGS) 
clean : 
		rm -f $(OBJS) $(TARGET)
