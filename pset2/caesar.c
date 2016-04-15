/**
 * caeser.c
 * 
 * Encrypts text using caeser cipher method
 * 
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <cs50.h>
 #include <string.h>
 #include <ctype.h>
 
 int main(int argc, string argv[])
 {
     int k;
     if (argc != 2)
     {
        printf("Enter correct input\n");
        return 1;
     }
     else 
     {
         k=atoi(argv[1]);
         if (k >= 0)
         {
            string message = GetString();
            for (int i=0, n = strlen(message); i < n; i++)
            {
                 int cipher;
                 k = k % 26;
                 if (isupper(message[i]))
                 {
                     //formula to encrypt uppercase alphabets
                    cipher = (int)message[i] + k;
                    if(cipher > 90)
                    cipher = 64 + cipher - 90;
                 }
                else if (islower(message[i]))
                {
                    //formula to encrypt lowercase alphabets
                    cipher = (int)message[i] + k;
                    if (cipher > 122)
                    cipher = 96 + cipher - 122;
                }
                else
                     cipher = (int)message[i];
                printf("%c",(char)cipher);
            }
         printf("\n");
         return 0;
        }
        else
            return 1;
    }
}
