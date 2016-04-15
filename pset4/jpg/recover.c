/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    typedef uint8_t  BYTE;
    
    //opening the card.raw
    FILE* file = fopen("card.raw", "r");
    
    //creating a buffer to hold values temporary
    BYTE* buf = malloc(512 * sizeof(BYTE));
    
    // keeps track of number of images
    int i=0;
    
    // temporary holds the name of the image, i.e, ###.jpg
    char title[10];
    
    // reads the whole file, 512 bytes at a time till the EOF is reached
    // it checks if it is a jpeg and copies the jpeg into a new file
    while (fread(buf, sizeof(BYTE), 512, file) != 0)
    {
        // if the starting bytes are 0xff,0xd8,0xff,(0xe0 or 0xe1) then we detect jpeg
        if (buf[0]==0xff && buf[1]==0xd8 && buf[2]==0xff && (buf[3]==0xe0 || buf[3]==0xe1 ))
        {
            sprintf(title, "%03d.jpg",i++);
            FILE* img=fopen(title,"a");
            fwrite(buf,sizeof(BYTE),512,img);
            fclose(img);
            free(buf);
            buf = malloc(512 * sizeof(BYTE));
            continue;
        }
        if (i!=0)
        {
            FILE* img=fopen(title,"a");
            fwrite(buf,sizeof(BYTE),512,img);
            fclose(img);
        }
        free(buf);
        buf = malloc(512 * sizeof(BYTE));
    }
    fclose(file);
    return 0;
}
