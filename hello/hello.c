#include <stdio.h> //importing standardio library
#include <cs50.h> //importing cs50's library

int main(void)
{
    string name = get_string("What is your name? "); //Asking for user-input
    printf("hello, %s\n", name); //Printing user's name
}