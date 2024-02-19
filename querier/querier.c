/*
* querier.c - CS50 'querier' program from Tiny Search Engine
*
* Usage: reads stdin and sees if any words match a webpage's word index
*
* User Provides: A crawler directory as well as and Indexer saved file
* Also provides a line by line query to see if their search matches any documents from the given directory
*
* Output: a ranked list of urls that have words matching the search, or a statement that says none match
* Only allows for letter based searches, also prevents conjunctions starting or ending the query and being searched in sequence
*
* Dylan Lawler, CS50 Spring 2022
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "pagedir.h"
#include "index.h"
#include "word.h"
#include "hashtable.h"
#include "bag.h"
#include "webpage.h"
#include "memory.h"

// struct to iterate over two counters at once
struct twocts {
	counters_t *result;
	counters_t *another;
};

// returns the minimum between two integers
static inline int min(const int a, const int b) {
  return (a < b ? a : b);
}

// local functions
static void parse_args(const int argc, char *argv[], char **pageDir, char **fileName);
void parse_query(char **words, int wordnum);
counters_t* load_score(char **words, index_t *index, int wordnum);
int num_of_words(char *query);
char** tokenizer(char *query);
void print_documents(char *pageDir, counters_t* result);
void counters_intersect(counters_t* ct1, counters_t* ct2);
void intersect_helper(void *arg, const int key, const int count);
void counters_union(counters_t *ct1, counters_t *ct2);
void union_helper(void *arg, const int key, const int count);
int num_counters(counters_t *counter);
void num_helper(void *arg, const int key, int count);
void get_files(void *arg, const int key, int count);
char** sort_scores(counters_t *result, char** filelist, int filenum);
void delete_words(char** words, int wordnum);

int main(int argc, char *argv[])
{
    // ensures correct command line
    char *pageDir = NULL;
    char *fileName = NULL;
    parse_args(argc, argv, &pageDir, &fileName);
    // create index from the given file
    index_t *index = assertp(index_load(fileName), "Load index");
    // prompt first query
    printf("Query? ");
    // prevents the prompt from printing after the query when stdin is file redirection
    fflush(stdout);
    // while the user is searching queries
    char *query;
    while ((query = freadlinep(stdin))){
        // get the number of words for the query
        int wordnum = num_of_words(query);
        // if the query is empty continue
        if (wordnum == 0){
        free(query);
        continue;
        }
        // tokenize the query into an array of strings
        char **words = tokenizer(query); 
        // ensure its a legal query, if it's not, move onto next query
        parse_query(words, wordnum);
        if (*words == NULL){
            free(words);
            free(query);
            continue;
        }
        // get all the scores of each file into a counter
        counters_t *result = load_score(words, index, wordnum);
        // print the matching documents in ranked order of word score
        print_documents(pageDir, result);
        // delete the words array and free it
        delete_words(words, wordnum);
        free(words);
        // delete the scores result
        counters_delete(result);
        // free the query
        free(query);
        // print a separator to prompt the next query
        printf("-----------------------------------------------\n\nQuery? ");
    }
    // print a line break when the program ends
    printf("\n");
    // delete the index of words and scores
    index_delete(index);
    return 0;
}

static void parse_args(const int argc, char *argv[], char **pageDir, char **fileName)
{
    // exit if there aren't two arguments with the program      
    char *program = argv[0];
    if (argc != 3){
        fprintf(stderr, "Usage: %s pageDirectory indexFilename\n", program);
        exit (1); 
    }
    // exit if the directory is not made by a crawler
    *pageDir = argv[1];
    if(!(is_crawler(*pageDir))){
        fprintf(stderr, "%s is not a Crawler produced directory\n", *pageDir);
        exit (2);
    } 
    // exit if the indexfile provided doesnt exist
    *fileName = argv[2];
    FILE *indexfile;
    if (!(indexfile = fopen(*fileName, "r"))){
        fprintf(stderr, "%s does not exist or is not a readable file\n", *fileName);
        exit (3);
    }
    fclose(indexfile);
}

char** tokenizer(char *query)
{
    // slot in the word array
    int slot = 0;
    // word array, 8 bytes for pointer to each word
    char **words = calloc(num_of_words(query), 8);
    // buffer so query doesnt get manipulated
    char buff[strlen(query)];
    strcpy(buff, query);
    // tokenize the query into words
    char *tok = strtok(buff, " ");
    while (tok){
        // insert into the word array
        words[slot] = malloc(sizeof(tok));
        strcpy(words[slot], tok);
        // get the next word of the string
        tok = strtok(NULL, " ");
        // move to the next slot of the array
        slot++;
    }
    return words;
}

void parse_query(char **words, int wordnum){
    // integer to check if conjunctions are searched in sequence
    int check = 0;
    // loop throught the word array
    for (int i = 0; i < wordnum; i++){
        // normalize the word into all lowercase
        char *word = NormalizeWord(words[i]);
        // return an error if the user inputs a nonletter word and delete the list
        if (word == NULL){
            fprintf(stderr, "'%s' is not a valid word\n\nQuery? ", words[i]);
            delete_words(words, wordnum);
            return;
        }
        // replace the word with the normalized word
        words[i] = word;
        if ((!strcmp(words[i], "or")) || (!strcmp(words[i], "and"))){
            // if the current and previous words were both conjunctions, return an eror and delete the list
            if (check == 1){
                fprintf(stderr, "'%s' and '%s' cannot be searched in sequence \n\nQuery? ", words[i], words[i-1]);
                delete_words(words, wordnum);
                return;
            }
            // keeps track of the conjunction to prevent doubles
            check = 1;
        }
        else{
            // word isnt a conjunction
            check = 0;
        }
    }

    // delete the word list if the first word is a conjunction
    if ((!strcmp(words[0], "or")) || (!strcmp(words[0], "and"))){
        fprintf(stderr, "First search word can not be '%s'\n\nQuery? ", words[0]);
        delete_words(words, wordnum);
        return;
    }
    // delete the word list if the last word is a conjunction 
    if ((!strcmp(words[wordnum - 1], "or")) || (!strcmp(words[wordnum - 1], "and"))){
        fprintf(stderr, "Last search word can not be '%s'\n\nQuery? ", words[wordnum - 1]);
        delete_words(words, wordnum);
        return;
    }
    // print the cleaned query back to the user to see 
    printf("Query: ");
    for (int i = 0; i < wordnum; i++){
        printf("%s ", words[i]);
    }
}

counters_t* load_score(char **words, index_t *index, int wordnum)
{
    // temp to keep up with the current and sequence
    counters_t *temp = NULL;
    // total score counter after query
    counters_t *result = assertp(counters_new(), "new counter");
    // prevents saving of words in and sequence if there's an unfound word
    int save = 0;
    
    for (int i = 0; i < wordnum; i++){ 
        // don't save word until next 'or'
        if (save == 1){
             if (!strcmp(words[i], "or")){
                 save = 0;
             }

            continue;
        }
        // if the word is 'or', update the result and reset the temp,  
        if (!strcmp(words[i], "or")){
            counters_union(result, temp);
            counters_delete(temp);
            temp = NULL;
            continue;
        }
        // continue the sequence if the word is 'and'
         if (!strcmp(words[i], "and")){
            continue;
        }
        // find the word in the index
        counters_t *count = index_find(index, words[i]);
        // if the word doesn't exist, prevent further saving in the and sequence , and reset the temp
        if (count == NULL){
            save = 1; 
            counters_delete(temp);
            continue;
        }
        // if temp is empty or NULL, create a new temp and update it with the found word
        if (num_counters(temp) == 0 || temp == NULL ){
            temp =  assertp(counters_new(), "new counter");
            counters_union(temp, count);
        }
        // if the temp isn't empty, intersect it with the found word
        else{
            counters_intersect(temp, count);
        }
        // if the word is the last of the query, update the result counter and delete the temp 
        if (i == wordnum - 1){
            counters_union(result, temp);
            counters_delete(temp);
            temp = NULL;
        }
    }
    // return the scores result
    return result;
}

void print_documents(char *pageDir, counters_t* result){
    // if result is null or empty, no documents exist matching the query
    if (result == NULL || num_counters(result) == 0){
        printf("\nNo documents match.\n");
        return;
    }
    // number of files in the counter
    int filenum = num_counters(result);
    // makes a string of the files from the counters to put into a list
    char files[filenum * 22];
    strcpy(files, "");
    // put all the file numbers into the list
    counters_iterate(result, files, get_files);
    // put all the files into a list
    char **filelist = tokenizer(files);
    // sort the files based on their score
    char** sortedfiles = sort_scores(result, filelist, filenum);
    // print the number of matching files
    printf("\nMatches %d documents (ranked)\n", filenum);
    for (int i = 0; i < filenum; i++){
        // load a webpage from the file number
        webpage_t *page = page_load(pageDir, atoi(sortedfiles[i]));
        int score = counters_get(result, atoi(sortedfiles[i]));
        // ignore files with a score of zero
        if (score == 0){
            continue;
        }
        // print the score, file number, and url of the matching document
        printf("score %5d doc %5s: %s\n", score, sortedfiles[i], webpage_getURL(page));
        // delete the current file's webpage
        webpage_delete(page);
    }
    // delete the list of files
    delete_words(filelist, filenum);
    free(filelist);
}

// counts the number of words in a query
int num_of_words(char *query)
{
    //checks if a word is startin 
    int check = 0; 
    // keeps track of number of words
    int count = 0;

    for(int i = 0; i < strlen(query); i++){
        // count at first letter
        if (check == 0 && !isspace(query[i])){
            check = 1; 
            count ++; 
        }
        // don't count until next letter
        if (isspace(query[i])){
            check = 0;
        }
    }
    // return number of words
    return count; 
}

void counters_intersect(counters_t* ct1, counters_t* ct2)
{
    // go over all counternodes in both counters in 'and' expression
    assertp(ct1, "ct1 is invalid");
    assertp(ct2, "ct2 is invalid");
	struct twocts args = {ct1, ct2}; 
	counters_iterate(ct1, &args, intersect_helper);
}

void intersect_helper(void *arg, const int key, const int count)
{
	struct twocts *two = arg; 
    // set the min between the two counters to the result counter
	counters_set(two->result, key, min(count, counters_get(two->another, key)));
}

void counters_union(counters_t *ct1, counters_t *ct2)
{
    // go over all the counters for 'or' expression 
    assertp(ct1, "ct1 is invalid");
    assertp(ct2, "ct2 is invalid");
    counters_iterate(ct2, ct1, union_helper);
}

void union_helper(void *arg, const int key, const int count)
{
  counters_t *ct1 = arg;
  int count2 = count;
  // find the same key in ct1
  int count1 = counters_get(ct1, key);
  if (count1 == 0) {
    // not found: insert it
    counters_set(ct1, key, count);
  } else {
    // add to the existing value
    count1 += count2;
    counters_set(ct1, key, count1);
  }
}

int num_counters(counters_t *counter){
    // count the number of counternodes and return
    int count = 0;
    counters_iterate(counter, &count, num_helper);
    return count;
}

void num_helper(void *arg, const int key, int count){
    // increment the counter if both the key and counter aren't null
    int *numctrs = arg;
    if (numctrs != NULL && key > 0 && count > 0){
        (*numctrs)++;
    }
}

void get_files(void *arg, const int key, int count){
    // print each file number to a string
    if (count != 0){
        char *file = arg;
        char num[10];
        sprintf(num, "%d ", key);
        strcat(file, num);
    }
}

char** sort_scores(counters_t *result, char** filelist, int filenum){
    // keeps track of the highest score
    int max = 0;
    for (int i = 0; i < filenum; i++){
        // set max to current slot
        max = i;
        // looks at the next slot 
        for (int j = i + 1; j < filenum; j++){
            // if the next slot is higher than the current, set the next equal to the max scored file
            int score = counters_get(result, atoi(filelist[j]));
            int maxscore = counters_get(result, atoi(filelist[max]));
            if (score > maxscore){
                    max = j;
            }
        }
        // swap the current and the next slot
        char *temp = filelist[max];
        filelist[max] = filelist[i];
        filelist[i] = temp;
    }
    // return the sorted liste of file numbers
    return filelist;
}

void delete_words(char** words, int wordnum)
{
    // if words is already null, return it
    if (!words){
        return;
    }
    // free and null all existing words
    for (int i = 0; i < wordnum; i++){
        if(!words[i]){
            continue;
        }
        free(words[i]);
        words[i] = NULL;
    }
    // null the words array
    words = NULL;
}
