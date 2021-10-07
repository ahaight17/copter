INCL=copter.h
SRC=main.c
OBJ=$(SRC:.c=.o)
ODIR=obj
EXE=copter

CC=gcc
CFLAGS=-c -Wall -I../includes/

$(EXE): $(ODIR)/$(OBJ)
	$(CC) $(ODIR)/$(OBJ) -o $@

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(ODIR)/$(OBJ) $(EXE) core a.out