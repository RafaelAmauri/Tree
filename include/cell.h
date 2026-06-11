#ifndef CELL_H
#define CELL_H

#include <stdlib.h>
#include <string.h>

// Cell for the linked stack.
typedef struct Cell {
    char *fullpath;
    char *name;
    int depth;
    struct Cell *next;
} Cell;

Cell *createCell(char *fullpath, char *name, int depth);

#endif
