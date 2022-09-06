#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2) // Checking whether command line contains only two arguments
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26) // Checking whether the arguments conatains 26 letters
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else // Checking whether the key contains only non repeating characters and alphabets
    {
        int flag = 0;
        for (int i = 0; i < strlen(argv[1]);
             i++) // Iterating through the key and checking whether key contains only non repeating characters and alphabets
        {
            if (isalpha(argv[1][i]) == 0)
            {
                flag++;
            }
            for (int j = 0; j < strlen(argv[1]); j++)
            {
                if (argv[1][i] == argv[1][j] && i != j)
                {
                    flag++;
                }
            }
        }
        if (flag != 0)
        {
            printf("Error: Please enter a non-repeating and only alphabetic characters in the key");
            return 1;
        }
    }
    string plain = get_string("plainstring:  ");
    string cipher = "";
    int len = strlen(argv[1]);
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++) // Iterating through plaintext and replacing it with CLI argument
    {
        if (isupper(plain[i]))
        {
            printf("%c", toupper(argv[1][((int) plain[i]) - 65])); // Directly printing the cipher characters
        }
        else if ((islower(plain[i])))
        {
            printf("%c", tolower(argv[1][((int) plain[i]) - 97])); // Directly printing the cipher characters
        }
        else
        {
            printf("%c", plain[i]); // Directly printing the cipher characters as raw
        }
    }
    printf("\n");
    return 0;
}