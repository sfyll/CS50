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
//Repeat until end of card
    FILE *img= NULL;
    int counter = 1;
    typedef uint8_t BYTE;
    BYTE ptr[512];
    char filename[8];
    //read 512 bytes into a buffer
    while(fread(ptr, 1, 512, card) == 512)
    {
        //start of a new JPEG
        if(ptr[0] == 0xff &&
           ptr[1] == 0xd8 &&
           ptr[2] == 0xff &&
           (ptr[3] & 0xf0) == 0xe0)
        {
            //close current image if there is any
            if(img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            fwrite(ptr, 1, 512, img);
            counter++;
        }
        else
        {
            if (img != NULL)
            {
                fwrite(ptr, 1, 512, img);
            }
        }
    }
    fclose(img);
    fclose(card);
return 0;
}
