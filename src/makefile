INCL=copter.h
SRC=main.c
LIBS=-lmingw32 -lSDL2main -lSDL2
OBJ=$(SRC:.c=.o)
ODIR=obj
EXE=copter

CC=gcc
CFLAGS=-c -Wall -I../includes/ -L../lib

$(EXE): $(ODIR)/$(OBJ)
	$(CC) $(ODIR)/$(OBJ) -o $@ $(LIBS)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	$(RM) $(ODIR)/$(OBJ) $(EXE) core a.out