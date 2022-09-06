#include <cs50.h> //importing standardio library
#include <stdio.h> //importing cs50's library

int main(void)
{
    int flag = 1, height;
    do  //prompting for input
    {
        height = get_int("Height: ");
        if (height >= 1 && height <= 8) //checking whether height lies between 1-8
        {
            flag = 0;
        }
    }
    while (flag != 0);

    for (int i = height; i >= 1; i--) //for rows
    {
        for (int j = 1; j <= i - 1; j++) //for spaces
        {
            printf(" ");
        }
        
        for (int k = i; k <= height; k++) //for hashes
        {
            printf("#");
        }
        printf("\n");
    }
}