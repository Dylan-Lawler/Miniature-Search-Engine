/* 
* word.c - word module, handles words in webpage
*
* see word.h for details
*
* Dylan Lawler, CS 50, Spring 2022
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "word.h"

char* NormalizeWord(char *word)
{
    if (!word){
        return NULL;
    }
        // change each letter to lowercase
        for (char *p = word; *p != '\0'; p++){
            if (!isalpha(*p)){
                return NULL;
            }
            *p = tolower(*p);
        }
    // return lowercase word
    return word;
}
