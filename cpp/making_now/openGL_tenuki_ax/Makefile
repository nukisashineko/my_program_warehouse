TARGET = a.out 
OBJS =  temp.o
LIBOBJS =
CC = g++
CFLAGS += -O
CFLAGS += -L/usr/X11R6/lib -lglut -lGLU -lGL -lXext -lX11 -lm -lpthread
CFLAGS += -W
LIBRIAY += -I/usr/X11R6/include
.SUFFIXES: .c .o

all:		$(TARGET)
	
$(TARGET):		$(OBJS)
		$(CC) $< -o $@ $(CFLAGS)
	
.c.o :		$<
		$(CC) $(LIBRIAY) -c $< $(CFLAGS)
clean :
		rm -f $(OBJS) $(TARGET)
