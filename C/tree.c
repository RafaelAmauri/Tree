#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// Cell for the linked stack.
typedef struct Cell {
    struct Cell *next;
    char *path;
} Cell;


// Linked Stack referencing the first element.
typedef struct LinkedStack {
    int numElements;
    Cell *firstCell;
} LinkedStack;


void createLinkedStack(LinkedStack *s);
void createCell(Cell *cell, char *path, Cell *parent);
void insertInLinkedStack(LinkedStack *s, Cell *cell);


void listDir(char* ROOT, int DEPTHLEVEL)
{
    DIR *dir;

    if ((dir = opendir(ROOT)) == NULL)
    {
        perror("opendir() error");
    }
    else
    {
        printf("Success");
    }

}


int main()
{
    int DEPTHLEVEL = -1;
    char ROOT[] = "./";
    
    LinkedStack *s = (LinkedStack*) malloc(sizeof(LinkedStack));

    Cell *c1 = (Cell*) malloc(sizeof(Cell));
    Cell *c2 = (Cell*) malloc(sizeof(Cell));

    createLinkedStack(s);

    s->firstCell = c1;

    createCell(c1, "1", NULL);
    createCell(c2, "2", c1);

    insertInLinkedStack(s, c1);
    insertInLinkedStack(s, c2);

    printf("%d\n", s->numElements);
    printf("%s\n", s->firstCell->path);

    return 0;
}


void createLinkedStack(LinkedStack *s)
{
    s->numElements = 0;
    s->firstCell   = NULL;
}


void createCell(Cell *cell, char *path, Cell *parent)
{
    cell->path   = path;

    if(parent != NULL)
        parent->next = cell;
}


void insertInLinkedStack(LinkedStack *s, Cell *cell)
{
    cell->next = s->firstCell;

    s->firstCell   = cell;
    s->numElements += 1;
}