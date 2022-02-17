// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];
int countwords = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // determine hash
    int hashre = hash(word);

    //new current node
    node * curr = table[hashre];

    while (curr != NULL)
    {
        if (strcasecmp(word, curr->word) == 0)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //sum for our return value
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        //uses value of letter
        sum = sum + tolower(word[i]);
    }
    //returns sum is devided by N (only full numbers)
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    // open the file for reading

    // exit if the file could not be opened
    if (file == NULL)
    {
        printf("Error opening file(s).\n");
        return false;
    }

    // copy the content from the file to the copy one character at a time

    char words[LENGTH + 1];

    while (fscanf(file, "%s", words) != EOF)
    {
        // TODO: Allocate memory for new person
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }

        strcpy(new->word, words);

        int hashre = hash(words);

        new->next = table[hashre];
        table[hashre] = new;

        countwords++;

    }

    // close the files when we are done with them
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return countwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {

        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
