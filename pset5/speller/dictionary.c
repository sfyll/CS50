// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

    //word counter variable for dictionnary
    int wordcounter = 0;


    //construct the structure of the dictionnary
    #define TABLESIZE 10000
    #define LENGHT 45

    typedef struct node
    {
        char word[LENGHT + 1];
        struct node *next;
    }
    node;
    node* hashtable[TABLESIZE];

    //Hash function from the following link : http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
    //const char means that the value at the pointed location cannot be changed
    #define MULTIPLIER (37)
    unsigned long hash(const char *s)
    {
        unsigned long h;
        unsigned const char *us;

        /* cast s to unsigned const char * */
        /* this ensures that elements of s will be treated as having values >= 0 */
        us = (unsigned const char *) s;

        h = 0;
        while(*us != '\0')
        {
            h = (h * MULTIPLIER + *us)%TABLESIZE;
            us++;
        }

        return h;
    }

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int leng =strlen(word);
    char words[leng + 1];
    //hash the word
    for(int i = 0; i < leng; i++)
    {
            words[i] = tolower(word[i]);
    }
    words[leng]='\0';
    unsigned long index = hash(words);
    //pointer to the head of the list
    node *cursor = hashtable[index];
    while(cursor != NULL)
    {
        if( strcmp(cursor -> word, words) == 0)
        {
            return true;
        }
        else
        {
        cursor = cursor -> next;
        }
    }
return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //construct the dico file and a temporary variable to pass the value to the file
    char *dword = calloc((LENGHT + 1), sizeof(char));
    FILE *dico = fopen(dictionary, "r");
    if (dico == NULL)
    {
        fprintf(stderr, "Could not open large\n");
        return 2;
    }

    //scan for each word of large, pour l'instant erreur et que rien ne vas dans espace alloué
    while(fscanf(dico, "%45s", dword)!= EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(new_node -> word, dword);
            unsigned long hashkey = hash(new_node -> word);

            //check if spot in table exists; if not, start the linked list
            if(hashtable[hashkey] == NULL)
            {
                hashtable[hashkey] = new_node;
                new_node -> next = NULL;
            }
            else
            {
                new_node -> next = hashtable[hashkey];
                hashtable[hashkey] = new_node;
            }
        wordcounter++;
        }
    }
    fclose(dico);
    free(dword);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return (wordcounter);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < TABLESIZE; i++)
    {
        node *cursor = hashtable[i];
        while(cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
return true;
}
