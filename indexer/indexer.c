/*
* indexer.c - CS50 'indexer' program from Tiny Search Engine
*
* Usage: inverted index of words that is written into a file 
*
* Dylan Lawler, CS50 Spring 2022
*/


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "pagedir.h"
#include "index.h"
#include "word.h"
#include "hashtable.h"
#include "bag.h"
#include "webpage.h"
#include "memory.h"

static void parse_args(const int argc, char *argv[], char **pageDir, char **fileName);
void index_build(char *directory, index_t *index); 
void index_page(index_t *index, webpage_t *page, int docID);

int main(int argc, char *argv[])
{
    // assign the parameters to variables
    char *pageDir = NULL;
    char *fileName = NULL;
    // parse and ensure correct arguments
    parse_args(argc, argv, &pageDir, &fileName);
    // index for all files words 
    index_t *index = assertp(index_new(500), "new index");
    // build the index by storing all the words and frequencies
    index_build(pageDir, index);
    // save the index to the given file
    index_save(index, fileName);
    // delete the index and return successfully
    index_delete(index); 
    return 0;
}

static void parse_args(const int argc, char *argv[], char **pageDir, char **fileName)
{
    // exit if there aren't two arguments with the program      
    char *program = argv[0];
    if (argc != 3){
        fprintf(stderr, "Usage: %s pageDirectory indexFilename\n", program);
        exit (1); 
    }
    // exit if the directory is not made by a crawler
    *pageDir = argv[1];
    if(!(is_crawler(*pageDir))){
        fprintf(stderr, "%s is not a Crawler produced directory\n", *pageDir);
        exit (2);
    } 
    // exit if the indexfile provided doesnt exist
    *fileName = argv[2];
    FILE *indexfile;
    if (!(indexfile = fopen(*fileName, "w"))){
        fprintf(stderr, "%s does not exist or is not a writable file\n", *fileName);
        exit (2);
    }
    fclose(indexfile);
}

void index_build(char *directory, index_t *index)
{   
    // integer to iterate over the directory files
    int docID = 1;
    // while there is a page to read over
    webpage_t *page;
    while ((page = page_load(directory, docID))!= NULL){
        // update the index with all of the file words 
        printf("Indexing %s from document %d\n", webpage_getURL(page), docID);
        index_page(index, page, docID);
        // iterate to the next file
        docID++;
    }
}

void index_page(index_t *index, webpage_t *page, int docID)
{
    // while there are still words to be read
    int pos = 0;
    char *result;
    while ((result = webpage_getNextWord(page, &pos)) != NULL) {
        // normalize the word into all lowercase
        char *word = NormalizeWord(result);
        // ignore words less than three characters
        if (strlen(word) < 3){
            free(word);
            continue;
        }
        //if the word doesn't exist in the index, create a counter for it and insert 
        counters_t *counter = index_find(index, word);
        if (!counter){
            counter = assertp(counters_new(), "new counter");
            counters_add(counter, docID);
            index_insert(index, word, counter);
        }
        // increment the file counter if the word already exists in the index 
        else{
            counters_add(counter, docID);
        }
        free(word);
    }
    webpage_delete(page);
}