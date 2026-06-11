#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include <linkedstack.h>


void printTreeEntry(Cell *cell);
int isDirectory(const char *fullpath);
void addSubcontentToStack(LinkedStack *stack);
void listDir(char *WORKINGDIR, int MAXDEPTH);

int main()
{
    int MAXDEPTH = -1;
    char WORKINGDIR[4096];
    getcwd(WORKINGDIR, sizeof(WORKINGDIR));

    listDir(WORKINGDIR, MAXDEPTH);

    return 0;
}


/*
    Given a working directory, lists all subcontents of said working directory that
    are under, at most, MAXDEPTH subdirectories.
*/
void listDir(char *WORKINGDIR, int MAXDEPTH)
{
    // Create stack and add WORKINGDIR as the first element.
    LinkedStack *stack = createLinkedStack();
    Cell *c1 = createCell(WORKINGDIR, WORKINGDIR, 0);
    insertInLinkedStack(stack, c1);

    /*
        While there are elements in the stack, print the topmost element,
        pop it off the stack and add its subcontents to the stack.
    */
    while(stack->numElements > 0)
    {
        // Gets attributes of current subfile (it will always be on top of the stack)
        if( (MAXDEPTH != -1) && (stack->firstCell->depth > MAXDEPTH) )
        {
            continue;
        }

        // Prints attributes
        printTreeEntry(stack->firstCell);

        // This function recognizes if stack->firstCell is a directory, and adds its subcontents to the stack if it is.
        addSubcontentToStack(stack);
    }
}


// Prints the contents of a cell in a tree-like fashion.
void printTreeEntry(Cell *cell) {
    printf("❘");

    for (int i = 0; i <= cell->depth; i++)
    {
        printf("――");
    }

    printf("❘  %s\n", cell->name);
}


int isDirectory(const char *fullpath)
{
    struct stat path_stat;
    stat(fullpath, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}


/*
    Checks if the first cell in the stack is a directory. If it is not, remove it from the stack (its name has already been printed in listDir(), so no problem!).

    If it is a directory, gets all subfiles inside of it and adds them to the stack.
*/
void addSubcontentToStack(LinkedStack *stack)
{
    // If it is not a dir (i.e., a file), just return!
    if(! isDirectory(stack->firstCell->fullpath))
    {
        removeTopCell(stack);
        return;
    }

    // Copy contents from first cell
    int  currentDepth = stack->firstCell->depth;
    char currentFullPath[4096];
    strcpy(currentFullPath, stack->firstCell->fullpath);

    // Removes the first cell from the stack. This operation has to be done HERE, otherwise it will get burried later when
    // we add new cells for the subfiles!!
    removeTopCell(stack);

    // Open a dir pointer and check for errors.
    DIR *dir = opendir(currentFullPath);
    if (dir == NULL)
    {
        perror("Error opening directory!");
    }

    // pathJoiner will concat the current path(that can be found in the fullPath variable of the cell that was at the top of the stack) with the name of
    // the subfiles found within <dir>. We need to concat to get the full path for the subfiles.
    char *pathJoiner = (char*)malloc(4096);

    struct dirent *d;
    // For each subfile in <dir>, create a cell for it and add it to the stack.
    while ((d = readdir(dir)) != NULL)
    {
        // readdir always returns '.' and '..', so we skip those
        if( (strcmp(d->d_name, ".")  != 0) &&
            (strcmp(d->d_name, "..") != 0)
            )
        {
            // Resetting the contents in pathJoiner for the next iteration.
            memset(pathJoiner, 0, strlen(pathJoiner));

            strcat(pathJoiner, currentFullPath);
            strcat(pathJoiner, "/");
            strcat(pathJoiner, d->d_name);

            Cell *aux = createCell(pathJoiner, d->d_name, currentDepth+1);
            insertInLinkedStack(stack, aux);
        }
    }

    free(pathJoiner);
    closedir(dir);
}
