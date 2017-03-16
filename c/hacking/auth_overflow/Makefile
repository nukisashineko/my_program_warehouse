PROGRAM := auth_overflow
SOURCES := $(wildcard *.c)
OBJS := $(SOURCES:.c=.o)
DEPENDS := $(SOURCES:.c=.depend)
CC := gcc
DEBUG := -g
CFLAGS := -O0 $(DEBUG)
CFLAGS += -Wall
LIBRIAY += 

.PHONY: all
all: $(PROGRAM)
$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(CFLAGS) $^

%.depend: %.cpp
	@echo generating $@
	@$(SHELL) -ec '$(CC) -MM $(CFLAGS) $<| sed "s/\($*\)\.o[ :]*/\1.o$@ : /g" > $@; [ -s$@ ] ||rm -f $@'

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPENDS)
endif

.PHONY:clean
clean:
	rm -f $(PROGRAM)
	rm -fr $(OBJS)
	rm -fr $(DEPENDS)
