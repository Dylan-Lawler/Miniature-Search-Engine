/*
* crawler.c - CS50 'crawler' program from Tiny Search Engine
*
* Usage: crawls through webpages given a seed URL, depth, and directory 
* Saves webpage info into unique files in given directory
*
* Dylan Lawler, CS50 Spring 2022
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/bag.h"
#include "../libcs50/webpage.h"
#include "../libcs50/memory.h"
#include "../common/pagedir.h"
#include "../common/word.h"

void crawler(char* url, char* pageDirectory, int maxDepth);
void page_scan(webpage_t *page, hashtable_t *explored, bag_t *toExplore, int maxDepth);

int main(int argc, char *argv[])
{   
    // command line may only be three arguments
    if (argc != 4){
        fprintf(stderr, "Usage: %s seedURL pageDirectory maxDepth\n", argv[0]);
        return 1; 
    }

    if ((is_valid(argv[2])) == 0){
        fprintf(stderr, "%s does not exist or is not writable\n", argv[2]);
        return 4;
    }

    // store maxdepth as an int
    int maxDepth = atoi(argv[3]);
    // makes sure 0 <= max depth <= 10
    if ((maxDepth < 0) || (maxDepth > 10)){
        fprintf(stderr, "maxDepth must be in the range [0, 10]\n");
        return 5;
    }

    // allocate memory for URL so webpage can free it later
    char* url = argv[1];
    char* urlcopy = malloc(strlen(url)+1);
    if (urlcopy == NULL){
        fprintf(stderr, "Failed to copy and allocate memory for seed URL");
    }
	strcpy(urlcopy, url);
    // makes sure link can be normalized
    if (!NormalizeURL(urlcopy)) {
    fprintf(stderr, "%s cannot be normalized\n", urlcopy);
    free(urlcopy);
    return 2;
    }
     // makes sure URL is internal
    if (!(IsInternalURL(urlcopy))){
        fprintf(stderr, "%s is not within the CS50 TSE playground\n", urlcopy);
        free(urlcopy);
        return 3; 
    }

    crawler(urlcopy, argv[2], maxDepth);
}


void crawler(char* url, char* pageDirectory, int maxDepth)
{
    int docID = 1;
    // create a webpage for the seed, add it to the to explore and explored  
    webpage_t *seed = webpage_new(url, 0, NULL);
    if (seed == NULL){
         fprintf(stderr, "Failed to make a webpage for seed URL");
         return;
    }
    bag_t *toExplore = bag_new();
    if (toExplore == NULL){
         fprintf(stderr, "Failed to make a bag to hold webpages");
         return;
    }
    hashtable_t *explored = hashtable_new(100);
    if (explored == NULL){
         fprintf(stderr, "Failed to make a hashtable to hold webpages");
         return;
    }
    bag_insert(toExplore, seed); 
    hashtable_insert(explored, url, "");
    // crawls through pages while there are still some in the bag
    webpage_t *page;
    while ((page = bag_extract(toExplore)) != NULL){
        // initialize the webpage with URL and get its HTML
        webpage_fetch(page);
        printf("%-3d Fetched: %s\n", webpage_getDepth(page),webpage_getURL(page));
        // make sure the URL has an HTML
        if (!(webpage_getHTML(page))){
            fprintf(stderr, "%s does not have a fetchable HTML\n", webpage_getURL(page));
            continue;
        }
        // create the file name with the unique id and save it to file
        page_save(page, pageDirectory, docID);
        docID++; 
        // makes sure current depth is less than max depth
        if (((webpage_getDepth(page)) < maxDepth)){ 
            // scan the pages for urls 
            page_scan(page, explored, toExplore, maxDepth);
        }
        //delete the page
        webpage_delete(page);
    }
    hashtable_delete(explored, NULL);
    bag_delete(toExplore, NULL);
}  

void page_scan(webpage_t *page, hashtable_t *explored, bag_t *toExplore, int maxDepth){
    //parse through all of the webpage's URLs 
        char *result;
        int pos = 0;
        printf("%-3d Scanning: %s\n", webpage_getDepth(page),webpage_getURL(page));
        while (((result = webpage_getNextURL(page, &pos)) != NULL)){
            printf("%-3d Found: %s\n", webpage_getDepth(page), result);
            // pass over external URLs
            if (!(IsInternalURL(result))){
                printf("%-3d IgnrExtrn: %s\n", webpage_getDepth(page), result);
                free(result);
                continue;
            }
            // ignore duplicate
            if (!(hashtable_insert(explored, result, ""))){
                printf("%-3d IgnrDupl: %s\n", webpage_getDepth(page), result);
                free(result);
                continue;
            }
            // create webpage for unexplored url and add it to the toExplore bag
            webpage_t *new = webpage_new(result, webpage_getDepth(page)+1, NULL); 
            if (new == NULL){
            fprintf(stderr, "Failed to make a webpage for seed URL");
            return;
            }
            bag_insert(toExplore, new); 
            printf("%-3d Added: %s\n", webpage_getDepth(page), result);
        }
}