BINARY:=tree
SRC:=tree.c cell.c linkedstack.c
CC:=gcc
FLAGS=-Wall -pedantic -O2
INCLUDE=-I./include

all:
	$(CC) $(INCLUDE) $(FLAGS) $(SRC) -o $(BINARY)
	strip $(BINARY)

clean:
	$(RM) $(BINARY)

debug:
	$(CC) $(INCLUDE) -g $(SRC) -o $(BINARY)
