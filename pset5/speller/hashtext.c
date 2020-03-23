#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#define TABLESIZE 500
#define MULTIPLIER (37)
#define LENGHT 45
int main(void)
{
    char *words = malloc(sizeof(char)*45);
    strcpy(words, "DAVID");
    printf("%lu\n", strlen(words));
    char *word = malloc(sizeof(words));
    for(int i = 0; i < strlen(words); i++)
    {
        word[i] = tolower(words[i]);
        printf("%c\n",word[i]);
    }
free(word);
free(words);
}