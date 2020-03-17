// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 16384;

// Hash table
node *table[N];

int number_of_words = 0; /* keep track of number of words*/

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char lowercase[strlen(word) + 1]; /* make a lowercase string with same length*/
    strcpy(lowercase, word); /*copy the word*/
    for (int i = 0; i < strlen(lowercase); i++)
    {
        lowercase[i] = tolower(word[i]);
    }

    int index = hash(lowercase) % N; /* hash the word*/
    node *cursor = table[index]; /* make a pointer to the hash array*/

    while (cursor != NULL) /*keep repeating until end of linked list*/
    {
        if (strcasecmp(cursor->word, lowercase) != 0) /*if not matching*/
        {
            cursor = cursor->next; /*move pointer to the next*/
        }
        else
        {
            return true; /*word matches*/
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /*Based on djb2 algorithm link: http://www.cse.yorku.ca/~oz/hash.html*/
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) ^ c; /* hash(i - 1) * ee ^ str [i]*/
    }

    return (int)hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r"); /*open the dictionary file with read*/
    if (f == NULL) /* if file is empty*/
    {
        return false;
    }

    char word[LENGTH + 1]; /* for loading the word into buffer*/

    while (fscanf(f, "%s", word) != EOF) /* keep doing until end of file*/
    {
        node *tmp = malloc(sizeof(node)); /* make a temporary node and allocate memory*/
        tmp->next = NULL; /* this line was the cause of memory leak*/
        if (tmp == NULL) /* no memory for tmp*/
        {
            return false;
        }
        strcpy(tmp->word, word); /* copy the word into the tmp word*/

        int index = hash(tmp->word) % N; /* hash the word*/

        if (table[index] == NULL) /*the array has not been inserted*/
        {
            table[index] = tmp; /*insert it*/
        }
        else /* the array index have been used*/
        {
            tmp->next = table[index]; /*repointing process*/
            table[index] = tmp;
        }
        number_of_words++; /* increment the number of words*/
    }
    fclose(f); /*close the file*/
    return true; /*loading process is done*/
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < N; i++) /*go thru all the array in the hashtable*/
    {
        node *cursor = table[i]; /* make a cursor*/

        while (cursor != NULL) /*repeat until the end of linked list*/
        {
            node *tmp = cursor; /* make a tmp node*/
            cursor = cursor->next; /*point cursor to the next*/
            free(tmp); /* free the memory allocated*/
        }
    }

    return true;
}
