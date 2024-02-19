/* 
* pagedir.h - headerfile for directory handling in TSE
*
* Provides functions that check the validity of a directory and saves webpage data to a given file
*
* CS 50
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"

/**************** is_valid ***********************************/
/* pass the pathname of a directory as a paramete
* concatenate "/.crawler" to a string with the directory path
* check if the file can be opened for writing
* return error message and 0 if not, means directory may not exist or be writable to 
* return 1 if successful
*/
int is_valid(char *dirpath);

/**************** page_save ***********************************/
/* 
* pass a webpage, file name
* returns if file fales to open for writing
* prints the url, page depth, and html respectully on their own lines
*/
void page_save(webpage_t* page, char* dirpath, int docID);

/**************** page_save ***********************************/
/* 
* pass a directory name, file number
* returns a created webpage from built from the crawler file
* returns NULL if file doesn't exist or isn't readable
*/
webpage_t* page_load(char *directory, int docID);

/**************** is_crawler ***********************************/
/* 
* pass a directory name
* 
* returns true if is crawler made ie. has an existing .crawler file
*/
bool is_crawler(char *pageDir);