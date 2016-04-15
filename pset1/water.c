/**
 * water.c
 * 
 * calculates number of bottles of water used to shower
 * 
 */
#include <cs50.h>
#include <stdio.h>
int main(void)
{
    printf("minutes: ");
    int len_of_shower = GetInt();
    printf("bottles: %d\n", len_of_shower * 12);
    return 0;
}
