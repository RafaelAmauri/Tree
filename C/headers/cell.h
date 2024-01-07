#include <stdlib.h>
#include <string.h>

// Cell for the linked stack.
typedef struct Cell {
    char *fullpath;
    char *name;
    int depth;
    struct Cell *next;
} Cell;


Cell *createCell(char *fullpath, char *name, int depth)
{
    Cell *cell = (Cell*) malloc(sizeof(Cell));

    cell->fullpath = (char*) malloc(4096);
    strcpy(cell->fullpath, fullpath);

    cell->name = (char*) malloc(255);
    strcpy(cell->name, name);

    cell->next  = NULL;
    cell->depth = depth;
}
