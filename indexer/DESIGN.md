# TSE Indexer Design Spec

 **crawler** parses through a crawler produced directory, forms a web page from each crawler file, then indexes all the words in that webpage and how many times it occured. 

### User interface

The indexer's only interface with the user is on the command-line; it must always have two arguments.

```
indexer pageDirectory indexFile
```

### Inputs and outputs

Input: the only inputs are command-line parameters; see the User Interface above.

Output: an index of the words from all the files followed by how frequently each followed had that word (Word fileID frequency)

For example
 * example 1 1

This means a file ID'd as 1 had the word 'example' appear 1 time. 

### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules
 2. *index_build*, which loops over ever file in the directory, gets the webpage, and indexes all the words in each webpage
 3. *page_load*, which creates a page from a page_save made file
 4. *index_page*, takes a webpage and iterates over all of its words and inserts them into the indexer with the file and the frequency of the word

And some helper modules that provide data structures:

 1. *hashtable* inherited by index to hold words and file frequencies
 2. *counter* item in the index that stores file ID and word frequency pairs

### Pseudo code for logic/algorithmic flow

The indexer will run as follows:

1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters, initialize other modules
3. Go through each file in the directory
    - While there are still files:
        - Make a webpage for the file
        - Iterate over every word in the webpage
4. While there are still words in the webpage:
    - Normalize the word
    - Ignore the word if it's less than three characters
    - If the word doesn't exist in the index already, put it in and add the webpages's frequency 
    - If the word already exists, increment the webpages tally for that word 


 *hashtable* abstract data structure denies any promise about the order of iterated items iterated. Thus, the when an index is built from a file, it may not be in the same order as the file that is created by saving an index. 


The indexer completes and exits when it has no files left to create webpages from. 


### Dataflow through modules

 1. *main* parses parameters and passes them to the index_build.
 2. *index_build* passes loops over all the files in the directory and passes them to page_load
 3. *page_load* creates a webpage struct out of every file and passes that back to indexer, who passes the page to index_page. 
 4. *index_page* loops over every word in the webpage, adding it to the index and keeping track of all the files that have that word and how many times

### Major data structures

Three helper modules provide data structures:

 1. *set* of words (indirectly used by hashtable)
 2. *hashtable* of words, inherited by index
 3. *counters* the item of the hashtable, holds each file and wordcounts

### Testing plan

0. Test the indexer with no arguments

1. Test the indexer with an unacceptable directory

2. Test the indexer with a non writable file

3. Test the crawler with the letters-index crawler directory at depth 0

4. Test the crawler with the letters-index crawler directory at depth 1

5. Test the crawler with the letters-index crawler directory at depth 2

6. Test the crawler with the letters-index crawler directory at depth 3

7. Test the crawler with the letters-index crawler directory at depth 4

8. Test the crawler with the letters-index crawler directory at depth 5

9. Test the crawler with the wikipedia-index crawler directory at depth 1
