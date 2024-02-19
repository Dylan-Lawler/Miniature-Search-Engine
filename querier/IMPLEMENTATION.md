# TSE Querier Implementation Spec

## Interface
See Pseudo Code for specific details and helper functions.
```c
int main(int argc, char *argv[]); 
```
    Takes a directory, and readable index file as arguments from the command line and reads queries from stdin. Loads an index from the given file.

```c
static void parse_args(const int argc, char *argv[], char **pageDir, char **fileName);
```
    Takes the command line and ensures theres only two arguments, the directory is from crawler, and the file is readable
```c
void parse_query(char **words, int wordnum);
```
    Takes the tokenized list of words and makes sure it consists only of letters and that conjunctions aren't first, last, or in sequence. Also normalizes the words and prints them for user to see 'cleaned' query.

```c
char** tokenizer(char *query);
```
    Takes the stdin query and tokenizes it by spaces and returns a list of separated words. 

```c
counters_t* load_score(char **words, index_t *index, int wordnum);
```
    Takes the word list, index, and number of words in the query and creates a counter of file numbers and each of their word scores for the given query. 

```c
void print_documents(char *pageDir, counters_t* result);
```
    Takes the provided crawler directory and the result counter of file scores. Puts the files into a list and sorts the list based on the file scores. Loops through the list and prints out the score, document, and url that matches the query.


## Pseudo Code

### Main
```c
int main(int argc, char *argv[]); 
```
    1. Initialize variables for the arguments, pass the arguments and the command line to parse_args ensure it is acceptable
    2. Load a word index from the file provided as an argument
    3. Prompt the users first query
    4. While their is still a query to be read:
        - Pass the query to num_of_words to get the number of words in the query
        - Ignore empty query, free the query pointer
        - Tokenize the query into a list of separated words
        -  Pass the list to parse_query to make sure the query is acceptable
        - If the query is invalid, delete the list of words and free the query pointer
        - If the query is valid, pass the list and index to load_score get the result counter of word scores from the files 
        - Pass the result and crawler directory to print_documents to print the results in ranked order based on score
        - Delete words and result. Free query pointer and prompt a new query
    5. Delete the index after user is done querying

### Parsing the Arguments
```c
static void parse_args(const int argc, char *argv[], char **pageDir, char **fileName);
```
    1. If the number of arguments isn't three including the program, exit with error
    2. If the directory provided isn't made by the crawler program, exit with error 
    3. If the file provided isn't readable, exit with error

### Number of Words in the Query 
```c
int num_of_words(char *query)
```
    1. Initialize a check (to check if its the first non-space) and count (for the number of words) integer
    2. Until you hit the end of the query:
        - If its the first space, change the check to true, increment the number of words
        - If the character isn't a space, check is false
    3. return the count
    
### Tokenizing the Query
```c
char** tokenizer(char *query);
```
    1. Initialize an integer that will keep track of the current slot of the array
    3. Initialize an array based on the number of words in the query an the fact that each word will be a pointer of 8 bytes
    4. Initialize a buffer and copy the query into it so the query isn't manipulated
    5. Initialize a token word pointer that uses strtok with " " as the delimiter
    6. While the token exists: 
        - Allocate memory in the word array
        - Copy the token into to word array slot
        - Move on to the next token and increment the slot
    7. Return the word list

### Parsing the Query 
```c
void parse_query(char **words, int wordnum);
```
    1. Initialize a variable to keep track of conjunction use
    2. For each word in the word list: 
        - Normalize the word
        - If the word cannot be normalized, delete the word list and print an error that the word is invalid
        - replace the initial word in the word list with the normalized word 
        - If the word is a conjunction:
            - If the check was true, print an error that the user can't search conjunctions in a row and delete the word list.
            - Otherwise, check is true.
        - If the word isn't a conjunction, check is false.
    3. If the first or last word is a conjunction, print an error and delete the word list 
    4. Print the cleaned query for user to see

### Getting the File Scores
```c
counters_t* load_score(char **words, index_t *index, int wordnum);
```
    1. Initialize a temporary counter to null and a new result counter
    2. Initialize a variable to prevent saving in an and sequence if a word is not found
    3. For each word in the word list:
        - If save is false:
            - If the word is 'or', save is true, else go onto the next word.
        - If the word is 'or':
            - Merge the temp counter with the result counter
            - delete the temporary counter and move onto the next word
        - If the word is 'and' move onto the next word
        - If the word isn't a conjunction, find it in the index
        - If the word isn't found:
            - Save is false
            - Delete the temp counter and move onto the next word.
        - If the temp counter is empty or NULL:
            - Create a new temp counter and merge the found word with it
        - If temp isn't empty, intersect it with the found word
        - If it is the last word:
            - Merge result and temp counters.
            - Delete temp.
    4. Return the result counter

```c
void counters_intersect(counters_t* ct1, counters_t* ct2);
void intersect_helper(void *arg, const int key, const int count);
static inline int min(const int a, const int b);
```
    1. Ensure neither counter is NULL
    2. Create a struct to hold the two counters
    3. Iterate over every result counter's counternode: 
        - Set the result counter to the minimum between the two counters' scores

```c
void counters_union(counters_t *ct1, counters_t *ct2);
void union_helper(void *arg, const int key, const int count);
```
    1. Ensure neither counter is NULL
    2. Iterate over every result counter's counternode:
        - If the result counter doesnt have the same key, set the result counter to the value of the second counter
        - If it does have the same key, add the two counts for the key and set that value for result's key 

### Printing the Documents
```c
void print_documents(char *pageDir, counters_t* result);
```
    1. If the result counter is NULL or empty, print no documents match 
    2. Initialize a variable to get the number of counters in result
    3. Initialize a string to print the files into
    4. Iterate over all the counters and print them into the string
    5. Tokenize the file string to get a list of the files
    6. Sort the files array based on their word score
    7. Print how many documents matched the query 
    8. For each file in the file list:
        - Load a webpage from the file
        - Get the score of that file, ignoring scores of 0
        - Print the score, doc number, and url 
        - Delete the webpage for that file
    9. Delete the file list

```c
int num_counters(counters_t *counter);
void num_helper(void *arg, const int key, int count);
```
    1. Initialize an integer to count the number of counternodes
    2. Iterate over the counternodes:
        - If the key and count are both not 0, increment the count

```c
void get_files(void *arg, const int key, int count);
```
    1. If the count is not 0, print the key to the provided string

```c
char** sort_scores(counters_t *result, char** filelist, int filenum);
```
    1. Initialize an integer for the file with the max score
    2. For each file in the file list:
        - Max is that file
        - For each file in the file list (one ahead of the outer loop):
            - if the if the score of the current node is greater than that of the previous, max is the current file
        - Swap the current and the max file
    3. Return the sorted file list

### Deleting the Word List
```c
void delete_words(char** words, int wordnum)
```
    1. If the word list is null, return
    2. For each word in the list:
        - Free the word if and set it to null if it isn't already null
    3. Set the words list equal to null

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
struct twocts
```
- Holds two counters so they can be iterated over simultaneously

```c
hashtable_t
```
- bag struct for storing items, see hashtable.h

## Error Handling
Querier parses through the command line to prevent running with wrong arguments (see pseudo code for parse_args). Also, any time memory is allocated by initializing a date type or opening a file, a catch is written to ensure that the allocation was successful. Lastly, the query is endured to be correct to prevent trying to match incorrect queries (see parse_query in pseudocode)

