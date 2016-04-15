/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes the bmp image to given scale factor.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }
    
    // ensures n is a positive integer less than or equal to 100
    int n = atoi(argv[1]);
    if (n > 100 || n < 1)
    {
        printf("n must be positive integer less than or equal to 100");
        return 2;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }
    
    // keep tracks of original image width and height
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    
    // updates the width and height for the new image
    bi.biWidth *= n;
    bi.biHeight *= n;
    
    // determine padding for scanlines
    int oldPadding =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //update biSizeImage and bfSize
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof(RGBTRIPLE)) + newPadding);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // this stores the information of a scanline for original and new image
    RGBTRIPLE* oldScanLine = malloc(oldWidth * sizeof(RGBTRIPLE));
    RGBTRIPLE* newScanLine = malloc(bi.biWidth * sizeof(RGBTRIPLE));

    // iterate over infile's scanlines
    for (int i = 0, oldht = abs(oldHeight); i < oldht; i++)
    {
        // reads the scanline of an old image
        fread(oldScanLine, sizeof(RGBTRIPLE), oldWidth,inptr);
        int newIndex=0;
        
        // horizontal scaling
        for (int k = 0; k < oldWidth; k++ )
        {
            for(int l = 0; l < n; l++)
            {
                newScanLine[newIndex++] = oldScanLine[k];
            }
        }
        
        //vertical scaling and padding
        for (int k = 0; k < n; k++)
        {
            fwrite(newScanLine,sizeof(RGBTRIPLE), bi.biWidth,outptr);
            for (int l = 0; l < newPadding; l++)
            {
                fputc(0x00, outptr);
            }
        }
        
        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

    }
    free(oldScanLine);
    free(newScanLine);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
