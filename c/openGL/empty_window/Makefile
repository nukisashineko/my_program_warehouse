CC = gcc
CFLAGS += -I/usr/X11R6/include
LDLIBS += -L/usr/X11R6/lib -lglut -lGLU -lGL -lXext -lX11 -lm -lpthread
a.out:program.c
	$(CC) $(CFLAGS) program.c $(LDLIBS)

