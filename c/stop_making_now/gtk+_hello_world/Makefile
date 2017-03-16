TARGET = gtk+_hello_world
OBJS = Gtk+_Hello_World.o
LIBOBJS = `pkg-config --libs gtk+-2.0` 
CC = gcc
CFLAGS += `pkg-config --cflags gtk+-2.0` 
CFLAGS += -O
CFLAGS += -Wall
.SUFFIXES:  .c .o

all:		$(TARGET)

$(TARGET):	$(OBJS)
		$(CC) $(LIBOBJS) $(OBJS)  -o $@  $(CFLAGS)
	
.c.o :		$<
		$(CC) -c $< $(CFLAGS) 
clean : 
		rm -f $(OBJS) $(TARGET)
