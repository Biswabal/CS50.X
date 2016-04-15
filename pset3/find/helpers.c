/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int count=0;
    int low = 0;
    int high = n-1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (values[mid] == value)
        {
            count++;
            break;
        }
        else if (values[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (count!=0)
        return true;
    else
        return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int i,j,count,temp;
    for (i = 0;i < n;i++)
    {
        count=0;
        for (j = 0; j < n-1; j++)
        {
            if(values[j] > values[j+1])
            {
                temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
                count++;
            }
        }
        if(count==0)
            break;
    }
    return;
}
