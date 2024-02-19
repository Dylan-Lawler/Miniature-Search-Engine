/* 
* word.h - header file for word module, handles words in webpage
*
* Implements NormalizeUrl(), turns all letters in a word to lowercase
*
* Dylan Lawler, CS 50, Spring 2022
*/

#include <ctype.h>

/**************** NormalizeWord ****************/
/* 
* takes a string as a paramater and returns the same word with all lowercase letters
*/
char* NormalizeWord(char *word);
