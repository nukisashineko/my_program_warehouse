TARGET = Card_Game_II
OBJS = Card_Game_II.c
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