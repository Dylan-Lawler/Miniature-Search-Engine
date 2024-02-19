/* 
 * pagedir.c - CS50 'pagedir' module
 *
 * see pagedir.h for more information.
 *
 * Dylan Lawler, CS50, Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
#include "../libcs50/memory.h"

int is_valid(char *dirpath)
{
    //concatenate file to directory path
    char filename[strlen(dirpath) + 10];
    sprintf(filename, "%s/.crawler", dirpath);
    
    // checks if directory exists
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL){
        return 0; 
    }
    else{
        fclose(fp);
        return 1;
    }
}

void page_save(webpage_t* page, char* dirpath, int docID)
{
    //concatenate file to directory path
    char fname[strlen(dirpath) + 11];
    sprintf(fname, "%s/%d", dirpath, docID);

    // check writability for file
    FILE *fp = fopen(fname, "w"); 

    if (fp == NULL){
        fprintf(stderr, "cannot open file for writing\n");
        return;
    }
    // print the url and the html as the first two lines of the file
	fprintf(fp, "%s\n%d\n%s", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
    fclose(fp);
}

webpage_t* page_load(char *directory, int docID)
{
    // concatenates file and directory name into relative path
    char filename[strlen(directory) + 11];
    sprintf(filename, "%s/%d", directory, docID);
    // ensures file exists and is readadble
    FILE *fp = fopen(filename, "r");
    if (!fp){
        return NULL;
    }    // gets url from first line
    char *url = freadlinep(fp);
    // gets depth from second line
    char *depthstr = freadlinep(fp);
    int depth = atoi(depthstr);
    // gets html from the rest of the file
    char *html = freadfilep(fp);
    //create webpage and return it
    webpage_t *page = assertp(webpage_new(url, depth, html), "new webpage"); 
    //close file and return built webpage
    fclose(fp);
    free(depthstr);
    return page;
}

bool is_crawler(char *pageDir)
{
    // string size of pagedirectory/.crawler
    char filename[strlen(pageDir) + 11];
    sprintf(filename, "%s/.crawler", pageDir);
    FILE *fp;
    if (!(fp = fopen(filename, "r"))){
        return false;
    }
    fclose(fp);
    return true;
}



