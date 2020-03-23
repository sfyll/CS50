#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
//Get k
{
    if (argc != 2)
    {
        printf("Please give us a figure\n");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);

        //ask the user for a string

        printf("what string would you like us to encrypt\n");
        string p = get_string();
        //Encypher the text
        printf("ciphertext: ");
        char y;
        char o;
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            if (isupper(p[i]))
            {
                y = ((((p[i] - 64) + k) % 26) + 64);
                printf("%c", y);
            }
            else if (islower(p[i]))
            {
                o = ((((p[i] - 96) + k) % 26) + 96);
                printf("%c", o);
            }
            else
            {
                printf("%c", p[i]);
            }
        }
        printf("\n");
    }
}