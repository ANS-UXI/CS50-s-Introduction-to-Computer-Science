#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char get_cipher(char plain, int x, string argv);

int main(int argc, string argv[])
{
    if (argc != 2) // Checking whether command line contains only two arguments
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else // Checking whether the key contains only digits
    {
        int flag = 0;
        for (int i = 0; i < strlen(argv[1]);
             i++) // Iterating through the key and checking whether key contains only non repeating characters and alphabets
        {
            if (isdigit(argv[1][i]) == 0)
            {
                flag++;
            }
        }
        if (flag != 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    string plain = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isupper(plain[i]))
        {
            char ciph = get_cipher(plain[i], 65, argv[1]);
            printf("%c", ciph); // Printing char one by one
        }
        else if (islower(plain[i]))
        {
            char ciph = get_cipher(plain[i], 97, argv[1]);
            printf("%c", ciph); // Printing char one by one
        }
        else
        {
            printf("%c", plain[i]); // Printing char one by one
        }
    }
    printf("\n");
    return 0;
}

char get_cipher(char plain, int x, string argv) // Returning the equivalent cipher text
{
    int dec = (int) plain;
    int ciph = dec + atoi(argv);
    while (ciph > (x + 25)) //Checking whether the ciph value is above the threshold
    {
        ciph -= 26;
    }
    return (char) ciph;
}