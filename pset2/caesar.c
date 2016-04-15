/**
 * vigenere.c
 *
 * Encrypts text using vigenere
 *
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <cs50.h>
 #include <string.h>
 #include <ctype.h>
 
 int main(int argc, string argv[])
 {
    if (argc!=2)
    {
        printf("Enter correct input\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        int k_len = strlen(key);
        int count=0;
        //checks all the characters of key are alphabet
        for (int i = 0;i < k_len; i++)
        {
            if (isalpha(key[i]))
                continue;
            else
            {
                count=1;
                break;
            }
        }
        if(count!=0)
        {
            printf("Enter correct input\n");
            return 1;
        }
        else
        {
            string message = GetString();
            int cipher,k;
            int j=0;
            for (int i=0, n = strlen(message); i < n; i++)
            {
                if (isupper(message[i]))
                {
                    k = ((int)(toupper(key[(j% k_len)]))-'A');
                    cipher = (int)message[i] + k;
                    if(cipher > 90)
                        cipher = 64 + cipher - 90;
                    j++;
                }
                else if (islower(message[i]))
                {
                    k = (int)(toupper(key[(j % k_len)]))-'A';
                    cipher = (int)message[i] + k;
                    if (cipher > 122)
                        cipher = 96 + cipher - 122;
                    j++;
                }
                else
                    cipher = (int)message[i];
                printf("%c",(char)cipher);
            }
            printf("\n");
            return 0;
        }
    }
 }
