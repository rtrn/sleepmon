TARG=sleepmon.exe

OFILES=\
	sleepmon.o\

HFILES=\
	args.h\

CC=gcc.exe
LD=gcc.exe
CFLAGS=-Wall -Wextra -c -O2
LDFLAGS=-s
LDADD=
BIN?=$(HOME)/bin

.PHONY:		all install clean

all:		$(TARG)

$(TARG):	$(OFILES)
	$(LD) $(LDFLAGS) -o $(TARG) $^ $(LDADD)

%.o:		%.c $(HFILES)
	$(CC) $(CFLAGS) $*.c

install:	$(BIN)/$(TARG)

$(BIN)/$(TARG):	$(TARG)
	cp $^ $(BIN)/$(TARG)

clean:
	rm -f *.o $(TARG)
