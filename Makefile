target  = Nv16To422
sources = main.c $(target).c
objects = $(patsubst %.c,%.o,$(sources))
CC = gcc
OPTS = -Wall

all: $(objects)
	$(CC) $(OPTS) -o $(target) $(objects)

clean:
	$(RM) $(target) $(objects)
