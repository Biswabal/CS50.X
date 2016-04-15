/**
 * initials.c
 * 
 * Displays only the initials of the name
 * 
 */
 
 #include <stdio.h>
 #include <string.h>
 #include <cs50.h>
 #include <ctype.h>
 
 int main(void)
 {
     string name = GetString();
     int i=0;
     printf("%c", toupper(name[i]));
     while (name[i] != '\0')
     {
        if (name[i] == ' ')
            printf("%c", toupper(name[i+1]));
        i++;
     }
     printf("\n");
     return 0;
 }
