/**
 * greedy.c
 * 
 * calculates minimum number of coins possible to return
 * 
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    float input;
    int change,count = 0;
    printf("Oh hai! ");
    do
    {
        printf("How much change is owed?\n");
        input = GetFloat();
    }while (input < 0);
    input = input * 100;
    change = (int) round(input);

    while (change >= 25)
    {
        change = change - 25;
        ++count;
    }
    while (change >= 10)
    {
        change = change - 10;
        ++count;
    }
    while (change >= 5)
    {
        change = change - 5;
        ++count;
    }
    while (change >= 1)
    {
        change = change - 1;
        ++count;
    }
    printf("%d\n",count);
    return 0;
}
