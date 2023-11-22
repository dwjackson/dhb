EXE_NAME = dhb
SRC_FILES = dhb.c
OBJ_FILES = $(SRC_FILES:.c=.o)
CC = cc
CFLAGS = -ansi -Wall -Wextra -Wpedantic -O2

PREFIX = ./usr
DESTDIR = $(PREFIX)/bin

MAN_FILE = $(EXE_NAME).1
MAN_GZ = $(MAN_FILE).gz
MAN_DESTDIR = $(PREFIX)/share/man/man1

all: $(EXE_NAME)

$(EXE_NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(OBJ_FILES)

$(OBJ_FILES): $(SRC_FILES)
	$(CC) $(CFLAGS) -c $(SRC_FILES)

$(MAN_GZ): $(MAN_FILE)
	gzip -k $(MAN_FILE)

install: $(EXE_NAME) $(MAN_GZ)
	install -m 557 $(EXE_NAME) $(DESTDIR)
	install -m 644 $(MAN_GZ) $(MAN_DESTDIR)

check: $(EXE_NAME)
	sh test.sh

clean:
	rm -f $(EXE_NAME)
	rm -f *.o
	rm -f $(MAN_GZ)

.PHONY: all check clean install
