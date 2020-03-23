#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
//Get k
//test key is composed of characters
{
    if (argc != 2)
    {
    printf("Please give us a string of characters\n");
    return 1;
    }
    else if(argc == 2)
    {
    string k = (argv[1]);
    for(int a = 0, b = strlen(k); a < b; a++)
    {
            if (!isalpha(k[a]))
            {
                printf("please provide us only with characters\n");
                return 1;
            }
    }
        int j = 0;

        //ask the user for a string

        printf("plaintext: ");
        string p = get_string();
        //Encypher the text
        printf("ciphertext: ");
        char y;
        char o;
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            int d = strlen(k);
            {
            if (isupper(p[i]))
            {
                y = (p[i] - 'A' + toupper(k[j%d]) - 'A') % 26 +'A';
                printf("%c", y);
                j++;

            }
            else if (islower(p[i]))
            {
                o = (p[i] - 'a' + tolower(k[j%d]) - 'a') % 26 + 'a';
                printf("%c", o);
                j++;
            }
            else
            {
                printf("%c", p[i]);
            }
            }
        }
        printf("\n");
    }
}
