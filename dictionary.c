// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH +1) * 'z';

// Hash table
int sum_words = 0;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //obtain hash index
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, word)==0)
        {
            return true;
        }
        cursor = cursor -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //hash function
    int sum= 0;
    for (int i = 0; i< strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opening dictionary.h which contains small/large files
   FILE *file =  fopen(dictionary, "r'");
   if (file == NULL)
    {
    return false;
    }

    //Read a word each time from the file, using a loop to cover all the words in the text.
    char  word[LENGTH + 1];
   while(fscanf(file, "%s", word) != EOF)
    {
       //Create a new node
       node *new_node = malloc(sizeof(node));
       if(new_node== NULL)
       {
           return false;
       }
       // copy the word into the node
       strcpy(new_node->word, word);
       new_node -> next = NULL;
       //Getting the suitable hash index
       int index = hash(word);

       if (table[index] == NULL)
        {
            table[index] = new_node;
        }

         else
            {
                new_node ->next = table[index];
                table[index] = new_node ;
             }

            sum_words++;
     }
       fclose(file);
        return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the size of words by using the variable sum_words that loads in real time with the load function
    return sum_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    /// Freeing allocated memory
    for (int i = 0 ; i<N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        
        while(cursor != NULL)
        {
            cursor = cursor -> next;
            free (tmp); 
            tmp = cursor;
        }
    }
    return true;
}
