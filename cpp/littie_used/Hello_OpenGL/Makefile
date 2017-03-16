TARGET = temp
OBJS = temp.o
LIBOBJS =
CC = g++
CFLAGS += -L/usr/X11R6/lib -lglut -lGLU -lGL -lXext -lX11 -lm -lpthread
CFLAGS += -O
CFLAGS += -Wall
LIBRIAY += -I/usr/X11R6/include
.SUFFIXES: .c .o

all:		$(TARGET)
	
$(TARGET):		$(OBJS)
		$(CC) $< -o $@ $(CFLAGS)
	
.c.o :		$<
		$(CC) $(LIBRIAY) -c $< $(CFLAGS)
clean :
		rm -f $(OBJS) $(TARGET)
