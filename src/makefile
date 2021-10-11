INCL=global.h copter.h environment.h
SRC=main.c render.c environment.c copter.c
LIBS=-lSDL2 -lSDL2main
ODIR=obj
OBJ=$(SRC:%.c=$(ODIR)/%.o)
EXE=copter

CC=gcc
CFLAGS=-c -ggdb -Wall -I../includes/ 

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	$(RM) $(ODIR)/$(OBJ) $(EXE) core a.out
