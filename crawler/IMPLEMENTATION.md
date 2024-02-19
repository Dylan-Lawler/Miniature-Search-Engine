# TSE Crawler Implementation Spec

## Interface
See Pseudo Code for specific details. 
```c
int main(int argc, char *argv[]); 
```
    Takes a seed URL, directory, and search depth as arguments from the command line and checks their validity

```c
void crawler(char* url, char* pageDirectory, int maxDepth);
```
    Takes the seed URL, directory, and depth as parameters, crawls through the pages from the seed and saves them into files in the directory. 
```c
void page_scan(webpage_t *page, hashtable_t *explored, bag_t *toExplore, int maxDepth)
```
    Takes a webpage, hashtable, bag, and depth as parameters, and scans each page for URLS and until depth has been reached, keeping track of visited ones. 


## Pseudo Code

### Main
```c
int main(int argc, char *argv[]); 
```
    1. Parse through the arguments and make sure there are exactly three plus the program call 
    2. Make a dyanamic copy of the url and make sure it can be normalized and is internal
    3. make sure the directory is valid (see pagedir.h)
    4. make sure the depth is in the range of [0,10]
    5. call crawler function 

### Crawler
```c
void crawler(char* url, char* pageDirectory, int maxDepth);
```
    1. Initialize an integer for the unique file ID
    2. Initialize the given seed url into a webpage struct (see webpage.h)
    3. Initialize a bag to put the webpages that need to be explored and a hashtable for webpages that have already been explored (see bag.h and hashtable.h)
    4. Insert the seed webpage into both the bag and the hashtable 
    5. While there are no webpages in the bag to extract:
        - Fetch the current webpage's HTML
        - Save the webpage info to a unique filename in the pageDirectory and increment the ID counter (see pagedir.h)
        - Call page_scan if the depth of the page is less than the given maxDepth
    6. Delete the webpage

### Page_Scan
```c
void page_scan(webpage_t *page, hashtable_t *explored, bag_t *toExplore, int maxDepth)
```
    1. Scan through all the linked URL's on the current page 
    2. While there are still URL's on the page (see webpage_getNextURL() for usage):
        - Check if the URL is internal (see isInternalURL())
        - Check to see if the URL is already in the hashtable
        - Create a new webpage for the URL and add it to the bag to be searched


## Data Structures
```c
webpage_t
```
- webpage for holding webpage information struct, see webpage.h

```c
bag_t
```
- bag struct for storing items, see bag.h

```c
hashtable_t
```
- bag struct for storing items, see hashtable.h

## Error Handling
Crawler parses through the command line to prevent running with wrong arguments (see pseudo code for main). Also, any time memory is allocated by initializing a date type or opening a file, a catch is written to ensure that the allocation was successful. Certain errors, such as an external URL, URL with a NULL HTML, or duplicate URL, don't halt the program.

