#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Program must accept only one command line argument, which is : card.raw\n");
        return 1;
    }
    // open forensic image for reading
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        fprintf(stderr, "Could not open card.raw\n");
        return 2;
    }
FILE *img = NULL;
uint8_t byte[512];
int counter = 1;
char filename[8];
while(fread(byte, 1, 512, card) == 512)
    {
        if(byte[0] == 0xff &&
           byte[1] == 0xd8 &&
           byte[2] == 0xff &&
           (byte[3] & 0xf0) == 0xe0)
        {
            if( img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            fwrite(byte, 1, 512, img);
            counter++;
        }
        else
        {
            if(img != NULL)
            {
                fwrite(byte, 1, 512, img);
            }
        }
    }
fclose(img);
fclose(card);
return 0;
}
