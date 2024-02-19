/*
* indextest.c - CS50 test for 'index' module
*
* Usage: oldIndexFilename newIndexFilename 
*
* Dylan Lawler, CS50 Spring 2022
*/

#include <stdlib.h>
#include <stdio.h>
#include "index.h"

int main(int argc, char *argv[])
{
    // make sure two arguments are included with the program 
    if (argc != 3){
         fprintf(stderr, "Usage: oldIndexFilename newIndexFilename");
    }

    // save the index info from the old file
    char *oldIndexFile = argv[1];
    index_t *index = index_load(oldIndexFile);

    // write the old index file info in to the new index file
    char *newIndexFile = argv[2];
    index_save(index, newIndexFile);

}