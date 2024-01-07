#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "headers/linkedstack.h"


void printTreeEntry(int depth, const char *fullpath);
int isDirectory(const char *fullpath);
void addSubcontentToStack(LinkedStack *stack, char *currentFullPath, int currentDepth);
void listDir(char *WORKINGDIR, int MAXDEPTH);

int main()
{
    int MAXDEPTH = 10;
    char WORKINGDIR[4096];
    getcwd(WORKINGDIR, sizeof(WORKINGDIR));

    listDir(WORKINGDIR, MAXDEPTH);

    return 0;
}


void listDir(char *WORKINGDIR, int MAXDEPTH)
{
    // Create stack and add WORKINGDIR as the first element.
    LinkedStack *stack = createLinkedStack();
    Cell *c1 = createCell(WORKINGDIR, WORKINGDIR, 0);
    insertInLinkedStack(stack, c1);
    
    char *currentFullPath = (char*) malloc(4096);
    char *currentName     = (char*) malloc(255);
    int currentDepth;
    
    /*
        While there are elements in the stack, print the topmost element,
        pop it off the stack and add its subcontents to the stack.
    */
    while(stack->numElements > 0)
    {
        memset(currentFullPath, 0, sizeof(currentFullPath));
        memset(currentName,     0, sizeof(currentName));
        strcpy(currentFullPath, stack->firstCell->fullpath);
        strcpy(currentName,     stack->firstCell->name);

        currentDepth = stack->firstCell->depth;
        removeTopCell(stack);

        if( (MAXDEPTH != -1) && (currentDepth > MAXDEPTH) )
        {
            continue;
        }

        printTreeEntry(currentDepth, currentName);

        // This function recognizes if currentFullPath is not a directory.
        addSubcontentToStack(stack, currentFullPath, currentDepth);
    }
}


void printTreeEntry(int depth, const char *name) {
    printf("❘");

    for (int i = 0; i <= depth; i++)
    {
        printf("――");
    }

    printf("❘  %s\n", name);
}


int isDirectory(const char *fullpath)
{
    struct stat path_stat;
    stat(fullpath, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}


void addSubcontentToStack(LinkedStack *stack, char *currentFullPath, int currentDepth)
{
    if(! isDirectory(currentFullPath))
        return;
    
    DIR *dir = opendir(currentFullPath);
    if (dir == NULL) 
    {
        perror("Error opening directory!");
    }

    struct dirent *d;
    // A path can be at most 4096 characters long.
    char *pathJoiner = (char*)malloc(4096);

    // For each subcontent in dir, add it to the stack.
    while ((d = readdir(dir)) != NULL)
    {
        // readdir returns '.' and '..', so we skip those
        if( (strcmp(d->d_name, ".")  != 0) &&
            (strcmp(d->d_name, "..") != 0)
            )
        {
            memset(pathJoiner, 0, sizeof(pathJoiner));
            
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