TARGET = temp
OBJS = temp_before_arduino.o
LIBOBJS = CC = gcc
CFLAGS += -O0
CFLAGS += -g
CFLAGS += -W
CFLAGS += -Wall
CFLAGS += -fmudflap
CFLAGS += -lmudflap

.SUFFIXES: .c .o

all:		$(TARGET)

$(TARGET):	$(OBJS)
		$(CC) $<  -o $@ $(CFLAGS)

.c.o :		$<
		$(CC) -c $< $(CFLAGS)
clean : 
		rm -f $(OBJS) $(TARGET)
