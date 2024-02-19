# TSE Indexer Implementation Spec

## Interface
See Pseudo Code for specific details. 
```c
int main(int argc, char *argv[]); 
```
    Takes a directory, and writeable file as arguments from the command line and checks their validity. Initializes an index.

```c
void index_build(char *directory, index_t *index);
```
    Takes the directory and index as parameter, iterates over the files in the directory.
```c
webpage_t* page_load(char *directory, int docID);
```
    Takes a directory and file ID as paramaters and makes a webpage out of each file.

```c
void index_page(index_t *index, webpage_t *page, int docID);
```
    Takes an index, webpage, and file ID as parameters. Loops over all the words of the webpage and puts them into the index with their frequencies. 

## Pseudo Code

### Main
```c
int main(int argc, char *argv[]); 
```
    1. Parse through the arguments and make sure there are exactly two plus the program call 
    2. Make sure the directory given was produced by the crawler
    3. Make sure the given file is writable
    4. Initialize the index and call build.
    5. Write the index information into the given file
    6. Delete the index.

### Index Build
```c
void index_build(char *directory, index_t *index);
```
    1. Initialize an integer to loop over the file ID's
    2. Initialize a webpage:
        - While that webpage can be loaded from the current file ID:
            - Index all of the words from the page
            - Increment the docID

### Page Load
```c
webpage_t* page_load(char *directory, int docID);
```
    1. Create a filename by forming the relative path to the file with the given directory and file ID
    2. Open the file using the formed file name
    3. Read the url from the first line
    4. Read the depth from the second line as a string and store the converted integer into a separate variable 
    5. Read the HTML from the rest of the file
    6. initialize a webpage from the read URL, depth, and HTML
    7. Close the file 
    8. Free the depth string
    9. Return the webpage

### Index Page
```c
void index_page(index_t *index, webpage_t *page, int docID);
```
    1. While there are still words to read in the page:
        - Normalize the word
        - Ignore it if its less than 3 letters
        - Initialize a counter by searching the the index for the word
        - If that counter doesn't exist;
            - Initialize a new counter and add the file ID to it
            - Insert the counter into the index with the word
        -If the counter does exist: 
            - Increment the file ID's counter
        - free the word because it is a pointer
    2. Delete the webpage


## Data Structures
```c
webpage_t
```
- webpage for holding webpage information struct, see webpage.h

```c
counters_t
```
- counters struct for storing a counter for an integer, see counters.h

```c
hashtable_t
```
- bag struct for storing items, see hashtable.h

## Error Handling
Indexer parses through the command line to prevent running with wrong arguments (see pseudo code for main). Also, any time memory is allocated by initializing a date type or opening a file, a catch is written to ensure that the allocation was successful.

