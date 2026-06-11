#include <cell.h>

Cell *createCell(char *fullpath, char *name, int depth)
{
    Cell *cell = (Cell*) malloc(sizeof(Cell));

    cell->fullpath = (char*) malloc(4096);
    strcpy(cell->fullpath, fullpath);

    cell->name = (char*) malloc(255);
    strcpy(cell->name, name);

    cell->next  = NULL;
    cell->depth = depth;

    return cell;
}
