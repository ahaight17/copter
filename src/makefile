INCL=global.h copter.h environment.h
SRC=main.c render.c environment.c
LIBS=-lmingw32 -lSDL2main -lSDL2
ODIR=obj
OBJ=$(SRC:%.c=$(ODIR)/%.o)
EXE=copter

CC=gcc
CFLAGS=-c -Wall -I../includes/ -L/usr/local/bin

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	$(RM) $(ODIR)/$(OBJ) $(EXE) core a.out