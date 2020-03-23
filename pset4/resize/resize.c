// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    // ensure factor is between 1 and 100
    int n = atoi(argv[1]);
    if ( n < 1 || n > 100 )
        {
            printf("please give us a factor between 1 and 100 included\n");
            return 1;
        }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // create variables for original width and height
    int originalWidth = bi.biWidth;
    int originalHeight = bi.biHeight;
    // construction of arranged BITMAPFILEHEADER and INFOHEADER
    bi.biWidth *= n;
    bi.biHeight *= n;
    int padding_new =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding_new) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //memory allocation
    RGBTRIPLE *memory = malloc(sizeof(RGBTRIPLE)*bi.biWidth);

    // iterate over infile's scanlines
    for (int i = 0; i < abs(originalHeight); i++)
    {
        int tracker = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < originalWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //write pixel to buffer n times
            for(int count = 0; count < n; count++)
            {
                *(memory+(tracker)) = triple;
                tracker++;
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        //write rgbtriple to outfile
        for(int y = 0; y < n; y++)
        {
        fwrite((memory), sizeof(RGBTRIPLE), bi.biWidth, outptr);
        // write padding to outfile
                for (int k = 0; k < padding_new; k++)
                {
                    fputc(0x00, outptr);
                }
        }
    }

    free(memory);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
