/**
 * mario.c
 * 
 * prints half pyramid using '#' (mario)
 * 
 */

#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int ht_of_pyramid, i, j;
    do
    {
      printf("height: ");
      ht_of_pyramid = GetInt();
    }while (ht_of_pyramid < 0 || ht_of_pyramid > 23);

    for (i = 1; i <= ht_of_pyramid; i++)
    {
        for (j = i; j < ht_of_pyramid; j++)
        {
            printf(" ");
        }
        for (j = 1; j <= i+1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
