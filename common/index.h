/* 
* index.h, header file for index.c
*
* Inherits hashtable to store counters as set item
* Tracks word frequency in each webpage
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

/**************** global types ****************/
/* inherits hashtable struct*/
typedef hashtable_t index_t; 

/**************** index_new() ****************/
/* creates a new hashtable, see hashtable.h's hashtable_new()*/
index_t* index_new(const int numslots);

/**************** index_insert() ****************/
/* 
* Caller provides: 
*   index to be inserted into and number of slots of the hashtable
* 
* item of hashtable MUST be a counter, see hashtable_insert()
*/
bool index_insert(index_t *index, char *key, counters_t *ctr);

/**************** index_find() ****************/
/* 
* returns the counter for the provided key word
* 
* see hashtable_find()
*/
counters_t* index_find(index_t *index, const char *key);

/**************** index_delete() ****************/
/* 
* deletes the hashtable index and the counters withtin in
*
* see hashtable_delete() and counters.h's counters_delete()
*/
void index_delete(index_t *index);

/**************** index_load() ****************/
/* 
* loads information from a file into an index
*
* Caller provides:
*   filename to read index information from
*
* We return: 
*   a filled index with the information from the file
*
* Caller is responsible for deleting the index later on
*/
index_t* index_load(char* index_file);

/**************** index_save() ****************/
/*
* Opposite of index_load(), writes index data into a file 
*
* Caller provides: 
*   index to take info from, file to write the data into 
* 
* We return:
*   a boolean that is true if successful
*/
bool index_save(index_t* index, char* index_file);



