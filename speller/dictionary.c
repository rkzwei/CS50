// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int count;
unsigned int hvalue;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // defines temp value as number word
    hvalue = hash(word);
    // cursor variable to check for value in list
    node *cursor = table[hvalue];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor ->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hasher = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hasher += tolower(word[i]);
    }
    return hasher % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open");
        return false;
    }
    char word[LENGTH + 1];

    //executes until EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        //copies current value into node
        strcpy(n->word, word);
        hvalue = hash(word);
        //points to next node
        n->next = table[hvalue];

        table[hvalue] = n;

        count++;
    }
    fclose(file);
    return true;
}



// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count > 0)
    {
        //debug printf("%u", count);
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *ghostcursor = cursor;
            cursor = cursor -> next;
            free(ghostcursor);
        }
        if (cursor == NULL  && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
