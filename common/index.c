/* 
* index.c 'index' module, inherets hashtable
*
* see index.h and hashtable.h for details
*
* Dylan Lawler, CS50, Spring 2022
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../libcs50/memory.h"
#include "index.h"

void save_item (void *arg, const char *key, void *item);
void save_counts (void *arg, const int key, int count);
void delete_item(void *item);

/**************** index_new() ****************/
/* see index.h for description */
index_t* index_new(const int numslots)
{
    // creates a new index hashtable
    index_t *index = assertp(hashtable_new(numslots), "new hashtable");
    return index; 
}

/**************** index_insert() ****************/
/* see index.h for description */
bool index_insert(index_t *index, char *key, counters_t *ctr)
{
    // insert word and counter into hashtable
   return hashtable_insert(index, key, ctr);
}

/**************** index_find() ****************/
/* see index.h for description */
counters_t* index_find(index_t *index, const char *key)
{
    // return the counter of the given word
    return hashtable_find(index, key);
}

/**************** index_delete() ****************/
/* see index.h for description */
void index_delete(index_t *index)
{
    // delete the hashtable and counteritems
    hashtable_delete(index, delete_item);
}

/**************** index_load() ****************/
/* see index.h for description */
index_t* index_load(char* index_file)
{
    // make sure file exists and is readable
    FILE *fp = fopen(index_file, "r");
    if (!fp){
        fprintf(stderr, "failed to open %s\n", index_file);
        exit (1);
    }

    // create index to save info from file
    index_t *index = assertp(index_new(200), "new index");
    char *word;
    // for every line in file
    while ((word = freadwordp(fp)) != NULL){
        // create a counter for the specific word
        counters_t *counter = assertp(counters_new(), "new counter");
        // insert word and empty counter
        index_insert(index, word, counter);
        // read id and frequency pairs
        int id;
        int freq;
        while (fscanf(fp, " %d %d", &id, &freq) == 2){
            // add pair into the word's counter
            counters_set(index_find(index, word), id, freq);  
        }
        free(word);
    }
    fclose(fp);
    return index; 
}

/**************** index_save() ****************/
/* see index.h for description */
bool index_save(index_t* index, char* index_file)
{
    // open a file to write index data into
    FILE *fp = fopen(index_file, "w");
    if (!fp){
        return false;
    }
    // iterate over all hashtable items to print to file
    hashtable_iterate(index, fp, save_item);
    fclose(fp);
    return true;
}


/******** helper to save item in hashtable ********/
void save_item (void *arg, const char *key, void *item)
{
	FILE *fp = arg; 
	counters_t *c = item;
    // print word key into given file
	fprintf(fp, "%s", key);
    // get the files and frequency counters for given word 
	counters_iterate(c, fp, save_counts);
	fprintf(fp, "\n");
}

/******** helper to save items in counters ********/
void save_counts (void *arg, const int key, int count)
{
    // print the file frequency pairs
	FILE *fp = arg; 
	fprintf(fp, " %d %d", key, count);
}

void delete_item(void *item){
    if (item){
        counters_delete(item);
    }
}


