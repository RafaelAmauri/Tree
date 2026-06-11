#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <cell.h>


// A compact implementation of a linked stack.
typedef struct LinkedStack {
    int numElements;
    Cell *firstCell;
} LinkedStack;

LinkedStack *createLinkedStack(); // Allocates the linked stack in the memory
void insertInLinkedStack(LinkedStack *s, Cell *cell); // Inserts a cell in the stack
void removeTopCell(LinkedStack *s); // Removes the top element from the stack.
void printStack(LinkedStack *s);

#endif
