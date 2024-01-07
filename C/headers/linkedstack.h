#include <stdio.h>
#include <stdlib.h>
#include "cell.h"


// A compact implementation of a linked stack.
typedef struct LinkedStack {
    int numElements;
    Cell *firstCell;
} LinkedStack;


/*
    Allocates the linked stack in the memory
*/
LinkedStack *createLinkedStack()
{
    LinkedStack *s = (LinkedStack*) malloc(sizeof(LinkedStack));

    s->numElements = 0;
    s->firstCell   = NULL;

    return s;
}


/*
    Inserts a cell in the stack
*/
void insertInLinkedStack(LinkedStack *s, Cell *cell)
{
    cell->next = s->firstCell;

    s->firstCell   = cell;
    s->numElements += 1;
}


/*
    Removes the top element from the stack.
*/
void removeTopCell(LinkedStack *s)
{
    if (s->numElements > 0)
    {
        Cell *aux = s->firstCell;

        s->firstCell = s->firstCell->next;
        s->numElements -= 1;

        free(aux->name);
        free(aux->fullpath);
        free(aux);
    }
}


void printStack(LinkedStack *s)
{
    Cell *c = s->firstCell;

    for(int i = 0;i < s->numElements; i++)
    {
        printf("%s\n", c->fullpath);
        c = c->next;
    }
}