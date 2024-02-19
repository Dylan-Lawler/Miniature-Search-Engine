# TSE Querier Design Spec

 **querier** Given a crawler produced directory and indexer produced index file, querier prompts the user to search for words and prints any files that may match the search, ranked by their score for how well they match.

### User interface

The querier takes command line arguments, which are a crawler directory and index file (see structure below).

```
querier pageDirectory indexFile
```

The querier also reads from stdin, prompting the user to search for words. The querying ends when the user presses control d to end the stdin. (see example)

```
Query? this 
Query: this 
Matches 1 documents (ranked)
score     1 doc     1: http://cs50tse.cs.dartmouth.edu/tse/letters/index.html
-----------------------------------------------

Query? 
```
### Inputs and outputs

Input: Crawler produced directory and Indexer file passed to command line. Word queries passed to stdin from keyboard.

Output: A ranked list of all the files that match the query, ranked by their score. See example in user interface.


### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules
 2. *parse query*, which ensures the query is valid and prints out the cleaned version
 3. *tokenizer*, which separates the query into an array of word pointers
 4. *load_score*, which goes through the index file and scores the files based on the query
 5. *print_documents*, which prints the result files, ranked by their scores

And some helper modules that provide data structures:

 1. *hashtable* inherited by index to hold words and file frequencies
 2. *counter* item in the index that stores file ID and word frequency pairs
 3. *webpage* holds a websites URL (among other things but only URL is utilized in querier)

### Pseudo code for logic/algorithmic flow

The indexer will run as follows:

1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters, initialize other modules, load index from the file
3. Go through each query:
    - Get the number of words of the query, ignoring empty queries
    - Tokenize the query
    - Parse the query for validity, deleting invalid queries
    - Load the scores of the files into a counter
    - Print the files in order based on their scores
    - Clean up memory 



The querier completes and exits when it has no queries left to go through. 


### Dataflow through modules

 1. *main* parses parameters and passes them to the index_build.
 2. *num_words* gets the number of words for the query, helpful for iterating over the list of words
 3. *tokenizer* creates a list of words from the provided query, separated by spaces
 4. *parse_query* parses over the query to make sure its only leters and conjuctions are in proper syntax 
 5. *load_scores* gets all the files the match the query and their scores based on word appearance
 6. *print_documents* sorts the files based on their scores and prints them in ranked order

### Major data structures

Three helper modules provide data structures:

 1. *set* of words (indirectly used by hashtable)
 2. *hashtable* of words, inherited by index
 3. *counters* the item of the hashtable, holds each file and wordcounts
 4. *webpage* holds website information, used to get and print URL

### Testing plan

0. Test the querier with no arguments

1. Test the querier with an unacceptable directory

2. Test the querier with a non readable file

3. Test the querier with a file of all possible unacceptable queries

4. Test the querier with 10 queries from fuzzquery with letters depth 6

5. Test the querier with 10 queries from fuzzquery with wikipedia depth 1

