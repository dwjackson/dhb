EXE_NAME = dhb
SRC_FILES = dhb.c
OBJ_FILES = $(SRC_FILES:.c=.o)
CC = cc
CFLAGS = -ansi -Wall -Wextra -O2

all: $(EXE_NAME)

$(EXE_NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(OBJ_FILES)

$(OBJ_FILES): $(SRC_FILES)
	$(CC) $(CFLAGS) -c $(SRC_FILES)

clean:
	rm -f $(EXE_NAME)
	rm -f *.o

.PHONY: all clean
